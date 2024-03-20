#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;

struct nodo {
    string id;
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

vector<int> generarNumerosAleatoriosUnicos(int minimo, int maximo, int cantidad) {

    if (cantidad > maximo - minimo + 1) {
        cout << "Error: Cantidad de numeros a generar excede el rango posible.\n";
        return {};
    }

    mt19937 generador(time(0));

    vector<int> numeros;

    for (int i = minimo; i <= maximo; ++i) {
        numeros.push_back(i);
    }

    shuffle(numeros.begin(), numeros.end(), generador);

    numeros.resize(cantidad);

    return numeros;
}

void borrar(vector<vector<nodo*>> &mt) {
    vector<int> num;
    int porcentaje, profe;
    cin >> profe;
    porcentaje = profe * 4;
    num = generarNumerosAleatoriosUnicos(0, 399, porcentaje);
    
    for (int i = 0; i < num.size(); i++) {
        //cout << num[i] << " ";
        (*(mt[num[i] / 20][num[i] % 20])).delet();
    }

    cout << endl;
}

/*void conectar(vector<vector<nodo*>>& mt) {
    //laterales
    (*(mt[10][10])).lista.push_back(mt[10][11]);
    (*(mt[10][10])).lista.push_back(mt[10][9]);
    //sup e infe
    (*(mt[10][10])).lista.push_back(mt[9][10]);
    (*(mt[10][10])).lista.push_back(mt[11][10]);
    //diago sup
    (*(mt[10][10])).lista.push_back(mt[9][9]);
    (*(mt[10][10])).lista.push_back(mt[9][11]);
    //diago inf
    (*(mt[10][10])).lista.push_back(mt[11][9]);
    (*(mt[10][10])).lista.push_back(mt[11][11]);
    for (int i;; i++) {

    }
}*/

int main(){
    vector<vector<nodo*>> mt(20, vector<nodo*>(20));
    int j = 0;
    for (int i = 0;i<20; i++) {
        for (int k = 0;k<20; k++) {
            mt[i][k] = new nodo(to_string(j));
            j++;
        }
    }
    for (int i = 0; i < 20; i++) {
        for (int k = 0; k < 20; k++) {
            cout << (*(mt[i][k])).id << " ";
        }
        cout << endl;
    }
    borrar(mt);
    for (int i = 0; i < 20; i++) {
        for (int k = 0; k < 20; k++) {
            cout << (*(mt[i][k])).id << " ";
        }
        cout << endl;
    }
}

