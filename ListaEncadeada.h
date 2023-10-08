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
	bool ordenada;

public:
	ListaEncadeada();
	~ListaEncadeada();
	int getIFs() const;
	int getCopias() const;
	bool getOrdenada() const;
	void PreencherLista(ifstream& arquivo) override;
	void InsertFront(const string& nome, const string& rg);
	void InsertBack(const string& nome, const string& rg);
	void Insert(int pos, const string& nome, const string& rg) override;
	void RemoveFront();
	void RemoveBack();
	void Remove(int pos) override;
	void EncontrarElementoSequencial(string& RG);
	void EncontrarElementoBinaria(string& RG);
	void OrdenarListaPorRG(int op);
	void SelectionSort();
	void InsertionSort();
	void BubbleSort();
	void ShellSort();
	void QuickSort();
	void MergeSort();
	void ImprimirLista() override;
	void ExportarLista(const string& diretorio, const string& nomeArquivo) override;
};
