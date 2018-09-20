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
		No *no = NULL;
		while(i < strlen(dado)){
			*auxChar = dado[i];
			no = criaNo(auxChar, index);
			if(*li == NULL){
				*li = no;
			}else{
				(*li)->prox = no;
				no->ant = *li;
				*li = no;
			}
			++i;
			++index;
		}
	}

	return OK;
}

void positInit(Lista *li, int numPos){

	int i = 0;
	if(numPos == 0){
		while((*li)->ant != NULL){
			(*li) = (*li)->ant;
		}
		return;
	}
	while(((*li)->ant != NULL) && (i < numPos)){
		(*li) = (*li)->ant;
		++i;
	}
}

void positFim(Lista *li, int numPos){

	int i = 0;
	if(numPos == 0){
		while((*li)->prox != NULL){
			(*li) = (*li)->prox;
		}
		return;
	}
	while(((*li)->prox != NULL) && (i < numPos)){
		(*li) = (*li)->prox;
		++i;
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

int ehEsp(char *auxPalavra){
	if((auxPalavra[0] >= 'A' && auxPalavra[0] <= 'Z') || (auxPalavra[0] >= 'a' && auxPalavra[0] <= 'z') || (auxPalavra[0] >= '0' && auxPalavra[0] <= '9')){
		return 0;
	}
	return 1;
}

void imprimeLista(Lista *li){

	No *aux = *li;
	while(aux != NULL){
		if(aux->prox != NULL){
			if(ehEsp(aux->prox->dado)){
				printf("%s", aux->dado);
			}else{
				if(aux->dado[0] == '\n'){
					printf("%s", aux->dado);	
				}else{
					printf("%s ", aux->dado);
				}
			}
		}else{
			printf("%s", aux->dado);
		}
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
	No *no = criaNo(dado, index);
	if(*li == NULL){
		*li = no;
		return OK;
	}
	No *aux1 = (*li)->ant;
	(*li)->ant = no;
	no->prox = *li;
	no->ant = aux1;
	if(aux1 != NULL){
		aux1->prox = no;
	}
	
	No *aux = *li;
	while(aux != NULL){
		++(aux->index);
		aux = aux->prox;
	}
	return OK;
}

int insereDepois(Lista *li, char *dado, int index){

	if(li == NULL){
		return ERRO;
	}
	No *no = criaNo(dado, index);
	if(*li == NULL){
		*li = no;
		return OK;
	}
	no->prox = (*li)->prox;
	(*li)->prox = no;
	no->ant = (*li);
	if(no->prox != NULL){
		(no->prox)->ant = no;
	}
	
	No *aux = *li;
	aux = aux->prox;
	while(aux != NULL){
		++aux->index;
		aux = aux->prox;
	}

	return OK;
}

int removeAtual(Lista *cursor){

	if(cursor == NULL){
		return ERRO;
	}
	*cursor = (*cursor)->prox;
	No *aux1 = (*cursor)->ant;
	aux1->ant->prox = aux1->prox;
	aux1->prox->ant = aux1->ant;
	aux1->prox = NULL;
	aux1->ant = NULL;
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
	*cursor = (*cursor)->prox;
	No *aux1 = (*cursor)->ant;
	aux1->prox->ant = NULL;
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
	*cursor = (*cursor)->ant;
	No *aux1 = (*cursor)->prox;
	aux1->ant->prox = NULL;
	free(aux1);
	return OK;
}

Lista *lerArq(char *nome){

	Lista *liHead = criaLista();
	Lista *liAux = liHead;
	strcat(nome, ".ext");
	FILE *arqEnt = fopen(nome, "rt");
	while(arqEnt == NULL){
		printf("Arquivo nao encontrado. Digite novamente: \n");
		nome = nameArq();
		strcat(nome, ".ext");
		arqEnt = fopen(nome, "rt");
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
				j = j + strlen(caracteres);
				apagaCharArray(caracteres);
			}
			auxPalavra = strtok(NULL, " ");
		}
	}
	fclose(arqEnt);
	positInit(liHead, 0);
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

void removeNL(char *input){ 
    int len = strlen(input);
    if(input[0] == '\n'){
    	return;
    }
    if (len > 0 && input[len-1] == '\n') {
        input[--len] = '\0';
    }
}

int getNumber(char *palavra){

	char *endBuff;
	removeNL(palavra);
	int number = strtol(palavra, &endBuff, 10);
    while (*endBuff != '\0'){
        printf("Por favor digite um numero valido: ");
        fgets(palavra, 127, stdin);
        removeNL(palavra);
        number = strtol(palavra, &endBuff, 10);
    }
    return number;
}

void destroi(Lista *li){

	while((*li) != NULL){
		*li = (*li)->prox;
		if(*li != NULL){
			free((*li)->ant);
		}
	}
}

void comandos(Lista *li){

	Lista *cursor = li;
	char comando;
	char auxLinha[30];
	char *auxPalavra;
	int numPos = 0;

	while(comando != 's'){
		fgets(auxLinha, sizeof(auxLinha), stdin);
		auxPalavra = strtok(auxLinha, " ");
		comando = auxPalavra[0];
		switch(comando) {
			case 'i':
				auxPalavra = strtok(NULL, " ");
				removeNL(auxPalavra);
				if(ehEsp(auxPalavra) && (strlen(auxPalavra) > 1)){
					break;
				}
				insereAntes(cursor, auxPalavra, (*cursor)->index);
				break;
			case 'a':
				auxPalavra = strtok(NULL, " ");
				removeNL(auxPalavra);
				if(ehEsp(auxPalavra) && (strlen(auxPalavra) > 1)){
					break;
				}
				insereDepois(cursor, auxPalavra, (*cursor)->index);
				break;
			case 'r':
				auxPalavra = strtok(NULL, " ");
				removeNL(auxPalavra);
				if((*cursor)->prox == NULL){
					removeUlt(cursor);
					insereDepois(cursor, auxPalavra, (*cursor)->index);
				}else{
					if((*cursor)->ant == NULL){
						removePrim(cursor);
						insereAntes(cursor, auxPalavra, (*cursor)->index);
						*cursor = (*cursor)->ant;
					}else{
						removeAtual(cursor);
						insereAntes(cursor, auxPalavra, (*cursor)->index);
						*cursor = (*cursor)->ant;
					}
				}
				break;
			case 'f':
				auxPalavra = strtok(NULL, " ");
				removeNL(auxPalavra);
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
				break;
			case 'n':
				if((*cursor)->prox != NULL){
					positFim(cursor,1);
				}
				break;
			case 'p':
				if((*cursor)->ant != NULL){
					positInit(cursor,1);
				}
				break;
			case 'b':
				positInit(cursor, 0);
				break;
			case 'e':
				positFim(cursor, 0);
				break;
			case 'g':
				auxPalavra = strtok(NULL, " ");
				numPos = getNumber(auxPalavra);
				if(numPos < 0){
					numPos = (-1)*numPos;
					positInit(cursor, numPos);
				}else{
					positFim(cursor, numPos);
				}
				break;
			case 's':
				positInit(cursor, 0);
				imprimeLista(cursor);
				destroi(cursor);
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
