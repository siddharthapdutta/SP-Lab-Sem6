/*
C++ Program to Differentiate Between Literals and Symbols
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string line;
    vector<string> symbols;
    vector<string> literals;
    ifstream inpfile ("Input Program.txt");
    if(inpfile.is_open())
    {
        while(getline(inpfile,line))
        {
            string token = line.substr(0, line.find("\t")); // Checks the symbol column
            int delim = line.find(")"); // Creating a ')' delimiter
            if (delim >= 0)
            {
                if (token.length() != 0)
                    symbols.push_back(token);
                string op = line.substr(delim, 8);
                if(op == ") + 00 0")
                {
                    string lit = line.substr(delim+9, 3);
                    if (lit != "000")
                        literals.push_back(lit);
                }
            }
        }
    }
    cout<<"Symbols"<<endl;
    for (int i = 0; i < symbols.size(); i++)
        cout<<symbols[i]<<endl;

    cout<<"\nLiterals"<<endl;
    for (int i = 0; i < literals.size(); i++)
        cout<<literals[i]<<endl;
}
