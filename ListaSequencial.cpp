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
ListaSequencial::ListaSequencial() : capacidade(), elementos(), contadorIf(), contadorCop(), ordenada(false) {}

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

// Função para obter numero de IFs realizados
int ListaSequencial::getIFs() const
{
    return contadorIf;
}

// Função para obter numero de cópias realizadas
int ListaSequencial::getCopias() const
{
    return contadorCop;
}

// Função para obter valor que indica se a lista ja foi ordenada
bool ListaSequencial::getOrdenada() const
{
    return ordenada;
}

// Função para obter numero determinado elemento em posicao N da lista
ListaSequencial::Dado ListaSequencial::getElemento(int n)
{
    if (n == -1)
        return elementos[capacidade - 1];
    else if (n <= capacidade && n >= 0)
        return elementos[n];
    else
    {
        Dado null;
        return null;
    }
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

    if (pos < -1 || pos > capacidade)
    {
        cout << "posicao invalida LS" << endl;
        return;
    }

    for (int i = capacidade; i >= pos; i--)
    {
        elementos[i + 1].rg = elementos[i].rg;
        elementos[i + 1].nome = elementos[i].nome;
        contadorCop += 2;
    }

    elementos[pos].rg = rg;
    elementos[pos].nome = nome;
    contadorCop += 2;

    capacidade++;
}

// Função para remover um elemento da lista sequencial
void ListaSequencial::Remove(int pos)
{
    contadorIf = 0;
    contadorCop = 0;

    contadorIf++;
    pos = (pos == -1) ? capacidade : pos;

    for (int i = pos; i < capacidade; i++)
    {
        elementos[i].rg = elementos[i + 1].rg;
        elementos[i].nome = elementos[i + 1].nome;
        contadorCop += 2;
    }
    capacidade--;
}

// Função para encontrar um elemento na lista sequencial com base no RG por meio da busca sequencial
void ListaSequencial::EncontrarElementoSequencial(string& RG)
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

// Função para encontrar um elemento na lista sequencial com base no RG por meio da busca binaria
void ListaSequencial::EncontrarElementoBinaria(string& RG)
{
    contadorIf = 0;
    contadorCop = 0;

    // Primeiro, ordenar a lista com base no campo RG
    int esquerda = 0;
    int direita = capacidade - 1;
    bool encontrado = false;

    while (esquerda <= direita)
    {
        int meio = esquerda + (direita - esquerda) / 2;

        contadorIf++;
        if (elementos[meio].rg == RG)
        {
            cout << "O elemento " << elementos[meio].nome << "," << elementos[meio].rg << " se encontra na posicao " << meio - 1 << "\n" << endl;
            encontrado = true;
            break; // Elemento encontrado, podemos sair do loop
        }
        contadorIf++;
        if (elementos[meio].rg < RG)
        {
            esquerda = meio + 1;
        }
        else
        {
            direita = meio - 1;
        }
    }
    contadorIf++;
    if (!encontrado)
    {
        cout << "O elemento nao foi encontrado" << endl;
    }
}

// Função para selecionar o metodo de ordenação da lista
void ListaSequencial::OrdenarListaPorRG(int op)
{
    contadorIf = 0;
    contadorCop = 0;

    switch (op)
    {
    case 1:
        SelectionSort();
        break;
    case 2:
        InsertionSort();
        break;
    case 3:
        BubbleSort();
        break;
    case 4:
        ShellSort();
        break;
    case 5:
        QuickSort(0, capacidade - 1);
        break;
    case 6:
        MergeSort(0, capacidade - 1);
        break;
    default:
        cout << "Opcao invalida" << endl;
    }
}

// Métodos de ordenação
void ListaSequencial::SelectionSort()
{
    for (int i = 0; i < capacidade - 1; i++)
    {
        // Encontre o índice do elemento mínimo na parte não ordenada da lista
        int indiceMinimo = i;
        for (int j = i + 1; j < capacidade; j++)
        {
            contadorIf++;
            if (elementos[j].rg < elementos[indiceMinimo].rg)
            {
                indiceMinimo = j;
            }
        }

        // Troque o elemento mínimo com o primeiro elemento não ordenado
        if (indiceMinimo != i)
        {
            swap(elementos[i], elementos[indiceMinimo]);
            contadorCop += 3; // Conta as operações de troca
        }
    }
    ordenada = true;
}

void ListaSequencial::InsertionSort()
{
    for (int i = 1; i < capacidade; i++)
    {
        Dado chave = elementos[i];
        contadorCop++;
        int j = i - 1;

        // Mova os elementos da lista[0.i-1] que são maiores do que a chave
        // para uma posição à frente de sua posição atual
        while (j >= 0 && elementos[j].rg > chave.rg)
        {
            elementos[j + 1] = elementos[j];
            j = j - 1;
            contadorCop++;
        }
        contadorCop++;
        elementos[j + 1] = chave;
    }
    ordenada = true;
}

void ListaSequencial::BubbleSort()
{
    int n = capacidade;
    bool troca; // Variável para verificar se ocorreu alguma troca em uma passagem

    do
    {
        troca = false;
        for (int i = 0; i < n - 1; i++)
        {
            contadorIf++;
            if (elementos[i].rg > elementos[i + 1].rg)
            {
                // Trocar elementos[i] e elementos[i + 1]
                swap(elementos[i], elementos[i + 1]);
                contadorCop += 3; // Conta as operações de troca
                troca = true;
            }
        }
        n--;
    }
    while (troca);
    ordenada = true;
}

void ListaSequencial::ShellSort()
{
  int n = capacidade;
    int h = 1;

    // Define os intervalos (gaps) iniciais usando a sequência de Knuth
    while (h < n / 3)
    {
        h = 3 * h + 1;
    }

    while (h >= 1)
    {
        // Aplica o Insertion Sort com intervalo h
        for (int i = h; i < n; i++)
        {
            contadorCop++;
            Dado chave = elementos[i];
            int j = i;

            // Move os elementos que são maiores que a chave para a frente do array
            while (j >= h && elementos[j - h].rg > chave.rg)
            {
                elementos[j] = elementos[j - h];
                j -= h;
                contadorCop++;
            }
            contadorCop++;
            elementos[j] = chave;
        }

        // Reduz o intervalo (gap) de h para o próximo valor de Knuth
        h = h / 3;
    }
    ordenada = true;
}

void ListaSequencial::QuickSort(int baixo, int alto)
{
    contadorIf++;
    if (baixo < alto)
    {
        contadorCop++;
        Dado pivo = elementos[alto];
        int i = baixo - 1;

        for (int j = baixo; j <= alto - 1; j++)
        {
            contadorIf++;
            if (elementos[j].rg < pivo.rg)
            {
                i++;
                swap(elementos[i], elementos[j]);
                contadorCop += 3; // Conta as operações de troca
            }
        }

        swap(elementos[i + 1], elementos[alto]);
        contadorCop += 3; // Conta as operações de troca

        int pi = i + 1;

        QuickSort(baixo, pi - 1);
        QuickSort(pi + 1, alto);
    }
    ordenada = true;
}

void ListaSequencial::MergeSort(int baixo, int alto)
{
    contadorIf++;
    if (baixo < alto)
    {
        int meio = baixo + (alto - baixo) / 2;

        // Chame MergeSort recursivamente para as duas metades
        MergeSort(baixo, meio);
        MergeSort(meio + 1, alto);

        // Combine as duas metades classificadas
        int n1 = meio - baixo + 1;
        int n2 = alto - meio;

        Dado* subListaEsquerda = new Dado[n1];
        Dado* subListaDireita = new Dado[n2];

        for (int i = 0; i < n1; i++)
        {
            contadorCop++;
            subListaEsquerda[i] = elementos[baixo + i];
        }
        for (int j = 0; j < n2; j++)
        {
            contadorCop++;
            subListaDireita[j] = elementos[meio + 1 + j];
        }

        int i = 0;
        int j = 0;
        int k = baixo;

        while (i < n1 && j < n2)
        {
            contadorIf++;
            if (subListaEsquerda[i].rg <= subListaDireita[j].rg)
            {
                contadorCop++;
                elementos[k] = subListaEsquerda[i];
                i++;
            }
            else
            {
                contadorCop++;
                elementos[k] = subListaDireita[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            elementos[k] = subListaEsquerda[i];
            i++;
            k++;
            contadorCop++;
        }

        while (j < n2)
        {
            elementos[k] = subListaDireita[j];
            j++;
            k++;
            contadorCop++;
        }

        delete[] subListaEsquerda;
        delete[] subListaDireita;
    }
    ordenada = true;
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

// Função para limpar a lista sequencial
void ListaSequencial::LimparLista()
{
    delete[] elementos;
    capacidade = 0;
    ordenada = false;
}
