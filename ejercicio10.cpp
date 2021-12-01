#include <iostream>
#include <cassert>
#include <string>
#include <cmath>
using namespace std;

int buscarOperario(char pisos[], int ultimoOperario, int n)
{
    int pos = -1;
    for (int i = ultimoOperario; i < n && pos == -1; i++)
    {
        if(pisos[i] == 'O')
        {
            pos = i;
        }
    }
    return pos;
}

int buscarCuadrilla(char pisos[], int ultimaCuadrilla, int n)
{
    int pos = -1;
    for (int i = ultimaCuadrilla; i < n && pos == -1; i++)
    {
        if(pisos[i] == 'C')
        {
            pos = i;
        }
    }
    return pos;
}

void laConstruccion(char pisos[], int k, int n)
{
    int pisosAtendidos = 0;
    int ultimoOperario = 0;
    int ultimaCuadrilla = 0;
    int indiceOperario = buscarOperario(pisos, ultimoOperario, n);
    int indiceCuadrilla = buscarCuadrilla(pisos, ultimaCuadrilla, n);
    while (indiceOperario != -1 && indiceCuadrilla != -1)
    {
        if (abs(indiceOperario - indiceCuadrilla) <= k)
        {
            pisosAtendidos++;
            ultimoOperario = indiceOperario + 1;
            ultimaCuadrilla = indiceCuadrilla + 1;
            indiceOperario = buscarOperario(pisos, ultimoOperario, n);
            indiceCuadrilla = buscarCuadrilla(pisos, ultimaCuadrilla, n);
        }
        else if (indiceOperario < indiceCuadrilla)
            {
                ultimoOperario = indiceOperario + 1;
                indiceOperario = buscarOperario(pisos, ultimoOperario, n);
            } 
            else
            {
                ultimaCuadrilla = indiceCuadrilla + 1;
                indiceCuadrilla = buscarCuadrilla(pisos, ultimaCuadrilla, n); 
            }
    }
    cout << pisosAtendidos << endl;
}

int main()
{
    int p,k,n;
    cin >> p;
    for (int i = 0; i < p; i++)
    {
        cin >> k;
        cin >> n;
        char input[n];
        for (int j = 0; j < n; j++)
        {
            cin >> input[j];
        }
        laConstruccion(input,k,n);
    }
}