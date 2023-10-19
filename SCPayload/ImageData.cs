using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCPayload
{   
    internal class ImageData
    {
        byte[] data;//stores the image
        Telem tel;
        ImageData()
        {
            data = null!;
        }

        public void downloadImage()
        {
            //reading the image from a text file and saving it to the image buffer
        }

        public byte[] getImage()
        {
          //return image buffer
          return data;
        }

        public float getlat() 
        { 
            return tel.Lat;
        }
    }
}
