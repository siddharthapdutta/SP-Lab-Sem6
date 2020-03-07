// Program requires C++11
// Algorithm 4.1 (Assembler First Pass)
#include "data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <iterator>
#include <list>
using namespace std;

int main()
{
    // Data Structures Required
    int loc_entr = 0;
    string line;
    list<string> symbols; // For indexing
    map<string, string> SYMTAB;


    // LITTAB does not contain literals, but index of literals,
    // List literals contain the literals and corresponding index.
    list<string> literals;
    list<string>::iterator lit_itr;
    map<string, string> LITTAB;

    // Maintaining POOLTAB
    int pooltab_ptr = 0;
    map<string, string> POOLTAB;
    POOLTAB.insert(pair<string, string>(to_string(pooltab_ptr), to_string(0)));
    map<string, string>::iterator pooltab_itr;


    // Opening Files
    ifstream inpfile ("Input Program.txt");
    ofstream outfile ("Intermediate Code.txt");

    if (inpfile.is_open())
    {
        while(getline(inpfile, line))
        {
            // Separating Input Line (\t Tokenizer)
            stringstream check1(line);
            string inter;
            vector<string> instruction;
            while(getline(check1, inter, '\t'))
                instruction.push_back(inter);
            string intermediate = "";
            string this_label = "";

            if (instruction[0].length() != 0) // Label Field is Non-Empty
            {
                this_label = instruction[0];
                if(SYMTAB.count(this_label) > 0) // If Label is Already in SYMTAB, Add Location
                    SYMTAB.find(this_label)-> second = to_string(loc_entr);
                else
                {
                    symbols.push_back(this_label);
                    SYMTAB.insert(pair<string, string>(this_label, to_string(loc_entr)));
                }
            }

            //---------------Assembly Directives---------------//
            if (instruction[1] == "START")
            {
                loc_entr = stoi(instruction[2]);
                intermediate = "(AD,00) (C," + instruction[2] +")";
            }
            if (instruction[1] == "ORIGIN")
            {
                string label = instruction[2].substr(0, instruction[2].find('+'));
                intermediate = "(AD,02) (S,";
                int index = index_symbol(symbols, label);
                intermediate += to_string(index)+")";
                if (label == instruction[2]) // No Shifting Required
                    loc_entr = stoi(SYMTAB.at(label));
                else // Shifting of Words due to Presence of Addition Operator
                {
                    loc_entr = stoi(SYMTAB.at(label)) + stoi(instruction[2].substr(instruction[2].find('+')+1, instruction[2].length()));
                    intermediate += "+" + (instruction[2].substr(instruction[2].find('+')+1, instruction[2].length()));
                }
            }
            if (instruction[1] == "EQU")
            {
                SYMTAB.find(this_label)->second = SYMTAB.at(instruction[2]);
                intermediate = "(AD,03) (S," + to_string(index_symbol(symbols, instruction[2])) + ")";
            }
            if (instruction[1] == "END")
            {
                intermediate = "(AD,01)";
                int index = 0;
                for (const auto& i : literals)
                {
                    if(LITTAB.find(to_string(index))->second == "-")
                    {

                        LITTAB.find(to_string(index))->second = to_string(loc_entr);
                        loc_entr += 1;
                    }
                    index += 1;
                }
                pooltab_ptr += 1;
            }
            if (instruction[1] == "LTORG")
            {
                intermediate = "(AD,04)";
                int index = 0;
                for (const auto& i : literals)
                {
                    if(LITTAB.find(to_string(index))->second == "-")
                    {

                        LITTAB.find(to_string(index))->second = to_string(loc_entr);
                        loc_entr += 1;
                    }
                    else
                        break;
                    index += 1;
                }
                pooltab_ptr += 1;
                POOLTAB.insert(pair<string, string>(to_string(pooltab_ptr), to_string(index)));
            }
            if (instruction[0] == "" and instruction[1] == "") // Generating IC for Literals Allocation
            {
                string literal = instruction[2].substr(instruction[2].find('=')+1);
                int starting_index = stoi(POOLTAB.at(to_string(pooltab_ptr-1)));
                intermediate = "(L,";
                intermediate += to_string(index_literal(literals, literal, starting_index)) + ")";
            }

            //---------------Declarative Statements---------------//
            if (instruction[1] == "DC")
            {
                loc_entr += 1;
                intermediate = "(DL,00) ";
                literals.push_back(instruction[2].substr(instruction[2].find('=')+1));
                LITTAB.insert(pair<string,string>(to_string(literals.size()-1),"-"));
                intermediate += "(L," + to_string(literals.size()-1) + ")";
            }
            if (instruction[1] == "DS")
            {
                loc_entr += stoi(instruction[2]);
                intermediate = "(DL,01) (C,";
                intermediate += instruction[2] + ")";
            }

            //---------------Imperative Statements---------------//
            if (IS.count(instruction[1]) > 0)
            {
                intermediate = "(IS," + IS.at(instruction[1]) + ") ";
                if (instruction[2].length() != 0) // Operand1 Field Exists
                {
                    if (instruction[1] == "BC")
                    {
                        intermediate += "(" + BC.at(instruction[2]) + ") ";
                        if(SYMTAB.count(instruction[3]) == 0) // Symbol not in SYMTAB yet
                        {
                            symbols.push_back(instruction[3]);
                            SYMTAB.insert(pair<string, string>(instruction[3], "-"));
                        }
                        intermediate += "(S," + to_string(index_symbol(symbols,instruction[3])) + ")";
                    }
                    else if (instruction[1] == "READ" || instruction [1] == "PRINT") // READ or PRINT statements
                    {
                        if(SYMTAB.count(instruction[2]) == 0) // Symbol not in SYMTAB yet
                        {
                            symbols.push_back(instruction[2]);
                            SYMTAB.insert(pair<string, string>(instruction[2], "-"));
                        }
                        intermediate += "(S," + to_string(index_symbol(symbols,instruction[2])) + ")";
                    }
                    else if (instruction[1] != "STOP") // All other IS except STOP
                    {
                        intermediate += "(" + REG.at(instruction[2]) + ") ";
                        if (is_literal(instruction[3]))
                        {
                            literals.push_back(instruction[3].substr(instruction[3].find('=')+1));
                            LITTAB.insert(pair<string,string>(to_string(literals.size()-1),"-"));
                            intermediate += "(L," + to_string(literals.size()-1) + ")";
                        }
                        else
                        {
                            if(SYMTAB.count(instruction[3]) == 0) // Symbol not in SYMTAB yet
                            {
                                symbols.push_back(instruction[3]);
                                SYMTAB.insert(pair<string, string>(instruction[3], "-"));
                            }
                            intermediate += "(S," + to_string(index_symbol(symbols,instruction[3])) + ")";
                        }
                    }
                }
                loc_entr += 1; // All IS = 1 Memory Word
            }
            cout<<intermediate<<endl;
            outfile<<intermediate<<endl;
        }
    }
    outfile.close();

    int index = 0;

    // Symbol Table
    ofstream sym_file ("Symbol Table.txt");
    sym_file<<"Symbol Table"<<endl;
    sym_file<<"\nIndex\tSymbol\tAddress"<<endl;
    for (const auto& i : symbols)
    {
        string temp = to_string(index) + "\t" + i + "\t" + SYMTAB.find(i)->second;
        sym_file<<temp<<endl;
        index += 1;
    }
    sym_file.close();

    // Literal Table
    index = 0;
    ofstream lit_file ("Literal Table.txt");
    lit_file<<"Literal Table"<<endl;
    lit_file<<"\nIndex\tLiteral\tAddress"<<endl;
    for (const auto& i : literals)
    {
        string temp = to_string(index) + "\t" + i + "\t" + LITTAB.find(to_string(index))->second;
        lit_file<<temp<<endl;
        index += 1;
    }
    lit_file.close();

    // Displaying Pooltab Table
    ofstream pool_file ("Pooltab Table.txt");
    pool_file<<"Pooltab Table"<<endl;
    pool_file<<"\nIndex\tLITTAB#"<<endl;
    for (pooltab_itr = POOLTAB.begin(); pooltab_itr != POOLTAB.end(); ++pooltab_itr)
    {
        string temp = pooltab_itr->first + "\t" + pooltab_itr->second;
        pool_file<<temp<<endl;
    }
    pool_file.close();
}
