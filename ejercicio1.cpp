#include <iostream>
using namespace std;

struct NodoAVL {
    int dato;
    int bal;
    NodoAVL * izq;
    NodoAVL * der;
    NodoAVL(int dt): dato(dt), izq(0), der(0), bal(0) {}
    NodoAVL(int dt, NodoAVL * i, NodoAVL * d,int bl): dato(dt), izq(i), der(d), bal(bl) {}
};


class Arbol {
    private:
        typedef NodoAVL * AVL;
        AVL raiz;
        bool varioH;
        void insertarAux(int &x,AVL &pa){
            AVL p1, p2;
            if(pa == 0) {
                pa = new NodoAVL(x,0,0,0);
                this->varioH = true;
            }else if (pa->dato > x) {
                insertarAux(x,pa->izq);
                if(this->varioH) {
                    switch (pa->bal)
                    {
                    case 1:
                        pa->bal = 0;
                        this->varioH = false;
                        break;
                    case 0:
                        pa->bal = -1;
                        break;
                    case -1:
                        p1 = pa->izq;
                        if(p1->bal == -1) {
                            // II
                            pa->izq = p1->der;
                            p1->der = pa;
                            pa->bal =0;
                            pa = p1;
                        }else {
                            // ID
                            p2 = p1->der;
                            p1->der = p2->izq;
                            p2->izq = p1;
                            pa->izq = p2->der;
                            p2->der = pa;
                            pa->bal = p2->bal == -1 ? 1 : 0;
                            p1->bal = p2->bal == 1 ? -1 : 0;
                            pa = p2;
                        }
                        pa->bal =0;
                        this->varioH =false;
                        break;
                    }
                }
            } else {
                insertarAux(x,pa->der);
                if(this->varioH) {
                    switch (pa->bal)
                    {
                        case -1:
                            pa->bal = 0;
                            this->varioH = false;
                            break;
                        case 0:
                            pa->bal = 1;
                            break;
                        case 1:
                            p1 = pa->der;
                            if(p1->bal == 1) {
                                // DD
                                pa->der = p1->izq;
                                p1->izq = pa;
                                pa->bal =0;
                                pa = p1;
                            }else {
                                // DI
                                p2 = p1->izq;
                                p1->izq = p2->der;
                                p2->der = p1;
                                pa->der = p2->izq;
                                p2->izq = pa;
                                pa->bal = p2->bal == 1 ? -1 : 0;
                                p1->bal = p2->bal == -1 ? 1 : 0;
                                pa = p2;
                            }
                            pa->bal =0;
                            this->varioH =false;
                            break;
                    }
                }
            }
        }
        void recInOrderAux(AVL nodo) {
            if(nodo != 0) {
                recInOrderAux(nodo->izq);
                cout << nodo->dato << endl;
                recInOrderAux(nodo->der);
            }
        }
    public:
        Arbol() {
            raiz = 0;
        }
        void insertar(int &dato) {
            this->insertarAux(dato,raiz);
        }
        void recInOrder() {
            this->recInOrderAux(raiz);
        }
};

int main () 
{
    // Lee los primeros n datos
    int n;
    cin >> n;
    int *vec = new int[n];
    for (int i = 0; i < n; i++){
        cin >> vec[i];
    }
    // Inicializar el arbol
    Arbol * miArbol = new Arbol();
    // Insertar los datos ordenados en el arbol
    for (int i = 0; i < n; i++) {
        miArbol->insertar(vec[i]);
    }
    //Imprimir los datos en orden
    miArbol->recInOrder();
    return 0;
}