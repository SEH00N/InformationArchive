using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using UnityEngine;

public class SocketModule : MonoBehaviour
{
    public static SocketModule Instance = null;

    private TcpClient clientSocket;
    private NetworkStream serverStream = default;
    private string nickname;
    private bool isRunning = false;

    public void Login(string id)
    {
        if(!isRunning)
        {
            clientSocket = new TcpClient();
            IPAddress address = IPAddress.Parse("127.0.0.1");
            clientSocket.Connect(address, 8888);
            serverStream = clientSocket.GetStream();

            byte[] outStream = Encoding.UTF8.GetBytes(id + "$");
            serverStream.Write(outStream, 0, outStream.Length);
            serverStream.Flush();

            isRunning= true;
            nickname = id;
        }
    }

    public void SendData(string str)
    {
        if(isRunning && serverStream != null)
        {
            byte[] outStream = Encoding.UTF8.GetBytes("$" + str);
            serverStream.Write(outStream, 0, outStream.Length);
            serverStream.Flush();
        }
    }

    public void Logout()
    {
        if(isRunning)
        {
            isRunning = false;
            nickname = "";
        }

        if(serverStream != null)
        {
            serverStream.Close();
            serverStream = null;
        }

        clientSocket.Close();
    }

    private void GetMessage()
    {
        byte[] inStream = new byte[1024];
        string returnData = "";

        try {
            while(isRunning)
            {
                serverStream = clientSocket.GetStream();
                int buffSize = clientSocket.ReceiveBufferSize;
                int numBytesRead;

                if(serverStream.DataAvailable)
                {
                    while(serverStream.DataAvailable)
                    {
                        numBytesRead = serverStream.Read(inStream, 0, buffSize);
                        returnData += Encoding.UTF8.GetString(inStream, 0, numBytesRead);
                    }
                }
            }
        } catch (Exception err) {
            isRunning = false;
            Debug.LogWarning(err);
        }
    }
}
