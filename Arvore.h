#ifndef TP3_ARVORE_H
#define TP3_ARVORE_H

#include <iostream>

struct Node {
    Node* esquerda;
    Node* direita;
    std::string letra;
    std::string codigoMorse;
};

class Arvore {
    private:
        Node* raiz;
        void constroiArvore(const std::string& pathArquivo);
        static void imprimeArvorePreOrdem(Node* nodeAtual);
    public:
        explicit Arvore(const std::string& pathArquivo);
        void adicionaNode(const std::string& codigoMorse, std::string letra);
        Node* obtemNode(const std::string& codigoMorse);
        void imprimeArvorePreOrdem();
};


#endif
