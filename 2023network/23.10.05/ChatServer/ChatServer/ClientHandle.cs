using System;
using System.Collections;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace ChatServer
{
    internal class ClientHandle
    {
        public TcpClient clientSocket;
        public int userID;
        public string userName;

        public Hashtable clientsList;
        private bool noConnection = false;

        public void StartClient(TcpClient inClientSocket, Hashtable cList, int userSerial)
        {
            userID = userSerial;
            this.clientSocket = inClientSocket;
            this.clientsList = cList;

            Thread clientThread = new Thread(DoChat);
            clientThread.Start();
        }

        private bool SocketConnected(Socket socket)
        {
            bool part1 = socket.Poll(1000, SelectMode.SelectRead);
            bool part2 = (socket.Available == 0);

            if(part1 && part2)
                return false;
            return true;
        }

        private void DoChat()
        {
            byte[] bytesFrom = new byte[1024];
            string dataFromClient;

            NetworkStream stream = clientSocket.GetStream();

            while(!noConnection)
            {
                try
                {
                    int numBytesRead;
                    if(!SocketConnected(clientSocket.Client))
                    {
                        noConnection = true;
                    }
                    else
                    {
                        if(stream.DataAvailable)
                        {
                            dataFromClient = "";
                            while(stream.DataAvailable)
                            {
                                numBytesRead = stream.Read(bytesFrom, 0, bytesFrom.Length);
                                dataFromClient = Encoding.UTF8.GetString(bytesFrom, 0, numBytesRead);

                                int idx = dataFromClient.IndexOf('$');

                                if(userName == null && idx > 0)
                                {
                                    userName = dataFromClient.Substring(0, idx);
                                    Program.UserAdd(userName);
                                }
                                else if(idx > 1)
                                {
                                    dataFromClient = dataFromClient.Substring(0, dataFromClient.Length - 1);
                                    Program.BroadCast(dataFromClient, userName, true);
                                    Console.WriteLine($"From Client - {userName}: {dataFromClient}");
                                }
                                else
                                {
                                    dataFromClient = "";
                                }
                            }
                        }
                    }
                } 
                catch(Exception err)
                {
                    noConnection = true;
                    Console.WriteLine($"Error: {err.Message}");
                }
            }
        }
    }
}
