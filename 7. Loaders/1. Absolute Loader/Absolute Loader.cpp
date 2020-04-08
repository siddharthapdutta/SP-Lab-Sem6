/*
C++ Program to implement an Absolute Loader
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    string name, line;
    ifstream inpfile("abssrc.txt");
    ofstream outfile("output.txt");

    if (inpfile.is_open())
    {
        while(getline(inpfile, line))
        {
            // Splitting Line With ^ Delimiter
            stringstream check(line);
            string inter;
            vector<string> records;
            while(getline(check, inter, '^'))
                records.push_back(inter);

            if(records[0] == "H")
            {
                outfile<<"Name of Program: "<<records[1]<<endl;
                outfile<<"Starting Address: "<<stoi(records[2])<<endl;
                outfile<<"Program Length: "<<stoi(records[3])<<endl;
            }
            if (records[0] == "T")
            {
                outfile<<endl;
                int address = stoi(records[1]);
                for (int i = 3; i < records.size(); i++) // 3rd token onwards is the data
                {
                    for (int j = 0; j < records[i].length()-1; j+=2) // Takes care of $ in last token
                    {
                        outfile<<address<<"\t"<<records[i].substr(j, 2)<<endl;
                        address += 1;
                    }
                }
            }
            if (records[0] == "E")
            {
                outfile<<"\nEnd Record. Address jumps to: "<<stoi(records[1])<<endl;
                break;
            }
        }
    }
    inpfile.close();
    outfile.close();
    return 0;
}
