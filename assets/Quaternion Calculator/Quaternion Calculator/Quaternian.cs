using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Quaternion_Calculator
{
    class Quaternian
    {
        private float w;
        public float W
        {
            get { return w; }
            set { w = value; }
        }
        private float i;
        public float I
        {
            get { return i; }
            set { i = value; }
        }
        private float j;
        public float J
        {
            get { return j; }
            set { j = value; }
        }
        private float k;
        public float K
        {
            get { return k; }
            set { k = value; }
        }
        /// <summary>
        /// constructer 1 
        /// setting each point in the quaternian 
        /// to  0 value;
        /// </summary>
        public Quaternian()
        {
            w = 0.0f;
            i = 0.0f;
            j = 0.0f;
            k = 0.0f;
        }
        /// <summary>
        /// consta=ructer 2 
        /// allowing the quaternians to 
        /// take float values
        /// </summary>
        /// <param name="_A0"></param>
        /// <param name="_A1"></param>
        /// <param name="_A2"></param>
        /// <param name="_A3"></param>
        public Quaternian(float _A0, float _A1, float _A2, float _A3)
        {
            w = _A0;
            i = _A1;
            j = _A2;
            k = _A3;
        }
        /// <summary>
        /// a string is made to diplay the answer 
        /// in the correct form 
        /// and i, j, k are added as a string in the correct place
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return "(" + w.ToString("g3") + "," + i.ToString("g3")+"i" + "," + j.ToString("g3")+"j" + "," + k.ToString("g3")+"k" + ")";
        }

        

        /// <summary>
        /// the plus operator 
        /// each point in the quaternian is added to 
        /// its corresponding point in the other 
        /// quaternian
        /// </summary>
        /// <param name="Q1"></param>
        /// <param name="Q2"></param>
        /// <returns></returns>
        public static Quaternian operator +(Quaternian Q1, Quaternian Q2)
        {
            return new Quaternian((Q1.w + Q2.w), (Q1.i + Q2.i), (Q1.j + Q2.j), (Q1.k + Q2.k));
        }
        /// <summary>
        /// the minus operator
        /// the difference ids found between the two quaternians
        /// each point in the quaternian is subtracted from 
        /// the corresponding point
        /// </summary>
        /// <param name="Q1"></param>
        /// <param name="Q2"></param>
        /// <returns></returns>
        public static Quaternian operator -(Quaternian Q1, Quaternian Q2)
        {
            return new Quaternian((Q1.w - Q2.w), (Q1.i - Q2.i), (Q1.j - Q2.j), (Q1.k - Q2.k));
        }
        /// <summary>
        /// the scaler operator 
        /// each point in the quaterion is multiplied 
        /// by the value in the the scaler textbox
        /// the scale is represented by the float x
        /// </summary>
        /// <param name="Q1"></param>
        /// <param name="x"></param>
        /// <returns></returns>
        public static Quaternian operator *(Quaternian Q1, float x)
        {
            return new Quaternian((Q1.w * x), (Q1.i * x), (Q1.j * x), (Q1.k * x));
        }
        /// <summary>
        /// quaternion negate
        /// each quaterniion component is set to a minus value
        /// and returned to the form class
        /// </summary>
        /// <param name="Q1"></param>
        /// <returns></returns>
        public static Quaternian operator -(Quaternian Q1)
        {
            return new Quaternian(-Q1.w, -Q1.i, -Q1.j, -Q1.k);
        }
        /// <summary>
        /// multiplication operator
        /// there are two quaternions passed into the multiply operator
        /// each component is multiplied by each component in the other quaternion
        /// minus signs are to where applied according to the formula
        /// i2 = j2 = k2 = ijk = −1,
        /// </summary>
        /// <param name="Q1"></param>
        /// <param name="Q2"></param>
        /// <returns></returns>
        public static Quaternian operator *(Quaternian Q1, Quaternian Q2)
        {
            float first = Q1.w * Q2.w - Q1.i * Q2.i - Q1.j * Q2.j - Q1.k * Q2.k;
            float second = Q1.w * Q2.i + Q1.i * Q2.w + Q1.j * Q2.k - Q1.k * Q2.j;
            float third= Q1.w * Q2.j + Q1.j * Q2.w + Q1.k * Q2.i - Q1.i * Q2.k;
            float fourth = Q1.w * Q2.k + Q1.k * Q2.w + Q1.i * Q2.j - Q1.j * Q2.i;
            return new Quaternian(first, second, third, fourth);
            
        }
        /// <summary>
        /// the i, j and k values are negated 
        /// the w value remains positive
        /// </summary>
        /// <param name="Q1"></param>
        /// <returns></returns>
        public  Quaternian Conjugate(Quaternian Q1)
        {
            return new Quaternian(Q1.w, -Q1.i, -Q1.j, -Q1.k);
        }
        /// <summary>
        /// the modulas formula is used 
        /// each component is multiplied by itself and added 
        /// the square root of these components is returned
        /// </summary>
        /// <returns></returns>
        public double Modulas()
        {
            return Math.Sqrt((w * w) + (i * i) + (j * j) + (k * k));
        }
        /// <summary>
        /// the rotation of a quaternion formula is used 
        /// the cos of the angle is found and sin of the angle multiplied 
        /// by each x y and z component of the quaternion
        /// the x y and z components of the quaternion are multiplied by the x y and z
        /// components of the vector 
        /// minus is applied where it is needed as per the formula 
        /// i2 = j2 = k2 = ijk = −1
        /// </summary>
        /// <param name="Q1"></param>
        /// <param name="V1"></param>
        /// <param name="x"></param>
        /// <returns></returns>
        public  Vector3 Rotate(Quaternian Q1, Vector3 V1, double x)
        {
            
            Quaternian normQ = new Quaternian((float)Math.Cos(x), ((float)Math.Sin(x)) * V1.X, ((float)Math.Sin(x)) * V1.Y, ((float)Math.Sin(x)) * V1.Z);
            Quaternian firstQuat = new Quaternian(normQ.w + Q1.i, (normQ.i * Q1.i)*(-1), -(normQ.j * Q1.i), normQ.k * Q1.i);
            Quaternian secondQuat = new Quaternian(normQ.w + Q1.j, normQ.i * Q1.j, (normQ.j * Q1.j)*(-1), -(normQ.k * Q1.j));
            Quaternian thirdQuat = new Quaternian(normQ.w + Q1.k, -(normQ.i * Q1.k), normQ.j * Q1.k, (normQ.k * Q1.k)*(-1));
            Quaternian newQuat = new Quaternian(firstQuat.i + secondQuat.j + thirdQuat.k, firstQuat.w + secondQuat.k + thirdQuat.j,
                firstQuat.k + secondQuat.w + thirdQuat.i, firstQuat.j + secondQuat.i + thirdQuat.w);

            Quaternian quatOne = new Quaternian(newQuat.w + normQ.w, newQuat.i + (-normQ.w), newQuat.j + (-normQ.w), newQuat.k + (-normQ.w));
            Quaternian quatTwo = new Quaternian(newQuat.w + normQ.i, (newQuat.i + (-normQ.i))*(-1), -(newQuat.j + (-normQ.i)), newQuat.k + (-normQ.i));
            Quaternian quatThree = new Quaternian(newQuat.w + normQ.j, newQuat.i + (-normQ.j), (newQuat.j + (-normQ.j))*(-1), -(newQuat.k + (-normQ.j)));
            Quaternian quatFour = new Quaternian(newQuat.w + normQ.k, -(newQuat.i + (-normQ.k)), newQuat.j + (-normQ.k), (newQuat.k + (-normQ.k))*(-1));
            Quaternian finalQuat = new Quaternian(quatOne.w + quatTwo.i + quatThree.j + quatFour.k, quatOne.i + quatTwo.w + quatThree.k + quatFour.j, 
                quatOne.j + quatTwo.k + quatThree.w + quatFour.i, quatOne.k + quatTwo.j + quatThree.i + quatFour.w);

            return new Vector3(finalQuat.i, finalQuat.j, finalQuat.k);

        }

    }
}
