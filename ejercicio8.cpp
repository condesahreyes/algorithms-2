#include <iostream>
using namespace std;

struct Lista
{
    int vertice = -1;
    Lista *sig;
    Lista(int vertice, Lista *sig)
    {
        this->vertice = vertice;
        this->sig = sig;
    };
};

class pArticulacion
{
private:
    typedef Lista *ListaAdy;
    ListaAdy *listaAdy;
    int v;

    void DFS_rec(int origen, bool *&visitados)
    {
        visitados[origen] = true;
        ListaAdy adyacentesAOrigen = this->listaAdy[origen];
        while (adyacentesAOrigen != NULL)
        {
            int w = adyacentesAOrigen->vertice;
            if (!visitados[w])
                DFS_rec(w, visitados);
            adyacentesAOrigen = adyacentesAOrigen->sig;
        }
    }

    bool DFS(int origen)
    {
        bool *visitados = new bool[v]();
        DFS_rec(origen, visitados);
        int contadorNoVisitados = 0;
        for (int i = 1; i < v; i++)
            if (visitados[i] == false)
                contadorNoVisitados++;
        return contadorNoVisitados > 1 ? false : true;
    }

public:
    pArticulacion(int cantV)
    {
        this->listaAdy = new Lista *[cantV + 1]();
        this->v = cantV + 1;
    }
    agregarVertice(int origen, int destino)
    {

        ListaAdy nodoOrigen = new Lista(destino, listaAdy[origen]);
        ListaAdy nodoDestino = new Lista(origen, listaAdy[destino]);
        this->listaAdy[origen] = nodoOrigen;
        this->listaAdy[destino] = nodoDestino;
    }
    ListaAdy devolverLista(int origen)
    {
        return this->listaAdy[origen];
    }
    borrar(ListaAdy &l, int dato)
    {
        if (l == NULL)
            return 0;
        if (dato != l->vertice)
            return borrar(l->sig, dato);
        ListaAdy temp = l;
        l = l->sig;
        delete temp;
        return 0;
    }
    ListaAdy eliminarVertice(int origen)
    {
        this->listaAdy[origen] = NULL;
        for (int i = 1; i < this->v; i++)
            if (i != origen)
                borrar(this->listaAdy[i], origen);
    }
    agregarListaAdyacencia(int origen, ListaAdy ady)
    {
        this->listaAdy[origen] = ady;
        while (ady != NULL)
        {
            ListaAdy aux = listaAdy[ady->vertice];
            aux = new Lista(origen, listaAdy[ady->vertice]);
            this->listaAdy[ady->vertice] = aux;
            ady = ady->sig;
        }
    }
    bool esConexo(int origen)
    {
        DFS(origen) ? true : false;
    }
};

int main()
{
    // Lee los primeros n datos
    int v;
    cin >> v;
    int e;
    cin >> e;
    pArticulacion *adyacentes = new pArticulacion(v);
    int origen = 0;
    int destino = 0;
    for (int i = 1; i <= e; i++)
    {
        cin >> origen;
        cin >> destino;
        adyacentes->agregarVertice(origen, destino);
    }

    Lista *aux;
    for (int i = 1; i <= v; i++)
    {

        aux = adyacentes->devolverLista(i);

        adyacentes->eliminarVertice(i);

        int prueba = 0;
        if (i > 1)
            prueba = 1;
        if (i < v)
            prueba = v;
        if (!adyacentes->esConexo(prueba))
            cout << i << endl;
        adyacentes->agregarListaAdyacencia(i, aux);
    }

    return 0;
}