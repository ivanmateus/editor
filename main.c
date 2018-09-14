/*****************************************/
/* Autor: Ivan Mateus de Lima Azevedo    */
/* No. USP: 10525602                     */
/*****************************************/

//Inclusao das bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERRO 0

//Definicao da struct de lista encadeada
struct no{
	char *dado;
	int index;
	struct no *prox;
	struct no *ant;
};

typedef struct no No;	//Definicao de um no da lista
typedef struct no* Lista;	//Definicao da lista em si

//Construtor da lista
Lista *criaLista(){

	Lista *li = (Lista *)malloc(sizeof(Lista));

	if(li != NULL){
		*li = NULL;
	}
	return li;
}

//Funcao que cria um no novo
No *criaNo(char *dado, int index){

	No *no = (No *)malloc(sizeof(No));

    if(no == NULL){
        return ERRO;
	}

	no->dado = calloc(strlen(dado), sizeof(char));
    strcpy(no->dado, dado);
	no->index = index;
	no->prox = NULL;
    no->ant = NULL;
	return no;
}

//Funcao que insere os nos no fim da lista
int insereFim(Lista *li, char *dado, int index){

	if(li == NULL){
		return ERRO;
	}
	if((dado[0] >= 'A' && dado[0] <= 'Z') || (dado[0] >= 'a' && dado[0] <= 'z') || (dado[0] >= '0' && dado[0] <= '9')){
		No *no = criaNo(dado, index);
		if(*li == NULL){
			*li = no;
		}else{
			(*li)->prox = no;
			no->ant = *li;
			*li = no;
		}
	}else{
		int i = 0;
		char *auxChar = calloc(2, sizeof(char));
		while(i < strlen(dado)){
			*auxChar = dado[i];
			No *no = criaNo(auxChar, index++);

			if(*li == NULL){
				*li = no;
			}else{
				(*li)->prox = no;
				no->ant = *li;
				*li = no;
			}
			++i;
		}
	}

	return OK;
}

void positInit(Lista *li){

	while((*li)->ant != NULL){
		(*li) = (*li)->ant;
	}
}

char *procuraCarac(char *palavra){

	char *aux = palavra;
	while(*aux != '\0'){
		if((*aux >= 'A' && *aux <= 'Z') || (*aux >= 'a' && *aux <= 'z') || (*aux >= '0' && *aux <= '9')){
			++aux;
		}else{
			if(*aux == '\n'){
				return aux;
			}else{
				return aux;
			}
		}
	}
	return NULL;
}

void apagaChar(char *palavra, char carac){

	char *aux = palavra;
	while(*aux != '\0'){
		if(*aux == carac){
			*aux = '\0';
			return;
		}
		++aux;
	}
}

void apagaCharArray(char *array){

	char *aux = array;
	while(*aux != '\0'){
		*aux = '\0';
		++aux;
	}
}

void imprimeLista(Lista *li){

	No *aux = *li;
	while(aux != NULL){
		printf("[%d] [%s] ",aux->index, aux->dado);
		aux = aux->prox;
	}
	printf("\n");
}

char *nameArq(){
	char *nome = calloc(5, sizeof(char));
	scanf("%s", nome);
	return nome;
}

int insereAntes(Lista *li, char *dado, int index){

	if(li == NULL){
		return ERRO;
	}
	if((dado[0] >= 'A' && dado[0] <= 'Z') || (dado[0] >= 'a' && dado[0] <= 'z') || (dado[0] >= '0' && dado[0] <= '9')){
		No *no = criaNo(dado, index);
		if(*li == NULL){
			*li = no;
		}else{
			no->ant = (*li)->ant;
			(*li)->ant = no;
			no->prox = *li;
			if(no->ant != NULL){
				no->ant->prox = no;
			}
		}
	}else{
		int i = 0;
		char *auxChar = calloc(2, sizeof(char));
		while(i < strlen(dado)){
			*auxChar = dado[i];
			No *no = criaNo(auxChar, index++);

			if(*li == NULL){
				*li = no;
			}else{
				no->ant = (*li)->ant;
				(*li)->ant = no;
				no->prox = *li;
				if(no->ant != NULL){
					no->ant->prox = no;
				}
			}
			++i;
		}
	}
	No *no = *li;
	while(no != NULL){
		++no->index;
		no = no->prox;
	}
	return OK;
}

int insereDepois(Lista *li, char *dado, int index){

	if(li == NULL){
		return ERRO;
	}
	if((dado[0] >= 'A' && dado[0] <= 'Z') || (dado[0] >= 'a' && dado[0] <= 'z') || (dado[0] >= '0' && dado[0] <= '9')){
		No *no = criaNo(dado, index);
		if(*li == NULL){
			*li = no;
		}else{
			no->prox = (*li)->prox;
			(*li)->prox = no;
			no->ant = (*li);
			if(no->prox != NULL){
				(no->prox)->ant = no;
			}
		}
	}else{
		int i = 0;
		char *auxChar = calloc(2, sizeof(char));
		while(i < strlen(dado)){
			*auxChar = dado[i];
			No *no = criaNo(auxChar, index++);

			if(*li == NULL){
				*li = no;
			}else{
				no->prox = (*li)->prox;
				(*li)->prox = no;
				no->ant = (*li);
				if(no->prox != NULL){
					(no->prox)->ant = no;
				}
			}
			++i;
		}
	}
	No *no = *li;
	no = no->prox;
	while(no != NULL){
		++no->index;
		no = no->prox;
	}

	return OK;
}

int removeAtual(Lista *cursor){

	if(cursor == NULL){
		return ERRO;
	}

	No *aux1 = *cursor;
	printf("cu %s a1 %s\n", (*cursor)->dado, aux1->dado);
	*cursor = aux1->prox;
	printf("cu %s a1 %s\n", (*cursor)->dado, aux1->dado);
	aux1->prox->ant = aux1->ant;
	printf("cu %s a1 %s\n", (*cursor)->dado, aux1->dado);
	aux1->ant->prox = aux1->prox;
	printf("cu %s a1 %s\n", (*cursor)->dado, aux1->dado);
	aux1->prox = NULL;
	printf("cu %s a1 %s\n", (*cursor)->dado, aux1->dado);
	aux1->ant = NULL;
	printf("cu %s a1 %s\n", (*cursor)->dado, aux1->dado);
	free(aux1);
	No *aux2 = *cursor;
	while(aux2 != NULL){
		--(aux2->index);
		aux2 = aux2->prox;
	}
	return OK;
}

int removePrim(Lista *cursor){

	if(cursor == NULL){
		return ERRO;
	}
	No *aux1 = *cursor;
	printf("cu %s a1 %s\n", (*cursor)->dado, aux1->dado);
	aux1->prox->ant = NULL;
	printf("cu %s a1 %s\n", (*cursor)->dado, aux1->dado);
	*cursor = aux1->prox;
	printf("cu %s a1 %s\n", (*cursor)->dado, aux1->dado);
	aux1->prox = NULL;
	printf("cu %s a1 %s\n", (*cursor)->dado, aux1->dado);
	free(aux1);
	No *aux2 = *cursor;
	while(aux2 != NULL){
		--(aux2->index);
		aux2 = aux2->prox;
	}
	return OK;
}

int removeUlt(Lista *cursor){

	if(cursor == NULL){
		return ERRO;
	}
	No *aux = (*cursor);
	*cursor = aux->ant;
	aux->ant->prox = NULL;
	free(aux);
	return OK;
}

Lista *lerArq(char *nome){

	strcat(nome, ".ext");
	FILE *arqEnt = fopen(nome, "rt");
	Lista *liHead = criaLista();
	Lista *liAux = liHead;
	if(arqEnt == NULL){
		printf("Erro!\n");
		return liHead;
	}
	int i = 0;
	int j = 0;
	char auxLinha[300];
	char caracteres[30];
	char *auxChar;
	char *auxPalavra;

	while(fgets(auxLinha, 299, arqEnt)){
		auxPalavra = strtok(auxLinha, " ");
		while(auxPalavra != NULL){
			i = 0;
			auxChar = procuraCarac(auxPalavra);
			while(auxChar != NULL){
				caracteres[i] = *auxChar;
				auxChar = procuraCarac(auxChar + 1);
				++i;
			}
			caracteres[i] = '\0';
			if(strcmp(caracteres, "") == 0){
				insereFim(liAux, auxPalavra, j);
				++j;
			}else{
				if(auxPalavra[0] != caracteres[0]){
					apagaChar(auxPalavra, caracteres[0]);
					insereFim(liAux, auxPalavra, j);
					++j;
				}
				insereFim(liAux, caracteres, j);
				apagaCharArray(caracteres);
				j = j + strlen(caracteres);
			}
			auxPalavra = strtok(NULL, " ");
		}
	}
	positInit(liHead);
	return liHead;
}

int buscaPalavra(Lista *cursor, char *dado){

	No *aux = (*cursor);
	while(aux != NULL){
		if(strcmp(aux->dado, dado) == 0){
			printf("%d\n", aux->index);
			return OK;
		}
		aux = aux->prox;
	}
	return ERRO;
}

void comandos(Lista *li){

	Lista *cursor = li;
	char comando = '0';
	char auxPalavra[30];

	while(comando != 's'){
		scanf(" %c", &comando);
		switch(comando) {
			case 'i':
				scanf(" %s", auxPalavra);
				if((auxPalavra[0] >= 'A' && auxPalavra[0] <= 'Z') || (auxPalavra[0] >= 'a' && auxPalavra[0] <= 'z') || (auxPalavra[0] >= '0' && auxPalavra[0] <= '9')){
					insereAntes(cursor, auxPalavra, (*cursor)->index);
				}else{
					insereAntes(cursor, auxPalavra, (*cursor)->index);
				}
				break;
			case 'a':
				scanf(" %s", auxPalavra);
				if((auxPalavra[0] >= 'A' && auxPalavra[0] <= 'Z') || (auxPalavra[0] >= 'a' && auxPalavra[0] <= 'z') || (auxPalavra[0] >= '0' && auxPalavra[0] <= '9')){
					insereDepois(cursor, auxPalavra, (*cursor)->index);
				}else{
					insereDepois(cursor, auxPalavra, (*cursor)->index);
				}
				break;
			case 'r':
				scanf(" %s", auxPalavra);
				if((*cursor)->prox == NULL){
					removeUlt(cursor);
					insereDepois(cursor, auxPalavra, (*cursor)->index);
				}else{
					if((*cursor)->ant == NULL){
						removePrim(cursor);
						insereAntes(cursor, auxPalavra, (*cursor)->index);
					}else{
						removeAtual(cursor);
						insereDepois(cursor, auxPalavra, (*cursor)->index);
					}
				}
				break;
			case 'f':
				scanf(" %s", auxPalavra);
				buscaPalavra(cursor, auxPalavra);
				break;
			case 'd':
				if((*cursor)->prox == NULL){
					removeUlt(cursor);
				}else{
					if((*cursor)->ant == NULL){
						removePrim(cursor);
					}else{
						removeAtual(cursor);
					}
				}
				printf("d atu %s\n", (*cursor)->dado);
				printf("d ant %s\n", (*cursor)->ant->dado);
				printf("d pro %s\n", (*cursor)->prox->dado);
				break;
			case 'n':
				cursor = &((*cursor)->prox);
				printf("n atu %s\n", (*cursor)->dado);
				printf("n ant %s\n", (*cursor)->ant->dado);
				printf("n pro %s\n", (*cursor)->prox->dado);
				break;
			case 'p':
				break;
			case 'b':
				break;
			case 'e':
				break;
			case 'g':
				break;
			case 's':
				while((*cursor)->ant != NULL){
					cursor = &((*cursor)->ant);
				}
				imprimeLista(li);
				break;
		}
	}
}

int main(int argc, char const *argv[])
{
	Lista *li = criaLista();
	char *nome = nameArq();
	li = lerArq(nome);
	comandos(li);
	return 0;
}
