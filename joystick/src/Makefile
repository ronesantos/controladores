CC :=gcc
CFLAGS := -g -Wall -pthread 

TARGET := main
all: $(TARGET)

main: main.c joystick.h
	$(CC) $(CFLAGS) main.c -o main


clean:
	rm -rf main 
