all:
	g++ -Wall -g -o pokeTool main.cc

clean:
	clear
	-rm -r a.out *.o pokeTool *.tmp
	ls -l

tempClean:
	-rm ./pokeTemp/*.tmp
