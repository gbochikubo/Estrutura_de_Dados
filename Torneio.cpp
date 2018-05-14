#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Data;
Torneio
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
        Torneio(Data vet[], int tam, int cap=0);
        ~Torneio();
        void imprime();
        Data espiaRaiz();
        Data retiraRaiz();
        void insere(Data d);
        void heapSort();
};

Torneio :: Torneio (int n){
    this->capacidade = (n*2)-1;
    this->tamanho = 0;
    this->heap = new Data[capacidade];
}

Torneio :: Torneio (Data vet[], int n){
    this->capacidade = (n*2)-1;
    


