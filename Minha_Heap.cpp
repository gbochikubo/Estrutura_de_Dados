#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Data;

class MaxHeap{
    private:
        Data *heap;
        int tamanho;
        int capacidade
        inline int esquerdo(int i);
        inline int direito(int i);
        inline int pai(int i);
        void arruma();
        void corrigeDescendo(int i);
        void corrigeSubindo(int i);
    public:
        MaxHeap(int cap);
        MaxHeap(Data vet[], int tam, int cap=0);
        ~MaxHeap();
        void imprime();
        Data espiaRaiz();
        Data retiraRaiz();
        void insere(Data d);
};

MaxHeap :: MaxHeap(int cap){
    this->capacidade = cap;
    this->tamanho = 0;
    this->heap = new Data[cap];
}

MaxHeap :: MaxHeap(Data vet[], int tam, int cap){
    if(cap == 0){
        this->capacidade = tam;
    }
    else {
        this->capacidade = cap;
    }
    this->heap = new Data[cap];
    for(int i = 0 ;i < tam; i++){
        heap[i] = vet[i];
    }
    tamanho = tam;
    arruma();
}

MaxHeap :: ~MaxHeap(){
    delete [] heap;
}

int MaxHeap :: pai(int i){
    return (i-1)/2;
}

int MaxHeap :: esquerdo(int i){
   return (2*i)+1;
}

int MaxHeap :: direito(int i){
    return (2*i)+2;
}

void MaxHeap :: corrigeDescendo(int i){
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior;
    
    if((esq < tamanho) and (heap[esq] > heap[i])){
        maior = esq;
    }
    else {
        maior = i;
    }
    if((dir < tamanho) and (heap[dir] > heap[maior])){
        maior = dir;
    }
    if(maior != i){
        swap(heap[maior],heap[i]);
        corrigeDescendo(maior);
    }
}
    

