﻿#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<fstream>
//benes
const int PRIMO = 37;
const int TAM = 7;

using namespace std;

template <class TYPE>
class No{
private:
    TYPE data;
public:
    No<TYPE> *proximoPtr;

    No(const TYPE &);
    TYPE getData()const;
};

template<class TYPE>
No<TYPE>::No(const TYPE &info)
{
    data = info;
    proximoPtr = 0;
}

template<class TYPE>
TYPE No<TYPE>::getData()const{
    return data;
}

template<class TYPE>
class Lista{
public:
    Lista();
    ~Lista();

    int getTamanho();
//    void inserirFrente(const TYPE &);
    void inserirAtras(const TYPE &);
    bool removerFrente();
    bool removerAtras();
    void print()const;
    string busca(const string &);
    string get(const int &);

private:
    int tamanho;
    bool estaVazia()const;

    No<TYPE> *primeiroPtr;
    No<TYPE> *ultimoPtr;

    No<TYPE> *getNovoNo(const TYPE &);
};


template<class TYPE>
Lista<TYPE>::Lista(){
    tamanho = 0;
    primeiroPtr = 0;
    ultimoPtr = 0;
}

template<class TYPE>
Lista<TYPE>::~Lista(){
    if(!estaVazia()){
        No <TYPE> *atualPtr = primeiroPtr;
        No <TYPE> *temporarioPtr;

        while(atualPtr != 0){
            temporarioPtr = atualPtr;
            atualPtr = atualPtr->proximoPtr;
            delete temporarioPtr;
        }
    }
}

template<class TYPE>
int Lista<TYPE>::getTamanho(){
    return tamanho;
}

// template<class TYPE>
// void Lista<TYPE>::inserirFrente(const TYPE &valor){
//     No<TYPE> *novoPtr = getNovoNo(valor);
//
//     if(estaVazia()){
//         primeiroPtr = ultimoPtr = novoPtr;
//     }
//     else{
//         tamanho += 1;
//         novoPtr->proximoPtr = primeiroPtr;
//         primeiroPtr = novoPtr;
//     }
// }

template<class TYPE>
void Lista<TYPE>::inserirAtras(const TYPE &valor){
    No<TYPE> *novoPtr = getNovoNo(valor);

    //Lista está vazia
    if(estaVazia()){
        primeiroPtr = ultimoPtr = novoPtr;
    }
    else{
        tamanho += 1;
        ultimoPtr-> proximoPtr = novoPtr;
        ultimoPtr = novoPtr;
    }
}

template<class TYPE>
bool Lista<TYPE>::removerFrente(){

    if(estaVazia()){
        return false;
    }
    else{
        No<TYPE> *temporarioPtr = primeiroPtr;

        if(primeiroPtr == ultimoPtr){
            primeiroPtr = ultimoPtr = 0;
        }
        else{
            primeiroPtr = primeiroPtr->proximoPtr;
        }

        tamanho -= 1;
        delete temporarioPtr;
        return true;

    }
}

template<class TYPE>
bool Lista<TYPE>::removerAtras(){
    if(estaVazia()){
        return false;
    }
    else{
        No<TYPE> *temporarioPtr = ultimoPtr;
        if(primeiroPtr == ultimoPtr){
            primeiroPtr = ultimoPtr = 0;
        }
        else{
            No<TYPE> *atualPtr = primeiroPtr;

            while(atualPtr->proximoPtr != ultimoPtr){
                atualPtr = atualPtr->proximoPtr;
            }

            ultimoPtr = atualPtr;
            atualPtr->proximoPtr = 0;
        }

        tamanho -= 1;
        //valor = temporarioPtr->getData();
        delete temporarioPtr;
        return true;

    }
}

template<class TYPE>
bool Lista<TYPE>::estaVazia()const{
    return primeiroPtr == 0;
}

template<class TYPE>
No<TYPE> *Lista<TYPE>::getNovoNo(const TYPE &valor){
    return new No<TYPE>(valor);
}

template<class TYPE>
void Lista<TYPE>::print()const{
    if(estaVazia()){
        cout<< "A lista esta vazia"<<"\n";
        return;
    }

    No<TYPE> *atualPtr = primeiroPtr;

    while(atualPtr != 0){
        cout << atualPtr->getData();
        atualPtr = atualPtr->proximoPtr;

    }
}

template<class TYPE>
string Lista<TYPE>::busca(const string &chaveRecebida){

    No<TYPE> *atualPtr = primeiroPtr;


    while(atualPtr != 0){
        if(atualPtr->getData() == chaveRecebida){
            return atualPtr->getData();
        }
        atualPtr = atualPtr->proximoPtr;
    }

    return "-1";

}

template<class TYPE>
string Lista<TYPE>::get(const int &indice){

    No<TYPE> *atualPtr = primeiroPtr;

    int contador = 0;

    while(atualPtr != 0){
        if(contador == indice){
            return atualPtr->getData();
        }
        contador += 1;
        atualPtr = atualPtr->proximoPtr;
    }

    return "-1";
}

// struct Dupla{
//     string simbolo;
//     string chave;
// };

// int strParaInt(string chave){
//     int acumulador = 0;
//     int chaveTam = strlen(chave.c_str());
//     for(int i = 0; i < chaveTam; i++){
//         acumulador += (int)chave[i];
//     }
//     acumulador *= PRIMO;
//     return acumulador;
// }
//
// int h(string chave){
//
//     return strParaInt(chave) % TAM;
// }

template <class TYPE>
class TabelaHash{
private:
    Lista<TYPE> th[TAM];
public:
    TabelaHash();
    ~TabelaHash(){};

    int hash(string);
    void inserirElemento(const string &);
    string buscarElemento(const string &chave);
};

template<class TYPE>
TabelaHash<TYPE>::TabelaHash(){
    for(int i = 0; i < TAM; i++){
        Lista<TYPE> lista;
        th[i] = lista;
    }
}

template<class TYPE>
int TabelaHash<TYPE>::hash(string chave){
    int acumulador = 0;

    int chaveTam = strlen(chave.c_str());
    for(int i = 0; i < chaveTam; i++){
        acumulador += (int)chave[i];
    }
    acumulador *= PRIMO;

    return acumulador % TAM;
}

template<class TYPE>
void TabelaHash<TYPE>::inserirElemento(const string &data){
    int i = hash(data);
    th[i].inserirAtras(data);
}

template<class TYPE>
string TabelaHash<TYPE>::buscarElemento(const string &chave){
    string chaveStr = chave;
    int i = hash(chave);
    return th[i].busca(chaveStr);
}

template <class TYPE>
class NoArvore{
private:
    TYPE data;
    int altura;
public:
    NoArvore <TYPE> *ptrEsquedo;
    NoArvore <TYPE> *ptrDireito;

    NoArvore(const TYPE &d){
        ptrEsquedo = 0;
        data = d;
        ptrDireito = 0;
    }

    TYPE getData() const{
        return data;
    }
};


template <class TYPE>
class Arvore{
public:
    Arvore();
    ~Arvore(){}

    void insereNo(const TYPE &);
    TYPE busca(const TYPE &);
    // void percorrePreOrdem () const;
    // void percorreCentral () const;
    // void percorrePosOrdem () const;

private:
    NoArvore <TYPE> *ptrRaiz;
    TYPE ajudanteDeBusca (NoArvore <TYPE> **, const TYPE &);
    void ajudanteDeInsereNo (NoArvore <TYPE> **, const TYPE &);
    // void ajudantePercorrePreOrdem (NoArvore <TYPE> *) const;
    // void ajudantePercorreCentral (NoArvore <TYPE> *) const;
    // void ajudantePercorrePosOrdem (NoArvore <TYPE> *) const;
};

template <class TYPE>

Arvore<TYPE>::Arvore(){
    ptrRaiz = 0;
}

template <class TYPE>
TYPE Arvore<TYPE>::busca(const TYPE &item){
    return ajudanteDeBusca(&ptrRaiz, item);
}

template <class TYPE>
TYPE Arvore<TYPE>::ajudanteDeBusca(NoArvore<TYPE> **ptr, const TYPE &item){
    if(*ptr == 0){
        return "-1";
        cout << "item nao encontrado";
    }
    if(item == (*ptr)->getData()){
        return (*ptr)->getData();
    }

    else{
        if(item < (*ptr)->getData()){
            ajudanteDeBusca(&((*ptr)->ptrEsquedo), item);
        }
        else{
            if(item > (*ptr)->getData()){
                ajudanteDeBusca(&((*ptr)->ptrDireito), item);
            }
        }
    }
}




template <class TYPE>
void Arvore<TYPE>::insereNo(const TYPE &valor){
    ajudanteDeInsereNo(&ptrRaiz, valor);
}

template <class TYPE>
void Arvore<TYPE>::ajudanteDeInsereNo(NoArvore<TYPE> **ptr, const TYPE &valor){
    if(*ptr == 0){
        *ptr = new NoArvore<TYPE>(valor);

    }
    else{
        if(valor < (*ptr)->getData()){
            ajudanteDeInsereNo(&((*ptr)->ptrEsquedo), valor);
        }
        else{
            if(valor > (*ptr)->getData()){
                ajudanteDeInsereNo(&((*ptr)->ptrDireito), valor);
            }
            else{
                cout << valor << " -duplicata" << endl;
            }
        }
    }
}

// template <class TYPE>
// void Arvore<TYPE>::percorrePreOrdem() const{
//     ajudantePercorrePreOrdem(ptrRaiz);
// }
//
// template <class TYPE>
// void Arvore<TYPE>::ajudantePercorrePreOrdem(NoArvore<TYPE> *ptr) const{
//     if(ptr != 0){
//         cout << ptr->data<<' ';
//         ajudantePercorrePreOrdem(ptr->ptrEsquedo);
//         ajudantePercorrePreOrdem(ptr->ptrDireito);
//     }
// }
//
// template <class TYPE>
// void Arvore<TYPE>::percorreCentral() const{
//     ajudantePercorreCentral(ptrRaiz);
// }
//
// template <class TYPE>
// void Arvore<TYPE>::ajudantePercorreCentral(NoArvore<TYPE> *ptr)const{
//     if(ptr != 0){
//         ajudantePercorreCentral(ptr->ptrEsquedo);
//         cout << ptr -> data << ' ';
//         ajudantePercorreCentral(ptr->ptrDireito);
//     }
// }
//
// template <class TYPE>
// void Arvore<TYPE>::percorrePosOrdem() const{
//     ajudantePercorrePosOrdem(ptrRaiz);
// }
//
// template <class TYPE>
// void Arvore<TYPE>::ajudantePercorrePosOrdem(NoArvore<TYPE> *ptr)const{
//     if(ptr != 0){
//         ajudantePercorrePosOrdem(ptr->ptrEsquedo);
//         ajudantePercorrePosOrdem(ptr->ptrDireito);
//         cout << ptr -> data << ' ';
//     }
// }

int main(){

    //int valor;
    string linha;
    Arvore<string> arvore;

    ifstream arquivo("teste.txt");
    if (!arquivo.is_open()){
        cout << "Falha na abertura do arquivo" << endl;
        exit(1);
    }
    else{
        while (getline (arquivo, linha)) {
            arvore.insereNo(linha);
            cout << linha << '\n';
        }
    }
    cout << "\nResultado da busca: " << arvore.busca("chave") << endl;

    arquivo.close();


    //cout << "insira 10 valores inteiros\n";

    // for(int i = 0; i < 10; i++){
    //     cin >> valor;
    // }


    // cout << "\nPre ordem\n";
    // arvoreInt.percorrePreOrdem();
    // cout << "\n\nCentral\n";
    // arvoreInt.percorreCentral();
    // cout << "\n\nPos ordem\n";
    // arvoreInt.percorrePosOrdem();
return 0;

}
