#pragma once

#include <string>
#include <iostream>

using namespace std;

class Lista
{
private:
    virtual void PreencherLista(ifstream& arquivo) = 0;
    virtual void Insert(int pos, const string& nome, const int& rg) = 0;
    virtual void Remove(int pos) = 0;
    virtual void ImprimirLista() = 0;
    virtual void ExportarLista(const string& diretorio, const string& nomeArquivo) = 0;
    virtual void EncontrarElementoSequencial(int& RG) = 0;
    virtual void LimparLista() = 0;
};
