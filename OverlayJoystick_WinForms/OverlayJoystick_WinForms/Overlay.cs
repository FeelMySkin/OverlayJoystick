using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OverlayJoystick_WinForms
{
    public partial class Overlay : Form
    {
        RECT rect;
        public string WINDOW_NAME;

        public struct RECT
        {
            public int left, top, right, bottom;
        }

        [DllImport("user32.dll", SetLastError = true)]
        static extern IntPtr FindWindow(string lpClassName, string lpWindowName);
        [DllImport("user32.dll", SetLastError = true)]
        private static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);
        [DllImport("user32.dll", SetLastError = true)]
        private static extern int GetWindowLong(IntPtr hWnd, int nIndex);
        [DllImport("user32.dll", SetLastError = true)]
        static extern bool GetWindowRect(IntPtr hwnd, out RECT lpRect);

        public Overlay()
        {
            InitializeComponent();
        }

        private void Overlay_Load(object sender, EventArgs e)
        {
            this.BackColor = Color.Wheat;
            this.TransparencyKey = Color.Wheat;
            this.TopMost = true;
            this.FormBorderStyle = FormBorderStyle.None;
        }

        private void Overlay_VisibleChanged(object sender, EventArgs e)
        {
            
            if (!this.Visible) return;
            label1.Text = new Random((int)DateTime.Now.ToBinary()).Next().ToString();

            int initialStyle = GetWindowLong(this.Handle, -20);
            //SetWindowLong(this.Handle, -20, initialStyle | 0x80000 | 0x20);
            SetWindowLong(this.Handle, -20, initialStyle | 0x08000000 | 0x8);

            IntPtr handle = FindWindow(null, WINDOW_NAME);
            GetWindowRect(handle, out rect);
            this.Size = new Size(rect.right - rect.left, rect.bottom - rect.top);
            this.Top = rect.top;
            this.Left = rect.left;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (this.BackColor == Color.Wheat) this.BackColor = Color.Gray;
            else this.BackColor = Color.Wheat;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SendKeys.Send(Keys.A.ToString());
        }
    }
}
