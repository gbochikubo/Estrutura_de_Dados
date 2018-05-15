#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Data;

class Torneio{
    private:
        Data *heap;
        int tamanho;
        int capacidade;
        inline int esquerdo(int i);
        inline int direito(int i);
        inline int pai(int i);
        void arruma();
        void corrigeDescendo(int i);
        void corrigeSubindo(int i);
    public:
        Torneio(int n);
        Torneio(Data vet[], int tam);
        ~Torneio();
        void imprime();
        Data espiaRaiz();
        Data retiraRaiz();
        void insere(Data d);
        void heapSort();
        void removeMaior(int n);
};

Torneio :: Torneio (int n){
    this->capacidade = (n*2)-1;
    this->tamanho = 0;
    this->heap = new Data[capacidade];
}

Torneio :: Torneio (Data vet[], int n){
    this->capacidade = (n*2)-1;
    int quantidade = n;
    this->heap = new Data[capacidade];
    int j = n-1;
     
    for(int i = capacidade-1; i > quantidade-2; i--){
        heap[i] = vet[j];
        j--;
        tamanho++;
    
    }
    for(int i = quantidade-2; i >=0; i--){

        int esq = (2*i)+1;
        int dir = (2*i)+2;
        Data maior;
        if(heap[esq] > heap[dir]){
            maior = heap[esq];
        }
        else {
            maior = heap[dir];
        }
        heap[i] = maior;
        tamanho ++;
        
    }
}
    
Torneio :: ~Torneio (){
    delete [] heap;
}

    
void Torneio :: imprime(){
    for(int i=0; i < tamanho; i++){
        cout << heap[i] << " ";
    }
    cout << endl;
}

void Torneio :: removeMaior (int n){
    int x = n;
    int vet[x];
    Data maior = heap[0];
    int j=x-1;
    for(int i =capacidade-1; i > x-2; i--){
        if(heap[i] == maior){
            heap[i] = -1;
        }
        vet[j] = heap[i];
        j--;
    }
    Torneio t(vet,x);
    for(int i = 0; i < capacidade-1; i++){
        heap[i] = t.heap[i];
    }
}

int main(){
    
    int tam = 8;
    
    Data vet[] = {1,12,3,40,99,10,17,0};
    
    Torneio *h = new Torneio(vet,tam);
    
    h->imprime();
    h->removeMaior(tam);
    h->imprime();
    h->removeMaior(tam);
    h->imprime();
  
    
    delete h;
    
    return 0;
}
    


