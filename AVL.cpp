#include <iostream>
#include <cstdlib>

using namespace std;

typedef int Dado;

enum posicao{esq, dir};

class noh{
	friend class avl;
	friend int calcAltura(noh* umNoh);
	friend int calcBal(noh* umNoh);
	private:
		noh* pai;
		noh* esq;
		noh* dir;
		Dado dado;
		int altura;
	public:
		noh(Dado d);
		~noh();
		int fatorBalanceamento();
		
};

noh :: noh(Dado d){
	pai = NULL;
	esq = NULL;
	dir = NULL;
	dado = d;
	altura = 1;
}

noh :: ~noh(){
	delete esq;
	delete dir;
}

int calcAltura(noh* umNoh){
	if(umNoh == NULL){
		return 0;
	}
	else{
		return umNoh->altura;
	}
}

int calcBal(noh* umNoh){
	if(umNoh == NULL){
		return 0;
	}
	else{
		return umNoh->fatorBalanceamento();
	}
}

int noh :: fatorBalanceamento(){
	return calcAltura(esq)-calcAltura(dir);
}

class avl{
	private:
		noh* raiz;
		noh* insereAux(noh* umNoh,Dado d);
		noh* rotacaoEsquerda(noh* umNoh);
		noh* rotacaoDireita(noh* umNoh);
		noh* arrumaBalanceamento(noh* umNoh);
		void percorreEmOrdemAux(noh* atual, int nivel);
		void percorrePreOrdemAux(noh* atual);
		void percorrePosOrdemAux(noh* atual);
	public:
		avl();
		~avl();
		void insere(Dado d);
		void percorreEmOrdem();
		void percorrePreOrdem();
		void percorrePosOrdem();
		
};

avl :: avl(){
	raiz = NULL;
}

avl :: ~avl(){
	delete raiz;
}

void avl :: insere(Dado d){
	raiz = insereAux(raiz,d);
}

noh* avl :: insereAux(noh* umNoh, Dado d){

	if(umNoh == NULL){
		noh* novo = new noh(d);
		return novo;
	}
	
		if(d < umNoh->dado){
			umNoh->esq = insereAux(umNoh->esq,d);
			umNoh->esq->pai = umNoh;
		}
		else if(d > umNoh->dado){
			umNoh->dir = insereAux(umNoh->dir,d);
			umNoh->dir->pai = umNoh;
		}
		else{
			cerr << "Elemento Repetido" << endl;
			return umNoh;
		}
	
	return arrumaBalanceamento(umNoh);
}



noh* avl :: rotacaoEsquerda(noh* umNoh){
	noh* aux = umNoh->dir;
	umNoh->dir = aux->esq;
	if(aux->esq != NULL){
		aux->esq->pai = umNoh;
	}
	aux->pai = umNoh->pai;
	if(umNoh->pai != NULL){
		if(umNoh == umNoh->pai->esq){
			umNoh->pai->esq = aux;
		}
		else{
			umNoh->pai->dir = aux;
		}
	}
	umNoh->pai = aux;
	aux->esq = umNoh;
	
	umNoh->altura = 1 + max(calcAltura(umNoh->esq),calcAltura(umNoh->dir));
	aux->altura = 1+max(calcAltura(aux->esq),calcAltura(aux->dir));
	
	return aux;
}

noh* avl :: rotacaoDireita(noh* umNoh){
	noh* aux = umNoh->esq;
	umNoh->esq = aux->dir;
	if(aux->dir != NULL){
		aux->dir->pai = umNoh;
	}
	aux->pai = umNoh->pai;
	
	if(umNoh->pai != NULL){
		if(umNoh == umNoh->pai-esq){
			umNoh->pai->esq = aux;
		}
		else{
			umNoh->pai->dir = aux;
		}
	}
	
	umNoh->pai = aux;
	aux->dir = umNoh;
	
	umNoh->altura = 1+max(calcAltura(umNoh->esq),calcAltura(umNoh->dir));
	aux->altura = 1+max(calcAltura(umNoh->esq),calcAltura(umNoh->dir));
	
	return aux;
}

noh* avl :: arrumaBalanceamento(noh* umNoh){
	
	umNoh->altura = 1+max(calcAltura(umNoh->esq),calcAltura(umNoh->dir));
	
	int bal = umNoh->fatorBalanceamento();
	
	if((bal>=-1) and (bal<=1)){
		return umNoh;
	}
	
	//rotacao simples a direita (RR)
	if((bal > 1) and(calcBal(umNoh->esq) >=0)){
		return rotacaoDireita(umNoh);
	}
	
	//rotacao simples a esquerda(LL)
	if((bal <-1) and(calcBal(umNoh->esq) <=0)){
		return rotacaoEsquerda(umNoh);
	}
	
	//rotacao dupla a esquerda (RL)
	if((bal <-1) and(calcBal(umNoh->dir) >=1)){
		umNoh->dir = rotacaoDireita(umNoh->dir);
		return rotacaoEsquerda(umNoh);
	}
	
	//rotacao dupla esquerda direita (LR)
	if((bal > 1) and (calcBal(umNoh->esq) <=-1)){
		umNoh->esq = rotacaoEsquerda(umNoh->esq);
		return rotacaoDireita(umNoh);
	}
	cerr << "Não deveria chegar aqui" << endl;
	return NULL;
}

void avl :: percorreEmOrdem(){
	percorreEmOrdemAux(raiz,0);
	cout << endl;
}

void avl :: percorreEmOrdemAux(noh* atual, int nivel){
	if(atual != NULL){
		percorreEmOrdemAux(atual->esq,nivel+1);
		cout << atual->dado << "/" << nivel << " ";
		percorreEmOrdemAux(atual->dir,nivel+1);
	}
}

void avl :: percorrePreOrdem(){
	percorrePreOrdemAux(raiz);
}

void avl :: percorrePreOrdemAux(noh* atual){
	if(atual != NULL){
		cout << atual->dado << " ";
		percorrePreOrdemAux(atual->esq);
		percorrePreOrdemAux(atual->dir);
	}
}

void avl :: percorrePosOrdem(){
	percorrePosOrdemAux(raiz);
	cout << endl;
}

void avl :: percorrePosOrdemAux(noh* atual){
	if(atual != NULL){
		percorrePosOrdemAux(atual->esq);
		percorrePosOrdemAux(atual->dir);
		cout << atual->dado << " ";
	}
}



int main(){
	
	avl minhaAvl;
	
	minhaAvl.insere(100);
	minhaAvl.insere(110);
	minhaAvl.insere(120);
	minhaAvl.insere(50);
	minhaAvl.percorrePreOrdem();
	return 0;
}





		
