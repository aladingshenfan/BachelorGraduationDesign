namespace TrackingProject
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.VideoBox = new Emgu.CV.UI.ImageBox();
            this.VideoSourceComboBox = new System.Windows.Forms.ComboBox();
            this.VideoSourceLabel = new System.Windows.Forms.Label();
            this.ExitButton = new System.Windows.Forms.Button();
            this.PauseButton = new System.Windows.Forms.Button();
            this.StopButton = new System.Windows.Forms.Button();
            this.OpenButton = new System.Windows.Forms.Button();
            this.TragetSourceLabel = new System.Windows.Forms.Label();
            this.TargetSourceComboBox = new System.Windows.Forms.ComboBox();
            this.TrackerLabel = new System.Windows.Forms.Label();
            this.TrackerComboBox = new System.Windows.Forms.ComboBox();
            this.PreviousFrameBox = new Emgu.CV.UI.ImageBox();
            this.CurrentFrameBox = new Emgu.CV.UI.ImageBox();
            this.SetVideoSourceLabel = new System.Windows.Forms.Label();
            this.SetVideoSourceTextBox = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.VideoBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.PreviousFrameBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.CurrentFrameBox)).BeginInit();
            this.SuspendLayout();
            // 
            // VideoBox
            // 
            this.VideoBox.BackColor = System.Drawing.Color.Silver;
            this.VideoBox.FunctionalMode = Emgu.CV.UI.ImageBox.FunctionalModeOption.RightClickMenu;
            this.VideoBox.Location = new System.Drawing.Point(12, 12);
            this.VideoBox.Name = "VideoBox";
            this.VideoBox.Size = new System.Drawing.Size(640, 480);
            this.VideoBox.TabIndex = 2;
            this.VideoBox.TabStop = false;
            this.VideoBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.VideoBox_MouseDown);
            this.VideoBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.VideoBox_MouseMove);
            this.VideoBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.VideoBox_MouseUp);
            // 
            // VideoSourceComboBox
            // 
            this.VideoSourceComboBox.FormattingEnabled = true;
            this.VideoSourceComboBox.Items.AddRange(new object[] {
            "视频文件",
            "本地摄像头",
            "视频图片序列",
            "远程IP摄像头"});
            this.VideoSourceComboBox.Location = new System.Drawing.Point(708, 12);
            this.VideoSourceComboBox.Name = "VideoSourceComboBox";
            this.VideoSourceComboBox.Size = new System.Drawing.Size(141, 20);
            this.VideoSourceComboBox.TabIndex = 3;
            this.VideoSourceComboBox.SelectedIndexChanged += new System.EventHandler(this.VideoSourceComboBox_SelectedIndexChanged);
            // 
            // VideoSourceLabel
            // 
            this.VideoSourceLabel.AutoSize = true;
            this.VideoSourceLabel.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.VideoSourceLabel.Location = new System.Drawing.Point(658, 15);
            this.VideoSourceLabel.Name = "VideoSourceLabel";
            this.VideoSourceLabel.Size = new System.Drawing.Size(44, 17);
            this.VideoSourceLabel.TabIndex = 4;
            this.VideoSourceLabel.Text = "视频源";
            // 
            // ExitButton
            // 
            this.ExitButton.Location = new System.Drawing.Point(774, 469);
            this.ExitButton.Name = "ExitButton";
            this.ExitButton.Size = new System.Drawing.Size(75, 23);
            this.ExitButton.TabIndex = 5;
            this.ExitButton.Text = "退出系统";
            this.ExitButton.UseVisualStyleBackColor = true;
            this.ExitButton.Click += new System.EventHandler(this.ExitButton_Click);
            // 
            // PauseButton
            // 
            this.PauseButton.Location = new System.Drawing.Point(773, 440);
            this.PauseButton.Name = "PauseButton";
            this.PauseButton.Size = new System.Drawing.Size(75, 23);
            this.PauseButton.TabIndex = 6;
            this.PauseButton.Text = "暂停播放";
            this.PauseButton.UseVisualStyleBackColor = true;
            this.PauseButton.Click += new System.EventHandler(this.PauseButton_Click);
            // 
            // StopButton
            // 
            this.StopButton.Location = new System.Drawing.Point(662, 469);
            this.StopButton.Name = "StopButton";
            this.StopButton.Size = new System.Drawing.Size(75, 23);
            this.StopButton.TabIndex = 7;
            this.StopButton.Text = "停止播放";
            this.StopButton.UseVisualStyleBackColor = true;
            this.StopButton.Click += new System.EventHandler(this.StopButton_Click);
            // 
            // OpenButton
            // 
            this.OpenButton.Location = new System.Drawing.Point(662, 440);
            this.OpenButton.Name = "OpenButton";
            this.OpenButton.Size = new System.Drawing.Size(75, 23);
            this.OpenButton.TabIndex = 8;
            this.OpenButton.Text = "打开视频";
            this.OpenButton.UseVisualStyleBackColor = true;
            this.OpenButton.Click += new System.EventHandler(this.OpenButton_Click);
            // 
            // TragetSourceLabel
            // 
            this.TragetSourceLabel.AutoSize = true;
            this.TragetSourceLabel.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.TragetSourceLabel.Location = new System.Drawing.Point(658, 45);
            this.TragetSourceLabel.Name = "TragetSourceLabel";
            this.TragetSourceLabel.Size = new System.Drawing.Size(44, 17);
            this.TragetSourceLabel.TabIndex = 9;
            this.TragetSourceLabel.Text = "目标源";
            // 
            // TargetSourceComboBox
            // 
            this.TargetSourceComboBox.FormattingEnabled = true;
            this.TargetSourceComboBox.Location = new System.Drawing.Point(708, 42);
            this.TargetSourceComboBox.Name = "TargetSourceComboBox";
            this.TargetSourceComboBox.Size = new System.Drawing.Size(141, 20);
            this.TargetSourceComboBox.TabIndex = 10;
            this.TargetSourceComboBox.Text = "暂时不可用";
            // 
            // TrackerLabel
            // 
            this.TrackerLabel.AutoSize = true;
            this.TrackerLabel.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.TrackerLabel.Location = new System.Drawing.Point(659, 76);
            this.TrackerLabel.Name = "TrackerLabel";
            this.TrackerLabel.Size = new System.Drawing.Size(44, 17);
            this.TrackerLabel.TabIndex = 11;
            this.TrackerLabel.Text = "跟踪器";
            // 
            // TrackerComboBox
            // 
            this.TrackerComboBox.FormattingEnabled = true;
            this.TrackerComboBox.Items.AddRange(new object[] {
            "KCF",
            "TLD",
            "MIL",
            "BOOSTING",
            "MEDIANFLOW"});
            this.TrackerComboBox.Location = new System.Drawing.Point(709, 73);
            this.TrackerComboBox.Name = "TrackerComboBox";
            this.TrackerComboBox.Size = new System.Drawing.Size(139, 20);
            this.TrackerComboBox.TabIndex = 12;
            this.TrackerComboBox.SelectedIndexChanged += new System.EventHandler(this.TrackerComboBox_SelectedIndexChanged);
            // 
            // PreviousFrameBox
            // 
            this.PreviousFrameBox.FunctionalMode = Emgu.CV.UI.ImageBox.FunctionalModeOption.Minimum;
            this.PreviousFrameBox.Location = new System.Drawing.Point(661, 148);
            this.PreviousFrameBox.Name = "PreviousFrameBox";
            this.PreviousFrameBox.Size = new System.Drawing.Size(187, 140);
            this.PreviousFrameBox.TabIndex = 2;
            this.PreviousFrameBox.TabStop = false;
            // 
            // CurrentFrameBox
            // 
            this.CurrentFrameBox.FunctionalMode = Emgu.CV.UI.ImageBox.FunctionalModeOption.Minimum;
            this.CurrentFrameBox.Location = new System.Drawing.Point(662, 294);
            this.CurrentFrameBox.Name = "CurrentFrameBox";
            this.CurrentFrameBox.Size = new System.Drawing.Size(187, 140);
            this.CurrentFrameBox.TabIndex = 13;
            this.CurrentFrameBox.TabStop = false;
            // 
            // SetVideoSourceLabel
            // 
            this.SetVideoSourceLabel.AutoSize = true;
            this.SetVideoSourceLabel.Enabled = false;
            this.SetVideoSourceLabel.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.SetVideoSourceLabel.Location = new System.Drawing.Point(658, 107);
            this.SetVideoSourceLabel.Name = "SetVideoSourceLabel";
            this.SetVideoSourceLabel.Size = new System.Drawing.Size(92, 17);
            this.SetVideoSourceLabel.TabIndex = 14;
            this.SetVideoSourceLabel.Text = "视频序列文件夹";
            this.SetVideoSourceLabel.Visible = false;
            // 
            // SetVideoSourceTextBox
            // 
            this.SetVideoSourceTextBox.Enabled = false;
            this.SetVideoSourceTextBox.Location = new System.Drawing.Point(756, 103);
            this.SetVideoSourceTextBox.Name = "SetVideoSourceTextBox";
            this.SetVideoSourceTextBox.Size = new System.Drawing.Size(93, 21);
            this.SetVideoSourceTextBox.TabIndex = 15;
            this.SetVideoSourceTextBox.Visible = false;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(861, 504);
            this.Controls.Add(this.SetVideoSourceTextBox);
            this.Controls.Add(this.SetVideoSourceLabel);
            this.Controls.Add(this.CurrentFrameBox);
            this.Controls.Add(this.PreviousFrameBox);
            this.Controls.Add(this.TrackerComboBox);
            this.Controls.Add(this.TrackerLabel);
            this.Controls.Add(this.TargetSourceComboBox);
            this.Controls.Add(this.TragetSourceLabel);
            this.Controls.Add(this.OpenButton);
            this.Controls.Add(this.StopButton);
            this.Controls.Add(this.PauseButton);
            this.Controls.Add(this.ExitButton);
            this.Controls.Add(this.VideoSourceLabel);
            this.Controls.Add(this.VideoSourceComboBox);
            this.Controls.Add(this.VideoBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Text = "目标跟踪系统";
            ((System.ComponentModel.ISupportInitialize)(this.VideoBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.PreviousFrameBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.CurrentFrameBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Emgu.CV.UI.ImageBox VideoBox;
        private System.Windows.Forms.ComboBox VideoSourceComboBox;
        private System.Windows.Forms.Label VideoSourceLabel;
        private System.Windows.Forms.Button ExitButton;
        private System.Windows.Forms.Button PauseButton;
        private System.Windows.Forms.Button StopButton;
        private System.Windows.Forms.Button OpenButton;
        private System.Windows.Forms.Label TragetSourceLabel;
        private System.Windows.Forms.ComboBox TargetSourceComboBox;
        private System.Windows.Forms.Label TrackerLabel;
        private System.Windows.Forms.ComboBox TrackerComboBox;
        private Emgu.CV.UI.ImageBox PreviousFrameBox;
        private Emgu.CV.UI.ImageBox CurrentFrameBox;
        private System.Windows.Forms.Label SetVideoSourceLabel;
        private System.Windows.Forms.TextBox SetVideoSourceTextBox;
    }
}

