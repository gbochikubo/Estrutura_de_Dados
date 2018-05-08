#include <iostream>

using namespace std;

typedef char Dado;

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
        void iguais(pilha& umaPilha,pilha& outraPilha);
        int calcula();
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
            Dado x = umaPilha.desempilha();
            outraPilha.empilha(x);
            cont++;
        }
        Dado mid = umaPilha.desempilha();
        if(mid != 'C'){
            simetrico = false;
        }
        while(topo != NULL){
            Dado p1 = umaPilha.desempilha();
            Dado p2 = outraPilha.desempilha();
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
            Dado x = umaPilha.desempilha();
            outraPilha.empilha(x);
            cont++;
        }
        while(topo != NULL){
            Dado p1 = umaPilha.desempilha();
            Dado p2 = outraPilha.desempilha();
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
            Dado x = umaPilha.desempilha();
            outraPilha.empilha(x);
            cont++;
        }
        while(topo != NULL){
            Dado p1 = umaPilha.desempilha();
            Dado p2 = outraPilha.desempilha();
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
            Dado x = umaPilha.desempilha();
            outraPilha.empilha(x);
            cont++;
        }
        Dado mid = umaPilha.desempilha();
        if(mid != 'C'){
            simetrico = false;
        }
        while(topo != NULL){
            Dado p1 = umaPilha.desempilha();
            Dado p2 = outraPilha.desempilha();
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

void pilha :: iguais(pilha& umaPilha,pilha& outraPilha){
    bool igual = true;

    while(outraPilha.topo != NULL and umaPilha.topo != NULL){
      
        Dado x = desempilha();
        Dado y = outraPilha.desempilha();
       
        if(x != y){
            igual = false;
        }
    }
    if(igual){
        cout << "TRUE" << endl;
    }
    else{
        cout << "FALSE" << endl;
    }
}


int pilha :: calcula(){
    Dado temp;
    char n=0;
    pilha aux;
    int resultado = 0 ;
    while(not vazia()){
        //cout << "ENTROU" << endl;
        temp = desempilha();
        int x = temp;
        //~ cout << x << endl;
        if(x >= 48 and x <=57){
            //~ cout << "ENTROU" << endl;
            aux.empilha(temp);
            //~ cout << "empilhou" << endl;
        }
        else{
            while(not aux.vazia()){
                //~ cout << "ENTROU" << endl;
                n = aux.desempilha();
                    if(temp == '+'){
                        cout << "ENTROU SOMA" << endl;
                        cout << "SOMANDO " << resultado << " com " << (n-48) << endl;
                        resultado = resultado + (n-48);
                }
                else if(temp == '*'){
                    cout << "ENTROU MULTIPLICA" << endl;
                    if(resultado == 0){
                        resultado = n-48;
                    }
                    cout << "MULTIPLICANDO  " << resultado << " com " << (n-48) << endl; 
                    resultado = resultado * (n-48);
                }
           }
       }
       
   }
   return resultado;
} 
            



int main (){
    
    
    pilha p;
    
    p.empilha('+');
    p.empilha('5');
    p.empilha('*');
    p.empilha('3');
    p.empilha('5');
    //~ p.empilha('+');
    //~ p.empilha('5');
    //~ p.empilha('*');
    //~ p.empilha('5');
    cout << p.calcula() << endl;
 
    
    return 0;
}
    
