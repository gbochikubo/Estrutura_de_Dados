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
    this->heap = new Data[capacidade];
    int j = n-1;
    for(int i = (n*2)-2; i >= n-1; i--){
        heap[i] = vet[j];
        j--;
        tamanho++;
        
    }
    for(int  i = (((n*2)-2)-n); i >= 0; i--){
        int esq = ((2*i)+1);
        int dir = (2*i)+2;
        int maior;
        if(heap[dir] > heap[esq]){
            maior = heap[dir];
        }
        else {
            maior = heap[esq];
        }
        heap[i] = maior;
        tamanho++;
    }
}

Torneio :: ~Torneio(){
    delete [] heap;
}
void Torneio :: imprime(){
    for(int i=0; i < tamanho; i++){
        cout << heap[i] << " ";
    }
    cout << endl;
}

void Torneio :: removeMaior(int n){
    Data maior = heap[0];
    Data vet[n];
    for(int i = n-1; i >=0; i--){
        vet[i] = 
}


int main (){
    
    int tam = 6;
    
    Data vet[] = {1,2,3,4,50,70};
    
    Torneio *h = new Torneio(vet,tam);
    h->removeMaior(tam);
    //h->imprime();
    
    delete h;
    
    return 0;
}
    
    
    


