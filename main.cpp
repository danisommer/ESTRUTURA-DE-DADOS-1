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
#include "Dado.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
using namespace std;

/*
void limparTela() {
  #ifdef _WIN32
  system("cls");
  #else
  system("clear");
  #endif
}
*/
// Função para pausar a execução e esperar pelo pressionamento de Enter
void pausarExecucao() {
    cout << "Pressione Enter para continuar...";
    cin.get();
    cin.get(); // Aguarda um pressionamento de Enter
}

//Função para obter o arquivo que será utilizado
void getArquivo(int &opcao2) {
    cout << "\nEscolha o arquivo que deseja abrir:\n"
         << "(1) NomeRG10\n"
         << "(2) NomeRG50\n"
         << "(3) NomeRG100\n"
         << "(4) NomeRG1K\n"
         << "(5) NomeRG10K\n"
         << "(6) NomeRG1M\n"
         << "(7) NomeRG100M\n"
         << "(8) Outro\n"
         << "(9) Sair\n";
    cin >> opcao2;
}

// Função para obter a opção do usuário
void getOpcao(int &opcao) {
    //limparTela();
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
         << "(10) Escolher outro arquivo\n"
         << "(11) Sair\n";
    cin >> opcao;
}

// Função para calcular e exibir o tempo de execução
void calculaTempoExec(const string& tipoLista, clock_t inicio, clock_t fim) {
    double tempoExec = double(fim - inicio) / CLOCKS_PER_SEC;
    cout << "Tempo total de execucao para " << tipoLista <<": "<<  fixed << tempoExec << setprecision(5);
    cout << " sec" << endl;
}

int main() {
    clock_t inicioSeq, fimSeq, inicioEnc, fimEnc;
    string nome, nomeEscolhido, RGEscolhido, linha, RG, nomeArquivoSec,nomeArquivoEnc;
    string diretorio = "C:/Users/fabri/Downloads/Programacao/ESTRUTURA-DE-DADOS/ARQUIVOS_TXT/";
    ListaSequencial listaSeq;
    ListaEncadeada listaEnc;
    int opcao = -1, opcao2 = -1, N, op, contadorTXT = 0;
    ifstream arquivo;

    while (opcao != 11 && opcao2 != 9) {


        if (arquivo.is_open()) {
            arquivo.close(); // Fechar o arquivo atual, se estiver aberto
        }

        opcao2 = 0;

        getArquivo(opcao2);

        switch (opcao2) {

            case 1:
                nome = "NomeRG10.txt";
                break;
            case 2:
                nome = "NomeRG50.txt";
                break;
            case 3:
                nome = "NomeRG100.txt";
                break;
            case 4:
                nome = "NomeRG1K.txt";
                break;
            case 5:
                nome = "NomeRG10K.txt";
                break;
            case 6:
                nome = "NomeRG1M.txt";
                break;
            case 7:
                nome = "NomeRG100M.txt";
                break;
            case 8:
                cout << "Digite o nome do arquivo: " << endl;
                cin >> nome;
                break;
            case 9:
                cout << "Encerrando o programa" << endl;
                continue;
            default:
                cout << "Escolha um numero de 1 a 9." << endl;
        }


        // Montar o caminho completo do arquivo
        arquivo.open(diretorio + nome);

        if (!arquivo.is_open()) {
            cout << "Erro ao abrir o arquivo." << endl;
            continue; // Continuar para a próxima iteração do loop
        }

        inicioSeq = clock();
        listaSeq.PreencherLista(arquivo); // Preencher a lista sequencial com dados do arquivo
        fimSeq = clock();
        cout << "Lista sequencial inicializada" << endl;
        calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);

        inicioEnc = clock();
        listaEnc.PreencherLista(arquivo); // Preencher a lista encadeada com dados do arquivo
        fimEnc = clock();
        cout << "Lista encadeada inicializada" << endl;
        calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);

        opcao = 0;


        while (opcao != 10 && opcao != 11) {

            getOpcao(opcao);

            switch (opcao) {
                case 1:
                    cout << "Insira o nome e rg que deseja adicionar" << endl;
                    cin >> nomeEscolhido;
                    cin >> RGEscolhido;

                    inicioSeq = clock();
                    listaSeq.InserirElemento(0, nomeEscolhido, RGEscolhido); // Inserir no início da lista sequencial
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.InserirElemento(0, nomeEscolhido, RGEscolhido); // Inserir no início da lista encadeada
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);

                    pausarExecucao();

                    break;

                case 2:
                    cout << "Insira o nome e rg que deseja adicionar" << endl;
                    cin >> nomeEscolhido;
                    cin >> RGEscolhido;

                    inicioSeq = clock();
                    listaSeq.InserirElemento(-1, nomeEscolhido, RGEscolhido); // Inserir no fim da lista sequencial
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.InserirElemento(-1, nomeEscolhido, RGEscolhido); // Inserir no fim da lista encadeada
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
                    listaSeq.InserirElemento(N, nomeEscolhido, RGEscolhido); // Inserir em uma posição específica na lista sequencial
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.InserirElemento(N, nomeEscolhido, RGEscolhido); // Inserir em uma posição específica na lista encadeada
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);

                    pausarExecucao();

                    break;

                case 4:
                    inicioSeq = clock();
                    listaSeq.RemoverElemento(0); // Remover do início da lista sequencial
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.RemoverElemento(0); // Remover do início da lista encadeada
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);

                    pausarExecucao();

                    break;

                case 5:
                    inicioSeq = clock();
                    listaSeq.RemoverElemento(-1); // Remover do fim da lista sequencial
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.RemoverElemento(-1); // Remover do fim da lista encadeada
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);

                    pausarExecucao();

                    break;

                case 6:
                    cout << "Digite a posicao desejada: " << endl;
                    cin >> N;
                    inicioSeq = clock();
                    listaSeq.RemoverElemento(N); // Remover de uma posição específica na lista sequencial
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.RemoverElemento(N); // Remover de uma posição específica na lista encadeada
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);

                    pausarExecucao();

                    break;

                case 7:
                    cout << "Digite o RG da pessoa que deseja encontrar: " << endl;
                    cin >> RG;
                    inicioSeq = clock();
                    listaSeq.EncontrarElemento(RG); // Procurar um dado na lista sequencial
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.EncontrarElemento(RG); // Procurar um dado na lista encadeada
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);

                    pausarExecucao();

                    break;

                case 8:
                    inicioSeq = clock();
                    listaSeq.ImprimirLista(); // Mostrar a lista sequencial completa
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.ImprimirLista(); // Mostrar a lista encadeada completa
                    fimEnc = clock();

                    calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);
                    calculaTempoExec("Lista Encadeada",inicioEnc, fimEnc);
                    pausarExecucao();

                    break;

                case 9:
                    cout << "\nEscolha uma opcao para salvar o arquivo:\n"
                         << "(1) Criar novo arquivo.\n"
                         << "(2) Salvar em arquivo ja existente.\n";
                    cin >> op;

                    switch (op) {
                        case 1:
                            inicioSeq = clock();
                            listaSeq.ExportarLista(diretorio,"Seq_Dados" + to_string(contadorTXT) + ".txt"); // Exportar a lista sequencial para um arquivo
                            fimSeq = clock();
                            calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);

                            inicioEnc = clock();
                            listaEnc.ExportarLista(diretorio,"Enc_Dados" + to_string(contadorTXT) + ".txt"); // Exportar a lista encadeada para um arquivo
                            fimEnc = clock();
                            calculaTempoExec("Lista Encadeada", inicioEnc, fimEnc);
                            break;
                        case 2:
                            cout << "Digite o nome do arquivo para salvar a lista sequencial: " << endl;
                            cin >> nomeArquivoSec;
                            cout << "Digite o nome do arquivo para salvar a lista encadeada: " << endl;
                            cin >> nomeArquivoEnc;

                            inicioSeq = clock();
                            listaSeq.ExportarLista(diretorio,nomeArquivoSec); // Exportar a lista sequencial para um arquivo
                            fimSeq = clock();
                            calculaTempoExec("Lista Sequencial",inicioSeq, fimSeq);

                            inicioEnc = clock();
                            listaEnc.ExportarLista(diretorio,nomeArquivoEnc); // Exportar a lista encadeada para um arquivo
                            fimEnc = clock();
                            calculaTempoExec("Lista Encadeada", inicioEnc, fimEnc);
                            break;
                        default:
                            cout << "Escolha uma das duas opcoes." << endl;
                    }

                    contadorTXT++;
                    pausarExecucao();

                    break;

                case 10:
                    cout << "Voltando para selecao de arquivo..." << endl;
                    break;

                case 11:
                    cout << "Encerrando o programa." << endl;
                    arquivo.close();
                    break;

                default:
                    cout << "Escolha um numero de 1 a 10." << endl;
            }
        }
    }
    return 1;
}

#pragma clang diagnostic pop