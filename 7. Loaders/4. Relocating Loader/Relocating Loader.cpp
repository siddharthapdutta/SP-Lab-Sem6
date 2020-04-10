/*
C++ Program
to Implement
Relocating Loader
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

string convert(string mask)
{
    string temp = "";
    for (int i = 0; i < mask.length(); i++)
    {
        switch(mask[i])
        {
        case '0':
            temp += "0";
            break;
        case '1':
            temp += "1";
            break;
        case '2':
            temp += "01";
            break;
        case '3':
            temp += "11";
            break;
        case '4':
            temp += "100";
            break;
        case '5':
            temp += "101";
            break;
        case '6':
            temp += "110";
            break;
        case '7':
            temp += "111";
            break;
        case '8':
            temp += "1000";
            break;
        case '9':
            temp += "1001";
            break;
        case 'A':
            temp += "1010";
            break;
        case 'B':
            temp += "1011";
            break;
        case 'C':
            temp += "1100";
            break;
        case 'D':
            temp += "1101";
            break;
        case 'E':
            temp += "1110";
            break;
        case 'F':
            temp += "1111";
            break;
        }
    }
    return temp;
}

string dec_to_hex(int num)
{
    stringstream s;
    s << hex << num;
    string res = s.str();
    return res;
}

int hex_to_dec(string val)
{
    int num;
    stringstream s;
    s << val;
    s >> hex >> num;
    return num;
}

int main()
{
    string line, bitmask, add, program_name;
    int start, address, len, bit;
    ifstream inpfile("rlin.txt");
    ofstream outfile("rlout.txt");
    cout<<"Enter starting address: ";
    cin>>start;

    outfile<<"Starting Address: ";
    outfile<<start<<endl<<endl;
    outfile<<"Memory\tOp\tLocation"<<endl;
    while(getline(inpfile, line))
    {
        stringstream check(line);
        string temp;
        vector<string> records;
        while(getline(check, temp, ' '))
            records.push_back(temp);

        if (records[0] == "H")
        {
            program_name = records[1];
        }
        if (records[0] == "T")
        {
            address = stoi(records[1]);
            address += start;
            string add = to_string(address);
            bitmask = convert(records[3]);
            int bit = 0;
            for (int i = 4; i < records.size(); i+= 2)
            {
                outfile<<add<<"\t";
                outfile<<records[i]<<"\t";
                if (bitmask[bit] == '1')
                {
                    string addr = records[i+1];
                    addr = dec_to_hex(hex_to_dec(addr) + hex_to_dec(to_string(start)));
                    outfile<<addr<<endl;
                }
                else
                    outfile<<records[i+1]<<endl;
                bit += 1;
                add = dec_to_hex(hex_to_dec(add) + 3);
            }
        }
        if (records[0] == "E")
            break;
    }
    return 0;
}
