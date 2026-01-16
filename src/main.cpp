#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "../include/endereco.h"
#include "../include/palavra.h"
#include "../include/consulta.h"
#include "../include/logradouro.h"

using namespace std;

int main(int argc, char *argv[]){

    if(argc < 2){
        cout << "Erro: informe o arquivo de entrada." << endl;
        return 1;
    }

    ifstream arquivo(argv[1]);
    if(!arquivo.is_open()){
        cout << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    Endereco enderecos;
    int num_enderecos;
    
    arquivo >> num_enderecos;
    string lixo;
    getline(arquivo, lixo); // Limpa o \n após o inteiro
    
    string idEnd, idLogStr, tipoLog, nomeLog, numStr, bairro, regiao, cep, latStr, longStr;

    for(int i=0; i < num_enderecos; i++){
        getline(arquivo, idEnd, ';');
        getline(arquivo, idLogStr, ';');
        getline(arquivo, tipoLog, ';');
        getline(arquivo, nomeLog, ';');
        getline(arquivo, numStr, ';');
        getline(arquivo, bairro, ';');
        getline(arquivo, regiao, ';');
        getline(arquivo, cep, ';');
        getline(arquivo, latStr, ';');
        getline(arquivo, longStr); 
        
        if(!idEnd.empty()) { 
            try {
                enderecos.adicionarEndereco(
                    idEnd, stoi(idLogStr), tipoLog, nomeLog, stoi(numStr), 
                    bairro, regiao, cep, stod(latStr), stod(longStr)
                );
            } catch (...) {}
        }
    }

    //GERAÇÃO DOS TADs
    Logradouro* logradouros = enderecos.gerarLogradourosUnicos();
    Dicionario* palavras = new Dicionario(); 

    ListLogradouros* atual = logradouros->getPrimeiro();

    while(atual != nullptr) {
        stringstream ss(atual->nomeLogradouro); 
        string palavra;
        
        while(ss >> palavra){
            palavras->insere(palavra, atual); 
        }
        atual = atual->proximo;
    }

    //LEITURA DAS CONSULTAS ->
    int num_consultas, num_resultados;
    string id_consulta;
    
    arquivo >> num_consultas >> num_resultados;
    getline(arquivo, lixo);
    
    string logradouro_consulta;
    string lat_consulta, long_consulta;

    for(int i=0; i < num_consultas; i++){
        Consulta* novaConsulta = new Consulta(); 
        
        getline(arquivo, id_consulta, ';');
        getline(arquivo, logradouro_consulta, ';');
        getline(arquivo, lat_consulta, ';');
        getline(arquivo, long_consulta); 

        stringstream ss(logradouro_consulta);
        string palavra;
        bool primeiraPalavra = true;

        while(ss >> palavra){
            ListaInvertida* resultadoBusca = palavras->buscar(palavra);

            if (primeiraPalavra) {
                novaConsulta->iniciarBusca(resultadoBusca);
                primeiraPalavra = false;
            } else {
                novaConsulta->intersectar(resultadoBusca);
            }
        }

        double latOrigem = stod(lat_consulta);
        double longOrigem = stod(long_consulta);
        
        cout << id_consulta << ";"; 
        
        //Calcula tudo
        novaConsulta->processarResultados(latOrigem, longOrigem, num_resultados);
        
        //Imprime "NumRespostas" (quebra linha) e depois os logradouros
        novaConsulta->imprimirResultados(num_resultados);

        delete novaConsulta; 
    }

    delete palavras; 
    delete logradouros;

    return 0;
}