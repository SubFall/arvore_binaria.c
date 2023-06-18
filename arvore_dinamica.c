#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct NO{
    int dado;
    struct NO* pai;
    struct NO* esq;
    struct NO* dir;
}NO;

typedef struct ARVORE{
    NO* raiz; 
}ARVORE;

ARVORE a;

int contador = 0;

void inserirNo(int dado);
void preOrdem(NO* raiz);
void emOrdem(NO* raiz);
void posOrdem(NO* raiz);
void liberarMemoria(NO* no);
int procuraNo(NO* raiz, int valor);

int main(){
    setlocale(LC_ALL, "Portuguese");

    a.raiz = NULL;

    inserirNo(10);
    inserirNo(2);
    inserirNo(4);
    inserirNo(1);
    inserirNo(13);
    inserirNo(11);
    preOrdem(a.raiz);
    printf("\n\n");
    emOrdem(a.raiz);
    printf("\n\n");
    posOrdem(a.raiz);
    printf("\n\n");
    contador = procuraNo(a.raiz, 12);
    if(contador == -1){
        printf("Não foi encontrado o valor no NÓ\n");
    }else{
        printf("valor percorrido por NÓs, %d\n", contador);
    }
    liberarMemoria(a.raiz);//chama a funcão para liberar a memória
}

void inserirNo(int dado){
    NO* ptr = (NO*)malloc(sizeof(NO));//aloca váriavel dinamicamente
    if(ptr == NULL){//verifica se o ponteiro é null
        printf("Erro ao alocar memória\n");
        return;
    }
    //inicializar o ponteiro
    ptr->dado = dado;
    ptr->pai = NULL;
    ptr->dir = NULL;
    ptr->esq = NULL;

    //se for o primeiro NÓ, vai ser a raiz
    if(a.raiz == NULL){
        a.raiz = ptr;
        return;
    }else{
        NO* current = a.raiz;
        NO* pai;
        while(current != NULL){
            pai = current;
            if(ptr->dado < pai->dado){
                current = current->esq;
                if(current == NULL){
                    pai->esq = ptr;
                    printf("NO filho: %d recebe o NO pai a esquerda: \n", ptr->dado);
                    return;
                }
            }else {
                current = current->dir;
                if(ptr->dado > pai->dado){
                    if(current == NULL){
                        pai->dir = ptr;
                        printf("NO filho: %d recebe o NO pai a direita: \n", ptr->dado);
                        return;
                    }
                }
            }
        }
    }
}

//funcão para encontrar um valor especifico no NÓ
int procuraNo(NO* raiz, int valor){
    contador++;
    if(raiz == NULL){
        return -1;
    }
    if(raiz->dado == valor){
        return contador;
    }
    if(valor < raiz->dado){
        return procuraNo(raiz->esq, valor);
    }else if(valor > raiz->dado){
        return procuraNo(raiz->dir, valor);
    }
  
    return -1;
}

//funcão para desalocar memória
void liberarMemoria(NO* no){
    if(no == NULL){
        return;
    }

    liberarMemoria(no->esq);
    liberarMemoria(no->dir);

    free(no);
}

void preOrdem(NO* raiz){//caminhamento pre-ordem
	if(raiz != NULL){
		printf("%d \t", raiz->dado);
		preOrdem(raiz->esq);
		preOrdem(raiz->dir);
	}
}

void emOrdem(NO* raiz){//caminhamento em-ordem
    if(raiz != NULL){
        emOrdem(raiz->esq);
        printf("%d \t", raiz->dado);
        emOrdem(raiz->dir);
    }
}

void posOrdem(NO* raiz){//caminhamento pos-ordem
    if(raiz != NULL){
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d \t", raiz->dado);
    }
}