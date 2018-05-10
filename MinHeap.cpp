#include <iostream>
#include <cstdlib> 

using namespace std;

typedef int Data;

class MinHeap {
    private:
        Data *heap;
        int tamanho;
        int capacidade;
        void arruma();
        void corrigeDescendo(int i);
        void corrigeSubindo(int i);
        int Pai();
        int esquerdo();
        int direito();
    public:
        MinHeap(int cap);
        MinHeap(Data vet[], int tam, int cap=0);
        ~MinHeap();
        void imprime();
        Data retiraRaiz();
        Data espiaRaiz();
        void insere(Data d);
};

MinHeap :: MinHeap(int cap){
    this->capacidade = cap;
    this->tamanho = 0;
    this->heap = new Data[capacidade];
}

MinHeap :: MinHeap(Data vet, int tam, int cap){
    if(cap == 0){
        cap = tam;
    }
    this->heap = new Data[capacidade];
    for(int i = 0; i < tam; i++){
        heap[i] = vet[i];
        tamanho++;
    }
    this->tamanho = tam;
    arruma();
}

int MinHeap :: pai(int i){
    return (i-1)/2;
}

int MinHeap :: esquerdo(int i){
     
int main (){
