using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCPayload
{
    /// <summary>
    /// this class is responsable for handling all functions related to the image data
    /// </summary>
    public class ImageData
    {
        /// <summary>
        /// a byte[] member variable that holdds the current images data the data can be up to 2gb 
        /// </summary>
        byte[] data;
        /// <summary>
        /// the telemetry object to hold all telemetry data
        /// </summary>
        Telem tel;
        public ImageData()
        {
            data = null!;
        }
        /// <summary>
        /// reading the image from a text file and saving it to the image buffer
        /// </summary>
        public void downloadImage()
        {
            
        }
        /// <summary>
        /// return image buffer the buffer will be a byte[] that holds the binary data max size 2GB storage
        /// </summary>
        public byte[] getImage()
        {
          
          return data;
        }

      
    }
}
