#include "../include/palavra.h"
#include <algorithm> //modificar isso aqui

using namespace std;

Dicionario::Dicionario() {
    raiz = nullptr;
}

Dicionario::~Dicionario() {
    destruirRecursivo(raiz);
}

void Dicionario::destruirRecursivo(NoArvore* no) {
    if (no != nullptr) {
        destruirRecursivo(no->esquerda);
        destruirRecursivo(no->direita);
        
        ListaInvertida* atual = no->listaOcorrencias;
        while (atual != nullptr) {
            ListaInvertida* prox = atual->proximo;
            delete atual;
            atual = prox;
        }
        delete no;
    }
}

int Dicionario::getAltura(NoArvore* no) {
    if (no == nullptr) return 0;
    return no->altura;
}

int Dicionario::getFatorBalanceamento(NoArvore* no) {
    if (no == nullptr) return 0;
    return getAltura(no->esquerda) - getAltura(no->direita);
}

NoArvore* Dicionario::rotacaoDireita(NoArvore* y) {
    NoArvore* x = y->esquerda;
    NoArvore* T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza alturas
    y->altura = max(getAltura(y->esquerda), getAltura(y->direita)) + 1;
    x->altura = max(getAltura(x->esquerda), getAltura(x->direita)) + 1;

    // Retorna nova raiz
    return x;
}

NoArvore* Dicionario::rotacaoEsquerda(NoArvore* x) {
    NoArvore* y = x->direita;
    NoArvore* T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza alturas
    x->altura = max(getAltura(x->esquerda), getAltura(x->direita)) + 1;
    y->altura = max(getAltura(y->esquerda), getAltura(y->direita)) + 1;

    // Retorna nova raiz
    return y;
}

//Auxiliar para inserir na lista encadeada
void Dicionario::insereNaLista(NoArvore* no, ListLogradouros* logPtr) {
    ListaInvertida* novo = new ListaInvertida;
    novo->logradouroAlvo = logPtr;
    novo->proximo = no->listaOcorrencias; 
    no->listaOcorrencias = novo;
}

void Dicionario::insere(string palavra, ListLogradouros* logPtr) {
    raiz = inserirRecursivo(raiz, palavra, logPtr);
}

NoArvore* Dicionario::inserirRecursivo(NoArvore* no, string palavra, ListLogradouros* logPtr) {
    //inserção normal de BST
    if (no == nullptr) {
        NoArvore* novo = new NoArvore;
        novo->palavra = palavra;
        novo->esquerda = nullptr;
        novo->direita = nullptr;
        novo->altura = 1;
        
        // Cria a lista e adiciona o primeiro elemento
        novo->listaOcorrencias = new ListaInvertida;
        novo->listaOcorrencias->logradouroAlvo = logPtr;
        novo->listaOcorrencias->proximo = nullptr;
        
        return novo;
    }

    if (palavra < no->palavra)
        no->esquerda = inserirRecursivo(no->esquerda, palavra, logPtr);
    else if (palavra > no->palavra)
        no->direita = inserirRecursivo(no->direita, palavra, logPtr);
    else {
        //Palavra ja existe apenas adiciona o logradouro na lista de logradour0os
        insereNaLista(no, logPtr);
        return no; 
    }

    //Atualiza altura do no
    no->altura = 1 + max(getAltura(no->esquerda), getAltura(no->direita));

    //Verifica se desbalanceou e roda
    int balance = getFatorBalanceamento(no);

    // Caso Esquerda-Esquerda
    if (balance > 1 && palavra < no->esquerda->palavra)
        return rotacaoDireita(no);

    // Caso Direita-Direita
    if (balance < -1 && palavra > no->direita->palavra)
        return rotacaoEsquerda(no);

    // Caso Esquerda-Direita
    if (balance > 1 && palavra > no->esquerda->palavra) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && palavra < no->direita->palavra) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

//busca palavra na arvore 
ListaInvertida* Dicionario::buscar(string palavra) {
    NoArvore* res = buscarRecursivo(raiz, palavra);
    if (res != nullptr) {
        return res->listaOcorrencias;
    }
    return nullptr;
}

//auxiliar da funcao de busca
NoArvore* Dicionario::buscarRecursivo(NoArvore* no, string palavra) {
    // --- ADICIONE ISSO ---
    //if (no != nullptr) {
        // Imprime o endereço de memória do nó atual no canal de erro
    //    cerr << "MEM:" << no << endl; 
    //}
    // ---------------------
    if (no == nullptr || no->palavra == palavra)
        return no;

    if (palavra < no->palavra)
        return buscarRecursivo(no->esquerda, palavra);

    return buscarRecursivo(no->direita, palavra);
}