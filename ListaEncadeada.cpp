/*============================================================================*/
/* ICSF20 - ESTRUTURA DE DADOS 1 - 2023-2 - MAURO FONSECA                     */
/*----------------------------------------------------------------------------*/
/* AUTOR: DANIEL ZAKI SOMMER, 2582708                                         */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*============================================================================*/

#include "ListaEncadeada.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Construtor da ListaEncadeada
ListaEncadeada::ListaEncadeada() : inicio(nullptr), final(nullptr), capacidade(0), contadorIf(), contadorCop() {}

// Destrutor padrão da ListaEncadeada
ListaEncadeada::~ListaEncadeada() = default;

// Função para preencher a lista encadeada a partir de um arquivo
void ListaEncadeada::PreencherLista(ifstream& arquivo)
{
    while (inicio != nullptr)
    {
        Node* NodeAEliminar = inicio;
        inicio = inicio->proximo;
        delete NodeAEliminar;
    }
    string linha, nome, rgStr;

    arquivo.clear();
    arquivo.seekg(0);

    while (getline(arquivo, linha))
    {
        stringstream ss(linha);

        // Lê o nome (parte antes da vírgula) e o RG (parte após a vírgula)
        getline(ss, nome, ',');
        getline(ss, rgStr);

        InsertBack(nome, rgStr);
    }
}

// Função para inserir elemento na frente da lista encadeada
void ListaEncadeada::InsertFront(const string& nome, const string& rg)
{
    contadorIf = 0;
    contadorCop = 0;

    Node* novoNode = new Node;
    novoNode->dado.nome = nome;
    novoNode->dado.rg = rg;
    contadorCop+=2;

    novoNode->anterior = nullptr;

    contadorIf++;
    if (inicio == nullptr)
    {
        novoNode->proximo = nullptr;
        final = novoNode;
        contadorCop++;
    }
    else
    {
        novoNode->proximo = inicio;
        inicio->anterior = novoNode;
        contadorCop+=2;
    }

    contadorCop++;
    inicio = novoNode;
    capacidade++;
}

// Função para inserir elemento no fim da lista encadeada
void ListaEncadeada::InsertBack(const string& nome, const string& rg)
{
    contadorIf = 0;
    contadorCop = 0;

    Node* novoNode = new Node;
    novoNode->dado.nome = nome;
    novoNode->dado.rg = rg;
    contadorCop+=2;

    novoNode->proximo = nullptr;

    contadorIf++;
    if (final == nullptr)
    {
        novoNode->anterior = nullptr;
        inicio = novoNode;
        contadorCop++;
    }
    else
    {
        contadorCop+=2;
        novoNode->anterior = final;
        final->proximo = novoNode;
    }

    contadorCop++;
    final = novoNode;
    capacidade++;
}

// Função para inserir elemento em uma posicao N da lista encadeada
void ListaEncadeada::Insert(int pos, const string& nome, const string& rg)
{
    contadorIf = 0;
    contadorCop = 0;

    Node* novoNode = new Node;
    novoNode->dado.nome = nome;
    novoNode->dado.rg = rg;
    contadorCop+=2;

    contadorCop++;
    Node* pNode = inicio;

    for (int i = 0; i < pos; i++)
    {
        contadorCop++;
        pNode = pNode->proximo;
    }

    contadorCop+=4;
    novoNode->anterior = pNode->anterior;
    novoNode->proximo = pNode;
    pNode->anterior->proximo = novoNode;
    pNode->anterior = novoNode;

    capacidade++;
}

// Função para remover elemento da frente da lista encadeada
void ListaEncadeada::RemoveFront()
{
    contadorIf = 0;
    contadorCop = 0;

    contadorIf++;
    if (inicio == nullptr)
    {
        // A lista está vazia, não há nada para remover.
        return;
    }

    contadorCop++;
    Node* temp = inicio;

    contadorIf++;
    if (inicio == final)
    {
        // A lista contém apenas um elemento.
        inicio = nullptr;
        final = nullptr;
    }
    else
    {
        contadorCop++;
        inicio = inicio->proximo;
        inicio->anterior = nullptr;
    }

    delete temp;
    capacidade--;
}

// Função para remover elemento do fim da lista encadeada
void ListaEncadeada::RemoveBack()
{
    contadorIf = 0;
    contadorCop = 0;

    contadorIf++;
    if (final == nullptr)
    {
        // A lista está vazia, não há nada para remover.
        return;
    }
    contadorCop++;
    Node* temp = final;

    contadorIf++;
    if (inicio == final)
    {
        // A lista contém apenas um elemento.
        inicio = nullptr;
        final = nullptr;
    }
    else
    {
        contadorCop++;
        final = final->anterior;
        final->proximo = nullptr;
    }

    delete temp;
    capacidade--;
}

// Função para remover elemento de uma posicao N da lista encadeada
void ListaEncadeada::Remove(int pos)
{
    contadorIf = 0;
    contadorCop = 0;

    contadorIf++;
    if (pos < 0 || pos >= capacidade)
    {
        // Posição inválida.
        return;
    }
    contadorCop++;
    Node* pNode = inicio;

    for (int i = 0; i < pos; i++)
    {
        contadorCop++;
        pNode = pNode->proximo;
    }
    contadorCop+=2;
    pNode->anterior->proximo = pNode->proximo;
    pNode->proximo->anterior = pNode->anterior;
    delete pNode;
    capacidade--;

}

// Função para encontrar um elemento na lista encadeada com base no RG
void ListaEncadeada::EncontrarElemento(string& RG)
{
    contadorIf = 0;
    contadorCop = 0;

    Node* atual = inicio;
    int posicao = 0;
    bool encontrado = false;

    while (atual != nullptr)
    {
        contadorIf++;
        if (atual->dado.rg == RG)
        {
            cout << "O elemento " << atual->dado.nome << "," << atual->dado.rg << " se encontra na posicao " << posicao << "\n" << endl;
            encontrado = true;
            break; // Elemento encontrado, podemos sair do loop
        }
        contadorCop++;
        atual = atual->proximo;
        posicao++;
    }
    contadorIf++;
    if (!encontrado)
    {
        cout << "O elemento nao foi encontrado" << endl;
    }
}

// Função para imprimir a lista encadeada
void ListaEncadeada::ImprimirLista()
{
    Node* atual = inicio;
    int posicao = 0;
    cout << "\nLISTA ENCADEADA:\n" << endl;

    while (atual != nullptr)
    {
        cout << posicao << ") Nome: " << atual->dado.nome << " | RG: " << atual->dado.rg << endl;
        atual = atual->proximo;
        posicao++;
    }
}

// Função para exportar a lista encadeada para um arquivo
void ListaEncadeada::ExportarLista(const string& diretorio, const string& nomeArquivo)
{
    ofstream arquivo(diretorio + nomeArquivo);

    if (!arquivo.is_open())
    {
        cout << "Não foi possível abrir o arquivo." << endl;
        return;
    }

    Node* atual = inicio;

    while (atual != nullptr)
    {
        arquivo << atual->dado.nome << "," << atual->dado.rg << endl;
        atual = atual->proximo;
    }

    arquivo.close();
}

// Função para obter numero de IFs realizados
const int ListaEncadeada::getIFs()
{
    return contadorIf;
}

// Função para obter numero de cópias realizadas
const int ListaEncadeada::getCopias()
{
    return contadorCop;
}