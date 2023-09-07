#pragma once

#include <string>
#include "Dado.h"
#include <iostream>

using namespace std;

struct Nodo {
    Dado dado;
    Nodo* proximo{};
};

class ListaEncadeada {
private:
    Nodo* inicio;

public:
    ListaEncadeada();
    ~ListaEncadeada();
    void PreencherLista(ifstream &arquivo);
    void InserirElemento(int pos, const string& nome, const string& rg);
    void RemoverElemento(int pos);
    void EncontrarElemento(string &RG);
    void ImprimirLista();
    void ExportarLista(const string& nomeArquivo);

};
