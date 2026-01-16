#include "logradouro.h"
#include <iostream>
#include <iomanip>

using namespace std;

Logradouro::Logradouro(){
    logradouros_primeiro = nullptr;
    logradouros_ultimo = nullptr;
    num_logradouros = 0;
}

Logradouro::~Logradouro(){
    ListLogradouros* atual = logradouros_primeiro;
    while (atual != nullptr) {
        ListLogradouros* prox = atual->proximo;
        delete atual;
        atual = prox;
    }
    logradouros_primeiro = nullptr;
    logradouros_ultimo = nullptr;
}
        
// Método para inserir um logradouro Ja CALCULADO
void Logradouro::insere(int id, string tipo, string cep, string bairro, string regiao, string nome, double latMedia, double longMedia){
    ListLogradouros* novo = new ListLogradouros;

    novo->idLogradouro = id;
    novo->tipoLogradouro = tipo;
    novo->nomeLogradouro = nome;
    novo->bairro = bairro;
    novo->regiao = regiao;
    novo->cep = cep;
    novo->latitudeMedia = latMedia;
    novo->longitudeMedia = longMedia;
    novo->proximo = nullptr;

    //logica de inserção no final da lista
    if (logradouros_primeiro == nullptr) {
        //ista vazia: novo nó é o primeiro E o último
        logradouros_primeiro = novo;
        logradouros_ultimo = novo;
    } else {
        // Lista com elementos: conecta o atual último ao novo
        logradouros_ultimo->proximo = novo;
        // Atualiza o ponteiro 'logradouros_ultimo' para ser o novo nó
        logradouros_ultimo = novo;
    }
    this->num_logradouros++;
}
        
// Método para impressao e debug
void Logradouro::imprime(){
    ListLogradouros* atual = logradouros_primeiro;
    int contador = 0;

    if (atual == nullptr) {
        cout << "A lista de logradouros está vazia." << endl;
        return;
    }

    cout << "================ LISTA DE LOGRADOUROS ================" << endl;
    
    while (atual != nullptr) {
        cout << "Logradouro #" << contador + 1 << endl;
        cout << "ID: " << atual->idLogradouro << endl;
        cout << "Nome: " << atual->tipoLogradouro << " " << atual->nomeLogradouro << endl;
        cout << "Bairro: " << atual->bairro << endl;
        
        cout << fixed << setprecision(6); 
        cout << "Lat Média: " << atual->latitudeMedia << endl;
        cout << "Long Média: " << atual->longitudeMedia << endl;
        cout << "------------------------------------------------------" << endl;

        atual = atual->proximo;
        contador++;
    }
    
    cout << "Total de logradouros únicos: " << this->num_logradouros << endl;
    cout << "======================================================" << endl;
}
        
ListLogradouros* Logradouro::getPrimeiro(){
    return logradouros_primeiro;
}

int Logradouro::getNumLogradouros(){
    return this->num_logradouros;
}