
#ifndef ATACADAO_H
#define ATACADAO_H

#define MAX_EMAIL 80
#define MAX_USER 30
#define MAX_SENHA 20
#define MAX_NOME_ITEM 50

typedef struct {
    int id;
    char nome[MAX_NOME_ITEM];
    int quantidade;
    float preco;
    int promocao;
} Item;

typedef struct {
    char usuario[MAX_USER];
    char senha[MAX_SENHA];
    char email[MAX_EMAIL];
} Usuario;

void limparBuffer();
int existeUsuarios();
void cadastrarUsuario();
int login();
void mensagemBoasVindas();
void menu();
void carregarItens();
void salvarItens();
void cadastrarItem();
void listarItens();
void editarItem();
void excluirItem();
void listarPromocoes();
void buscarPorNome();
void ajustarEstoque();
void aplicarDesconto();
void ordenarItens();
int buscaBinaria(int id);

#endif // ATACADAO_H
