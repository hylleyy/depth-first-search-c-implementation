# flagsss
CC = gcc
CFLAGS = -I./include -Wall ${RE_PATH}

RE_PATH = -I"C:\MinGW\msys\1.0\include" -L"C:\MinGW\msys\1.0\lib" -lregex # MingW MSYS workaround for regex library in Windows. Change it for your own regex flags if needed

# object files
OBJ = src/main.o src/graph.o src/euler.o

# compiling c to object
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# linking
graph: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
