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
    
    bool simetrico;
  
    int inicio = 0;
    int fim = tamanho-1;
    int meio = (inicio + fim)/2;
  //  cout << meio << endl;
    if(tamanho%2 != 0){
        Dado vetor1[meio]; 
        Dado vetor2[meio];
        Dado mid;
        for(int i=0; i < meio; i++){
          
            vetor1[i] = desempilha();
    
        }
        mid = desempilha();
    //    cout << "MID :" << mid << endl;
        for(int i = 0; i < meio; i++){
  
           vetor2[i] = desempilha();
    
        }
    
        int j = meio-1;
        int cont = 0;
        for(int i = 0 ; i < meio; i ++){
        //    cout << "VETOR 1 : " << vetor1[i] << " / " << "VETOR 2 : " << vetor2[j] << endl;
            if(vetor1[i] == vetor2[j]){
                cont ++;
            }
            j--;
        }
        if((cont == meio)and(mid=="C")){
            simetrico = true;
        }
        else {
            simetrico = false;
        }
    
    }
    else {
        simetrico = false;
    }
    if ( simetrico == true ) {
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
    bool simetrica;
    
    if(tamanho%4 == 2){
        Dado vetorA1[tamanho/4];
        Dado vetorA2[tamanho/4];
        Dado vetorC[(tamanho/4)*2];
        Dado B1;
        Dado B2;
        for(int i = 0; i < tamanho/4; i++){
            vetorA1[i] = desempilha();
        }
        B1 = desempilha();
        for(int i = 0; i < (tamanho/4)*2; i++){
            vetorC[i] = desempilha();
        }
        B2 = desempilha();
        for(int i = 0; i < tamanho/4; i++){
            vetorA2[i] = desempilha();
        }
        int cont = 0;
        for(int i = 0; i<tamanho/4; i++){
            if(vetorA1[i] != vetorA2[i]){
                cont = -1;
            }
        }
        for (int i = 0; i < (tamanho/4)*2; i++)
        {
            if(vetorC[i] != "C"){
                cont = -1;
            }
            
        }
        if((B1 != "B") or (B2 != "B")){
            cont = -1;
        }
        if(cont == 0){
            simetrica = true;
        }
        else {
            simetrica = false;
        }
    }
    else {
        simetrica = false;
    }
    
    if(simetrica == true){
        cout << "VERDADEIRO" << endl;
    }
    else {
        cout << "FALSO" << endl;
    }
        
    
}

void pilha :: reconhece(pilha& umaPilha){
    bool acabouA=true;
    bool acabouC=true;
    bool acabouB=true;
    string A;
    string B;
    string C;
    int contA=0;
    int contC=0;
    int contB=0;
    string x;
    while(umaPilha.topo!= NULL){
        x = desempilha();
        if((x == "A")and(acabouA)){
            contA++;
        }
        else {
            acabouA = false;
            if((x == "C") and (acabouC)){
                contC++;
            }
            else {
                acabouC = false;
                if((x == "B") and (acabouB)){
                contB++;
                }
                else {
                    acabouB = false;
                }
            }
        }
    }
    if((contA == contB)and(contA+contB+contC == tamanho)){
        cout << "VERDADEIRO" << endl;
    }
    else {
        cout << "FALSO" << endl;
    }
}
        
        
        

    
    

int main (){
    
    pilha p;
    p.empilha("A");
    p.empilha("B");
 
    p.empilha("C");

    p.empilha("B");
    p.empilha("A");
   
    p.reconhece(p);

    return 0;
}
    
