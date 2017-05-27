typedef struct node { //struct fonalmental del codi
  struct node **fills;//apuntador a un vector de nodes
  int n_fills; //nombre de fills del node (columnes buides)
  char tauler[N][M]; //tauler del node
  int filaMoviment; //fila on es fa el darrer moviment
  int columnaMoviment; //columna on es fa el darrer moviment
  double score; // valor de la funcio heuristica evaluant el tauler del node (si es un node terminal) o el valor corresponent a la posicio del arbre quoe ocupa.
} Node;


Node *creaNode (Node*, int ,char); // crea un node
void crea1Nivell(Node*, char); // crea tots els fills d'un node
void creaArbre (Node*, int); // crea l'arbre de nodes fins al nombre de nivells que desitgem

void esborraNode(Node*); //esborra un node
void esborra1Nivell (Node *arrel);  // esborra tots els fills d'un node
void esborraArbre (Node*, int); // esborra tots els nodes d'un arbre fins al nombre de nivells que desitgem


void copiaTauler(char fillTauler[N][M], char pareTauler[N][M]); //copia els valors del pareTauler al fillTauler
int calculaColumna(char tauler[N][M],int numFill); // donat tauler i un numero de node, calcula la columna del moviment que li correspon
int calculaFila(char tauler[N][M], int ); //donat la columna on es fa moviment torna la fila on caura per gravetat la fitxa
void aplicaTirada(char tauler[N][M], int , int , char ); //donat un tauler, aplica la tirada del jugaror introduit a la fila i columnes introduides
int nPossiblesMoviments(char tauler[N][M]); //columnes buides del tauler introduit

void inicialitzaTauler (Node*); //edita el tauler del node rebut, posant cada valor del tauler a BUIT
void printfTauler(char tauler[N][M]);//imprimeix per printf el tauler donat
void marcaUltimaTiradaiPrintTauler(char tauler[N][M], int, int, int, int);//marca derreres tirades de cada jugador i fa el print

int taulerPler (char tauler[N][M]);//torna 1 si el tauler està pler, 0 si no.
int correctInput (int n, char tauler[N][M]);//comprova que el input de tirada sigui posible realitzar-se

void minimaxAlphabeta(Node *node, int nivells, int alpha, int beta, int maximitza);//evaula tots els nodes necessaris de l'arbre amb la funcio heuristica
int minimaxMove(Node *node);//tria el node corresponent al cami optim del minimax (millor tirada calculada segons la funcio heuristica)
