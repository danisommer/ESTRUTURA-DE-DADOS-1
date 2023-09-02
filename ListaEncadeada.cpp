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
#include <utility>

using namespace std;

ListaEncadeada::ListaEncadeada() : inicio(nullptr) {}

ListaEncadeada::~ListaEncadeada() = default;

void ListaEncadeada::PreencherLista(ifstream &arquivo) {
    string linha, nome, rgStr;

    arquivo.clear();
    arquivo.seekg(0);

    Nodo* ultimoNodo = nullptr; // Mantém uma referência ao último nodo da lista

    while (getline(arquivo, linha)) {
        stringstream ss(linha);

        // Lê o nome (parte antes da vírgula) e o RG (parte após a vírgula)
        getline(ss, nome, ',');
        getline(ss, rgStr);

        // Cria um novo nodo para armazenar os dados lidos
        Nodo* novoNodo = new Nodo;
        novoNodo->dado.nome = nome;
        novoNodo->dado.rg = rgStr;
        novoNodo->proximo = nullptr; // O novo nodo será o último, então o próximo é nulo

        // Verifica se a lista está vazia
        if (inicio == nullptr) {
            inicio = novoNodo; // Se estiver vazia, o novo nodo se torna o início da lista
        } else {
            // Caso contrário, atualiza o próximo do último nodo para apontar para o novo nodo
            ultimoNodo->proximo = novoNodo;
        }

        // Atualiza o último nodo para o novo nodo
        ultimoNodo = novoNodo;
    }
}

void ListaEncadeada::InserirElemento(int pos, string nome, string rg) {
    //pos = 0 -> inicio | pos = -1 -> fim | pos = N -> qualquer pos

    // Cria um novo nodo com os dados fornecidos
    Nodo* novoNodo = new Nodo;
    novoNodo->dado.nome = std::move(nome);
    novoNodo->dado.rg = std::move(rg);

    if (pos == 0) {
        // Inserir no início da lista
        novoNodo->proximo = inicio;
        inicio = novoNodo;
    } else if (pos == -1) {
        // Inserir no fim da lista
        novoNodo->proximo = nullptr;
        if (inicio == nullptr) {
            // Se a lista estiver vazia, o novo nodo se torna o início da lista
            inicio = novoNodo;
        } else {
            // Encontra o último nodo e insere após ele
            Nodo* atual = inicio;
            while (atual->proximo != nullptr) {
                atual = atual->proximo;
            }
            atual->proximo = novoNodo;
        }
    } else {
        // Inserir em uma posição específica
        if (inicio == nullptr || pos <= 0) {
            // Se a lista estiver vazia ou a posição for inválida, insere no início
            novoNodo->proximo = inicio;
            inicio = novoNodo;
        } else {
            Nodo* anterior = nullptr;
            Nodo* atual = inicio;
            int contador = 0;

            // Encontra a posição de inserção
            while (atual != nullptr && contador < pos) {
                anterior = atual;
                atual = atual->proximo;
                contador++;
            }

            // Insere o novo nodo na posição encontrada
            anterior->proximo = novoNodo;
            novoNodo->proximo = atual;

        }
    }
}

void ListaEncadeada::RemoverElemento(int pos) {
    //pos = 0 -> inicio | pos = -1 -> fim | pos = N -> qualquer pos
    if (inicio == nullptr) {
        cout << "LE - Lista vazia, nenhum elemento para remover." << endl;
        return;
    }

    if (pos == 0) {
        // Remover o elemento no início da lista
        Nodo* temp = inicio;
        inicio = inicio->proximo;
        delete temp;
    } else if (pos == -1) {
        // Remover o elemento no fim da lista
        if (inicio->proximo == nullptr) {
            // Se houver apenas um elemento na lista
            delete inicio;
            inicio = nullptr;
        } else {
            Nodo* anterior = nullptr;
            Nodo* atual = inicio;

            while (atual->proximo != nullptr) {
                anterior = atual;
                atual = atual->proximo;
            }

            anterior->proximo = nullptr;
            delete atual;
        }
    } else {
        // Remover elemento em uma posição específica
        if (pos < 0) {
            cout << "LE - Posição inválida para remoção." << endl;
            return;
        }

        Nodo* anterior = nullptr;
        Nodo* atual = inicio;
        int contador = 0;

        while (atual != nullptr && contador < pos) {
            anterior = atual;
            atual = atual->proximo;
            contador++;
        }

        if (atual == nullptr) {
            cout << "LE - Posição não encontrada para remoção." << endl;
        } else {
            anterior->proximo = atual->proximo;
            delete atual;
        }
    }
}

void ListaEncadeada::EncontrarElemento(string &RG) {
    Nodo* atual = inicio;
    int posicao = 0;
    bool encontrado = false;

    while (atual != nullptr) {
        if (atual->dado.rg == RG) {
            cout << "O elemento se encontra na posicao " << posicao << endl;
            encontrado = true;
            break; // Elemento encontrado, podemos sair do loop
        }

        atual = atual->proximo;
        posicao++;
    }

    if (!encontrado) {
        cout << "O elemento nao foi encontrado" << endl;
    }
}

void ListaEncadeada::ImprimirLista() {
    Nodo* atual = inicio;
    int posicao = 0;
    cout << "\nLISTA ENCADEADA:\n" << endl;

    while (atual != nullptr) {
        cout << posicao << ") Nome: " << atual->dado.nome << " | RG: " << atual->dado.rg << endl;
        atual = atual->proximo;
        posicao++;
    }
}

void ListaEncadeada::ExportarLista(const string& nomeArquivo) {
    ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cout << "Não foi possível abrir o arquivo." << endl;
        return;
    }

    Nodo* atual = inicio;

    while (atual != nullptr) {
        arquivo << atual->dado.nome << "," << atual->dado.rg << endl;
        atual = atual->proximo;
    }

    arquivo.close();
}
