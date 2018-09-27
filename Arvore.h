#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Códigos comuns às duas estruturas

typedef struct arvore
{
    long int valor;
    int h;
    struct arvore *esquerda;
    struct arvore *direita;
}Arvore;

bool arvore_vazia(Arvore *bt)
{
    return (bt == NULL);
}

Arvore* criar_arvore_vazia()
{
    return NULL;
}

Arvore* criar_arvore(int valor, Arvore *esquerda, Arvore *direita)
{
    Arvore *nova_arvore = (Arvore*)malloc(sizeof(Arvore));
    nova_arvore->valor = valor;
    nova_arvore->esquerda = esquerda;
    nova_arvore->direita = direita;
    nova_arvore->h = 1;

    return nova_arvore;
}

void imprimir_pre_ordem(Arvore *bt)
{
    if(!arvore_vazia(bt))
    {
        printf("%d ", bt->valor);
        imprimir_pre_ordem(bt->esquerda);
        imprimir_pre_ordem(bt->direita);
    }
}

//*********************************************************************//
//******************@@@@@@@@@**@@@@@@@@****@@@@@@@@********************//
//******************@@     @@**@@      @@**@@      @@******************//
//******************@@     @@**@@      @@**@@      @@******************//
//******************@@@@@@@@@**@@@@@@@@****@@@@@@@@********************//
//******************@@     @@**@@      @@**@@      @@******************//
//******************@@     @@**@@      @@**@@      @@******************//
//******************@@     @@**@@@@@@@@****@@@@@@@@********************//
//*********************************************************************//

// Códigos específicos da árvore de busca binária

Arvore* adicionar_abb(Arvore *bt, int valor)
{
    if(bt == NULL) bt = criar_arvore(valor, NULL, NULL);
    else if(bt->valor > valor) bt->esquerda = adicionar_abb(bt->esquerda, valor);
    else bt->direita = adicionar_abb(bt->direita, valor);

    return bt;
}

Arvore *buscar_abb(FILE *arquivo, Arvore *bt, long int valor, int cont)
{
    if (bt == NULL)
    {
        cont++;
        fprintf(arquivo, "%li\t%d\t", valor, cont);
        return bt;
    }

    if (bt->valor == valor)
    {
        cont++;
        fprintf(arquivo, "%li\t%d\t", valor, cont);
        return bt;
    }
    else if (bt->valor > valor) return buscar_abb(arquivo, bt->esquerda, valor, cont + 1);
    else return buscar_abb(arquivo, bt->direita, valor, cont + 1);

    return bt;
}

//*********************************************************************//
//******************@@@@@@@@@**@@       @@**@@*************************//
//******************@@     @@**@@       @@**@@*************************//
//******************@@     @@***@@     @@***@@*************************//
//******************@@@@@@@@@***@@     @@***@@*************************//
//******************@@     @@****@@   @@****@@*************************//
//******************@@     @@*****@@ @@*****@@*************************//
//******************@@     @@******@@@******@@@@@@@@@******************//
//*********************************************************************//

//Códigos específicos da AVL

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int h(Arvore *bt)
{
    if(bt == NULL) return -1;
    else return 1 + max(h(bt->esquerda), h(bt->direita));
}

int esta_balanceado(Arvore *bt)
{
    int bf = h(bt->esquerda) - h(bt->direita);
    return ((-1 <= bf) && (bf <= 1));
}

int checar_balanceio(Arvore *bt)
{
    if (bt == NULL)
        return 0;
    return h(bt->esquerda) - h(bt->direita);
}

Arvore* rotacionar_esquerda(Arvore *bt)
{
    Arvore *raiz_subarvore = NULL;

    if(bt != NULL && bt->direita != NULL)
    {
        raiz_subarvore = bt->direita;
        bt->direita = raiz_subarvore->esquerda;
        raiz_subarvore->esquerda = bt;
    }

    raiz_subarvore->h = h(raiz_subarvore);
    bt->h = h(bt);

    return raiz_subarvore;
}

Arvore* rotacionar_direita(Arvore *bt)
{
    Arvore *raiz_subarvore = NULL;

    if(bt != NULL && bt->esquerda != NULL)
    {
        raiz_subarvore = bt->esquerda;
        bt->esquerda = raiz_subarvore->direita;
        raiz_subarvore->direita = bt;
    }

    raiz_subarvore->h = h(raiz_subarvore);
    bt->h = h(bt);
    
    return raiz_subarvore;
}

Arvore* adicionar_avl(Arvore *bt, int valor)
{
    if(bt == NULL) return criar_arvore(valor, NULL, NULL);
    else if(bt->valor > valor) bt->esquerda = adicionar_avl(bt->esquerda, valor);
    else bt->direita = adicionar_avl(bt->direita, valor);

    bt->h = h(bt);
    Arvore *filha;

    if(checar_balanceio(bt) == 2 || checar_balanceio(bt) == -2)
    {
        if(checar_balanceio(bt) == 2)
        {
            filha = bt->esquerda;
            if(checar_balanceio(filha) == -1)
            {
                bt->esquerda = rotacionar_esquerda(filha);
            }
            bt = rotacionar_direita(bt);
        }
        else if(checar_balanceio(bt) == -2)
        {
            filha = bt->direita;
            if(checar_balanceio(filha) == 1)
            {
                bt->direita = rotacionar_direita(filha);
            }
            bt = rotacionar_esquerda(bt);
        }
    }

    return bt;
}

Arvore *buscar_avl(FILE *arquivo, Arvore *bt, long int valor, int cont)
{
    if (bt == NULL)
    {
        if(cont == 0) cont++;
        fprintf(arquivo, "%d\n", cont);
        return bt;
    }

    if (bt->valor == valor)
    {
        if(cont == 0) cont++;
        fprintf(arquivo, "%d\n", cont);
        return bt;
    }
    else if (bt->valor > valor) return buscar_avl(arquivo, bt->esquerda, valor, cont + 1);
    else return buscar_avl(arquivo, bt->direita, valor, cont + 1);

    return bt;
}