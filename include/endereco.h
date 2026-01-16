#ifndef ENDERECO_H
#define ENDERECO_H

#include <string>
#include "logradouro.h"
using namespace std;

// Representa um endereço bruto lido do arquivo
struct ListEndereco {
    string idEndereco;
    int idLogradouro;
    string tipoLogradouro;
    string logradouro;
    int numero;
    string bairro;
    string regiao;
    string cep;
    double latitude;
    double longitude;
    ListEndereco* proximo;
};

class Endereco {
    private:
        ListEndereco* enderecos;
        ListEndereco* ultimo;
        ListLogradouros* logradouros;

    public:
        Endereco();
        ~Endereco();
        
        //processa a lista de endereços brutos e cria a lista de logradouros unicos
        Logradouro* gerarLogradourosUnicos();
        
        void calcularCoordMedia();
        
        //insere um nó de logradouro usado internamente ou por classes amigas
        void inserirLogradouroNoFinal(ListLogradouros *novo);

        void adicionarEndereco(string idEnd, int idLog, string tipo, string log, int num, string bairro, string reg, string cep, double lat, double lon);

        void ordenarPorID();

        ListEndereco* mergeSort(ListEndereco* cabeca);

        ListEndereco* mesclar(ListEndereco* a, ListEndereco* b);

        void dividir(ListEndereco* fonte, ListEndereco** frente, ListEndereco** tras);
};

#endif