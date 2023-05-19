#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
struct Atleta{
int valor ;
//string nomb;	
char nombr[20];	
int tiempo;	
 Atleta *derecha,*izquerda;	
 int vueltaAtleta;	
	
};
 
Atleta *raiz_arbol=NULL,*aux,*aux1;

int registraTiempo(){
	
	aux =raiz_arbol;
	//aqui vamos a buscar el  numero de la persona q le vamos q colocar el tiempo por ronda o vuelta 
	int valor2;
	cout<<"buscar Atleta colaca el numero de la camisa ";
	cin>>valor2;
	if(aux->valor == valor2){
		// si  la camisa  es igual a la camisa el sistema va permitir  colocar el tiempo al atleta q buscan 
		// para mirar cuantas ronda  lleva o vuelta   ultilimos un  apuntador contador +++
		aux->vueltaAtleta++;
	
	   cout<<"Nombre: "<<aux->nombr<<" | "<<"vuelta del atleta: "<<aux->vueltaAtleta<<" | "<<"Tiempo del Alteta: "<<aux->tiempo<<endl;
	   
	    
	     cout<<"\n";
	     cout<<"\n";

	cout<<"Ingrese el Tiempo  el Atleta "; cin>>aux->tiempo;
	
	
	    
		
	}else 
	  cout<<"el Atleta no se puedo encontrar ?"<<endl;
	
	
	
	
	
	
	return 0;
}



int mostra_arbol(Atleta *auxb){


	cout<<"\t Numero del  Atleta: "<<auxb->nombr<<" Numero de camisa del  Atleta: "<<auxb->valor<<" Tiempo del Atleta: "<<auxb->tiempo<<endl;
   
 
	  if(auxb->izquerda != NULL){
  		
       mostra_arbol(auxb->izquerda);  		
  		
	  } if(auxb->derecha != NULL){
	  	
	  	  mostra_arbol(auxb->derecha);  
	  }
	
	return 0;
}




int posicionar(){


	if(aux->valor < aux1->valor ){
	// izquerda de posicionar	
  if(aux1->izquerda!= NULL){
  	   
		 aux1 = aux1->izquerda;
	       posicionar();
	        
		      }else
		      
	    aux1->izquerda = aux;
	    
	  }
	  
	  //derecha posicionar
	  else if(aux->valor > aux1->valor){
	  	
	  	if(aux1->derecha != NULL){
	      
		   aux1 = aux1->derecha;
	         posicionar();
	         
	          }else
	    aux1->derecha =aux;
	  	
	  }
	
	
	
}

int registraratleta(){
	aux =(struct Atleta *)malloc(sizeof(struct Atleta));
	aux->vueltaAtleta=0;
    cout<<"Ingresar numero de la camisa "<<endl;
    cin>>aux->valor;
    cout<<"Ingresar nombre de la Atleta "<<endl;
    cin>>aux->nombr;
	aux->derecha =NULL;
	aux->izquerda=NULL;
	
	if(raiz_arbol == NULL){
	   	
	 raiz_arbol	 =aux;
	 aux= NULL;
	free(aux);	
		
	}else{
		
	aux1 = raiz_arbol;	
	 posicionar();	
		
	}
	
	
	
}



int main(){
   int menu;	
	do{
 
			
	cout<<" \t Menu"<<endl;
	cout<<"1:Registar  "<<endl;
	cout<<"2:Mostra  "<<endl;
	cout<<"3:Ingresar tiempo de carrera "<<endl;
	cout<<"4:Salir "<<endl;
	cin>>menu;	
	system("cls");
		switch(menu){
			
				case 1: 
			
			registraratleta();
				break;
			
			case 2: 
			 mostra_arbol(raiz_arbol);
			
			       break;
				
				case 3:
				registraTiempo(); 
				break;
		
		
}
		
		
		
	}while(menu !=4);
	

	
	
	
	return 0;
}

