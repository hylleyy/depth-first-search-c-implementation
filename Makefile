# flagsss
CC = gcc
CFLAGS = -I./include -Wall ${RE_PATH}
RE_PATH = -I"C:\MinGW\msys\1.0\include" -L"C:\MinGW\msys\1.0\lib" -lregex # MingW MSYS workaround for regex library in Windows. Change it for your own regex flags if needed

# source to object
SRCS = $(wildcard src/*.c) $(wildcard src/utils/*.c)
OBJS = $(SRCS:.c=.o)

# final executable
TARGET = graph
all: $(TARGET)

# linking
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

# compiling
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	del /Q src\*.o src\utils\*.o $(TARGET).exe

# debug mode
debug: CFLAGS += -DDEBUG -D__USE_MINGW_ANSI_STDIO=1 -g
debug: clean $(TARGET)