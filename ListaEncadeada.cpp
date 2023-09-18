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
ListaEncadeada::ListaEncadeada() : inicio(nullptr) {}

// Destrutor padrão da ListaEncadeada
ListaEncadeada::~ListaEncadeada() = default;

// Função para preencher a lista encadeada a partir de um arquivo
void ListaEncadeada::PreencherLista(ifstream &arquivo) {
    while (inicio != nullptr) {
        Nodo* nodoAEliminar = inicio;
        inicio = inicio->proximo;
        delete nodoAEliminar;
    }
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

// Função para inserir um elemento na lista encadeada
void ListaEncadeada::InserirElemento(int pos, const string& nome, const string& rg) {
    //pos = 0 → inicio | pos = -1 → fim | pos = N → qualquer pos

    int contadorCopias = 0;
    int contadorIf = 0;

    // Cria um novo nodo com os dados fornecidos
    Nodo* novoNodo = new Nodo;
    novoNodo->dado.nome = nome;
    novoNodo->dado.rg = rg;
    contadorCopias+=2;

    // Armazena os dados do elemento que será inserido
    Dado elementoInserido = novoNodo->dado;

    contadorIf++;
    if (pos == 0) {
        // Inserir no início da lista
        novoNodo->proximo = inicio;
        inicio = novoNodo;
        contadorCopias+=2;

        // Imprimir o elemento inserido
        cout << "Elemento " << elementoInserido.nome << "," << elementoInserido.rg << " inserido no inicio da lista encadeada\n" << endl;

    } else if (pos == -1) {
        contadorIf++;
        // Inserir no fim da lista
        novoNodo->proximo = nullptr;
        contadorCopias++;
        contadorIf++;
        if (inicio == nullptr) {
            // Se a lista estiver vazia, o novo nodo se torna o início da lista
            inicio = novoNodo;
            contadorCopias++;

        } else {
            // Encontra o último nodo e insere após ele
            Nodo* atual = inicio;
            while (atual->proximo != nullptr) {
                atual = atual->proximo;
                contadorCopias++;
            }
            atual->proximo = novoNodo;
            contadorCopias++;

        }

        // Imprimir o elemento inserido
        cout << "Elemento " << elementoInserido.nome << "," << elementoInserido.rg << " inserido no fim da lista encadeada\n" << endl;

    } else {
        contadorIf++;
        if (pos < 0) {
            // Verificar se a posição é válida
            cout << "Posicao invalida." << endl;
            delete novoNodo; // Liberar a memória alocada para o novoNodo
            return;
        }

        // Inserir em uma posição específica
        contadorIf++;
        if (inicio == nullptr) {
            // Se a lista estiver vazia ou a posição for inválida, insere no início
            novoNodo->proximo = inicio;
            inicio = novoNodo;
            contadorCopias+=2;
        } else {
            Nodo* anterior = nullptr;
            Nodo* atual = inicio;
            contadorCopias+=2;
            int contador = 0;

            // Encontra a posição de inserção
            while (atual != nullptr && contador < pos) {
                anterior = atual;
                atual = atual->proximo;
                contadorCopias+=2;
                contador++;
            }

            contadorIf++;
            if (pos > contador) {
                // Verificar se a posição é válida
                cout << "Posicao invalida." << endl;
                delete novoNodo; // Liberar a memória alocada para o novoNodo
                return;
            }

            // Insere o novo nodo na posição encontrada
            anterior->proximo = novoNodo;
            novoNodo->proximo = atual;
            contadorCopias+=2;
        }

        // Imprimir o elemento inserido
        cout << "Elemento " << elementoInserido.nome << "," << elementoInserido.rg << " inserido na posicao " << pos << " da lista encadeada\n" << endl;
    }

    cout << "M(n) da lista encadeada = " << contadorCopias << endl;
    cout << "C(n) da lista encadeada = " << contadorIf << "\n" << endl;
}

// Função para remover um elemento da lista encadeada
void ListaEncadeada::RemoverElemento(int pos) {
    //pos = 0 → inicio | pos = -1 → fim | pos = N → qualquer pos
    int contadorIf = 0;
    int contadorCopias = 0;

    contadorIf++;
    if (inicio == nullptr) {
        cout << "Lista vazia, nenhum elemento para remover." << endl;
        return;
    }

    if (pos == 0) {
        // Armazena o elemento que será removido
        Dado elementoRemovido = inicio->dado;

        // Remover o elemento no início da lista
        Nodo* temp = inicio;
        inicio = inicio->proximo;
        contadorCopias+=2;
        delete temp;

        // Imprimir o elemento removido
        cout << "Elemento " << elementoRemovido.nome << "," << elementoRemovido.rg << " removido do inicio da lista encadeada\n" << endl;
    } else if (pos == -1) {
        contadorIf++;
        // Remover o elemento no fim da lista
        contadorIf++;
        if (inicio->proximo == nullptr) {
            // Se houver apenas um elemento na lista

            // Armazena o elemento que será removido
            Dado elementoRemovido = inicio->dado;

            delete inicio;
            inicio = nullptr;

            // Imprimir o elemento removido
            cout << "Elemento " << elementoRemovido.nome << "," << elementoRemovido.rg << "  removido do fim da lista encadeada\n" << endl;
        } else {
            Nodo* anterior = nullptr;
            Nodo* atual = inicio;
            contadorCopias+=2;

            while (atual->proximo != nullptr) {
                anterior = atual;
                atual = atual->proximo;
                contadorCopias+=2;
            }

            // Armazena o elemento que será removido
            Dado elementoRemovido = atual->dado;

            anterior->proximo = nullptr;
            contadorCopias++;

            delete atual;

            // Imprimir o elemento removido
            cout << "Elemento " << elementoRemovido.nome << "," << elementoRemovido.rg << "removido do fim da lista encadeada\n" << endl;
        }

    } else {
        // Remover elemento em uma posição específica
        contadorIf++;
        if (pos < 0) {
            cout << "Posicao invalida." << endl;
            return;
        }

        Nodo* anterior = nullptr;
        Nodo* atual = inicio;
        contadorCopias+=2;
        int contador = 0;

        while (atual != nullptr && contador < pos) {
            anterior = atual;
            atual = atual->proximo;
            contadorCopias+=2;
            contador++;
        }
        contadorIf++;
        if (pos > contador) {
            // Verificar se a posição é válida
            cout << "Posicao invalida." << endl;
            return;
        }
        contadorIf++;
        if (atual == nullptr) {
            cout << "Posicao invalida." << endl;
        } else {
            // Armazena o elemento que será removido
            Dado elementoRemovido = atual->dado;

            anterior->proximo = atual->proximo;
            contadorCopias++;

            delete atual;

            // Imprimir o elemento removido
            cout << "Elemento " << elementoRemovido.nome << "," << elementoRemovido.rg << " removido da posicao " << pos << " da lista encadeada\n" << endl;
        }
    }
    cout << "M(n) da lista sequencial = " << contadorCopias << endl;
    cout << "C(n) da lista sequencial = " << contadorIf << "\n" << endl;
}

// Função para encontrar um elemento na lista encadeada com base no RG
void ListaEncadeada::EncontrarElemento(string &RG) {
    Nodo* atual = inicio;
    int posicao = 0;
    int contadorIf = 0;
    int contadorCopias = 0;
    bool encontrado = false;

    while (atual != nullptr) {
        contadorIf++;
        if (atual->dado.rg == RG) {
            cout << "O elemento " << atual->dado.nome << "," << atual->dado.rg <<  " se encontra na posicao " << posicao << "\n" << endl;
            encontrado = true;
            break; // Elemento encontrado, podemos sair do loop
        }
        contadorCopias++;
        atual = atual->proximo;
        posicao++;
    }
    contadorIf++;
    if (!encontrado) {
        cout << "O elemento nao foi encontrado" << endl;
    }
    cout << "M(n) da lista encadeada = " << contadorCopias << endl;
    cout << "C(n) da lista encadeada = " << contadorIf << "\n" << endl;
}

// Função para imprimir a lista encadeada
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

// Função para exportar a lista encadeada para um arquivo
void ListaEncadeada::ExportarLista(const string& diretorio, const string& nomeArquivo) {
    ofstream arquivo(diretorio + nomeArquivo);

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
