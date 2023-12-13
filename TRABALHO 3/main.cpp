#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>

using namespace std;

// Estruturas e Funções da Árvore de Huffman
struct NoHuffman {
    char dado;
    int frequencia;
    NoHuffman *esquerda, *direita;

    NoHuffman(char d, int f) : dado(d), frequencia(f), esquerda(nullptr), direita(nullptr) {}
};

struct CompararNos {
    bool operator()(NoHuffman* esquerda, NoHuffman* direita) {
        return esquerda->frequencia > direita->frequencia;
    }
};

NoHuffman* construirArvoreHuffman(const unordered_map<char, int>& mapaFrequencia) {
    priority_queue<NoHuffman*, vector<NoHuffman*>, CompararNos> minHeap;

    for (const auto& par : mapaFrequencia) {
        minHeap.push(new NoHuffman(par.first, par.second));
    }

    while (minHeap.size() > 1) {
        NoHuffman* esquerda = minHeap.top();
        minHeap.pop();

        NoHuffman* direita = minHeap.top();
        minHeap.pop();

        auto* novoNo = new NoHuffman('$', esquerda->frequencia + direita->frequencia);
        novoNo->esquerda = esquerda;
        novoNo->direita = direita;

        minHeap.push(novoNo);
    }

    return minHeap.top();
}

void gerarCodigosHuffman(NoHuffman* raiz, const string& codigo, unordered_map<char, string>& codigosHuffman) {
    if (raiz == nullptr) {
        return;
    }

    if (raiz->dado != '$') {
        codigosHuffman[raiz->dado] = codigo;
    }

    gerarCodigosHuffman(raiz->esquerda, codigo + "0", codigosHuffman);
    gerarCodigosHuffman(raiz->direita, codigo + "1", codigosHuffman);
}

string comprimirArquivo(const string& nomeArquivoEntrada, const unordered_map<char, string>& codigosHuffman) {
    ifstream arquivoEntrada(nomeArquivoEntrada);
    string dadosComprimidos;

    char caractere;
    while (arquivoEntrada.get(caractere)) {
        dadosComprimidos += codigosHuffman.at(caractere);
    }

    arquivoEntrada.close();

    return dadosComprimidos;
}

void salvarArquivoComprimido(const string& nomeArquivoSaida, const string& dadosComprimidos, const unordered_map<char, string>& codigosHuffman) {
    ofstream arquivoSaida(nomeArquivoSaida);

    for (const auto& par : codigosHuffman) {
        arquivoSaida << par.first << ":" << par.second << "\n";
    }
    arquivoSaida << "\n";

    arquivoSaida << dadosComprimidos;

    arquivoSaida.close();
}

// Estruturas e Funções da Árvore de Busca Binária
struct NoArvore {
    string palavra;
    int ocorrencias;
    vector<int> posicoes;
    NoArvore* esquerda;
    NoArvore* direita;

    NoArvore(string p, int pos) : palavra(std::move(p)), ocorrencias(1), esquerda(nullptr), direita(nullptr) {
        posicoes.push_back(pos);
    }
};

string removerCaracteresEspeciais(const string& str) {
    string resultado;
    for (char ch : str) {
        if (isalpha(ch)) {
            resultado += tolower(ch);
        }
    }
    return resultado;
}

NoArvore* inserir(NoArvore* raiz, const string& palavra, int pos) {
    if (raiz == nullptr) {
        return new NoArvore(palavra, pos);
    }

    string palavraLimpa = removerCaracteresEspeciais(palavra);
    string palavraRaizLimpa = removerCaracteresEspeciais(raiz->palavra);

    int comparacao = palavraLimpa.compare(palavraRaizLimpa);

    if (comparacao == 0) {
        raiz->ocorrencias++;
        raiz->posicoes.push_back(pos);
    } else if (comparacao < 0) {
        raiz->esquerda = inserir(raiz->esquerda, palavra, pos);
    } else {
        raiz->direita = inserir(raiz->direita, palavra, pos);
    }

    return raiz;
}

vector<NoArvore*> buscar(NoArvore* raiz, const string& palavra) {
    vector<NoArvore*> resultados;

    if (raiz == nullptr) {
        return resultados;
    }

    string palavraRaizLimpa = removerCaracteresEspeciais(raiz->palavra);
    string palavraLimpa = removerCaracteresEspeciais(palavra);

    if (palavraLimpa.compare(palavraRaizLimpa) < 0) {
        resultados = buscar(raiz->esquerda, palavra);
    } else if (palavraLimpa.compare(palavraRaizLimpa) > 0) {
        resultados = buscar(raiz->direita, palavra);
    } else {
        resultados.push_back(raiz);
        vector<NoArvore*> resultadosEsquerda = buscar(raiz->esquerda, palavra);
        vector<NoArvore*> resultadosDireita = buscar(raiz->direita, palavra);

        resultados.insert(resultados.end(), resultadosEsquerda.begin(), resultadosEsquerda.end());
        resultados.insert(resultados.end(), resultadosDireita.begin(), resultadosDireita.end());
    }

    return resultados;
}

void imprimirContexto(const vector<string>& palavras, int posicao, int tamanhoContexto) {
    int inicio = max(0, posicao - tamanhoContexto);
    int fim = min(static_cast<int>(palavras.size()), posicao + tamanhoContexto + 1);

    for (int i = inicio; i < fim; ++i) {
        cout << palavras[i] << " ";
    }

    cout << endl;
}

void imprimirArvore(NoArvore* raiz) {
    if (raiz != nullptr) {
        imprimirArvore(raiz->esquerda);
        cout << "Palavra: " << raiz->palavra << ", Ocorrencias: " << raiz->ocorrencias << ", Posicoes: ";
        for (int pos : raiz->posicoes) {
            cout << pos << " ";
        }
        cout << endl;
        imprimirArvore(raiz->direita);
    }
}

int main() {
    priority_queue<NoHuffman*, vector<NoHuffman*>, CompararNos> minHeap;

    string nomeArquivo;
    unordered_map<char, int> mapaFrequencia;
    int escolha = 0;

    // Inicialização da Árvore de Busca Binária
    NoArvore* raizABB = nullptr;
    vector<string> palavras;

    // Inicialização da Árvore de Huffman
    NoHuffman* raizHuffman;
    unordered_map<char, string> codigosHuffman;

    cout << "Digite o nome do arquivo texto: ";
    cin >> nomeArquivo;

    ifstream arquivo("C:/Users/fabri/Downloads/Programacao/ESTRUTURA-DE-DADOS/TRABALHO 3/" + nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    // Contar a frequência de cada caractere no arquivo para codificação de Huffman
    char caractere;
    while (arquivo.get(caractere)) {
        mapaFrequencia[caractere]++;
    }

    // Construir a árvore de Huffman
    raizHuffman = construirArvoreHuffman(mapaFrequencia);
    gerarCodigosHuffman(raizHuffman, "", codigosHuffman);

    // Comprimir o arquivo usando códigos Huffman
    string dadosComprimidos = comprimirArquivo(nomeArquivo, codigosHuffman);

    // Salvar o arquivo comprimido
    salvarArquivoComprimido("C:/Users/fabri/Downloads/Programacao/ESTRUTURA-DE-DADOS/TRABALHO 3/comprimido_" + nomeArquivo, dadosComprimidos, codigosHuffman);

    cout << "Arquivo comprimido com sucesso." << endl;

    arquivo.close();

    // Construir Árvore de Busca Binária para ocorrências de palavras
    arquivo.open("C:/Users/fabri/Downloads/Programacao/ESTRUTURA-DE-DADOS/TRABALHO 3/" + nomeArquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    palavras.clear();

    string palavra;
    int posicao = 0;

    while (arquivo >> palavra) {
        palavras.push_back(palavra);
        raizABB = inserir(raizABB, palavra, posicao);
        posicao++;
    }

    cout << "Arvore binaria criada com sucesso." << endl;

    while (escolha != 3) {
        cout << "Escolha uma opcao:\n"
             << "1. Procurar uma palavra na arvore.\n"
             << "2. Mostrar arvore completa.\n"
             << "3. Sair do sistema.\n";

        cin >> escolha;

        switch (escolha) {
            case 1: {
                if (raizABB == nullptr) {
                    cerr << "A arvore binaria ainda nao foi criada." << endl;
                    continue;
                }

                cout << "Digite a palavra a ser procurada: ";
                cin >> nomeArquivo;

                vector<NoArvore*> resultados = buscar(raizABB, nomeArquivo);

                if (!resultados.empty()) {
                    for (NoArvore* resultado : resultados) {
                        cout << "Numero de ocorrencias: " << resultado->ocorrencias << endl;
                        cout << "Posicoes no arquivo: ";
                        for (int pos : resultado->posicoes) {
                            cout << pos << " ";
                        }
                        cout << endl;

                        for (int pos : resultado->posicoes) {
                            cout << "Contexto da ocorrencia na posicao " << pos << ":";
                            imprimirContexto(palavras, pos, 3);
                        }
                        cout << endl;
                    }
                } else {
                    cout << "Palavra nao encontrada na arvore." << endl;
                }

                break;
            }

            case 2: {
                if (raizABB == nullptr) {
                    cerr << "A arvore binaria ainda nao foi criada." << endl;
                    continue;
                }

                cout << "Arvore binaria completa:" << endl;
                imprimirArvore(raizABB);
                break;
            }

            case 3:
                cout << "Saindo do sistema." << endl;
                arquivo.close();
                break;

            default:
                cout << "Opção invalida. Tente novamente." << endl;
        }
    }

    while (!minHeap.empty()) {
        NoHuffman* no = minHeap.top();
        minHeap.pop();
        delete no;
    }

    return 0;
}
