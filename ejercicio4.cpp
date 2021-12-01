#include <iostream>
#include <cassert>
#include <string>
using namespace std;

struct elemHeap
{
    int elem;
    int nivel;
};

class Heap
{
private:
	elemHeap*heap;
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
        elemHeap aux = heap[x];
        heap[x] = heap[y];
        heap[y] = aux;
    }

    void flotar(int nodo) {
        if(nodo != 1) {
            int nodoPadre = padre(nodo);
            if(heap[nodo].nivel < heap[nodoPadre].nivel) {
                intercambiar(nodo, nodoPadre);
                flotar(nodoPadre);
            } else if (heap[nodo].nivel == heap[nodoPadre].nivel && heap[nodo].elem < heap[nodoPadre].elem) {
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
            if(derecho < ultimoLibre && heap[derecho].nivel < heap[izquierdo].nivel) {
                hijoMenor = derecho;
            } else if (derecho < ultimoLibre && heap[derecho].nivel == heap[izquierdo].nivel && heap[derecho].elem < heap[izquierdo].elem) {
                hijoMenor = derecho;
            }
            if(heap[hijoMenor].nivel < heap[nodo].nivel) {
                intercambiar(hijoMenor, nodo);
                hundir(hijoMenor);
            } else if (heap[hijoMenor].nivel == heap[nodo].nivel && heap[hijoMenor].elem < heap[nodo].elem) {
                        intercambiar(hijoMenor, nodo);
                        hundir(hijoMenor);
                    }
        }
    }

public:

	Heap(int tamanio) {
        heap = new elemHeap[tamanio + 1];
        capacidad = tamanio;
        ultimoLibre = 1;
    }

    void insertar(elemHeap nuevoElemento) {
        if(!estaLleno()) {
            heap[ultimoLibre] = nuevoElemento;
            flotar(ultimoLibre);
            ultimoLibre++;
        }
    }

    elemHeap obtenerMinimo() {
        if(!esVacio()) {
            elemHeap ret = heap[1];
            heap[1] = heap[ultimoLibre - 1];
            ultimoLibre--;
            hundir(1);
            return ret;
        }
        elemHeap aux;
        aux.nivel = -1;
        aux.elem = -1;
        return aux;
    }

    bool esVacio() {
        return ultimoLibre == 1;
    }

    bool estaLleno() {
        return ultimoLibre == capacidad + 1;
    }

};

class ColaPrio 
{
    private:
        Heap*h;
    public:
    ColaPrio(int unTamanio)
    {
        h = new Heap(unTamanio);
    }

    // pre:
    // pos: retorna si la CP esta vacia
    bool esVacia(){
        return h->esVacio();
    }
    // pre:
    // pos: retorna si la CP esta llena
    bool estaLlena()
     {
         return h->estaLleno();
    }
    // pre: la CP no este llena
    // pos: inserta el elementos en la CP
    void push(elemHeap elemento)
    {
        assert(!h->estaLleno());
        h->insertar(elemento);
    }
    // pre: la CP no este vacia
    // pos: elimna el minimo elemento de la CP (el que tiene mayor prioridad) y lo retorna
    elemHeap pop()
    {
        assert(!h->esVacio());
        return h->obtenerMinimo();
    }
};

struct Arista
{
	int origen;
	int destino;
	Arista(int unOrigen, int unDestino) : origen(unOrigen), destino(unDestino){};
};

struct NodoLista 
	{
		Arista ari;
		NodoLista *sig;
		NodoLista(Arista &unaInfo, NodoLista *unSig) : ari(unaInfo) , sig(unSig){};
		NodoLista(Arista &unaInfo) : ari(unaInfo){};
	};

typedef NodoLista*ListaAristas;

class GrafoListaAdy {

private:
	ListaAristas *listaAdy;
	int V;
	int A;

	bool esDirigido;
	bool esPonderado;

	int *initGradoDeEntrada()
    {
        int *ret = new int[V + 1]();
        for (int i = 1; i <= V; i++)
        {
            ListaAristas adyacentes = this->adyacentesA(i);
            while (adyacentes != NULL)
            {
                Arista arista = adyacentes->ari;
                ret[arista.destino]++;
                adyacentes = adyacentes->sig;
            }
        }
        return ret;
    }

public:

	GrafoListaAdy(int cantV, bool esDirigido = true, bool esPonderado = false)
	{
		this->V = cantV;
		this->A = 0;
		this->esDirigido = esDirigido;
		this->esPonderado = esPonderado;
		listaAdy = new ListaAristas[cantV+1];
		for (int i = 1; i <= cantV; ++i)
		{
			listaAdy[i] = NULL;
		}

	}

	void agregarArista (int unOrigen, int unDestino)
	{
		Arista a1 (unOrigen,unDestino);
		listaAdy[unOrigen] = new NodoLista(a1, listaAdy[unOrigen]);
		if (!esDirigido) {
			Arista a2 (unDestino,unOrigen);
			listaAdy[unDestino] = new NodoLista(a2, listaAdy[unDestino]);
		}
        this->A++;
	}

	ListaAristas adyacentesA (int v) {
		ListaAristas ret = NULL;
		ListaAristas aux = listaAdy[v];
		while(aux != NULL) {
            Arista aristaAuxiliar = aux->ari;
            ret = new NodoLista(aristaAuxiliar, ret);
            aux = aux->sig;
        }
        
        return ret;
    }

    void OT()
    {
        int *gradoEntrada = initGradoDeEntrada(); // inicializa el grado de entrada de cada uno de ls vertices del grafo
        ColaPrio*cola = new ColaPrio(V);
        int nivel = 0;
        elemHeap aux, vertice;
        for (int v = 1; v <= V; v++) // encolo todos los vertices de grado de entrada 0
            if (gradoEntrada[v] == 0) {
                aux.elem = v;
                aux.nivel = 0;
                cola->push(aux);
            }
        while (!cola->esVacia())
        {
            vertice = cola->pop();
            cout << vertice.elem << endl;
            nivel = vertice.nivel + 1;
            // recorrer los adyecentes al vertice
            ListaAristas adyacentes = this->adyacentesA(vertice.elem);
            while (adyacentes != NULL)
            {
                Arista a = adyacentes->ari;
                int w = a.destino;
                gradoEntrada[w]--; // quito un grado de entrada
                if (gradoEntrada[w] == 0)
                {
                    aux.elem = w;
                    aux.nivel = nivel;
                    cola->push(aux); // el vertice w esta listo para imprimir
                }
                adyacentes = adyacentes->sig;
            }
        }
    }
};

int main()
{
    int v;
	cin >> v;
	GrafoListaAdy *grafo = new GrafoListaAdy(v,true,false);
	int a;
	cin >> a;
	for (int i = 1; i <= a; ++i)
	{	
		int o,d;
		cin >> o >> d;
		grafo->agregarArista(o,d);
	}
	grafo->OT();
    return 0;
}