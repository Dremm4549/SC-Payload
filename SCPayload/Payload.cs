using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SCPayload
{
    /// <summary>
    /// payload class will handle all requests sent by the packet class and send the data that is requested back to the packet class to be sent to other modules
    /// </summary>
    public class Payload
    {
        /// <summary>
        /// bool variable both with public getters and setters for the power state of the payload 
        /// </summary>
       public bool PowerState { set; get; }
       private ImageData imgData;
    }
}
