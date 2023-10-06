#pragma once

#include <string>
#include <iostream>

using namespace std;

class Lista {
public:
    virtual void PreencherLista(ifstream &arquivo) = 0;
    virtual void InserirElemento(int pos, const string& nome, const string& rg) = 0;
    virtual void RemoverElemento(int pos) = 0;
    virtual void EncontrarElemento(string &RG) = 0;
    virtual void ImprimirLista() = 0;
    virtual void ExportarLista(const string& diretorio, const string& nomeArquivo) = 0;
};
