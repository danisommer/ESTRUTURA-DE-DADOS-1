#pragma once

#include <string>
#include <iostream>
#include "Lista.hpp"

using namespace std;

class ListaEncadeada : public Lista
{
private:
    struct Dado
    {
        string nome;
        int rg;
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
    int getIFs() const;
    int getCopias() const;
    void PreencherLista(ifstream& arquivo) override;
    void InsertFront(const string& nome, const int& rg);
    void InsertBack(const string& nome, const int& rg);
    void Insert(int pos, const string& nome, const int& rg) override;
    void RemoveFront();
    void RemoveBack();
    void Remove(int pos) override;
    void EncontrarElementoSequencial(int& RG) override;
    void ImprimirLista() override;
    void ExportarLista(const string& diretorio, const string& nomeArquivo) override;
    void LimparLista() override;
};
