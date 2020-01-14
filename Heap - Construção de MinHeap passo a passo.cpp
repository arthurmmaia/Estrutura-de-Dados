#include <iostream>

using namespace std;

typedef int Dado;

class Heap{
	protected:
	int mTamanho;
	Dado* mVetValores;
	
	public:
	Heap(Dado vetor[], int cap);
	~Heap();
	void CorrigeDescendo(int pos);
	void Corrige(int tamanho);
	unsigned Direito(int pos){ return (2*pos)+2;};
	unsigned Esquerdo(int pos){ return(2*pos)+1;};
	void Imprime();
};

Heap::Heap(Dado vetor[], int tamanho)
: 	mTamanho(tamanho),
	mVetValores(new Dado[tamanho])
{
	for(int i=0; i<tamanho; ++i){
		mVetValores[i]=vetor[i];
	}
}

Heap::~Heap(){
	delete[] mVetValores;
}


void Heap::CorrigeDescendo(int pos){
	int esquerdo, direito, fim, menor;
	menor= pos;
	esquerdo= Esquerdo(pos);
	direito= Direito(pos);
	fim= mTamanho-1;
	
	if ((esquerdo<= fim) and (mVetValores[esquerdo]>mVetValores[pos])){
		menor=esquerdo;
	}
	if(( direito<=fim) and ( mVetValores[direito]>mVetValores[menor])){
		menor=direito;
	}
	if( menor!=pos){
		swap(mVetValores[menor], mVetValores[pos]);
		CorrigeDescendo(menor);
	}
}

void Heap::Imprime(){
	for(int j=0; j<mTamanho; ++j){
			cout<< mVetValores[j]<< " ";			
		}
		cout<<endl;
}

void Heap::Corrige(int tamanho){
	int meio= (tamanho/2)-1;
	for(int i=meio; i>=0; --i){
		CorrigeDescendo(i);
		cout<< i<< ':'<< " ";
		Imprime();
	}
	
}

int main(){
	int tam;
	
	cin>>tam;
	
	Dado vet[tam];
	
	for(int i=0; i<tam; ++i){
		cin>> vet[i];
	}
	
	Heap meuHeap(vet, tam);
	
	meuHeap.Corrige(tam);
	
return 0;
}
