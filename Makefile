all: v1 v2

v1:
	gcc -o v1 mainQ1.c -lpthread

v2:
	gcc -o v2 mainQ2.c -lpthread

clean:
	rm -f v1 v2
