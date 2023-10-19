using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCPayload
{
     /// <summary>
     /// this class handles and changes or requests for data of the telemarty
     /// </summary>
    public class Telem
    {
        /// <summary>
        /// variable for the tempature data type is a float and it has a private set and public get
        /// </summary>
        public float Long{ get; private set; }
        /// <summary>
        /// variable for the tempature data type is a float and it has a private set and public get
        /// </summary>
        public float Lat { get; private set; }
        /// <summary>
        /// variable for the tempature data type is a float and it has a private set and public get
        /// </summary>
        public float Temp { get; private set; }

        /// <summary>
        /// default constructor for the telematry object will set all values to 0 by default
        /// </summary>
        public Telem()
        {
            Long = 0;
            Lat = 0; 
            Temp = 0;
        }
        /// <summary>
        /// this is a paramaterized constructor to set a telematry object to a specific state 
        /// </summary>
        /// <param name="x"> longatude as a float</param>
        /// <param name="y"> latatude as a float</param>
        /// <param name="c"> tempature in celcius as a float</param>
        public Telem(float x, float y, float c)
        {
            Long = x;
            Lat = y;
            Temp = c;
        }
        /// <summary>
        /// this function sets the telematry of the current telemtary object upon request to the new values
        /// </summary>
        /// <param name="x">longatude as a float</param>
        /// <param name="y">latatude as a float</param>
        /// <param name="c">tempature in celcius as a float</param>
        public void SetTelemetry(float x, float y, float c)
        {
            this.Long = x; 
            this.Lat = y; 
            this.Temp = c;
        }
    }
}
