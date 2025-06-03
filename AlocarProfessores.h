#ifndef ALOCARPROFESSORES_C
#define ALOCARPROFESSORES_C

#include "estruturas_e_funcoes.h"
#include "atribuicao_salas.h"


RelacaoSalaMateriaProfessor* SearchElementRelacao(RelacaoSalaMateriaProfessor *relacao, char *codMateria) {
    while (relacao != NULL)
    {
        if (strcmp(relacao->materia->data->cod_comp, codMateria) == 0)
        {
            return relacao;
        }
        relacao = relacao->proxima;
    }
    return NULL;
}

Professor* SearchProfessor(Professor *professores, char *nome) {
    while (professores != NULL)
    {
        if (strcmp(professores->nome, nome) == 0)
        {
            return professores;
        }
        professores = professores->proximo;
    }
}

void escolherProfessorMateria(RelacaoSalaMateriaProfessor *relacao, Professor *professor) 
{
    RelacaoSalaMateriaProfessor *aux = relacao;

    while (aux->materia->data->periodo < 4) aux = aux->proxima;

    while (aux->materia->data->periodo > 4 || aux->materia->data->optativo == true)
    {
        Professor *prof = professor;

        while (prof != NULL)
        {
            No *auxDisc = prof->lista_materias;
            while (auxDisc != NULL)
            {
                if (strcmp(aux->materia->data->cod_comp, auxDisc->data->cod_comp) == 0)
                {
                    if (verificarDisponibilidadeHorario(prof->lista_disciplinas_ministradas, *aux->materia->data) && prof->disciplinasMinistradas <= 3)
                    {
                        if (aux->professor == NULL)
                        {
                            prof->disciplinasMinistradas++;
                            aux->professor = (Professor*) malloc(sizeof(Professor));
                            *aux->professor = *prof;
                            aux->professor->proximo = NULL;
                        }
                        else
                        {
                            if (aux->professor->disciplinasMinistradas > prof->disciplinasMinistradas)
                            {
                                Professor *tempAux = SearchProfessor(professor, aux->professor->nome);

                                tempAux->disciplinasMinistradas--;
                                prof->disciplinasMinistradas++;
                                aux->professor = (Professor*) malloc(sizeof(Professor));
                                *aux->professor = *prof;
                                aux->professor->proximo = NULL;
                            }
                        }
                    }
                }
                auxDisc = auxDisc->next;
            }
            prof = prof->proximo;
        }
        
        aux = aux->proxima;
    }

    aux = relacao;

    while (aux != NULL)
    {
        if (aux->professor == NULL)
        {
            Professor *prof = professor;

            while (prof != NULL)
            {
                if (strcmp(prof->titulacao, aux->materia->data->area) == 0)
                {
                    if (verificarDisponibilidadeHorario(prof->lista_disciplinas_ministradas, *aux->materia->data) && prof->disciplinasMinistradas <= 3)
                    {
                        if (aux->professor == NULL)
                        {
                            prof->disciplinasMinistradas++;
                            aux->professor = (Professor*) malloc(sizeof(Professor));
                            *aux->professor = *prof;
                            aux->professor->proximo = NULL;
                        }
                        else
                        {
                            if (aux->professor->disciplinasMinistradas > prof->disciplinasMinistradas)
                            {
                                Professor *tempAux = SearchProfessor(professor, aux->professor->nome);

                                tempAux->disciplinasMinistradas--;
                                prof->disciplinasMinistradas++;
                                aux->professor = (Professor*) malloc(sizeof(Professor));
                                *aux->professor = *prof;
                                aux->professor->proximo = NULL;
                            }
                        }
                    }
                }
                
                prof = prof->proximo;
            }   
        }

        aux = aux->proxima;
    }

    aux = relacao;

    while(aux != NULL)
    {
        if (aux->professor != NULL)
        {
            aux = aux->proxima;   
            continue;
        }

        for (int i = 0; i <= 3; i++)
        {
            Professor *prof = professor;

            while (prof != NULL)
            {
                if (prof->disciplinasMinistradas == 0)
                {
                    prof->disciplinasMinistradas++;
                    aux->professor = (Professor*) malloc(sizeof(Professor));
                    *aux->professor = *prof;
                    aux->professor->proximo = NULL;

                    break;
                }
                else if (prof->disciplinasMinistradas == i)
                {
                    if (verificarDisponibilidadeHorario(prof->lista_disciplinas_ministradas, *aux->materia->data) && aux->professor == NULL)
                    {
                        prof->disciplinasMinistradas++;
                        aux->professor = (Professor*) malloc(sizeof(Professor));
                        *aux->professor = *prof;
                        aux->professor->proximo = NULL;

                        break;
                    }
                }

                prof = prof->proximo;
            }
        }

        aux = aux->proxima;
    }
    
}

#endif