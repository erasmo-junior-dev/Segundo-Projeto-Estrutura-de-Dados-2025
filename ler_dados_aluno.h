#ifndef LER_DADOS_ALUNO_H
#define LER_DADOS_ALUNO_H

#include "estruturas_e_funcoes.h"
#include <stdio.h>

void inputHistorico(FILE *historico)
{

}

void controleHistoricoAluno()
{
    int id_aluno = 1;
    char nome_arquivo[16];
    strcpy(nome_arquivo, "historico_");
    nome_arquivo[10] = id_aluno + '0';
    strcat(nome_arquivo, ".txt");

    FILE *historico = fopen(nome_arquivo, "r");
    while (historico != NULL)
    {
        inputHistorico(historico);
        fclose(historico);

        id_aluno++;
        nome_arquivo[10] = id_aluno + '0';

        historico = fopen(nome_arquivo, "r");
    }

    return;
}

#endif