#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cmath>
#include <utility>
#include <thread>
#include <map>
#include <algorithm>

using namespace std;

struct nodo {
    string id;
    vector<pair<nodo*, float>> listaConexos;
    map <string, bool> recorrido;
    double dist_euc;
    vector<nodo*> rflags;
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

void makeConnection(vector<vector<nodo*>>& matriz, int inicio, int fin) {
    for (int i = inicio; i < fin; i++) {
        for (int j = 0; j < 20; j++) {
            if (j < 19)
                matriz[i][j]->listaConexos.push_back(make_pair(matriz[i][j + 1], 10.0));
            if (j > 0)
                matriz[i][j]->listaConexos.push_back(make_pair(matriz[i][j - 1], 10.0));
            if (i > 0)
                matriz[i][j]->listaConexos.push_back(make_pair(matriz[i - 1][j], 10.0));
            if (i < 19)
                matriz[i][j]->listaConexos.push_back(make_pair(matriz[i + 1][j], 10.0));
            if (j < 19 && i < 19)
                matriz[i][j]->listaConexos.push_back(make_pair(matriz[i + 1][j + 1], 14.14));
            if (i > 0 && j < 19)
                matriz[i][j]->listaConexos.push_back(make_pair(matriz[i - 1][j + 1], 14.14));
            if (j > 0 && i > 0)
                matriz[i][j]->listaConexos.push_back(make_pair(matriz[i - 1][j - 1], 14.14));
            if (j > 0 && i < 19)
                matriz[i][j]->listaConexos.push_back(make_pair(matriz[i + 1][j - 1], 14.14));
        }
    }
}


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

void calc_dis_eu(vector<vector<nodo*>>& mt, int fin) {
    ;
    for (int i = 0; i < 400; i++) {
        if ((*(mt[i / 20][i % 20])).id != "") {
            (*(mt[i / 20][i % 20])).dist_euc = sqrt(pow((i / 20) - (fin / 20), 2) + pow((i % 20) - (fin % 20), 2)) * 10;
        }
    }
}

void detect_fin(nodo*& ini, int fin, vector<nodo*>& camino, bool& S) {
    int cont = 0;
    for (int i = 0; i < ini->listaConexos.size(); i++) {
        if (ini->listaConexos[i].first->id != "") {
            cont++;
        }
    }
    if (ini->rflags.size() == cont || ini->id == to_string(fin)) {
        S = 0;
    }
    cont = 0;
}

bool compararPorDistEuc(const pair<nodo*, float>& a, const pair<nodo*, float>& b) {
    return a.first->dist_euc > b.first->dist_euc;
}

void hill(vector<vector<nodo*>>& mt, int ini, int fin, vector<nodo*>& camino) {
    nodo* start = mt[ini / 20][ini % 20];
    camino.push_back(start);
    if (ini == fin) {
        return;
    }
    bool S = 1;
    while (camino[camino.size() - 1]->id != to_string(fin) && S == 1) {
        nodo* minNode = camino.back();
        sort(camino.back()->listaConexos.begin(), camino.back()->listaConexos.end(),compararPorDistEuc);
        for (int i = 0; i < camino[camino.size() - 1]->listaConexos.size(); i++) {
            bool f = 1;
            if (camino.back()->listaConexos[i].first->id != "" /* && camino.back()->listaConexos[i].first->dist_euc > minNode->dist_euc*/) {
                for (int j = 0; j < camino.back()->rflags.size(); j++) {
                    if (camino.back()->listaConexos[i].first->id == camino.back()->rflags[j]->id) {
                        f = 0;
                        break;
                    }
                }
                if (f == 1)
                    minNode = camino.back()->listaConexos[i].first;
            }
            /*else if (camino.back()->listaConexos[i].first->id != "" && camino.back()->listaConexos[i].first->dist_euc < minNode->dist_euc) {
                for (int j = 0; j < camino.back()->rflags.size(); j++) {
                    if (camino.back()->listaConexos[i].first->id == camino.back()->rflags[j]->id) {
                        f = 0;
                        break;
                    }
                }
                if (f == 1)
                    minNode = camino.back()->listaConexos[i].first;
            }*/
        }
        bool p = 1;
        for (int i = 0; i < camino.size(); i++) {
            if (minNode->id == camino[i]->id) { 
                camino.back()->rflags.push_back(minNode);
                p = 0;
                break;
            }
        }
        if (p == 1) {
            camino.push_back(minNode);
        }
        else {
            camino.pop_back();
            camino.back()->rflags.push_back(minNode);
        }
        detect_fin(start, fin, camino, S);
    }
    return;
}

void borrar(vector<vector<nodo*>>& mt) {
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


int main() {
    vector<vector<nodo*>> mt(20, vector<nodo*>(20));
    int j = 0;
    for (int i = 0; i < 20; i++) {
        for (int k = 0; k < 20; k++) {
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
    //makeConnection(mt,0,20);
    thread T1(makeConnection, ref(mt), 0, 5);
    thread T2(makeConnection, ref(mt), 5, 10);
    thread T3(makeConnection, ref(mt), 10, 15);
    thread T4(makeConnection, ref(mt), 15, 20);
    T1.join();
    T2.join();
    T3.join();
    T4.join();
    borrar(mt);
    for (int i = 0; i < 20; i++) {
        for (int k = 0; k < 20; k++) {
            cout << (*(mt[i][k])).id << " ";
        }
        cout << endl;
    }
    int ini, fin;
    cout << "Escribe id de nodo inicial: ";
    cin >> ini;
    cout << endl;
    cout << "Escribe id de nodo final: ";
    cin >> fin;
    cout << endl;
    calc_dis_eu(mt, fin);
    cout << (*(mt[ini / 20][ini % 20])).dist_euc << endl;
    vector<nodo*> camino;
    hill(mt, ini, fin, camino);
    if (camino.size() == 1 && camino.back()->id != to_string(fin)) {
        cout << "No hay camino" << endl;
    }
    else {
        for (int o = 0; o < camino.size(); o++) {
            cout << camino[o]->id << " ";
        }
    }
    return 0;
}

