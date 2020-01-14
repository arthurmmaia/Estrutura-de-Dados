#include <iostream>

typedef int Dado;

class Fila {
    public:
        Fila(unsigned cap = 80);
        ~Fila();
		Dado Desenfileira();// Remove e retorna o primeiro elemento da fila.
        bool Enfileirar(const Dado& valor);// Insere um valor na fila. Retorna um booleano que informa se a inserÃ§Ã£o foi realmente realizada.
        void EscreverConteudo();// Escreve todo o conteÃºdo do armazenamento da fila na saÃ­da de dados.
        void Info() const;// Retorna tamanho, capacidade, inicio e fim da fila.
        Dado Proximo() const;// Retorna o primeiro elemento da fila, sem removÃª-lo.
        unsigned Tamanho() const { return mTamanho; }// Retorna a quantidade de elementos na fila.
        bool Vazia() const;// Consulta se a fila estÃ¡ vazia.
    protected:
        unsigned mCapacidade;
        Dado* mDados;
        unsigned mPosInicio; // indica a posicao do primeiro
        unsigned mPosFim;    // indica a posicao do ultimo
        unsigned mTamanho;
};

using namespace std;

Fila::Fila(unsigned cap)  // cap tem valor default
:	mCapacidade(cap),
	mDados (new Dado[cap]),
	mPosInicio(-1),
	mPosFim(-1),
	mTamanho(0)
{
}

Fila::~Fila() {
	delete[] mDados;
}

// Remove e retorna o primeiro elemento da fila.
Dado Fila::Desenfileira() {
	Dado aux;
	
	aux= mDados[mPosInicio];
	
	if( mPosInicio<mCapacidade-1){
		mPosInicio++;
		
		mTamanho--;
		
		if (mTamanho==0){
			mPosInicio=-1;
			mPosFim=-1;
			
		}
	}
	
	else if(mPosInicio == mCapacidade-1){
		mPosInicio=0;
		mTamanho--;
		
		
		if (mTamanho==0){
			mPosInicio=-1;
			mPosFim=-1;
		
		}
		
	}
	return aux;
}


// Insere um valor na fila. Retorna um booleano que informa se a inserÃ§Ã£o foi realmente realizada.
bool Fila::Enfileirar(const Dado& valor) {
	
	if(mTamanho!=0 and (mPosFim+1== mPosInicio or (mPosFim==mCapacidade-1 and mPosInicio==0))){
		return false;
	}
	else if (mPosFim< mCapacidade-1 and mTamanho!=0){
		mPosFim++;
		mDados[mPosFim]= valor;
		mTamanho++;
		
		return true;
	}
	else if (mTamanho!= 0 and mPosFim== mCapacidade-1){
		mPosFim=0;
		mDados[mPosFim]= valor;
		mTamanho++;
		return true;
	}

	mPosInicio=0;
	mPosFim=0;
	mDados[mPosFim]=valor;
	mTamanho++;
	
	return true;
	
}

// Escreve todo o conteÃºdo do armazenamento (comeÃ§ando da posiÃ§Ã£o zero) da fila na saÃ­da de dados.
void Fila::EscreverConteudo(){
	for(unsigned i=0; i<mCapacidade; ++i){
		cout<< mDados[i]<< " ";
	}	
	cout<< endl;
}

// Retorna tamanho, capacidade, inicio e fim da fila.
void Fila::Info() const {
	cout<< "tamanho="<< mTamanho<< " "<< "capacidade=" << mCapacidade<< " "<< "inicio="<< mPosInicio<< " " <<"fim=" << mPosFim<< endl;
}

// Retorna o primeiro elemento da fila, sem removÃª-lo.
Dado Fila::Proximo() const {
	Dado aux= mDados[mPosInicio];
	
	return aux;
}

// Consulta se a fila estÃ¡ vazia.
bool Fila::Vazia() const {
	
	if(mTamanho==0){
		return true;
	}
	else {
		return false;
	}
}

int main() {
    unsigned capacidade;
    cin >> capacidade;
    Fila fila(capacidade);
    Dado valor;
    char comando;
    cin >> comando;
    while (comando != 't') {
       
        if (comando == 'e'){// enfileirar
            cin >> valor;
            if (not fila.Enfileirar(valor)){
                cerr << "FILA CHEIA!"<<endl;;
			}
		}
        else if(comando== 'd'){ // desenfileirar
            if (fila.Vazia()){
                cerr << "ERRO"<< endl;
			}
            else {
                valor = fila.Desenfileira();
                cout << valor << endl;
            }
		}
       else if(comando== 'p'){ // proximo
            if (fila.Vazia()){
                cerr << "ERRO"<< endl;
			}
            else{
                cout << fila.Proximo() << endl;
			}
		}
        else if (comando== 'i'){ // informacoes sobre a fila
            fila.Info();
            fila.EscreverConteudo();
       }
       else{
            cout << "comando invalido"<< endl;
        }
        cin >> comando;
    }
return 0;
}
