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
        int pai(int i);
        int esquerdo(int i);
        int direito(int i);
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
    this->heap = new Data[cap];
}

//~ MinHeap :: MinHeap(Data vet[], int tam, int cap){
    //~ if(cap == 0){
        //~ cap = tam;
    //~ }
    //~ else{
        //~ this->capacidade = cap;
    //~ }
    //~ this->heap = new Data[capacidade];
    //~ for(int i = 0; i < tam; i++){
        //~ heap[i] = vet[i];
        //~ tamanho++;
    //~ }
    //~ this->tamanho = tam;
  //~ //  cout << "FOI" << endl;
    //~ arruma();
//~ }
MinHeap :: MinHeap(Data vet[], int tam, int cap){
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
    cout <<"VAI ARRUMAR" << endl;
    arruma();
}
MinHeap :: ~MinHeap(){
    delete [] heap;
}
int MinHeap :: pai(int i){
    return (i-1)/2;
}

int MinHeap :: esquerdo(int i){
    return (2*1)+1;
}

int MinHeap :: direito(int i){
    return (2*i)+2;
}

//~ void MinHeap :: corrigeDescendo(int i){
    
    //~ int esq = esquerdo(i);
    //~ int dir = direito(i);
    //~ int menor = i;
    //~ cout << "VAI CORRIGIR : " << i << endl;
    //~ if((esq < tamanho) and (heap[esq] < heap[i])){
        //~ menor = esq;
    //~ }
    //~ if((dir < tamanho) and (heap[dir] < heap[menor])){
        //~ menor = dir;
    //~ }
    //~ if(menor != i){
        //~ swap(heap[menor],heap[i]);
        //~ corrigeDescendo(i);
    //~ }
//~ }
void MinHeap :: corrigeDescendo(int i){
    int esq = esquerdo(i);
    int dir = direito(i);
    int maior;
    cout << "VAI CORRIGIR : " << i << endl;
    if((esq < tamanho) and (heap[esq] < heap[i])){
        maior = esq;
    }
    else {
        maior = i;
    }
    if((dir < tamanho) and (heap[dir] < heap[maior])){
        maior = dir;
    }
    if(maior != i){
        swap(heap[maior],heap[i]);
        corrigeDescendo(maior);
    }
}


void MinHeap :: corrigeSubindo(int i){
    int p = pai(i);
    
    if(heap[i] < heap[p]){
        swap(heap[i],heap[p]);
        corrigeSubindo(p);
    }
}

//~ void MinHeap :: arruma(){
    //~ for(int i = (tamanho/2)-1; i >= 0; i--){
        //~ corrigeDescendo(i);
    //~ }
//~ }
void MinHeap :: arruma (){          // corrige descendo a partir do ultimo nó com filhos
    for(int i=(tamanho/2)-1; i >= 0; i--){
        corrigeDescendo(i);
    }
}

Data MinHeap :: espiaRaiz(){
    return heap[0];
}

Data MinHeap :: retiraRaiz(){
    Data aux = heap[0];
    swap(heap[0],heap[tamanho-1]);
    tamanho--;
    corrigeDescendo(0);
    return aux;
}

void MinHeap :: insere(Data d){
    if(tamanho == capacidade){
        cerr << "ERRO" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        heap[tamanho] = d;
        corrigeSubindo(tamanho);
        tamanho++;
    }
}

void MinHeap :: imprime(){
    for(int i = 0; i < tamanho; i++){
        cout << heap[i] << " ";
    }
    cout << endl;
}

    
    
    
     
int main (){
    
    
    int tam = 13;
    
    Data vet[] = {50,2,90,20,230,43,8,34,66,100,110,3,13};
    
    MinHeap *h = new MinHeap(vet,tam);
    cout << "CRIOU" << endl;
    //cout << h->espiaRaiz();
    h->imprime();
    
    //~ for(int i=0; i < tam; i++){
        //~ //cout << "Raiz : ";
        //~ cout << h->retiraRaiz() << "  ";
    //~ }
    //~ cout << endl;
    
    //~ h->imprime();
    
    //~ for(int i=0; i < tam; i++){
        //~ h->insere(vet[i]);
    //~ }
    //~ h->imprime();
    
    //~ delete h;
    return 0;
}
