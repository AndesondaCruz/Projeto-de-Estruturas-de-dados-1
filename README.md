
📦 Sistema Atacadão – Gerenciamento de Estoque

Sistema desenvolvido em C para gerenciamento de itens em um ambiente de atacado, permitindo cadastro, listagem, ordenação e busca eficiente de produtos.

O projeto foi desenvolvido como atividade da disciplina de Estruturas de Dados, com foco na aplicação de conceitos fundamentais como alocação dinâmica de memória, ordenação e busca binária.

📌 Funcionalidades

🔐 Sistema de autenticação

Cadastro de usuários

Login com validação de credenciais

Validação e verificação de e-mail único

📦 Gerenciamento de itens

Cadastro de novos produtos

Listagem de produtos cadastrados

Persistência de dados em arquivos

📊 Estruturas de dados

Armazenamento dinâmico de itens usando alocação dinâmica (malloc/realloc)

Ordenação de itens por ID

Busca eficiente utilizando Busca Binária

💾 Persistência em arquivos

Itens armazenados em arquivo binário

Usuários e e-mails armazenados em arquivos de texto

🧠 Conceitos de Estruturas de Dados Aplicados

Este projeto utiliza diversos conceitos importantes da disciplina:

Alocação dinâmica de memória

Manipulação de arquivos (fopen, fread, fwrite)

Algoritmos de ordenação

Busca binária

Estruturas (struct)

Manipulação de strings

🛠️ Tecnologias Utilizadas

Linguagem C

Manipulação de arquivos

Estruturas de dados

Compilação via GCC

## Estrutura do Projeto
```
/src/        --> Código fonte (.c e .h)
/data/       --> Arquivos de dados gerados
.gitignore   --> Ignorar arquivos compilados e de dados
README.md    --> Descrição do projeto
```

## Como compilar:
```bash
gcc src/atacadao.c -o atacadao
```

## Como executar:
```bash
./atacadao
```
