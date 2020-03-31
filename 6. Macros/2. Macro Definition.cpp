/*
C++ program output text file of
macro definition from the
given input assembly source code.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
int main()
{
    string line;
    int flag = -1;
    ifstream inpfile ("Input Program with MACROS.txt");
    ofstream outfile ("Macro Definitions.txt");
    if (inpfile.is_open())
    {
        while (getline(inpfile, line))
        {
            stringstream check(line);
            string inter;
            vector<string> instruction;
            while(getline(check, inter, '\t'))
                instruction.push_back(inter);
            if (instruction[1] == "MACRO")
                flag = 1;
            if (flag == 1)
                outfile<<line<<endl;
            if (instruction[1] == "MEND")
            {
                outfile<<endl;
                flag = -1;
            }
        }
    }
    inpfile.close();
    outfile.close();
    return 0;
}
