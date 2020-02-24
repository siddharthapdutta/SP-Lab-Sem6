#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#include <map>
#include <string>
#include <algorithm> // For count function

bool is_literal(std::string s)
{
    if (std::count(s.begin(), s.end(), '\'') == 2)
        return true;
    else
        return false;
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
    {"LT","01"},
    {"LE","02"},
    {"EQ","03"},
    {"GT","04"},
    {"GE","05"},
    {"ANY","06"}
};

const std::map<std::string, std::string> DL = {
    {"DC","00"},
    {"DS","01"}
};

const std::map<std::string, std::string> AD = {
    {"START","00"},
    {"END","01"},
    {"EQU","03"},
    {"LTORG","04"},
    {"ORIGIN","05"}
};

const std::map<std::string, std::string> REG = {
    {"AREG","0"},
    {"BREG","1"},
    {"CREG","3"},
    {"DREG","4"}
};

#endif // DATA_H_INCLUDED
