#include <cassert>
#include <string>
#include <iostream>
#include <climits>
using namespace std;

class Laberinto
{
private:
    char **facultad;
    bool **matriz;

    bool pertenece(int xi, int yi, int m, int n)
    {
        return xi >= 1 && xi < m && yi >= 1 && yi < n;
    }
    bool pase(int xi, int yi)
    {
        return this->matriz[xi][yi] == true;
    }

    void caminoMasCortoRec(int xi, int yi, int xf, int yf, int cant, int &mejorCant, int m, int n)
    {

        if (cant < mejorCant)
            if (pertenece(xi, yi, m, n) && !pase(xi, yi) && (this->facultad[xi][yi]) != 'P')
            {
                this->matriz[xi][yi] = true;
                if (xi == xf && yi == yf && cant < mejorCant)
                {
                    mejorCant = cant;
                }
                else
                {
                    int movF[4] = {1, -1, 0, 0};
                    int movC[4] = {0, 0, 1, -1};
                    for (int mov = 0; mov < 4; mov++)
                        caminoMasCortoRec(xi + movF[mov], yi + movC[mov], xf, yf, cant + 1, mejorCant, m, n);
                }
                this->matriz[xi][yi] = false;
            }
    }

public:
    Laberinto(int m, int n)
    {
        facultad = new char *[m]();
        matriz = new bool *[m]();
        for (int i = 1; i <= m; i++)
        {
            this->facultad[i] = new char[n]();
            this->matriz[i] = new bool[n]();
        }
    }
    llenarMatriz(int i, int j, char dato)
    {
        this->facultad[j][i] = dato;
    }
    void caminoMasCorto(int *aux, int bx, int by, int m, int n)
    {
        int mejorCantB = INT_MAX;
        int mejorCantD = INT_MAX;
        caminoMasCortoRec(aux[0], aux[1], bx, by, 0, mejorCantB, m, n);
        if (mejorCantB != INT_MAX)
            caminoMasCortoRec(bx, by, aux[2], aux[3], 0, mejorCantD, m, n);
        int total = (mejorCantB == INT_MAX || mejorCantD == INT_MAX) ? 0 : mejorCantD + mejorCantB + 1;
        cout << total << endl;
    }
};

int main()
{
    int m;
    cin >> m;
    int n;
    cin >> n;
    Laberinto laberinto = Laberinto(m, n);
    char dato;
    int bx = -1;
    int by = -1;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> dato;
            if (dato == 'B')
            {
                bx = j;
                by = i;
            }
            laberinto.llenarMatriz(i, j, dato);
        }
    }

    int valorP;
    int *pruebas = new int[4]();

    int datosDePrueba;
    cin >> datosDePrueba;
    for (int i = 0; i < datosDePrueba; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> valorP;
            pruebas[j] = valorP;
        }
        laberinto.caminoMasCorto(pruebas, bx, by, m + 1, n + 1);
    }

    return 0;
}