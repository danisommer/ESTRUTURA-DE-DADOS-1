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
#include <vector>

using namespace std;

// Construtor da ListaSequencial
ListaSequencial::ListaSequencial() : capacidade(), elementos(), contadorIf(), contadorCop() {}

// Destrutor da ListaSequencial
ListaSequencial::~ListaSequencial()
{
    delete[] elementos;
}

// Função para obter o tamanho do arquivo
int ListaSequencial::getSize(ifstream& arquivo)
{
    string linha;
    capacidade = 0;

    // Conta quantas linhas há no arquivo para determinar a capacidade da lista
    while (getline(arquivo, linha))
    {
        capacidade++;
    }

    return capacidade;
}

// Função para preencher a lista sequencial a partir de um arquivo
void ListaSequencial::PreencherLista(ifstream& arquivo)
{
    string linha, nome, rgStr;
    capacidade = getSize(arquivo);

    elementos = new Dado[capacidade + 100]; // Aloca espaço para os elementos da lista

    // Retorna ao início do arquivo
    arquivo.clear();
    arquivo.seekg(0);

    // Preenche a lista com os elementos do arquivo
    for (int i = 0; i < capacidade; i++)
    {
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

// Função para inserir um elemento em qualquer posição da lista sequencial
void ListaSequencial::Insert(int pos, const string& nome, const string& rg)
{
    contadorIf = 0;
    contadorCop = 0;

    contadorIf++;
    pos = (pos == -1) ? capacidade : pos;

    for(int i = capacidade; i > pos; i--)
    {
        elementos[i + 1].rg = elementos[i].rg;
        elementos[i + 1].nome = elementos[i].nome;
        contadorCop += 2;
    }

    elementos[pos].rg = rg;
    elementos[pos].nome = nome;
    contadorCop = 2;

    capacidade++;
}

// Função para remover um elemento da lista sequencial
void ListaSequencial::Remove(int pos)
{
    contadorIf = 0;
    contadorCop = 0;

    contadorIf++;
    pos = (pos == -1) ? capacidade : pos;

    cout << "Elemento " << elementos[pos].nome << "," << elementos[pos].rg << " removido da posicao " << pos << " da lista sequencial\n" << endl;

    for(int i = pos; i < capacidade; i++)
    {
        elementos[i].rg = elementos[i + 1].rg;
        elementos[i].nome = elementos[i + 1].nome;
        contadorCop += 2;
    }
    capacidade--;
}

// Função para encontrar um elemento na lista sequencial com base no RG
void ListaSequencial::EncontrarElemento(string& RG)
{
    contadorIf = 0;
    contadorCop = 0;

    int posicao = 0;
    bool encontrado = false;

    for (int i = 0; i < capacidade; i++)
    {
        contadorIf++;
        if (elementos[i].rg == RG)
        {
            cout << "O elemento " << elementos[i].nome << "," << elementos[i].rg << " se encontra na posicao " << i << "\n" << endl;
            encontrado = true;
            break; // Elemento encontrado, podemos sair do loop
        }
        posicao++;
    }
    contadorIf++;
    if (!encontrado)
    {
        cout << "O elemento nao foi encontrado" << endl;
    }
}

// Função para imprimir a lista sequencial
void ListaSequencial::ImprimirLista()
{
    cout << "\nLISTA SEQUENCIAL:\n" << endl;

    for (int i = 0; i < capacidade; i++)
    {
        cout << i << ") Nome: " << elementos[i].nome << " | RG: " << elementos[i].rg << endl;
    }
}

// Função para exportar a lista sequencial para um arquivo
void ListaSequencial::ExportarLista(const string& diretorio, const string& nomeArquivo)
{
    ofstream arquivo(diretorio + nomeArquivo);

    if (!arquivo.is_open())
    {
        cout << "Não foi possível abrir o arquivo." << endl;
        return;
    }

    for (int i = 0; i < capacidade; i++)
    {
        arquivo << elementos[i].nome << "," << elementos[i].rg << endl;
    }
    arquivo.close();
}

// Função para obter numero de IFs realizados
const int ListaSequencial::getIFs()
{
    return contadorIf;
}

// Função para obter numero de cópias realizadas
const int ListaSequencial::getCopias()
{
    return contadorCop;
}


