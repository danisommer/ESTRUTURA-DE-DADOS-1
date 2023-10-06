#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include "ListaEncadeada.h"
#include "ListaSequencial.h"

class Principal {
private:
    ListaSequencial listaSeq;
    ListaEncadeada listaEnc;
    int opcao, opcao2, N, op, contadorTXT;
    clock_t inicioSeq, fimSeq, inicioEnc, fimEnc;
    string nome, nomeEscolhido, RGEscolhido, linha, RG, nomeArquivoSec,nomeArquivoEnc;
    string diretorio;
    ifstream arquivo;

public:
    Principal();
    ~Principal();
    static void pausarExecucao();
    static void getArquivo(int &opcao2);
    static void getOpcao(int &opcao);
    static void calculaTempoExec(const string& tipoLista, clock_t inicio, clock_t fim);
    void Executar();

};


