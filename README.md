# Entrega 2 – Lista no Mini-git

**Grupo:** MINI GIT – Projeto de Algoritmos, Universidade Católica de Santos

## Como compilar e rodar

```
make
./minigit
```

No Windows com MinGW, use `mingw32-make` e depois `minigit.exe`. Sem o `make`:

```
gcc -Wall -Wextra -o minigit main.c lista.c
```

O programa compila sem erros e sem avisos.

## Onde a Lista foi aplicada e por quê

A Lista guarda o **histórico de commits** do mini-git. Num controle de versão, os commits
ficam em ordem, do mais antigo ao mais novo, e cada commit novo entra no fim. Também é
preciso ver todos (`log`), procurar um commit e apagar um commit. Uma lista faz
exatamente isso: guarda itens em ordem e permite inserir, remover e procurar.

Cada item da lista é um commit, guardado numa struct no lugar do número da aula:

```c
typedef struct {
    int  id;             /* numero do commit: 1, 2, 3... */
    char mensagem[50];   /* o que mudou                  */
    char autor[30];      /* quem fez                     */
} Commit;
```

| Opção do menu | Função da lista usada |
|---|---|
| 1 - Fazer commit | `lst_inserir` na última posição (`k = tamanho`) |
| 2 - Ver histórico | `lst_len` e leitura de `itens[i]` |
| 3 - Buscar commit pelo id | `lst_localizar` |
| 4 - Remover commit pelo id | `lst_localizar` e `lst_remover` |

A lista guarda no máximo 10 commits (`LST_MAX`). A função `lst_concatenar` também foi
implementada e testada; ela não aparece no menu, mas será usada na Entrega Final para
juntar históricos.

## O que corrigimos no código do Moodle

1. `lst_localizar`: a variável `i` não estava declarada (erro de compilação).
2. `lst_inserir` e `lst_remover` chamavam `lst_len(l)` com um ponteiro (erro de
   compilação). Agora usam `l->tamanho`.
3. `lst_inserir` perdia um item ao inserir no meio: o laço parava em `i > k`. Agora é
   `i >= k`.
4. `lst_inserir` aceitava posição negativa. Agora recusa `k < 0`.
5. `lst_remover` aceitava `k == tamanho`, uma posição que não existe. Agora recusa
   `k >= tamanho` e `k < 0`.
6. `lst_concatenar` só tinha o protótipo. Nós a implementamos.
7. O `int` da lista virou a struct `Commit`.

## Casos especiais

| Caso | O que acontece |
|---|---|
| Lista vazia | Ver, buscar ou remover sem nenhum commit mostra um aviso |
| Lista cheia | O 11º commit é recusado: "historico cheio (maximo de 10 commits)" |
| Valor inválido | Letra no lugar de número, id que não existe, opção que não existe, mensagem ou autor vazios: o programa avisa e volta ao menu |

## Exemplo de uso

```
=== MINI-GIT: historico de commits ===

1 - Fazer commit
2 - Ver historico (log)
3 - Buscar commit pelo id
4 - Remover commit pelo id
0 - Sair
Opcao: 1
Mensagem do commit: cria a estrutura do projeto
Autor: Nicolas
Commit 1 criado.

Opcao: 1
Mensagem do commit: adiciona o comando log
Autor: Pedro
Commit 2 criado.

Opcao: 2
Historico (2 de 10 commits):
  commit 1 - cria a estrutura do projeto (autor: Nicolas)
  commit 2 - adiciona o comando log (autor: Pedro)

Opcao: 3
Id do commit: 7
Erro: commit 7 nao existe.

Opcao: 4
Id do commit: 1
Commit 1 removido: cria a estrutura do projeto

Opcao: 0
Saindo do mini-git.
```

(O menu aparece antes de cada "Opcao:"; aqui ele foi mostrado só na primeira vez.)
