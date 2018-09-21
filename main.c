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

//Funcao que verifica se eh um
//caractere especial ou se eh uma palavra normal
int ehEsp(char *auxPalavra){
	if((auxPalavra[0] >= 'A' && auxPalavra[0] <= 'Z') || (auxPalavra[0] >= 'a' && auxPalavra[0] <= 'z') || (auxPalavra[0] >= '0' && auxPalavra[0] <= '9')){
		return 0;
	}
	return 1;
}

//Funcao que insere os nos no fim da lista
int insereFim(Lista *li, char *dado, int index){

	//Se a lista estiver vazia
	if(li == NULL){
		return ERRO;
	}
	//Se nao for um caractere especial
	if(!ehEsp(dado)){
		No *no = criaNo(dado, index);
		//Se for o primeiro no
		if(*li == NULL){
			*li = no;
		}else{	//Senao, insere na frente
			(*li)->prox = no;
			no->ant = *li;
			*li = no;
		}
	}else{	//Se for um caractere especial
		int i = 0;
		char *auxChar = calloc(2, sizeof(char));
		No *no = NULL;
		while(i < strlen(dado)){	//Enquanto houver caracteres
			*auxChar = dado[i];
			no = criaNo(auxChar, index);
			if(*li == NULL){	//Se for o primeiro no
				*li = no;
			}else{	//Senao, insere na frente
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

//Funcao que move o cursor numPos posicoes para tras
//mas se numPos for zero, move para o inicio da lista
void positInit(Lista *li, int numPos){

	int i = 0;
	if(numPos == 0){	//Se numPos for zero, move para o inicio
		while((*li)->ant != NULL){
			(*li) = (*li)->ant;
		}
		return;
	}	//Se nao for, move numPos posicoes para tras ou ate antes de NULL (o inicio)
	while(((*li)->ant != NULL) && (i < numPos)){
		(*li) = (*li)->ant;
		++i;
	}
}

//Funcao que move o cursor numPos posicoes para frente
//mas se numPos for zero, move para o fim da lista
void positFim(Lista *li, int numPos){

	int i = 0;
	if(numPos == 0){	//Se numPos for zero, move para o fim
		while((*li)->prox != NULL){
			(*li) = (*li)->prox;
		}
		return;
	}	//Se nao for, move numPos posicoes para frente ou ate antes de NULL (o fim)
	while(((*li)->prox != NULL) && (i < numPos)){
		(*li) = (*li)->prox;
		++i;
	}
}

//Procura se uma palavra possui um caractere especial junto dela
char *procuraCarac(char *palavra){

	char *aux = palavra;
	while(*aux != '\0'){	//Enquanto nao chegar no fim da palavra
		//Se o caractere nao for especial, vai para o proximo
		if(!ehEsp(aux)){
			++aux;
		}else{	//Senao, retorna o caractere
			if(*aux == '\n'){	//Se for quebra de linha, retorna tambem
				return aux;
			}else{
				return aux;
			}
		}
	}
	return NULL;
}

//Apaga o caractere de uma palavra
void apagaChar(char *palavra, char carac){

	char *aux = palavra;
	while(*aux != '\0'){	//Enquanto nao chegar no fim da palavra
		if(*aux == carac){	//Se achar o caractere
			*aux = '\0';	//Termina a palavra
			return;
		}
		++aux;
	}
}

//Apaga uma palavra
void apagaCharArray(char *array){

	char *aux = array;
	while(*aux != '\0'){
		*aux = '\0';
		++aux;
	}
}

//Imprime a lista de palavras
void imprimeLista(Lista *li){

	No *aux = *li;
	while(aux != NULL){	//Enquanto nao chegar no fim
		if(aux->prox != NULL){	//Se o proximo nao for NULL
			if(ehEsp(aux->prox->dado)){	//E se sua palavra for especial
				printf("%s", aux->dado);	//Imprime sem caracteres adicionais
			}else{	//Senao
				if(aux->dado[0] == '\n'){	//Se for uma quebra de linha, imprime sem caracteres adicionais
					printf("%s", aux->dado);	//Imprime sem caracteres adicionais
				}else{	//Senao imprime com um espaco
					printf("%s ", aux->dado);	//Imprime sem caracteres adicionais
				}
			}
		}else{	//Se o proximo ja for NULL, imprime sem caracteres adicionais
			printf("%s", aux->dado);	//Imprime sem caracteres adicionais
		}
		aux = aux->prox;
	}
}

//Pega o nome do arquivo
char *nameArq(){
	char *nome = calloc(5, sizeof(char));
	scanf("%s", nome);
	return nome;
}

//Insere uma palavra antes do cursor
int insereAntes(Lista *li, char *dado, int index){

	//Se a lista nao estiver inicializada
	if(li == NULL){
		return ERRO;
	}
	No *no = criaNo(dado, index);
	if(*li == NULL){	//Se for o primeiro
		*li = no;
		return OK;
	}	//Senao, insere o no
	No *aux1 = (*li)->ant;
	(*li)->ant = no;
	no->prox = *li;
	no->ant = aux1;
	if(aux1 != NULL){
		aux1->prox = no;
	}
	
	//Ajusta os indices das posicoes posteriores
	No *aux = *li;
	while(aux != NULL){
		++(aux->index);
		aux = aux->prox;
	}
	return OK;
}

//Insere uma palavra depois do cursor
int insereDepois(Lista *li, char *dado, int index){

	//Se a lista nao estiver inicializada
	if(li == NULL){
		return ERRO;
	}
	No *no = criaNo(dado, index);
	if(*li == NULL){	//Se for o primeiro no
		*li = no;
		return OK;
	}	//Senao, insere o no
	no->prox = (*li)->prox;
	(*li)->prox = no;
	no->ant = (*li);
	if(no->prox != NULL){
		(no->prox)->ant = no;
	}
	
	//Ajusta os indices das posicoes posteriores
	No *aux = *li;
	aux = aux->prox;
	while(aux != NULL){
		++aux->index;
		aux = aux->prox;
	}

	return OK;
}

//Remove o no apontado pelo cursor
int removeAtual(Lista *cursor){

	//Se o cursor nao apontar pra nada
	if(cursor == NULL){
		return ERRO;
	}	//Remove o no
	*cursor = (*cursor)->prox;
	No *aux1 = (*cursor)->ant;
	aux1->ant->prox = aux1->prox;
	aux1->prox->ant = aux1->ant;
	aux1->prox = NULL;
	aux1->ant = NULL;
	free(aux1);

	//Ajusta os indices das posicoes posteriores
	No *aux2 = *cursor;
	while(aux2 != NULL){
		--(aux2->index);
		aux2 = aux2->prox;
	}
	return OK;
}


//Remove o primeiro no
//(o cursor deve estar apontando para ele)
int removePrim(Lista *cursor){

	//Se o cursor nao apontar para nada
	if(cursor == NULL){
		return ERRO;
	}	//Remove o no
	*cursor = (*cursor)->prox;
	No *aux1 = (*cursor)->ant;
	aux1->prox->ant = NULL;
	free(aux1);

	//Ajusta os indices das posicoes posteriores
	No *aux2 = *cursor;
	while(aux2 != NULL){
		--(aux2->index);
		aux2 = aux2->prox;
	}
	return OK;
}


//Remove o ultimo no
//(o cursor deve estar apontando para ele)
int removeUlt(Lista *cursor){

	//Se o cursor nao apontar para nada
	if(cursor == NULL){
		return ERRO;
	}	//Senao, remove o no
	*cursor = (*cursor)->ant;
	No *aux1 = (*cursor)->prox;
	aux1->ant->prox = NULL;
	free(aux1);
	return OK;
}

//Funcao que le o arquivo com as palavras
//e transforma na lista
Lista *lerArq(char *nome){

	Lista *liHead = criaLista();
	Lista *liAux = liHead;
	strcat(nome, ".ext");
	FILE *arqEnt = fopen(nome, "rt");
	while(arqEnt == NULL){	//Enquanto o nome nao estiver correto
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
	
	while(fgets(auxLinha, 299, arqEnt)){	//Enquanto houver linhas no arquivo
		auxPalavra = strtok(auxLinha, " ");	//Pega a primeira palavra
		while(auxPalavra != NULL){	//Enquanto houver palavras na linha
			i = 0;
			auxChar = procuraCarac(auxPalavra);	//Verifica se tem caractere especial
			while(auxChar != NULL){	//Enquanto houver caracteres especiais na palavra
				caracteres[i] = *auxChar;	//Recebe no vetor
				auxChar = procuraCarac(auxChar + 1);
				++i;
			}
			caracteres[i] = '\0';	//Finaliza o vetor de caracteres especiais
			if(strcmp(caracteres, "") == 0){	//Se o vetor estiver vazio (somente caracteres comuns)
				insereFim(liAux, auxPalavra, j);	//Insere somente a palavra normalmente	
				++j;
			}else{	//Se nao estiver vazio
				char *ultimoEsp;
				if(auxPalavra[0] == caracteres[0]){	//Se a palavra for o proprio caractere
					insereFim(liAux, caracteres, j);	//Insere os caracteres
					j = j + strlen(caracteres);
				}else{	//Se nao for, eh a palavra eh composta de comum + especial (e pode ser + comum tambem)
					auxChar = procuraCarac(auxPalavra);	//Procura a posicao do caractere especial
					ultimoEsp = auxChar;	//Guarda a posicao
					apagaChar(auxPalavra, caracteres[0]);	//Apaga os caracteres da palavra
					insereFim(liAux, auxPalavra, j);	//Insere a palavra
					++j;
					if(auxChar != NULL){	//Se a palavra tiver caractere
						while(auxChar != NULL){	//Enquanto tiver caractere
							++auxChar;
							auxChar = procuraCarac(auxChar);	//Procura os outros
							if(auxChar != NULL){	//Se tiver, guarda
								ultimoEsp = auxChar;
							}
						}
						insereFim(liAux, caracteres, j);	//Insere os caracteres
						j = j + strlen(caracteres) - 1;
						if(ultimoEsp != NULL){	//Se tiver comum, insere
							++ultimoEsp;
							insereFim(liAux, ultimoEsp, j);
							++j;
						}
					}
					apagaCharArray(caracteres);	//Apaga o vetor de caracteres
				}
			}
			auxPalavra = strtok(NULL, " ");	//Pega a proxima palavra da linha
		}
	}
	fclose(arqEnt);	//Quando acabar de usar o arquivo, fecha
	positInit(liHead, 0);	//Volta o cursor pro inicio
	return liHead;
}

//Busca uma palavra na lista
int buscaPalavra(Lista *cursor, char *dado){

	No *aux = *cursor;
	while(aux != NULL){	//Enquanto nao chegar no fim
		if(strcmp(aux->dado, dado) == 0){	//Se achar
			printf("%d\n", aux->index);	//Imprime o indice
			return OK;
		}
		aux = aux->prox;
	}
	return ERRO;
}

//Remove o '\n' da palavra
void removeNL(char *input){ 
    int len = strlen(input);	
    if(input[0] == '\n'){	//Se a palavra for o proprio caractere, nao remove
    	return;
    }
    if(len > 0 && input[len-1] == '\n'){	//Se a string nao for vazia e o antepenultimo caractere for '\n' 
        input[--len] = '\0';	//Troca por '\0'
    }
}

//Transforma o numero de string para int
int getNumber(char *palavra){

	char *endBuff;
	removeNL(palavra);
	int number = strtol(palavra, &endBuff, 10);
    while (*endBuff != '\0'){	//Enquanto nao houver somente numeros na palavra
        printf("Por favor digite um numero valido: ");
        fgets(palavra, 127, stdin);
        removeNL(palavra);
        number = strtol(palavra, &endBuff, 10);
    }
    return number;
}

//Destroi a lista
void destroi(Lista *li){

	while((*li)->prox != NULL){	//Enquanto nao chegar no fim
		*li = (*li)->prox;	//Vai para o proximo no
		if(*li != NULL){	//Se ele nao for NULL
			free((*li)->ant);	//Libera o anterior
		}
	}
	free(*li);
}

//Funcao que executa os comandos
void comandos(Lista *li){

	Lista *cursor = li;
	char comando;
	char auxLinha[30];
	char *auxPalavra;
	int numPos = 0;

	while(comando != 's'){	//Enquanto nao mandar sair
		fgets(auxLinha, sizeof(auxLinha), stdin);	//Pega a linha
		auxPalavra = strtok(auxLinha, " ");	//Pega o comando
		comando = auxPalavra[0];
		switch(comando) {
			case 'i':	//Se for i, insere antes
				auxPalavra = strtok(NULL, " ");	//Pega a palavra
				removeNL(auxPalavra);
				if(ehEsp(auxPalavra) && (strlen(auxPalavra) > 1)){	//Se for mais de 1 caractere especial, nao insere
					break;
				}
				insereAntes(cursor, auxPalavra, (*cursor)->index);
				break;
			case 'a':	//Se for a, insere depois
				auxPalavra = strtok(NULL, " ");	//Pega a palavra
				removeNL(auxPalavra);
				if(ehEsp(auxPalavra) && (strlen(auxPalavra) > 1)){	//Se for mais de 1 caractere especial, nao insere
					break;
				}
				insereDepois(cursor, auxPalavra, (*cursor)->index);
				break;
			case 'r':	//Se for r, troca a palavra
				auxPalavra = strtok(NULL, " ");	//Pega a nova palavra
				removeNL(auxPalavra);
				if((*cursor)->prox == NULL){	//Se estiver no fim
					removeUlt(cursor);
					insereDepois(cursor, auxPalavra, (*cursor)->index);
				}else{
					if((*cursor)->ant == NULL){	//Se estiver no inicio
						removePrim(cursor);
						insereAntes(cursor, auxPalavra, (*cursor)->index);
						*cursor = (*cursor)->ant;
					}else{	//Se for no meio
						removeAtual(cursor);
						insereAntes(cursor, auxPalavra, (*cursor)->index);
						*cursor = (*cursor)->ant;
					}
				}
				break;
			case 'f':	//Se for f, acha a palavra
				auxPalavra = strtok(NULL, " ");	//Pega a palavra
				removeNL(auxPalavra);
				buscaPalavra(cursor, auxPalavra);
				break;
			case 'd':	//Se for d, remove a palavra atual
				if((*cursor)->prox == NULL){	//Se estiver no fim
					removeUlt(cursor);
				}else{
					if((*cursor)->ant == NULL){	//Se estiver no inicio
						removePrim(cursor);
					}else{	//Se estiver no meio
						removeAtual(cursor);
					}
				}
				break;
			case 'n':	//Se for n, anda uma posicao pra frente
				if((*cursor)->prox != NULL){
					positFim(cursor,1);
				}
				break;	
			case 'p':	//Se for p, anda uma palavra pra tras
				if((*cursor)->ant != NULL){
					positInit(cursor,1);
				}
				break;
			case 'b':	//Se for b, vai pro inicio
				positInit(cursor, 0);
				break;	
			case 'e':	//Se for e, vai pro fim
				positFim(cursor, 0);
				break;
			case 'g':	//Se for g, anda um numero de posicoes
				auxPalavra = strtok(NULL, " ");	//Pega o numero (string)
				numPos = getNumber(auxPalavra);	//Transforma pra int
				if(numPos < 0){	//Se for menor que zero, retrocede
					numPos = (-1)*numPos;
					positInit(cursor, numPos);
				}else{	//Senao, anda pra frente
					positFim(cursor, numPos);
				}
				break;
			case 's':	//Se for s, imprime e deleta a lista
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
