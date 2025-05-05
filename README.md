# BRANCH DE TESTES

## Segundo Projeto de ED

### Objetivo:
Gerar uma oferta de disciplina de matérias do IC, com dias e horários definidos respeitando os requisitos a partir da disponibilidade de professores da matéria e do histórico dos alunos.

### Requisitos:

- Usar apenas estruturas dinâmicas.
- O professor pode ministrar no máximo 3 disciplinas por semestre.
- Pode dividir uma disciplina entre mais de um professor.
- O professor deve ser alocado no menor número de dias possíveis.
- As ênfases tem a maior prioridade.

### Tasks:

- [x] Reaproveitar a função de input de dados e de histórico. (Erasmo)
> [!NOTE]
> Como teremos diversas entrada, é necessário usar um parâmetro para o alvo do fopen na função de input do histórico.

> [!WARNING]
> Será necessário a criação de uma função reguladora para alterar a string de parâmetro do arquivo alvo na função de input de histórico.

- [x] Refazer as estruturas que serão reaproveitadas. (Erasmo)
> [!WARNING]
> Talvez seja necessário refazer do zero para evitar problemas. Também será necessário refazer todas as outras funções que iremos aproveitar.

> [!TIP]
> Vamos fazer o input já ordenado, para não precisar usar uma função de ordenação.

- [x] Criar um .txt com os dados de todos professores ativos do IC. (Victor)
- [x] Criar um .txt com os dados das salas do IC. (Victor)
- [x] Criar uma função para ler os dados dos professores do IC. (Erasmo)
- [x] Criar uma estrutura, ou modificar uma já existente que aponte à disciplina aos professores. (Victor)
- [x] Criar uma estrutura que faça a ligação entre sala, professor e disciplina. (Erasmo)
- [x] Criar uma função de conflito de horário (Erasmo)
- [ ] Criar estruturas condicionais para a função de atribuição de salas (Victor)
- [ ] Criar o loop da função de atribuição de salas (Erasmo)