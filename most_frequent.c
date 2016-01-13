#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIM_PAROLA 30
#define DIM_PAROLE 250000
#define DIM_RIGA 256

typedef struct s_parola{
	char* parola;
	int frequenza;
}t_parola;

int compare(const void *a, const void *b) { 
    struct s_parola *ia = (struct t_parola *)a;
    struct s_parola *ib = (struct t_parola *)b;
    return strcmp(ia->parola, ib->parola);
} 

int last_occurence(char* word, t_parola* tmp, int last){
	while(strcmp(tmp[last+1].parola, word) == 0){
		last++;
	}
	return last;
}

char* find_max(t_parola* parole, int len){
	int i;
	int max = 0;
	char* winner; // parola più presente
	for(i=0;i<len-1422;i++){
		if(parole[i].frequenza > max){
			winner = parole[i].parola;
			max = parole[i].frequenza;
		}
	}
	return winner;
}

void main(){
	int i;
	t_parola* parole = malloc(sizeof(struct s_parola)*DIM_PAROLE);
	
	FILE* fp = fopen("i_promessi_sposi.txt", "r");
	
	if(fp == NULL){
		printf("\n Il file non è stato aperto correttamente.");
		exit(1);
	}
	// Leggo le parole dal file e le inserisco nella struct 
	const char separators[] = "\t\n\v\r\f !\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~";
	char buffer[DIM_RIGA];
	char *rest, *line, *word;
	int conta = 0;
	while (fgets(buffer, sizeof(buffer), fp)) {
		rest = line = buffer;
		while ((word = strtok_s(line, separators, &rest))) {
			char* dest = malloc(sizeof(char)*DIM_PAROLA);
			dest = strdup(word);
			(parole+conta)->parola = dest;
			conta++;
			line=rest;
		}
	}
	// Ordino alfabeticamente la struct
	qsort(parole, conta, sizeof(struct s_parola), compare);

	int last;
	int contatore = 0;
	int incremento = 1;
	// Conto occorrenze
	while(contatore<conta-1422){
		last = last_occurence(parole[contatore].parola, parole, contatore);
		parole[contatore].frequenza = (last - contatore) + 1;
		if(last - contatore == 0)
			contatore += incremento;
		else
			contatore = last + 1;
	}
	
	// Trovo la parole con il numero massimo di occorrenze
	char* max = find_max(parole, conta);
	printf("La parola piu presente --> %s\n", max);
	
	// Stampo contenuto della struct
	//for(i=0;i<200;i++)
	//	printf("%s --> %i\n", parole[i].parola, parole[i].frequenza);		
	
}
