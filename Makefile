# flagsss
CC = gcc
CFLAGS = -I./include -Wall

# source to object
SRCS = $(wildcard src/*.c) $(wildcard src/utils/*.c)
OBJS = $(SRCS:.c=.o)

# final executable
TARGET = graph
all: clean $(TARGET)

# linking
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

# compiling
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	del /Q src\*.o src\utils\*.o $(TARGET).exe

# debug mode
debug: CFLAGS += -DDEBUG -D__USE_MINGW_ANSI_STDIO=1 -g # DEBUG flag activates internal program output; __USE_MINGW_ANSI_STDIO allows using the %zu format specifier in printf (required for printing unsigned integers)
debug: clean $(TARGET)