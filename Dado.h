#pragma once

#include <string>
#include <ctime>

using namespace std;

struct Dado {
    string nome;
    string rg;
};

//void limparTela();
void pausarExecucao();
void getArquivo(int &opcao2);
void getOpcao(int &opcao);
void calculaTempoExec(const string& tipoLista, clock_t inicio, clock_t fim);
