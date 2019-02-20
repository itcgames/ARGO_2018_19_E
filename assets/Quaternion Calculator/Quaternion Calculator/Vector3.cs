using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Quaternion_Calculator
{
    class Vector3
    {
    
        private float x;
        private float y;
        private float z;
        public float Z
        {
            get { return z; }
            set { z = value; }
        }

        public float Y
        {
            get { return y; }
            set { y = value; }
        }

        public float X
        {
            get { return x; }
            set { x = value; }
        }
        /// <summary>
        /// default constructor, makes null vector
        /// </summary>
        public Vector3()
        {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }
        /// <summary>
        /// Constructor  taking values for x, y and z
        /// </summary
        /// <param name="x1"></param>
        /// <param name="y1"></param>
        /// <param name="z1"></param>
        public Vector3(float x1, float y1, float z1)
        {
            x = x1;
            y = y1;
            z = z1;
        }

        public Vector3(string textX, string textY, string textZ)
        {
            if (!float.TryParse(textX, out x))
            {
                System.Windows.Forms.MessageBox.Show("Bad Number X", "Input Error", System.Windows.Forms.MessageBoxButtons.OK);
                x = 0;
                y = 0;
                z = 0;
                return;
            }
            if (!float.TryParse(textY, out y))
            {
                System.Windows.Forms.MessageBox.Show("Bad Number Y", "Input Error", System.Windows.Forms.MessageBoxButtons.OK);
                x = 0;
                y = 0;
                z = 0;
                return;
            }
            if (!float.TryParse(textZ, out z))
            {
                System.Windows.Forms.MessageBox.Show("Bad Number Z", "Input Error", System.Windows.Forms.MessageBoxButtons.OK);
                x = 0;
                y = 0;
                z = 0;
                return;
            }

        }
        /// <summary>
        /// constructor taking a vector as the source
        /// </summary>
        /// <param name="v"></param>
        public Vector3(Vector3 v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
        }
        /// <summary>
        /// override for ToString method outputting brackets, comas and formatting the
        /// values as general 3 digits
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return "(" + x.ToString("g3") + "," + y.ToString("g3") + "," + z.ToString("g3") + ")";
        }
        //calculates the length of each individual vector 
        //multiplies each vector component by itself and gets the sqyuare root returning the answer
        public double Length()
        {
            return Math.Sqrt(x * x + y * y + z * z);

        }
        /// <summary>
        /// deteermines whether the two vector equal one another using a boolean
        /// </summary>
        /// <param name="v2"></param>
        /// <returns></returns>
        public bool Equals(Vector3 v2)
        {
            if (x == v2.x && y == v2.y && z == v2.z)
                return true;
            else return false;
        }

        public override bool Equals(System.Object obj)
        {
            // If parameter is null return false.
            if (obj == null)
            {
                return false;
            }

            // If parameter cannot be cast to Vector3 return false.
            Vector3 v2 = obj as Vector3;
            if ((System.Object)v2 == null)
            {
                return false;
            }

            // Return true if the fields match:
            return (x == v2.x && y == v2.y && z == v2.z);
        }

        public override int GetHashCode()
        {
            return (int)(x * y * z);
        }

        public static bool operator ==(Vector3 v1, Vector3 v2)
        {
            // If both are null, or both are same instance, return true.
            if (System.Object.ReferenceEquals(v1, v2))
            {
                return true;
            }

            // If one is null, but not both, return false.
            if (((object)v1 == null) || ((object)v2 == null))
            {
                return false;
            }
            return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
        }

        public static bool operator !=(Vector3 v1, Vector3 v2)
        {
            return !(v1 == v2);
        }
        //method to calculate the dot product and return the answer to the method call
        public double DotProduct(Vector3 v2)
        {
            return x * v2.x + y * v2.y + z * v2.z;
        }
        //method to calculate the cross product and return the answer to the method call
        public Vector3 CrossProduct(Vector3 v2)
        {
            return new Vector3((y * v2.z) - (v2.y * z), -((x * v2.z) - (v2.x * z)), (x * v2.y) - (v2.x * y));
        }
        //method to calculate the angle between and return the answer to the method call
        public double AngleBetween(Vector3 v1)
        {
            double length1 = Math.Sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
            double length2 = Math.Sqrt(x * x + y * y + z * z);
            double dotProduct = (v1.x * x + v1.y * y + v1.z * z);
            double dotDivLen = dotProduct / (length1 * length2);
            double answer = Math.Acos(dotDivLen) * 180 / Math.PI;
            return answer;

        }
        //method to calculate the unit vector and pass it back to the identity form class method
        public Vector3 Unit()
        {
            double length = Math.Sqrt(x * x + y * y + z * z);
            return new Vector3((float)x / (float)length, (float)y / (float)length, z / (float)length);
        }
        /// <summary>(float)
        /// Also called projection
        /// calculates the paralell components and passes them back to the paralell method 
        /// </summary>
        /// <param name="v2"></param>
        /// <returns></returns>
        public Vector3 ParralelComponent(Vector3 v2)
        {
            double length = Math.Sqrt(x * x + y * y + z * z);
            double dotProduct = x * v2.x + y * v2.y + z * v2.z;
            double dot = (float)dotProduct / (length * length);
            return new Vector3((float)dot * (float)x, (float)dot * (float)y, (float)dot * (float)z);
        }
        /// <summary>
        /// Alos called normal but the result will not normally be a unit vector
        /// calculates the perpendicular components and passes it back to the method 
        /// </summary>
        /// <param name="v2"></param>
        /// <returns></returns>
        public Vector3 PerpendicularComponent(Vector3 v2)
        {
            double length = Math.Sqrt(x * x + y * y + z * z);
            double dotProduct = x * v2.x + y * v2.y + z * v2.z;
            double dotDivLength = (float)dotProduct / (length * length);
            double perp1 = (float)dotDivLength * x;
            double perp2 = (float)dotDivLength * y;
            double perp3 = (float)dotDivLength * z;

            return new Vector3((float)v2.x - (float)perp1, (float)v2.y - (float)perp2, (float)v2.z - (float)perp3);
        }
        /// <summary>
        /// converts the scale from a double into a float by casting it a float
        /// </summary>
        /// <param name="scale"></param>
        /// <returns></returns>
        public Vector3 Scale(double scale)
        {
            return Scale((float)scale);
        }
        /// <summary>
        /// multiplies each x, y and z by the scale to find what the answer scaled 
        /// </summary>
        /// <param name="scale"></param>
        /// <returns></returns>
        public Vector3 Scale(float scale)
        {
            return new Vector3(scale * x, scale * y, scale * z);
        }
        /// <summary>
        /// makes + add the corresponding vector of the same symbol when used in the form
        /// returns the new vector when added
        /// </summary>
        /// <param name="v1"></param>
        /// <param name="v2"></param>
        /// <returns></returns>
        public static Vector3 operator +(Vector3 v1, Vector3 v2)
        {
            return new Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
        }
        /// <summary>
        /// Subtract second vector from first
        /// return new vector passing difference between components
        /// as values for constructor
        /// </summary>
        /// <param name="v1">first operand</param>
        /// <param name="v2">second operand</param>
        /// <returns></returns>
        public static Vector3 operator -(Vector3 v1, Vector3 v2)
        {
            return new Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
        }
        /// <summary>
        /// An overloaded operator - to return the negation of a single vector
        /// return a new vector negating each of the components
        /// </summary>
        /// <param name="v1">vector</param>
        /// <returns></returns>
        public static Vector3 operator -(Vector3 v1)
        {
            return new Vector3(-v1.x, -v1.y, -v1.z);
        }
    }
}
    