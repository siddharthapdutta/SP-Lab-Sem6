#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <iterator>
using namespace std;

int main()
{
    string line;
    string call;
    string macro_name;
    map<string, string> parameters;
    map<string, string>::iterator itr;
    ifstream inpfile ("Macro Definition.txt");
    ofstream outfile ("Macro Expansion.txt");

    // Getting MACRO Call Assembly Statement
    cout<<"Enter MACRO Call: ";
    getline(cin, call);

    // Creating Mapping
    macro_name = call.substr(0,call.find(' '));
    call = call.substr(call.find(' ')+1);
    stringstream check1(call);
    string inter;
    vector<string> arguments;
    while(getline(check1, inter, ','))
        arguments.push_back(inter);
    vector<string>::iterator ptr;
    for (ptr = arguments.begin(); ptr < arguments.end(); ptr++)
    {
        string temp = *ptr;
        parameters.insert(pair<string,string>(temp.substr(0,temp.find('=')), temp.substr(temp.find('=')+1)));
    }

    // Macro Expansion
    if (inpfile.is_open())
    {
        while(getline(inpfile, line))
        {
            if (line == "MACRO" || line.find(macro_name) == 0) // Skip Macro Header and Macro Prototype
                continue;
            if (line == "MEND")
                break;
            for (itr = parameters.begin(); itr != parameters.end(); ++itr)
            {
                int pos = line.find(itr->first);
                if (pos != -1)
                    line.replace(pos, (itr->first).size(), itr->second);
            }
            outfile<<line<<endl;
        }
    }
    cout<<"\nComplete!"<<endl;
    inpfile.close();
    outfile.close();
    return 0;
}
