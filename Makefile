CFlags = -g -std=c11 -Wall
all: P11 P12 P21 P22

P11: P11.c
	gcc $(CFlags) P11.c -o P11 
P12: P12.c
	gcc $(CFlags) P12.c -o P12
P21: P21.c
	gcc $(CFlags) P21.c -o P21 -lm
P22: P22.c
	gcc $(CFlags) P22.c -o P22 -lm
clean:
	rm P11 P12 P21 P22
