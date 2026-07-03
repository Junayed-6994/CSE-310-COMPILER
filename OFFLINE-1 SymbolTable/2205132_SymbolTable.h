#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "2205132_ScopeTable.h"

class SymbolTable{

private:
    ScopeTable* current;
    int Num_Brackets;

public:
    SymbolTable(int Num_Brackets)
    {
        this->Num_Brackets = Num_Brackets;
        current = new ScopeTable(Num_Brackets); //Global Scope eita
    }

    ~SymbolTable()
    {
        while(current != nullptr)
        {
            ScopeTable* temp = current;
            current = current->getParentSCope();
            delete temp;
        }
    }

    ScopeTable* getParentSCope()
    {
        return current->getParentSCope();
    }

    void EnterScope()
    {
        ScopeTable* New_Scope = new ScopeTable(Num_Brackets,current);
        current = New_Scope;
        fout << "\tScopeTable# " << current->getId() << " created\n";

    }

    void ExitScope()
    {
        if(current->getParentSCope() == nullptr)
        {

            // fout << "\tScopeTable# 1 cannot be deleted\n";
            return ;

        }

        string id = current->getId();
        ScopeTable* temp = current;
        current = current->getParentSCope();
        delete temp;

        fout << "\tScopeTable# " << id << " removed\n";

    }

    void ExitAllScopes()
    {
        while(current != nullptr)
        {
            string id = current->getId();
            ScopeTable* temp = current;
            current = current->getParentSCope();
            delete temp;

            fout << "\tScopeTable# " << id << " removed\n";
        }
    }

    void insert(string Symbol_Name, string Symbol_Type)
    {
        int bucket_index,position;

        if(current->insert(Symbol_Name, Symbol_Type,bucket_index,position))
        {
            fout<<"\tInserted in ScopeTable# " << current->getId() << " at position " << bucket_index << ", " <<position << endl;
        }
        else
        {
            fout<<"\t'" <<Symbol_Name<<"' already exists in the current ScopeTable"<<endl;
        }
    }

    void remove(string Symbol_Name)
    {
        int bucket_index,position;
        if(current->remove(Symbol_Name,bucket_index,position))
        {
            fout<<"\tDeleted '" << Symbol_Name << "' from ScopeTable# " << current->getId() << " at position "<< bucket_index << ", " <<position << endl;
        }
        else
        {
            fout<<"\tNot found in the current ScopeTable"<<endl;
        }
    }

    void lookup(string Symbol_Name)
    {
        ScopeTable* temp = current;
        while(temp != nullptr)
        {
            int bucket_index,position;

            SymbolInfo* Entry_Check = temp->lookup(Symbol_Name,bucket_index,position);
            if(Entry_Check != nullptr)
            {
                fout << "\t'"<<Symbol_Name<<"' found in ScopeTable# "
                     << temp->getId() << " at position " << bucket_index << ", " << position << endl;
                return;
            }

            temp = temp->getParentSCope();
        }

        fout << "\t'"<<Symbol_Name<<"' not found in any of the ScopeTables\n";
    }

    void printCurrent()
    {
        current->print(1);
    }

    void printAll()
    {
        ScopeTable* temp = current;
        int depth = 1;

        while(temp != nullptr)
        {
            temp->print(depth);
            depth++;
            temp = temp->getParentSCope();
        }
    }
};

#endif
