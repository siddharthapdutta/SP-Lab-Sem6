/*  C++ Program to Determine Size of Instruction
    All instructions are part of the 8085 Microprocessor
    Only major instructions are included in this program (53/246)
*/
#include <iostream>
using namespace std;

int main()
{
    string instr;
    cout<<"Enter machine instruction: ";
    getline(cin, instr);
    string base = "";
    for(int i = 0; i < instr.length(); i++)
    {
        if (instr[i] == ' ')
            break;
        base += toupper(instr[i]);
    }
    if (base.compare("MOV") == 0 ||
        base.compare("ADD") == 0 ||
        base.compare("SUB") == 0 ||
        base.compare("INR") == 0 ||
        base.compare("DCR") == 0 ||
        base.compare("LDAX") == 0 ||
        base.compare("STAX") == 0 ||
        base.compare("XCHG") == 0 ||
        base.compare("ADC") == 0 ||
        base.compare("SBB") == 0 ||
        base.compare("DAD") == 0 ||
        base.compare("INX") == 0 ||
        base.compare("DCX") == 0 ||
        base.compare("CMC") == 0 ||
        base.compare("STC") == 0 ||
        base.compare("SPHL") == 0 ||
        base.compare("XTHL") == 0 ||
        base.compare("PCHL") == 0 ||
        base.compare("PUSH") == 0 ||
        base.compare("POP") == 0 ||
        base.compare("CMP") == 0 ||
        base.compare("ANA") == 0 ||
        base.compare("ORA") == 0 ||
        base.compare("XRA") == 0 ||
        base.compare("RAL") == 0 ||
        base.compare("RAR") == 0 ||
        base.compare("RLC") == 0 ||
        base.compare("RRC") == 0 ||
        base.compare("CMA") == 0 ||
        base.compare("RET") == 0 ||
        base.compare("NOP") == 0 ||
        base.compare("HLT") == 0 ||
        base.compare("DI") == 0 ||
        base.compare("EI") == 0)
            cout<<"Size of Instruction: 1 byte"<<endl;
    else if (base.compare("MVI") == 0 ||
        base.compare("ADI") == 0 ||
        base.compare("ACI") == 0 ||
        base.compare("SUI") == 0 ||
        base.compare("SBI") == 0 ||
        base.compare("IN") == 0 ||
        base.compare("OUT") == 0 ||
        base.compare("CPI") == 0 ||
        base.compare("ANI") == 0 ||
        base.compare("ORI") == 0 ||
        base.compare("XRI") == 0)
            cout<<"Size of Instruction: 2 bytes"<<endl;
    else if (base.compare("LDA") == 0 ||
        base.compare("STA") == 0 ||
        base.compare("LHLD") == 0 ||
        base.compare("SHLD") == 0 ||
        base.compare("LXI") == 0 ||
        base.compare("JMP") == 0 ||
        base.compare("JZ") == 0 ||
        base.compare("CALL") == 0)
            cout<<"Size of Instruction: 3 bytes"<<endl;
    else
            cout<<"Instruction Not Part of 8085 Microprocessor Set!"<<endl;
    return 0;
}
