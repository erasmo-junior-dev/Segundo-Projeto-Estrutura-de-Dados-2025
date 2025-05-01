#ifndef LER_DADOS_ALUNO_H
#define LER_DADOS_ALUNO_H

#include "estruturas_e_funcoes.h"
#include <stdio.h>

typedef struct Aluno
{
    char enfase[30];
    int periodo;
    No *disciplinasCursadas;
} Aluno;

void preverDependencias(No *head, Aluno *aluno)
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
                for (int i = 0; i <= aux->data->qntPR; i++)
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
}

void inputHistorico(FILE *historico, No *head)
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
        No *disciplina;

        char *token = strtok(getLinha, ";");
        char cod_comp[10];
        strcpy(cod_comp, token);

        token = strtok(NULL, "\n");
        char nota_char[5];
        strcpy(nota_char, token);

        double nota = atof(nota_char);

        if (nota >= 7.0)
        {
            disciplina = SearchElement(cod_comp, head);
            No *aux = (No*) malloc(sizeof(No));
            *aux = *disciplina;
            aux->next = aluno.disciplinasCursadas;
            aluno.disciplinasCursadas = aux;
        }
        memset(getLinha, 0, sizeof(getLinha));
    }

    preverDependencias(head, &aluno);
}

void controleHistoricoAluno(No *head)
{
    int id_aluno = 1;
    char nome_arquivo[16];
    memset(nome_arquivo, 0, sizeof(nome_arquivo));
    strcpy(nome_arquivo, "historico_");
    nome_arquivo[10] = id_aluno + '0';
    strcat(nome_arquivo, ".txt");

    FILE *historico = fopen(nome_arquivo, "r");
    while (historico != NULL)
    {
        inputHistorico(historico, head);
        fclose(historico);

        id_aluno++;
        nome_arquivo[10] = id_aluno + '0';

        historico = fopen(nome_arquivo, "r");
    }

    return;
}

#endif