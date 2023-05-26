#include <iostream>
#include <string.h>
#include <algorithm>
#include <malloc.h>

using namespace std;

struct Atleta {
    int valor;
    char nom[20];
    int tiempo;
    Atleta* derecha;
    Atleta* izquierda;
    int vueltaAtleta;
    int altura;
    int promedio;
    int promedioTotal;

};
int calcularPromedio();
Atleta* raiz_arbol = NULL;
Atleta* aux;
Atleta* aux_posicion;

int altura(Atleta* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}

int factorEquilibrio(Atleta* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

Atleta* rotarIzquierda(Atleta* nodo) {
    Atleta* nodoDerecha = nodo->derecha;
    Atleta* nodoIzquierdaSubArbolDerecho = nodoDerecha->izquierda;

    nodoDerecha->izquierda = nodo;
    nodo->derecha = nodoIzquierdaSubArbolDerecho;

    nodo->altura = max(altura(nodo->izquierda), altura(nodo->derecha)) + 1;
    nodoDerecha->altura = max(altura(nodoDerecha->izquierda), altura(nodoDerecha->derecha)) + 1;

    return nodoDerecha;
}

Atleta* rotarDerecha(Atleta* nodo) {
    Atleta* nodoIzquierda = nodo->izquierda;
    Atleta* nodoDerechaSubArbolIzquierdo = nodoIzquierda->derecha;

    nodoIzquierda->derecha = nodo;
    nodo->izquierda = nodoDerechaSubArbolIzquierdo;

    nodo->altura = max(altura(nodo->izquierda), altura(nodo->derecha)) + 1;
    nodoIzquierda->altura = max(altura(nodoIzquierda->izquierda), altura(nodoIzquierda->derecha)) + 1;

    return nodoIzquierda;
}

Atleta* balancearArbol(Atleta* nodo) {
    if (nodo == NULL) {
        return nodo;
    }

    nodo->altura = max(altura(nodo->izquierda), altura(nodo->derecha)) + 1;

    int factor = factorEquilibrio(nodo);

    if (factor > 1) {
        if (factorEquilibrio(nodo->izquierda) < 0) {
            nodo->izquierda = rotarIzquierda(nodo->izquierda);
        }
        return rotarDerecha(nodo);
    }
    if (factor < -1) {
        if (factorEquilibrio(nodo->derecha) > 0) {
            nodo->derecha = rotarDerecha(nodo->derecha);
        }
        return rotarIzquierda(nodo);
    }

    return nodo;
}

void promedio(Atleta* raiz_arbol) {
    
    promedio(raiz_arbol->izquierda);  
    
    cout << "Camisa del atleta: " << raiz_arbol->valor << endl;
    cout << "Promedio de tiempos: " << raiz_arbol->promedioTotal << endl << endl;
     promedio(raiz_arbol->derecha);  
	 
}



void registraTiempo() {
    aux = raiz_arbol;

    int valor2;
    cout << "Ingrese el número de la camiseta del atleta: ";
    cin >> valor2;

    aux = raiz_arbol; // Restablecer aux a raiz_arbol

    while (aux != NULL && aux->valor != valor2) {
        if (aux->valor < valor2) {
            aux = aux->derecha;
        } else {
            aux = aux->izquierda;
        }
    }
    if (aux != NULL) {
        aux->vueltaAtleta++;

        cout << "Nombre: " << aux->nom << " - "
             << "Vuelta del atleta: " << aux->vueltaAtleta << " - "
             << "Tiempo del Atleta: " << aux->tiempo << endl;

        cout << "\n";

        cout << "Ingrese el tiempo del atleta: ";
        cin >> aux->tiempo;
        calcularPromedio();
        
    } else {
        cout << "El atleta no se pudo encontrar." << endl;
    }
}

void mostra_arbol(Atleta* auxb) {
    if (auxb->izquierda != NULL) {
        mostra_arbol(auxb->izquierda);
    }

    cout << "\t Nombre del Atleta: " << auxb->nom
         << " Numero de camisa del Atleta: " << auxb->valor
         << " Tiempo del Atleta: " << auxb->tiempo << endl;

    if (auxb->derecha != NULL) {
        mostra_arbol(auxb->derecha);
    }
}

void posicionar() {
    if (aux->valor < aux_posicion->valor) {
        if (aux_posicion->izquierda != NULL) {
            aux_posicion = aux_posicion->izquierda;
            posicionar();
        } else {
            aux_posicion->izquierda = aux;
        }
    } else if (aux->valor > aux_posicion->valor) {
        if (aux_posicion->derecha != NULL) {
            aux_posicion = aux_posicion->derecha;
            posicionar();
        } else {
            aux_posicion->derecha = aux;
        }
    } else {
        cout << "El número de camiseta ya está en uso." << endl;
       
    }
    raiz_arbol = balancearArbol(raiz_arbol); // Equilibrar el árbol después de la inserción
}

void registrarAtleta() {
   aux  = (struct Atleta *) malloc (sizeof(struct Atleta));
    aux->vueltaAtleta = 0;
    aux->tiempo=0;
    

    cout << "Ingresar numero de la camiseta: ";
    cin >> aux->valor;
    cout << "Ingresar nombre del Atleta: ";
    cin >> aux->nom;
    
    aux->derecha = NULL;
    aux->izquierda = NULL;
    aux->altura = 1;

    if (raiz_arbol == NULL) {
        raiz_arbol = aux;
    } else {
        aux_posicion = raiz_arbol;
        posicionar();
    }
}

int calcularPromedio() {
    aux = raiz_arbol;
    aux->promedio +=aux->tiempo;
    aux->promedioTotal=aux->promedio/aux->vueltaAtleta;
    
    
}

int main() {
    int menu;
    do {
    	cout<<"\n";
        cout<<"\n";

        cout << "\t *** Atleta ***" << endl;
        cout << "1: Registrar atleta" << endl;
        cout << "2: Mostrar atletas" << endl;
        cout << "3: Ingresar tiempo" << endl;
        cout << "4: Promedio de tiempos" << endl;
        cout << "5: Salir" << endl;
        cin >> menu;
        system("cls");
        switch (menu) {
            case 1:
                registrarAtleta();
                break;
            case 2:
                mostra_arbol(raiz_arbol);
                break;
            case 3:
                registraTiempo();
                break;
            case 4:
                promedio(raiz_arbol);
                break;
        }
    } while (menu != 5);

    return 0;
}

