#include <iostream>
#include <unordered_set>
#include <stack>
#include <vector>

using namespace std;
struct nodo {
    string id;
    unordered_set<string> recorrido;
    vector<nodo*> lista;
    nodo() {
        id = "";
    }
    nodo(string id_) {
        id = id_;
    }
    void delet() {
        id = "";
    }

};

void Profundidad(vector<vector<nodo*>> mt, int ini, int fin){
    stack<nodo*> busqueda;
    nodo * first = mt[ini/20][ini%20];
    first->recorrido.insert(first->id);
    busqueda.push(first);

    while(busqueda.top()->id != mt[fin/20][fin%20]->id && !busqueda.empty()){
        nodo * nodoAnterior = busqueda.top();
        busqueda.pop();
        for(int i = nodoAnterior->lista.size()-1; i > -1;i--){
            if(nodoAnterior->lista[i]->id == "" || nodoAnterior->recorrido.count(nodoAnterior->lista[i]->id) == 1) continue;
            nodo * nuevo = nodoAnterior->lista[i];
            nuevo->recorrido = nodoAnterior->recorrido;
            nuevo->recorrido.insert(nuevo->id);
            busqueda.push(nuevo);
        }
    }
    if(busqueda.empty()){
        cout << "No hay camino" << endl;
        return;
    }
    nodo * result = busqueda.top();
    for(auto it = result->recorrido.begin(); it != result->recorrido.end(); it++){
        cout << *it << " " << endl;
    }
}

int main(){
    return 0;
}