namespace Quaternion_Calculator
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lblQ1 = new System.Windows.Forms.Label();
            this.lblQ2 = new System.Windows.Forms.Label();
            this.lblVecV = new System.Windows.Forms.Label();
            this.lblScale = new System.Windows.Forms.Label();
            this.lblAngle = new System.Windows.Forms.Label();
            this.tbQ1w = new System.Windows.Forms.TextBox();
            this.tbQ1x = new System.Windows.Forms.TextBox();
            this.tbQ1y = new System.Windows.Forms.TextBox();
            this.tbQ1z = new System.Windows.Forms.TextBox();
            this.tbQ2w = new System.Windows.Forms.TextBox();
            this.tbScale = new System.Windows.Forms.TextBox();
            this.tbVecX = new System.Windows.Forms.TextBox();
            this.tbQ2x = new System.Windows.Forms.TextBox();
            this.tbQ2y = new System.Windows.Forms.TextBox();
            this.tbQ2z = new System.Windows.Forms.TextBox();
            this.tbVecY = new System.Windows.Forms.TextBox();
            this.tbVecZ = new System.Windows.Forms.TextBox();
            this.tbAngle = new System.Windows.Forms.TextBox();
            this.tbAnswer = new System.Windows.Forms.TextBox();
            this.btnAdd = new System.Windows.Forms.Button();
            this.btnMultiply = new System.Windows.Forms.Button();
            this.btnScaler = new System.Windows.Forms.Button();
            this.btnNeg = new System.Windows.Forms.Button();
            this.btnSubtract = new System.Windows.Forms.Button();
            this.btnModulas = new System.Windows.Forms.Button();
            this.btnSwap = new System.Windows.Forms.Button();
            this.btnConjugate = new System.Windows.Forms.Button();
            this.btnRotate = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // lblQ1
            // 
            this.lblQ1.AutoSize = true;
            this.lblQ1.Location = new System.Drawing.Point(9, 26);
            this.lblQ1.Name = "lblQ1";
            this.lblQ1.Size = new System.Drawing.Size(74, 13);
            this.lblQ1.TabIndex = 0;
            this.lblQ1.Text = "Quaternion q1";
            // 
            // lblQ2
            // 
            this.lblQ2.AutoSize = true;
            this.lblQ2.Location = new System.Drawing.Point(10, 64);
            this.lblQ2.Name = "lblQ2";
            this.lblQ2.Size = new System.Drawing.Size(74, 13);
            this.lblQ2.TabIndex = 1;
            this.lblQ2.Text = "Quaternion q2";
            // 
            // lblVecV
            // 
            this.lblVecV.AutoSize = true;
            this.lblVecV.Location = new System.Drawing.Point(22, 107);
            this.lblVecV.Name = "lblVecV";
            this.lblVecV.Size = new System.Drawing.Size(47, 13);
            this.lblVecV.TabIndex = 2;
            this.lblVecV.Text = "Vector v";
            // 
            // lblScale
            // 
            this.lblScale.AutoSize = true;
            this.lblScale.Location = new System.Drawing.Point(22, 150);
            this.lblScale.Name = "lblScale";
            this.lblScale.Size = new System.Drawing.Size(45, 13);
            this.lblScale.TabIndex = 3;
            this.lblScale.Text = "Scalar s";
            // 
            // lblAngle
            // 
            this.lblAngle.AutoSize = true;
            this.lblAngle.Location = new System.Drawing.Point(179, 150);
            this.lblAngle.Name = "lblAngle";
            this.lblAngle.Size = new System.Drawing.Size(34, 13);
            this.lblAngle.TabIndex = 4;
            this.lblAngle.Text = "Angle";
            // 
            // tbQ1w
            // 
            this.tbQ1w.Location = new System.Drawing.Point(111, 23);
            this.tbQ1w.Name = "tbQ1w";
            this.tbQ1w.Size = new System.Drawing.Size(22, 20);
            this.tbQ1w.TabIndex = 5;
            this.tbQ1w.Text = "4";
            // 
            // tbQ1x
            // 
            this.tbQ1x.Location = new System.Drawing.Point(167, 23);
            this.tbQ1x.Name = "tbQ1x";
            this.tbQ1x.Size = new System.Drawing.Size(22, 20);
            this.tbQ1x.TabIndex = 6;
            this.tbQ1x.Text = "3";
            // 
            // tbQ1y
            // 
            this.tbQ1y.Location = new System.Drawing.Point(221, 23);
            this.tbQ1y.Name = "tbQ1y";
            this.tbQ1y.Size = new System.Drawing.Size(22, 20);
            this.tbQ1y.TabIndex = 7;
            this.tbQ1y.Text = "2";
            // 
            // tbQ1z
            // 
            this.tbQ1z.Location = new System.Drawing.Point(271, 23);
            this.tbQ1z.Name = "tbQ1z";
            this.tbQ1z.Size = new System.Drawing.Size(22, 20);
            this.tbQ1z.TabIndex = 8;
            this.tbQ1z.Text = "1";
            // 
            // tbQ2w
            // 
            this.tbQ2w.Location = new System.Drawing.Point(111, 61);
            this.tbQ2w.Name = "tbQ2w";
            this.tbQ2w.Size = new System.Drawing.Size(22, 20);
            this.tbQ2w.TabIndex = 9;
            this.tbQ2w.Text = "1";
            // 
            // tbScale
            // 
            this.tbScale.Location = new System.Drawing.Point(111, 143);
            this.tbScale.Name = "tbScale";
            this.tbScale.Size = new System.Drawing.Size(22, 20);
            this.tbScale.TabIndex = 10;
            this.tbScale.Text = "2";
            // 
            // tbVecX
            // 
            this.tbVecX.Location = new System.Drawing.Point(167, 104);
            this.tbVecX.Name = "tbVecX";
            this.tbVecX.Size = new System.Drawing.Size(22, 20);
            this.tbVecX.TabIndex = 11;
            this.tbVecX.Text = "1";
            // 
            // tbQ2x
            // 
            this.tbQ2x.Location = new System.Drawing.Point(167, 61);
            this.tbQ2x.Name = "tbQ2x";
            this.tbQ2x.Size = new System.Drawing.Size(22, 20);
            this.tbQ2x.TabIndex = 12;
            this.tbQ2x.Text = "2";
            // 
            // tbQ2y
            // 
            this.tbQ2y.Location = new System.Drawing.Point(221, 61);
            this.tbQ2y.Name = "tbQ2y";
            this.tbQ2y.Size = new System.Drawing.Size(22, 20);
            this.tbQ2y.TabIndex = 13;
            this.tbQ2y.Text = "3";
            // 
            // tbQ2z
            // 
            this.tbQ2z.Location = new System.Drawing.Point(271, 61);
            this.tbQ2z.Name = "tbQ2z";
            this.tbQ2z.Size = new System.Drawing.Size(22, 20);
            this.tbQ2z.TabIndex = 14;
            this.tbQ2z.Text = "4";
            // 
            // tbVecY
            // 
            this.tbVecY.Location = new System.Drawing.Point(221, 104);
            this.tbVecY.Name = "tbVecY";
            this.tbVecY.Size = new System.Drawing.Size(22, 20);
            this.tbVecY.TabIndex = 15;
            this.tbVecY.Text = "2";
            // 
            // tbVecZ
            // 
            this.tbVecZ.Location = new System.Drawing.Point(271, 104);
            this.tbVecZ.Name = "tbVecZ";
            this.tbVecZ.Size = new System.Drawing.Size(22, 20);
            this.tbVecZ.TabIndex = 16;
            this.tbVecZ.Text = "3";
            // 
            // tbAngle
            // 
            this.tbAngle.Location = new System.Drawing.Point(237, 143);
            this.tbAngle.Name = "tbAngle";
            this.tbAngle.Size = new System.Drawing.Size(33, 20);
            this.tbAngle.TabIndex = 17;
            this.tbAngle.Text = "120";
            // 
            // tbAnswer
            // 
            this.tbAnswer.Font = new System.Drawing.Font("Franklin Gothic Medium Cond", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbAnswer.Location = new System.Drawing.Point(25, 208);
            this.tbAnswer.Multiline = true;
            this.tbAnswer.Name = "tbAnswer";
            this.tbAnswer.Size = new System.Drawing.Size(268, 83);
            this.tbAnswer.TabIndex = 18;
            // 
            // btnAdd
            // 
            this.btnAdd.Location = new System.Drawing.Point(13, 308);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(75, 23);
            this.btnAdd.TabIndex = 19;
            this.btnAdd.Text = "q1 + q2";
            this.btnAdd.UseVisualStyleBackColor = true;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // btnMultiply
            // 
            this.btnMultiply.Location = new System.Drawing.Point(12, 363);
            this.btnMultiply.Name = "btnMultiply";
            this.btnMultiply.Size = new System.Drawing.Size(75, 23);
            this.btnMultiply.TabIndex = 20;
            this.btnMultiply.Text = "q1 * q2";
            this.btnMultiply.UseVisualStyleBackColor = true;
            this.btnMultiply.Click += new System.EventHandler(this.btnMultiply_Click);
            // 
            // btnScaler
            // 
            this.btnScaler.Location = new System.Drawing.Point(12, 413);
            this.btnScaler.Name = "btnScaler";
            this.btnScaler.Size = new System.Drawing.Size(75, 23);
            this.btnScaler.TabIndex = 21;
            this.btnScaler.Text = "q1 * s";
            this.btnScaler.UseVisualStyleBackColor = true;
            this.btnScaler.Click += new System.EventHandler(this.btnScaler_Click);
            // 
            // btnNeg
            // 
            this.btnNeg.Location = new System.Drawing.Point(114, 308);
            this.btnNeg.Name = "btnNeg";
            this.btnNeg.Size = new System.Drawing.Size(75, 23);
            this.btnNeg.TabIndex = 22;
            this.btnNeg.Text = "-q1";
            this.btnNeg.UseVisualStyleBackColor = true;
            this.btnNeg.Click += new System.EventHandler(this.btnNeg_Click);
            // 
            // btnSubtract
            // 
            this.btnSubtract.Location = new System.Drawing.Point(218, 308);
            this.btnSubtract.Name = "btnSubtract";
            this.btnSubtract.Size = new System.Drawing.Size(75, 23);
            this.btnSubtract.TabIndex = 23;
            this.btnSubtract.Text = "q1 - q2";
            this.btnSubtract.UseVisualStyleBackColor = true;
            this.btnSubtract.Click += new System.EventHandler(this.btnSubtract_Click);
            // 
            // btnModulas
            // 
            this.btnModulas.Location = new System.Drawing.Point(114, 363);
            this.btnModulas.Name = "btnModulas";
            this.btnModulas.Size = new System.Drawing.Size(75, 23);
            this.btnModulas.TabIndex = 24;
            this.btnModulas.Text = "| q1 |";
            this.btnModulas.UseVisualStyleBackColor = true;
            this.btnModulas.Click += new System.EventHandler(this.btnModulas_Click);
            // 
            // btnSwap
            // 
            this.btnSwap.Location = new System.Drawing.Point(114, 413);
            this.btnSwap.Name = "btnSwap";
            this.btnSwap.Size = new System.Drawing.Size(75, 23);
            this.btnSwap.TabIndex = 25;
            this.btnSwap.Text = "Swap";
            this.btnSwap.UseVisualStyleBackColor = true;
            this.btnSwap.Click += new System.EventHandler(this.btnSwap_Click);
            // 
            // btnConjugate
            // 
            this.btnConjugate.Location = new System.Drawing.Point(218, 363);
            this.btnConjugate.Name = "btnConjugate";
            this.btnConjugate.Size = new System.Drawing.Size(75, 23);
            this.btnConjugate.TabIndex = 26;
            this.btnConjugate.Text = "conjugate";
            this.btnConjugate.UseVisualStyleBackColor = true;
            this.btnConjugate.Click += new System.EventHandler(this.btnConjugate_Click);
            // 
            // btnRotate
            // 
            this.btnRotate.Location = new System.Drawing.Point(218, 413);
            this.btnRotate.Name = "btnRotate";
            this.btnRotate.Size = new System.Drawing.Size(75, 23);
            this.btnRotate.TabIndex = 27;
            this.btnRotate.Text = "Rotate";
            this.btnRotate.UseVisualStyleBackColor = true;
            this.btnRotate.Click += new System.EventHandler(this.btnRotate_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(90, 26);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(15, 13);
            this.label6.TabIndex = 28;
            this.label6.Text = "w";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(90, 64);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(15, 13);
            this.label7.TabIndex = 29;
            this.label7.Text = "w";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(149, 107);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(12, 13);
            this.label8.TabIndex = 30;
            this.label8.Text = "x";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(202, 107);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(12, 13);
            this.label9.TabIndex = 31;
            this.label9.Text = "y";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(202, 68);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(12, 13);
            this.label10.TabIndex = 32;
            this.label10.Text = "y";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(202, 26);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(12, 13);
            this.label11.TabIndex = 33;
            this.label11.Text = "y";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(149, 26);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(12, 13);
            this.label12.TabIndex = 34;
            this.label12.Text = "x";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(149, 61);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(12, 13);
            this.label13.TabIndex = 35;
            this.label13.Text = "x";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(253, 26);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(12, 13);
            this.label14.TabIndex = 36;
            this.label14.Text = "z";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(253, 64);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(12, 13);
            this.label15.TabIndex = 37;
            this.label15.Text = "z";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(253, 107);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(12, 13);
            this.label16.TabIndex = 38;
            this.label16.Text = "z";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(317, 448);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.btnRotate);
            this.Controls.Add(this.btnConjugate);
            this.Controls.Add(this.btnSwap);
            this.Controls.Add(this.btnModulas);
            this.Controls.Add(this.btnSubtract);
            this.Controls.Add(this.btnNeg);
            this.Controls.Add(this.btnScaler);
            this.Controls.Add(this.btnMultiply);
            this.Controls.Add(this.btnAdd);
            this.Controls.Add(this.tbAnswer);
            this.Controls.Add(this.tbAngle);
            this.Controls.Add(this.tbVecZ);
            this.Controls.Add(this.tbVecY);
            this.Controls.Add(this.tbQ2z);
            this.Controls.Add(this.tbQ2y);
            this.Controls.Add(this.tbQ2x);
            this.Controls.Add(this.tbVecX);
            this.Controls.Add(this.tbScale);
            this.Controls.Add(this.tbQ2w);
            this.Controls.Add(this.tbQ1z);
            this.Controls.Add(this.tbQ1y);
            this.Controls.Add(this.tbQ1x);
            this.Controls.Add(this.tbQ1w);
            this.Controls.Add(this.lblAngle);
            this.Controls.Add(this.lblScale);
            this.Controls.Add(this.lblVecV);
            this.Controls.Add(this.lblQ2);
            this.Controls.Add(this.lblQ1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblQ1;
        private System.Windows.Forms.Label lblQ2;
        private System.Windows.Forms.Label lblVecV;
        private System.Windows.Forms.Label lblScale;
        private System.Windows.Forms.Label lblAngle;
        private System.Windows.Forms.TextBox tbQ1w;
        private System.Windows.Forms.TextBox tbQ1x;
        private System.Windows.Forms.TextBox tbQ1y;
        private System.Windows.Forms.TextBox tbQ1z;
        private System.Windows.Forms.TextBox tbQ2w;
        private System.Windows.Forms.TextBox tbScale;
        private System.Windows.Forms.TextBox tbVecX;
        private System.Windows.Forms.TextBox tbQ2x;
        private System.Windows.Forms.TextBox tbQ2y;
        private System.Windows.Forms.TextBox tbQ2z;
        private System.Windows.Forms.TextBox tbVecY;
        private System.Windows.Forms.TextBox tbVecZ;
        private System.Windows.Forms.TextBox tbAngle;
        private System.Windows.Forms.TextBox tbAnswer;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.Button btnMultiply;
        private System.Windows.Forms.Button btnScaler;
        private System.Windows.Forms.Button btnNeg;
        private System.Windows.Forms.Button btnSubtract;
        private System.Windows.Forms.Button btnModulas;
        private System.Windows.Forms.Button btnSwap;
        private System.Windows.Forms.Button btnConjugate;
        private System.Windows.Forms.Button btnRotate;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
    }
}

