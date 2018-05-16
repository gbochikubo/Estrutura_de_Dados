#include <iostream>

using namespace std;

class noh{
    friend class fila;
    private:
        int _dado;
        noh* proximo;
    public:
        noh(int d);
};

noh :: noh(int d){
    this->_dado = d;
    this->proximo = NULL;
}

class fila{
    private:
        noh* primeiro;
        noh* ultimo;
        int tamanho;
    public:
        fila();
        ~fila();
        void enqueue(int d);
        void insere(int d);
        void enfilera(int d);
        int dequeue ();
        int retira();
        int desenfilera();
        int espia();
        bool vazia();
        void limpaFila();
        void inverte();
        void empilha(int d);
        int desempilha();
};


fila :: fila(){
    this->tamanho = 0;
    this->primeiro = NULL;
    this->ultimo = NULL;
}

fila :: ~fila(){
    while (primeiro!=NULL){
        desenfilera();
    }
}

void fila :: enfilera(int d){
    noh* temp = new noh(d);
    if(ultimo!=NULL){
    ultimo->proximo=temp;
    }
    ultimo = temp;
    if(vazia()){
        primeiro=temp;
    }
    tamanho++;
}

int fila:: desenfilera(){
    int removido;
    noh* temp;
    removido = primeiro->_dado;
    temp = primeiro;
    primeiro = primeiro->proximo;
    if(vazia()){
        ultimo = NULL;
    }
    delete temp;
    tamanho--;
    return removido;
}

int fila :: espia(){
    return primeiro->_dado;
}

void fila :: limpaFila(){
    while(primeiro != NULL){
        cout << desenfilera() << endl;
    }
}

bool fila :: vazia(){
    return (primeiro == NULL);
}

void fila :: inverte(){
    int x;
    if(primeiro != NULL){
        x = desenfilera();
        cout << "DESENFILEIROU " << x << endl;
        inverte();
        enfilera(x);
    }
    //enfilera(x);
}

int fila :: desempilha(){
   
    if(not vazia()) {
        fila aux;
        int x;
        int tam = tamanho;
        for(int i = 0; i < tam-1; i++){
            x = desenfilera();
            aux.enfilera(x);
        }
        int topo = desenfilera();
        tam = aux.tamanho;
        for(int i = 0; i < tam; i++){
            x = aux.desenfilera();
            enfilera(x);
        }
    return topo;
    }
    else {
        return -1;
    }
}

void fila :: empilha(int d){
    enfilera(d);
}




int main () {
    fila f1;
    
    f1.empilha(100);
    f1.empilha(200);
    f1.empilha(300);
    f1.empilha(400);
    f1.empilha(500);
    
    
   // f1.inverte();
    
   // f1.limpaFila();
    
    f1.empilha(1000);
    //f1.limpaFila();
    
    cout << f1.desempilha() << endl;
    cout << f1.desempilha() << endl;
    cout << f1.desempilha() << endl;
    cout << f1.desempilha() << endl;
    
    
    return 0;
}

    


