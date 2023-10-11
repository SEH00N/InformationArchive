using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Collections;
using System.Runtime.CompilerServices;

namespace chatServerCS202
{
    class Program
    {   //사용자 관리 해시테이블
        public static Hashtable clientsList = new Hashtable();
        private static int userCount = 0; //고유 ID
        private static Mutex mut = new Mutex();

        public static Dictionary<string, HandleClient> nicknameMap = new Dictionary<string, HandleClient>(); // 로그인 된 클라이언트 리스트

        public static bool IsVoting = false;
        public static string VotingTarget = "";
        public static int VoteCount = 0;

        static void Main(string[] args)
        {
            try
            {
                //Socket(), Bind()
                TcpListener serverSocket = new TcpListener(IPAddress.Any, 8888);
                TcpClient clientSocket = default;
                int counter = 0;
                byte[] bytesFrom = new byte[1024];

                //Listen()
                serverSocket.Start();
                Console.WriteLine("C# Server Started");

                while (true)
                {
                    //Accept()
                    clientSocket = serverSocket.AcceptTcpClient();
                    NetworkStream networkStream = clientSocket.GetStream();

                    counter = userCount;
                    userCount++;

                    //Accept한 클라이언트 처리
                    HandleClient client = new HandleClient();
                    clientsList.Add(counter, client);
                    client.StartClient(clientSocket, clientsList, counter);
                }//end while

                clientSocket.Close();
                serverSocket.Stop();
                Console.WriteLine("exit");
                Console.ReadLine();
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }//end Main

        //id값으로 해시테이블에서 해당 소켓 찾기
        public static TcpClient GetSocket(int id)
        {
            TcpClient socket = null;
            if (clientsList.ContainsKey(id))
            {
                HandleClient hc = (HandleClient)clientsList[id];
                socket = hc.clientSocket;
            }
            return socket;
        }

        // msg : 메세지
        // destination : 귓속말 할 사람 닉네임
        // sender : 귓속말을 보내는 사람 닉네임
        public static void Whisper(string msg, string destination, string sender)
        {
            mut.WaitOne(); // 락킹 걸고

            byte[] broadcastBytes = Encoding.UTF8.GetBytes($"whisper from {sender} : {msg}"); // 메세지 직렬화

            if(nicknameMap.ContainsKey(destination)) // 메세지를 보낼 사람이 현재 로그인 되어있으면
            {
                // 전송
                TcpClient broadcastSocket = nicknameMap[destination].clientSocket;
                NetworkStream broadcastStream = broadcastSocket.GetStream();

                broadcastStream.Write(broadcastBytes, 0, broadcastBytes.Length);
                broadcastStream.Flush();
            }

            mut.ReleaseMutex(); // 락커 릴리즈
        }

        //접속 중인 모든 클라이언트한테 메세지 뿌리기
        //응용) 닉네임, id 번호로 검색 해당 클라 메세지 보내기
        public static void Broadcast(string msg, string uName, bool flag)
        {
            mut.WaitOne();

            try
            {
                byte[] broadcastBytes;

                //1. 클라이언트가 보내는 메세지
                if (flag == true)
                {
                    broadcastBytes = Encoding.UTF8.GetBytes(uName + "$" + msg);
                    //ex) 경동엽$안녕하세요
                }
                //2. 서버가 보내는 메세지
                else
                {
                    broadcastBytes = Encoding.UTF8.GetBytes(msg);
                }
                foreach (DictionaryEntry Item in clientsList)
                {
                    TcpClient broadcastSocket;
                    HandleClient hc = (HandleClient)Item.Value;
                    broadcastSocket = hc.clientSocket;
                    NetworkStream broadcastStream = broadcastSocket.GetStream();
                    //Write() send()
                    broadcastStream.Write(broadcastBytes, 0, broadcastBytes.Length);
                    broadcastStream.Flush();
                }
            } catch { }

            mut.ReleaseMutex();
        }//end broadcast function

        public static bool UserAdd(string userName)
        {
            //서버에서 보내는 브로드캐스트 메세지
            if(nicknameMap.ContainsKey(userName)) // 이미 해당 닉네임이 사용중이라면
                return false; // 로그인 실패
            
            Broadcast(userName + " Joined", "", false);
            Console.WriteLine(userName + " Joined Chat room");

            return true; // 여기까지 왔다면 로그인 성공
        }

        public static void UserLeft(string userName, int userID)
        {
            try
            {
                if (clientsList.ContainsKey(userID))
                {
                    // 닉네임이 비어있는 상태라면 로그인 조차 되지 않은 상태
                    // 닉네임이 채워져 있을 때만 출력 & 브로드캐스팅
                    if (string.IsNullOrEmpty(userName) == false)
                    {
                        Console.WriteLine(userName + " Left Chat room");
                        nicknameMap.Remove(userName);
                        Broadcast(userName + " Left", "", false);
                    }

                    //소켓 닫기
                    TcpClient clientSocket = GetSocket(userID);
                    clientSocket.Close();
                    clientsList.Remove(userID);
                }
            }
            catch { }
        }

        public static void CheckVote()
        {
            int unvotedCount = 0;
            double targetCount = Math.Floor(clientsList.Count / (float)2);

            if (VoteCount > targetCount)
            {
                if(nicknameMap.ContainsKey(VotingTarget))
                {
                    byte[] broadcastBytes = Encoding.UTF8.GetBytes("err");
                    NetworkStream broadcastStream = nicknameMap[VotingTarget].clientSocket.GetStream();
                    broadcastStream.Write(broadcastBytes, 0, broadcastBytes.Length);
                    broadcastStream.Flush();

                    try
                    {
                        int userID = 0;
                        foreach (DictionaryEntry Item in clientsList)
                        {
                            HandleClient hc = (HandleClient)Item.Value;
                            Console.WriteLine(hc.userName + " " + VotingTarget);
                            if (hc.userName == VotingTarget)
                            {
                                userID = hc.userID;
                                break;
                            }
                        }
                        UserLeft(VotingTarget, userID);
                    }
                    catch { }
                }

                return;
            }

            foreach (DictionaryEntry Item in clientsList)
            {
                HandleClient hc = (HandleClient)Item.Value;
                if (hc.voted == false)
                    unvotedCount++;
            }

            if(targetCount - VoteCount > unvotedCount)
            {
                Broadcast($"{VotingTarget}의 투표가 취소되었습니다.", "GM", true);

                VoteCount = 0;
                VotingTarget = "";
                IsVoting = false;

                foreach (DictionaryEntry Item in clientsList)
                {
                    HandleClient hc = (HandleClient)Item.Value;
                    hc.voted = false;
                }
            }
        }
    }//end Main class

    class HandleClient
    {
        public TcpClient clientSocket;
        public int userID;
        public string userName;

        public Hashtable clientsList;
        public bool noConnection = false;
        public bool voted = false;

        public void StartClient(TcpClient inClientSocket, Hashtable cList, int userSerial)
        {
            userID = userSerial;
            this.clientSocket = inClientSocket;
            this.clientsList = cList;

            //스레드한테 채팅 일 시키기
            Thread ctThread = new Thread(DoChat);
            ctThread.Start();
        }

        //소켓 연결 상태 확인
        bool SocketConnected(Socket s)
        {
            bool part1 = s.Poll(1000, SelectMode.SelectRead);
            bool part2 = (s.Available == 0); //읽을 데이터가 없으면 part2 true
            if (part1 && part2)
            {
                return false;
            }
            else return true;
        }

        //스레드. 해당 클라한테 메세지를 받음
        private void DoChat()
        {
            byte[] bytesFrom = new byte[1024];
            string dataFromClient;
            NetworkStream networkStream = clientSocket.GetStream();

            while (!noConnection)
            {
                try
                {
                    int numBytesRead;
                    if (!SocketConnected(clientSocket.Client))
                    {
                        noConnection = true;
                    }
                    else
                    {
                        if (networkStream.DataAvailable)
                        {
                            dataFromClient = "";
                            while (networkStream.DataAvailable)
                            {
                                //Recv()
                                numBytesRead = networkStream.Read(bytesFrom, 0, bytesFrom.Length);
                                dataFromClient = Encoding.UTF8.GetString(bytesFrom, 0, numBytesRead);
                            }//end while
                            int idx = dataFromClient.IndexOf('$');

                            //처음 접속. 닉네임 전달
                            if(userName==null && idx > 0)
                            {
                                string tempName = dataFromClient.Substring(0, idx);
                                if (Program.UserAdd(tempName)) // 로그인이 성공했으면
                                {
                                    userName = tempName; // 닉네임 할당
                                    Program.nicknameMap.Add(userName, this);
                                }
                                else
                                {
                                    byte[] broadcastBytes = Encoding.UTF8.GetBytes("err");
                                    NetworkStream broadcastStream = clientSocket.GetStream();
                                    broadcastStream.Write(broadcastBytes, 0, broadcastBytes.Length);
                                    broadcastStream.Flush();

                                    Program.UserLeft(userName, userID);
                                    break;
                                }
                            }
                            //채팅 내용 전달
                            else if(idx> 1)
                            {
                                dataFromClient = dataFromClient.Substring(0, dataFromClient.Length-1);
                                Console.WriteLine(userName + ": " + dataFromClient);

                                if(Program.IsVoting && (voted == false) && (dataFromClient == "yes" || dataFromClient == "no"))
                                {
                                    if (dataFromClient == "yes")
                                    {
                                        Program.VoteCount++;
                                        Program.Whisper("찬성에 투표하셨습니다.", userName, "GM");
                                        voted = true;
                                    }
                                    else if(dataFromClient == "no")
                                    {
                                        Program.Whisper("반대에 투표하셨습니다.", userName, "GM");
                                        voted = true;
                                    }

                                    Program.CheckVote();
                                }
                                else if(dataFromClient == "LogoutReq") // 메세지가 LogoutReq면
                                {
                                    // 그냥 퇴장
                                    byte[] broadcastBytes = Encoding.UTF8.GetBytes("err");
                                    NetworkStream broadcastStream = clientSocket.GetStream();
                                    broadcastStream.Write(broadcastBytes, 0, broadcastBytes.Length);
                                    broadcastStream.Flush();

                                    Program.UserLeft(userName, userID);
                                    break;
                                }
                                else if(dataFromClient.IndexOf("/") == 0) // 메세지가 '/'로 시작하면 커맨드로 분류
                                {
                                    string[] commands = dataFromClient.Split(' '); // 메세지를 ' '를 기준으로 나눴을 때
                                    string command = commands[0]; // 커맨드는 0번째

                                    switch(command) // 스위치 케이스
                                    {
                                        case "/v":
                                            string target = commands[1];
                                            if (Program.IsVoting == true)
                                                Program.Whisper("이미 투표가 진행중에 있습니다.", userName, "GM");
                                            else if(Program.nicknameMap.ContainsKey(target) == false)
                                                Program.Whisper("투표 대상이 잘못되었습니다.", userName, "GM");
                                            else
                                            {
                                                Program.IsVoting = true;
                                                Program.VotingTarget = target;

                                                Program.Broadcast($"{target}의 퇴장 투표를 시작헀습니다. 찬성 : yes, 반대 : no", "GM", true);
                                            }
                                            break;
                                        case "/w": // 메세지가 '/w ' 로 시작하면 귓속말 처리
                                            
                                            if (commands.Length >= 3) // 최소 3개는 있어야 함 ex) '/w', '상대방', '메세지...'
                                            {
                                                string destination = commands[1]; // 상대방은 메세지를 ' '를 기준으로 나눴을 때 1번 인덱스에 위치하고
                                                string message = dataFromClient.Substring(dataFromClient.IndexOf(destination) + destination.Length + 1); // 메세지는 닉네임 뒤로 전부
                                                Program.Whisper(message, destination, userName); // 이 데이터를 가지고 귓속말
                                            }
                                            break;
                                    }
                                }
                                else // 귓속말이 아니라면
                                    Program.Broadcast(dataFromClient, userName, true); // 그냥 브로드 캐스팅
                                //경동엽: 안녕하세요
                            }
                            else
                            {
                                dataFromClient = "";
                            }
                        }
                    }
                }
                catch(Exception ex)
                {
                    noConnection = true;
                    Console.WriteLine("Error: " + ex.ToString());
                }
            }//end while
            Program.UserLeft(userName, userID);
        }
    }
}
