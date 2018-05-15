#include <iostream>

using namespace std;

typedef int Dado;

class filav{
    private:
        int tamanho;
        Dado *dado;
        int posInicio;
        int posFim;
        int capacidade;
    public:
        filav(int cap = 100);
        ~filav();
        void enfileira(Dado valor);
        Dado desenfileira();
        Dado espia();
        void info();
        void depura();
        void filav();
        
};

filav :: filav(int cap){
    this->tamanho = 0;
    this->capacidade = cap;
    this->dado = new Dado [capacidade];
    this->posInicio = -1;
    this->posFim = -1;
}

filav :: ~filav(){
    delete[] dado;
}

void filav :: enfileira(Dado valor){
    if((tamanho == capacidade)){
        cerr << "Erro : fila cheia " << endl;
    }
    if(posInicio==-1){
        posInicio++;
    }
    posFim = (posFim+1)%capacidade;
    dado[posFim] = valor;
    tamanho++;
}

Dado filav :: desenfileira(){
    if(tamanho == 0){
        cerr << "Erro : fila vazia " << endl;
    }
    Dado aux = dado[posInicio];
    if(posInicio == posFim){
        posInicio = -1;
        posFim = -1;
    }
    else{
        posInicio = (posInicio+1)%capacidade;
    }
    tamanho--;
    return aux;
}

Dado filav :: espia(){
    return dado[posInicio];
}

void filav :: info(){
    cout << "TAMANHO : " << tamanho << endl;
    cout << "CAPACIDADE : " << capacidade << endl;
    cout << "POS-INICIO : " << posInicio << endl;
    cout << "POS-FIM : " << posFim << endl;
}

void filav :: depura(){
    for(int i = 0; i < capacidade; i++){
        cout << dado[i] << " ";
    }
    cout << endl;
}

void filav :: inverte (){
    filav outrafila(capacidade);
    int cont =0;
    Dado x;
    while(cont < tamanho){
       x = desenfileira();
       outrafila.




int main(){
    
    filav fila(10);
    
    fila.enfileira(100);
    fila.enfileira(200);
    fila.enfileira(300);
    fila.enfileira(400);
    fila.enfileira(500);
    fila.enfileira(600);
    
    cout << fila.desenfileira() << endl;
    
    fila.info();
    
    fila.depura();
    
    return 0;
}
