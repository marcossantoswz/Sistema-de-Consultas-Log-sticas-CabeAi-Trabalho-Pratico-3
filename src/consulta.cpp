#include "../include/consulta.h"
#include <cmath>
#include <iostream>

using namespace std;

Consulta::Consulta(){
    this->candidatosAtuais = nullptr;
    this->resultadoFinal = nullptr;
}

Consulta::~Consulta(){
    // limpando memoria
    while(candidatosAtuais != nullptr){
        ListaInvertida* temp = candidatosAtuais;
        candidatosAtuais = candidatosAtuais->proximo;
        delete temp;
    }
    while(resultadoFinal != nullptr){
        ResultadoOrdenado* temp = resultadoFinal;
        resultadoFinal = resultadoFinal->proximo;
        delete temp;
    }
}

//inicializa a busca com a lista da primeira palavra
void Consulta::iniciarBusca(ListaInvertida* listaPrimeiraPalavra){
    
    //limpar lista anterior se houver
    while(this->candidatosAtuais != nullptr){
        ListaInvertida* temp = this->candidatosAtuais;
        this->candidatosAtuais = this->candidatosAtuais->proximo;
        delete temp;
    }
    this->candidatosAtuais = nullptr;
    
    ListaInvertida* origem = listaPrimeiraPalavra;
    ListaInvertida* ultimoCopiado = nullptr;

    while(origem != nullptr){
        ListaInvertida* novo = new ListaInvertida;
        novo->logradouroAlvo = origem->logradouroAlvo;
        novo->proximo = nullptr;

        if(this->candidatosAtuais == nullptr){
            this->candidatosAtuais = novo;
            ultimoCopiado = novo;
        } else {
            ultimoCopiado->proximo = novo;
            ultimoCopiado = novo;
        }
        origem = origem->proximo;
    }
}

// Função auxiliar estatica para ver se logradouro existe na lista
bool existeNaLista(ListaInvertida* listaOndeProcurar, int idAlvo) {
    ListaInvertida* aux = listaOndeProcurar;
    while (aux != nullptr) {
        if (aux->logradouroAlvo->idLogradouro == idAlvo) {
            return true;
        }
        aux = aux->proximo;
    }
    return false; //varreu a lista toda e não achou
}

// filtra os candidatos atuais mantendo APENAS quem também está na nova lista
void Consulta::intersectar(ListaInvertida* listaNovaPalavra) {
    // Se a nova palavra não existe em lugar nenhum a interseção é vazia
    if (listaNovaPalavra == nullptr) {
        while (candidatosAtuais != nullptr) {
            ListaInvertida* temp = candidatosAtuais;
            candidatosAtuais = candidatosAtuais->proximo;
            delete temp;
        }
        return;
    }

    ListaInvertida* atual = candidatosAtuais;
    ListaInvertida* anterior = nullptr;

    while (atual != nullptr) {
        // Verifica se o candidato atual existe na lista da nova palavra
        bool mantemLogradouro = existeNaLista(listaNovaPalavra, atual->logradouroAlvo->idLogradouro);

        if (mantemLogradouro) {
            anterior = atual;
            atual = atual->proximo;
        } else {
            ListaInvertida* paraDeletar = atual;

            if (anterior == nullptr) {
                candidatosAtuais = atual->proximo;
                atual = candidatosAtuais;
            } else {
                anterior->proximo = atual->proximo;
                atual = atual->proximo;
            }
            
            delete paraDeletar; 
        }
    }
}

// calcula distasncias e gera a lista final ordenada pronta pra impressao
void Consulta::processarResultados(double latOrigem, double longOrigem, int maxResultados) {
    // Limpa resultados anteriores
    while (resultadoFinal != nullptr) {
        ResultadoOrdenado* temp = resultadoFinal;
        resultadoFinal = resultadoFinal->proximo;
        delete temp;
    }
    resultadoFinal = nullptr;

    if (candidatosAtuais == nullptr) {
        return;
    }

    ListaInvertida* atual = candidatosAtuais;
    int totalEncontrados = 0;

    // CALCULA E ORDENA (Insertion Sort na Lista Encadeada)
    while (atual != nullptr) {
        totalEncontrados++;
        ListLogradouros* rua = atual->logradouroAlvo;

        double dLat = rua->latitudeMedia - latOrigem;
        double dLong = rua->longitudeMedia - longOrigem;
        double distancia = sqrt((dLat * dLat) + (dLong * dLong));

        ResultadoOrdenado* novoResultado = new ResultadoOrdenado;
        novoResultado->logradouro = rua;
        novoResultado->distancia = distancia;
        novoResultado->proximo = nullptr;

        // intersecao ordenada
        if (resultadoFinal == nullptr || distancia < resultadoFinal->distancia) {
            novoResultado->proximo = resultadoFinal;
            resultadoFinal = novoResultado;
        } else {
            ResultadoOrdenado* aux = resultadoFinal;
            // Mantewm estabilidade para distâncias iguais usando <=
            while (aux->proximo != nullptr && aux->proximo->distancia <= distancia) {
                aux = aux->proximo;
            }
            novoResultado->proximo = aux->proximo;
            aux->proximo = novoResultado;
        }

        atual = atual->proximo;
    }
    
    // Armazena o total encontrado no primeiro no
    if (this->resultadoFinal != nullptr) {
        this->resultadoFinal->num_logradouros = totalEncontrados;
    }
}
        
//imprime a saida no formato exigido
void Consulta::imprimirResultados(int max_resultado){
    if (resultadoFinal == nullptr) {
        cout << "0" << endl; //0 resultados encontrados
        return;
    }
    
    // Imprime o numero total ou o máximo solicitado
    if(resultadoFinal->num_logradouros < max_resultado)
        cout << resultadoFinal->num_logradouros << endl;
    else
        cout << max_resultado << endl;

    ResultadoOrdenado* cursor = resultadoFinal;

    for(int i = 0; i < max_resultado && cursor != nullptr; i++){
        cout << cursor->logradouro->idLogradouro << ";" << cursor->logradouro->nomeLogradouro << endl;
        cursor = cursor->proximo;
    }
}