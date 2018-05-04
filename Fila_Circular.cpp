#include <iostream>

using namespace std;

typedef int Dado;

class filav {
    private:
        int capacidade;
        Dado *dados;
        int tamanho;
        int posInicio;
        int posFim;
    
    public:
        filav(int cap = 100);
        ~filav();
        void enfileira(Dado valor);
        Dado desenfileira();
        Dado espia();
        void depura();
        void info();
};

filav :: filav (int cap){
    this->capacidade = cap;
    this->dados = new Dado [capacidade];
    this->posInicio = -1;
    this->posFim = -1;
    this->tamanho = 0;
}

filav :: ~filav(){
    delete[] dados;
}

void filav :: info(){
    cout << "TAMANHO : " << tamanho << endl;
    cout << "CAPACIDADE : " <<capacidade << endl;
    cout << "POS-INICIO : " << posInicio << endl;
    cout << "POS-FIM " << posFim << endl;
}

Dado filav :: espia(){
    return dados[posInicio];
}

Dado filav :: desenfileira(){
    if (tamanho == 0){ // tentou desenfileirar de fila vazia
        cerr << "Erro : fila vazia" << endl;
    }
    Dado aux = dados [posInicio];
    
    // checo se não estou removendo o último elemento
    if(posInicio == posFim){
        posFim = -1;
        posInicio = -1;
    }
    else {
        posInicio = (posInicio+1)%capacidade;
    }
    tamanho--;
    return aux;
}

void filav :: enfileira (int valor){
    if(((posFim + capacidade - posInicio)%capacidade) == capacidade-1){
        // Tá cheio !! 
        // (tamanho == capacidade)
        cerr << "Erro: fila cheia" << endl;
    }
    if(posInicio == -1){ // fila vazia
        posInicio++;
    }
    posFim = (posFim + 1) % capacidade;
    dados[posFim] = valor;
    tamanho++;
}

void filav :: depura(){
    //implementação apenas para depuração
    for(int i = 0 ; i < capacidade; i++){
        cout << dados[i] << " ";
    }
    cout << endl;
}

int main(){
    filav fila (9);
    //~ Dado vetor[5];
    //~ for(int i = 0 ; i < 5; i++){
        //~ vetor[i] = i;
        //~ fila.enfileira(vetor[i]);
    //~ }
    fila.enfileira(100);
    fila.enfileira(200);
    fila.enfileira(300);
    fila.enfileira(400);
    fila.enfileira(500);
    
    cout <<fila.espia();
   fila.info();
    
    
    return 0;
}
    

        
