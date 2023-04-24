#include <iostream>
#include <malloc.h>
#include <cstring>
#include <algorithm>

using namespace std;

struct Times
{
    int contador = 0;
    int time;
    int promedio = 0;
    int sematemp=0;
};

struct corredor
{
    char nombre[20];
    int nasignado;
    Times estruc2;
    corredor *sig;
};

corredor *cab, *aux, *aux2;

int numero;
int i=0;

// REGISTRAR ATLETA



int registrar()
{

    if (cab == NULL)
    {

        cab = (struct corredor *)malloc(sizeof(struct corredor));

        cout << "INGRESE NOMBRE DEL CORREDOR: ";
        cin >> cab->nombre;

        cout << "INGRESE NUMERO DE CAMISETA: ";
        cin >> cab->nasignado;

        cab->sig = NULL;
    }
    else
    {
        aux = (struct corredor *)malloc(sizeof(struct corredor));

        cout << "INGRESE NOMBRE DEL CORREDOR: ";
        cin >> aux->nombre;

        cout << "INGRESE NUMERO DE CAMISETA: ";
        cin >> aux->nasignado;

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
//int num corredor


    aux2 = cab;
    int camisa;
    bool encontrado = false;
    cout << "INGRESE NUMERO DE CAMISETA DEL CORREDOR: ";
    cin >> camisa;

    for (aux2 = cab; aux2 != NULL; aux2 = aux2->sig)
    {
        if (camisa == aux2->nasignado)
        {
           
            if (aux2->estruc2.contador  >= 2)
            {
                int multime;
                aux2->estruc2.contador++;
                cout << "INGRESE TIEMPO "<< "DE VUELTA"<<"-"<<aux2->estruc2.contador<<":";
                cin >> multime;
                 aux2->estruc2.sematemp = (aux2->estruc2.sematemp + multime) ;
                int resultado =  (aux2->estruc2.sematemp) / 2;
                aux2->estruc2.promedio= resultado;
                aux2->estruc2.time= (multime);
                encontrado = true;
                aux2 = aux = NULL;
                cout << "Registro Exitoso";
                i++;
                break;
  
            }

            if (aux2->estruc2.contador == 1)
            {
                
                int segundotime;
                aux2->estruc2.contador++;
                 cout << "INGRESE TIEMPO "<< "DE VUELTA"<<"-"<<aux2->estruc2.contador<<":";
                cin >> segundotime;
                aux2->estruc2.sematemp = (aux2->estruc2.time + segundotime) ;
                int resultado = (aux2->estruc2.time + segundotime) / 2;
                aux2->estruc2.promedio= resultado;
                aux2->estruc2.time= (segundotime);
                
                encontrado = true;
                aux2 = aux = NULL;
                cout << "Registro Exitoso";
                break;
            }


           else {
            aux2->estruc2.contador++;
            cout << "INGRESE TIEMPO "<< "DE VUELTA"<<"-"<<aux2->estruc2.contador<<":";
            cin >> aux2->estruc2.time;
            encontrado = true;
            aux2 = NULL;
            cout << "Registro Exitoso";
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

int mostrar()
{

    int i = 1;
    int j = 0;
    cout << " \t\t\tLista de participante " << endl;
    cout << "\n";
    cout << "\n";

    for (aux = cab; aux != NULL; aux = aux->sig)
    {
        cout << i++ << ". corredor  camisa #" << aux->nasignado << " Nombre: " << aux->nombre << " Ultimo Tiempo: " << aux->estruc2.time<< " Numero de vueltas: " << aux->estruc2.contador << "  Promedio: " << aux->estruc2.promedio << endl;
        j++;
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
            if (sig->estruc2.promedio > mayor->estruc2.promedio)
            {
                mayor = sig;
            }
            sig = sig->sig;
        }
        int temp = actual->estruc2.promedio;
        int tamp = actual->nasignado;
        char nom[20];
        memcpy(nom, actual->nombre, 20);

        actual->estruc2.promedio = mayor->estruc2.promedio;
        mayor->estruc2.promedio = temp;

        actual->nasignado = mayor->nasignado;
        mayor->nasignado = tamp;

        memcpy(actual->nombre, mayor->nombre, 20);
        memcpy(mayor->nombre, nom, 20);
        actual = actual->sig;
    }
}

int main()
{

    int opc = 0;
    do
    {
        cout << endl;
        cout << endl;
        cout << "<<  SISTEMA DE ATLETAS  >>" << endl;
        cout << endl;
        cout << "1.REGISTRAR CORREDOR" << endl;
        cout << "2.REGISTRAR TIEMPO DE VUELTAS" << endl;
        cout << "3.MOSTRAR " << endl;
        cout << "4.SALIR" << endl;
        cin >> opc;

        switch (opc)
        {
        case 1:
            registrar();
            break;

        case 2:
            correr();

            break;
        case 3:
            ordenar_FIFO_desc(cab);
            mostrar();

            break;

        default:
            break;
        }

    } while (opc != 4);

    return 0;
}