/*
*	AUTOR: XAVIER LOPEZ ESPANOL
*	NIU: 1305397
*	1a ENTREGA PROGRAMACIO AVANCADA
*	17/10/2016
*
*/

/*
*	FITXER: main.c
*	DESCRIPCIO: permet triar el nivell de profunditat de l'arbre possibles tirades que s'analitza
*				i anar fent partides, contant el marcador total de victories-derrotes.
*				
*				Fitxer compilable.
*				
*/

#include"partida.c"

void main () {
	int scoreJ1=0, scoreJ2=0; 
  	int resultat;
  	char resposta;

  	int maxNivellsArbre;

  	/*missatge benvinguda:*/
  	printf("\n \t\tBenvingut al 4 en ratlla \n\n");
  	/*introduim profunditat de l'arbre*/
  	printf("\tIntrodueix el numero de nivells de profunditat \n\tque usa l'arbre de possibles moviments del BOT \n\t(es recomanable que sigui un numero entre 1 i 4\n\tper tal de tenir un temps d'execucio raonable)\n");
  	scanf(" %d",&maxNivellsArbre);
  	/*demanem introduir tirada*/
  	printf("\n \t\tPer a moure cal introduir \n \t\t el numero de la columna \n \t\t    on vulguis tirar \n");
  	
  while(1){
  //imprimim marcador al comencar la partida
	resultat=partida(maxNivellsArbre,scoreJ2,scoreJ1); //Fem un partida i al acabar-la guardem a resultat 1 si a guanyat J1, -1 si ha guanyat J2 i 0 en cas d'empat
  	
	if(resultat==1) scoreJ1++; //si a la darrera partida guanya J1, li afegim un punt al marcador
  	else if (resultat ==-1) scoreJ2++; //si a la darrera partidaguanya J2, li afegim un punt al marcador
  	
	printf("\n\t\tVols tornar a jugar? (s/n)\n");
  	scanf(" %c", &resposta);
	if(resposta=='n') break; //seguirem jugant per tota resposta diferent de 'n'
  }

  printf("\n \t\t  FINAL GAME SCORE:\n \t\t BOT = %d JUGADOR = %d \n", scoreJ2, scoreJ1);//ja no volem seguir jugant, imprimim marcador final i acabem
}
  
  
