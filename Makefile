all : hw1_naive hw1_kmp

hw1_naive : hw1_naive.c
	gcc -g hw1_naive.c -o hw1_naive

hw1_kmp : hw1_kmp.c
	gcc -g hw1_kmp.c -o hw1_kmp

.PHONY : clean
clean :
	rm hw1_naive hw1_kmp
