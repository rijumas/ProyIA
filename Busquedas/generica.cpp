#include <iostream>
#include <vector>
#include <map>

using namespace std;

template<class T>
class Nodo;

//Creacion del Nodo
template<class T>
class Nodo{
public:
    T valor;
    bool paso;
    vector<Nodo<T> *> conexos;
    Nodo(T v);
    ~Nodo();
};

//Creacion del Grafo
template<class T>
class Grafo{
public:
    map<T,Nodo<T>*> nodos;
    void addNodo(Nodo<T> *);
    void addArista(Nodo<T> *, Nodo<T> *);
    void Arbol(Nodo<T> *);
};

template<class T>
Nodo<T>::Nodo(T v){
    valor = v;
    paso = 1;
}

template<class T>
void Grafo<T>::addNodo(Nodo<T> * N){
    nodos[N->valor] = N;
}

template<class T>
void Grafo<T>::addArista(Nodo<T> * N1, Nodo<T> * N2){
    N1->conexos.push_back(N2);
    N2->conexos.push_back(N1);
}



int main(){
    Grafo<char> G;
    G.addNodo(new Nodo<char>('s'));
    for(char i = 'a'; i <= 'g'; i++){
        G.addNodo(new Nodo<char>((char) i));
    }
    G.addArista(G.nodos['s'], G.nodos['a']);
    G.addArista(G.nodos['a'], G.nodos['b']);
    G.addArista(G.nodos['b'], G.nodos['c']);
    G.addArista(G.nodos['s'], G.nodos['d']);
    G.addArista(G.nodos['d'], G.nodos['a']);
    G.addArista(G.nodos['b'], G.nodos['e']);
    G.addArista(G.nodos['d'], G.nodos['e']);
    G.addArista(G.nodos['e'], G.nodos['f']);
    G.addArista(G.nodos['f'], G.nodos['g']);
    return 0;
}