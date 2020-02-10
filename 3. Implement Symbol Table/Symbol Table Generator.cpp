#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    int line_count = 0;
    string line;
    ifstream inpfile ("Input Program.txt");
    ofstream outfile ("Symbol Table.txt");
    cout<<"Reading from Input Program.txt"<<endl;
    outfile<<"Symbol,Address\n"<<endl;
    if(inpfile.is_open())
    {
        while(getline(inpfile,line))
        {
            string token = line.substr(0, line.find("\t")); // Checks the symbol column
            line_count += 1;
            if(token.length() != 0)
            {
                string address = "";
                int delim = line.find(")");
                if (delim < 0) // Symbol does not have an address
                    continue;
                address = line.substr(delim-3, 3);
                outfile<<token<<","<<address<<endl;
            }
        }
        inpfile.close();
        cout<<"Symbol Table Generated: Symbol Table.txt"<<endl;
    }
    else
        cout<<"Unable to read input program"<<endl;
    outfile.close();
    return 0;
}
