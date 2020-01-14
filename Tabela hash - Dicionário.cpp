#include <iostream>
#include <string>

using namespace std;

const int UMPRIMO = 39;

int funcaoHash(string s) {
    int h = 0;
    for (unsigned i = 0; i < s.length(); i++)
        h = (UMPRIMO * h + s[i]) % 23;
    return h;
}

class noh {
    friend class tabelaHash;
    private:
        string palavra;
        string significado;
        noh* proximo = NULL;
    public:
        noh(string c, string v) {
            palavra = c;
            significado = v;
        }
};

class tabelaHash {
    private:
        // vetor de ponteiros de nós
        noh** elementos;
        int capacidade;
    public:
        // construtor padrão
        tabelaHash(int cap = 100);
        // destrutor
        ~tabelaHash();
        // insere um valor v com chave c
        void insere(string c, string v);
        // recupera um valor associado a uma dada chave
        void recupera(string c);
        // percorrendo a tabela hash (para fins de debug)
        void percorre();
};

// construtor padrão
tabelaHash::tabelaHash(int cap) {
    elementos = new noh*[cap];
    capacidade = cap;
    for (int i = 0; i < cap; i++)
        elementos[i] = NULL;
}

// destrutor
tabelaHash::~tabelaHash() {
    for (int i=0; i < capacidade; i++) {
        noh* atual = elementos[i];
        // percorre a lista removendo todos os nós
        while (atual != NULL) {
            noh* aux = atual;
            atual = atual-> proximo;
            delete aux;
        }
    }
    delete[] elementos;
}

// Insere um valor v com chave c.
void tabelaHash::insere(string c, string v) {
    //  CODIGO A SER DESENVOLVIDO
    noh* novo= new noh(c, v);
    int hash=funcaoHash(c);
    if(elementos[hash]==NULL){
        elementos[hash]=novo;
    }
    else{
        noh* busca= elementos[hash];
        while(busca->proximo!= NULL){
            busca= busca->proximo;
        }
        busca->proximo= novo;
    }
}

// recupera um valor associado a uma dada chave
void tabelaHash::recupera(string c) {
    int h;
    h = funcaoHash(c);

    if ((elementos[h] != NULL) and (elementos[h]->palavra == c)) {
        cout<<"["<<elementos[h]->palavra<<"] =>"<< elementos[h]->significado<<endl;
    } else {
        noh* atual = elementos[h];

        while ((atual != NULL) and (atual->palavra != c)) {
            atual = atual->proximo;
        }

        if ((atual != NULL) and (atual->palavra == c)) {
            cout<<"["<<atual->palavra<<"]=>"<< atual->significado<<endl;
        } else {
           cout<<"["<<c<<"] =>"<< " NULL"<<endl;
        }
    }
}


int main( ) {
    tabelaHash th(23);
    int qtdade;
    string palavra;
    string significado;

    // insercao na tabela
    cin >> qtdade;
    for (int i=0; i < qtdade; i++) {
        cin >> palavra;
        getline(cin, significado);
        th.insere(palavra,significado);
    }

	cin>>palavra;
    // recupera valores
    while(palavra!="-1"){
		th.recupera(palavra);
		cin >> palavra;
	}


    return 0;
}
