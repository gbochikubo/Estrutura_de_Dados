#include <iostream>

using namespace std;

typedef int Dado;

class noh{
    friend class deque;
    private :
        Dado _dado;
        noh* proximo;
    public:
        noh(Dado d);
};

noh :: noh(Dado d){
    this-> _dado = d;
    this->proximo = NULL;
}

class deque{
    private:
        noh* esquerda;
        noh* direita;
        int tamanho;
    public:
        deque();
        ~deque();
        void insereNaEsquerda(Dado d);
        void insereNaDireita(Dado d);
        Dado retiraEsquerda();
        Dado retiraDireita();
        Dado espiaEsquerda();
        Dado espiaDireita();
        void imprime();
        inline bool vazia();
};

deque ::deque (){
    this->esquerda = NULL;
    this->direita = NULL;
    this->tamanho = 0;
}

deque :: ~deque () {
    while(esquerda != NULL){
        noh* aux = esquerda;
        esquerda = esquerda->proximo;
        delete aux;
    }
}

inline bool deque :: vazia(){
    return(direita == NULL);
}
void deque ::insereNaDireita(Dado d){
    noh* novo = new noh(d);
    if(vazia()){
        direita = novo;
        esquerda = novo;
    }
    else {
        direita->proximo = novo;
        direita = novo;
    }
    tamanho ++;
}

void deque :: insereNaEsquerda(Dado d){
    noh* novo = new noh(d);
    if(vazia()){
        direita = novo;
        esquerda = novo;
    }
    else {
        novo -> proximo = esquerda;
        esquerda = novo;
    }
    tamanho++;
}

Dado deque :: retiraDireita(){
    noh* temp = esquerda;
    while(temp->proximo != direita){
        temp = temp->proximo;
    }
    noh* remove = direita;
    Dado removido = remove->_dado;
    temp->proximo = NULL;
    delete remove;
    direita = temp;
    tamanho--;
    return removido;
}

Dado deque :: retiraEsquerda(){
    noh* temp = esquerda;
    noh* aux = esquerda->proximo;
    Dado removido = temp->_dado;
    esquerda = aux;
    delete temp;
    tamanho--;
    return removido;
}
void deque :: imprime(){
    noh* aux = esquerda;
    while(aux != NULL){
        cout << aux->_dado << " ";
        aux = aux->proximo;
    }
    cout << endl;
}

Dado deque :: espiaDireita(){
    return direita->_dado;
}

Dado deque :: espiaEsquerda(){
    return esquerda->_dado;
}
        
        



int main () {
    
    deque lista;
    
    lista.insereNaDireita(100);
    lista.insereNaDireita(200);
    lista.insereNaDireita(300);
    lista.insereNaDireita(400);
    lista.insereNaDireita(500);
    
    lista.imprime();
    
    //~ lista.insereNaEsquerda(99);
    //~ lista.retiraDireita();
    //~ lista.retiraDireita();
    //~ lista.retiraEsquerda();
    //lista.imprime();
    cout << lista.espiaDireita() << endl;
    cout << lista.espiaEsquerda() << endl;
    
    return 0;
}
    
    
