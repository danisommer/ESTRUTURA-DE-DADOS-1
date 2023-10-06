#pragma once

#include <string>
#include "Lista.h"

using namespace std;

class ListaSequencial : public Lista {
private:
    struct Dado {
        string nome;
        string rg;
    };

    Dado* elementos;
    int capacidade;

public:
    ListaSequencial();
    ~ListaSequencial();
    void PreencherLista(ifstream &arquivo) override;
    void InserirElemento(int pos, const string &nome, const string &rg) override;
    void RemoverElemento(int pos) override;
    void EncontrarElemento(string &RG) override;
    void ImprimirLista() override;
    void ExportarLista(const string& diretorio, const string& nomeArquivo) override;
};
