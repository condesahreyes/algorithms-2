#include <iostream>
#include <cassert>
#include <string>
using namespace std;

struct tripleta
{
    int x;
    int y;
    int h;
};

struct par
{
    int x;
    int h;
    par*sig;
};

class ListaPares
{

    public:

    par *ppio, *fin;

    ListaPares()
    {
      ppio=NULL;
      fin=NULL;
    }

    void insertar(int unX, int unH)
    {
        par *aux = new par;
        aux->x = unX;
        aux->h = unH;
        if(ppio == NULL)
        {
            ppio = aux;
            fin = aux;
        }
        else 
        {
            fin->sig = aux;
            fin = aux;
        }
    }
};

ListaPares*merge(ListaPares*subizq, ListaPares*subder)
{
    int hizq = 0;
    int hder = 0;
    int x = 0;
    int max;
    int ultimaH = 0;
    ListaPares*res = new ListaPares();
    par* izq = subizq->ppio;
    par* der = subder->ppio;
    while (izq != NULL && der != NULL)
    {
        if (izq->x < der->x)
        {
            x = izq->x;
            hizq = izq->h;
            izq = izq->sig;
        } else if (izq->x > der->x)
                {
                    x = der->x;
                    hder = der->h;
                    der = der->sig;
                }
                else 
                {
                    hder = der->h;
                    hizq = izq->h;
                    x = der->x; // o izq->h, es lo mismo pq son iguales
                    if (hizq > hder) 
                    {
                        izq = izq->sig;
                    }
                    else
                    {
                        der = der->sig;
                    }
                }
        max = hizq > hder ? hizq : hder;
        if(ultimaH != max)
        {
            res->insertar(x,max);
            ultimaH = max;
        }
    }
    while (izq != NULL)
    {
        x = izq->x;
        hizq = izq->h;
        max = hizq > hder ? hizq : hder;
        if(ultimaH != max)
        {
            res->insertar(x,max);
            ultimaH = max;
        }
        izq = izq->sig;
    }
    while (der != NULL)
    {
        x = der->x;
        hder = der->h;
        max = hizq > hder ? hizq : hder;
        if(ultimaH != max)
        {
            res->insertar(x,max);
            ultimaH = max;
        }
        der = der->sig;
    }
    return res;
}

ListaPares*siluetas(tripleta input[], int inicio, int final)
{
    if(inicio == final)
    {
        tripleta t = input[inicio];
        ListaPares*l = new ListaPares();
        l->insertar(input[inicio].x,input[inicio].h);
        l->insertar(input[inicio].y, 0);
        return l;
    }

    int mitad = (inicio + final) / 2;

    ListaPares*izq = siluetas(input, inicio, mitad);
    ListaPares*der = siluetas(input, mitad + 1, final);

    return merge(izq, der);
}

int main()
{
    int n;
    cin >> n;
    tripleta input[n];
    for (int i = 0; i < n; i++)
    {
        cin >> input[i].x >> input[i].y >> input[i].h;
    }
    ListaPares* res = siluetas(input, 0, n - 1);
    par*aux = new par();
    aux = res->ppio;
    while (aux != NULL)
    {
        cout << aux->x << " " << aux->h << endl;
        aux = aux->sig;
    }
    return 0;
}