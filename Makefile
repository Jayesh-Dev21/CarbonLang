CC = gcc
CFLAGS = -Wall

TARGET = carbon_run

SRC = main.c dependencies/lexer.c dependencies/transpiler.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)