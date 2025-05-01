#ifndef LER_DADOS_PROFESSORES_H
#define LER_DADOS_PROFESSORES_H

#include <stdio.h>
#include "estruturas_e_funcoes.h"

Professor* carregarDadosProfessores()
{
    
}

Sala* carregarDadosSalas()
{
    FILE *arquivo = fopen("salas.txt", "r");
    Sala *newSala = NULL;

    char getLinha[100];
    memset(getLinha, 0, sizeof(getLinha));

    while (fgets(getLinha, sizeof(getLinha), arquivo) != NULL)
    {
        Sala *new_sala = (Sala*)malloc(sizeof(Sala));
        char *token = strtok(getLinha, ";");

        strcpy(new_sala->nome_sala, token);
        
        token = strtok(NULL, ";");
        new_sala->capacidade = atoi(token);

        token = strtok(NULL, ";");
        strcpy(new_sala->tipo_sala, token);

        new_sala->proxima = newSala;
        newSala = new_sala;

        memset(getLinha, 0, sizeof(getLinha));
    }

    fclose(arquivo);

    return newSala;
}

#endif