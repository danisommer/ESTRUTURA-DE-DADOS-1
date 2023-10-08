#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include "ListaEncadeada.h"
#include "ListaSequencial.h"

class Principal
{
private:
	static ListaSequencial listaSeq;
	static ListaEncadeada listaEnc;
	static clock_t inicioSeq, fimSeq, inicioEnc, fimEnc;
	static string nomeEscolhido, RGEscolhido;
	static int opcao, opcao2;
	int N, op, contadorTXT;
	string nome, linha, RG, nomeArquivoSec, nomeArquivoEnc;
	string diretorio;
	ifstream arquivo;

public:
	Principal();
	~Principal();
	static void mostraDados();
	static void pausarExecucao();
	static void getArquivo();
	static void getOpcao();
	static void calculaTempoExec(clock_t inicio, clock_t fim);
	void Executar();

};


