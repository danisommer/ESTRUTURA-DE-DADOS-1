#pragma once

#include <string>
#include "Lista.h"

using namespace std;

class ListaSequencial : public Lista
{
private:
    struct Dado
    {
        string nome;
        string rg;
    };

    Dado* elementos;
    int capacidade;
    int contadorIf;
    int contadorCop;

public:
    ListaSequencial();
    ~ListaSequencial();
    int getSize(ifstream& arquivo);
    const int getIFs() override;
    const int getCopias() override;
    void PreencherLista(ifstream& arquivo) override;
    void Insert(int pos, const string& nome, const string& rg) override;
    void Remove(int pos) override;
    void EncontrarElemento(string& RG) override;
    void ImprimirLista() override;
    void ExportarLista(const string& diretorio, const string& nomeArquivo) override;
};
