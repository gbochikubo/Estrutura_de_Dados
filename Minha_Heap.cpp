#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Data;

class MaxHeap{
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
        MaxHeap(int cap);
        MaxHeap(Data vet[], int tam, int cap=0);
        ~MaxHeap();
        void imprime();
        Data espiaRaiz();
        Data retiraRaiz();
        void insere(Data d);
        void heapSort();
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
    this->heap = new Data[capacidade];
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

void MaxHeap :: arruma (){          // corrige descendo a partir do ultimo nó com filhos
    for(int i=(tamanho/2)-1; i >= 0; i--){
        corrigeDescendo(i);
    }
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
    
void MaxHeap :: corrigeSubindo(int i){
    int p = pai(i);
    
    if(heap[i] > heap[p]){
        swap(heap[i],heap[p]);
        corrigeSubindo(p);
    }
}

Data MaxHeap :: espiaRaiz(){
    return heap[0];
}

Data MaxHeap :: retiraRaiz(){
    if(tamanho == 0){
        cerr << "ERRO" << endl;
        exit(EXIT_FAILURE);
    }
    Data aux = heap[0];
    swap(heap[0],heap[tamanho-1]);
    tamanho--;
    corrigeDescendo(0);
    return aux;
}

void MaxHeap :: imprime(){
    for(int i=0; i < tamanho; i++){
        cout << heap[i] << " ";
    }
    cout << endl;
}

void MaxHeap :: insere(Data d){
    if(tamanho == capacidade){
        cerr << "HEAP CHEIA" << endl;
        exit(EXIT_FAILURE);
    }
    heap[tamanho] = d;
    corrigeSubindo(tamanho);
    tamanho++;
}

void MaxHeap :: heapSort(){
    int quantidade = tamanho;
    //cout << tamanho << endl;
    while(tamanho > 1){
    //    cout << "TROCANDO : " << heap[0] << " com " << heap[tamanho-1] << endl;
        swap(heap[0],heap[tamanho-1]);
        tamanho--;
        corrigeDescendo(0);
    }
    tamanho = quantidade;
}

void MaxHeap :: torneio(int n);
    
    

int main (){
    
    int tam = 13;
    
    Data vet[] = {50,2,90,20,230,43,8,34,66,100,110,3,13};
    
    MaxHeap *h = new MaxHeap(vet,tam);
    
    h->heapSort();
    h->imprime();
    
    delete h;
    
    return 0;
}

