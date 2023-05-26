#include <iostream>
#include <malloc.h>
#include <cstring>
#include <algorithm>

using namespace std;

struct corredor
{
    int contador = 0;
    int time;
    int promedio = 0;
    int sematemp = 0;
//datos 
    char nombre[20];
    int asignado;
    corredor *sig;
    corredor *izquierdo;
    corredor *derecho;
};

corredor *cab, *aux, *aux2, *raiz, *auxA, *auxA2;

int numero;
int i = 0;
int arbol = 0;


int calcularAltura(corredor *nodo)
{
    if (nodo == NULL)
        return 0;
    return 1 + max(calcularAltura(nodo->izquierdo), calcularAltura(nodo->derecho));
}

// Realiza una rotación simple a la derecha
void rotacionSimpleDerecha(corredor *&nodo)
{
    corredor *aux = nodo->izquierdo;
    nodo->izquierdo = aux->derecho;
    aux->derecho = nodo;
    nodo = aux;
}

// Realiza una rotación simple a la izquierda
void rotacionSimpleIzquierda(corredor *&nodo)
{
    corredor *aux = nodo->derecho;
    nodo->derecho = aux->izquierdo;
    aux->izquierdo = nodo;
    nodo = aux;
}

// Realiza una rotación doble a la derecha
void rotacionDobleDerecha(corredor *&nodo)
{
    rotacionSimpleIzquierda(nodo->izquierdo);
    rotacionSimpleDerecha(nodo);
}

// Realiza una rotación doble a la izquierda
void rotacionDobleIzquierda(corredor *&nodo)
{
    rotacionSimpleDerecha(nodo->derecho);
    rotacionSimpleIzquierda(nodo);
}    

// Realiza el balanceo del árbol AVL
void balancearArbol(corredor *&nodo)
{
    if (nodo == NULL)
        return;

    int alturaIzq = calcularAltura(nodo->izquierdo);
    int alturaDer = calcularAltura(nodo->derecho);
    int diferenciaAltura = alturaDer - alturaIzq;

    if (diferenciaAltura > 1)
    {
        // Desbalance hacia la derecha
        int alturaDerDer = calcularAltura(nodo->derecho->derecho);
        int alturaDerIzq = calcularAltura(nodo->derecho->izquierdo);
        if (alturaDerDer >= alturaDerIzq)
            rotacionSimpleIzquierda(nodo);
        else
            rotacionDobleIzquierda(nodo);
    }
    else if (diferenciaAltura < -1)
    {
        // Desbalance hacia la izquierda
        int alturaIzqIzq = calcularAltura(nodo->izquierdo->izquierdo);
        int alturaIzqDer = calcularAltura(nodo->izquierdo->derecho);
        if (alturaIzqIzq >= alturaIzqDer)
            rotacionSimpleDerecha(nodo);
        else
            rotacionDobleDerecha(nodo);
    }

    // Recursivamente balancear los hijos
    balancearArbol(nodo->izquierdo);
    balancearArbol(nodo->derecho);
}

// FUNCION PARTE DEL REGISTRO EN EL ARBOL
int posicionar()
{
    if (auxA->promedio < auxA2->promedio)
    {
        if (auxA2->izquierdo != NULL)
        {
            auxA2 = auxA2->izquierdo;
            posicionar();
        }
        else
            auxA2->izquierdo = auxA;
    }
    else if (auxA->promedio > auxA2->promedio)
    {
        if (auxA2->derecho != NULL)
        {
            auxA2 = auxA2->derecho;
            posicionar();
        }
        else
            auxA2->derecho = auxA;
    }
    return 0;
}

// REGISTRA EL CALCULO DEL PROMEDIO EN EL ARBOL
int registrarArbol(corredor *fifo)
{

    auxA = fifo;

    auxA->izquierdo = auxA->derecho = NULL;
    if (raiz == NULL)
    {
        raiz = auxA;
        auxA = NULL;
        free(auxA);
    }
    else
    {
        auxA2 = raiz;
        posicionar();
    }
    return 0;
}

// REGISTRAR ATLETA

int registrar()
{

    if (cab == NULL)
    {

        cab = (struct corredor *)malloc(sizeof(struct corredor));

        cout << "Ingrase nombre del atleta: ";
        cin >> cab->nombre;

        cout << "Ingrese numero de camisa: ";
        cin >> cab->asignado;

        cab->contador = 0;
        cab->promedio = 0;
        cab->sematemp = 0;
        cab->time = 0;


        cab->sig = NULL;
    }
    else
    {
        aux = (struct corredor *)malloc(sizeof(struct corredor));

        cout << "Ingrase nombre del atleta:  ";
        cin >> aux->nombre;

        cout << "Ingrese numero de camiseta: ";
        cin >> aux->asignado;

        for (corredor *temp = cab; temp != NULL; temp = temp->sig)
        {
            if (aux->asignado == temp->asignado)
            {
                cout << "El numero de camiseta ya existe. intente otra vez.." << endl;
                free(aux);

                return 0;
            }
        }
        aux->contador = 0;
        aux->promedio = 0;
        aux->sematemp = 0;
        aux->time = 0;

        cout << "guardado" << endl;

        aux->sig = NULL;
        aux2 = cab;

        while (aux2->sig != NULL)

            aux2 = aux2->sig;
        aux2->sig = aux;

        aux2 = aux = NULL;
        free(aux);
        free(aux2);
    }
    return 0;
}

int correr()
{

    aux = cab;
    int camisa;
    bool encontrado = false;
    cout << "Ingrese numero de camiseta: ";
    cin >> camisa;

    for (aux = cab; aux != NULL; aux = aux->sig)
    {
        if (camisa == aux->asignado)
        {
            if (aux->contador == 1)
            {
                int multime;
                aux->contador++;
                cout << "Ingrse tiempo de vuelta "<< "  " << aux->contador << ":";
                cin >> multime;
                
                if (multime < 0)
                {
                    cout << "El tiempo ingresado no puede ser negativo. Ingrese un tiempo valido." << endl;
                    aux->contador--;
                    aux = aux2 = NULL;
                    return 0;
                }

                aux->sematemp = (aux->sematemp + multime);
                int resultado = (aux->sematemp) / 2;
                aux->promedio = resultado;
                aux->time = (multime);
                registrarArbol(aux);
                encontrado = true;
                aux = aux2 = NULL;
                cout << "Guardado ";
                arbol++;
                i++;
                break;
            }
            if (aux->contador > 1)
            {
                int multime;
                aux->contador++;

                cout << "Ingrese tiempo de vuelta" << "  " << aux->contador << ":";
                cin >> multime;
                if (multime < 0)
                {
                    cout << "El tiempo ingresado no puede ser negativo. Ingrese un tiempo valido." << endl;
                    aux->contador--;
                    aux = aux2 = NULL;
                    return 0;
                }

                aux->sematemp = (aux->sematemp + multime);
                int resultado = (aux->sematemp) / 2;
                aux->promedio = resultado;
                aux->time = (multime);
                registrarArbol(aux);
                balancearArbol(raiz);
                encontrado = true;
                aux = aux2 = NULL;
                cout << "Registro Exitoso";
                arbol++;
                i++;
                break;
            }

            else
            {
                int x = 1;
                int y = aux->contador;

                aux->contador = x + y;

                cout << "Ingrese tiempo de  vielta"<< "  " << aux->contador << ":";
                cin >> aux->time;
                int multime = aux->time;
                // Validar tiempo positivo
                if (multime < 0)
                {
                    cout << "El tiempo ingresado no puede ser negativo. Ingrese un tiempo valido." << endl;
                    aux->contador--;
                    aux = aux2 = NULL;
                    return 0;
                }

                encontrado = true;
                aux = NULL;
                cout << "Guardado ";
                arbol++;
                break;
            }
        }
    }

    if (encontrado == false)
    {
        printf("No se encontro el atleta");
    }
    return 0;
}

// MUESTRA DE MENOR A MAYOR
int inorden(corredor *recursive)
{

    if (arbol == 0)
    {
        cout << "~~vacio~~" << endl;
        return 0;
    }

    if (recursive->izquierdo != NULL)
    {
        inorden(recursive->izquierdo);
    }
    cout << "corredor  camisa N." << recursive->asignado << " Nombre: " << recursive->nombre << " Ultimo Tiempo: " << recursive->time << " Numero de vueltas: " << recursive->contador << "  Promedio: " << recursive->promedio << endl;

    if (recursive->derecho != NULL)
    {
        inorden(recursive->derecho);
    }
    return 0;
}



void ordenar_FIFO_desc(struct corredor *inicio)
{
    struct corredor *actual = inicio;
    while (actual != NULL)
    {
        struct corredor *mayor = actual;
        struct corredor *sig = actual->sig;
        while (sig != NULL)
        {
            if (sig->promedio > mayor->promedio)
            {
                mayor = sig;
            }
            sig = sig->sig;
        }
        int temp = actual->promedio;
        int tamp = actual->asignado;
        int tomp = actual->time;
        int timp = actual->contador;
        int tump = actual->sematemp;

        char nom[20];
        memcpy(nom, actual->nombre, 20);

        actual->promedio = mayor->promedio;
        mayor->promedio = temp;

        actual->asignado = mayor->asignado;
        mayor->asignado = tamp;

        actual->time = mayor->time;
        mayor->time = tomp;

        actual->contador = mayor->contador;
        mayor->contador = timp;

        actual->sematemp = mayor->sematemp;
        mayor->sematemp = tump;

        memcpy(actual->nombre, mayor->nombre, 20);
        memcpy(mayor->nombre, nom, 20);
        actual = actual->sig;
    }
}

void uso(){
     cab = NULL;
    aux = NULL;
    aux2 = NULL;
    raiz = NULL;
    auxA = NULL;
    auxA2 = NULL;

}

int main()
{
  uso(); 
    int opc = 0;
    do
    {
        cout << endl;
        cout << endl;
        cout << "*PLANILLA DE ATLETAS ***" << endl;
        cout << endl;
        cout << "1-REGISTRAR CORREDOR" << endl;
        cout << "2-REGUISTRO DE CARRERAS " << endl;
        cout << "3-VER DATOS EN EL ARBOL" << endl;
        cout << "4-SALIR" << endl;
        cin >> opc;

        switch (opc)
        {
        case 1:
        system("cls");
            registrar(); break;

        case 2:
        system("cls");
          correr();  break;
    

        case 3:
        system("cls");
            inorden(raiz);  break;

        case 4:
            cout << "....Fin..." << endl; break;

        default:
            break;
        }

    } while (opc != 4);

    return 0;
}

