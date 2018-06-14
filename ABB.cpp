#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Dado;

enum posicao{esq,dir};

class noh{
	friend class abb;
	private:
		noh* pai;
		noh* esq;
		noh* dir;
		Dado valor;
	public:
		noh(Dado d);
};

noh :: noh(Dado d){
	valor = d;
	esq = NULL;
	dir = NULL;
	pai = NULL;
}

class abb{
	private:
		noh* raiz;
		noh* minimoAux(noh* aux);
		noh* maximoAux(noh* aux);
		void percorrePreOrdemAux(noh* aux);
		void percorreEmOrdemAux(noh* aux);
		void percorrePosOrdemAux(noh* aux);
		
		
	public:
		abb(); 
		~abb();
		inline bool vazia();
		void insere(Dado d);
		noh* busca(Dado d);
		Dado minimo();
		Dado maximo();
		void percorrePreOrdem();
		void percorreEmOrdem();
		void percorrePosOrdem();
		void remove(Dado d);
		void transplanta(noh* antigo,noh* novo);
		
		
};

abb :: abb(){
	raiz = NULL;
}

abb :: ~abb(){
	delete[] raiz;
}

void abb :: insere(Dado d){
	noh* novo = new noh(d);
	posicao posInsercao;
	if(raiz == NULL){
		raiz = novo;
	}
	else{
		noh* atual = raiz;
		noh* anterior;
		while(atual != NULL){
			anterior = atual;
			if(d > atual->valor){
				atual = atual->dir;
				posInsercao = dir;
			}
			else{
				atual = atual->esq;
				posInsercao = esq;
			}
		}
		novo->pai = anterior;
		if(posInsercao == dir){
			anterior->dir = novo;
		}
		else{
			anterior->esq = novo;
		}
	}
}	

noh* abb :: busca(Dado d){
	noh* atual = raiz;
	while((atual != NULL) and (atual->valor != d)){
		if(d > atual->valor){
			atual = atual->dir;
		}
		else{
			atual = atual->esq;
		}
	}
		return atual;
}	

inline bool abb :: vazia(){
	return (raiz == NULL);
}


Dado abb :: minimo(){
	if(vazia()){
		cerr << "Arvore vazia " << endl;
		exit(EXIT_FAILURE);
	}
	else{
		noh* menor;
		menor = minimoAux(raiz);
		return menor->valor;
	}
}

noh* abb :: minimoAux(noh* aux){
	while(aux->esq != NULL){
		aux = aux->esq;
	}
	return aux;
}

Dado abb :: maximo(){
	if(vazia()){
		cerr << "Arvore vazia " << endl;
		exit(EXIT_FAILURE);
	}
	else{
		noh* maior;
		maior = maximoAux(raiz);
		return maior->valor;
	}
}

noh* abb :: maximoAux(noh* aux){
	while(aux->dir != NULL){
		aux = aux->dir;
	}
	return aux;
}

void abb :: percorrePreOrdem(){
	if(vazia()){
		cerr << "Arvore Vazia" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		percorrePreOrdemAux(raiz);
	}
}

void abb :: percorrePreOrdemAux(noh* aux){
	if(aux != NULL){
		cout << aux->valor << " ";
		percorrePreOrdemAux(aux->esq);
		percorrePreOrdemAux(aux->dir);
	}
}

void abb :: percorreEmOrdem(){
	if(vazia()){
		cerr << "Arvore Vazia" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		percorreEmOrdemAux(raiz);
	}
}

void abb :: percorreEmOrdemAux(noh* aux){
	if(aux != NULL){
		percorreEmOrdemAux(aux->esq);
		cout << aux->valor << " ";
		percorreEmOrdemAux(aux->dir);
		//cout << aux->valor << " ";
	}
}

void abb :: percorrePosOrdem(){
	if(vazia()){
		cerr << "Arvore Vazia" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		percorrePosOrdemAux(raiz);
	}
}

void abb :: percorrePosOrdemAux(noh* aux){
	if(aux != NULL){
		percorrePosOrdemAux(aux->esq);
		percorrePosOrdemAux(aux->dir);
		cout << aux->valor << " ";
	}
} 

void abb :: transplanta(noh* antigo, noh* novo){
	if(antigo == raiz){
		raiz = novo;
	}
	else if(antigo == antigo->pai->esq){
			antigo->pai->esq = novo;
		}
	else{
		antigo->pai->dir = novo;
			}
	if(novo != NULL){
		novo->pai = antigo->pai;
	}
}

void abb :: remove(Dado d){
	noh* VaiRemover = busca(d);
	if(VaiRemover == NULL){
		cerr << "Dado não está na arvore" << endl;
	}
	else{
		if(VaiRemover->esq == NULL){
			transplanta(VaiRemover, VaiRemover->dir);
		}
		else if(VaiRemover->dir == NULL){
			transplanta(VaiRemover,VaiRemover->esq);
		}
		else{
			//caso o nó tenha dois filhos é preciso achar o sucessor ou o antecessor e transplantar
			noh* sucessor = minimoAux(VaiRemover->dir);
			if(sucessor->pai != VaiRemover){
				transplanta(sucessor,sucessor->dir);
				sucessor->dir = VaiRemover->dir;
				sucessor->dir->pai = sucessor;
			}
			transplanta(VaiRemover,sucessor);
			sucessor->esq = VaiRemover->esq;
			sucessor->esq->pai = sucessor;
		}
		VaiRemover->dir = NULL;
		VaiRemover->esq = NULL;
		delete[] VaiRemover;
	}
}


int main (){
	
	abb tree;
	tree.insere(70);
	tree.insere(65);
	tree.insere(80);
	tree.insere(50);
	tree.insere(75);
	tree.insere(77);
	tree.insere(73);
	tree.insere(85);
	tree.insere(84);
	tree.insere(88);
	tree.remove(80);
	tree.percorrePosOrdem();
	
	return 0;
}

