using System;
using System.Windows.Forms;
using System.Threading.Tasks;
using System.Threading;
using System.Diagnostics;

namespace ReceiveDataCS
{
    public partial class Form1 : Form
    {
        public bool RunFlags = true;
        public Thread ReceiveThread = null;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            ReceiveThread = new Thread(ReceiveData);
            ReceiveThread.Start();
        }

        private void ReceiveData()
        {
            while (RunFlags)
            {
                Thread.Sleep(1);
                foreach (var process in Process.GetProcesses())
                {
                    if (process.ProcessName == "SendDataCS")
                    {
                        RunFlags = false;
                        label2.Text = SendDataCS.Form1.SendData;
                    }
                }
            }

            ReceiveThread.Abort();
        }
    }
}
