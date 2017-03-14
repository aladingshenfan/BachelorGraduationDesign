using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Emgu.CV;
using Emgu.Util;
using Emgu.CV.UI;
using Emgu.CV.CvEnum;
using Emgu.CV.Structure;
using Emgu.CV.Tracking;

namespace TrackingProject
{
    public partial class MainForm : Form
    {
        private VideoCapture capture;
        private Mat Frame;
        private Mat InitialTargetImage;
        private Mat CurrentTagetImage;
        private int VideoFps=30;
        private bool StartSelect = false;
        private bool HaveSelected = false;
        private Rectangle BoundingBox;
        static string TrackerType;
        Tracker tracker;

        public MainForm()
        {
            InitializeComponent();
        }

        private void ProcessFrame(object sender, EventArgs e)
        {
            bool HaveInitialized = false;
            Frame = capture.QueryFrame();
            if(Frame != null)
            {
                if (HaveSelected && TrackerType != "")
                {
                    if (!HaveInitialized)
                    {
                        if (!tracker.Init(Frame, BoundingBox))
                        {
                            HaveSelected = false;
                        }
                        HaveInitialized = true;
                    }
                    else
                    {
                        if (tracker.Update(Frame, out BoundingBox))
                        {
                            CvInvoke.Rectangle(Frame, BoundingBox, new MCvScalar(0, 0, 255), 2);
                        }
                    }
                }               
                System.Threading.Thread.Sleep((int)(1000.0 / VideoFps - 5));
                VideoBox.Image = Frame;
                GC.Collect();
            }
        }

        /// <summary>
        /// VideoCapture(string filename)
        /// filename--It can be name of video file (eg. video.avi)
        /// or image sequence (eg. img_%02d.jpg, which will read samples like img_00.jpg, img_01.jpg, img_02.jpg, ...)
        /// or URL of video stream (eg. protocol://host:port/script_name?script_params|auth).
        /// Note that each video stream or IP camera feed has its own URL scheme. Please refer to the documentation of source stream to know the right URL. 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OpenButton_Click(object sender, EventArgs e)
        {
            if (VideoSourceComboBox.Text != "" && TrackerComboBox.Text != "")
            {
                switch (VideoSourceComboBox.Text)
                {
                    case "视频文件":
                        {
                            HaveSelected = false;
                            OpenFileDialog openfiledialog = new OpenFileDialog();
                            openfiledialog.Filter = "AVI文件|*.avi|RMVB文件|*.rmvb|WMV文件|*.wmv|MKV文件|*.mkv|所有文件|*.*";
                            if (openfiledialog.ShowDialog() == DialogResult.OK)
                            {
                                capture = new VideoCapture(openfiledialog.FileName);
                                Application.Idle += new EventHandler(ProcessFrame);
                                VideoFps = (int)capture.GetCaptureProperty(Emgu.CV.CvEnum.CapProp.Fps);
                                capture.SetCaptureProperty(Emgu.CV.CvEnum.CapProp.FrameWidth, VideoBox.Width);
                                capture.SetCaptureProperty(Emgu.CV.CvEnum.CapProp.FrameHeight, VideoBox.Height);
                            }
                            break;
                        }
                    case "本地摄像头":
                        {
                            HaveSelected = false;
                            capture = new VideoCapture(0);
                            Application.Idle += new EventHandler(ProcessFrame);
                            capture.SetCaptureProperty(Emgu.CV.CvEnum.CapProp.FrameWidth, VideoBox.Width);
                            capture.SetCaptureProperty(Emgu.CV.CvEnum.CapProp.FrameHeight, VideoBox.Height);
                            break;
                        }
                    case "视频图片序列":
                        {
                            HaveSelected = false;
                            string filename = SetVideoSourceTextBox.Text + "//%04d.jpg";
                            capture = new VideoCapture(filename);
                            Application.Idle += new EventHandler(ProcessFrame);
                            break;
                        }
                    case "远程IP摄像头":
                        {
                            HaveSelected = false;
                            string VideoStreamAdress = SetVideoSourceTextBox.Text;
                            capture = new VideoCapture(VideoStreamAdress);
                            Application.Idle += new EventHandler(ProcessFrame);
                            capture.SetCaptureProperty(Emgu.CV.CvEnum.CapProp.FrameWidth, VideoBox.Width);
                            capture.SetCaptureProperty(Emgu.CV.CvEnum.CapProp.FrameHeight, VideoBox.Height);
                            break;
                        }
                    default: break;
                }
            }
            else
                MessageBox.Show("请先选择视频源以及跟踪器!");
        }

        private void PauseButton_Click(object sender, EventArgs e)
        {
            if (PauseButton.Text == "暂停播放")
            {
                CvInvoke.CvtColor(Frame, Frame, Emgu.CV.CvEnum.ColorConversion.Bgr2Gray);
                VideoBox.Image = Frame;
                Application.Idle -= new EventHandler(ProcessFrame);
                PauseButton.Text = "继续播放";
            }
            else
            {
                Application.Idle += new EventHandler(ProcessFrame);
                PauseButton.Text = "暂停播放";
            }
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            capture = new VideoCapture();
            capture.Dispose();
            Application.Idle -= new EventHandler(ProcessFrame);
            VideoBox.Image = null;
            PauseButton.Text = "暂停播放";
        }

        private void ExitButton_Click(object sender, EventArgs e)
        {
            System.Environment.Exit(0);
        }

        private void VideoSourceComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (VideoSourceComboBox.Text == "视频图片序列")
            {
                SetVideoSourceLabel.Visible = true;
                SetVideoSourceLabel.Enabled = true;
                SetVideoSourceLabel.Text = "视频序列文件夹";
                SetVideoSourceTextBox.Visible = true;
                SetVideoSourceTextBox.Enabled = true;
            }
            else if (VideoSourceComboBox.Text == "远程IP摄像头")
            {
                SetVideoSourceLabel.Visible = true;
                SetVideoSourceLabel.Enabled = true;
                SetVideoSourceLabel.Text = "视频流IP地址";
                SetVideoSourceTextBox.Visible = true;
                SetVideoSourceTextBox.Enabled = true;
            }
            else 
            {
                SetVideoSourceLabel.Visible = false;
                SetVideoSourceLabel.Enabled = false;
                SetVideoSourceTextBox.Visible = false;
                SetVideoSourceTextBox.Enabled = false;
            }
        }

        private void VideoBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                StartSelect = true;
                BoundingBox.X = e.X;
                BoundingBox.Y = e.Y;
                BoundingBox.Width = BoundingBox.Height = 0;
            }
        }

        private void VideoBox_MouseMove(object sender, MouseEventArgs e)
        {
            if (StartSelect && !HaveSelected)
            {
                BoundingBox.Width = e.X - BoundingBox.X;
                BoundingBox.Height = e.Y - BoundingBox.Y;
            }
        }

        private void VideoBox_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                StartSelect = false;
                HaveSelected = true;
                if (BoundingBox.Width < 0)
                {
                    BoundingBox.X += BoundingBox.Width;
                    BoundingBox.Width *= -1;
                }
                if (BoundingBox.Height < 0)
                {
                    BoundingBox.Y += BoundingBox.Height;
                    BoundingBox.Height *= -1;
                }
                CvInvoke.Rectangle(Frame, BoundingBox, new MCvScalar(0, 0, 255), 2);
                VideoBox.Image = Frame;
            }
        }

        private void TrackerComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(TrackerComboBox.Text!="")
            {
                TrackerType = TrackerComboBox.Text;
                tracker = new Tracker(TrackerType);
            }
        }
    }
}
