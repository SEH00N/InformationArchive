using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Collections;
using System.Threading;

//멀티쓰레드를 이용한 C# 채팅 서버
namespace ChatServerCS201
{
    class Program
    {
        const char CHAR_TERMINATOR = ';'; //메세지 맨 끝
        const char CHAR_NAME = '$'; //닉네임 구분

        //사용자 관리 해시테이블
        public static Hashtable clientsList = new Hashtable();
        private static int userCount = 0;
        private static Mutex mut = new Mutex();

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
                Console.WriteLine("C# server started");

                while (true)
                {
                    //Accept()
                    clientSocket = serverSocket.AcceptTcpClient();
                    NetworkStream networkStream = clientSocket.GetStream();

                    counter = userCount;
                    userCount++;

                    handleClient client = new handleClient();
                    clientsList.Add(counter, client);
                    client.StartClient(clientSocket, clientsList, counter);
                }
                clientSocket.Close();
                serverSocket.Stop();
                Console.WriteLine("exit");
                Console.ReadLine();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }

        //클라 고유 ID로 해당 소켓 반환
        public static TcpClient GetSocket(int id)
        {
            TcpClient socket = null;
            if (clientsList.ContainsKey(id))
            {
                handleClient hc = (handleClient)clientsList[id];
                socket = hc.clientSocket;
            }
            return socket;
        }

        //브로드캐스트 (접속 중인 모든 클라한테 메세지 뿌리기)
        public static void BroadCast(string msg, string uName, bool flag)
        {
            byte[] broadcastBytes;
            List<object> deleteClients = new List<object>(); //삭제된 클라이언트 리스트

            //1. 클라이언트가 보내는 브로드캐스트
            if (flag == true)
            {
                broadcastBytes = Encoding.UTF8.GetBytes($"{uName}{CHAR_NAME}{msg}{CHAR_TERMINATOR}");
                //ex) 곽석현$안녕하세요;
            }
            //2. 서버에서 보내는 브로드캐스트
            else
            {
                broadcastBytes = Encoding.UTF8.GetBytes($"{msg}{CHAR_TERMINATOR}");
            }
            mut.WaitOne();
            foreach (DictionaryEntry Item in clientsList)
            {

                TcpClient broadcastSocket;
                handleClient hc = (handleClient)Item.Value;
                broadcastSocket = hc.clientSocket;
                NetworkStream broadcastStream = broadcastSocket.GetStream();
                //Send()
                try
                {
                    broadcastStream.Write(broadcastBytes, 0, broadcastBytes.Length);
                    broadcastStream.Flush();
                }
                catch (Exception ex)
                {
                    deleteClients.Add(Item.Key);
                }
            }
            mut.ReleaseMutex();
            foreach (var item in deleteClients)
            {
                TcpClient broadCastSocket;
                handleClient hc = (handleClient)clientsList[item];
                broadCastSocket = hc.clientSocket;
                broadCastSocket.Close();
                clientsList.Remove(item);
            }

        }//end broadcast // 응용) 고유 id, 닉네임 검색해서 1:1 귓속말 기능

        public static void UserAdd(string userName)
        {
            BroadCast($"{userName}{CHAR_NAME}#Enter#", "", false);
            Console.WriteLine(userName + " Joined chat room");
        }

        public static void UserLeft(int userID, string userName)
        {
            if (clientsList.ContainsKey(userID))
            {
                BroadCast($"{userName}{CHAR_NAME}#Left#", "", false);
                Console.WriteLine(userName + " Left chat room");
                TcpClient clientSocket = GetSocket(userID);
                clientsList.Remove(userID);
                clientSocket.Close();
            }
        }
    }//end Main class

    public class handleClient
    {
        const string COMMAND_MOVE = "#Move#";
        const char CHAR_TERMINATOR = ';';

        public TcpClient clientSocket;
        public int userID; //고유 ID
        public string userName; //닉네임

        public Hashtable clientsList;
        private bool noConnection = false;

        public float posX;
        public float posY;

        public void StartClient(TcpClient inClientSocket, Hashtable cList, int userSerial)
        {
            userID = userSerial;
            this.clientSocket = inClientSocket;
            this.clientsList = cList;

            Thread ctThread = new Thread(DoChat);
            ctThread.Start();
        }

        //소켓 연결 상태 확인. socket.connected로 잡지 못 하는 부분 검사
        bool SocketConnected(Socket s)
        {
            bool part1 = s.Poll(1000, SelectMode.SelectRead);
            bool part2 = (s.Available == 0); //읽어들일 데이터가 없으면 True
            if (part1 && part2)
            {
                return false;
            }
            else return true;
        }

        //스레드가 할 일. 채팅 메소드
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
                        Program.UserLeft(userID, userName);
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

                                int idx = dataFromClient.IndexOf('$');

                                //처음 접속. 닉네임 추출 후 저장
                                if (userName == null && idx > 0)
                                {
                                    NetworkStream stream = clientSocket.GetStream();
                                    StringBuilder message = new StringBuilder("#UserInfo#");
                                    foreach(DictionaryEntry item in Program.clientsList)
                                    {
                                        handleClient hc = item.Value as handleClient;
                                        message.Append($"{hc.userName}/{hc.posX}/{hc.posY},");
                                    }
                                    message.Append(";");

                                    byte[] data = Encoding.UTF8.GetBytes(message.ToString());
                                    stream.Write(data, 0, data.Length);
                                    stream.Flush();

                                    userName = dataFromClient.Substring(0, idx);
                                    Console.WriteLine($"{userName} Enter Chat room");
                                    Program.UserAdd(userName);
                                }
                                //채팅 보냄
                                int pos = idx + 1;
                                if (pos < dataFromClient.Length)
                                {
                                    dataFromClient = dataFromClient.Substring(pos, dataFromClient.Length - pos);
                                    Console.WriteLine("From client - " + userName + ": " + dataFromClient);
                                    ProcessCommand(userName, dataFromClient);
                                    Program.BroadCast(dataFromClient, userName, true);
                                    //ex) From client - 곽석현: 안녕하세요
                                }
                                else
                                {
                                    dataFromClient = "";
                                }
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    noConnection = true;
                    Console.WriteLine("Error: " + ex.ToString());
                }
            }//end while
        }//end DoChat

        private string DeleteTerminator(string remain)
        {
            int idx = remain.IndexOf(CHAR_TERMINATOR);
            if (idx > 0)
            {
                remain = remain.Substring(0, idx);
            }
            return remain;
        }

        private void ProcessMove(string clientName, string remain)
        {
            var strs = remain.Split(',');
            try
            {
                posX = float.Parse(strs[0]);
                posY = float.Parse(strs[1]);
                Console.Write($"User Move-{clientName} to {posX} , {posY}");

            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }

        private void ProcessCommand(string clientName, string dataFromClient)
        {
            if (dataFromClient[0] == '#')
            {
                string command;
                string remain;
                int idx = dataFromClient.IndexOf('#', 1);
                if (idx > 1)
                {
                    //#Move#12.4564,7.45987;
                    command = dataFromClient.Substring(0, idx + 1);
                    if (command == COMMAND_MOVE)
                    {   //12.4564,7.45987
                        remain = DeleteTerminator(dataFromClient.Substring(idx + 1));
                        ProcessMove(clientName, remain);
                    }
                }
            }
        }
    }
}