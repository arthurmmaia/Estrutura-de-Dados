#include <iostream>
#include <stdexcept>
#include <queue>

typedef std::string TValor;
typedef unsigned TChave;
enum Cor {PRETO, VERMELHO};

class Noh {
	friend class ArvoreRN;
	friend std::ostream& operator<<(std::ostream& saida, Noh* ptNoh);
	public:
		Noh(unsigned chave, TValor valor);
	private:
		Noh* Tio();
		void DesalocarRecursivo();
		TValor mValor;
		TChave mChave;
		Cor mCor;
		Noh* mEsq;
		Noh* mDir;
		Noh* mPai;
};

class ArvoreRN {
	public:
		ArvoreRN();
		~ArvoreRN();
		void EscreverNivelANivel(std::ostream& saida);
		void Inserir(unsigned chave, TValor valor);
	private:
		void ArrumarInsercao(Noh* umNoh);
		void RotacionarDireita(Noh* umNoh);
		void RotacionarEsquerda(Noh* umNoh);
		Noh* mRaiz;
};

using namespace std;

// === classe Noh ==============================================================
Noh::Noh(TChave chave, TValor valor)
	: mValor(valor), mChave(chave), mCor(VERMELHO), mEsq(NULL), mDir(NULL), mPai(NULL) {
}

// Desaloca as subárvores e depois a si próprio.
void Noh::DesalocarRecursivo() {
	if(mEsq!=NULL){
		mEsq->DesalocarRecursivo();
	}
	else if(mDir!=NULL){
		mDir->DesalocarRecursivo();
	}
	delete this;
}

// Retorna o tio do nó, ou NULL se não houver tio
Noh* Noh::Tio() {
	if(mPai!=NULL){//se tem pai
		if(mPai->mPai!=NULL){//se tem avo
			//olha qual tio tem que pegar, se e da direita ou da esquerda
			if(mPai->mPai->mDir==mPai){
				//se o pai eh filho da direita, pega o irmao dele da esquerda
				return mPai->mPai->mEsq;
			}
			else{
				//se o pai eh filho da esquerda, pega o irmao dele da direita
				return mPai->mPai->mDir;
			}
		}
		else{//se tem pai mas não tem avo, entao nao tem tio
			return NULL;
		}
	}
	else{
	//se nao tem pai, eh raiz e raiz nao tem tio
		return NULL;
	}
}

// === classe ArvoreRN =========================================================
ArvoreRN::ArvoreRN() : mRaiz(NULL) {
}

ArvoreRN::~ArvoreRN() {
	mRaiz->DesalocarRecursivo();
}

// insere uma chave/valor na árvore,
// chama ArrumarInsercao para corrigir eventuais problemas
void ArvoreRN::Inserir(unsigned chave, TValor valor) {
	Noh* novo=new Noh(chave, valor);
	//primeira insercao
	if(mRaiz==NULL){
		mRaiz=novo;
	}
	//se ja tiver inserido algo
	else{
		//insercao iterativa
		Noh* busca= mRaiz;
		bool insere=false;
		while(not insere){
			//se a chave pra inserir for menor
			if(novo->mChave <  busca->mChave){
				if(busca->mEsq==NULL){//se chegou na folha
					busca->mEsq=novo;
					novo->mPai=busca;
					ArrumarInsercao(novo);
					insere=true;
				}
				else{
					busca=busca->mEsq;
				}
			}
			//se a chave pra inserir for maior
			else{
				if(busca->mDir==NULL){//se chegou na folha
					busca->mDir=novo;
					novo->mPai=busca;
					ArrumarInsercao(novo);
					insere=true;
				}
				else{
					busca=busca->mDir;
				}	
			}
		}
	}
	mRaiz->mCor=PRETO;
}

// procedimento para manter balanceamento após inserção
void ArvoreRN::ArrumarInsercao(Noh* umNoh) {

	// percorre a árvore do nó até a raiz, 
	// ou ter arrumado o balanceamento 
	while((umNoh!=NULL) and (umNoh!=mRaiz) and (umNoh->mPai->mCor==VERMELHO)) { //enquanto os pais foem vermelhos e for diferente de raiz
		//se o pai for preto acaba a funcao
		Noh* tio= umNoh->Tio();
		if(tio!=NULL and tio->mCor==VERMELHO) { // CASO 1
			//o tio e o pai que eram vermelhos ficam pretos
			tio->mCor=PRETO;
			umNoh->mPai->mCor = PRETO;
			umNoh->mPai->mPai->mCor=VERMELHO;
			// Atualiza umNoh com o avô para continuar o teste
			umNoh=umNoh->mPai->mPai;
		}
		else{
			//o pai é vermelho e o tio é preto ou se nao tenho tio
			//se o pai é filho da direita e o noh é filho da direita
			if((umNoh->mPai == umNoh->mPai->mPai->mDir) and (umNoh==umNoh->mPai->mDir)) { // CASO 2
			//coloco o pai preto e avo vermelho e rotaciono a esquerda
				umNoh->mPai->mCor=PRETO;
				umNoh->mPai->mPai->mCor=VERMELHO; 
				RotacionarEsquerda(umNoh->mPai->mPai);
			} 
			
			//se o pai é filho da esquerda e o noh é filho da esquerda
			else if((umNoh->mPai == umNoh->mPai->mPai->mEsq) and (umNoh == umNoh->mPai->mEsq)) { // CASO 3
				//coloco o pai preto e o avo vermelho e rotaciona a direita
				umNoh->mPai->mCor=PRETO;
				umNoh->mPai->mPai->mCor=VERMELHO; 
				RotacionarDireita(umNoh->mPai->mPai);
			} 
			//se o pai é filho da direita e o noh é filho da esquerda
			else if((umNoh->mPai == umNoh->mPai->mPai->mDir) and (umNoh == umNoh->mPai->mEsq)) { // CASO 4
				//coloco o noh preto
				//salvo o meu avo
				//coloco meu avo vermelho
				// giro meu pai pra direita e meu avo pra esquerda
				
				umNoh->mCor =PRETO;
				Noh* avo =umNoh->mPai->mPai; // para manter após primeira rotação
				avo->mCor=VERMELHO;
				RotacionarDireita(umNoh->mPai); 
				RotacionarEsquerda(avo);
				// atualiza umNoh para verificação no while
				umNoh=umNoh->mPai; 
			}
			  //pai é filho da esquerda e o noh é filho da direita
			else {
				  //coloco o noh preto
				  //salvo o avo
				  //coloco o avo vermelho
				  //giro o pai a esquerda e o avo a direita
				  
				umNoh->mCor =PRETO;
				Noh* avo =umNoh->mPai->mPai; // para manter após primeira rotação
				avo->mCor=VERMELHO;
				RotacionarEsquerda(umNoh->mPai); 
				RotacionarDireita(avo);
				// atualiza umNoh para verificação no while
				umNoh=umNoh->mPai; 
				}
			}
	}
	mRaiz->mCor=PRETO;
}

// rotação à esquerda, muda a raiz se necessário
void ArvoreRN::RotacionarEsquerda(Noh* umNoh) {
	//salva o filho da esquerda
	Noh* aux= umNoh->mDir;
	//o filho da direita do meu noh vai ser o filho da esquerda do filho direito do meu noh
	umNoh->mDir= aux->mEsq;
	
	if(aux->mEsq!=NULL){//se meu noh aux tem filho esquerdo eu falo pra ele quem é o novo pai dele
		aux->mEsq->mPai=umNoh;
	}
	aux->mPai=umNoh->mPai; //faz a funçao do transplanta, fala pro aux que o pai dele é o antigo pai do noh
	
	//se meu noh era raiz nao precisa falar pro pai dele que o aux é filho
	if(umNoh==mRaiz){
		mRaiz=aux;
	}
	//se eu tenho pai eu tenho que falar pra ele quem é o novo filho dele
	
	else if(umNoh==umNoh->mPai->mEsq){//se o noh é o filho esquerdo
		umNoh->mPai->mEsq=aux; //falo que o filho esquerdo do antigo pai do noh é o nohAux
	}
	else{//se for filho direito
		umNoh->mPai->mDir=aux;
	}
	
	//faco o noh ser filho esquerdo do meu aux e falo pro noh que o pai dele é o nohAux
	aux->mEsq =umNoh;
	umNoh->mPai = aux;

}

// rotação à direita, muda a raiz se necessário
void ArvoreRN::RotacionarDireita(Noh* umNoh) {
	//salva o filho da esquerda
	Noh* aux= umNoh->mEsq;
	//o filho da esquerda do meu noh vai ser o filho da direita do filho esquerdo do meu noh
	umNoh->mEsq= aux->mDir;
	
	if(aux->mDir!=NULL){//se meu noh aux tem filho direito eu falo pra ele quem é o novo pai dele
		aux->mDir->mPai=umNoh;
	}
	aux->mPai=umNoh->mPai; //faz a funçao do transplanta, fala pro que o pai do aux é o antigo pai do noh
	
	//se meu noh era raiz nao precisa falar pro pai dele que o aux é filho
	if(umNoh==mRaiz){
		mRaiz=aux;
	}
	
	//se eu tenho pai eu tenho que falar pra ele quem é o novo filho dele
	
	else if(umNoh==umNoh->mPai->mEsq){//se o noh é o filho esquerdo
		umNoh->mPai->mEsq=aux; //falo que o filho esquerdo do antigo pai do noh é o nohAux
	}
	else{//se for filho direito
		umNoh->mPai->mDir=aux;
	}
	
	//faco o noh ser filho esquerdo do meu aux e falo pro noh que o pai dele é o nohAux
	aux->mDir =umNoh;
	umNoh->mPai = aux;
}

// Escreve o conteúdo da árvore nível a nível
void ArvoreRN::EscreverNivelANivel(ostream& saida) {
	queue<Noh*> filhos;
	filhos.push(mRaiz);
	while (not filhos.empty()) {
		unsigned nroNohsNesteNivel = unsigned(filhos.size());
		for (unsigned i = 0; i < nroNohsNesteNivel; ++i) {
			Noh* ptNoh = filhos.front();
			filhos.pop();
			saida << ptNoh << ' ';
			if (ptNoh != NULL) {
				filhos.push(ptNoh->mEsq);
				filhos.push(ptNoh->mDir);
			}
		}
		cout << "\n";
	}
}

// Escreve um nó (ou NIL).
ostream& operator<<(ostream& saida, Noh* ptNoh) {
	static char vetLetrasCores[] = "PV";
	if (ptNoh == NULL)
		saida << "NIL";
	else
		saida << '[' << vetLetrasCores[ptNoh->mCor] << ':' << ptNoh->mChave << '/'
			  << ptNoh->mValor << ']';
	return saida;
}

int main() {
	ArvoreRN arvore;
	char opcao;
	TChave chave;
	TValor valor;
	do {
		cin >> opcao;
		switch (opcao) {
			case 'i': // Inserir
				cin >> chave >> valor;
				arvore.Inserir(chave, valor);
				break;
			case 'e': // Escrever nós nível a nível
				arvore.EscreverNivelANivel(cout);
				break;
			case 'f': // Finalizar o programa
				// vai verificar depois
				break;
			default:
				cerr << "Opção inválida\n";
		}
	} while (opcao != 'f');
	return 0;
}
