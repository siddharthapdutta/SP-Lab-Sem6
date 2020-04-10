/*
C++ Program to Implement
Pass Two of a
Direct Linking Loader
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
    string line, addr, name, esline;
    int progaddr, cslen, staddr, addr2, execaddress;
    ifstream estab("estab.txt");
    ifstream inpfile("link2in.txt");
    ofstream outfile("dupout.txt");
    cout<<"Enter starting address: ";
    cin>>progaddr;

    outfile<<"Starting Address: ";
    outfile<<progaddr<<endl<<endl;
    while(inpfile >> line)
    {
        stringstream check(line);
        string inter;
        vector<string> records;
        while(getline(check, inter, '^'))
            records.push_back(inter);

        if(records[0] == "H")
        {
            addr = records[2];
            cslen = stoi(records[3]);
        }
        else if (records[0] != "E")
        {
            if (records[0] == "T")
            {
                staddr = stoi(records[1]) + progaddr;
                for (int i = 3; i < records.size(); i++) // 3rd token onwards is the data
                {
                    for (int j = 0; j < records[i].length()-1; j+=2) // Takes care of $ in last token
                    {
                        outfile<<staddr<<"\t"<<records[i].substr(j, 2)<<endl;
                        staddr += 1;
                    }
                }
            }
            else if (records[0] == "M")
            {
                name = records[3].substr(1, records[3].length()-2); // Extract name from +[NAME]$
                while(getline(estab, esline))
                {
                    stringstream check(esline);
                    string inter;
                    vector<string> es_contents;
                    while(getline(check, inter, '\t'))
                        es_contents.push_back(inter);

                    if (es_contents[1] == name)
                    {
                        addr2 = stoi(records[1]) + progaddr + stoi(es_contents[2]);
                        outfile<<"\n"<<name<<"\t"<<addr2<<endl;
                        break;
                    }
                }
            }
        }
        else
        {
            execaddress = progaddr + cslen;
            outfile<<"\nThe exec address is: "<<execaddress<<endl;
        }
    }
    estab.close();
    inpfile.close();
    outfile.close();
    return 0;
}
