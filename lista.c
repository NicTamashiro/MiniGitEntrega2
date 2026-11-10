#include "lista.h"

int lst_len(lista l){
    return l.tamanho;
}

int lst_localizar(lista l, int id){
    for(int i = 0; i < lst_len(l); i++){
        if(id == l.itens[i].id){
            return i;
        }
    }

    return -1;
}

bool lst_inserir(lista*l, Commit val, int k){

    if(l->tamanho == LST_MAX || k < 0 || k > l->tamanho)
        return false;

    for(int i = l->tamanho - 1; i >= k; i--){
        l->itens[i+1] = l->itens[i];
    }

    l->itens[k] = val;
    l->tamanho++;
    return true;
}

bool lst_remover(lista*l, int k, Commit * val){

    if(l->tamanho == 0 || k < 0 || k >= l->tamanho){
        return false;
    }
    (*val) = l->itens[k];
    for(int i = k; i < l->tamanho - 1; i++){
        l->itens[i] = l->itens[i+1];
    }
    l->tamanho--;
    return true;
}

bool lst_concatenar(lista l1, lista l2, lista * l3){
    /* Não cabe se a soma passar do máximo */
    if(lst_len(l1) + lst_len(l2) > LST_MAX)
        return false;
    l3->tamanho = 0;
    for(int i = 0; i < lst_len(l1); i++){
        l3->itens[l3->tamanho] = l1.itens[i];
        l3->tamanho++;
    }
    for(int i = 0; i < lst_len(l2); i++){
        l3->itens[l3->tamanho] = l2.itens[i];
        l3->tamanho++;
    }
    return true;
}
