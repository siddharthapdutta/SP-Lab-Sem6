/*
C++ Program to
implement pass one
of a direct linking loader
*/
#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    array<string,2> files{"linkin.txt","linkin1.txt"};
    int csaddr;
    string line;
    ofstream outfile("output.txt");
    cout<<"Enter starting address: ";
    cin>>csaddr;
    outfile<<"Starting Address: ";
    outfile<<csaddr<<endl<<endl;
    for (int i = 0; i < files.size(); i++)
    {
        ifstream inpfile(files[i]);
        if(inpfile.is_open())
        {
            int cslth = 0;
            while(getline(inpfile,line))
            {
                // Splitting Line With ^ Delimiter
                stringstream check(line);
                string inter;
                vector<string> records;
                while(getline(check, inter, '^'))
                    records.push_back(inter);

                if(records[0] == "H")
                {
                    outfile<<records[1]<<"\t"<<csaddr<<"\t"<<records[3]<<endl;
                    cslth = stoi(records[3]);
                }

                if(records[0] == "D")
                {
                    for (int i = 1; i < records.size(); i+=2)
                        outfile<<records[i]<<"\t"<<csaddr+stoi(records[i+1])<<endl;
                }
                if(records[0] == "E")
                    break;
            }
            csaddr += cslth;
        }
        inpfile.close();
    }
    outfile.close();
    return 0;
}
