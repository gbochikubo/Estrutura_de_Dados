//~ ARQUIVOS BINARIOS
//~ http://dcm.ffclrp.usp.br/~augusto/teaching/ici/Arquivos-Binarios-CPP.pdf


#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

// FUNÇÃO HASH // 

const int valor = 104729;

int funcaoHash(int id){
    long h = id%16;
    return h;
}

// Classe de Corpos Celestes // 
class CorposCelestes{
    friend class TabelaHash;
    friend class Block;
    private:
        unsigned int _id;
        char _nome[50];
        char _tipo[50];
         double _distancia;
        char _localizacao[20];
        char _descricao[200];
    public:
        CorposCelestes(unsigned int _id, const char nome[50]);
        CorposCelestes();
        void insereNome(const char nome[50]);
        void insereID(unsigned int id);
        void insereTipo( const char tipo[50]);
        void insereDistancia( double distancia);
        void insereLocalizacao(const char localizacao[20]);
        void insereDescricao(const char descricao[200]);
        
     
        void imprime();
        int EspiaId();
        char* EspiaNome();
        
};

CorposCelestes :: CorposCelestes(){
    this->_id = -1;
    strcpy(_nome," ");
    strcpy(_tipo," ");
    this->_distancia = -1;
    strcpy(_localizacao," ");
    strcpy(_descricao, " ");
}

CorposCelestes :: CorposCelestes(unsigned int id, const char nome[50]){
    this->_id = id;
    strcpy(_nome,nome);

}

void CorposCelestes :: insereNome(const char nome[50]){
    strcpy(_nome,nome);
}

void CorposCelestes :: insereID(unsigned int id){
    this->_id = id;
}


void CorposCelestes :: insereTipo(const char tipo[50]){
    strcpy(_tipo,tipo);
    
}

void CorposCelestes :: insereDistancia( double distancia){
    this->_distancia = distancia;
}

void CorposCelestes :: insereLocalizacao(const char localizacao[20]){
    strcpy(_localizacao,localizacao);
}

void CorposCelestes :: insereDescricao (const char descricao[200]){
    strcpy(_descricao,descricao);
}

void CorposCelestes :: imprime (){
    cout << "ID : " << _id << endl << "NOME  : " << _nome << endl << "TIPO  : " << _tipo << endl;
    cout << "DISTANCIA DA TERRA  : " << _distancia << endl << "LOCALIZACÃO  : " << _localizacao << endl << "DESCRIÇÃO :  " <<_descricao << endl;
    cout << "hash: " << funcaoHash(_id) << endl; 
    cout << endl << "************************************" << endl;
    
}

int CorposCelestes :: EspiaId(){
    return _id;
}

char* CorposCelestes :: EspiaNome(){
	return _nome;
}

// Classe Bloco //

class Block {
    friend class TabelaHash;
    private:
        CorposCelestes _elemento[4];
        int _tamanho;
    public:
        Block();
        inline bool vazio();
        void insere(CorposCelestes& elemento);
        void remove(CorposCelestes& elemento);
        void Imprime(const char* ArquivoBloco);
        void imprime();
};

Block :: Block(){
    this->_tamanho = 0;
}

inline bool Block :: vazio(){
    return (_tamanho == 0);
}

void Block :: imprime(){
    for(int i = 0; i < _tamanho; i++){
        _elemento[i].imprime();
    }
}
    

void Block :: insere(CorposCelestes& elemento){
    if(_tamanho < 4){
        _elemento[_tamanho] = elemento;
        _tamanho++;
    }
}

void Block :: remove(CorposCelestes& elemento){
    bool existe = false;
    int posicao=0;
    for(int i = 0; i < _tamanho; i++){
        if(_elemento[i].EspiaNome() == elemento.EspiaNome()){
            existe = true;
            posicao = i;
        }
    }
    if(existe){
        if(_tamanho == 1){
            _tamanho--;
        }
        else{
            while((posicao < _tamanho)){
                swap(_elemento[posicao],_elemento[posicao+1]);
                posicao = posicao+1;
            }
        _tamanho--;
        }
    }
    
 //FAZER TRATAMENTO DE ERRO PARA O CASO DE NÃO EXISTIR
}
void Block::Imprime(const char* ArquivoBloco){
    ifstream leitor(ArquivoBloco, ios::binary);
    leitor.seekg(0,leitor.end);
    int bytes = leitor.tellg();
    cout << bytes << endl;
    leitor.seekg(0,leitor.beg);
    bytes = bytes/sizeof(Block);
    
    Block auxImprime;
    for(int j = 0; j < bytes; j++){
        leitor.read((char*)(&auxImprime),sizeof(Block));
        for(int i = 0; i < (auxImprime._tamanho); i++){
            auxImprime._elemento[i].imprime();
        }
    }
}


//FUNÇÃO PARA CONVERTER BINARIO//

int ConverteDecimal(int numero, int& tam){
    
    int n = numero;
    int i = 0;
    int binario=0;
    int b[tam];
    while(n!=0 ){
        b[i] = n%2;
        n = n/2;
        i++;           
    }
    for(int i=0; i < tam; i++){
        if(b[i] == 1){
            binario = binario + pow(10,i);
        }
    }
    return binario;
}


int ConverteBinario(int binario){
    int decimal=0;
    int copia=binario;
    int tam = 0;
    while(copia != 0){
        copia =copia/10;
        tam++;
    }   
    int b[tam];
    int i=0;
    while(binario != 0){
        if(binario%10 == 0){
            b[i] = 0;
        }
        else{
            b[i] = 1;
        }
        binario = binario/10;
        i++;
    }
    for(int i = 0; i < tam; i++){
        if(b[i] == 1){
            decimal = decimal + pow(2,i);
        }
    }
     return decimal;
    
}




// Classe Tabela Hash //

class TabelaHash{
	//~ friend class Block;
    public:
        TabelaHash(const char* ArquivoBloco, const char* ArquivoLocalizacao);
        void Insere(CorposCelestes& CorpoC);
        void imprimeNaHash();
        void remove(int id);
         void CarregaMapeamento();
        
    private:
        void Localizando(const char* ArquivoLocalizacao);
        int* mLocalizacao;          //Hash
        char* mArquivoBloco;        //nome do arquivo dos blocos    
        char* mArquivoLocalizacao;  //nome do arquivo hash
        int mCapacidade;            
        Block* getBlock(int key);
        void registerBlock(Block* bloco, int key);
        void SalvaMapeamento();
        //void CarregaMapeamento();
        
        
};
TabelaHash::TabelaHash(const char* ArquivoBloco, const char* ArquivoLocalizacao){
    mArquivoBloco = new char[strlen(ArquivoBloco)];
    strcpy(mArquivoBloco, ArquivoBloco);
    mArquivoLocalizacao = new char[strlen(ArquivoLocalizacao)];
    strcpy(mArquivoLocalizacao, ArquivoLocalizacao);
    mCapacidade = 16;
    mLocalizacao = new int[mCapacidade];
    for(int i=0; i<16; ++i){
        mLocalizacao[i] = -1;
    }
    CarregaMapeamento();
    
    
}

void TabelaHash::Localizando(const char* ArquivoLocalizacao){
    
    ifstream leitor(mArquivoLocalizacao, ios::binary);
    int PosHash, PosArq;
    leitor.seekg(0,leitor.end);
    int bytes = leitor.tellg();
    leitor.seekg(0,leitor.beg);
    if(leitor){
        for(int i = 0; i < bytes/4; i++){
            leitor.read((char*)(&PosHash),sizeof(int));
            leitor.read((char*)(&PosArq),sizeof(int));
            mLocalizacao[PosHash] = PosArq;
        }
    }
}

/** Função Responsavel por gravar um bloco no arquivo **/

void TabelaHash::registerBlock(Block* bloco, int key){
    int posicao = mLocalizacao[key];
    bool controlador = false;
    bool TemVazio = false;
    if(posicao == -1){
        ifstream leitor(mArquivoBloco, ios::binary);
        leitor.seekg(0, leitor.end);
        int tamanho = leitor.tellg();
        leitor.seekg(0, leitor.beg);
        if(tamanho == -1){
            tamanho = 0;
        }
        posicao = tamanho/sizeof(Block);
        controlador = true;
        Block* aux = new Block();
         if(tamanho > 0){
			for(unsigned int i = 0; i < ((tamanho/sizeof(Block)) and (not TemVazio)); i++){
				 if(leitor.good() and leitor.read((char*)(aux),sizeof(Block))) {
					if(aux->_tamanho == 0){
						posicao = i;
						TemVazio = true;
					}
					delete aux;
				}
			 }
		 }
		 mLocalizacao[key] = posicao;
		leitor.close();		 
    }
    if((controlador)and(not TemVazio)){
        fstream gravador(mArquivoBloco, ios::binary | ios::app);
        gravador.write(reinterpret_cast<const char*> (bloco), sizeof(Block));
        SalvaMapeamento();
    }
    else{
        fstream gravador(mArquivoBloco, ios::binary | ios::in | ios::out);
        gravador.seekp((posicao)*sizeof(Block));
        gravador.write(reinterpret_cast<const char*> (bloco), sizeof(Block));
        SalvaMapeamento();
    }
}

/**Função Responsavel por Inserir um Corpo Celeste no aquivo**/

void TabelaHash::Insere(CorposCelestes& CorpoC){
    int key = funcaoHash(CorpoC._id);
    Block* bloco;
    if(mLocalizacao[key] == -1)
        bloco = new Block();
    else{
        bloco = getBlock(key);
    }
        
    bloco->insere(CorpoC);
    
    registerBlock(bloco, key);
} 

/** Função Responsavel por voltar o bloco em determinada chave procurada **/

Block* TabelaHash::getBlock (int key){
 
    ifstream leitor(mArquivoBloco, ios::binary);
    int ChaveHash = mLocalizacao[key];
    int tamanho = sizeof(Block);
    leitor.seekg((ChaveHash)*tamanho);
    Block* Procurado= new Block();
    leitor.read((char*)(Procurado),sizeof(Block));
    return Procurado;
                
}    

void TabelaHash :: imprimeNaHash(){
    Block auxiliar;
    auxiliar.Imprime(mArquivoBloco);
}

void TabelaHash :: remove(int id){
	int chave = funcaoHash(id);
	Block* aux = getBlock(chave);
	int i = 0;
	bool removeu = false;
	while((i < aux->_tamanho)){
		if(aux->_elemento[i].EspiaId() == id){
			aux->remove(aux->_elemento[i]);
			i=aux->_tamanho+1;
			removeu = true;
		}
		i++;
	}
	if(removeu){
		int posicao = mLocalizacao[chave];
		fstream gravador(mArquivoBloco, ios::binary | ios::in | ios::out);
        gravador.seekp((posicao)*sizeof(Block));
        gravador.write(reinterpret_cast<const char*> (aux), sizeof(Block));
        if(aux->_tamanho == 0){
			mLocalizacao[chave] = -1;
		}
		
	}
	else{
		cout << "deu errado" << endl;
	}
		
		
}

void TabelaHash :: SalvaMapeamento (){
	fstream gravador(mArquivoLocalizacao, ios::binary | ios::out |ios::trunc);
	for(int i = 0; i < 16; i++){
		if(mLocalizacao[i] != -1){
			int binario = 0;
			int TamBin = 4;
			binario = ConverteDecimal(i,TamBin);
			gravador.write(reinterpret_cast<const char*> (&binario), sizeof(int));
			gravador.write(reinterpret_cast<const char*> (&mLocalizacao[i]), sizeof(int));
		}
	}
	gravador.close();
}

void TabelaHash :: CarregaMapeamento(){
	ifstream Mapeamento(mArquivoLocalizacao, ios::binary);
    if(Mapeamento){
		Mapeamento.seekg(0, Mapeamento.end);
		int tamanho = Mapeamento.tellg();
		Mapeamento.seekg(0, Mapeamento.beg);
		int key;
		int pos;
		for(unsigned int i = 0; i < tamanho/(2*sizeof(int)); i++){
			Mapeamento.read((char*)(&key),sizeof(int));
            Mapeamento.read((char*)(&pos),sizeof(int));
			key = ConverteBinario(key);
			mLocalizacao[key] = pos;
		}
	}
	Mapeamento.close();
}

			
			
			

int main(){
   CorposCelestes terra;
    terra.insereID(1);
    terra.insereNome("terra");
    terra.insereDescricao("Tem agua");
    terra.insereDistancia(0);
    terra.insereLocalizacao("sistema solar");
    terra.insereTipo("planeta");
    
     CorposCelestes marte;
     marte.insereID(2);
     marte.insereNome("Mars");
     marte.insereDescricao("Tem agua nao");
     marte.insereDistancia(200);
     marte.insereLocalizacao("sistema solar");
     marte.insereTipo("planeta");
    
    
    CorposCelestes sol;
     sol.insereID(3);
     sol.insereNome("sun");
     sol.insereDescricao("Tem agua nao");
     sol.insereDistancia(1000);
     sol.insereLocalizacao("sistema solar");
     sol.insereTipo("estrela");
     
     CorposCelestes A;
     A.insereID(4);
     A.insereNome("A");
     A.insereDescricao("A");
     A.insereDistancia(1);
     A.insereLocalizacao("A");
     A.insereTipo("A");
     CorposCelestes B;
     B.insereID(5);
     B.insereNome("B");
     B.insereDescricao("B");
     B.insereDistancia(2);
     B.insereLocalizacao("B");
     B.insereTipo("B");
     CorposCelestes C;
     C.insereID(6);
     C.insereNome("C");
     C.insereDescricao("C");
     C.insereDistancia(200);
     C.insereLocalizacao("C");
     C.insereTipo("C");
      CorposCelestes D;
     D.insereID(7);
     D.insereNome("DD");
     D.insereDescricao("DD");
     D.insereDistancia(400);
     D.insereLocalizacao("DD");
     D.insereTipo("DD");
     CorposCelestes E;
     E.insereID(8);
     E.insereNome("EE");
     E.insereDescricao("EE");
     E.insereDistancia(500);
     E.insereLocalizacao("EE");
     E.insereTipo("EE");
     CorposCelestes Z;
     Z.insereID(20);
     Z.insereNome("Z");
     Z.insereDescricao("ZZZ");
     Z.insereDistancia(5000);
     Z.insereLocalizacao("ZZZ");
     Z.insereTipo("ZZZ");
 
     
    TabelaHash tabela("ArqBloco", "ArqLocalizacao");
    tabela.Insere(terra);
     tabela.Insere(marte);
     tabela.Insere(sol);
     //~ tabela.Insere(A);
     tabela.Insere(B);
     tabela.Insere(C);
     //~ tabela.Insere(D);
     tabela.Insere(E);

     tabela.remove(1);
     tabela.Insere(Z);
    
    //~ tabela.imprimeNaHash();
    //~ //tabela.remove("EE");
    tabela.imprimeNaHash();	
  
    return 0;
}
