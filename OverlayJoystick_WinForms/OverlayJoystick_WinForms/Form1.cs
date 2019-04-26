using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace OverlayJoystick_WinForms
{
    public partial class Form1 : Form
    {
        Overlay frm = new Overlay();
        Process[] procList = Process.GetProcesses();

        public Form1()
        {
            InitializeComponent();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            frm.WINDOW_NAME = comboBox1.Items[comboBox1.SelectedIndex].ToString();
            if(checkBox1.Checked == true)
            {
                frm.Show();
            }
            else
            {
                frm.Hide();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            foreach (Process proc in procList)
            {
                if(!String.IsNullOrEmpty(proc.MainWindowTitle)) comboBox1.Items.Add(proc.MainWindowTitle);
            }
        }
    }
}
