#pragma once

#include <string>
#include <iostream>
#include "Lista.h"

using namespace std;

class ListaEncadeada : public Lista
{
private:
    struct Dado
    {
        string nome;
        string rg;
    };

    struct Nodo
    {
        Dado dado;
        Nodo* proximo{};
    };

    Nodo* inicio;

public:
    ListaEncadeada();
    ~ListaEncadeada();
    void PreencherLista(ifstream &arquivo) override;
    void InserirElemento(int pos, const string& nome, const string& rg) override;
    void RemoverElemento(int pos) override;
    void EncontrarElemento(string &RG) override;
    void ImprimirLista() override;
    void ExportarLista(const string& diretorio, const string& nomeArquivo) override;

};
