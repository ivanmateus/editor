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

typedef char* tipo;

struct no{
	tipo dado;
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
No *criaNo(tipo dado){

	No *no = (No *)malloc(sizeof(No));

    if(no == NULL){
        return ERRO;
	}

	no->dado = calloc(strlen(dado), sizeof(char));
    strcpy(no->dado, dado);
	no->prox = NULL;
    no->ant = NULL;
	return no;
}

//Funcao que insere os nos no fim da lista
int insereFim(Lista *li, tipo dado){

	if(li == NULL){
		return ERRO;
	}

	No *no = criaNo(dado);
	if(*li == NULL){
		*li = no;
	}else{
		(*li)->prox = no;
		no->ant = *li;
		*li = no;
	}
	
	return OK;
}

void positInit(Lista *li){

	while((*li)->ant != NULL){
		(*li) = (*li)->ant;
	}
}

Lista *lerArq(tipo nome){

	FILE *arqEnt = fopen(nome, "rt");
	Lista *liHead = criaLista();
	if(arqEnt == NULL){
		printf("Erro!\n");
		return liHead;
	}
	char aux[30];

	while(fscanf(arqEnt, "%s", aux) != EOF){
		insereFim(liHead, aux);
	}

	positInit(liHead);
	return liHead;
}

void imprimeLista(Lista *li){

	Lista *aux = li;
	while(*aux != NULL){
		printf("%s ", (*aux)->dado);
		*aux = (*aux)->prox;
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	Lista *li = criaLista();
	char *nome = malloc(sizeof(char));
	strcpy(nome, "1");
	strcat(nome, ".ext");
	li = lerArq(nome);
	imprimeLista(li);
	return 0;
}