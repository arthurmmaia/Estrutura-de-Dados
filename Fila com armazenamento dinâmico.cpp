#include <iostream>

typedef int Dado;

class Noh {
    friend class Fila;
    private:
        Dado mDado;
        Noh* mPtProx;
	public:
		Noh( Dado num);
	
};

Noh::Noh(Dado num)
:	mDado(num),
	mPtProx(NULL)
{
}

class Fila {
    public:
        // Constroi uma fila vazia.
        Fila();
        // Desaloca memÃ³ria de todos os nÃ³s da fila.
        ~Fila();
        // Remove e retorna o primeiro item da fila.
        Dado Remover();
        // Insere um item no final da fila.
        void Inserir(const Dado& d);
        // Retorna o primeiro item da fila sem remover.
        Dado Proximo() const;
        // Remove todos os itens da fila.
        void LimparTudo();
        // Consulta a quantidade de itens na fila.
        unsigned Tamanho() const { return mTamanho; }
        // Consulta se a fila estÃ¡ vaiza.
        bool Vazia() const;
    private:
        Noh* mPrimeiro;
        Noh* mUltimo;
        unsigned mTamanho;
};

using namespace std;

Fila::Fila()
:	mPrimeiro(NULL),
	mUltimo(NULL),
	mTamanho(0)
{
}

Fila::~Fila() {
	LimparTudo();
}

void Fila::Inserir(const Dado& d) {
	Noh* novo= new Noh(d);
	if (mTamanho==0){
		mPrimeiro=novo;
		mUltimo=novo;
	}
	else{
		mUltimo -> mPtProx= novo;
		mUltimo= novo;
	}
	mTamanho++;
}

Dado Fila::Remover() {
	
	if( Vazia()){
		cerr<< "pilha vazia"<< endl;
		
		return -1;
	}
	else {
		Noh* aux= new Noh(0);
		
		aux= mPrimeiro;
		
		mPrimeiro= mPrimeiro -> mPtProx;
		
		Dado desejo;
		
		desejo= aux -> mDado;
		
		delete aux;
		
		mTamanho--;
		
		return desejo;
	}
}

Dado Fila::Proximo() const {
	return mPrimeiro -> mDado;
}

void Fila::LimparTudo() {
	while (mTamanho>0){
		Remover();
	}
}

bool Fila::Vazia() const {
	if (mTamanho ==0){
		return true;
	}
	else{
		return false;
	}
}

int main() {
    Fila fila;
    Dado valor;
    char comando;
    do {
        cin >> comando;
        switch (comando) {
            case 'i': // inserir
                cin >> valor;
                fila.Inserir(valor);
                break;
            case 'r': // remover
                cout << fila.Remover() << endl;
                break;
            case 'l': // limpar tudo
                fila.LimparTudo();
                break;
            case 't': // escrever tamanho
                cout << fila.Tamanho() << endl;
                break;
            case 'e': // espiar proximo
                cout << fila.Proximo() << endl;
                break;
            case 'f': // finalizar
                // vai verificar adiante
                break;
            default:
                cerr << "comando invÃ¡lido\n";
        }
    } while (comando != 'f'); // finalizar execuÃ§Ã£o
    while (not fila.Vazia()) {
        cout << fila.Remover() << ' ';
    }
    cout << endl;
    return 0;
}
