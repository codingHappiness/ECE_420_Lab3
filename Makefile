all: main.c Lab3IO.c
	gcc -o datagen datagen.c Lab3IO.c
	gcc -o main main.c Lab3IO.c -fopenmp -lm -O3

noops: main.c Lab3IO.c
	gcc -o datagen datagen.c Lab3IO.c
	gcc -o main main.c Lab3IO.c -fopenmp -lm

clean:
	rm datagen main data_input data_output serialtester

clean-win32:
	rm datagen.exe main.exe data_input data_output serialtester.exe
