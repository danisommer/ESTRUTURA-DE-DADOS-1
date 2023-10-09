/*============================================================================*/
/* ICSF20 - ESTRUTURA DE DADOS 1 - 2023-2 - MAURO FONSECA                     */
/*----------------------------------------------------------------------------*/
/* AUTOR: DANIEL ZAKI SOMMER, 2582708                                         */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*============================================================================*/
#define N_ARQUIVOS 7
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include "Principal.h"

using namespace std;

ListaSequencial Principal::listaSeq{};
ListaEncadeada Principal::listaEnc{};
clock_t Principal::inicioSeq = 0;
clock_t Principal::fimSeq = 0;
clock_t Principal::inicioEnc = 0;
clock_t Principal::fimEnc = 0;
string Principal::nomeEscolhido;
string Principal::RGEscolhido;
int Principal::opcao = -1;
int Principal::opcao2 = -1;

Principal::Principal() : N(), op(), contadorTXT(0)
{
    diretorio = "C:/Users/fabri/Downloads/Programacao/ESTRUTURA-DE-DADOS/ARQUIVOS_TXT/";
    Executar();
}

Principal::~Principal() = default;

// Função para pausar a execução e esperar pelo pressionamento de Enter
void Principal::pausarExecucao()
{
    cout << "Pressione Enter para continuar...";
    cin.get();
    cin.get(); // Aguarda um pressionamento de Enter

}

void Principal::mostraDados()
{

    cout << "\nLISTA SEQUENCIAL:" << endl;
    calculaTempoExec(inicioSeq, fimSeq);
    cout << "C(n) = " << listaSeq.getIFs() << endl;
    cout << "M(n) = " << listaSeq.getCopias() << "\n" << endl;

    cout << "\nLISTA ENCADEADA:" << endl;
    calculaTempoExec(inicioEnc, fimEnc);
    cout << "C(n) = " << listaEnc.getIFs() << endl;
    cout << "M(n) = " << listaEnc.getCopias() << "\n" << endl;

    pausarExecucao();
}

void Principal::mostraDadosSeq()
{

    cout << "\nLISTA SEQUENCIAL:" << endl;
    calculaTempoExec(inicioSeq, fimSeq);
    cout << "C(n) = " << listaSeq.getIFs() << endl;
    cout << "M(n) = " << listaSeq.getCopias() << "\n" << endl;

    pausarExecucao();
}

void Principal::getArquivo()
{
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

void Principal::getOpcao()
{
    //limparTela();
    cout << "\nDigite a opcao que deseja utilizar:\n"
         << "(1) Inserir dado no inicio da lista\n"
         << "(2) Inserir dado no fim da lista\n"
         << "(3) Inserir dado em alguma posicao N da lista\n"
         << "(4) Remover dado no inicio da lista\n"
         << "(5) Remover dado no fim da lista\n"
         << "(6) Remover dado em alguma posicao N da lista\n"
         << "(7) Procurar um dado na lista\n"
         << "(8) Ordenar elementos da lista\n"
         << "(9) Mostrar a lista completa\n"
         << "(10) Salvar a lista em um arquivo\n"
         << "(11) Escolher outro arquivo\n"
         << "(12) Sair\n";
    cin >> opcao;
}

void Principal::calculaTempoExec(clock_t inicio, clock_t fim)
{
    double tempoExec = double(fim - inicio) / CLOCKS_PER_SEC;
    cout << "Tempo de execucao: " << fixed << tempoExec << setprecision(5);
    cout << " sec" << endl;
}

void Principal::Executar()
{

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("C:/Users/fabri/Downloads/Programacao/ESTRUTURA-DE-DADOS/ARQUIVOS_TXT/*.*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "Erro ao abrir a pasta." << endl;
        return;
    }

    int fileCount = 0;

    do
    {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            // Se o item não for um diretório, é um arquivo.
            fileCount++;
        }
    }
    while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

    contadorTXT = (fileCount - N_ARQUIVOS) / 2;

    while (opcao != 12 && opcao2 != 9)
    {

        if (arquivo.is_open())
        {
            arquivo.close(); // Fechar o arquivo atual, se estiver aberto
        }

        opcao2 = 0;

        getArquivo();

        switch (opcao2)
        {

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

        if (!arquivo.is_open())
        {
            cout << "Erro ao abrir o arquivo." << endl;
            continue; // Continuar para a próxima iteração do loop
        }

        inicioSeq = clock();
        listaSeq.PreencherLista(arquivo); // Preencher a lista sequencial com dados do arquivo
        fimSeq = clock();
        cout << "Lista sequencial inicializada" << endl;
        calculaTempoExec(inicioSeq, fimSeq);

        inicioEnc = clock();
        listaEnc.PreencherLista(arquivo); // Preencher a lista encadeada com dados do arquivo
        fimEnc = clock();
        cout << "Lista encadeada inicializada" << endl;
        calculaTempoExec(inicioEnc, fimEnc);

        opcao = 0;

        while (opcao != 11 && opcao != 12)
        {
            getOpcao();

            switch (opcao)
            {
            case 1:
                cout << "Insira o nome e rg que deseja adicionar" << endl;
                cin >> nomeEscolhido;
                cin >> RGEscolhido;

                inicioSeq = clock();
                listaSeq.Insert(0, nomeEscolhido, RGEscolhido); // Inserir no início da lista sequencial
                fimSeq = clock();

                inicioEnc = clock();
                listaEnc.InsertFront(nomeEscolhido, RGEscolhido); // Inserir no início da lista encadeada
                fimEnc = clock();

                cout << "Elemento " << nomeEscolhido << "," << RGEscolhido << " inserido no inicio das listas" << endl;
                mostraDados();

                break;

            case 2:
                cout << "Insira o nome e rg que deseja adicionar" << endl;
                cin >> nomeEscolhido;
                cin >> RGEscolhido;

                inicioSeq = clock();
                listaSeq.Insert(-1, nomeEscolhido, RGEscolhido); // Inserir no fim da lista sequencial
                fimSeq = clock();

                inicioEnc = clock();
                listaEnc.InsertBack(nomeEscolhido, RGEscolhido); // Inserir no fim da lista encadeada
                fimEnc = clock();

                cout << "Elemento " << nomeEscolhido << "," << RGEscolhido << " inserido no fim das listas" << endl;
                mostraDados();

                break;

            case 3:
                cout << "Digite a posicao desejada: " << endl;
                cin >> N;
                cout << "Insira o nome e rg que deseja adicionar" << endl;
                cin >> nomeEscolhido;
                cin >> RGEscolhido;

                inicioSeq = clock();
                listaSeq.Insert(N, nomeEscolhido, RGEscolhido); // Inserir em uma posição específica na lista sequencial
                fimSeq = clock();

                inicioEnc = clock();
                listaEnc.Insert(N, nomeEscolhido, RGEscolhido); // Inserir em uma posição específica na lista encadeada
                fimEnc = clock();

                cout << "Elemento " << nomeEscolhido << "," << RGEscolhido << " inserido na posicao " << N << " das listas" << endl;
                mostraDados();

                break;

            case 4:
                cout << "Elemento " << listaSeq.getElemento(0).nome << "," << listaSeq.getElemento(0).rg << " removido da posicao inicial das listas" << endl;

                inicioSeq = clock();
                listaSeq.Remove(0); // Remover do início da lista sequencial
                fimSeq = clock();

                inicioEnc = clock();
                listaEnc.RemoveFront(); // Remover do início da lista encadeada
                fimEnc = clock();

                mostraDados();

                break;

            case 5:
                cout << "Elemento " << listaSeq.getElemento(-1).nome << "," << listaSeq.getElemento(-1).rg << " removido da posicao final das listas" << endl;

                inicioSeq = clock();
                listaSeq.Remove(-1); // Remover do fim da lista sequencial
                fimSeq = clock();

                inicioEnc = clock();
                listaEnc.RemoveBack(); // Remover do fim da lista encadeada
                fimEnc = clock();

                mostraDados();

                break;

            case 6:
                cout << "Digite a posicao desejada: " << endl;
                cin >> N;

                cout << "Elemento " << listaSeq.getElemento(N).nome << "," << listaSeq.getElemento(N).rg << " removido da posicao " << N << " das listas" << endl;

                inicioSeq = clock();
                listaSeq.Remove(N); // Remover de uma posição específica na lista sequencial
                fimSeq = clock();

                inicioEnc = clock();
                listaEnc.Remove(N); // Remover de uma posição específica na lista encadeada
                fimEnc = clock();

                mostraDados();

                break;

            case 7:
                cout << "Escolha uma forma de procurar o elemento:\n"
                     << "(1) Busca sequencial\n"
                     << "(2) Busca binaria.\n";
                cin >> op;

                switch (op)
                {
                case 1:
                    cout << "Digite o RG da pessoa que deseja encontrar: " << endl;
                    cin >> RG;
                    inicioSeq = clock();
                    listaSeq.EncontrarElementoSequencial(RG); // Procurar um dado na lista sequencial
                    fimSeq = clock();

                    inicioEnc = clock();
                    listaEnc.EncontrarElementoSequencial(RG); // Procurar um dado na lista encadeada
                    fimEnc = clock();

                    mostraDados();
                    break;
                case 2:
                    if (!listaSeq.getOrdenada())
                    {
                        cout << "Selecione o metodo de ordenacao:\n"
                             << "1) Selection-Sort\n"
                             << "2) Insertion-Sort\n"
                             << "3) Bubble-Sort\n"
                             << "4) Shell-Sort\n"
                             << "5) Quick-Sort\n"
                             << "6) Merge-Sort\n";
                        cin >> op;
                        listaSeq.OrdenarListaPorRG(op);
                    }

                    cout << "Digite o RG da pessoa que deseja encontrar: " << endl;
                    cin >> RG;
                    inicioSeq = clock();
                    listaSeq.EncontrarElementoBinaria(RG); // Procurar um dado na lista sequencial
                    fimSeq = clock();

                    mostraDadosSeq();
                    break;
                default:
                    cout << "Escolha uma das duas opcoes" << endl;
                }
                break;

            case 8:
                cout << "Selecione o metodo de ordenacao:\n"
                     << "1) Selection Sort\n"
                     << "2) Insertion-Sort\n"
                     << "3) Bubble-Sort\n"
                     << "4) Shell-Sort\n"
                     << "5) Quick-Sort\n"
                     << "6) Merge Sort\n";
                cin >> op;

                inicioSeq = clock();
                listaSeq.OrdenarListaPorRG(op);
                fimSeq = clock();

                mostraDadosSeq();

                cout << "Quer ver a lista ordenada? \n(1) SIM \n(2) NÃO" << endl;
                cin >> op;

                switch(op)
                {
                case 1:
                    listaSeq.ImprimirLista(); // Mostrar a lista sequencial completa
                    break;
                default:
                    continue;
                }
                break;

            case 9:
                inicioSeq = clock();
                listaSeq.ImprimirLista(); // Mostrar a lista sequencial completa
                fimSeq = clock();

                inicioEnc = clock();
                listaEnc.ImprimirLista(); // Mostrar a lista encadeada completa
                fimEnc = clock();

                cout << "\nLISTA SEQUENCIAL:" << endl;
                calculaTempoExec(inicioSeq, fimSeq);

                cout << "\nLISTA ENCADEADA:" << endl;
                calculaTempoExec(inicioEnc, fimEnc);
                pausarExecucao();

                break;

            case 10:
                cout << "Escolha uma opcao para salvar o arquivo:\n"
                     << "(1) Gerar arquivo automaticamente.\n"
                     << "(2) Gerar arquivo manualmente (escolher o nome).\n";
                cin >> op;

                switch (op)
                {
                case 1:

                    nomeArq = "Seq_Dados";
                    if(listaSeq.getOrdenada())
                        nomeArq += "_Ordenada";

                    inicioSeq = clock();
                    listaSeq.ExportarLista(diretorio, nomeArq + to_string(contadorTXT) + ".txt"); // Exportar a lista sequencial para um arquivo
                    fimSeq = clock();

                    cout << "\nLISTA SEQUENCIAL:" << endl;
                    calculaTempoExec(inicioSeq, fimSeq);

                    inicioEnc = clock();
                    listaEnc.ExportarLista(diretorio, "Enc_Dados" + to_string(contadorTXT) + ".txt"); // Exportar a lista encadeada para um arquivo
                    fimEnc = clock();

                    cout << "\nLISTA ENCADEADA:" << endl;
                    calculaTempoExec(inicioEnc, fimEnc);

                    contadorTXT++;
                    break;
                case 2:
                    cout << "Digite o nome do arquivo para salvar a lista sequencial (sem a extensao .txt): " << endl;
                    cin >> nomeArquivoSec;
                    cout << "Digite o nome do arquivo para salvar a lista encadeada (sem a extensao .txt): " << endl;
                    cin >> nomeArquivoEnc;

                    inicioSeq = clock();
                    listaSeq.ExportarLista(diretorio, nomeArquivoSec + ".txt"); // Exportar a lista sequencial para um arquivo
                    fimSeq = clock();

                    cout << "\nLISTA SEQUENCIAL:" << endl;
                    calculaTempoExec(inicioSeq, fimSeq);

                    inicioEnc = clock();
                    listaEnc.ExportarLista(diretorio, nomeArquivoEnc + ".txt"); // Exportar a lista encadeada para um arquivo
                    fimEnc = clock();

                    cout << "\nLISTA ENCADEADA:" << endl;
                    calculaTempoExec(inicioEnc, fimEnc);

                    break;
                default:
                    cout << "Escolha uma das duas opcoes." << endl;
                }

                pausarExecucao();

                break;

            case 11:
                cout << "Voltando para selecao de arquivo..." << endl;
                listaEnc.LimparLista();
                listaSeq.LimparLista();
                continue;

            case 12:
                cout << "Encerrando o programa." << endl;
                arquivo.close();
                continue;

            default:
                cout << "Escolha um numero de 1 a 12." << endl;
            }
        }
    }
}

