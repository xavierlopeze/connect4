/*
*	FITXER: 4enratlla.c
*	DESCRIPCIO: la funcio del fitxer es definir la funcio IVenRatlla(tauler, jugador), 
*				que ens permet saber donat un tauler i un jugador si aquest jugador 
*				ha conectat 4 peces d'alguna forma possible (en fila, columna o diagonal).
*				
*/

#include"4enratlla.h"

/*
*	FUNCIO IVenRatlla
*
*	INPUT: 	reb un tauler i un jugador (J1 o J2)
*	OUTPU: 	torna 1 si el jugador 	 ha conectat 4 peces (fila, columna o diagonal)
			torna 0 si el jugador no ha conectat 4 peces (fila, columna o diagonal)
*/

int IVenRatlla(char tauler[N][M], char jugador){
	if(	IVenFila(tauler, jugador) || 
		IVenColumna(tauler,jugador) ||
		IVenDiagonal(tauler,jugador)){
		return 1;
	}
	return 0;
}

/*
*	FUNCIO IVenFila
*
*	INPUT: 	reb un tauler i un jugador (J1 o J2)
*	OUTPU: 	torna 1 si    hi ha 4 peces en fila del mateix jugador en alguna posicio del tauler
			torna 0 si NO hi ha 4 peces en fila del mateix jugador en alguna posicio del tauler
*/
int IVenFila(char tauler[N][M], char jugador){
	int i,j;
	int n; // n conta el nombre de peces iguals seguides a la mateixa fila
	for(i=0; i<N; i++){
		n =0;
		for(j=0; j<M; j++)
			if(tauler[i][j]==jugador){
				n++;
				if(n==4)
					return 1;
			}
			else
				n = 0;
	}
	return 0;
}

/*
*	FUNCIO IVenColumna
*
*	INPUT: 	reb un tauler i un jugador (J1 o J2)
*	OUTPU: 	torna 1 si    hi ha 4 peces en columna del mateix jugador en alguna posicio del tauler
			torna 0 si NO hi ha 4 peces en columna del mateix jugador en alguna posicio del tauler
*/
int IVenColumna(char tauler[N][M], char jugador){
	int i,j;
	int n; // n conta el nombre de peces iguals seguides a la mateixa columna
	for(j=0; j<M; j++){
		n =0;
		for(i=0; i<N; i++)
			if(tauler[i][j]==jugador){
				n++;
				if(n==4)
					return 1;
			}
			else
				n = 0;
	}
	return 0;
}

/*
*	FUNCIO IVenDiagonal
*
*	INPUT: 	reb un tauler i un jugador (J1 o J2)
*	OUTPU: 	torna 1 si    hi ha 4 peces en diagonal del mateix jugador en alguna posicio del tauler
			torna 0 si NO hi ha 4 peces en diagonal del mateix jugador en alguna posicio del tauler
*/

int IVenDiagonal(char tauler[N][M], char jugador){
	int i,j;
	
	for(i=0; i<N-3; i++)
		for(j=0; j<M-3; j++)
			if(	tauler[i][j]==jugador &&
				tauler[i+1][j+1]==jugador &&
				tauler[i+2][j+2]==jugador &&
				tauler[i+3][j+3]==jugador)
			return 1; //tenim diagonal per la dreta
	
	for(i=3; i<N; i++)
		for(j=0; j<M-3; j++)
			if(	tauler[i][j]==jugador &&
				tauler[i-1][j+1]==jugador &&
				tauler[i-2][j+2]==jugador &&
				tauler[i-3][j+3]==jugador)
			return 1; // tenim diagonal per l'esquerra
	
	return 0;
}






