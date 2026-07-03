#ifndef SYMBOLINFO_H
#define SYMBOLINFO_H

#include <string>
using namespace std;

class SymbolInfo{

private:
    string Symbol_Name,Symbol_Type;
    SymbolInfo* Next_Obj;

public:

        SymbolInfo(string Symbol_Name , string Symbol_Type , SymbolInfo* Next_Obj = nullptr)
        {
            this->Symbol_Name = Symbol_Name;
            this->Symbol_Type = Symbol_Type;
            this->Next_Obj = Next_Obj;
        }

        ~SymbolInfo()
        {
            // if(Next_Obj != nullptr) delete Next_Obj;
        }

        void set_Symbol_Name(string Symbol_Name)
        {
            this->Symbol_Name = Symbol_Name;
        }

        void set_Symbol_Type(string Symbol_Type)
        {
            this->Symbol_Type = Symbol_Type;
        }

        void set_Next_Obj(SymbolInfo* Next_Obj)
        {
            this->Next_Obj = Next_Obj;
        }

        string get_Symbol_Name()
        {
            return Symbol_Name;
        }

        string get_Symbol_Type()
        {
            return Symbol_Type;
        }

        SymbolInfo* getNext_Obj()
        {
            return Next_Obj;
        }

        //Not needed but debugging er zonno apatoto rakhlam
        // void show()
        // {
        //     cout<<"Symbol Name : " <<Symbol_Name<<endl;
        //     cout<<"Symbol Type : " <<Symbol_Type;
        // }

};


#endif