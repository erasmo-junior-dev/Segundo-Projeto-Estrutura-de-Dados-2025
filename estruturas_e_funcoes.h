#ifndef ESTRUTURAS_E_FUNCOES_H
#define ESTRUTURAS_E_FUNCOES_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Materias
{
    char no_comp[50];
    char cod_comp[9];
    char tipo[32];
    int periodo;
    bool optativo;
    int qntPR;
    int qntCR;
    struct Materias *pre_req[22];
    struct Materias *co_req;
    char horario[12];
    char area[11];
    int alunosDependentes;
} Materias;

typedef struct OptativasEnfase
{
    char enfase[30];
    Materias *optativas[5];
} OptativasEnfase;

typedef struct node
{
    Materias *data;;
    struct node *next;
} No;

No* CreateNewNode()
{
    return NULL;
}

No* SearchElement(char *cod_comp, No *head)
{
    No *current = head;
    while (current != NULL)
    {
        if (strcmp(current->data->cod_comp, cod_comp) == 0) return current;
        current = current->next;
    }
}

OptativasEnfase optativas[4];

#endif