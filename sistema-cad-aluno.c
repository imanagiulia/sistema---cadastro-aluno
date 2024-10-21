#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TURMAS_CURSO 5
#define MAX_ALUNOS_TURMA 45
#define NUM_CURSOS 3
#define MAX_CHAR_NOME 100
#define MAX_CHAR_MATRICULA 20 

#define CURSO1  "Engenharia de Software"
#define CURSO2  "Cinema"
#define CURSO3  "Psicologia"

//PREVIA DAS FUNÇÕES
void cad_aluno(int numCurso, int numTurma);
int def_turma ();
int def_curso();
void menu_cursos();
void mostrar_cadastros();
int repetir();

// DECLARAÇÃO DAS MATRIZES E VARIÁVEIS GLOBAIS
char matricula[NUM_CURSOS][MAX_TURMAS_CURSO][MAX_ALUNOS_TURMA][MAX_CHAR_MATRICULA] = {0}; 
char nome[NUM_CURSOS][MAX_TURMAS_CURSO][MAX_ALUNOS_TURMA][MAX_CHAR_NOME] = {0};
int numCadastrado[NUM_CURSOS][MAX_TURMAS_CURSO] = {0};
const char *curso[NUM_CURSOS] = {CURSO1, CURSO2, CURSO3};

int main() {
    int nCurso, nTurma, r;
    int indicador = 0;

    puts("------------------------------");
    puts("     CADASTRO DE ALUNOS");
    puts("------------------------------");
    puts("");

    sleep(1);

    do {
        system("cls");

        puts("     MENU DE OPÇÕES: ");
        puts("------------------------------");
        puts("[1] Cadastrar novo aluno ");
        puts("[2] Consultar aluno");
        puts("");

        do {
            printf("Qual função deseja realizar? ");
            scanf("%d", &indicador);
            if (indicador < 1 || indicador > 2) {
                printf("[ERRO] Opção inválida!\n");
            }
        } while (indicador < 1 || indicador > 2);

        system("cls");

        switch (indicador) {
            case 1:
                while (indicador == 1) {
                    nCurso = def_curso();
                    nTurma = def_turma();

                    if (numCadastrado[nCurso][nTurma] == MAX_ALUNOS_TURMA) {
                        printf("[ERRO] Turma já alcançou sua capacidade máxima\n");
                        continue;
                    }

                    cad_aluno(nCurso, nTurma); 
                    numCadastrado[nCurso][nTurma]++;
                    indicador = 0;
                }
                break;

            case 2:
                mostrar_cadastros();
                break;

            default:
                printf("[ERRO] Opção inválida\n");
        }
        r = repetir();
    } while (r == 1);
}

void cad_aluno(int numCurso, int numTurma) {

    int cadastrados = numCadastrado[numCurso][numTurma];
    printf("NOME DO ALUNO: ");
    fgets(nome[numCurso][numTurma][cadastrados], MAX_CHAR_NOME, stdin);
    nome[numCurso][numTurma][cadastrados][strcspn(nome[numCurso][numTurma][cadastrados], "\n")] = '\0';

    printf("MATRÍCULA DO ALUNO: ");
    fflush(stdin);
    scanf(" %s", matricula[numCurso][numTurma][cadastrados]); 
    fflush(stdin);
}

void menu_cursos() {

    puts("ESCOLHA O CURSO");
    
    for (int i = 0; i < NUM_CURSOS; i++) {
        printf("[%d] %s \n", i + 1, curso[i]);
    }
}

int def_turma() {
    char turma;
    int numTurma;

    do {

        printf("TURMA DO ALUNO (a-e): ");
        fflush(stdin);
        scanf(" %c", &turma);
        fflush(stdin);

        numTurma = turma - 'a';
        if (numTurma < 0 || numTurma >= MAX_TURMAS_CURSO) {
            printf("[ERRO] Turma inexistente!\n");
        }
    } while (numTurma < 0 || numTurma >= MAX_TURMAS_CURSO);

    return numTurma;
}

int def_curso() {
    int numCurso;

    do {
        menu_cursos();
        scanf("%d", &numCurso);
        numCurso -= 1;
        if (numCurso < 0 || numCurso >= NUM_CURSOS) {
            printf("[ERRO] Curso inválido\n");
        } 
    } while (numCurso < 0 || numCurso >= NUM_CURSOS);

    return numCurso;
}

void mostrar_cadastros() {
    int aux;
    int encontrado = 0;
    char nomeBusca[MAX_CHAR_NOME];
    char matriBusca[MAX_CHAR_MATRICULA];
    puts("Deseja consultar aluno por: ");
    puts("[1] NOME");
    puts("[2] MATRÍCULA");
    scanf("%d", &aux);
    fflush(stdin);

    switch (aux) {
        case 1:
            printf("Nome do aluno: ");
            fgets(nomeBusca, MAX_CHAR_NOME, stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
           

            for (int i = 0; i < NUM_CURSOS; i++) {
                for (int j = 0; j < MAX_TURMAS_CURSO; j++) {
                    for (int k = 0; k < numCadastrado[i][j]; k++) {
                        if (strcmp(nome[i][j][k], nomeBusca) == 0) {
                            printf("%s \nMatrícula: %s \nCurso: %s \nTurma: %c\n", 
                                    nome[i][j][k], matricula[i][j][k], curso[i], j + 'a');
                                    encontrado++;
                        }
                    }
                }
            }
            if (encontrado == 0){
                printf("Aluno não cadastrado!");
            }
            break;

        case 2:
            printf("Matrícula do aluno: ");
            scanf(" %s", matriBusca);
            fflush(stdin);

            for (int i = 0; i < NUM_CURSOS; i++) {
                for (int j = 0; j < MAX_TURMAS_CURSO; j++) {
                    for (int k = 0; k < numCadastrado[i][j]; k++) {
                        if (strcmp(matricula[i][j][k], matriBusca) == 0) {
                            printf("%s \nNome: %s \nCurso: %s \nTurma: %c\n", 
                                    matricula[i][j][k], nome[i][j][k], curso[i], j + 'a');
                        }else{
                            printf("Aluno não cadastrado!");
                        }
                    }
                }
            }
            break;

        default:
            printf("[ERRO] Operador inválido\n");
            break;
    }
}

int repetir() {

    int aux;

    printf("Deseja realizar nova operação? [1] Sim [-1] Não\n");
    scanf("%d", &aux);
    
    return aux;
}
