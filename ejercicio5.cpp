#include <iostream>
using namespace std;





class caminoMasCorto {
    private:
        int** matriz;
        

    public:
       caminoMasCorto(int v){
            matriz = new int*[v]();
            for(int i = 0; i < v; i++){
                this->matriz[i] = new int[v]();
            }
            for (int i = 0; i <v; i++){
               for(int j=0; j<v; j++){
                    this->matriz[i][j]=-1;  
               }
            }
       }
       
         agregarPonderacion(int origen, int destino, int ponderacion){
            matriz[origen][destino]=ponderacion;
        }
        
        mostrar(int v){
            for (int i = 0; i <v; i++){
               for(int j=0; j<v; j++){
                    cout << this->matriz[i][j] << endl;  
               }
            }
        }

};

int main () 
{
    // Lee los primeros n datos
    
    int v;
    cin >> v;
    int e;
    cin >> e;
    caminoMasCorto* camino = new caminoMasCorto(v);
    int origen=0;
    int destino=0;
    int ponderacion=0;
    for (int i = 1; i <= e ; i++){
        cin >> origen;
        cin >> destino;
        cin >> ponderacion;
        camino->agregarPonderacion(origen-1, destino-1, ponderacion);
    }

    cout << endl;
    camino->mostrar(v);
    

    

    return 0;
}