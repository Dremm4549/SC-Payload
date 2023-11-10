#include "Packet.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
void Packet::readIP()
{
    ifstream file("../IP.txt");
    if (file.is_open()) {
        for (int i = 0; i < 7; i++)
        {
            getline(file, IP[i]);
        }
        file.close();
    }
}