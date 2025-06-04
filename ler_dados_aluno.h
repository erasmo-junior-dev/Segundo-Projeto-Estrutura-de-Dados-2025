#ifndef LER_DADOS_ALUNO_H
#define LER_DADOS_ALUNO_H

#include "estruturas_e_funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Aluno
{
    char enfase[30];
    int periodo;
    No *disciplinasCursadas;
} Aluno;

void preverDependencias(No *head, Aluno *aluno, OptativasEnfase *o)
{
    No *aux = head;
    while (aux != NULL)
    {
        bool podeCursar = true;
        int periodoDisciplina = aux->data->periodo;

        if (periodoDisciplina <= aluno->periodo || periodoDisciplina == 0)
        {
            if (aux->data->qntPR != -1)
            {
                for (int i = 0; i < aux->data->qntPR; i++)
                {
                    No *aux2 = SearchElement(aux->data->pre_req[i]->cod_comp, aluno->disciplinasCursadas);
                    if (aux2 == NULL)
                    {
                        podeCursar = false;
                        break;
                    }
                }
            }

            if (podeCursar && SearchElement(aux->data->cod_comp, aluno->disciplinasCursadas) == NULL) aux->data->alunosDependentes++;
        }
        else break;

        aux = aux->next;
    }

    int i = 0;
    while (strcmp(aluno->enfase, o[i].enfase) != 0) i++;

    for (int j = 0; j < 5; j++)
    {
        bool podeCursar = true;

        if (o[i].optativas[j]->qntPR != -1)
        {
            for (int k = 0; k < o[i].optativas[j]->qntPR; k++)
            {
                No *aux2 = SearchElement(o[i].optativas[j]->pre_req[k]->cod_comp, aluno->disciplinasCursadas);
                if (aux2 == NULL)
                {
                    podeCursar = false;
                    break;
                }
            }
        }

        if (SearchElement(o[i].optativas[j]->cod_comp, aluno->disciplinasCursadas) == NULL && podeCursar) o[i].optativas[j]->alunosDependentes++;
    }
}

void inputHistorico(FILE *historico, No *head, OptativasEnfase *o)
{
    Aluno aluno;
    char getLinha[100];

    fgets(getLinha, sizeof(getLinha), historico);
    strcpy(aluno.enfase, getLinha);
    aluno.enfase[strcspn(aluno.enfase, "\n")] = 0;
    memset(getLinha, 0, sizeof(getLinha));

    fgets(getLinha, sizeof(getLinha), historico);
    aluno.periodo = atoi(getLinha) + 1;
    memset(getLinha, 0, sizeof(getLinha));

    aluno.disciplinasCursadas = NULL;
    while (fgets(getLinha, sizeof(getLinha), historico) != NULL)
    {
        char *token = strtok(getLinha, ";");
        char cod_comp[10];
        strcpy(cod_comp, token);

        token = strtok(NULL, "\n");
        char nota_char[5];
        strcpy(nota_char, token);

        double nota = atof(nota_char);

        if (nota >= 7.0)
        {
            No *disciplina = SearchElement(cod_comp, head);
            if (disciplina != NULL)
            {
                No *aux = (No *)malloc(sizeof(No));
                *aux = *disciplina;
                aux->next = aluno.disciplinasCursadas;
                aluno.disciplinasCursadas = aux;
            }
        }

        memset(getLinha, 0, sizeof(getLinha));
    }

    preverDependencias(head, &aluno, o);
}

void controleHistoricoAluno(No *head, OptativasEnfase *o)
{
    int id_aluno = 1;
    char nome_arquivo[64];

    sprintf(nome_arquivo, "historico_%d.txt", id_aluno);
    FILE *historico = fopen(nome_arquivo, "r");

    while (historico != NULL)
    {
        inputHistorico(historico, head, o);
        fclose(historico);

        id_aluno++;
        sprintf(nome_arquivo, "historico_%d.txt", id_aluno);
        historico = fopen(nome_arquivo, "r");
    }
}

#endif