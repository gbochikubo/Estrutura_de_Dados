#include <iostream>
#include <cstdlib>


using namespace std;

typedef int dado;



class noh{
	friend class lista;
	private:
		dado _dado;
		noh* proximo;
		noh* anterior;
	public:
		noh(dado d);
};

noh :: noh(dado d){

	this -> _dado = d;
	this -> proximo = NULL;
	this -> anterior = NULL;
}

class lista{
	
	private:
		int tamanho;
		noh* primeiro;
		noh* ultimo;
		void apagaTudo();
	
	public:
		lista();
		~lista();
		lista(const lista& umaLista);
        lista(const dado umVetor[], int tam);
		inline bool vazia();
		void insere(dado d);
		void insereNoFim(dado d);
		void insereNaPosicao(int posicao , dado d);
		void insereNoInicio(dado d);
		void remove(int posicao);
		void imprime();
		void imprimeReverso();
		lista& operator = (const lista& umaLista);
        lista& operator + (const lista& umaLista);
        lista& operator - (const lista& umaLista);
		noh* acessaPosicao(int posicao);
		void troca(int p1, int p2);
        void bubble();
        void buscaBinaria(dado elemento);
        void removeDuplicado(const lista& umaLista);
        void removeDado(dado d);
        void removeRepetido();
        void divide(int n, lista& umaLista);
        void inverte();
        
};

lista :: lista(){
	this -> tamanho = 0;
	this -> primeiro = NULL;
	this -> ultimo = NULL;
}

lista :: ~lista(){
	apagaTudo();
}

lista :: lista (const dado umVetor[], int tam){
    this -> tamanho = 0;
    this -> primeiro = NULL;
    this -> ultimo = NULL;
    for(int i = 0; i < tam; i++){
        insereNoFim(umVetor[i]);
    }
}

lista :: lista(const lista& umaLista){
	tamanho = 0;
	primeiro = NULL;
	ultimo = NULL;
	
	noh* aux = umaLista.primeiro;
	
	while(aux != NULL){
		insere(aux->_dado);
		aux = aux->proximo;
	}
	
}

void lista :: apagaTudo(){
	
	noh* aux = primeiro;
	
	while (aux != NULL){
			noh* atual = aux;
			aux = aux->proximo;
			delete atual;
		}
	this->primeiro = NULL;
	this->ultimo = NULL;
	this->tamanho = 0;
}	

inline bool lista :: vazia(){
	return (primeiro==NULL and ultimo==NULL);
}

void lista :: insereNoFim(dado d){
	
	noh* novo = new noh(d);
	
	if(vazia()){
		
		primeiro = novo;
		ultimo = novo;
	}
	
	else {
		ultimo->proximo = novo;
		novo->anterior = ultimo;
		ultimo = novo;
	}
	tamanho++;
}

void lista :: imprime(){
	noh* aux = primeiro;
	while ( aux != NULL){
		cout << aux->_dado << " ";
		aux = aux->proximo;
	}
	cout << endl;
}

void lista :: imprimeReverso(){
	noh* aux = ultimo;
	while(aux != NULL){
		cout << aux->_dado << " ";
		aux = aux->anterior;
	}
	cout << endl;
}

void lista :: insere(dado d){
	insereNoFim(d);
}

void lista :: insereNoInicio(dado d){
	
	noh* novo = new noh(d);
	if ((primeiro == NULL) and (ultimo == NULL)){
			primeiro = novo;
			ultimo = novo;
		}
		else {
			primeiro->anterior = novo;
			novo->proximo = primeiro;
			primeiro = novo;
		}
		tamanho++;
}

void lista :: insereNaPosicao(int posicao, dado d){
	
	noh* novo = new noh(d);
	int cont =0;
	if((posicao >= 0) and (posicao <= tamanho)){
		if(posicao == 0){
			insereNoInicio(d);
		}
		else if(posicao == tamanho){
			insereNoFim(d);
		}
		else {
			noh* x = primeiro;
			while (cont < posicao-1){
				x = x->proximo;
				cont ++;
			}
			
			noh* y = x->proximo;
			x->proximo = novo;
			novo->anterior = x;
			y->anterior = novo;
			novo->proximo = y;
		}
	}
	else {
		cerr << "POSIÇÃO INVALIDA !" << endl;
	}
}

void lista :: remove(int posicao){
	
	if((posicao >= 0) and (posicao <tamanho)){
		int cont = 0;
		noh* aux = primeiro;
		if(posicao == 0){
			noh* y = aux->proximo;
			y->anterior = NULL;
			primeiro = y;
		}
		else if(posicao == tamanho-1){
			noh* y = ultimo;
			aux = y->anterior;
			aux->proximo = NULL;
			ultimo = aux;
		}
		else {
			while(cont < posicao){
				aux = aux->proximo;
				cont++;
			}
			noh* x = aux->anterior;
			noh* y = aux->proximo;
			x->proximo = y;
			y->anterior = x;
			delete aux;
		}
	}
	else {
		cerr << "POSIÇÃO INVALIDA !" << endl;
	}
}

lista& lista:: operator = (const lista& umaLista){
	
	apagaTudo();
	
	noh* aux = umaLista.primeiro;
	
	while(aux != NULL){
		insereNoFim(aux->_dado);
		aux = aux->proximo;
	}
	return *this;
}	

noh* lista :: acessaPosicao(int posicao){
	if((posicao >=0)and(posicao<tamanho)){
		noh* elemento = primeiro;
		for(int i=0; i < posicao;i++){
			elemento = elemento->proximo;
		}
	
		return elemento;	
	}
	else {
		cerr << "POSICÃO INVALIDA !" << endl;
		return NULL;
	}
	
}

void lista :: troca(int p1, int p2){
	
	int maior = p2;
	if(p1 > p2){
		maior = p1;
		p1 = p2;
		p2 = maior;
	}
	
	if((p1 >= 0) and (p2 <= tamanho-1)){
		
		if((p1 == 0) and (p2 == tamanho-1)){
			noh* x = acessaPosicao(p1);
			noh* y = acessaPosicao(p2);
			noh* xProx = x->proximo;
			noh* yAnt = y->anterior;
			
			x->anterior = yAnt;
			xProx->anterior = y;
			y->anterior = NULL;
			x->proximo = NULL;
			yAnt->proximo = x;
			y->proximo = xProx;
			primeiro = y;
			ultimo =x;
		}
		else if((p1 == 0) and (p2 == 1)){
			noh* x = acessaPosicao(p1);
			noh* y = acessaPosicao(p2);
			noh* yProx = y->proximo;
			x->proximo = yProx;
			x->anterior = y;
			y->proximo = x;
			y->anterior = NULL;
			yProx->anterior = x;
			primeiro = y;
		}
		else if((p1 == tamanho-2) and (p2 == tamanho-1)){
			noh* x = acessaPosicao(p1);
			noh* y = acessaPosicao(p2);
			noh* xAnt = x->anterior;
			xAnt->proximo = y;
			x->proximo = NULL;
			y->proximo = x;
			x->anterior = y;
			y->anterior = xAnt;
			ultimo = x;
		}
		
		else if((p1 == 0) and (p2 != tamanho-1)){
			
			noh* x = acessaPosicao(p1);
			noh* y = acessaPosicao(p2);
			noh* xProx = x->proximo;
			noh* yAnt = y->anterior;
			noh* yProx = y->proximo;
			x->proximo = yProx;
			y->proximo = xProx;
			yAnt->proximo = x;
			x->anterior = yAnt;
			y->anterior = NULL;
			yProx->anterior = x;
			xProx->anterior = y;
			primeiro = y;
		}
		else if ((p1 != 0) and (p2 == tamanho-1)){
			
			noh* x = acessaPosicao(p1);
			noh* y = acessaPosicao(p2);
			noh* yAnt = y->anterior;
			noh* xAnt = x->anterior;
			noh* xProx = x->proximo;
			x->proximo = NULL;
			yAnt->proximo = x;
			xAnt->proximo = y;
			y->proximo = xProx;
			x->anterior = yAnt;
			xProx->anterior = y;
			y->anterior = xAnt;
			ultimo = x;
		}
        else if((p2-p1)==1){
		
		noh* anterior = acessaPosicao(p1-1);
		noh* proximo = acessaPosicao(p2+1);
		noh* auxX = acessaPosicao(p1);
		noh* auxY = acessaPosicao(p2);
		
		anterior->proximo = auxY;
		auxY->proximo = auxX;
		auxX->proximo = proximo;
		auxY->anterior = anterior;
		auxX->anterior = auxY;
		proximo->anterior = auxX;
        
	}
    else {
		
		noh* auxX = acessaPosicao(p1);
		noh* auxY = acessaPosicao(p2);
		noh* anteriorX = auxX->anterior;
		noh* anteriorY = auxY->anterior;
		noh* proximoX = auxX->proximo;
		noh* proximoY = auxY->proximo;
		
		anteriorX->proximo=auxY;
		auxX->proximo = proximoY;
		anteriorY->proximo = auxX;
		auxY->proximo = proximoX;
		proximoY->anterior = auxX;
		auxY->anterior = anteriorX;
		auxX->anterior = anteriorY;
		proximoX->anterior = auxY;
        }
    }
}

lista& lista :: operator +( const lista& umaLista){
        
    noh* aux = umaLista.primeiro;
    while ( aux != NULL){
        insereNoFim(aux->_dado);
        aux = aux->proximo;
    }
    return *this;
}


void lista :: bubble () {
    
    bool trocou = true;
    
    while (trocou) {
        trocou = false;
    
        for(int i = 0; i < tamanho-1; i++){
            
            noh* aux = acessaPosicao(i);
            noh* aux2 = acessaPosicao(i+1);
            
            if(aux->_dado > aux2->_dado){
                troca(i, i+1);
                trocou = true;
            }
        }
    }
}


void lista :: buscaBinaria(dado elemento){
    bubble();
    
    int inicio = 0;
    int fim = tamanho-1;
    int meio;
    int posicao = -1;
    
    while (inicio <= fim){
        meio = (inicio+fim)/2;
        noh* aux = acessaPosicao(meio);

        if(aux->_dado == elemento){
            posicao = meio;
            inicio = fim+1;
        }
        else {
            if (elemento > aux->_dado){
                inicio = meio+1;
            }
            else {
                fim = meio-1;
            }
        }
    }
    if(posicao == -1){
        cout <<"DADO NÃO ENCONTRADO !" << endl;
    }
    else {
        cout << posicao << endl;
    }
}

void lista :: removeDuplicado(const lista& umaLista){
    
    noh* aux = umaLista.primeiro;
    noh* original = primeiro;

    while(original != NULL){
        aux = umaLista.primeiro;
        while ((aux != NULL)){
             cout << "original " << original->_dado;
            cout << "/ aux  " << aux->_dado << endl;
            
            if ( aux->_dado == original->_dado){
               removeDado(original->_dado);
               
                
            }
            aux = aux->proximo;
        }
        
        original = original->proximo;
        
    }
    
}

void lista :: removeDado(dado d){
    
    noh* aux = primeiro;
    bool trocou = true;
    
    while ( aux != NULL){
        
        if ((aux->_dado == d)and (trocou)){
            
            if(aux == primeiro){
                noh* segundo = aux->proximo;
                segundo->anterior = NULL;
                primeiro =segundo;
                delete aux;
                trocou = false;
            }
            else if ( aux == ultimo){
                noh* penultimo = aux->anterior;
                penultimo->proximo = NULL;
                ultimo = penultimo;
                delete aux;
                trocou = false;
            }
            else {
                noh* anterior = aux->anterior;
                noh* posterior = aux->proximo;
                anterior->proximo = posterior;
                posterior->anterior = anterior;
                delete aux;
                trocou = false;
            }
        }
        aux = aux->proximo;
    }
}

void lista::removeRepetido(){
    noh* aux = primeiro;
    bool removeu = true;
    
    while (( aux->proximo!= NULL)){

        noh* copia = aux->proximo;
    
        while ((copia != NULL)and(removeu)){
            if ( copia->_dado == aux->_dado){
                removeDado(aux->_dado);
                removeu = false;
            }
            copia = copia->proximo;
        }
        removeu = true;
        aux = aux->proximo;
    }
}

void lista :: divide(int n, lista& umaLista){
    
    noh* aux = acessaPosicao(n);
    cout << "AQUI " << aux->_dado << endl;
    while(aux != NULL){
        cout << "ENTROU " << aux->_dado << " XX " << endl;
        umaLista.insere(aux->_dado);
        removeDado(aux->_dado);
        aux = aux->proximo;
    }
}

void lista :: inverte (){
    
    noh* aux = primeiro;
    
    lista auxiliar;
    
    while(aux != NULL){
        auxiliar.insereNoFim(aux->_dado);
        aux = aux->proximo;
    }
    
    apagaTudo();
    
    noh* copia = auxiliar.ultimo;
    
    while(copia != NULL){
        insereNoFim(copia->_dado);
        copia=copia->anterior;
    }
    auxiliar.apagaTudo();
}

lista& lista :: operator -(const lista& umaLista){
    
    noh* aux = umaLista.primeiro;
    
    while( aux != NULL){
        noh* original = primeiro;
        while(original != NULL){
            if(aux->_dado == original->_dado){
                removeDado(original->_dado);
            }
            original = original->proximo;
        }
        aux = aux->proximo;
    }
    return *this;
}
    

int main(){
	
	lista list;
	
	list.insere(150);
	list.insere(200);
	list.insere(300);
	list.insere(450);
	list.insere(500);
	
	lista list2;
	
	list2.insere(100);
	list2.insere(200);
	list2.insere(300);
	list2.insere(400);
	list2.insere(500);

        lista list3;
        list3 = list2 - list;
        list3.imprime();
    
	
	return 0;
}

