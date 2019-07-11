Word Searcher - TP2ED2
=============

Indexador de palavras feito em C como 2º trabalho de Estrutura de Dados I

Para uma melhor experiência e entendimento, leia esse readme antes de usar


Compile antes de executar usando
----------

	$ make

Uso
----------

	$ ./main [files] [options] [N param]

Files:
----------
Você deverá passar os caminhos dos arquivos a serem indexados. O programa não possui limite de arquivos, podendo ser passados quantos arquivos o computador do usuário aguentar carregar.

Options:
----------
Essas opções são obrigatórias para o funcionamento do programa.

    0                     Escolhe a opção de Lista Encadeada
    1                     Escolhe a opção de Árvore Binária
    2                     Escolhe a opção de Árvore AVL
    3                     Escolhe a opção de Árvore Prefixada
    4                     Escolhe a opção de Tabela Hash
    5                     Escolhe a opção de Avaliação de Desempenho (Benchmark)

N param:
----------
Essa opção indica quantas palavras serão pesquisadas (default = 0).

Caso não seja indicada, será assumido N = 0.

Se a opção 0 for escolhida e não for escolhido a função Benchmark, além de inserir os elementos na estrutura, também serão impressos os conteúdos das mesmas.

A opção de benchmark junto com N = 0 apenas irá inserir os elementos.
  
    0			Apenas insere e printa a estrutura (default)
    [1..n]		        Pesquisa de 1 até n palavras dadas	


Davi Petris e Jairo Marcos
=============

