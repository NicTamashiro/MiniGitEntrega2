#ifndef _LISTA_H
#define _LISTA_H
#include <stdbool.h>

#define LST_MAX 10

typedef struct {
    int  id;             
    char mensagem[50];  
    char autor[30];      
} Commit;

typedef struct{
    Commit itens[LST_MAX];
    int tamanho;
} lista;

bool lst_inserir(lista*l, Commit val, int k);
bool lst_remover(lista*l, int k, Commit * val);
bool lst_concatenar(lista l1, lista l2, lista * l3);
int lst_len(lista l);

int lst_localizar(lista l, int id);

#endif 
