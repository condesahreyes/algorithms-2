#include <iostream>
#include <cassert>
#include <string>
using namespace std;

struct Arista
{
	int origen;
	int destino;
    int peso;
	Arista(int unOrigen, int unDestino, int unPeso) : origen(unOrigen), destino(unDestino), peso(unPeso){};
};

struct NodoLista 
	{
		Arista ari;
		NodoLista *sig;
		NodoLista(Arista &unaInfo, NodoLista *unSig) : ari(unaInfo) , sig(unSig){};
		NodoLista(Arista &unaInfo) : ari(unaInfo){};
	};

typedef NodoLista*ListaAristas;

#define INF INT_MAX;

class GrafoListaAdy {

private:
	ListaAristas *listaAdy;
	int V;
	int A;

	bool esDirigido;
	bool esPonderado;

    bool *initVisitados()
    {
        bool *ret = new bool[V + 1];
        for (int i = 1; i <= V; i++)
        {
            ret[i] = false;
        }
        return ret;
    }


        int *initCostos(int origen)
    {
        int *ret = new int[V + 1];
        for (int i = 1; i <= V; i++)
        {
            ret[i] = i == origen ? 0 : INF;
        }
        return ret;
    }

    int *initVengo()
    {
        int *ret = new int[V + 1];
        for (int i = 1; i <= V; i++)
        {
            ret[i] = -1;
        }
        return ret;
    }

    int verticesDesconocidoDeMenorCosto(bool *vistados, int *costos)
    {
        int menorVerticeNoConocido = -1;
        int menorCosto = INF;
        for (int i = 1; i <= V; i++)
        {
            if (!vistados[i] && costos[i] < menorCosto)
            {
                menorVerticeNoConocido = i;
                menorCosto = costos[i];
            }
        }
        return menorVerticeNoConocido;
    }

public:

	GrafoListaAdy(int cantV, bool esDirigido = false, bool esPonderado = true)
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

	void agregarArista (int unOrigen, int unDestino, int unCosto)
	{
		Arista a1 (unOrigen,unDestino,unCosto);
		listaAdy[unOrigen] = new NodoLista(a1, listaAdy[unOrigen]);
		if (!esDirigido) {
			Arista a2 (unDestino,unOrigen,unCosto);
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

        void prim(int origen)
    {
        bool *visitados = initVisitados();
        int *costos = initCostos(origen);
        int *vengo = initVengo();

        for (int i = 1; i <= V; i++)
        {
            int v = verticesDesconocidoDeMenorCosto(visitados, costos);
            if (v != -1)
            {
                visitados[v] = true;
                ListaAristas ady = adyacentesA(v);
                while (ady != NULL)
                {
                    int w = ady->ari.destino;
                    if (!visitados[w] && costos[w] > ady->ari.peso)
                    {
                        costos[w] = ady->ari.peso;
                        vengo[w] = v;
                    }
                    ady = ady->sig;
                }
            }
        }
        int pesoTotal = 0;
        bool conexo = true;
        for (int i = 1; i <= V && conexo; i++)
        {
            if (vengo[i] != -1)
            {
                pesoTotal += costos[i];
            }
            else if (i != origen) {
                    pesoTotal = -1;
                    conexo = false;
                }

        }
        cout << pesoTotal;
    }
};

int main() {
    int v;
	cin >> v;
	GrafoListaAdy *grafo = new GrafoListaAdy(v,false,true);
	int a;
	cin >> a;
	for (int i = 1; i <= a; ++i)
	{	
		int o,d,c;
		cin >> o >> d >> c;
		grafo->agregarArista(o,d,c);
	}
	grafo->prim(1);
    return 0;
}