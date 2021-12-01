#include <iostream>
using namespace std;

class pasesMin {
    private:
        int** matriz;
        

    public:
       pasesMin(int m, int n){
            matriz = new int*[m]();
            for(int i = 0; i < m; i++){
                this->matriz[i] = new int[n]();
            }
            for (int i = 0; i <m; i++){
               for(int j=0; j<n; j++){
                    this->matriz[i][j]=-1;  
               }
            }
       }
       
        agregarPonderacion(int origen, int destino, int ponderacion){
            matriz[origen][destino]=ponderacion;
        }

        bool adyacentes(int m, int n){
            bool bandera=false;
            for (int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    if(matriz[i][j]>0){
                        if(i<m-1){
                        if(matriz[i + 1][j]<0)    
                            bandera=true;
                        matriz[i + 1][j]=abs(matriz[i + 1][j]);
                        }
                        if(i>0){
                        if(matriz[i - 1][j]<0)    
                            bandera=true;
                        matriz[i - 1][j]=abs(matriz[i - 1][j]);
                        }
                        if(j<n-1){
                        if(matriz[i][j+1]<0)    
                            bandera=true;
                        matriz[i][j+1]=abs(matriz[i][j+1]);
                        }
                        if(j>0){
                        if(matriz[i][j-1]<0)    
                            bandera=true;
                        matriz[i][j-1]=abs(matriz[i][j-1]);
                        }
                    }   
                }
            }
            return bandera;
        }
        
        mostrar(int v){
            for (int i = 0; i <v; i++){
               for(int j=0; j<v; j++){
                    cout << this->matriz[i][j] << endl;  
               }
            }
        }

};

int main () {
    // Lee los primeros n datos
    
    int m;
    cin >> m;
    int n;
    cin >> n;
    pasesMin* pase = new pasesMin(m, n);
    int origen, destino, ponderacion=0;
    for (int i = 0; i <m ; i++){
        for (int j = 0; j < n; j++){
        cin >> origen;
        cin >> destino;
        cin >> ponderacion;
        pase->agregarPonderacion(origen-1, destino-1, ponderacion);
        }
    }
    bool contador = true;
    int cont=0;
    while (contador){
        contador = pase->adyacentes(m,n);
        if(contador) cont ++;  
    }
    cout << cont;

    return 0;
}