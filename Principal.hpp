#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include "ListaEncadeada.hpp"
#include "ListaSequencial.hpp"

class Principal
{
private:
    static ListaSequencial listaSeq;
    static ListaEncadeada listaEnc;
    static clock_t inicioSeq, fimSeq, inicioEnc, fimEnc;
    static string nomeEscolhido;
    int RGEscolhido, RG;
    static int opcao, opcao2;
    int N, op, contadorTXT;
    string nome, linha, nomeArquivoSec, nomeArquivoEnc, nomeArq;
    string diretorio;
    ifstream arquivo;

public:
    Principal();
    ~Principal();
    static void mostraDados();
    static void mostraDadosSeq();
    static void pausarExecucao();
    static void getArquivo();
    static void getOpcao();
    static void calculaTempoExec(clock_t inicio, clock_t fim);
    void Executar();

};


