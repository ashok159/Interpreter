//Name: Ashok Surujdeo
//Main C++ File

#include <iostream>
#include <fstream>
#include "Interpreter.h"
using namespace std;

int main(int argc, char** argv)
{
    Interpreter manage;
    if (argc == 2)
    {
        manage.Run(argv[1]);
    }
    else
    {
        cout << "Please enter a file name." << endl;
    }
    return 0;
}
