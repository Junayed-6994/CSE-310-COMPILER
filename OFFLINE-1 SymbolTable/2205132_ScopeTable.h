#ifndef SCOPETABLE_H
#define SCOPETABLE_H

#include "2205132_SymbolInfo.h"
#include <fstream>
using namespace std;

extern ofstream fout;


class ScopeTable{

private:

    int Num_Brackets; //Hashing er zonno
    SymbolInfo** table; //2D cause first hash kore index e dhukbo and then symbols gula bhitore Linked thakbe
    ScopeTable* Parent_Scope; //For LookUp
    string id; //As prottekta ke unique id define krbo
    // int Child_Count;

    static int Next_Id;
public:

    ScopeTable(int Num_Brackets, ScopeTable* Parent_Scope = nullptr)
    {
        this->Num_Brackets = Num_Brackets;
        this->Parent_Scope = Parent_Scope;
        // this->Child_Count = 0;

        table = new SymbolInfo*[Num_Brackets];

        for(int i = 0 ; i < Num_Brackets ; i++)
        {
            table[i] = nullptr; 
        }

        id = to_string(Next_Id++);

        if(Parent_Scope == nullptr) 
        {
            fout << "\tScopeTable# " << id << " created\n";
        }

    }

    ~ScopeTable()
    {
        for(int i = 0 ; i < Num_Brackets ; i++)
        {
            SymbolInfo* current = table[i];

            while(current != nullptr)
            {
                SymbolInfo * temp = current;
                current = current->getNext_Obj();
                delete temp;
            }
        }

        delete[] table;
    }

    // void increment_Child_Count()
    // {
    //     this-> Child_Count++;
    // }

    string getId()
    {
        return id;
    }

    // int get_Child_Count()
    // {
    //     return Child_Count;
    // }

    ScopeTable* getParentSCope()
    {
        return Parent_Scope;
    }

    unsigned int SDBMHash(string str) {
        unsigned int hash = 0;
        unsigned int len = str.length();

        for(unsigned int i = 0; i < len; i++) {
            hash = ((str[i]) + (hash << 6) + (hash << 16) - hash) % Num_Brackets;
        }

        return hash;
    }

    bool insert(string Symbol_Name, string Symbol_Type, int& bucket_index, int& position)
    {
        int index = SDBMHash(Symbol_Name);
        bucket_index = index + 1;

        SymbolInfo* current = table[index];

        position = 1;

        //Dupclicate check korbo first e
        while(current != nullptr)
        {
            if(current->get_Symbol_Name() == Symbol_Name) return false;

            current = current->getNext_Obj();
        }

        //Age insert kri nai so now ekta new node banay tail(first insert first print output) e insert krbo
        SymbolInfo* New_Node = new SymbolInfo(Symbol_Name, Symbol_Type);

        if(table[index] == nullptr)
        {
            table[index] = New_Node;
        }

        else
        {
            current = table[index];
            while(current->getNext_Obj() != nullptr)
            {
                current = current->getNext_Obj();
                position++;
            }

            position++;
            current->set_Next_Obj(New_Node);
        }

        return true;
    }

    SymbolInfo* lookup(string Symbol_Name, int& bucket_index, int& position)
    {
        int index = SDBMHash(Symbol_Name);
        bucket_index = index + 1;
        position = 1;

        SymbolInfo* current = table[index];

        while(current != nullptr)
        {
            if(current->get_Symbol_Name() == Symbol_Name) return current;

            position++ ;
            current = current->getNext_Obj();
        }

        return nullptr;
    }

    bool remove(string Symbol_Name, int& bucket_index, int& position)
    {
        int index = SDBMHash(Symbol_Name);
        bucket_index = index + 1;
        position = 1;


        SymbolInfo* current = table[index];
        SymbolInfo* previous = nullptr;


        while(current != nullptr)
        {
            if(current->get_Symbol_Name() == Symbol_Name)
            {
                if(previous == nullptr)
                {
                    table[index] = current->getNext_Obj();
                }

                else
                {
                    previous->set_Next_Obj(current->getNext_Obj());
                }

                delete current;
                return true;
            }

            position++;
            previous = current;
            current = current->getNext_Obj();
        }

        return false;
    }

    void print(int depth)
    {
        string tabs(depth, '\t');
        fout << tabs << "ScopeTable# " <<id<<endl;

        for(int i=0 ; i < Num_Brackets ; i++)
        {
            fout << tabs << i+1 << "--> ";

            SymbolInfo* current = table[i];

            while(current != nullptr)
            {
                fout << "<" << current->get_Symbol_Name() << "," << current->get_Symbol_Type() << "> ";
                current = current->getNext_Obj();
            }

            fout<<endl;
        }
    }

};

int ScopeTable::Next_Id = 1 ;

#endif
