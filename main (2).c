#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REGISTROS 100

struct Registro {
    char nomeDono[50];
    char NomeDoPet[50];
    char Servico[20];
};

void cadastrar(struct Registro *registros, int *numRegistros) {
    if (*numRegistros < MAX_REGISTROS) {
        printf("Digite o nome do dono do pet: ");
        scanf(" %[^\n]", registros[*numRegistros].nomeDono);

        printf("Digite o nome do pet: ");
        scanf(" %[^\n]", registros[*numRegistros].NomeDoPet);

        printf("Qual procedimento deseja fazer no seu Pet? ");
        scanf(" %[^\n]", registros[*numRegistros].Servico);

        (*numRegistros)++;
        printf("Registro cadastrado com sucesso.\n");
    } else {
        printf("Limite de registros atingido.\n");
    }
}

void visualizar(struct Registro *registros, int numRegistros) {
    if (numRegistros > 0) {
        printf("\nRegistros:\n");
        for (int i = 0; i < numRegistros; i++) {
            printf("Nome do Dono: %s\n", registros[i].nomeDono);
            printf("Nome do pet: %s\n", registros[i].NomeDoPet);
            printf("Serviço: %s\n", registros[i].Servico);
            printf("------------------------\n");
        }
    } else {
        printf("Nenhum registro encontrado.\n");
    }
}

void alterar(struct Registro *registros, int numRegistros) {
    char NomeDoPet[50];
    printf("Digite o Nome do Seu pet que quer Alterar: ");
    scanf(" %[^\n]", NomeDoPet);

    for (int i = 0; i < numRegistros; i++) {
        if (strcmp(registros[i].NomeDoPet, NomeDoPet) == 0) {
            printf("Digite o novo nome do Dono: ");
            scanf(" %[^\n]", registros[i].nomeDono);

            printf("Digite o novo nome do Pet: ");
            scanf(" %[^\n]", registros[i].NomeDoPet);

            printf("Digite qual serviço deseja fazer: ");
            scanf(" %[^\n]", registros[i].Servico);

            printf("Registro alterado com sucesso.\n");
            return;
        }
    }

    printf("Registro não encontrado.\n");
}

void excluir(struct Registro *registros, int *numRegistros) {
    char NomeDoPet[50];
    printf("Digite o nome do pet para excluir: ");
    scanf(" %[^\n]", NomeDoPet);

    for (int i = 0; i < *numRegistros; i++) {
        if (strcmp(registros[i].NomeDoPet, NomeDoPet) == 0) {
            // Substituir o registro a ser excluído pelo último registro
            registros[i] = registros[*numRegistros - 1];
            (*numRegistros)--;
            printf("Registro excluído com sucesso.\n");
            return;
        }
    }

    printf("Registro não encontrado.\n");
}

void salvarEmArquivo(struct Registro *registros, int numRegistros) {
    FILE *arquivo;

    if ((arquivo = fopen("dados.bin", "wb")) == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    fwrite(registros, sizeof(struct Registro), numRegistros, arquivo);

    fclose(arquivo);
}

void carregarDoArquivo(struct Registro *registros, int *numRegistros) {
    FILE *arquivo;

    if ((arquivo = fopen("dados.bin", "rb")) != NULL) {
        *numRegistros = fread(registros, sizeof(struct Registro), MAX_REGISTROS, arquivo);
        fclose(arquivo);
    }
}

int main() {
    struct Registro registros[MAX_REGISTROS];
    int numRegistros = 0;

    carregarDoArquivo(registros, &numRegistros);

    int escolha;
    do {
        printf("\nMENU:\n");
        printf("1. Cadastrar\n");
        printf("2. Visualizar\n");
        printf("3. Alterar\n");
        printf("4. Excluir\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                cadastrar(registros, &numRegistros);
                break;
            case 2:
                visualizar(registros, numRegistros);
                break;
            case 3:
                alterar(registros, numRegistros);
                break;
            case 4:
                excluir(registros, &numRegistros);
                break;
            case 0:
                printf("Saindo...\n");
                salvarEmArquivo(registros, numRegistros);
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (escolha != 0);

    return 0;
}
