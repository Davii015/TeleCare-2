#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char nome[50];
    int idade;
    float batimentosCardiacos;
    float nivelGlicose;
    bool alertado;
} Paciente;

#define MAX_PACIENTES 5

void cadastrarPaciente(Paciente pacientes[], int *numPacientes) {
    if (*numPacientes >= MAX_PACIENTES) {
        printf("Limite de pacientes atingido.\n");
        return;
    }
    
    printf("\nCadastro de Paciente:\n");
    printf("Nome: ");
    scanf(" %[^\n]", pacientes[*numPacientes].nome);
    printf("Idade: ");
    scanf("%d", &pacientes[*numPacientes].idade);
    pacientes[*numPacientes].alertado = false;
    (*numPacientes)++;
    printf("Paciente cadastrado com sucesso.\n");
}

void inserirDadosSaude(Paciente *paciente) {
    printf("\nInserir Dados de Saúde para %s:\n", paciente->nome);
    printf("Batimentos Cardíacos (bpm): ");
    scanf("%f", &paciente->batimentosCardiacos);
    printf("Nível de Glicose (mg/dL): ");
    scanf("%f", &paciente->nivelGlicose);
}

void analisarDadosSaude(Paciente *paciente) {
    bool alerta = false;
    
    if (paciente->batimentosCardiacos < 60 || paciente->batimentosCardiacos > 100) {
        printf("Alerta: Batimentos cardíacos fora do normal para %s.\n", paciente->nome);
        alerta = true;
    }
    if (paciente->nivelGlicose < 70 || paciente->nivelGlicose > 140) {
        printf("Alerta: Nível de glicose fora do normal para %s.\n", paciente->nome);
        alerta = true;
    }

    if (alerta) {
        paciente->alertado = true;
    } else {
        printf("Dados normais para %s.\n", paciente->nome);
    }
}

void exibirPacientes(Paciente pacientes[], int numPacientes) {
    printf("\nLista de Pacientes:\n");
    for (int i = 0; i < numPacientes; i++) {
        printf("Nome: %s | Idade: %d | Batimentos: %.1f bpm | Glicose: %.1f mg/dL | Alerta: %s\n", 
               pacientes[i].nome, pacientes[i].idade, 
               pacientes[i].batimentosCardiacos, pacientes[i].nivelGlicose,
               pacientes[i].alertado ? "Sim" : "Não");
    }
}

int main() {
    Paciente pacientes[MAX_PACIENTES];
    int numPacientes = 0;
    int opcao;

    printf("Telecare\n");

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Paciente\n");
        printf("2. Inserir Dados de Saude\n");
        printf("3. Analisar Dados de Saude (IA)\n");
        printf("4. Exibir Pacientes\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPaciente(pacientes, &numPacientes);
                break;
            case 2:
                if (numPacientes > 0) {
                    int pacienteID;
                    printf("Escolha o paciente (0 a %d): ", numPacientes - 1);
                    scanf("%d", &pacienteID);
                    if (pacienteID >= 0 && pacienteID < numPacientes) {
                        inserirDadosSaude(&pacientes[pacienteID]);
                    } else {
                        printf("Paciente invalido.\n");
                    }
                } else {
                    printf("Nenhum paciente cadastrado.\n");
                }
                break;
            case 3:
                if (numPacientes > 0) {
                    for (int i = 0; i < numPacientes; i++) {
                        analisarDadosSaude(&pacientes[i]);
                    }
                } else {
                    printf("Nenhum paciente cadastrado.\n");
                }
                break;
            case 4:
                exibirPacientes(pacientes, numPacientes);
                break;
            case 5:
                printf("Saindo do sistema.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}
