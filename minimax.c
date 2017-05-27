#include "mida_tauler.h" //definim N i M
#include "simbols_tauler.h" //definim J1,J2 i 'BUIT'
#include"minimax.h"
#include"4enratlla.h"
#include"heuristic.c"

#include <stdio.h>
#include <stdlib.h>


/*
*	FUNCIO creaNode
*
*	INPUT: 	reb el nodePare, el numero de fill que li correspon i el jugador que fa la tirada
*	DESCRIPCIO:  donat un node crea un dels seus fills,aquest fill es el numero de fill numFill, 
*				 aplica el moviment que li correspongui per numFill amb el caracter adequat a
*				 la fila i columna que correspongui i guarda memoria per els nous fills.
*/

Node *creaNode (Node *nodePare, int numFill, char jugador){
 
  Node *p=malloc(sizeof(Node)); //usem un punter per poder tornarlo, si no usessim punter es perdria
  copiaTauler(p->tauler, nodePare->tauler); // copiem el tauler del nodePare al nou node
  p->columnaMoviment=calculaColumna(p->tauler,numFill); //donat el numero de fill que correspon, calculem la columna on s'ha de fer el moviment (descartem columnes plenes)
  p->filaMoviment = calculaFila(p->tauler, p->columnaMoviment); // donada la columna on es fa el moviment calcula la fila on caura el moviment per gravetat al tauler
  aplicaTirada(p->tauler, p->columnaMoviment, p->filaMoviment, jugador); // alpiquem la tirada al tauler del node a la fila i columna corresponents, amb el char del jugador que fa la tirada.
  p->n_fills=nPossiblesMoviments(p->tauler); //calcula el nombre de columnes buides i.e. nombre de possibles moviments
  p->fills=malloc(p->n_fills*sizeof(Node *));
 
 return p;
}

/*
*	FUNCIO crea1Nivell
*
*	INPUT: 	reb el nodePare, i el jugador que fara la tirada
*	DESCRIPCIO:  creaa tots els fills del nodePare, on jugador es qui aplica la tirada
*/

void crea1Nivell(Node *pare, char jugador){
  int i;
  for (i=0; i<(pare->n_fills);i++)
    pare->fills[i]=creaNode(pare,i,jugador);
}

/*
*	FUNCIO creaArbre
*
*	INPUT: 	reb el node arrel i el nombre de nivells que volem crear
*	DESCRIPCIO:  crea tots els nivells de l'arbre que desitgem 
				(totes les jugades possibles fins a nombre de viells "nivells")
*/

void creaArbre (Node *arrel, int nivells) { 
    int i,j;
    crea1Nivell(arrel, J2); // creem els fills per l'arrel
    for (i=0; i<arrel->n_fills; i++) {
        crea1Nivell(arrel->fills[i],J1); // per cada fill de l'arrel creem els seus fills
        if (nivells>1)
            for (j=0; j<arrel->fills[i]->n_fills; j++)
                creaArbre(arrel->fills[i]->fills[j],nivells-1); // si nivells>1, creem un altre arbre de cada fulla, amb nivells-1
    }
}

/*
*	FUNCIO esborraNode
*
*	INPUT: 	reb un node
*	DESCRIPCIO:  esborra el node (cal que aquest node no tingui fills)
*/

void esborraNode(Node *node) {
    free(node->fills);
    free(node);
}

/*
*	FUNCIO esborra1Nivell
*
*	INPUT: 	reb un node arrel
*	DESCRIPCIO:  esborra tots els fills d'un node
*/

void esborra1Nivell (Node *arrel) {
    int i;
    for (i=0; i<arrel->n_fills; i++)
        esborraNode(arrel->fills[i]);
}

/*
*	FUNCIO esborraArbre
*
*	INPUT: 	reb un node arrel i un nombre de nivells
*	DESCRIPCIO:  esborra tots els nodes de l'arbre fins al nombre de nivells que introduim
*/

void esborraArbre (Node *arrel, int nivells) {
    int i,j;
    if (nivells-1 > 0) {
        for (i=0; i<arrel->n_fills; i++) {
            for (j=0; j<arrel->fills[i]->n_fills; j++)
                esborraArbre(arrel->fills[i]->fills[j],nivells-1);
        }
    }
    for (i=0; i < arrel->n_fills; i++)
        esborra1Nivell(arrel->fills[i]);
    esborra1Nivell(arrel);
}

/*
*	FUNCIO copiaTauler
*
*	INPUT: 	reb dos taulers
*	DESCRIPCIO:  copia els valors del pareTauler al fillTauler
*/
void copiaTauler(char fillTauler[N][M], char pareTauler[N][M]) { /*copiem pareTauler a pTauler*/
  int i, j;
  for (i=0;i<N; i++)
    for(j=0; j<M; j++)
      fillTauler[i][j]=pareTauler[i][j];
}

/*
*	FUNCIO calculaColumna
*
*	INPUT: 	reb un tauler i un número de fill.
*	OUTPUT:  torn al acolumna on ha de realitzar el node fill amb número corresponent (descarta columnes plenes)
*/

int calculaColumna(char tauler[N][M],int numFill){
  int i,j=0;
  for (i=0; j<= numFill; i++){
    if(tauler[N-1][i]==BUIT) 
      j++;}
  return i-1;
}


/*
*	FUNCIO calculaFila
*
*	INPUT: reb un tauler i una columna on es fa el moviment
*	OUTPUT:  torna la fila on ha de caure la nova fitxa (per gravetat) a la columna corresponent
*/

int calculaFila(char tauler[N][M],int columna){
	int i;
    for (i=0; i<=N; i++) {
        if (tauler[i][columna] == BUIT)
            return i;
    } 	
}

/*
*	FUNCIO aplicaTirada
*
*	INPUT: 	reb un tauler, la columna i la fila en que realitzem el moviment, i el jugador que el reatliza
*	DESCRIPCIO:  edita el tauler afegint la tirada a la columna i fila donada.
*/

void aplicaTirada(char tauler[N][M], int columna, int fila, char jugador) {
 tauler[fila][columna]=jugador;
}

/*
*	FUNCIO nPossiblesMoviments
*
*	INPUT: 	reb un tauler
*	DESCRIPCIO: donat un tauler NxM torna el nombre de possibles moviments a fer, 
				i.e. donat el tauler d'un node ens indicara el numero de fills d'aquest,
				nota que els possibles moviments és el número de columnes no plenes.
*/

int nPossiblesMoviments(char tauler[N][M]){
  int i,j=0;
for (i=0; i<M; i++) {
  if (tauler[N-1][i]==BUIT) 
    j++;
}
return j;
}

/*
*	FUNCIO inicialitzaTauler
*
*	INPUT: 	reb un node
*	DESCRIPCIO: edita el tauler del node rebut, posant cada valor del tauler a BUIT
*/
void inicialitzaTauler (Node *node){
  int i,j;
  for (i=0; i<N; i++){
    for (j=0; j<M; j++){
      node->tauler[i][j]=BUIT;}}
}

/*
*	FUNCIO printfTauler
*
*	INPUT: 	reb un tauler
*	DESCRIPCIO: imprimeix per printf el tauler donat
*/
void printfTauler(char tauler[N][M]){
  int j,i;
  printf("\n");
  for(i=N-1;i>=0;i--){
  printf("\t\t");
    for(j=0;j<M;j++)
      printf(" %c ",tauler[i][j]);
    printf("\n");
  }
  printf("\n");
  printf("\t\t");
  for(j=1;j<=M;j++)
      printf("(%i)",j);
  printf("\n \n");
};

/*
*	FUNCIO marcaUltimaTIradaiPrintTauler
*
*	INPUT: 	reb un tauler, i 4 ints corresponents a dos posicions del tauler (2 files i dos columnes)
*	DESCRIPCIO: canvia els simbols de les posicions enviades al tauler per majuscules (J1M) i imprimeix el tauler
*				un cop impres, torna els valors originals. 		
*/

void marcaUltimaTiradaiPrintTauler(char tauler[N][M], int filaJ1, int columnaJ1, int filaJ2, int columnaJ2){
		tauler[filaJ1][columnaJ1]=J1M; // a les crides que fem a aquesta ufncio es compleix tauler[filaJ1][columnaJ1]==J1
		tauler[filaJ2][columnaJ2]=J2M;// a les crides que fem a aquesta ufncio es compleix tauler[filaJ1][columnaJ2]==J2
		printfTauler(tauler);
		tauler[filaJ1][columnaJ1]=J1;
		tauler[filaJ2][columnaJ2]=J2;
}

/*
*	FUNCIO taulerPler
*
*	INPUT: 	reb un tauler
*	DESCRIPCIO: torna 1 si el tauler està pler, 0 si no.
*/
int taulerPler (char tauler[N][M]){
  int i;
  for (i=0; i<M; i++) {
    if (tauler[N-1][i]==BUIT) {
		return 0;}
  }
  return 1;
}

/*
*	FUNCIO correctInput
*
*	INPUT: 	reb un int "n" corresponent a la columna tirada i un tauler
*
*	DESCRIPCIO: torna  1  si la tirada introduida es mes gran que el nombre maxim de columnes
*				torna -1  si la tirada introduida es zero o negativa
				torna  0  si la columna on es tira esta plena
*/
int correctInput (int n, char tauler[N][M]) {
  if (n>M) return 1;
  if (n<=0) return -1;
  if (tauler[N-1][n-1]==BUIT) return 0;
  else return 2;
}

/*
*	FUNCIO max
*
*	INPUT: 	dos dobules, a i b
*	OUTPUT: torna el valor introduit mes gran
*/
double max(double a, double b){
	if(a>b) return a;
	return b;
}

/*
*	FUNCIO min
*
*	INPUT: 	dos dobules, a i b
*	OUTPUT: torna el valor introduit mes petit
*/
double min(double a, double b){
	if(a>b) return b;
	return a;
}

/*
*	FUNCIO: minimaxAlphabeta
*
*	INPUT:  -un node
*			-el nombre de nivells que hem d'evaluar
*			-dos parametres alpha i beta per a evitar evaular nodes prescindibles
*			-un enter maximitza, pren valors 0 o 1, segons si estem a la branca de l'arbre que hem de maximitzar o minimitzar.
*	
*	DESCRIPCIO: dona un valor al score de cada node si es un node que cal ser evaluat.
				per a descartar nodes prescindibles d'evaluar usem la poda alpha-beta:
					https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
* 				Nota que usem la poda alpha-beta per a descartar els nodes que no cal evaluar 
				per evitar fer excesives crides a la funcio heuristica.
*/
void minimaxAlphabeta(Node *node, int nivells, int alpha, int beta, int maximitza){
	int i;
	double v;
	if(nivells == 0){
		node->score=heuristic(node->tauler); //evalua node
	}
	else{
		if(maximitza){
			v=-2e6;
			for(i=0; i<node->n_fills; i++ ){
				minimaxAlphabeta(node->fills[i],nivells-1, alpha,beta,0);
				v=max(v,node->fills[i]->score);
				alpha=max(alpha,v);
				if(beta<=alpha) 
					break;//no cal evaular node
			}	
		}
		else{
			v=2e6;
			for(i=0; i<node->n_fills; i++){
				minimaxAlphabeta(node->fills[i],nivells-1,alpha,beta,1);
				v=min(v,node->fills[i]->score);
				beta = min(beta, v);
				if(beta<=alpha)  //no cal evaular node
					break;
			}
			
		}
		node->score=v;		
	}
}	

/*
*	FUNCIO minimaxMove
*
*	INPUT: 	un node
*	OUTPUT: torna el nombre de node fill que tingui el mateix score que el node pare (cami optim),
			per a que tingui sentit usar minimaxMove primer cal tenir un arbre evaluat.
			Per evaluar l'arbre usem minimaxAlphabeta
*/
int minimaxMove(Node *node){
		int i;
		for (i=0; i<node->n_fills; i++){
			if(node->fills[i]->score == node->score)
				return i;
		}
	}

