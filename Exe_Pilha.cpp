#include <iostream>

using namespace std;

typedef string Dado;

class noh{
    friend class pilha;
    private:
        Dado _dado;
        noh* proximo;
    public:
        noh(Dado dado);
};

noh :: noh(Dado dado){
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
        void push(Dado d);
        void empilha(Dado d);
        Dado pop();
        Dado desempilha();
        Dado espia(); 
        bool vazia();
        void limpaPilha();
        void xCy(pilha& umaPilha);
        void reconhecedor(pilha& umaPilha);
        void reconhece(pilha& umaPilha);
        int tam();
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

void pilha :: empilha(Dado d){
    noh* temp = new noh(d);
    temp->proximo = topo;
    topo = temp;
    tamanho ++;
}

Dado pilha :: desempilha(){
    Dado removido;
    noh* temp;
    removido = topo->_dado;
    temp = topo;
    topo = topo->proximo;
    delete temp;
    return removido;
}

Dado pilha :: espia (){
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

void pilha :: xCy(pilha& umaPilha){
    
    bool simetrico = true;
    //cout << tamanho << endl;
    if(tamanho%2 != 0){
        int cont = 0;
        int meio = (tamanho)/2;
        pilha outraPilha;
        while(cont < meio){
            string x = umaPilha.desempilha();
            outraPilha.empilha(x);
            cont++;
        }
        string mid = umaPilha.desempilha();
        if(mid != "C"){
            simetrico = false;
        }
        while(topo != NULL){
            string p1 = umaPilha.desempilha();
            string p2 = outraPilha.desempilha();
            if(p1 != p2){
                simetrico = false;
            }
        } 
    }
    else{
        simetrico = true;
    }
    if(simetrico){
        cout << "VERDADEIRO" << endl;
    }
    else {
        cout << "FALSO" << endl;
    }
}

int pilha :: tam(){
    return tamanho;
}

void pilha :: reconhecedor(pilha& umaPilha){
    
    bool simetrico = true;
    
    if(tamanho%2 == 0){
         int cont = 0;
         int meio = (tamanho)/2;
         pilha outraPilha;
        while(cont < meio){
            string x = umaPilha.desempilha();
            outraPilha.empilha(x);
            cont++;
        }
        while(topo != NULL){
            string p1 = umaPilha.desempilha();
            string p2 = outraPilha.desempilha();
            if(p1 != p2){
                simetrico = false;
            }
        }
    }
    else{
        simetrico = false;
    }
    if(simetrico) {
        cout << "TRUE" << endl;
    }
    else {
        cout << "FALSE" << endl;
        }
}

void pilha :: reconhece(pilha& umaPilha){
    bool simetrico = true;
    
    if( tamanho%2 == 0 ){
        int cont = 0;
         int meio = (tamanho)/2;
         pilha outraPilha;
        while(cont < meio){
            string x = umaPilha.desempilha();
            outraPilha.empilha(x);
            cont++;
        }
        while(topo != NULL){
            string p1 = umaPilha.desempilha();
            string p2 = outraPilha.desempilha();
            if(p1 != p2){
                simetrico = false;
            }
        }
    }
    else{
        int cont = 0;
        int meio = (tamanho)/2;
        pilha outraPilha;
        while(cont < meio){
            string x = umaPilha.desempilha();
            outraPilha.empilha(x);
            cont++;
        }
        string mid = umaPilha.desempilha();
        if(mid != "C"){
            simetrico = false;
        }
        while(topo != NULL){
            string p1 = umaPilha.desempilha();
            string p2 = outraPilha.desempilha();
            if(p1 != p2){
                simetrico = false;
            }
        }
    }
    if(simetrico){
        cout << "TRUE" << endl;
    }
    else{
        cout << "FALSE" << endl;
    }
} 
        
        



int main (){
    
    pilha p;
    p.empilha("X");
    p.empilha("A");
  //  p.empilha("C");
    p.empilha("C");
    p.empilha("A");
    //p.empilha("");
    p.empilha("X");
   
    p.reconhece(p);

    return 0;
}
    
