#include "estruturas_e_funcoes.h"
#include "ler_dados_materias.h"
#include "ler_dados_aluno.h"
#include "ler_dados_professores.h"
#include "atribuicao_salas.h"
#include "AlocarSalaNovo.h"

int main()
{
    No *lista_de_disciplinas = CreateNewNode();
    lista_de_disciplinas = carregarDados(lista_de_disciplinas);

    Sala *lista_de_salas = carregarDadosSalas();

    controleHistoricoAluno(lista_de_disciplinas);

    Professor *lista_de_professores = carregarDadosProfessores(lista_de_disciplinas);

    RelacaoSalaMateriaProfessor *output = NULL;
    AlocarSala(lista_de_disciplinas, lista_de_salas, &output);

    for (RelacaoSalaMateriaProfessor *p = output; p != NULL; p = p->proxima) {
        printf("Sala: %s, Materia: %s\n", p->sala->nome_sala, p->materia->data->no_comp);
}


    return 0;
}
