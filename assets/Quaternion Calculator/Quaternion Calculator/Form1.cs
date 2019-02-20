using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
/* James Condon 
 * c00207200
 * 28/02/16
 * worked on 27/02 21:00 - 23:00
 * worked on 28/02 21:00 - 23:00
 * total time worked on 4 hours 
 * this app is a quaterniion calculator that displays two quaternions, a vector and an angle 
 * there are a total of 9 operations that can be carried out. each operation is a button with the symbol 
 * corresponding to the formula used and when this button is clicked an answer is converted to a string 
 * this answeris displayed in the answer text box in the form required.
 * known bugs: there are no known bugs 
 */
namespace Quaternion_Calculator
{
    /// <summary>
    /// public quaternion created 
    /// called quaternion answer
    /// </summary>
    public partial class Form1 : Form
    {
        Quaternian quaternianAnswer;

        public Form1()
        {
            InitializeComponent();
        }
        /// <summary>
        /// reads the text values from the string 
        /// providing they are are a numeric value 
        /// if not an error message will appear
        /// if numeric value it is converted and returned 
        /// </summary>
        /// <param name="textString"></param>
        /// <returns></returns>
        private float GetNumber(string textString)
        {
            float numericValue;
            if (!float.TryParse(textString, out numericValue))
            {
                MessageBox.Show("Bad Number " + textString, "Input Error", MessageBoxButtons.OK);
                numericValue = 0;
            }
            return numericValue;
        }
        /// <summary>
        /// the two quaternions are created one and two
        /// the answer box is cleared 
        /// the answer is set to one and two added 
        /// text box displays the answer in the answer text box
        /// it is then converted to a sting
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnAdd_Click(object sender, EventArgs e)
        {
            Quaternian quaternianOne;
            Quaternian quaternionTwo;

            quaternianOne = new Quaternian(GetNumber(tbQ1w.Text), GetNumber(tbQ1x.Text), GetNumber(tbQ1y.Text), GetNumber(tbQ1z.Text));
            quaternionTwo = new Quaternian(GetNumber(tbQ2w.Text), GetNumber(tbQ2x.Text), GetNumber(tbQ2y.Text), GetNumber(tbQ2z.Text));

            tbAnswer.Clear();
            quaternianAnswer = quaternianOne + quaternionTwo;
            tbAnswer.Text = "The sum of " + quaternianOne.ToString() + " and " + quaternionTwo.ToString() + " is " + quaternianAnswer.ToString();
        }
        /// <summary>
        /// the two quaternions are created one and two
        /// the answer box is cleared 
        /// the answer is set Q2 subtracted from Q1
        /// text box displays the answer in the answer text box
        /// it is then converted to a sting
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSubtract_Click(object sender, EventArgs e)
        {
            Quaternian quaternianOne;
            Quaternian quaternionTwo;

            quaternianOne= new Quaternian(GetNumber(tbQ1w.Text), GetNumber(tbQ1x.Text), GetNumber(tbQ1y.Text), GetNumber(tbQ1z.Text));
            quaternionTwo = new Quaternian(GetNumber(tbQ2w.Text), GetNumber(tbQ2x.Text), GetNumber(tbQ2y.Text), GetNumber(tbQ2z.Text));

            tbAnswer.Clear();
            quaternianAnswer = quaternianOne - quaternionTwo;
            tbAnswer.Text = "The difference between " + quaternianOne.ToString() + " and " + quaternionTwo.ToString() + " is " + quaternianAnswer.ToString();
        }
        /// <summary>
        /// Q1 is created and set 
        /// answer text box is cleared 
        /// the - operator is applied to the quaternion one 
        /// the text in the answer text box is set to display the answer 
        /// converted to a string
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnNeg_Click(object sender, EventArgs e)
        {
            Quaternian quaternianOne;

            quaternianOne = new Quaternian(GetNumber(tbQ1w.Text), GetNumber(tbQ1x.Text), GetNumber(tbQ1y.Text), GetNumber(tbQ1z.Text));

            tbAnswer.Clear();
            quaternianAnswer = -quaternianOne;
            tbAnswer.Text = "The negative of " + quaternianOne.ToString() + " is " + quaternianAnswer.ToString();
        }
        /// <summary>
        /// Q1 is created and a float x stores the the scale value 
        /// fetched fom the scale text box 
        /// answer tb is cleared 
        /// answer is set to  Q1 * the scale value
        /// the answer is converted to a string and displayed in the text box
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>

        private void btnScaler_Click(object sender, EventArgs e)
        {
            Quaternian quaternianOne;
            float x = GetNumber(tbScale.Text);

            quaternianOne = new Quaternian(GetNumber(tbQ1w.Text), GetNumber(tbQ1x.Text), GetNumber(tbQ1y.Text), GetNumber(tbQ1z.Text));

            tbAnswer.Clear();
            quaternianAnswer = quaternianOne * x;
            tbAnswer.Text = "The product of " + quaternianOne.ToString() + " and " + x + " is " + quaternianAnswer.ToString();
        }
        /// <summary>
        /// temp stiring is created to hold the text values 
        /// each text is said to equal eachother 
        /// and also the temp string allowing 
        /// for the values to swap with one another
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSwap_Click(object sender, EventArgs e)
        {
            string temp;

            temp = tbQ2w.Text;
            tbQ2w.Text = tbQ1w.Text;
            tbQ1w.Text = temp;

            temp = tbQ2x.Text;
            tbQ2x.Text = tbQ1x.Text;
            tbQ1x.Text = temp;
            
            temp = tbQ2y.Text;
            tbQ2y.Text = tbQ1y.Text;
            tbQ1y.Text = temp;
            
            temp = tbQ2z.Text;
            tbQ2z.Text = tbQ1z.Text;
            tbQ1z.Text = temp;
        }
        /// <summary>
        /// both Q1 and Q2 are created
        /// thge answer text box is cleared 
        /// answer is set to the first quaternion multiplied by the second
        /// the answer text box displaysthe answer converted to a string
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnMultiply_Click(object sender, EventArgs e)
        {
            Quaternian quaternianOne;
            Quaternian quaternionTwo;

            quaternianOne = new Quaternian(GetNumber(tbQ1w.Text), GetNumber(tbQ1x.Text), GetNumber(tbQ1y.Text), GetNumber(tbQ1z.Text));
            quaternionTwo = new Quaternian(GetNumber(tbQ2w.Text), GetNumber(tbQ2x.Text), GetNumber(tbQ2y.Text), GetNumber(tbQ2z.Text));

            tbAnswer.Clear();
            quaternianAnswer = quaternianOne * quaternionTwo;
            tbAnswer.Text = "The product of " + quaternianOne.ToString() + " and " + quaternionTwo.ToString() + " is " + quaternianAnswer.ToString();
        }
        /// <summary>
        /// Q1 is created 
        /// the answer text box is cleared 
        /// the answer text is set to display the conjugate of Q1
        /// Q1 is passed to the conjugate method in the quaternion class 
        /// and the answer is returned to the form class and displayed converted to a string 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnConjugate_Click(object sender, EventArgs e)
        {
            Quaternian quaternianOne;

            quaternianOne = new Quaternian(GetNumber(tbQ1w.Text), GetNumber(tbQ1x.Text), GetNumber(tbQ1y.Text), GetNumber(tbQ1z.Text));

            tbAnswer.Clear();
            tbAnswer.Text = "The conjugate of " + quaternianOne.ToString() + " is " + quaternianOne.Conjugate(quaternianOne).ToString();
        }
        /// <summary>
        /// Q1 is created 
        /// the answer text box is cleared 
        /// Q1 is passed to the modulas method in the quaternion class 
        /// the answer is then returned to the form class 
        /// it is displayed in the answer text box and converted to a string 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnModulas_Click(object sender, EventArgs e)
        {
            Quaternian quaternianOne;

            quaternianOne = new Quaternian(GetNumber(tbQ1w.Text), GetNumber(tbQ1x.Text), GetNumber(tbQ1y.Text), GetNumber(tbQ1z.Text));

            tbAnswer.Clear();
            tbAnswer.Text = "The modulas of " + quaternianOne.ToString() + " is " + quaternianOne.Modulas().ToString();
        }
        /// <summary>
        /// Q1 is created 
        /// the vector is creted getting the text values from the vector text boxes 
        /// the angle float is creted using the text value from the angle text box 
        /// the answer text box is cleared 
        /// Q1, V1 and the angle are passed to the rotate method in the qaternion class 
        /// the answer is then returned to form class
        /// the answer text box is set to display the answer converted to a string 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnRotate_Click(object sender, EventArgs e)
        {
            Quaternian quaternianOne;
            Vector3 vector;
            float angle;

            quaternianOne = new Quaternian(GetNumber(tbQ1w.Text), GetNumber(tbQ1x.Text), GetNumber(tbQ1y.Text), GetNumber(tbQ1z.Text));
            vector = new Vector3(GetNumber(tbVecX.Text), GetNumber(tbVecY.Text), GetNumber(tbVecZ.Text));
            angle = GetNumber(tbAngle.Text);

            tbAnswer.Clear();
            tbAnswer.Text = "The point " + vector.ToString() + " rotated about " + quaternianOne.ToString() + " by " + angle + "  is " + quaternianOne.Rotate(quaternianOne, vector, angle).ToString();
        }



        
    }
}
