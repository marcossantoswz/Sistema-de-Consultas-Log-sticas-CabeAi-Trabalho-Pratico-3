#ifndef LOGRADOURO_H
#define LOGRADOURO_H

#include <string>

using namespace std;

// Representa um nó da lista encadeada de logradouros
struct ListLogradouros {
    int idLogradouro;
    string tipoLogradouro;
    string nomeLogradouro;
    string bairro;
    string regiao;
    string cep;
    double latitudeMedia;
    double longitudeMedia;
    ListLogradouros *proximo;
};

class Logradouro {
    private:
        ListLogradouros *logradouros_primeiro;
        ListLogradouros *logradouros_ultimo;
        int num_logradouros;

    public:
        Logradouro();
        ~Logradouro();
        
        void insere(int id, string tipo, string cep, string bairro, string regiao, string nome, double latMedia, double longMedia);
        
        void imprime();
        
        // Retorna o ponteiro para o início da lista (usado para iterar externamente se necessário)
        ListLogradouros* getPrimeiro();
        int getNumLogradouros();
};

#endif