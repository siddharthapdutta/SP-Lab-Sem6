/*
C++ program to
implement one pass macro.

NOTE:
    Not checked for nested MACRO definitions
    Assumes input program has tab width 8.
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <map>
#include <iterator>
#include <list>

using namespace std;

int main()
{
    string line;
    ifstream inpfile("Input Program with MACROS.txt");
    ofstream outfile("Macro Expanded Source Program.txt");

    // Data Structures
    map<string, array<int,2>> NAMTAB;
    vector<string> DEFTAB;
    int DEFTAB_pointer = 0, counter; // Counts number of instruction inside MACRO definition
    list<string> ARGTAB;

    string macro_name = "";
    bool define = false;
    bool expand = false;

    // Macroprocessor
    if (inpfile.is_open())
    {
        while(getline(inpfile, line))
        {
            // Separating Input Line (\t Tokenizer)
            stringstream check(line);
            string inter;
            vector<string> instruction;
            while(getline(check, inter, '\t'))
                instruction.push_back(inter);

            // PROCESSLINE Procedure
            if (NAMTAB.count(instruction[1]))
            {
                macro_name = instruction[1];
                expand = true;
                string parameters = instruction[2];
                stringstream check1(parameters);
                string inter;
                while(getline(check1, inter, ','))
                    ARGTAB.push_back(inter);
            }
            else if (instruction[1] == "MACRO")
            {
                macro_name = instruction[0];
                DEFTAB_pointer = DEFTAB.size();
                counter = -1;
                define = true;
            }
            else
            {
                if (!define)
                    outfile<<line<<endl;
            }

            // DEFINE Procedure
            if (define)
            {
                DEFTAB.push_back(line);
                counter += 1;
                if (instruction[1] == "MEND")
                {
                    define = false;
                    NAMTAB.insert(pair<string, array<int,2>>(macro_name,{DEFTAB_pointer, DEFTAB_pointer+counter}));
                }
            }

            // EXPAND Procedure
            if (expand)
            {
                map<string, string> argument_list;
                int def_line = NAMTAB.find(macro_name)->second[0]; // MACRO Definition Line
                int def_end = NAMTAB.find(macro_name)->second[1];
                string params = DEFTAB[def_line].substr(DEFTAB[def_line].find('&'));
                stringstream check2(params);
                int index = 0;
                while(getline(check2, inter, ','))
                {
                    argument_list.insert(pair<string,string>(inter,ARGTAB.front()));
                    ARGTAB.pop_front();
                }
                for (int i = def_line + 1; i < def_end; i++)
                {
                    string instr = DEFTAB[i];
                    for (auto itr = argument_list.begin(); itr != argument_list.end(); ++itr)
                    {
                        int pos = instr.find(itr->first);
                        if (pos != -1)
                            instr.replace(pos, (itr->first).size(), itr->second);
                    }
                    outfile<<instr<<endl;
                }
                //for (auto itr = argument_list.begin(); itr != argument_list.end(); ++itr)
                expand = false;
                ARGTAB.clear();
            }
        }
    }

    cout<<"NAMTAB\nMacro\tStart\tEnd"<<endl;
    map<string,array<int,2>>::iterator itr;
    for (itr = NAMTAB.begin(); itr != NAMTAB.end(); ++itr)
    {
        cout<<itr->first<<"\t";
        for(auto const& value: itr->second)
            cout<<value<<"\t";
        cout<<endl;
    }

    cout<<"\nDEFTAB"<<endl;
    for(int i = 0; i < DEFTAB.size(); i++)
        cout<<i<<"\t"<<DEFTAB[i]<<endl;

    return 0;
}
