#pragma once

#include <string>
#include <ctime>

using namespace std;

void pausarExecucao();
void getOpcao(int &opcao);
void calculaTempoExec(const string& tipoLista, clock_t inicio, clock_t fim);

using namespace std;

struct Dado {
    string nome;
    string rg;
};