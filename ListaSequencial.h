#pragma once

#include <string>
#include "Dado.h"

using namespace std;

class ListaSequencial {
private:
    Dado* elementos{};
    int capacidade;

public:
    ListaSequencial();
    ~ListaSequencial();
    void PreencherLista(ifstream &arquivo);
    void InserirElemento(int pos, string &nome, string &rg);
    void RemoverElemento(int pos);
    void EncontrarElemento(string &RG);
    void ImprimirLista();
    void ExportarLista(const string& diretorio, const string& nomeArquivo);
};
