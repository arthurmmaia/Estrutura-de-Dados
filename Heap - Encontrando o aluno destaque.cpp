#include <iostream>   // Pode usar varias coisas prontas
#include <vector>     // mas e' preciso completar a classe
#include <limits>     // classe Heap. E' permitido fazer
#include <string>     // alteracoes na classe Heap.
#include <stdexcept>


class Atividade {
    public:
        int nota;
        int tentativas;
};

class Aluno {
    public:
        Aluno();
        Aluno(unsigned matr, const std::string& n);
        ~Aluno();
        void InserirAtividade(const Atividade& a);
        std::string Nome() const { return nome; }
        unsigned Matricula() { return matricula; }
        float Media() const;
        int Tentativas() const;
    protected:
        unsigned matricula;
        std::string nome;
        std::vector<Atividade> vetAtividades;
};

Aluno::Aluno()
    : matricula(0), nome(), vetAtividades() {
}

Aluno::Aluno(unsigned matr, const std::string& n)
    : matricula(matr), nome(n), vetAtividades() {
}

Aluno::~Aluno() {
}

void Aluno::InserirAtividade(const Atividade& a) {
    vetAtividades.push_back(a);
}

float Aluno::Media() const {
    float soma = 0.0f;
    unsigned nroAtividades = unsigned(vetAtividades.size());
    for (unsigned i = 0; i < nroAtividades; ++i)
        soma += float(vetAtividades.at(i).nota);
    return soma / float(nroAtividades);
}

int Aluno::Tentativas() const {
    int tentativas = 0;
    unsigned nroAtividades = unsigned(vetAtividades.size());
    for (unsigned i = 0; i < nroAtividades; ++i)
        tentativas += vetAtividades[i].tentativas;
    return tentativas;
}
using namespace std;

bool operator>(const Aluno& a1, const Aluno& a2) {
	float media1, media2;
	media1= a1.Media();
	media2= a2.Media();
	if(media1>media2){
		return true;
	}
	else if(media1==media2){
		int tenta1, tenta2;
		tenta1= a1.Tentativas();
		tenta2= a2.Tentativas();
		if(tenta1<tenta2){
			return true;
		}
		else if(tenta1==tenta2){
			int alfabetica=-1;
			string nome1, nome2;
			nome1= a1.Nome();
			nome2=a2.Nome();
			int tam1, tam2;
			tam1= nome1.size();
			tam2= nome2.size();
			int i=0;
			while (alfabetica==0){
				if(i<tam1 and i<tam2){
					if(nome1[i]<nome2[i]){
						alfabetica=1;
					}
					if(nome1[i]>nome2[i]){
						alfabetica=2;
					}
				}
				else if(i<tam1 and i>tam2){
					alfabetica=1;
				}
				else if(i>tam1 and i<tam2){
					alfabetica=2;
				}
			}
			if(alfabetica==1){
				return true;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

typedef Aluno TDado;

class Heap {
    // classe Heap (max-heap, o maior fica na raiz/inicio)
    public:
        // Criar heap sem dados e com capacidade informada
        Heap(int cap);
        // Destruttor
        ~Heap();
        // Inserir um dado na heap
        void Inserir(const TDado& d);
        // Consulta a raiz
        TDado Raiz();
        // Retira e retorna a raiz
        TDado Retirar();
        // Verifica se a heap estÃ¡ vazia
        bool Vazia();
    protected:
        void ArrumarDescendo(int i);
        void ArrumarSubindo(int i);
        inline int Direito(int i);
        inline int Esquerdo(int i);
        inline int Pai(int i);
        int mCapacidade;
        int mTamanho;
        TDado* mVetDados;
};

using namespace std;

Heap::Heap(int cap) 
:	mCapacidade(cap),
	mTamanho(0),
	mVetDados(new TDado[cap])
{
}

Heap::~Heap() {
}

void Heap::ArrumarDescendo(int i) {
    // Arruma as posicoes de i para baixo.
    int filhoE, filhoD, maior;
    filhoE= Esquerdo(i);
    filhoD= Direito(i);
    maior= i;
    if(filhoE<mTamanho and  mVetDados[filhoE]>mVetDados[maior]){
		maior=filhoE;
	}
	if(filhoD<mTamanho and  mVetDados[filhoD]>mVetDados[maior]){
		maior=filhoD;
	}
	if(maior!=i){
		swap(mVetDados[i],mVetDados[maior]);
		ArrumarDescendo(maior);
	}
}

void Heap::ArrumarSubindo(int i) {
    // Arruma as posicoes de i para cima.
    int pai;
    pai= Pai(i);
    
    if(pai>=0 and mVetDados[i]>mVetDados[pai]){
		swap(mVetDados[pai],mVetDados[i]);
		ArrumarSubindo(pai);
	}
}

int Heap::Pai(int i) {
	return (i-1)/2;
}

int Heap::Esquerdo(int i) {
	return (i*2)+1;
}

int Heap::Direito(int i) {
	return (i*2)+2;
}

TDado Heap::Raiz() {
    if (mTamanho == 0) {
        cerr << "Heap vazia nao tem raiz." << endl;
        return TDado();
    }
    else{
		return mVetDados[0];
	}
}

TDado Heap::Retirar() {
    if (mTamanho == 0) {
        cerr << "Impossivel retirar de heap vazia." << endl;
        return TDado();
    }
    else{
		return Raiz();
	}
}

bool Heap::Vazia() {
	return mTamanho==0;
}

void Heap::Inserir(const TDado& d){
    if (mTamanho == mCapacidade) {
        cerr << "Impossivel inserir em heap cheio.\n";
        return;
    }
    else{
		mVetDados[mTamanho]=d;
		mTamanho++;
		ArrumarSubindo(mTamanho-1);
		
	}
}

int main() {
    unsigned qtdeAlunos;
    cin >> qtdeAlunos;
    unsigned qtdeAtividades;
    cin >> qtdeAtividades;
    Heap heap(qtdeAlunos);
    Atividade atividade;
    string nome;
    unsigned matricula;
    for (unsigned i = 0; i < qtdeAlunos; ++i) {
        cin >> matricula >> nome;
        Aluno aluno(matricula, nome);
        for (unsigned i = 0; i < qtdeAtividades; ++i) {
            cin >> atividade.nota >> atividade.tentativas;
            aluno.InserirAtividade(atividade);
        }
        heap.Inserir(aluno);
    }
    Aluno alunoDestaque(heap.Retirar());
    cout << '[' << alunoDestaque.Matricula() << "] " << alunoDestaque.Nome() << endl;
    return 0;
}
