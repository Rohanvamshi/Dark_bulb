CC=gcc
CFLAGS=-g -Wall
# The build target executable:
TARGET=bulb
SRC=./src
INCLUDE_DIR=./include
INCLUDES= -I$(INCLUDE_DIR)
FILE_PARSER=ini_config_parser

.PHONY: clean

all: $(TARGET)

$(TARGET): $(TARGET).o $(FILE_PARSER).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o $(FILE_PARSER).o

$(TARGET).o: $(SRC)/$(TARGET).c $(INCLUDE_DIR)/$(TARGET).h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC)/$(TARGET).c

$(FILE_PARSER).o: $(SRC)/$(FILE_PARSER).c $(INCLUDE_DIR)/$(FILE_PARSER).h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC)/$(FILE_PARSER).c

clean:
	$(RM) $(TARGET)
	$(RM) $(TARGET).o
	$(RM) $(TARGET).S
