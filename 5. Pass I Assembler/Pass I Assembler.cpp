// Program requires C++11
#include "data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
#include <list>
using namespace std;

int main()
{
    int loc;
    string line;
    map<string, string> symtab;
    list<string> symbols;
    map<string, string> littab;
    map<string, string> optab;
    map<string, string>::iterator itr;
    ifstream inpfile ("Input Program.txt");
    vector<string> IC;
    if(inpfile.is_open())
    {
        while(getline(inpfile,line))
        {
            // Tokenizing Input
            stringstream check1(line);
            string intermediate;
            vector<string> instr;
            while(getline(check1, intermediate, '\t'))
                instr.push_back(intermediate);
            string inter = "";
            if(AD.count(instr[1]) > 0) // Statement Is Assembler Directive
            {
                if(instr[1] == "START")
                {
                    loc = stoi(instr[2]);
                    inter += to_string(loc) + ") (AD," + AD.at(instr[1]) +") (C," + instr[2] + ")";
                }
                if(instr[1] == "EQU")
                {
                    symbols.push_back(instr[0]);
                    symtab.insert(pair<string, string>(instr[0], symtab.at(instr[2])));
                }
                if(instr[1] == "ORIGIN")
                {
                    string label = instr[2].substr(0, instr[2].find('+'));
                    if (label == instr[2]) // LOOP
                        loc = stoi(symtab.at(label));
                    else // LOOP + 2
                        loc = stoi(symtab.at(label)) + stoi(instr[2].substr(instr[2].find('+')+1, instr[2].length()));
                }
                // Rest of Assembler Directives
            }
            if(IS.count(instr[1]) > 0) // Statement Is Imperative Statement
            {
                loc += 1;
                if(instr[0].length() != 0) // A Label Exists
                {
                    symbols.push_back(instr[0]);
                    symtab.insert(pair<string, string>(instr[0],to_string(loc)));
                }

                if(instr[1] == "STOP")
                    inter += to_string(loc) + ") (IS," + IS.at(instr[1]) + ")";
                else if(instr[1] == "READ" || instr[1] == "PRINT")
                {
                    //symtab.insert(pair<string, string>(instr[2],"NULL"));
                    //symbols.push_back(instr[2]);
                    inter += to_string(loc) + ") (IS," + IS.at(instr[1]) + ") (S," + to_string(symbols.size()-1) + ")"; // Determine if symbol or literal
                }
                else
                {
                    // Rest of the Imperative Statements
                }
            }
            cout<<inter<<endl;
        }
    }
    for (itr = symtab.begin(); itr != symtab.end(); ++itr)
        cout<<itr->first<<'\t'<< itr->second<<endl;
    inpfile.close();
}
