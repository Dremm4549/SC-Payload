using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCPayload
{
     
    public class Telem
    {        
        public float Long{ get; private set; }
        public float Lat { get; private set; }
        public float Temp { get; private set; }

        public Telem()
        {
            Long = 0;
            Lat = 0; 
            Temp = 0;
        }

        public Telem(float x, float y, float c)
        {
            Long = x;
            Lat = y;
            Temp = c;
        }

        public void SetTelemetry(float x, float y, float c)
        {
            this.Long = x; 
            this.Lat = y; 
            this.Temp = c;
        }
    }
}
