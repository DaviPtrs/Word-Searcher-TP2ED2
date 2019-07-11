#	A Flag -c diz para gerar o arquivo de objeto, o -o $@ diz para colocar a saída da compilação no arquivo nomeado no lado esquerdo do :, o $< é o primeiro item na lista de dependências, e o A macro CFLAGS é definida como acima.
#	Como simplificação final, vamos usar as macros especiais $@ e $^, que são os lados esquerdo e direito de :, respectivamente, para tornar a regra geral de compilação mais geral. 
#	No exemplo abaixo, todos os arquivos de inclusão devem ser listados como parte da macro DEPS e todos os arquivos de objetos devem ser listados como parte da macro OBJ.

#Flags interessantes
#-Wall dispara todos os warnings em seu código
#-g necessário para avaliar o código do valgrind (permite o valgrind dizer em que linha dá merda)
#-lm obrigatorio caso utilize a biblioteca math.h

CC=gcc
CFLAGS=-I. -Wall -lm -O3
OBJ = file.o word.o word_list.o output.o file_list.o int_list.o hash_table.o tree.o AVL.o trie.o benchmark.o

all: main

%.o: src/%.c include/*.h
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ) main.o
	$(CC) -o $@ $^ $(CFLAGS)
	rm -f *.o
clean:
	rm -f *.o
	rm -f ${EXEC}
	rm -f main
	rm -f lista
	rm -f arv
	rm -f tests/*.o
