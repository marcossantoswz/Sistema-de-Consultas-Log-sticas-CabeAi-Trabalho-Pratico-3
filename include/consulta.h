#ifndef CONSULTA_H
#define CONSULTA_H

#include "palavra.h"
#include "logradouro.h"
#include <string>

using namespace std;

struct ResultadoOrdenado {
    ListLogradouros* logradouro;
    double distancia;
    int num_logradouros;
    ResultadoOrdenado* proximo;
};

class Consulta {

    private:
        ListaInvertida* candidatosAtuais; //lista de candidatos filtrados
        ResultadoOrdenado* resultadoFinal;

    public:
        Consulta();
        ~Consulta();

        //recebe a lista invertida da primeira palavra digitada
        void iniciarBusca(ListaInvertida* listaPrimeiraPalavra);
        
        //eealiza a interseção (AND) com os resultados de uma nova palavra
        void intersectar(ListaInvertida* listaNovaPalavra);
        
        // Calcula distâncias e ordena
        void processarResultados(double latOrigem, double longOrigem, int maxResultados);
        
        void imprimirResultados(int max_resultado);
};

#endif