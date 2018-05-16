#include <iostream>

using namespace std;

class noh{
    friend class pilha;
    private:
        int _dado;
        noh* proximo;
    public:
        noh(int dado);
};

noh :: noh(int dado){
    this->_dado = dado;
    this->proximo = NULL;
}

class pilha {
    private:
        noh* topo;
        int tamanho;
    public:
        pilha();
        ~pilha();
        void push(int d);
        void empilha(int d);
        int pop();
        int desempilha();
        int espia(); 
        bool vazia();
        void limpaPilha();
        void calculadora();
};

pilha :: pilha(){
    this->topo = NULL;
    this->tamanho = 0;
}

pilha :: ~pilha(){
    while( topo != NULL ){
        desempilha();
    }
}

void pilha :: empilha(int d){
    noh* temp = new noh(d);
    temp->proximo = topo;
    topo = temp;
    tamanho ++;
}

int pilha :: desempilha(){
    int removido;
    noh* temp;
    removido = topo->_dado;
    temp = topo;
    topo = topo->proximo;
    delete temp;
    return removido;
}

int pilha :: espia (){
    return topo->_dado;
}

void pilha :: limpaPilha(){
    while(topo != NULL){
        cout << desempilha() << endl;
    }
}

bool pilha :: vazia(){
    return (topo == NULL);
}

    
    

int main (){
    
    pilha p;
    p.empilha(100);
    p.empilha(200);
    p.empilha(300);
    
    p.limpaPilha();
    
    return 0;
}
    
