/*============================================================================*/
/* ICSF20 - ESTRUTURA DE DADOS 1 - 2023-2 - MAURO FONSECA                     */
/*----------------------------------------------------------------------------*/
/* AUTOR: DANIEL ZAKI SOMMER, 2582708                                         */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*============================================================================*/

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "ListaEncadeada.h"
#include "ListaSequencial.h"

using namespace std;

void pausarExecucao();
void getOpcao(int &opcao);
void calculaTempoExec(const string& tipoLista, clock_t inicio, clock_t fim);

void pausarExecucao() {
    cout << "Pressione Enter para continuar...";
    cin.get();
    cin.get(); // Aguarda um pressionamento de Enter
}

void getOpcao(int &opcao) {
    cout << "\nDigite a opcao que deseja utilizar:\n"
         << "(1) Inserir dado no inicio da lista\n"
         << "(2) Inserir dado no fim da lista\n"
         << "(3) Inserir dado em alguma posicao N da lista\n"
         << "(4) Remover dado no inicio da lista\n"
         << "(5) Remover dado no fim da lista\n"
         << "(6) Remover dado em alguma posicao N da lista\n"
         << "(7) Procurar um dado na lista\n"
         << "(8) Mostrar a lista completa\n"
         << "(9) Salvar a lista em um arquivo\n"
         << "(10) Ler a lista de um arquivo\n"
         << "(11) Escolher outro arquivo\n";
    cin >> opcao;
}

void calculaTempoExec(const string& tipoLista, clock_t inicio, clock_t fim) {
    double tempoExec = double(fim - inicio) / CLOCKS_PER_SEC;
    cout << "Tempo total de execucao para " << tipoLista <<": "<<  fixed << tempoExec << setprecision(5);
    cout << " sec" << endl;
}

int main() {
    clock_t inicioSeq, fimSeq, inicioEnc, fimEnc, inicio, fim;
    string nome, nomeEscolhido, RGEscolhido, diretorio, linha, RG;
    ListaSequencial listaSeq;
    ListaEncadeada listaEnc;
    int opcao = 0, N, contadorTXT = 0;
    ifstream arquivo;

    while (true) {

        if (arquivo.is_open()) {
            arquivo.close(); // Fechar o arquivo atual, se estiver aberto
        }

        cout << "Digite o nome do arquivo desejado (ou digite 'sair' para encerrar): " << endl;
        cin >> nome;

        if (nome == "sair") {
            cout << "Encerrando o programa." << endl;
            break;
        }

        diretorio = "C:/Users/fabri/Downloads/Programa��o/ESTRUTURA-DADOS-1/" + nome;
        arquivo.open(diretorio);

        if (!arquivo.is_open()) {
            cout << "Erro ao abrir o arquivo." << endl;
            continue; // Continuar para a pr�xima itera��o do loop
        }

        inicioSeq = clock();
        listaSeq.PreencherLista(arquivo);
        fimSeq = clock();

        inicioEnc = clock();
        listaEnc.PreencherLista(arquivo);
        fimEnc = clock();

        calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
        calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);

        while (opcao != 11) {

            getOpcao(opcao);

            switch (opcao) {
                case 1:
                    cout << "Insira o nome e rg que deseja adicionar" << endl;
                    cin >> nomeEscolhido;
                    cin >> RGEscolhido;

                    inicioSeq = clock();
                    listaSeq.InserirElemento(0, nomeEscolhido, RGEscolhido);
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.InserirElemento(0, nomeEscolhido, RGEscolhido);
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial", inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);
                    pausarExecucao();

                    break;


                case 2:
                    cout << "Insira o nome e rg que deseja adicionar" << endl;
                    cin >> nomeEscolhido;
                    cin >> RGEscolhido;

                    inicioSeq = clock();
                    listaSeq.InserirElemento(-1, nomeEscolhido, RGEscolhido);
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.InserirElemento(-1, nomeEscolhido, RGEscolhido);
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);
                    pausarExecucao();

                    break;

                case 3:
                    cout << "Digite a posicao desejada: " << endl;
                    cin >> N;
                    cout << "Insira o nome e rg que deseja adicionar" << endl;
                    cin >> nomeEscolhido;
                    cin >> RGEscolhido;

                    inicioSeq = clock();
                    listaSeq.InserirElemento(N, nomeEscolhido, RGEscolhido);
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.InserirElemento(N, nomeEscolhido, RGEscolhido);
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);
                    pausarExecucao();

                    break;

                case 4:
                    inicioSeq = clock();
                    listaSeq.RemoverElemento(0);
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.RemoverElemento(0);
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);
                    pausarExecucao();

                    break;

                case 5:
                    inicioSeq = clock();
                    listaSeq.RemoverElemento(-1);
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.RemoverElemento(-1);
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);
                    pausarExecucao();

                    break;

                case 6:
                    cout << "Digite a posicao desejada: " << endl;
                    cin >> N;
                    inicioSeq = clock();
                    listaSeq.RemoverElemento(N);
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.RemoverElemento(N);
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);
                    pausarExecucao();

                    break;

                case 7:
                    cout << "Digite o RG da pessoa que deseja encontrar: " << endl;
                    cin >> RG;
                    inicioSeq = clock();
                    listaSeq.EncontrarElemento(RG);
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.EncontrarElemento(RG);
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);
                    pausarExecucao();

                    break;

                case 8:
                    inicioSeq = clock();
                    listaSeq.ImprimirLista();
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.ImprimirLista();
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);
                    pausarExecucao();

                    break;

                case 9:
                    inicioSeq = clock();
                    listaSeq.ExportarLista("dados" + to_string(contadorTXT) + ".txt");
                    contadorTXT++;
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.ExportarLista("dados" + to_string(contadorTXT) + ".txt");
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada", inicioEnc, fimEnc);
                    pausarExecucao();

                    break;

                case 10:
                    inicio = clock();
                    listaSeq.LerArquivo(arquivo);
                    fim = clock();

                    calculaTempoExec("ler o .txt", inicio, fim);
                    pausarExecucao();

                    break;

                case 11:
                    cout << "Voltando para selecao de arquivo..." << endl;
                    break;

                default:
                    cout << "Escolha um n�mero de 1 a 11." << endl;
            }
        }
    }
    if (arquivo.is_open()) {
        arquivo.close();
    }
    return 0;
}
