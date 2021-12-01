#include <iostream>
using namespace std;

struct NodoLista
{
    int elem;
    NodoLista *sig;
    NodoLista(int unElem) : elem(unElem), sig(0){};
    NodoLista(int unElem, NodoLista *unSig) : elem(unElem), sig(unSig){};
};

struct elemArray
{
    int elem;
    int lista;
    int pos;
};

typedef NodoLista *Lista;

class Heap
{
private:
	elemArray*heap;
	int ultimoLibre;
	int capacidad;

	int padre(int nodo) {
        return nodo/2;
    }

    int der(int nodo) {
        return nodo * 2 + 1;
    }

    int izq(int nodo) {
        return nodo * 2;
    }

    void intercambiar(int x, int y) {
        elemArray aux = heap[x];
        heap[x] = heap[y];
        heap[y] = aux;
    }

    void flotar(int nodo) {
        if(nodo != 1) {
            int nodoPadre = padre(nodo);
            if(heap[nodo].elem < heap[nodoPadre].elem) {
                intercambiar(nodo, nodoPadre);
                flotar(nodoPadre);
            }
        }
    }

    void hundir(int nodo) {
        if(izq(nodo) < ultimoLibre) {
            int izquierdo = izq(nodo);
            int derecho = der(nodo);
            int hijoMenor = izquierdo;
            if(derecho < ultimoLibre && heap[derecho].elem < heap[izquierdo].elem) {
                hijoMenor = derecho;
            }
            if(heap[hijoMenor].elem < heap[nodo].elem) {
                intercambiar(hijoMenor, nodo);
                hundir(hijoMenor);
            }
        }
    }

public:

	Heap(int tamanio) {
        heap = new elemArray[tamanio + 1];
        capacidad = tamanio;
        ultimoLibre = 1;
    }

    void insertar(elemArray nuevoElemento) {
        if(!estaLleno()) {
            heap[ultimoLibre] = nuevoElemento;
            flotar(ultimoLibre);
            ultimoLibre++;
        }
    }

    elemArray obtenerMinimo() {
        if(!esVacio()) {
            elemArray ret = heap[1];
            heap[1] = heap[ultimoLibre - 1];
            ultimoLibre--;
            hundir(1);
            return ret;
        }
        elemArray aux;
        aux.elem = -1;
        aux.lista = -1;
        aux.pos = -1;
        return aux;
    }

    bool esVacio() {
        return ultimoLibre == 1;
    }

    bool estaLleno() {
        return ultimoLibre == capacidad + 1;
    }

};

int main()
{
	int k,largo;
	cin >> k;
	int** listas = new int*[k];
	for (int i = 0; i < k; ++i)
	{
		cin >> largo;
		listas[i] = new int[largo+1];
        listas[i][0] = largo+1;
		for (int j = 1; j < largo+1; ++j)
		{
			cin >> listas[i][j];
		}
	}
	Heap *h = new Heap(k);
    elemArray aux,auxsig;
	for (int i = 0; i < k; ++i)
	{  
        aux.elem = listas[i][1];
        aux.lista = i;
        aux.pos = 1;
		h->insertar(aux);
	}
	while(!h->esVacio()){
        aux = h->obtenerMinimo();
        cout << aux.elem << endl;
        if (aux.pos < listas[aux.lista][0] - 1) {
            auxsig.elem = listas[aux.lista][aux.pos + 1];
            auxsig.lista = aux.lista;
            auxsig.pos = aux.pos + 1;
            h->insertar(auxsig);
        }
    }
	return 0;
}