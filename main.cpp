#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Arvore.h"

std::string decodificaMensagem(Arvore* arvore, const std::string& mensagem);

int main(int argc, char* argv[]) {
    Arvore* arvore = new Arvore("morse.txt"); //Cria arvore, passando o path do arquivo a ser lido.

    std::string mensagem;
    bool flagEndLine = false;
    std::string quebraLinha;
    while(getline(std::cin, mensagem)) { //Realiza a leitura das mensagens, enquanto ainda restar alguma.
        std::string mensagemDecodificada = decodificaMensagem(arvore, mensagem); //Decodifica mensagem.
        if(flagEndLine) {
            quebraLinha = "\n"; //Imprime endl para formatação do resultado.
        } else {
            flagEndLine = true;
        }
        std::cout << quebraLinha << mensagemDecodificada; //Imprime mensagem decodificada.
    }
    if(strcmp(argv[1], "-a") == 0) { //Verifica se argumento de impresão da árvore foi passado.
        arvore->imprimeArvorePreOrdem(); //Imprime arvore conforme Pre Ordem
    }
    return 0;
}

std::string decodificaMensagem(Arvore* arvore, const std::string& mensagem) {
    std::string mensagemDecodificada;
    std::string letraCodificada;
    for(char caracterMorse : mensagem) {//Realiza leitura da mensagem, caracter por caracter
        if(caracterMorse == '.' || caracterMorse == '-') { //Se for '.' ou '-' concatena na variavel letraCodificada
            letraCodificada += caracterMorse;
        } else if(caracterMorse == ' ' && !letraCodificada.empty()) { //Se for ' ' concatena letraCodificada à variavel mensagemDecodificada e limpa letraCodificada.
            Node* node = arvore->obtemNode(letraCodificada); //Utiliza arvore para obter node que contem a letra decodificada.
            mensagemDecodificada += node->letra;
            letraCodificada.clear();
        } else if(caracterMorse == '/') { //Se for '/' concatena espaço à mensagemDecodificada.
            mensagemDecodificada += " ";
        }
    }
    if(!letraCodificada.empty()) { //Por fim, imprime ultima letra, caso tenha restado.
        Node* node = arvore->obtemNode(letraCodificada);
        mensagemDecodificada += node->letra;
    }
    return mensagemDecodificada;
}