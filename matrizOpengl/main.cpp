#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;

struct nodo {
    string id;
    //vector<nodo> lista;
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
        cerr << "Error: Cantidad de números a generar excede el rango posible.\n";
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

void borrar(vector<vector<nodo>> &mt) {
    vector<int> num;
    int porcentaje, profe;
    cin >> profe;
    porcentaje = profe * 4;
    num = generarNumerosAleatoriosUnicos(0, 399, porcentaje);
    
    for (int i = 0; i < num.size(); i++) {
        cout << num[i] << " ";
        mt[num[i] / 20][num[i] % 20].delet();
    }

    cout << endl;
}

int main(){
    vector<vector<nodo>> mt(20);
    for (int i = 0;i<20; i++) {
        for (int k = 0+(20*i);k<(20*(i+1)); k++) {
            nodo* x = new nodo(to_string(k));
            mt[i].push_back(*x);
        }
    }
    for (int i = 0; i < 20; i++) {
        for (int k = 0; k < 20; k++) {
            cout << mt[i][k].id << " ";
        }
        cout << endl;
    }
    borrar(mt);
    for (int i = 0; i < 20; i++) {
        for (int k = 0; k < 20; k++) {
            cout << mt[i][k].id << " ";
        }
        cout << endl;
    }
}

