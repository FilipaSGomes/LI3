# LI3 - Guião 1

Projeto realizado no âmbito da disciplina de Laboratórios de Informática III.

## Tabela de Conteúdos

- **[O Programa](#Código-do-Projeto)**
- **[Como Usar](#Como-Usar)**
- **[Documentação](#Documentação)**
- **[Créditos](#Créditos)**

## Código do Projeto

O Guião 1 de LI3 foi realizado na linguagem C, assim como proposto pelos docentes.

O seu _Source Code_ encontra-se armazenado na pasta `/src` deste repositório, contendo os ficheiros `*.c` e `*.h` necessários à compilação do projeto.

## Como Usar

Para a execução deste guião devem existir os seguintes ficheiros localizados na pasta `/entrada`:

- `commits.csv`
- `repos.csv`
- `users.csv`

Tendo estas regras sendo cumpridas compilar o código devemos correr o seguinte comando:

 `make`

Isto fará com que o ficheiro Makefile faça a compilação dos _Source Files_ e o linking dos ficheiros `*.o` gerados. Após a conclusão da sua execução será gerado o ficheiro executável `guiao-1`.

A partir deste ponto o programa encontra-se pronto a ser executado usandos os comandos:

`./guiao-1 exercicio-1`

`./guiao-1 exercicio-2`

É de lembrar que os comandos devem ser executados pela ordem acima indicada uma vez que existe um encadeamento de dependencias entre exercicios.

Por fim, para _"limpar"_ os ficheiros gerados com a execução do `make` e do executavél usamos o comando:

`make clean`

**A execução do comando a cima elimina todos os resultados gerados, bem como os ficheiros `*.o` e o executável!**

## Documentação

A documentação do código deste projeto pode ser encontrada na pasta `docs/`, bem como o relatório referente ao trabalho realizado.

Para gerar a documentação do código deve ser corrido, dentro da pasta `docs/` o comando:

`doxygen Doxyfile`

Este gera toda a documentação num formato html mais _user friendly_ e pode ser acedido através do atalho `docs/Documentação` ou `docs/html/index.html`.

Por sua vez o relatório, produzido recorrendo a LaTeX encontra-se em `docs/relatorio.pdf`.

## Créditos

Este trabalho foi realizado por:

- a96556 - Filipa de Sousa Gomes , [FilipaSGomes](https://github.com/FilipaSGomes) 

- a96794 - Ricardo Alves Oliveira , [RicAlvesO](https://github.com/RicAlvesO) 

- a97257 - João Miguel Ferreira Loureiro , [jmfl27](https://github.com/jmfl27) 
