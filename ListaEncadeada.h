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

    struct Node
    {
        Dado dado;
        Node* proximo{};
        Node* anterior{};
    };

    Node* inicio;
    Node* final;
    int capacidade;
    int contadorIf;
    int contadorCop;

public:
    ListaEncadeada();
    ~ListaEncadeada();
    const int getIFs() override;
    const int getCopias() override;
    void PreencherLista(ifstream& arquivo) override;
    void InsertFront(const string& nome, const string& rg);
    void InsertBack(const string& nome, const string& rg);
    void Insert(int pos, const string& nome, const string& rg) override;
    void RemoveFront();
    void RemoveBack();
    void Remove(int pos) override;
    void EncontrarElemento(string& RG) override;
    void ImprimirLista() override;
    void ExportarLista(const string& diretorio, const string& nomeArquivo) override;
};
