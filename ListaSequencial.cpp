/*============================================================================*/
/* ICSF20 - ESTRUTURA DE DADOS 1 - 2023-2 - MAURO FONSECA                     */
/*----------------------------------------------------------------------------*/
/* AUTOR: DANIEL ZAKI SOMMER, 2582708                                         */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*============================================================================*/

#include "ListaSequencial.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Construtor da ListaSequencial
ListaSequencial::ListaSequencial() : capacidade() {}

// Destrutor da ListaSequencial
ListaSequencial::~ListaSequencial() {
    delete[] elementos;
}

// Função para preencher a lista sequencial a partir de um arquivo
void ListaSequencial::PreencherLista(ifstream &arquivo) {
    string linha, nome, rgStr;
    capacidade = 0;

    // Conta quantas linhas há no arquivo para determinar a capacidade da lista
    while (getline(arquivo, linha)) {
        capacidade++;
    }

    elementos = new Dado[capacidade]; // Aloca espaço para os elementos da lista

    // Retorna ao início do arquivo
    arquivo.clear();
    arquivo.seekg(0);

    // Preenche a lista com os elementos do arquivo
    for (int i = 0; i < capacidade; i++) {
        getline(arquivo, linha);
        stringstream ss(linha);

        // Lê o nome (parte antes da vírgula) e o RG (parte após a vírgula)
        getline(ss, nome, ',');
        getline(ss, rgStr);

        // Armazena os dados lidos na estrutura Dado na posição atual da lista
        elementos[i].nome = nome;
        elementos[i].rg = rgStr;
    }
}

// Função para inserir um elemento na lista sequencial
void ListaSequencial::InserirElemento(int pos, string &nome, string &rg) {
    int contadorCopias = 0;
    int contadorIf = 0;

    // pos = 0 → inicio | pos = -1 → fim | pos = N → qualquer posição

    contadorIf++;
    if (pos == 0) {
        // Inserir no início

        // Criar uma cópia dos elementos atuais
        Dado *copia = new Dado[capacidade];

        for (int i = 0; i < capacidade; i++) {
            copia[i].nome = elementos[i].nome;
            copia[i].rg = elementos[i].rg;
        }
        contadorCopias++;

        // Liberar memória dos elementos antigos
        delete[] elementos;

        // Incrementar a capacidade
        capacidade++;
        elementos = new Dado[capacidade];

        // Inserir novo elemento no início
        elementos[0].nome = nome;
        elementos[0].rg = rg;

        // Copiar os elementos antigos para a nova capacidade
        for (int j = 0; j < capacidade - 1; j++) {
            elementos[j + 1].nome = copia[j].nome;
            elementos[j + 1].rg = copia[j].rg;
        }
        contadorCopias++;

        // Liberar memória da cópia
        delete[] copia;

        cout << "Elemento " << nome << "," << rg << " inserido no inicio da lista sequencial\n" << endl;

    } else if (pos == -1) {
        contadorIf++;
        // Inserir no fim

        // Criar uma cópia dos elementos atuais
        Dado *copia = new Dado[capacidade];

        for (int i = 0; i < capacidade; i++) {
            copia[i].nome = elementos[i].nome;
            copia[i].rg = elementos[i].rg;
        }
        contadorCopias++;

        // Liberar memória dos elementos antigos
        delete[] elementos;

        // Incrementar a capacidade
        capacidade++;
        elementos = new Dado[capacidade];

        // Inserir novo elemento no fim
        elementos[capacidade - 1].nome = nome;
        elementos[capacidade - 1].rg = rg;

        // Copiar os elementos antigos para a nova capacidade
        for (int j = 0; j < capacidade - 1; j++) {
            elementos[j].nome = copia[j].nome;
            elementos[j].rg = copia[j].rg;
        }
        contadorCopias++;

        // Liberar memória da cópia
        delete[] copia;

        cout << "Elemento " << nome << "," << rg << " inserido no fim da lista sequencial\n" << endl;

    } else {
        contadorIf++;
        if (pos < 0 || pos > capacidade) {
            // Verificar se a posição é válida
            cout << "Posicao invalida." << endl;
            return;
        }

        // Inserir em qualquer posição
        Dado *copia = new Dado[capacidade + 1];

        // Copiar elementos até a posição pos
        for (int i = 0; i < pos; i++) {
            copia[i].nome = elementos[i].nome;
            copia[i].rg = elementos[i].rg;
        }
        contadorCopias++;

        // Inserir novo elemento na posição pos
        copia[pos].nome = nome;
        copia[pos].rg = rg;

        // Copiar os elementos restantes para a nova capacidade
        for (int i = pos; i < capacidade; i++) {
            copia[i + 1].nome = elementos[i].nome;
            copia[i + 1].rg = elementos[i].rg;
        }
        contadorCopias++;

        // Liberar memória dos elementos antigos
        delete[] elementos;

        // Incrementar a capacidade
        capacidade++;
        elementos = new Dado[capacidade];

        // Copiar elementos da cópia para a nova capacidade
        for (int j = 0; j < capacidade; j++) {
            elementos[j].nome = copia[j].nome;
            elementos[j].rg = copia[j].rg;
        }
        contadorCopias++;

        // Liberar memória da cópia
        delete[] copia;

        cout << "Elemento " << nome << "," << rg << " inserido na posicao " << pos << " da lista sequencial\n" << endl;
    }

    cout << "Numero de copias para a lista sequencial = " << contadorCopias << endl;
    cout << "Numero de IFs para a lista sequencial = " << contadorIf << "\n" << endl;
}

// Função para remover um elemento da lista sequencial
void ListaSequencial::RemoverElemento(int pos) {
    int contadorCopias = 0;
    int contadorIf = 0;

    // pos = 0 → inicio | pos = -1 → fim | pos = N → qualquer posição
    contadorIf++;
    if (capacidade == 0) {
        cout << "Lista vazia, não é possível remover." << endl;
        return;
    }
    contadorIf++;
    if (pos == 0) {
        // Armazena os dados do elemento que será removido
        Dado elementoRemovido = elementos[0];

        // Remover do início

        // Criar uma cópia dos elementos após a remoção
        Dado *copia = new Dado[capacidade - 1];

        // Copiar os elementos após o primeiro
        for (int i = 1; i < capacidade; i++) {
            copia[i - 1].nome = elementos[i].nome;
            copia[i - 1].rg = elementos[i].rg;
        }
        contadorCopias++;

        // Liberar memória dos elementos antigos
        delete[] elementos;

        // Atualizar a capacidade
        capacidade--;
        elementos = new Dado[capacidade];

        // Copiar elementos da cópia para a nova capacidade
        for (int j = 0; j < capacidade; j++) {
            elementos[j].nome = copia[j].nome;
            elementos[j].rg = copia[j].rg;
        }
        contadorCopias++;

        // Liberar memória da cópia
        delete[] copia;

        // Imprimir o elemento removido
        cout << "Elemento " << elementoRemovido.nome << "," << elementoRemovido.rg << " removido do inicio da lista sequencial\n" << endl;

    } else if (pos == -1) {
        contadorIf++;
        // Armazena os dados do elemento que será removido
        Dado elementoRemovido = elementos[capacidade - 1];

        // Criar uma cópia dos elementos antes da remoção
        Dado *copia = new Dado[capacidade - 1];

        // Copiar os elementos antes do último
        for (int i = 0; i < capacidade - 1; i++) {
            copia[i].nome = elementos[i].nome;
            copia[i].rg = elementos[i].rg;
        }
        contadorCopias++;

        // Liberar memória dos elementos antigos
        delete[] elementos;

        // Atualizar a capacidade
        capacidade--;
        elementos = new Dado[capacidade];

        // Copiar elementos da cópia para a nova capacidade
        for (int j = 0; j < capacidade; j++) {
            elementos[j].nome = copia[j].nome;
            elementos[j].rg = copia[j].rg;
        }
        contadorCopias++;

        // Liberar memória da cópia
        delete[] copia;

        // Imprimir o elemento removido
        cout << "Elemento " << elementoRemovido.nome << "," << elementoRemovido.rg << " removido do fim da lista sequencial\n" << endl;

    } else if (pos > 0 && pos < capacidade) {
        contadorIf++;
        // Armazena os dados do elemento que será removido
        Dado elementoRemovido = elementos[pos];

        // Criar uma cópia dos elementos após a remoção
        Dado *copia = new Dado[capacidade - 1];

        // Copiar os elementos antes da posição e após a posição
        for (int i = 0; i < pos; i++) {
            copia[i].nome = elementos[i].nome;
            copia[i].rg = elementos[i].rg;
        }
        contadorCopias++;

        for (int i = pos + 1; i < capacidade; i++) {
            copia[i - 1].nome = elementos[i].nome;
            copia[i - 1].rg = elementos[i].rg;
        }
        contadorCopias++;

        // Liberar memória dos elementos antigos
        delete[] elementos;

        // Atualizar a capacidade
        capacidade--;
        elementos = new Dado[capacidade];

        // Copiar elementos da cópia para a nova capacidade
        for (int j = 0; j < capacidade; j++) {
            elementos[j].nome = copia[j].nome;
            elementos[j].rg = copia[j].rg;
        }
        contadorCopias++;

        // Liberar memória da cópia
        delete[] copia;

        // Imprimir o elemento removido
        cout << "Elemento " << elementoRemovido.nome << "," << elementoRemovido.rg << " removido da posicao " << pos << " da lista sequencial\n" << endl;

    } else {
        cout << "Posicao invalida." << endl;
    }
    cout << "Numero de copias para a lista sequencial = " << contadorCopias << endl;
    cout << "Numero de IFs para a lista sequencial = " << contadorIf << "\n" << endl;
}

// Função para encontrar um elemento na lista sequencial com base no RG
void ListaSequencial::EncontrarElemento(string &RG) {
    int contadorIf = 0;
    for (int i = 0; i < capacidade; i++) {
        contadorIf++;
        if (elementos[i].rg == RG) {
            cout << "O elemento " << elementos[i].nome << "," << elementos[i].rg << " se encontra na posicao " << i << "\n" << endl;
            cout << "Numero de copias para a lista sequencial = 0" << endl;
            cout << "Numero de IFs para a lista sequencial = " << contadorIf << "\n" << endl;
            return;
        }
    }
    cout << "O elemento nao foi encontrado" << endl;
}

// Função para imprimir a lista sequencial
void ListaSequencial::ImprimirLista() {
    cout << "\nLISTA SEQUENCIAL:\n" << endl;

    for (int i = 0; i < capacidade; i++) {
        cout << i << ") Nome: " << elementos[i].nome << " | RG: " << elementos[i].rg << endl;
    }
}

// Função para exportar a lista sequencial para um arquivo
void ListaSequencial::ExportarLista(const string& nomeArquivo) {
    ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        cout << "Não foi possível abrir o arquivo." << endl;
        return;
    }

    for (int i = 0; i < capacidade; i++) {
        arquivo << elementos[i].nome << "," << elementos[i].rg << endl;
    }
    arquivo.close();
}
