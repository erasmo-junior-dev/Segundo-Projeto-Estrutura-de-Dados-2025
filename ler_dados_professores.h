#ifndef LER_DADOS_PROFESSORES_H
#define LER_DADOS_PROFESSORES_H

#include <stdio.h>
#include "estruturas_e_funcoes.h"

Professor* carregarDadosProfessores(No *head)
{
    FILE *arquivo = fopen("professores.txt", "r");
    Professor *newProfessor = NULL;

    char getLinha[100];
    memset(getLinha, 0, sizeof(getLinha));

    while (fgets(getLinha, sizeof(getLinha), arquivo) != NULL)
    {
        Professor *new_prof = (Professor*)malloc(sizeof(Professor));
        char *token = strtok(getLinha, ";");

        strcpy(new_prof->nome, token);

        
        while ((token = strtok(NULL, ";")) != NULL) 
        {
            if (strncmp(token, "TITULO:", 7) == 0) 
            {
                strcpy(new_prof->titulacao, token + 7);
                new_prof->titulacao[strcspn(new_prof->titulacao, "\n")] = '\0';
                break;
            }

            No *disciplina = SearchElement(token, head);

            No *nova_disc = malloc(sizeof(No));
            *nova_disc = *disciplina;
            nova_disc->next = new_prof->lista_materias;
            new_prof->lista_materias = nova_disc;
        }

        new_prof->proximo = newProfessor;
        newProfessor = new_prof;

        memset(getLinha, 0, sizeof(getLinha));
    }


    fclose(arquivo);
    return newProfessor;
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