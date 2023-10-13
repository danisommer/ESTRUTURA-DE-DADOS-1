/*============================================================================*/
/* ICSF20 - ESTRUTURA DE DADOS 1 - 2023-2 - MAURO FONSECA                     */
/*----------------------------------------------------------------------------*/
/* AUTOR: DANIEL ZAKI SOMMER, 2582708                                         */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*============================================================================*/

#include "ListaEncadeada.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Construtor da ListaEncadeada
ListaEncadeada::ListaEncadeada() : inicio(nullptr), final(nullptr), capacidade(0), contadorIf(), contadorCop() {}

// Destrutor padrão da ListaEncadeada
ListaEncadeada::~ListaEncadeada()
{
    while (inicio != nullptr)
    {
        Node* NodeAEliminar = inicio;
        inicio = inicio->proximo;
        delete NodeAEliminar;
    }
}
// Função para obter numero de IFs realizados
int ListaEncadeada::getIFs() const
{
    return contadorIf;
}

// Função para obter numero de cópias realizadas
int ListaEncadeada::getCopias() const
{
    return contadorCop;
}

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
    contadorCop += 2;

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
        contadorCop += 2;
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
    contadorCop += 2;

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
        contadorCop += 2;
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
    if (pos < 0 || pos > capacidade)
    {
        cout << "posicao invalida LE" << endl;
        return;
    }

    // Cria um novo Node com os dados fornecidos
    Node* novoNode;
    novoNode = new Node;
    novoNode->dado.nome = nome;
    novoNode->dado.rg = rg;

    Node* pNode = inicio;

    if (pos == 0)
    {
        // Inserir na posição 0
        novoNode->proximo = inicio;
        novoNode->anterior = nullptr; // Não há um nó anterior ao primeiro
        if (inicio != nullptr)
        {
            inicio->anterior = novoNode; // Atualiza o nó anterior do nó atual de inicio
        }
        inicio = novoNode;
    }
    else
    {
        for (int i = 0; i < pos - 1; i++)
        {
            pNode = pNode->proximo;
        }
        novoNode->proximo = pNode->proximo;
        novoNode->anterior = pNode;
        if (pNode->proximo != nullptr)
        {
            pNode->proximo->anterior = novoNode; // Atualiza o nó anterior do nó seguinte
        }
        pNode->proximo = novoNode;
    }

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
    if (pos < 0 || pos >= capacidade)
    {
        cout << "Posicao invalida LE" << endl;
        return;
    }

    Node* pNode = inicio;

    if (pos == 0)
    {
        // Remoção do primeiro nó
        inicio = pNode->proximo;
        if (inicio != nullptr)
        {
            inicio->anterior = nullptr; // O novo início não tem nó anterior
        }
        delete pNode;
    }
    else
    {
        for (int i = 0; i < pos; i++)
        {
            pNode = pNode->proximo;
        }

        Node* nodeAnterior = pNode->anterior;
        Node* nodeSeguinte = pNode->proximo;

        if (nodeAnterior != nullptr)
        {
            nodeAnterior->proximo = nodeSeguinte;
        }

        if (nodeSeguinte != nullptr)
        {
            nodeSeguinte->anterior = nodeAnterior;
        }

        delete pNode;
    }

    capacidade--;
}

// Função para encontrar um elemento na lista sequencial com base no RG por meio da busca sequencial
void ListaEncadeada::EncontrarElementoSequencial(string& RG)
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

// Função para limpar a lista encadeada
void ListaEncadeada::LimparLista()
{
    while (inicio != nullptr)
    {
        Node* NodeAEliminar = inicio;
        inicio = inicio->proximo;
        delete NodeAEliminar;
    }

    // Reinicialize outras variáveis de controle, se necessário
    final = nullptr;
    capacidade = 0;
}
