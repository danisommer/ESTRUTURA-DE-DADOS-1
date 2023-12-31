#pragma once

#include <string>
#include "Lista.hpp"

using namespace std;

class ListaSequencial : public Lista
{
private:
    struct Dado
    {
        string nome;
        int rg;
    };

    Dado* elementos;
    int capacidade;
    int contadorIf;
    int contadorCop;
    bool ordenada;

public:
    ListaSequencial();
    ~ListaSequencial();
    int getSize(ifstream& arquivo);
    int getIFs() const;
    int getCopias() const;
    bool getOrdenada() const;
    Dado getElemento(int n);
    void PreencherLista(ifstream& arquivo) override;
    void Insert(int pos, const string& nome, const int& rg) override;
    void Remove(int pos) override;
    void EncontrarElementoSequencial(int& RG) override;
    void EncontrarElementoBinaria(int& RG);
    void OrdenarListaPorRG(int op);
    void SelectionSort();
    void InsertionSort();
    void BubbleSort();
    void ShellSort();
    void QuickSort(int baixo, int alto);
    void MergeSort(int baixo, int alto);
    void ImprimirLista() override;
    void ExportarLista(const string& diretorio, const string& nomeArquivo) override;
    void LimparLista() override;
};
