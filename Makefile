# flagsss
CC = gcc
CFLAGS = -I./include -Wall ${RE_PATH}

RE_PATH = -I"C:\MinGW\msys\1.0\include" -L"C:\MinGW\msys\1.0\lib" -lregex # MingW MSYS workaround for regex library in Windows. Change it for your own regex flags if needed

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRCS = $(call rwildcard,src,*.c)

OBJ = $(SRCS:.c=.o)

TARGET = graph

# linking
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# compiling c to object
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# clean utility to remove objects and the executable
clean:
	del /S *.o $(TARGET).exe