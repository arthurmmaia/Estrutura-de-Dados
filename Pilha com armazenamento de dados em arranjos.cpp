#include <iostream>

using namespace std;

typedef int Dado; // para facilitar a troca de int para outro tipo
 
// pilha implementada em arranjo 
class pilhav {
    private:
        int mCapacidade;
        Dado *mDados;
        int mTamanho;
        int mPosTopo;
    public:
        pilhav(unsigned cap);
        ~pilhav();
        void empilha(Dado valor);
        Dado desempilha();
        Dado espia(); // acessa elemento do topo, mas não retira
        void depura(); // imprime os dados do vetor da pilha sem removê-los (desempilhar)
        void info();  // imprime informações da pilha (tamanho e  posição do topo)
};


pilhav::pilhav(unsigned cap)
	:	mCapacidade( cap),
		mDados (new Dado [cap]),
		mTamanho(0),
		mPosTopo(-1)
{
}

pilhav:: ~pilhav (){
	delete[] mDados;
}

void pilhav::empilha (Dado valor){
	if( mTamanho< mCapacidade){
		mPosTopo++;
		mDados[mPosTopo]= valor;
		mTamanho++;
	}
}

Dado pilhav:: desempilha(){
	
	Dado aux;
	
	aux= mDados[mPosTopo];
	
	mPosTopo--;
	
	mTamanho--;
	
	return aux;
}

Dado pilhav::espia(){
	Dado elemento;
	
	elemento= mDados[mPosTopo];
	
	return elemento;	
}

void pilhav::depura(){
	
	Dado pos_depura;
	
	pos_depura= mPosTopo;
	
	for (int x=0; x<=pos_depura; ++x){
		cout<< mDados[x]<< " "; 
	}
	cout<< endl;
}

void pilhav::info(){
	
	cout<< mTamanho<< " "<< mPosTopo<< endl;
}


int main(){
	
	Dado num;
	
	pilhav pilha(20);
	
	for( int i=0; i<5; ++i){
		cin>> num;
		pilha.empilha(num);
	}
	
	for( int i=0; i<3; ++i){
		cout<< pilha.desempilha()<< " ";
	}
	cout<<endl;
	
	for( int i=0; i<4; ++i){
		cin>> num;
		pilha.empilha(num);
	}
	
		for( int i=0; i<3; ++i){
		cout<< pilha.desempilha()<< " ";
	}
	cout<<endl;
	
	cout<< pilha.espia()<< endl;
	
	pilha.depura();
	
	pilha.info();
	
return 0;
}
