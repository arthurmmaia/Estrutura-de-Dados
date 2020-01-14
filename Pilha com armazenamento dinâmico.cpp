#include <iostream>

using namespace std;

typedef int Dado;

class Noh {
    friend class Pilha;
    public:
    
    Noh	(Dado num);
    
    private:
        Dado mDado; // poderia ser outro tipo de variavel
        Noh* mPtProx;
};

Noh::Noh( Dado num)
:	mDado(num),
	mPtProx(NULL)
{	
}



class Pilha {
    public:

        Pilha();// Constroi pilha vazia.
		~Pilha(); // Destrutor que desaloca memoria.
        // Retira e retorna o valor que estiver no mPtTopo da pilha.
        // Escreve uma mensagem de erro se nÃ£o for possÃ­vel desempilhar.
        Dado Desempilhar(); // retorna o mPtTopo da Pilha
        // Insere um valor na pilha.
        void Empilhar(const Dado& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Informa quantos valores existem na pilha.
        unsigned Tamanho() { return mTamanho; }
        // Retorna o valor que estÃ¡ no mPtTopo sem desempilhar.
        Dado Topo() const;
        // Informa se a pilha estÃ¡ Vazia.
        bool Vazia() const;
    private:
        Noh* mPtTopo;
        unsigned mTamanho;
};

using namespace std;

Pilha::Pilha() 
:	mPtTopo(NULL),
	mTamanho(0)
	
{
}

Pilha::~Pilha() {
	LimparTudo();
}

Dado Pilha::Desempilhar() {
	if (mPtTopo== NULL){
		cerr<< "pilha vazia"<< endl;
		return -1;
	}
	else {
		Noh* aux = new Noh(0);
		Dado valor;
	
		aux= mPtTopo;
	
		valor = aux -> mDado;
	
		mPtTopo= aux -> mPtProx;
		
		delete aux;
		
		mTamanho--;
		return valor; 
	}
}

void Pilha::Empilhar(const Dado& d) {
	Noh* novo= new Noh(d);
	if( mTamanho== 0){
		mPtTopo= novo;
	}
	else{
		novo -> mPtProx= mPtTopo;
		mPtTopo= novo;
	}
	
	mTamanho++;
}

void Pilha::LimparTudo() {
	while(mTamanho>0){
		Desempilhar();
	}
}

Dado Pilha::Topo() const {
	return mPtTopo -> mDado;
	
}

bool Pilha::Vazia() const {
	if(mTamanho==0){
		return true;
	}
	else{
		return false;
	}
}

int main() {
    Pilha pilha;
    Dado valor;
    char comando;
    do {
        cin >> comando;
        switch (comando) {
            case 'i': // inserir
                cin >> valor;
                pilha.Empilhar(valor);
                break;
            case 'r': // remover
                cout << pilha.Desempilhar() << endl;
                break;
            case 'l': // limpar tudo
                pilha.LimparTudo();
                break;
            case 't': // consultar tamanho
                cout << pilha.Tamanho() << endl;
                break;
            case 'e': // espiar
                cout << pilha.Topo() << endl;
                break;
            case 'f': // finalizar
                // checado no do-while
                break;
            default:
                cerr << "comando invÃ¡lido\n";
        }
    } while (comando != 'f'); // finalizar execuÃ§Ã£o
    while (not pilha.Vazia()) {
        cout << pilha.Desempilhar() << ' ';
    }
    cout << endl;
    return 0;
}
