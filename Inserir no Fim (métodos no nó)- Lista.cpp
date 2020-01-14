// Este programa Ã© uma implementaÃ§Ã£o mÃ­nima de Lista.
// Sem atributos tamanho e Ãºltimo, sem remoÃ§Ã£o, sem alteraÃ§Ã£o, etc...
// Os mÃ©todos estÃ£o "no nÃ³".

#include <iostream>

typedef int Dado;

class Noh;

// === DeclaraÃ§Ã£o da Lista ======
class Lista {
    public:
        // Cria Lista vazia.
        Lista();
        // Desaloca memÃ³ria.
        ~Lista();
        // Insere um dado no fim da lista.
        void InserirNoFim(const Dado& dado);
        // Retorna um item da lista.
        Dado Item(unsigned pos);
        // Escreve todos os itens da lista.
        void Escrever(std::ostream& saida);
    protected:
        Noh* mPtPrimeiro;
};

// === DeclaraÃ§Ã£o do Noh ========
class Noh {
    public:
        Noh(Dado d, Noh* prox);
        ~Noh();
        void DesalocarProximos();
        void EscreverDadosAPartirDaqui(std::ostream& saida);
        Dado Item(unsigned distancia);
        void ProcurarUltimoEInserir(const Dado& dado);
    protected:
        Dado mDado;
        Noh* mPtProximo;
};

using namespace std;

// === ImplementaÃ§Ã£o do Noh =====
Noh::Noh(Dado d, Noh* prox)
    : mDado(d), mPtProximo(prox) {
}

Noh::~Noh() {
    cout << "Noh com o valor " << mDado << " desalocado.\n";
}

void Noh::DesalocarProximos() {
// desaloca todos os nÃ³s que aparecerem depois deste
    if (mPtProximo != NULL) {
        mPtProximo->DesalocarProximos();
        delete mPtProximo;
    }
}
void Noh::EscreverDadosAPartirDaqui(std::ostream& saida) {
// escreve o dado deste nÃ³ e todos os prÃ³ximos, separados por vÃ­rgula
    saida << mDado;
    if (mPtProximo != NULL) {
        saida << ',';
        mPtProximo->EscreverDadosAPartirDaqui(saida);
    }
}

Dado Noh::Item(unsigned distancia) {
    // Retorna o item Ã  distÃ¢ncia especificada deste nÃ³.
    // DistÃ¢ncia zero indica este mesmo nÃ³. DistÃ¢ncia indica o prÃ³ximo e assim por diante.
    // Escreve mensagem de erro e retorna dado default se a distÃ¢ncia for invÃ¡lida.
    
	if(distancia==0){
		return mDado;
	}
	else{
		Noh* busca=mPtProximo;
		unsigned i=1;
		while(busca->mPtProximo!=NULL and i<distancia){
			busca=busca->mPtProximo;
			i++;		
		}
		if(i<=(distancia-1)){
			cout << "Erro: posicao invalida!\n";
			return Dado();
		}
		else{
			return busca->mDado;
		}
	}
}

void Noh::ProcurarUltimoEInserir(const Dado& dado) {
// segue a sequencia de nohs ate o fim e insere o dado
	Noh* novo= new Noh(dado, NULL);
	Noh* busca=mPtProximo;
	if(busca==NULL){//se so tiver 1 elemento o prox do primeiro e null
		mPtProximo=novo;
	}
	else{
		while(busca->mPtProximo!=NULL){
			busca=busca->mPtProximo;
		}
		busca->mPtProximo=novo;
	}
}


// === ImplementaÃ§Ã£o da Lista ===
Lista::Lista()
    : mPtPrimeiro(NULL) {
// constrÃ³i uma Lista inicialmente vazia
}

Lista::~Lista() {
    if (mPtPrimeiro != NULL) {
        mPtPrimeiro->DesalocarProximos();
        delete mPtPrimeiro;
    }
}

void Lista::Escrever(ostream& saida) {
// escreve os elementos da lista na saida indicada
    saida << '[';
    if (mPtPrimeiro != NULL)
        mPtPrimeiro->EscreverDadosAPartirDaqui(saida);
    saida << "]\n";
}

void Lista::InserirNoFim(const Dado& dado) {
// insere um dado no final da lista
    if (mPtPrimeiro == NULL)
        mPtPrimeiro = new Noh(dado, NULL);
    else
        mPtPrimeiro->ProcurarUltimoEInserir(dado);
}

Dado Lista::Item(unsigned pos) {
    if (mPtPrimeiro != NULL)
        return mPtPrimeiro->Item(pos);
    cout << "Erro: posicao invalida!\n";
    return Dado(); // em caso de erro, retorna o dado default sÃ³ para o compilador nÃ£o reclamar
}

int main() {
    Lista lista;
    Dado valor;
    char opcao;
    int pos;
    cin >> opcao;
    while (opcao != 'f') {
        switch(opcao) {
            case 'i': // Inserir
                cin >> valor;
                lista.InserirNoFim(valor);
                lista.Escrever(cout);
                break;
            case 'p': // item na Posicao
                cin >> pos;
                cout << lista.Item(pos) << endl;
                break;
            default:
                cout << "Erro: opcao invalida!\n";
        }
        cin >> opcao;
    }
    return 0;
}
