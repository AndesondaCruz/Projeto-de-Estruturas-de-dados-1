
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atacadao.h"

#define ARQ_ITENS "data/itens.dat"
#define ARQ_EMAILS "data/emails.txt"
#define ARQ_USUARIOS "data/usuarios.txt"

Item *itens = NULL;
int totalItens = 0;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int existeUsuarios() {
    FILE *f = fopen(ARQ_USUARIOS, "r");
    if (!f) return 0;
    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    fclose(f);
    return tam > 0;
}

int emailValidoUnico(char email[]) {
    FILE *f = fopen(ARQ_EMAILS, "r");
    char linha[MAX_EMAIL];
    if (!strchr(email, '@') || strlen(email) >= MAX_EMAIL) {
        if (f) fclose(f);
        return 0;
    }
    if (f) {
        while (fgets(linha, sizeof(linha), f)) {
            linha[strcspn(linha, "\n")] = '\0';
            if (strcmp(linha, email) == 0) {
                fclose(f);
                return 0;
            }
        }
        fclose(f);
    }
    return 1;
}

void cadastrarUsuario() {
    Usuario u;
    char buffer[100];
    FILE *f = fopen(ARQ_USUARIOS, "a");
    FILE *fe = fopen(ARQ_EMAILS, "a");
    if (!f || !fe) {
        printf("Erro ao abrir arquivos para cadastro.\n");
        exit(1);
    }
    printf("\n=== Cadastro de novo usuário ===\n");
    printf("Usuário: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(u.usuario, buffer, MAX_USER);
    printf("Senha: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(u.senha, buffer, MAX_SENHA);
    int emailValido = 0;
    do {
        printf("E-mail: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (!emailValidoUnico(buffer)) {
            printf("E-mail inválido ou já cadastrado. Tente outro.\n");
        } else {
            emailValido = 1;
            strncpy(u.email, buffer, MAX_EMAIL);
        }
    } while (!emailValido);
    fprintf(f, "%s %s %s\n", u.usuario, u.senha, u.email);
    fprintf(fe, "%s\n", u.email);
    fclose(f);
    fclose(fe);
    printf("Usuário cadastrado com sucesso!\n\n");
}

int login() {
    char usuario[MAX_USER], senha[MAX_SENHA];
    char linha[200];
    char uArquivo[MAX_USER], sArquivo[MAX_SENHA], eArquivo[MAX_EMAIL];
    FILE *f;
    int autenticado = 0;
    while (!autenticado) {
        printf("\n=== Login ===\n");
        printf("Usuário: ");
        fgets(usuario, sizeof(usuario), stdin);
        usuario[strcspn(usuario, "\n")] = '\0';
        printf("Senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';
        f = fopen(ARQ_USUARIOS, "r");
        if (!f) {
            printf("Erro ao abrir arquivo de usuários.\n");
            exit(1);
        }
        autenticado = 0;
        while (fgets(linha, sizeof(linha), f)) {
            sscanf(linha, "%s %s %s", uArquivo, sArquivo, eArquivo);
            if (strcmp(usuario, uArquivo) == 0 && strcmp(senha, sArquivo) == 0) {
                autenticado = 1;
                break;
            }
        }
        fclose(f);
        if (!autenticado) {
            printf("Usuário ou senha incorretos. Tente novamente.\n");
        }
    }
    return 1;
}

void mensagemBoasVindas() {
    printf("\nBem-vindo ao Atacadão Central! Economia para o seu negócio começa aqui.\n\n");
}

void carregarItens() {
    FILE *f = fopen(ARQ_ITENS, "rb");
    Item temp;
    totalItens = 0;
    if (!f) return;
    while (fread(&temp, sizeof(Item), 1, f)) {
        itens = realloc(itens, (totalItens + 1) * sizeof(Item));
        itens[totalItens++] = temp;
    }
    fclose(f);
}

void salvarItens() {
    FILE *f = fopen(ARQ_ITENS, "wb");
    if (!f) {
        printf("Erro ao salvar itens.\n");
        return;
    }
    fwrite(itens, sizeof(Item), totalItens, f);
    fclose(f);
}

void cadastrarItem() {
    Item novo;
    char buffer[100];
    printf("\nCadastro de item:\n");
    printf("ID do item: ");
    scanf("%d", &novo.id);
    limparBuffer();
    printf("Nome do item: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcpy(novo.nome, buffer);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();
    printf("Preço: ");
    scanf("%f", &novo.preco);
    limparBuffer();
    printf("Item em promoção (1-Sim / 0-Não): ");
    scanf("%d", &novo.promocao);
    limparBuffer();
    itens = realloc(itens, (totalItens + 1) * sizeof(Item));
    itens[totalItens++] = novo;
    salvarItens();
    printf("Item cadastrado com sucesso!\n");
}

void listarItens() {
    printf("\nLista de Itens:\n");
    for (int i = 0; i < totalItens; i++) {
        printf("ID: %d | Nome: %s | Qtd: %d | Preço: %.2f | Promoção: %s\n",
            itens[i].id, itens[i].nome, itens[i].quantidade, itens[i].preco,
            itens[i].promocao ? "Sim" : "Não");
    }
}

void ordenarItens() {
    if (totalItens <= 1) return;
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = i + 1; j < totalItens; j++) {
            if (itens[i].id > itens[j].id) {
                Item temp = itens[i];
                itens[i] = itens[j];
                itens[j] = temp;
            }
        }
    }
}

int buscaBinaria(int id) {
    int esq = 0, dir = totalItens - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        if (itens[meio].id == id) return meio;
        else if (id < itens[meio].id) dir = meio - 1;
        else esq = meio + 1;
    }
    return -1;
}

void menu() {
    int opcao;
    do {
        printf("\n=== Menu Principal ===\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Listar itens\n");
        printf("3 - Ordenar Itens\n");
        printf("4 - Buscar item por ID (Busca Binária)\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        switch (opcao) {
            case 1: cadastrarItem(); break;
            case 2: listarItens(); break;
            case 3: ordenarItens(); printf("Itens ordenados!\n"); break;
            case 4: {
                int idBusca;
                printf("ID para buscar: ");
                scanf("%d", &idBusca);
                limparBuffer();
                int pos = buscaBinaria(idBusca);
                if (pos != -1) {
                    printf("Encontrado: %s - Qtd: %d - R$ %.2f\n",
                        itens[pos].nome, itens[pos].quantidade, itens[pos].preco);
                } else {
                    printf("Item não encontrado.\n");
                }
                break;
            }
            case 5: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 5);
}

int main() {
    if (!existeUsuarios()) {
        printf("Nenhum usuário cadastrado. Por favor, faça o cadastro primeiro.\n");
        cadastrarUsuario();
    }
    if (login()) {
        mensagemBoasVindas();
        carregarItens();
        menu();
        salvarItens();
    }
    free(itens);
    return 0;
}"}
