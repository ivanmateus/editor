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
	char *dadoComum;
	char dadoEsp;
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
No *criaNo(char *dadoComum, char dadoEsp){

	No *no = (No *)malloc(sizeof(No));

    if(no == NULL){
        return ERRO;
	}

	no->dadoComum = calloc(strlen(dadoComum), sizeof(char));
    strcpy(no->dadoComum, dadoComum);
	no->dadoEsp = dadoEsp;
	no->prox = NULL;
    no->ant = NULL;
	return no;
}

//Funcao que insere os nos no fim da lista
int insereFim(Lista *li, char *dadoComum, char *array){

	if(li == NULL){
		return ERRO;
	}
	if(strcmp(dadoComum, "") != 0){
		No *no = criaNo(dadoComum, '0');
		if(*li == NULL){
			*li = no;
		}else{
			(*li)->prox = no;
			no->ant = *li;
			*li = no;
		}
	}else{
		int i = 0;

		while(i < strlen(array)){
			No *no = criaNo("", array[i]);

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
		if(strcmp(aux->dadoComum, "") == 0){
			printf("[%c] ", aux->dadoEsp);
		}else{
			printf("[%s] ", aux->dadoComum);
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

int insereAntes(Lista *li, char *dadoComum, char *array){

	if(li == NULL){
		return ERRO;
	}
	if(strcmp(dadoComum, "") != 0){
		No *no = criaNo(dadoComum, '0');
		if(*li == NULL){
			*li = no;
		}else{
			(*li)->ant = no;
			no->prox = *li;
			*li = no;
		}
	}else{
		int i = 0;

		while(i < strlen(array)){
			No *no = criaNo("", array[i]);

			if(*li == NULL){
				*li = no;
			}else{
				(*li)->ant = no;
				no->prox = *li;
				*li = no;
			}
			++i;
		}
	}

	return OK;
}

int insereDepois(Lista *li, char *dadoComum, char *array){

	if(li == NULL){
		return ERRO;
	}
	if(strcmp(dadoComum, "") != 0){
		No *no = criaNo(dadoComum, '0');
		if(*li == NULL){
			*li = no;
		}else{
			no->ant = (*li);
			no->prox = (*li)->prox;
			(*li)->prox = no;
			((*li)->prox)->ant = no;
		}
	}else{
		int i = 0;

		while(i < strlen(array)){
			No *no = criaNo("", array[i]);

			if(*li == NULL){
				*li = no;
			}else{
				no->ant = (*li);
				no->prox = (*li)->prox;
				(*li)->prox = no;
				((*li)->prox)->ant = no;
			}
			++i;
		}
	}

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
				apagaChar(auxPalavra, caracteres[0]);
				insereFim(liAux, auxPalavra, "0");
			}else{
				if(auxPalavra[0] != caracteres[0]){
					apagaChar(auxPalavra, caracteres[0]);
					insereFim(liAux, auxPalavra, "0");
				}
				insereFim(liAux, "", caracteres);
				apagaCharArray(caracteres);
			}
			auxPalavra = strtok(NULL, " ");
		}
	}
	positInit(liHead);
	return liHead;
}

int removeNo(Lista *li){
	if(li == NULL){
		return ERRO;
	}
	if(strcmp(dadoComum, "") != 0){
		No *no = criaNo(dadoComum, '0');
		if(*li == NULL){
			*li = no;
		}else{
			no->ant = (*li);
			no->prox = (*li)->prox;
			(*li)->prox = no;
			((*li)->prox)->ant = no;
		}
	}else{
		int i = 0;

		while(i < strlen(array)){
			No *no = criaNo("", array[i]);

			if(*li == NULL){
				*li = no;
			}else{
				no->ant = (*li);
				no->prox = (*li)->prox;
				(*li)->prox = no;
				((*li)->prox)->ant = no;
			}
			++i;
		}
	}

	return OK;
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
					insereAntes(cursor, auxPalavra, "0");
				}else{
					insereAntes(cursor, "", auxPalavra);
				}
				break;
			case 'a':
				scanf(" %s", auxPalavra);
				if((auxPalavra[0] >= 'A' && auxPalavra[0] <= 'Z') || (auxPalavra[0] >= 'a' && auxPalavra[0] <= 'z') || (auxPalavra[0] >= '0' && auxPalavra[0] <= '9')){
					insereDepois(cursor, auxPalavra, "0");
				}else{
					insereDepois(cursor, "", auxPalavra);
				}
				break;
			case 'r':
				break;
			case 'f':
				break;
			case 'd':
				break;
			case 'n':
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

