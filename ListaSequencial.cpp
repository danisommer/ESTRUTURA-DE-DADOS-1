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

ListaSequencial::ListaSequencial() : capacidade() {}

ListaSequencial::~ListaSequencial() {
    delete[] elementos;
}

void ListaSequencial::PreencherLista(ifstream &arquivo) {

    string linha, nome, rgStr;
    capacidade = 0;

    while (getline(arquivo, linha)) {
        capacidade++;
    }

    elementos = new Dado[capacidade];

    //Retorna ao inicio do arquivo
    arquivo.clear();
    arquivo.seekg(0);

    // Preenche a lista com os elementos do arquivo
    for(int i = 0; i < capacidade; i++){
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

void ListaSequencial::InserirElemento(int pos, string &nome, string &rg) {
    // pos = 0 -> inicio | pos = -1 -> fim | pos = N -> qualquer posicao
    if (pos == 0) {
        // Inserir no início
        Dado *copia;

        // Criar uma cópia dos elementos atuais
        copia = new Dado[capacidade];

        for (int i = 0; i < capacidade; i++) {
            copia[i].nome = elementos[i].nome;
            copia[i].rg = elementos[i].rg;
        }

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

        // Liberar memória da cópia
        delete[] copia;
    } else if (pos == -1) {
        // Inserir no fim
        Dado *copia;

        // Criar uma cópia dos elementos atuais
        copia = new Dado[capacidade];

        for (int i = 0; i < capacidade; i++) {
            copia[i].nome = elementos[i].nome;
            copia[i].rg = elementos[i].rg;
        }

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

        // Liberar memória da cópia
        delete[] copia;
    } else {
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

        // Inserir novo elemento na posição pos
        copia[pos].nome = nome;
        copia[pos].rg = rg;

        // Copiar os elementos restantes para a nova capacidade
        for (int i = pos; i < capacidade; i++) {
            copia[i + 1].nome = elementos[i].nome;
            copia[i + 1].rg = elementos[i].rg;
        }

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

        // Liberar memória da cópia
        delete[] copia;
    }
}

void ListaSequencial::RemoverElemento(int pos) {
    //pos = 0 -> inicio | pos = -1 -> fim | pos = N -> qualquer posicao
    if (pos == 0) {
        // Remover do início
        if (capacidade == 0) {
            cout << "Lista vazia, não é possível remover." << endl;
            return;
        }

        // Criar uma cópia dos elementos após a remoção
        Dado *copia = new Dado[capacidade - 1];

        // Copiar os elementos após o primeiro
        for (int i = 1; i < capacidade; i++) {
            copia[i - 1].nome = elementos[i].nome;
            copia[i - 1].rg = elementos[i].rg;
        }

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

        // Liberar memória da cópia
        delete[] copia;
    } else if (pos == -1) {
        // Remover do fim
        if (capacidade == 0) {
            cout << "Lista vazia, não é possível remover." << endl;
            return;
        }

        // Criar uma cópia dos elementos antes da remoção
        Dado *copia = new Dado[capacidade - 1];

        // Copiar os elementos antes do último
        for (int i = 0; i < capacidade - 1; i++) {
            copia[i].nome = elementos[i].nome;
            copia[i].rg = elementos[i].rg;
        }

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

        // Liberar memória da cópia
        delete[] copia;
    } else if (pos >= 0 && pos < capacidade) {
        // Remover de uma posição específica
        if (capacidade == 0) {
            cout << "Lista vazia, não é possível remover." << endl;
            return;
        }

        // Criar uma cópia dos elementos após a remoção
        Dado *copia = new Dado[capacidade - 1];

        // Copiar os elementos antes da posição e após a posição
        for (int i = 0; i < pos; i++) {
            copia[i].nome = elementos[i].nome;
            copia[i].rg = elementos[i].rg;
        }
        for (int i = pos + 1; i < capacidade; i++) {
            copia[i - 1].nome = elementos[i].nome;
            copia[i - 1].rg = elementos[i].rg;
        }

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

        // Liberar memória da cópia
        delete[] copia;
    } else {
        cout << "Posição inválida." << endl;
    }
}

void ListaSequencial::EncontrarElemento(string &RG) {
    for(int i = 0; i < capacidade; i++){
        if (elementos[i].rg==RG){
            cout << "O elemento se encontra na posicao " << i << endl;
            return;
        }
    }
    cout << "O elemento nao foi encontrado" << endl;
}

void ListaSequencial::ImprimirLista() {
    cout << "\nLISTA SEQUENCIAL:\n" << endl;

    for (int i = 0; i < capacidade; i++) {
        cout << i << ") Nome: " << elementos[i].nome << " | RG: " << elementos[i].rg << endl;
    }
}

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

void ListaSequencial::LerArquivo(ifstream &arquivo) const {
    string linha;

    //Retorna ao inicio do arquivo
    arquivo.clear();
    arquivo.seekg(0);

    while(getline(arquivo, linha))
        cout << linha << endl;
}