#include "../include/endereco.h"
#include "../include/logradouro.h"

Endereco::Endereco(){
    enderecos = nullptr;
    ultimo = nullptr;
    logradouros = nullptr;
}

Endereco::~Endereco(){

    ListEndereco* atual = enderecos;
    while(atual != nullptr){
        ListEndereco* prox = atual->proximo;
        delete atual;
        atual = prox;
    }
    enderecos = nullptr;
    ultimo = nullptr;

}

Logradouro* Endereco::gerarLogradourosUnicos() {
    
    // Cria o TAD que vai guardar o resultado
    Logradouro* tadLogradouro = new Logradouro();

    if (enderecos == nullptr) return tadLogradouro;

    ListEndereco *atual = enderecos;
    
    //Variaveis para acumular a media das coordenadas
    double somaLat = 0;
    double somaLong = 0;
    int contador = 0;
    
    //guarda dados do grupo atual (primeira iteração)
    int idAtual = atual->idLogradouro;
    string nomeAtual = atual->logradouro;
    string tipoAtual = atual->tipoLogradouro;
    string cepAtual = atual->cep;
    string bairroAtual = atual->bairro;
    string regiaoAtual = atual->regiao;
    
    while (atual != nullptr) {
        //Se mudou o ID significa que acabamos de ler todos os endereços da rua anterior isso pq as ruas foram ordenadas por id
        if (atual->idLogradouro != idAtual) {
            
            // Calcula a media da rua que fechou
            if (contador > 0) {
                double latMedia = somaLat / contador;
                double longMedia = somaLong / contador;
                
                //insere no TAD Logradouro
                tadLogradouro->insere(idAtual, tipoAtual, cepAtual, bairroAtual, regiaoAtual, nomeAtual, latMedia, longMedia);
            }
            
            //reseta as variáveis para a nova rua
            idAtual = atual->idLogradouro;
            nomeAtual = atual->logradouro;
            tipoAtual = atual->tipoLogradouro;
            cepAtual = atual->cep;
            bairroAtual = atual->bairro;
            regiaoAtual = atual->regiao;
            somaLat = 0;
            somaLong = 0;
            contador = 0;
        }
        
        //acumula os dados da linha atual
        somaLat += atual->latitude;
        somaLong += atual->longitude;
        contador++;
        
        atual = atual->proximo;
    }

    //inserindo a ultima rua manualmente o loop acaba antes de processá-la
    if (contador > 0) {
        double latMedia = somaLat / contador;
        double longMedia = somaLong / contador;
        tadLogradouro->insere(idAtual, tipoAtual, cepAtual, bairroAtual, regiaoAtual, nomeAtual, latMedia, longMedia);
    }

    return tadLogradouro;
}

void Endereco::inserirLogradouroNoFinal(ListLogradouros *novo) {
    if (logradouros == nullptr) {
        // lista vazia
        logradouros = novo;
        novo->proximo = nullptr;
        return;
    }

    ListLogradouros *atual = logradouros;

    // andar ate o último
    while (atual->proximo != nullptr) {
        atual = atual->proximo;
        //ultimo = novo; // O novo vira o ultimo
    }

    atual->proximo = novo;
    novo->proximo = nullptr;
}

void Endereco::calcularCoordMedia(){
    
}

void Endereco::adicionarEndereco(string idEnd, int idLog, string tipo, string log, int num, string bairro, string reg, string cep, double lat, double lon){
    ListEndereco* novo = new ListEndereco;
    novo->idEndereco = idEnd;
    novo->idLogradouro = idLog;
    novo->tipoLogradouro = tipo;
    novo->logradouro = log;
    novo->numero = num;
    novo->bairro = bairro;
    novo->regiao = reg;
    novo->cep = cep;
    novo->latitude = lat;
    novo->longitude = lon;
    novo->proximo = nullptr;

    
    if (enderecos == nullptr) {
        enderecos = novo;
        ultimo = novo;
    } else {
        ultimo->proximo = novo; // O antigo último aponta para o novo
        ultimo = novo; // O novo vira o ultimo
    }
}

void Endereco::ordenarPorID() {
    if (enderecos == nullptr || enderecos->proximo == nullptr) {
        return; 
    }

    enderecos = mergeSort(enderecos);

    // Atualiza o ponteiro 'ultimo' após a reordenação
    ListEndereco* temp = enderecos;
    while (temp->proximo != nullptr) {
        temp = temp->proximo;
    }
    ultimo = temp;
}

ListEndereco* Endereco::mergeSort(ListEndereco* cabeca) {
    if (cabeca == nullptr || cabeca->proximo == nullptr) {
        return cabeca;
    }

    ListEndereco* a;
    ListEndereco* b;

    dividir(cabeca, &a, &b);

    a = mergeSort(a);
    b = mergeSort(b);

    return mesclar(a, b);
}

ListEndereco* Endereco::mesclar(ListEndereco* a, ListEndereco* b) {
    ListEndereco* resultado = nullptr;

    if (a == nullptr) return b;
    if (b == nullptr) return a;

    //comparamos pelo ID
    if (a->idLogradouro <= b->idLogradouro) {
        resultado = a;
        resultado->proximo = mesclar(a->proximo, b);
    } else {
        resultado = b;
        resultado->proximo = mesclar(a, b->proximo);
    }
    return resultado;
}

void Endereco::dividir(ListEndereco* fonte, ListEndereco** frente, ListEndereco** tras) {
    ListEndereco* rapido;
    ListEndereco* lento;

    lento = fonte;
    rapido = fonte->proximo;

    while (rapido != nullptr) {
        rapido = rapido->proximo;
        if (rapido != nullptr) {
            lento = lento->proximo;
            rapido = rapido->proximo;
        }
    }

    *frente = fonte;
    *tras = lento->proximo;
    lento->proximo = nullptr;
}