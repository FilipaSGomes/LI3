# My third makefile
 
# Name of the project
PROJ_NAME=guiao-2
 
# .c files
C_SOURCE=$(wildcard ./src/*.c)
 
# .h files
H_SOURCE=$(wildcard ./src/*.h)
 
# Object files
OBJ=$(subst .c,.o,$(subst src,obj,$(C_SOURCE)))
 
# Compiler and linker
CC=gcc
 
# Flags for compiler
CC_FLAGS=-c -Wextra -Werror -Wall -pedantic -g -lm $(pkg-config --cflags --libs glib-2.0)

# Command used at clean target
RM = rm -rf

#
# Compilation and linking
#
all: objFolder outpFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./obj/%.o: ./src/%.c ./src/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
 
./obj/main.o: ./src/main.c $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '
 
objFolder:
	@ mkdir -p obj

outpFolder:
	@ mkdir -p saida
 
clean:
	@ $(RM) ./obj/*.o $(PROJ_NAME) *~
	@ $(RM) ./testes/*_output.txt
	@ $(RM) saida

.PHONY: all clean
