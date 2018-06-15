all:
	g++ -Wall -o pokeTool main.cc

clean:
	clear
	-rm -r a.out *.o pokeTool *.tmp
	ls -l

