#include"heuristic.h"

 /*
 * FUNCIO scoreNode
 *
 * INPUT: reb un tauler
 * OUTPUT: torna un valor per al tauler (funcio heuristica)
 */
double heuristic(char tauler[N][M]){
	int liniesJ1, liniesJ2;
	
	if(IVenRatlla(tauler, J1)) //humà guanya, com més petit més fàcil per el huma guanyar
		return -1e6;
	else if (IVenRatlla(tauler,J2)) // ordi guanya
		return 1e6;
	else{
		return columnesGuanyadores(tauler,J2)+filesGuanyadores(tauler,J2)+diagonalsGuanyadores(tauler,J2)-columnesGuanyadores(tauler,J1)-filesGuanyadores(tauler,J1)-diagonalsGuanyadores(tauler, J1);
	}
}


/*
*	FUNCIO columnesGuanyadores
*
*	INPUT: 	reb un tauler i un jugador
*	DESCRIPCIO: torna el nombre de columnes (grups de 4 peces) en que el jugador té al menys una fitxa seva
*				i cap del jugador rival, és a dir, són buides o del mateix jugador.				
*/
double columnesGuanyadores(char tauler[N][M], char jugador){
	int i,j;
	double cols=0;
	for (i=3; i<N; i++){
		for(j=0; j<M; j++){
			if(tauler[i][j]==jugador 
			&& tauler[i-1][j]!=jugadorRival(jugador)
			&& tauler[i-2][j]!=jugadorRival(jugador)
			&& tauler[i-3][j]!=jugadorRival(jugador))
				cols++;
		}
	}
	return cols;
}

/*
*	FUNCIO filesGuanyadores
*
*	INPUT: 	reb un tauler i un jugador
*	DESCRIPCIO: torna el nombre de files (grups de 4 peces) en que el jugador té al menys una fitxa seva
*				i cap del jugador rival, és a dir, són buides o del mateix jugador.				
*/
double filesGuanyadores(char tauler[N][M], char jugador){
	int i,j;
	double files=0;
	for (i=0; i<N; i++){
		for(j=3; j<M; j++){
			if(tauler[i][j]==jugador 
			&& tauler[i][j-1]!=jugadorRival(jugador)
			&& tauler[i][j-2]!=jugadorRival(jugador)
			&& tauler[i][j-3]!=jugadorRival(jugador))
				files++;
		}
	}
	return files;
}
/*
*	FUNCIO filesGuanyadores
*
*	INPUT: 	reb un tauler i un jugador
*	DESCRIPCIO: torna el nombre de diagonals (grups de 4 peces) en que el jugador té al menys una fitxa seva
*				i cap del jugador rival, és a dir, són buides o del mateix jugador.				
*/
double diagonalsGuanyadores(char tauler[N][M], char jugador){
	int i,j;
	double diags=0;
	for(i=3; i<N; i++){
		for(j=3; j<M; j++){
			if(tauler[i][j]==jugador 
			&& tauler[i-1][j-1]!=jugadorRival(jugador)
			&& tauler[i-2][j-2]!=jugadorRival(jugador)
			&& tauler[i-3][j-3]!=jugadorRival(jugador))
				diags++;
		}
	}
	for(i=0; i<N-3; i++){
		for(j=3; j<M; j++){
			if(tauler[i][j]==jugador 
			&& tauler[i+1][j-1]!=jugadorRival(jugador)
			&& tauler[i+2][j-2]!=jugadorRival(jugador)
			&& tauler[i+3][j-3]!=jugadorRival(jugador))
				diags++;
		}
	}
	return diags;
}


/*
*	FUNCIO jugadorRival
*
*	INPUT: 	reb un jugador
*	DESCRIPCIO: torna el jugador rival			
*/
char jugadorRival(char jugador){
	if(jugador == J1) return J2;
	return J1;
}
