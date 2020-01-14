#include <iostream>
#include <queue>

typedef int TChave;

class Noh {
	friend class Arvore23;
	friend std::ostream& operator<<(std::ostream& saida, Noh* ptNoh);
	protected:
		// MÃ©todos
		Noh(const TChave& chave, Noh* ptPai);
		~Noh();
		void DesalocarRecursivo();
		void DividirSeNecessario(Noh** ptPtRaiz);
		void InserirLocal(const TChave& chave, Noh* ptFilho);
		void InserirRecursivo(const TChave& chave, Noh** ptPtRaiz);
		// Atributos
		TChave mChaves[3]; // 3 chaves so temporariamente
		Noh* mFilhos[4];   // 4 filhos so temporariamente
		Noh* mPtPai;
		short int mQtdChaves;
		int mID; // identificador, util para debugar o programa
};

class Arvore23 {
	public:
		Arvore23();
		~Arvore23();
		void EscreverNivelANivel(std::ostream& saida);
		void Inserir(const TChave& chave);
	protected:
		Noh* mPtRaiz;
};

using namespace std;

// === Classe Noh ==============================================================
Noh::Noh(const TChave& chave, Noh* ptPai) {
	mChaves[0] = chave;
	mQtdChaves = 1;
	mFilhos[0] = NULL; // usamos o primeiro filho para identificar folha
	mPtPai = ptPai;
	static int contador = 1;
	mID = contador++;
}

Noh::~Noh() {
}

void Noh::DesalocarRecursivo() {
	if (mFilhos[0] != NULL)
		for (int i = 0; i <= mQtdChaves; ++i)
			mFilhos[i]->DesalocarRecursivo();
	delete this;
}

// Divide um noh se for necessario, subindo a chave do meio e repetindo o processo.
// Recebe um ponteiro para ponteiro para a raiz, de forma a permitir a mudanca da raiz da arvore
// quando necessario.
void Noh::DividirSeNecessario(Noh** ptPtRaiz) {
	// Se o no esta acima do limite de chaves:
	// -> Criar novo noh com a chave da direita e seus filhos.
	// -> Se o noh tem pai, recomecar nele; senao, criar um novo pai e atualizar a raiz.
	
	//se tiver 3 chaves divide
	if(mQtdChaves==3){
		//crio um novo noh e copio o ultimo elemento pra lá
		Noh* novo= new Noh(mChaves[2], mPtPai);
		//levo os filhos pro novo noh
		novo->mFilhos[0]= mFilhos[2];
		novo->mFilhos[1]= mFilhos[3];
		//falo pros filhos quem são os pais deles
		if(mFilhos[2] != NULL and mFilhos[3]!=NULL){
			mFilhos[2]->mPtPai=novo;
			mFilhos[3]->mPtPai=novo;	
		}
		
		//diminuo a quantidade de chaves no meu antigo noh
		mQtdChaves--;
		
		//se eu tenho pai
		if(mPtPai!=NULL){
			//insiro  no meu pai
			mPtPai->InserirLocal(mChaves[1], novo);
		}
		//se eu não tenho pai
		else{
			Noh* novoPai= new Noh(mChaves[1], NULL);
			novoPai-> mFilhos[0]= this;
			novoPai-> mFilhos[1]= novo;
			
			mPtPai=novoPai;
			novo-> mPtPai= novoPai;
			
			*ptPtRaiz= novoPai;
		}
		//diminuo de novo a quantidade de chaves do meu noh
		mQtdChaves--;
	}
	
	//se nao tiver 3 chaves nao faz nada
	
}

// Adiciona uma chave e um filho ao nÃ³, na posiÃ§Ã£o certa dos vetores.
void Noh::InserirLocal(const TChave& chave, Noh* ptFilho) {
	// Deslocar chaves e filhos a  direita ate abrir espaco para a nova chave e filho.
	// Atualizar a quantidade de chaves no noh.
	int iterador= mQtdChaves-1;
	bool achei= false;
	
	while(iterador>=0 and achei==false){
		//se a chave for menor arrasta pra direita
		if(chave < mChaves[iterador]){
			//arrasta a chave
			mChaves[iterador+1]=mChaves[iterador];
			//arrasta o filho maior
			mFilhos[iterador+2]=mFilhos[iterador+1];
			
			//diminui o iterador
			iterador--;
			
		}
		//se a chave for maior, insere na direita
		else{
			mChaves[iterador+1]= chave;
			
			//insere o filho
			mFilhos[iterador+2]=ptFilho;
			achei=true;
		}
	}
	//se eu percorri tudo e continua sendo menor eu insiro na primeira posicao
	if(achei==false){
		mChaves[0]=chave;
		mFilhos[1]= ptFilho;
		// vai ser no filho 1 pq a chave que subiu é sempre maior que o filho da esquerda do 0
	}
	++mQtdChaves;
}

// Desce recursivamente atÃ© achar uma folha para inserÃ§Ã£o. Faz as arrumaÃ§Ãµes necessÃ¡rias.
void Noh::InserirRecursivo(const TChave& chave, Noh** ptPtRaiz) {

	// Se o noh e folha, inserir aqui mesmo e fazer ajustes necessarios.
	// Senao, recomecar a insercao no filho apropriado.
	
	//descer ate a folha
	if(mFilhos[0] != NULL){//se tem filhos entao nao é folha
		//verifico onde eu quero descer
		int iterador= mQtdChaves-1;
		bool desci=false;
		while(iterador>=0 and desci==false){
			if(chave<mChaves[iterador]){
				iterador--;
			}
			else{
				desci=true;
				mFilhos[iterador+1]->InserirRecursivo(chave, ptPtRaiz);
			}
		}
		if(desci==false){
			mFilhos[0]->InserirRecursivo(chave, ptPtRaiz);
		}
	}
	
	//o noh que eu estou eh folha
	else{
		InserirLocal(chave, NULL);		
	}
	
	DividirSeNecessario(ptPtRaiz);	
}

// Escreve um nÃ³ no formato [ID|chaves|pai;filhos]
	ostream& operator<<(ostream& saida, Noh* ptNoh) {
	if (ptNoh == NULL)
		saida << "[]";
	else {
		saida << '[' << ptNoh->mID << "|" << ptNoh->mChaves[0];
		for (int i = 1; i < ptNoh->mQtdChaves; ++i)
			saida << ',' << ptNoh->mChaves[i];
		int pai = (ptNoh->mPtPai == NULL) ? 0 : ptNoh->mPtPai->mID;
		saida << "|" << pai << ';';
		if (ptNoh->mFilhos[0] != NULL) {
			saida << ptNoh->mFilhos[0]->mID;
			for (int i = 1; i <= ptNoh->mQtdChaves; ++i)
				saida << ',' << ptNoh->mFilhos[i]->mID;
		}
		saida << ']';
	}
	return saida;
}

// === Classe Arvore23 =========================================================
Arvore23::Arvore23() : mPtRaiz(NULL) {
}

Arvore23::~Arvore23() {
	if (mPtRaiz != NULL)
		mPtRaiz->DesalocarRecursivo();
}

// Escreve a Ã¡rvore nÃ­vel a nÃ­vel para facilitar a depuraÃ§Ã£o.
void Arvore23::EscreverNivelANivel(ostream& saida) {
	if (mPtRaiz == NULL)
		cout << "[]\n";
	else {
		queue<Noh*> filhos;
		filhos.push(mPtRaiz);
		while (not filhos.empty()) {
			unsigned nroNohsNesteNivel = unsigned(filhos.size());
			for (unsigned i = 0; i < nroNohsNesteNivel; ++i) {
				Noh* ptNoh = filhos.front();
				filhos.pop();
				saida << ptNoh << ' ';
				if (ptNoh->mFilhos[0] != NULL)
					for (short int i = 0; i <= ptNoh->mQtdChaves; ++i)
						filhos.push(ptNoh->mFilhos[i]);
			}
			cout << "\n";
		}
	}
}

// Insere uma chave na Ã¡rvore.
void Arvore23::Inserir(const TChave& chave) {
	if (mPtRaiz == NULL)
		mPtRaiz = new Noh(chave, NULL);
	else
		mPtRaiz->InserirRecursivo(chave, &mPtRaiz);
}

// === Programa ================================================================
int main() {
	Arvore23 arvore;
	char opcao;
	TChave chave;
	do {
		cin >> opcao;
		switch (opcao) {
			case 'i': // Inserir
				cin >> chave;
				arvore.Inserir(chave);
				break;
			case 'e': // Escrever nÃ³s nÃ­vel a nÃ­vel
				arvore.EscreverNivelANivel(cout);
				break;
			case 'f': // Finalizar o programa
				// vai verificar depois
				break;
			default:
				cerr << "OpÃ§Ã£o invÃ¡lida\n";
		}
	} while (opcao != 'f');
	return 0;
}
