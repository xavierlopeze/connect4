#include"minimax.c"
#include"4enratlla.c"
#include<stdio.h>
#include <stdlib.h>


int partida (int maxNivellsArbre, int scoreJ2, int scoreJ1) {
  Node node;
  int input; //tir del jugador (columna)
  int pcmove; //tir del PC (numero de node fill)
  
  inicialitzaTauler(&node);
  printf("\n \t\t     GAME SCORE:\n \t\t BOT = %d JUGADOR = %d \n", scoreJ2, scoreJ1);
  printfTauler(node.tauler);
  printf("\t \t \t Mou! \n"); 
  
  while(scanf(" %d",&input)){ //sempre que rebi tirades
   	  
	  node.columnaMoviment=input-1; // cal restar 1 perque la primera columna la imprimim com a (1) pero internament es 0
	  								// i.e. les columnes per print van de 1..M però internament van de 0...M-1
		
	  //  Si l'input es incorrecte tornem el missatge d'error adient	
	  if(correctInput(input, node.tauler)!=0){
	    if(correctInput(input, node.tauler)==1){printf("\n\t\t   INCORRECT INPUT:\n\t\t  Has introduit (%d). \n\tHas d'introduir un nombre mes ptit que (%i)\n\n",input,M);}
	    if(correctInput(input, node.tauler)==-1){printf("\n\t\t   INCORRECT INPUT:\n\t\t Has introduit (%d). \n\t Has d'introduir un nombre mes gran que (%i)\n\n", input, 0);}
	    if(correctInput(input, node.tauler)==2){printf("\n\t\t   INCORRECT INPUT:\n\t\t  Has introudit (%d). \n\t      Aquesta columna esta plena\n\n", input);}
	  } 
	  
	  //Assumim que l'input es correcte
	  else {
	    node.filaMoviment =calculaFila(node.tauler,node.columnaMoviment); //calculem la fila del moviment corresponent a la columna introduida
		aplicaTirada(node.tauler, node.columnaMoviment, node.filaMoviment, J1); //apliquem la tirada al tauler a la posicio corresponent a la fila icolumna introduides
	    printf("\n\t\t JUGADOR:(%c)\tmou a (%d) \n",J1,node.columnaMoviment+1); //imprimim la posicio on ha mogut el jugador
	    
	    if (IVenRatlla(node.tauler,J1)==1) { //si guanya el jugador, imprimim el darrer tauler i acabem la partida
			printfTauler(node.tauler);
			printf("\t \t GAME OVER: YOU WIN \n"); 
			return 1;}
		
	   //si no guanya el jugador, calculem les possibles tirades
	 
	  	node.n_fills=nPossiblesMoviments(node.tauler);
	  	node.fills=malloc(node.n_fills*sizeof(Node *)); //reservem memòria per els nofdes fills
	  	creaArbre(&node, maxNivellsArbre); //creem arbre amb totes les possibles tirades amb profunditat maxNivellsArbre
	 	
		minimaxAlphabeta(&node,2*maxNivellsArbre,-2e6,2e6,1); //usem minimax per triar el millor movment del bot
	 	pcmove=minimaxMove(&node);//assignem el moviment del bot
	 	//pcmove=minimax(&node, maxNivellsArbre);  //usem minimax per triar el millor movment del bot
	  
	  	printf("\t \t BOT:(%c)\tmou a (%d)",J2,calculaColumna(node.tauler, pcmove)+1); //imprimim la posicio on ha mogut el bot
	  
	  	//printfTauler(node.fills[pcmove]->tauler); //imprimex el tauler
	  
	  	//imprimim el tauler posant majuscules a les darreres tirades del jugador i del bot
	 	marcaUltimaTiradaiPrintTauler(node.fills[pcmove]->tauler, node.filaMoviment, node.columnaMoviment,node.fills[pcmove]->filaMoviment, node.fills[pcmove]->columnaMoviment);
	  
	  	copiaTauler(node.tauler,node.fills[pcmove]->tauler); //copiem el tauler on fem el moviment
	  
	  	esborraArbre(&node, maxNivellsArbre); //alliberem memoria
	  }
	 
	 // Si guanya el BOT, acabem partida
	 if (IVenRatlla(node.tauler,J2)==1) {
	 	printf("\t \t GAME OVER: YOU LOSE \n"); 
		return -1;}
		
	 // Si hi ha un empat, acabem partida	
	 else if (taulerPler(node.tauler)){
			printf("\t \t GAME OVER: EMPAT\n"); 
			return 0;}
			
	 // Si la partida no s'ha acabat, demanem que es torni a tirar
	  else  printf("\t \t \t Mou! \n"); 
 
  }
  
}
