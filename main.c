#include <stdio.h>
#include <string.h>
#include "lista.h"

void ler_texto(char *texto, int tamanho){
    if(fgets(texto, tamanho, stdin) == NULL){
        texto[0] = '\0';
        return;
    }
    if(strchr(texto, '\n') == NULL){        
        int c;                              
        while((c = getchar()) != '\n' && c != EOF);
    }
    texto[strcspn(texto, "\n")] = '\0';
}

int ler_numero(int *numero){
    char texto[50];
    char sobra;
    ler_texto(texto, sizeof(texto));
    return sscanf(texto, "%d %c", numero, &sobra) == 1;
}

void fazer_commit(lista *historico, int *proximo_id){
    Commit c;

    if(lst_len(*historico) == LST_MAX){
        printf("Erro: historico cheio (maximo de %d commits).\n", LST_MAX);
        return;
    }

    printf("Mensagem do commit: ");
    ler_texto(c.mensagem, sizeof(c.mensagem));
    if(strlen(c.mensagem) == 0){
        printf("Erro: a mensagem nao pode ficar vazia.\n");
        return;
    }

    printf("Autor: ");
    ler_texto(c.autor, sizeof(c.autor));
    if(strlen(c.autor) == 0){
        printf("Erro: o autor nao pode ficar vazio.\n");
        return;
    }

    c.id = *proximo_id;

    if(lst_inserir(historico, c, lst_len(*historico))){
        printf("Commit %d criado.\n", c.id);
        (*proximo_id)++;
    }
}

void ver_historico(lista historico){
    int i;
    if(lst_len(historico) == 0){
        printf("Nenhum commit ainda.\n");
        return;
    }
    printf("Historico (%d de %d commits):\n", lst_len(historico), LST_MAX);
    for(i = 0; i < lst_len(historico); i++){
        printf("  commit %d - %s (autor: %s)\n",
               historico.itens[i].id, historico.itens[i].mensagem, historico.itens[i].autor);
    }
}

void buscar_commit(lista historico){
    int id, pos;
    if(lst_len(historico) == 0){
        printf("Erro: nao ha commits para buscar.\n");
        return;
    }
    printf("Id do commit: ");
    if(!ler_numero(&id)){
        printf("Erro: digite um numero.\n");
        return;
    }
    pos = lst_localizar(historico, id);
    if(pos == -1){
        printf("Erro: commit %d nao existe.\n", id);
        return;
    }
    printf("commit %d - %s (autor: %s)\n",
           historico.itens[pos].id, historico.itens[pos].mensagem, historico.itens[pos].autor);
}

void remover_commit(lista *historico){
    int id, pos;
    Commit removido;
    if(lst_len(*historico) == 0){
        printf("Erro: nao ha commits para remover.\n");
        return;
    }
    printf("Id do commit: ");
    if(!ler_numero(&id)){
        printf("Erro: digite um numero.\n");
        return;
    }
    pos = lst_localizar(*historico, id);
    if(pos == -1 || !lst_remover(historico, pos, &removido)){
        printf("Erro: commit %d nao existe.\n", id);
        return;
    }
    printf("Commit %d removido: %s\n", removido.id, removido.mensagem);
}

int main(){
    lista historico;
    historico.tamanho = 0;     
    int proximo_id = 1;
    int opcao;

    printf("=== MINI-GIT: historico de commits ===\n");
    do {
        printf("\n1 - Fazer commit\n");
        printf("2 - Ver historico (log)\n");
        printf("3 - Buscar commit pelo id\n");
        printf("4 - Remover commit pelo id\n");
        printf("0 - Sair\n");
        printf("Opcao: ");

        if(!ler_numero(&opcao)){
            if(feof(stdin)) break;         
            printf("Erro: opcao invalida, digite um numero.\n");
            continue;
        }

        if(opcao == 1)      fazer_commit(&historico, &proximo_id);
        else if(opcao == 2) ver_historico(historico);
        else if(opcao == 3) buscar_commit(historico);
        else if(opcao == 4) remover_commit(&historico);
        else if(opcao == 0) break;
        else printf("Erro: opcao %d nao existe.\n", opcao);
    } while (opcao != 0);

    printf("Saindo do mini-git.\n");
    return 0;
}
