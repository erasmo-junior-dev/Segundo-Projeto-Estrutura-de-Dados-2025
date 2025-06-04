#include "estruturas_e_funcoes.h"
#include "ler_dados_materias.h"
#include "ler_dados_aluno.h"
#include "ler_dados_professores.h"
#include "atribuicao_salas.h"
#include "AlocarSalaNovo.h"
#include "AlocarProfessores.h"
#include "optativas.h"

void output_func(RelacaoSalaMateriaProfessor *p, FILE *output)
{
    if (p == NULL) return;

    output_func(p->proxima, output);

    printf("Sala: %s, Materia: %s %s, Professor: %s\n", p->sala->nome_sala, p->materia->data->no_comp, p->materia->data->horario, p->professor->nome);
    fprintf(output, "Sala: %s, Materia: %s %s, Professor: %s\n", p->sala->nome_sala, p->materia->data->no_comp, p->materia->data->horario, p->professor->nome);
}

int main()
{
    No *lista_de_disciplinas = CreateNewNode();
    lista_de_disciplinas = carregarDados(lista_de_disciplinas);

    OptativasEnfase optativas[4];

    optativa(lista_de_disciplinas, optativas);

    Sala *lista_de_salas = carregarDadosSalas();

    controleHistoricoAluno(lista_de_disciplinas, optativas);

    Professor *lista_de_professores = carregarDadosProfessores(lista_de_disciplinas);

    RelacaoSalaMateriaProfessor *output = NULL;
    AlocarSala(lista_de_disciplinas, lista_de_salas, &output);
    escolherProfessorMateria(output, lista_de_professores);

    FILE *output_txt = fopen("oferta.txt", "w");

    output_func(output, output_txt);

    return 0;
}
