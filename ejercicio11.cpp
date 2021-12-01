#include <iostream>
#include <cassert>
#include <string>
using namespace std;

void sumaSinResta (int input[], int tamanio) {
    int suma[tamanio];
    int sumaPrevios = 0;
    int sumaPosteriores = 0;
    for (int i = 0; i < tamanio; ++i) {
        suma[i] = sumaPrevios;
        sumaPrevios += input[i];
    }
    for (int i = tamanio - 1; i >= 0; --i) {
        suma[i] += sumaPosteriores;
        sumaPosteriores += input[i];
    }
    for (int i = 0; i < tamanio; i++) {
        cout << suma[i] << endl;
    }
}

int main(){
    int n;
    cin >> n;
    int input[n];
    for (int i = 0; i < n; i++) {
        cin >> input[i];
    }
    sumaSinResta(input,n);
    return 0;
}