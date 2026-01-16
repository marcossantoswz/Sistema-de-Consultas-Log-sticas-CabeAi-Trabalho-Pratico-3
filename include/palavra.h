#ifndef PALAVRA_H
#define PALAVRA_H

#include <string>
#include <iostream>
#include "logradouro.h"

using namespace std;

//Lista encadeada onde cada nó aponta para um Logradouro que contem a palavra
struct ListaInvertida {
    ListLogradouros* logradouroAlvo; //O ponteiro direto para a rua na memória
    ListaInvertida* proximo;
};

// Nó da Arvore AVL
struct NoArvore {
    string palavra;        
    ListaInvertida* listaOcorrencias; //lista de ruas que contem esta palavra
    
    NoArvore* esquerda;
    NoArvore* direita;
    int altura;
};

class Dicionario {
    private:
        NoArvore* raiz;

        // Métodos auxiliares recursivos
        NoArvore* inserirRecursivo(NoArvore* no, string palavra, ListLogradouros* logPtr);
        void destruirRecursivo(NoArvore* no);
        NoArvore* buscarRecursivo(NoArvore* no, string palavra);
        
        // Balanceamento AVL
        int getAltura(NoArvore* no);
        int getFatorBalanceamento(NoArvore* no);
        NoArvore* rotacaoDireita(NoArvore* y);
        NoArvore* rotacaoEsquerda(NoArvore* x);
        
        
        void insereNaLista(NoArvore* no, ListLogradouros* logPtr);

    public:
        Dicionario();
        ~Dicionario();

        // Agora recebe a palavra e o PONTEIRO para o logradouro existente
        void insere(string palavra, ListLogradouros* logPtr);

        // Retorna a lista de ponteiros
        ListaInvertida* buscar(string palavra);
};

#endif