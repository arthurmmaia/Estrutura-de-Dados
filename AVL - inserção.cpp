#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>

class NohAVL; // declaração avançada

typedef std::string TChave; // chave da árvore
typedef float TValor; // valor da árvore

// Declarações das classes ===================================================

class NohAVL {
	friend class AVL;
	friend std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh);
	private:
		NohAVL (TChave c, const TValor& v);
		~NohAVL();
		NohAVL* ArrumarBalanceamento();
		void AtualizarAltura();
		void DesalocarFilhosRecursivo();
		int FatorBalanceamento();
		NohAVL* InserirRecursivo(NohAVL* ptNoh);
		NohAVL* RotacionarEsquerda();
		NohAVL* RotacionarDireita();
		void TrocarFilho(NohAVL* ptAntigo, NohAVL* ptNovo);
		TChave mChave;
		TValor mValor;
		NohAVL* mPtEsq;
		NohAVL* mPtDir;
		NohAVL* mPtPai;
		unsigned int mAltura; // folhas têm altura 1
};

class AVL {
	public:
		AVL();
		~AVL();
		void EscreverNivelANivel(std::ostream& saida);
		void Inserir(TChave chave, const TValor& valor);
	private:
		NohAVL* mPtRaiz;
};

// === Classe NohAVL ==============================================================================

using namespace std;

NohAVL::NohAVL(TChave c, const TValor& v) 
:	mChave(c),
	mValor(v),
	mPtEsq(NULL),
	mPtDir(NULL),
	mPtPai(NULL),
	mAltura(1)
{
}

NohAVL::~NohAVL() {
}

// Faz as rotações e ajustes necessários inclusive do nó pai. Atualiza a altura.
// Retorna o nó que ficar na posição dele após os ajustes.
NohAVL* NohAVL::ArrumarBalanceamento() {
	AtualizarAltura();
	
	int fatorBal= FatorBalanceamento();

//==========caso esteja desbalanceado=================================

	if(fatorBal>1 and mPtEsq->FatorBalanceamento()>=0){//esq esq
		return RotacionarDireita();
	}
	else if(fatorBal>1 and mPtEsq->FatorBalanceamento()<0){//esq dir
		mPtEsq=mPtEsq->RotacionarEsquerda();
		return RotacionarDireita();
	}
	else if(fatorBal<-1 and mPtDir->FatorBalanceamento()<=0){//dir dir
		return RotacionarEsquerda();
	}
	else if(fatorBal<-1 and mPtDir->FatorBalanceamento()>0){//dir esq
		mPtDir=mPtDir->RotacionarDireita();
		return RotacionarEsquerda();
	}
	
//========caso esteja balanceado======================================

	return this;
}

// Calcula e atualiza a altura de um nó.
void NohAVL::AtualizarAltura() {
	//altura do pai é a maior altura dos filhos +1
	
	if(mPtEsq==NULL and mPtDir==NULL){//se nao tem dois filhos, ou seja, eh folha
		mAltura=1;
	}
	else if(mPtEsq==NULL){//se o esquerdo for null mas o direito existir
		mAltura=mPtDir->mAltura+1;
	}
	else if(mPtDir==NULL){//se o direito for null mas o esquerdo existir
		mAltura= mPtEsq->mAltura+1;
	}
	else{//se tem dois filhos
		if(mPtEsq->mAltura > mPtDir->mAltura){//se esquerdo é maior que direito
			mAltura= mPtEsq->mAltura+1;
		}
		else{//se direito for maior ou as alturas forem iguais
			mAltura=mPtDir->mAltura+1;
		}
	}
}

// Desaloca todos os descendentes.
void NohAVL::DesalocarFilhosRecursivo() {
	if(mPtEsq!=NULL){
		mPtEsq->DesalocarFilhosRecursivo();
	}
	else if(mPtDir!=NULL){
		mPtDir->DesalocarFilhosRecursivo();
	}
	delete this;
}

// Calcula e retorna o fator de balanceamento do nó.
int NohAVL::FatorBalanceamento() {
	int dir;
	int esq;
	if(mPtDir==NULL){
		dir=0;
	}
	else{
		dir= mPtDir->mAltura;
	}
	
	if(mPtEsq==NULL){
		esq=0;
	}
	else{
		esq= mPtEsq->mAltura;
	}
	return esq-dir;
}

// Insere um nó numa subárvore.
NohAVL* NohAVL::InserirRecursivo(NohAVL* ptNoh) {
	if(ptNoh->mChave < mChave){//????????????????????????????
		if(mPtEsq == NULL){
			mPtEsq= ptNoh;
			ptNoh->mPtPai= this;
		}
		else{
			mPtEsq= mPtEsq->InserirRecursivo(ptNoh);
		}
	}
	else{
		if (mPtDir == NULL){
			mPtDir=ptNoh;
			ptNoh->mPtPai=this;
		}
		else{
			mPtDir= mPtDir->InserirRecursivo(ptNoh);
		}
	}

	return ArrumarBalanceamento();
}

// Rotaciona a subárvore à direita. Retorna a nova raiz da subárvore.
NohAVL* NohAVL::RotacionarDireita() {
	NohAVL* nohAux= mPtEsq; //aux é o filho esq do meu noh
	
	mPtEsq=nohAux->mPtDir; //faz o filho esquerdo do aux ser filho direito do noh
	
	if(nohAux->mPtDir!=NULL){//se meu noh aux tem filho esquerdo eu falo pra ele quem é o novo pai dele
		nohAux->mPtDir->mPtPai=this;
	}
	
	nohAux->mPtPai=mPtPai; //faz a funçao do transplanta, fala pro que o pai do aux é o antigo pai do noh

	//faco o noh ser filho esquerdo do meu aux e falo pro noh que o pai dele é o nohAux
	nohAux->mPtDir =this;
	mPtPai = nohAux;
	
	// atualiza alturas
	AtualizarAltura();
	nohAux->AtualizarAltura();
	
	// opcional: retornar a nova raiz da subárvore
	return nohAux;
}

// Rotaciona a subárvore à esquerda. Retorna a nova raiz da subárvore.
NohAVL* NohAVL::RotacionarEsquerda() {
	NohAVL* nohAux= mPtDir; //aux é o filho direito do meu noh
	mPtDir=nohAux->mPtEsq; //faz o filho esquerdo do aux ser filho direito do noh
	
	if(nohAux->mPtEsq!=NULL){//se meu noh aux tem filho esquerdo eu falo pra ele quem é o novo pai dele
		nohAux->mPtEsq->mPtPai=this;
	}
	nohAux->mPtPai=mPtPai; //faz a funçao do transplanta, fala pro que o pai do aux é o antigo pai do noh

	
	//faco o noh ser filho esquerdo do meu aux e falo pro noh que o pai dele é o nohAux
	nohAux->mPtEsq =this;
	mPtPai = nohAux;
	
	// atualiza alturas
	AtualizarAltura();
	nohAux->AtualizarAltura();
	
	// opcional: retornar a nova raiz da subárvore
	return nohAux;
}

// Substitui um dos filhos por um novo nó.
void NohAVL::TrocarFilho(NohAVL* ptAntigo, NohAVL* ptNovo) {
	if(ptAntigo==mPtEsq){//se for filho esq
		mPtEsq=ptNovo;
	}
	else{
		mPtDir=ptNovo;
	}
}

// Escreve o conteúdo de um nó no formato [altura:chave/valor].
// Escreve "[]" se o ponteiro recebido for NULL.
std::ostream& operator<<(std::ostream& saida, NohAVL* ptNoh) {
	if (ptNoh == NULL)
		saida << "[]";
	else
		saida << '[' << ptNoh->mAltura << ':' << ptNoh->mChave << '/' << ptNoh->mValor << ']';
	return saida;
}

// === Classe AVL =================================================================================
AVL::AVL() 
:	mPtRaiz(NULL)
{
}

AVL::~AVL() {
	mPtRaiz->DesalocarFilhosRecursivo();
}

// Escreve o conteúdo da árvore nível a nível, na saída de dados informada.
// Usado para conferir se a estrutra da árvore está correta.
void AVL::EscreverNivelANivel(ostream& saida) {
	queue<NohAVL*> filhos;
	NohAVL* fimDeNivel = new NohAVL(TChave(), TValor()); // nó especial para marcar fim de um nível
	filhos.push(mPtRaiz);
	filhos.push(fimDeNivel);
	while (not filhos.empty()) {
		NohAVL* ptNoh = filhos.front();
		filhos.pop();
		if (ptNoh == fimDeNivel) {
			saida << "\n";
			if (not filhos.empty())
				filhos.push(fimDeNivel);
		}
		else {
			saida << ptNoh << ' ';
			if (ptNoh != NULL) {
				filhos.push(ptNoh->mPtEsq);
				filhos.push(ptNoh->mPtDir);
			}
		}
	}
	delete fimDeNivel;
}

// Insere um par chave/valor na árvore.
void AVL::Inserir(TChave chave, const TValor& valor) {
	NohAVL* novo= new NohAVL(chave, valor);
	if(mPtRaiz==NULL){
		mPtRaiz=novo;
	}
	else{
		mPtRaiz = mPtRaiz->InserirRecursivo(novo);
	}
}

// === Programa ===================================================================================
int main() {
	AVL minhaArvore;
	char opcao;
	TChave chave;
	TValor valor;
	do {
		cin >> opcao;
		switch (opcao) {
			case 'i': // Inserir
				cin >> chave >> valor;
				minhaArvore.Inserir(chave, valor);
				break;
			case 'e': // Escrever nós nível a nível
				minhaArvore.EscreverNivelANivel(cout);
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
