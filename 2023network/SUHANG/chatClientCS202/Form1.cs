﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Net.Sockets;
using System.Threading;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace chatClientCS202
{
    public partial class Form1 : Form
    {
        TcpClient clientSocket = new TcpClient();
        NetworkStream serverStream = default;
        string readData = null; //텍스트박스2에 출력할 메세지
        bool isRunning = true;

        public Form1()
        {
            InitializeComponent();
        }

        //메세지 박스에 출력
        private void Msg()
        {
            if (InvokeRequired)
            {
                Invoke(new MethodInvoker(Msg));
            } //다시 호출되었을 때는 권한 얻어서 UI 변경
            else textBox2.Text += Environment.NewLine + " >> " + readData;
        }

        //서버에서 메세지 데이터 수신
        private void GetMessage()
        {
            byte[] inStream = new byte[1024];
            string returnData;

            try
            {   //서버와 연결되어 있는 동안에는 계속해서 데이터 수신
                while (isRunning)
                {
                    serverStream = clientSocket.GetStream();
                    int buffsize = clientSocket.ReceiveBufferSize;
                    int numBytesRead;

                    if (serverStream.DataAvailable)
                    {
                        returnData = "";
                        while (serverStream.DataAvailable)
                        {
                            numBytesRead = serverStream.Read(inStream, 0, inStream.Length);
                            returnData += Encoding.UTF8.GetString(inStream, 0, numBytesRead);
                        }//end while
                        readData = returnData;

                        if(readData == "err")
                        {
                            // 밴 당한 상황
                            isRunning = false;
                            serverStream.Close();
                            clientSocket.Close();

                            Application.Exit();
                        }
                        else
                            Msg();
                    }//end if
                }//end while
            }//try
            catch(Exception ex)
            {
                isRunning = false;
                Console.Write(ex.ToString());
            }
        }

        private void connect_Click(object sender, EventArgs e)
        {
            //1. 서버와 연결
            readData = "Connected to Chat Server...";
            Msg();
            clientSocket.Connect("localhost", 8888);
            serverStream = clientSocket.GetStream();

            //2. 닉네임 전달
            byte[] outStream = Encoding.UTF8.GetBytes(textBox1.Text + "$");
            serverStream.Write(outStream, 0, outStream.Length);
            serverStream.Flush();//초기화

            //3. 스레드 생성 후 데이터 수신
            Thread ctThread = new Thread(GetMessage);
            ctThread.Start();
        }
        //채팅 내용 서버에 전송
        private void send_Click(object sender, EventArgs e)
        {
            if(textBox3.Text == "/clear") // 보내는 메세지가 clear면
            {
                // 채팅창 클리어
                textBox2.Clear();
                textBox3.Clear();
                return;
            }
            else if(textBox3.Text == "/quit") // 보내는 메세지가 quit면
            {
                // 나가기
                LogOutClicked(null, null);
                return;
            }

            byte[] outStream = Encoding.UTF8.GetBytes(textBox3.Text + "$");
            serverStream.Write(outStream, 0, outStream.Length);
            serverStream.Flush();//초기화
            textBox3.Clear();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            isRunning = false;
            serverStream.Close();
            clientSocket.Close();
        }

        private void LogOutClicked(object sender, EventArgs e)
        {
            byte[] outStream = Encoding.UTF8.GetBytes("LogoutReq$");
            serverStream.Write(outStream, 0, outStream.Length);
            serverStream.Flush();//초기화
        }
    }
}
