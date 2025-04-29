#ifndef LER_DADOS_MATERIAS_H
#define LER_DADOS_MATERIAS_H

#include <stdio.h>
#include "estruturas_e_funcoes.h"

void associarPreReq(No *materia, No *pre_req_materia, int i) 
{
    if (materia->data->pre_req[i] == NULL) materia->data->pre_req[i] = pre_req_materia->data;
}

void associarCoReq(No *materia, No *co_req_materia) 
{
    materia->data->co_req = co_req_materia->data;
    co_req_materia->data->co_req = materia->data;
}

void carregarDados(No *head)
{
    FILE *materias = fopen("materias.txt", "r");

    char getLinha[200];

    fgets(getLinha, sizeof(getLinha), materias);

    while(strcmp(getLinha, "INICIO PRE-REQUISITOS\r\n") != 0)
    {
        No *newNode = (No*) malloc(sizeof(No));
        newNode->data = (Materias *)malloc(sizeof(Materias));
        newNode->next = NULL;

        if (strcmp("\r\n", getLinha) == 0)
        {
            fgets(getLinha, sizeof(getLinha), materias);
            continue;
        }

        char *dado = strtok(getLinha, ";");
        strcpy(newNode->data->cod_comp, dado);

        dado = strtok(NULL, ";");
        strcpy(newNode->data->no_comp, dado);

        dado = strtok(NULL, ";");
        strcpy(newNode->data->tipo, dado);

        dado = strtok(NULL, ";");
        char optativo[12];
        strcpy(optativo, dado);

        if (strcmp(optativo, "OPTATIVO") == 0) newNode->data->optativo = true;
        else newNode->data->optativo = false;

        dado = strtok(NULL, ";");
        strcpy(newNode->data->horario, dado);

        dado = strtok(NULL, ";");
        strcpy(newNode->data->area, dado);

        dado = strtok(NULL, "\r\n");
        newNode->data->periodo = atoi(dado);
        newNode->data->qntPR = -1;
        newNode->data->qntCR = -1;
        newNode->data->alunosDependentes = 0;

        if (head == NULL) head = newNode;
        else
        {
            No *aux = head;
            while (aux->next != NULL) aux = aux->next;
            aux->next = newNode;
        }

        memset(getLinha, 0, sizeof(getLinha));

        fgets(getLinha, sizeof(getLinha), materias);
    }

    memset(getLinha, 0, sizeof(getLinha));
    fgets(getLinha, sizeof(getLinha), materias);
    memset(getLinha, 0, sizeof(getLinha));

    fgets(getLinha, sizeof(getLinha), materias);

    while (strcmp(getLinha, "FIM") != 0)
    {

        if (strcmp(getLinha, "\r\n") == 0)
        {
            fgets(getLinha, sizeof(getLinha), materias);
            continue;
        }

        char *dado = strtok(getLinha, ";");
        No *dependente = SearchElement(dado, head);
        dado = strtok(NULL, ";");

        while (strcmp(dado, "\r\n") != 0)
        {
            No *dependência = SearchElement(dado, head);

            dependente->data->qntPR = dependente->data->qntPR + 1;

            associarPreReq(dependente, dependência, dependente->data->qntPR);

            dado = strtok(NULL, ";");
        }

        memset(getLinha, 0, sizeof(getLinha));
        fgets(getLinha, sizeof(getLinha), materias);
    }
    
    No *codependente = SearchElement("COMP372", head);
    No *codependencia = SearchElement("COMP373", head);

    associarCoReq(codependente, codependencia);

    fclose(materias);

    return;   
}

#endif