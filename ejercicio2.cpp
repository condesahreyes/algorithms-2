#include <iostream>
using namespace std;

struct NLpares {
	string valor;
	NLpares* sig;
	NLpares(string valor, NLpares* sig):valor(valor), sig(sig) {};
};



class tablaHashAbierta {
    private:
        typedef NLpares* NL;
        NL* array;
	    int cantElem;
        int tamanio;

unsigned int funStringToInt(string clave){
    int sum = 0;
    for (int k = 0; k < clave.length(); k++)
        sum += int(clave[k]);
    return sum;
}

unsigned int funHash(string clave, int largoArray) {
	int valorString = funStringToInt(clave);
    return abs(valorString % largoArray);
}

    public:
        tablaHashAbierta(int tamanio){
            this->tamanio=tamanio;
            this->cantElem=0;
            this->array=new NL[tamanio]();
        }


        void agregar(string clave) {
	        int pos = funHash(clave, this->tamanio);
            NL lista= this->array[pos];
            NL nodo = new NLpares(clave, lista);
            this->array[pos]= nodo;
            this->cantElem++;
        }

        
        int buscar(string clave) {
            int pos = funHash(clave, this->tamanio);
	        NL aux = this->array[pos];
            bool salir=false;
            while(aux){
                if(aux->valor==clave)
                    return 1;
                aux=aux->sig;   
            }
            return 0;
        }

};

int main () 
{
    // Lee los primeros n datos
    
    int n;
    cin >> n;
    tablaHashAbierta* tabla = new tablaHashAbierta(n);
    string aux;
    for (int i = 0; i < n; i++){
        cin >> aux;
        tabla->agregar(aux); 
    }
    int m;
    cin >> m;
    int* salida = new int[m];
    
    for (int i = 0; i < m; i++){
        cin >> aux;
        salida[i] = tabla->buscar(aux);
    }

    for (int i = 0; i < m; i++)
      cout << salida[i]<< endl;
    

    return 0;
}