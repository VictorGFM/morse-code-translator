#include <utility>

#include "Arvore.h"
#include <fstream>

Arvore::Arvore(const std::string& pathArquivo) { //Inicializa node raiz e chama funcao para construir arvore
    raiz = new Node();
    raiz->letra = "";
    raiz->codigoMorse = "";
    raiz->direita = nullptr;
    raiz->esquerda = nullptr;
    constroiArvore(pathArquivo);
}

void Arvore::constroiArvore(const std::string& pathArquivo) { //Constroi arvore por meio da leitura do conteudo do arquivo recebido.
    std::ifstream arquivoCodigoMorse;
    arquivoCodigoMorse.open(pathArquivo); //Abre arquivo.
    if(!arquivoCodigoMorse) { //Verifica se ocorreu erro ao tentar abrir o arquivo.
        std::cout << "Erro ao tentar abrir o arquivo!" << std::endl;
    }
    std::string linhaArquivo;
    while(getline(arquivoCodigoMorse, linhaArquivo)) { //Lê cada linha do arquivo, separando por letra e codigo morse, e adiciona na arvore.
        std::string letra = linhaArquivo.substr(0, 1);
        std::string codigoMorse = linhaArquivo.substr(2);
        adicionaNode(codigoMorse, letra);
    }
    arquivoCodigoMorse.close(); //Fecha arquivo.
}

void Arvore::adicionaNode(const std::string& codigoMorse, std::string letra) {
    Node* nodeAtual = raiz; //Define node atual como raiz inicialmente.
    for(char caracterMorse : codigoMorse) { //percorre todos os caracteres do codigo morse recebido
        if(caracterMorse=='.') { //Se o caracter for '.', caminha pela esquerda da arvore.
            Node* nodeEsquerdo = nodeAtual->esquerda;
            if(nodeEsquerdo == nullptr) { //Se o node esquerdo for nulo, entao cria novo node para dar suporte a adicao do node.
                nodeEsquerdo = new Node();
                nodeEsquerdo->letra = "";
                nodeEsquerdo->esquerda = nullptr;
                nodeEsquerdo->direita = nullptr;
                nodeAtual->esquerda = nodeEsquerdo;
            }
            nodeAtual = nodeEsquerdo; //Define nova posicao do nodeAtual, após percorrer parte da arvore.
        } else if(caracterMorse == '-') { //Se o caracter for '-', caminha pela direita da arvore.
            Node* nodeDireito = nodeAtual->direita;
            if(nodeDireito == nullptr) { //Se o node direito for nulo, entao cria novo node para dar suporte a adicao do node.
                nodeDireito = new Node();
                nodeDireito->letra = "";
                nodeDireito->esquerda = nullptr;
                nodeDireito->direita = nullptr;
                nodeAtual->direita = nodeDireito;
            }
            nodeAtual = nodeDireito; //Define nova posicao do nodeAtual, após percorrer parte da arvore.
        }
    }
    nodeAtual->letra = std::move(letra); //Inicializa letra do novo node adicionado.
    nodeAtual->codigoMorse = codigoMorse; //Inicializa codigo morse do novo node adicionado.
}

Node* Arvore::obtemNode(const std::string& codigoMorse) {
    Node* nodeAtual = raiz;
    for(char caracterMorse : codigoMorse) { //Percorre a arvore, caracter por caracter, até encontrar o node correspondente.
        if(caracterMorse=='.') { //Se o caracter for '.', caminha pela esquerda da arvore.
            Node* nodeEsquerdo = nodeAtual->esquerda;
            if(nodeEsquerdo == nullptr) {
                return nullptr; //Retorna null, caso o node procurado não exista na árvore.
            }
            nodeAtual = nodeEsquerdo;
        } else if(caracterMorse == '-') { //Se o caracter for '-', caminha pela direita da arvore.
            Node* nodeDireito = nodeAtual->direita;
            if(nodeDireito == nullptr) {
                return nullptr; //Retorna null, caso o node procurado não exista na árvore.
            }
            nodeAtual = nodeDireito;
        }
    }
    return nodeAtual; //Retorna node encontrado.
}

void Arvore::imprimeArvorePreOrdem() {
    imprimeArvorePreOrdem(raiz); //Chama função que imprime árvore conforme Pré Ordem.
}

void Arvore::imprimeArvorePreOrdem(Node* nodeAtual) {
    if(nodeAtual != nullptr) { //Enquanto node atual não for nulo, realiza processo de impressão.
        if(!nodeAtual->letra.empty()) { //Imprime letra e codigo morse do node atual, caso ele represente uma letra.
            std::cout << std::endl << nodeAtual->letra << " " << nodeAtual->codigoMorse;
        }
        imprimeArvorePreOrdem(nodeAtual->esquerda); //Realiza chamada recursiva, percorrendo a esquerda da árvore.
        imprimeArvorePreOrdem(nodeAtual->direita); //Realiza chamada recursiva, percorrendo a direita da árvore.
    }
}