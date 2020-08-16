CC=gcc
CFLAGS=-g -Wall
# The build target executable:
TARGET=bulb
SRC=./src
INCLUDE_DIR=./include
INCLUDES= -I$(INCLUDE_DIR)

.PHONY: clean

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: $(SRC)/$(TARGET).c $(INCLUDE_DIR)/$(TARGET).h
	$(CC) $(CFLAGS)  $(INCLUDES) -c $(SRC)/$(TARGET).c

clean:
	$(RM) $(TARGET)
	$(RM) $(TARGET).o
	$(RM) $(TARGET).S
