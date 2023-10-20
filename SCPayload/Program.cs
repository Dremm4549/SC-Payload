//space craft payload module project 5 class conestoga college 
// by: Nick, Micheal, brian, and ethan

using SCPayload;
using System;
public class Program
{
    /// <summary>
    /// Acts as a simple test harness to test components within payload object.
    /// </summary>
    static public void Main()
    {
        Telem telm = new Telem();

        ImageData imageData = new ImageData();

        Payload obj = new Payload();

        
        telm.SetTelemetry(3,4,5);

        Console.ReadKey();
    }
}