#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Libraries/Arvore.h"
#include "Libraries/InsertionSort.h"
#define MAX_SIZE 10000

int main()
{
    srand(time(NULL));

    FILE *arquivo;
    arquivo = fopen("ABBvsAVL.txt", "w+");

    Arvore *ABB = criar_arvore_vazia();
    Arvore *AVL = criar_arvore_vazia();
    long int i = 0;

    printf("1 - Pior caso da ABB\n2 - Valores aleatorios\n");
    int opcao;
    for(;;)
    {
        scanf("%d", &opcao);

        if(opcao != 1 && opcao != 2)
        {
            printf("Select a valid opcao\n");
        }
        else
        {
            printf("Adicionando...\n");
            if(opcao == 1)
            {
                while (i < MAX_SIZE)
                {
                    AVL = adicionar_avl(AVL, i);
                    ABB = adicionar_abb(ABB, i);
                    i++;
                }
                printf("Adicao completa!\n");
                break;
            }
            else if(opcao == 2)
            {
                while (i < MAX_SIZE)
                {
                    long int j = rand()%MAX_SIZE;
                    AVL = adicionar_avl(AVL, i);                
                    ABB = adicionar_abb(ABB, j);
                    i++;
                }
                printf("Adicao completa!\n");
                break;
            }
        }
        
    }

    int vetor[MAX_SIZE + 1];
    i = 0;
    while (i < MAX_SIZE)
    {
        vetor[i] = rand()%MAX_SIZE;
        i++;
    }
    i = 0;

    insertion(vetor, MAX_SIZE + 1);

    fprintf(arquivo, "VALOR\tABB\tAVL\n");

    printf("Buscando...\n");
    while (i < MAX_SIZE)
    {
        buscar_abb(arquivo, ABB, vetor[i], 0);
        buscar_avl(arquivo, AVL, vetor[i], 0);
        i++;
    }
    printf("Busca completa!\n");

    fclose(arquivo);
    return 0;
}
