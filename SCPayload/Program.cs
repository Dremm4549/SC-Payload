//space craft payload module project 5 class conestoga college 
// by: Nick, Micheal, brian, and ethan

using SCPayload;
using System;
public class Program
{
    static public void Main()
    {
        Telem telm = new Telem();

        Console.WriteLine(telm.Temp.ToString());
        telm.SetTelemetry(3,4,5);
        Console.WriteLine("hello");
        Console.ReadKey();
    }
}