#include <iostream>
#include <fstream>
#include <sstream>
#include "2205132_SymbolTable.h"

using namespace std;

ofstream fout;

int main()
{
    ifstream fin("input.txt");
    fout.open("output.txt");

    int bucket_size;
    fin >> bucket_size;
    fin.ignore();

    SymbolTable st(bucket_size);

    string line;
    int Cmd_No = 1;

    while(getline(fin, line))
    {
        if(line.empty()) continue;

        while (!line.empty() && (line.back() == ' ' || line.back() == '\t' || line.back() == '\r')) 
        {
            line.pop_back();
        }


        stringstream ss(line);
        string cmd;
        ss >> cmd;

        // if(!(cmd == "I" || cmd == "L" || cmd == "D" || cmd == "P" || cmd == "S" || cmd == "E" || cmd == "Q")) continue;

        // fout<< "Cmd " << Cmd_No++ << ": " << line <<endl;

        // cout<<"CMD FOR this line is " << cmd <<"\n";

        if(cmd == "I")
        {
            string Symbol_Name, Symbol_Type;

            if(!(ss >> Symbol_Name >> Symbol_Type))
            {
                // fout << "\tNumber of parameters mismatch for the command I\n";
                continue;
            }

            fout<< "Cmd " << Cmd_No++ << ": " << line <<endl;

            if(Symbol_Type == "FUNCTION")
            {
                string return_type;
                if(!(ss >> return_type))
                {
                    // fout << "\tNumber of parameters mismatch for the command I\n";
                    continue;
                }

                string temp, params = "";
                bool first = true;

                while(ss >> temp)
                {
                    if(!first) params += ',';
                    params += temp;
                    first = false;
                } 

                string Symbol_Type_FULL = Symbol_Type + "," + return_type + "<==(" + params + ")";

                st.insert(Symbol_Name,Symbol_Type_FULL);
            }


            else if (Symbol_Type == "STRUCT" || Symbol_Type == "UNION")
            {
                string Field_Type, Field_Name, extra = "{";
                bool first = true , error = false;

                while(ss >> Field_Type)
                {
                    if(!(ss >> Field_Name))
                    {
                        error = true;
                        break;
                    }

                    if(!first) extra+=",";
                    extra+= "(" + Field_Type + "," + Field_Name + ")";
                    first = false;
                }

                 if (error) 
                 {
                    // fout << "\tNumber of parameters mismatch for the command I\n";
                    continue;
                }
                
                extra += "}";

                string Symbol_Type_FULL = Symbol_Type + "," + extra;

                st.insert(Symbol_Name,Symbol_Type_FULL);
            }

            else
            {
                string extra;
                if(ss>>extra)
                {
                    // fout<<"\tNumber of parameters mismatch for the command I\n";
                    continue;
                }

                st.insert(Symbol_Name,Symbol_Type);
            }
        }

        else if(cmd == "L")
        {
            string Symbol_Name, extra;
            fout<< "Cmd " << Cmd_No++ << ": " << line <<endl;

            if(!(ss >> Symbol_Name) || ss >> extra)
            {
                fout<<"\tNumber of parameters mismatch for the command L\n";
                continue;               
            }

            st.lookup(Symbol_Name);
        }

        else if(cmd == "D")
        {
            string Symbol_Name, extra;
            
            fout<< "Cmd " << Cmd_No++ << ": " << line <<endl;
            
            if(!(ss >> Symbol_Name) || ss >> extra)
            {
                fout<<"\tNumber of parameters mismatch for the command D\n";
                continue;               
            }

            st.remove(Symbol_Name);
        }

        else if(cmd == "P")
        {
            string type;
            ss >> type;
            if(type == "A") 
            {
                fout<< "Cmd " << Cmd_No++ << ": " << line <<endl;
                st.printAll();
            }
            else if(type == "C")
            {
                fout<< "Cmd " << Cmd_No++ << ": " << line <<endl;
                st.printCurrent();
            }
            // else fout<<"\tNumber of parameters mismatch for the command P\n";
        }

        else if(cmd == "S") 
        {
            string remaining;
            ss >> remaining;
            if(remaining.size()!=0)
            {
                // fout<<"\tNumber of parameters mismatch for the command S\n";
            }

            fout<< "Cmd " << Cmd_No++ << ": " << line <<endl;
            st.EnterScope();
        }

        else if(cmd == "E") 
        {
            string remaining;
            ss >> remaining;
            if(remaining.size()!=0)
            {
                // fout<<"\tNumber of parameters mismatch for the command E\n";
            }

            ScopeTable* parent = st.getParentSCope();
            if(parent!=nullptr) fout<< "Cmd " << Cmd_No++ << ": " << line <<endl;

            st.ExitScope();
        }

        else if(cmd == "Q")
        {
            string remaining;
            ss >> remaining;
            if(remaining.size()!=0)
            {
                // fout<<"\tNumber of parameters mismatch for the command Q\n";
            }

            fout<< "Cmd " << Cmd_No++ << ": " << line <<endl;


            st.ExitAllScopes();

            // st.printAll();
            break;
        }

        // else
        // {
        //     fout<< "\tInvalid command\n";
        // } 
    }

    fin.close();
    fout.close();

    return 0;
}

