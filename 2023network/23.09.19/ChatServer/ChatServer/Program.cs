using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Threading;
using System.Collections;
using System.Text;

namespace ChatServer
{
    internal class Program
    {
        public static Hashtable clientsList = new Hashtable();
        private static int userCount = 0;
        private static Mutex mut = new Mutex();

        static void Main(string[] args)
        {
            try
            {
                TcpListener serverSocket = new TcpListener(IPAddress.Any, 8888);
                TcpClient clientSocket = null;
                int counter = 0;
                byte[] bytesFrom = new byte[1024];

                serverSocket.Start();
                Console.WriteLine("C# Server Started");

                while(true)
                {
                    clientSocket = serverSocket.AcceptTcpClient();
                    NetworkStream stream = clientSocket.GetStream();

                    counter = userCount;
                    userCount++;

                    ClientHandle client = new ClientHandle();
                    clientsList.Add(counter, client);
                    client.StartClient(clientSocket, clientsList, counter);
                }

                clientSocket.Close();
                serverSocket.Stop();

                Console.WriteLine("exit");
                Console.ReadLine();
            }
            catch (Exception err)
            {
                Console.WriteLine(err.Message);
            }
        }

        public static TcpClient GetSocket(int id)
        {
            TcpClient socket = null;
            if(clientsList.ContainsKey(id))
            {
                ClientHandle clientHandle = clientsList[id] as ClientHandle;
                socket = clientHandle.clientSocket;
            }

            return socket;
        }

        public static void Send(int destination, string msg, string userName, bool flag)
        {
            mut.WaitOne();
            byte[] broadcastBytes;

            if (flag == true)
            {
                broadcastBytes = Encoding.UTF8.GetBytes(userName + '$' + msg);
            }
            else
            {
                broadcastBytes = Encoding.UTF8.GetBytes(msg);
            }

            TcpClient broadcastSocket;
            ClientHandle handle = clientsList[destination] as ClientHandle;
            broadcastSocket = handle.clientSocket;

            NetworkStream broadcastStream = broadcastSocket.GetStream();
            broadcastStream.Write(broadcastBytes, 0, broadcastBytes.Length);
            broadcastStream.Flush();

            mut.ReleaseMutex();
        }

        public static void BroadCast(string msg, string userName, bool flag)
        {
            mut.WaitOne();
            byte[] broadcastBytes;

            if(flag == true)
            {
                broadcastBytes = Encoding.UTF8.GetBytes(userName + '$' + msg);
            }
            else
            {
                broadcastBytes = Encoding.UTF8.GetBytes(msg);
            }

            foreach(DictionaryEntry item in clientsList)
            {
                TcpClient broadcastSocket;
                ClientHandle handle = item.Value as ClientHandle;
                broadcastSocket = handle.clientSocket;

                NetworkStream broadcastStream = broadcastSocket.GetStream();
                broadcastStream.Write(broadcastBytes, 0, broadcastBytes.Length);
                broadcastStream.Flush();
            }

            mut.ReleaseMutex();
        }

        public static void UserAdd(string userName)
        {
            BroadCast(userName + " Joined", "", false);
            Console.WriteLine($"{userName} Joined Chat Room");
        }

        public static void UserLeft(int userID, string userName)
        {
            if(clientsList.ContainsKey(userID))
            {
                BroadCast($"{userName} Left", "", false);
                Console.WriteLine($"{userName} Left Chat Room");

                TcpClient clientSocket = GetSocket(userID);
                clientsList.Remove(userID);
                clientSocket.Close();
            }
        }

    }
}
