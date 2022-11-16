#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define SIZE 200 //tamanho do camos de dados text

/* ---------------------- dados Paciente -----------------------------
    - Nome; CPF; Telefone; Endereço (rua, número, bairro, cidade, estado e CEP)
    - Data de nascimento; E mail; Data do diagnóstico.
    - Comorbidade do paciente (diabetes, obesidade, hipertensão,tuberculose, outros)
*/

//- Estrutuda de dados de paciente
struct dados_paciente {
    char nome[SIZE];
    char email[SIZE];
    int numero, diaNas, mesNas, anoNas;
    char cpf[11], telefone[15], cep[10], diaDiag[11];
    char rua[SIZE], bairro[SIZE], cidade[SIZE], estado[SIZE], comorbidade[10], quais[SIZE];
};

struct dados_paciente paciente;

// Variaveis Globais
// - ponteiro de manipular arquivos
FILE *file;
// - ponteiro para struct que armazena data e hora
struct tm *data_hora_atual;
// - variavel do tipo time_t para armazenar o tempo em segundos
time_t segundos;
int count = 0;
// - variavel de url do arquivo txt que guadar os dados Pacientes
char urlArquivosPacientes[] = "dadosPacientes.txt";
// - variavel de url do arquivo txt que guadar os dados Pacientes Diagnosticados com comobidade
char urlArquivosPacientDiagnosticados[] = "dadosPacientesDiagnosticados.txt";

//declaração dos metodos
void menu();
void login();
void cadastrar_paciente();
void listar_pacientes();
void listar_pacientes_comorbidade();
void Salvar_no_arquivo();
void lendo_arquivo();

int main() {
    setlocale(LC_ALL, "Portuguese");
    //login();
    menu();
    printf("\n");
    return 0;
}

void menu() {
    int op;
    do {
        system("cls");
        printf(" -------------------- Menu de Opcoes -------------------- ");
        printf("\n 1 - Cadastrar Paciente \n 2 - Listar todos os Pacientes \n 3 - Listar Pacientes com Comorbidade");
        printf("\n 0 - Sair\n");
        scanf("%d", &op);
        switch(op) {
        case 0:
            printf("Fechando! Ate logo...\n\n");
            break;
        case 1:
            cadastrar_paciente();
            break;
        case 2:
            listar_pacientes();
            break;
        case 3:
            break;
        default:
            printf("Opcao invalida.\n\n");
        }
    } while(op != 0);
}

void cadastrar_paciente() {
    int op, dataAtual[3];
    //obtendo o tempo em segundos atual da maquina
    time(&segundos);
    //para converter de segundos para o tempo local
    //utilizamos a função localtime
    data_hora_atual = localtime(&segundos);
    dataAtual[0] = data_hora_atual->tm_mday;
    dataAtual[1] = data_hora_atual->tm_mon+1;
    dataAtual[2] = data_hora_atual->tm_year+1900;

    do {
        system("cls");
        printf(" -------------------- Cadastrar Paciente -------------------- ");
        printf("\n\tData Atual: %d/%d/%d \n", dataAtual[0], dataAtual[1], dataAtual[2]);

        printf("\n\tNome:");
        scanf(" %30[^\n]s", &paciente.nome);
        printf("\n\tCPF:");
        scanf(" %30[^\n]s", &paciente.cpf);;
        printf("\n\tTelefone:");
        scanf(" %30[^\n]s", &paciente.telefone);
        printf("\n\tEmail:");
        scanf(" %30[^\n]s", &paciente.email);
        printf("\n\tData de nascimento:");
        printf("\n\tDia: ");
        fflush(stdin);
        scanf("%d", &paciente.diaNas);
        printf("\n\tMes: ");
        fflush(stdin);
        scanf("%d", &paciente.mesNas);
        printf("\n\tAno: ");
        fflush(stdin);
        scanf("%d", &paciente.anoNas);
        printf("\tCEP: ");
        scanf(" %30[^\n]s", &paciente.cep);
        printf("\tRua: ");
        scanf(" %30[^\n]s", &paciente.rua);
        printf("\tNumero: ");
        scanf("%d", &paciente.numero);
        printf("\tBairro: ");
        scanf(" %30[^\n]s", &paciente.bairro);

        printf("\tCidade: ");
        scanf(" %30[^\n]s", &paciente.cidade);

        printf("\tEstado: ");
        scanf(" %30[^\n]s", &paciente.estado);

        //setbuf(stdin, NULL);

        //if(){}

        Salvar_no_arquivo();

        printf("\n\n\n\n Digite: 1) - Para Cadastrar novamente um Paciente ou 0) - Sair dessa opcao\n");
        scanf("%d", &op);

    } while (op != 0);
}

void listar_pacientes() {
    system("cls");
    printf(" -------------------- listar Paciente -------------------- \n\n");
    lendo_arquivo();
    printf("\n");
    system("pause");
}

void login() {
    char user[20], password[20];
    printf("\n");
    printf("  **   **  **   **   ****  ******        ******    ****    **   **       ****  **   ** \n");
    printf("  **   **  ***  **    **    **  **        **  **    **     *** ***        **   **   ** \n");
    printf("  **   **  **** **    **    **  **        **  **    **     *******        **    ** **  \n");
    printf("  **   **  ** ****    **    *****   **    *****     **     *******  **    **    ** **  \n");
    printf("  **   **  **  ***    **    **            **        **     ** * **        **     ***   \n");
    printf("  **   **  **   **    **    **            **        **     **   **        **     ***   \n");
    printf("   *****   **   **   ****  ****          ****      ****    **   **       ****     *    \n");
    printf("\n=====================================================================================\n");
    printf("\n                              Faça seu login                                         \n");
    printf("\n=====================================================================================\n");

    while(1) {
        printf("Digite seu usuário: ");
        (void)!scanf("%s",user);
        printf("Digite sua senha: ");
        (void)!scanf("%s",password);
        //Verifica o usuario e a senha pra entra no sistema
        if(strcmp(user,"admin") == 0 && strcmp(password, "admin") == 0) {
            (void)!system("clear");
            break;
        }
        system("cls");
        printf("Seu usuário ou senha está incorreto. Por favor tente novamente.");
        system("pause");
        exit(0);
    }
}

void Salvar_no_arquivo() {
    file = fopen(urlArquivosPacientes,"a");
    if(file == NULL) { //valida se foi possivel abri o arquivo
        printf("Erro, nao foi possivel abrir o arquivo\n e o programa sera fechado!\n");
        system("pause");
        exit(0);
    }
    fprintf(file,"%s %s \n",&paciente.nome,&paciente.cep);
    fclose(file);
}

void lendo_arquivo() {
    file = fopen(urlArquivosPacientes,"rt");
    if(file == NULL) { //valida se foi possivel abri o arquivo
        printf("Erro, nao foi possivel abrir o arquivo\n e o programa sera fechado!\n");
        system("pause");
        exit(0);
    }
    while(fscanf(file,"%s %s \n",paciente.nome,paciente.cep) != -1)
        printf("%s %s \n",paciente.nome,paciente.cep);
    fclose(file);
}
