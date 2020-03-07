#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#include <map>
#include <string>
#include <list>
#include <sstream>
#include <iostream>
#include <algorithm> // For count function

bool is_literal(std::string s)
{
    if (std::count(s.begin(), s.end(), '\'') == 2)
        return true;
    else
        return false;
}

int index_symbol(std::list<std::string> symbols, std::string label)
{
    int index = 0;
    for (const auto& i : symbols)
    {
        if (label == i)
            break;
        index += 1;
    }
    return index;
}

int index_literal(std::list<std::string> literals, std::string literal, int starting_index)
{
    int index = 0;
    for (const auto& i : literals)
    {
        if (literal == i && index >= starting_index)
            return index;
        index += 1;
    }
    return -1;
}

const std::map<std::string, std::string> IS = {
    {"STOP","00"},
    {"ADD","01"},
    {"SUB","02"},
    {"MULT","03"},
    {"MOVER","04"},
    {"MOVEM","05"},
    {"COMP","06"},
    {"BC","07"},
    {"DIV","08"},
    {"READ","09"},
    {"PRINT","10"}
};

const std::map<std::string, std::string> BC = {
    {"LT","1"},
    {"LE","2"},
    {"EQ","3"},
    {"GT","4"},
    {"GE","5"},
    {"ANY","6"}
};

const std::map<std::string, std::string> REG = {
    {"AREG,","1"},
    {"BREG,","2"},
    {"CREG,","3"},
    {"DREG,","4"}
};

#endif // DATA_H_INCLUDED
