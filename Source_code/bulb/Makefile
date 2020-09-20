CC=gcc
CFLAGS=-g -Wall
# The build target executable:
TARGET=bulb
SRC=./src
INCLUDE_DIR=./include
INCLUDES= -I$(INCLUDE_DIR)
FILE_PARSER=ini_config_parser
SEVEN_SEG_P=seven_seg_peripheral
INFRARED_FC_51_P=infrared_fc_51_peripheral
 

.PHONY: clean

all: $(TARGET)

$(TARGET): $(TARGET).o $(FILE_PARSER).o $(SEVEN_SEG_P).o $(INFRARED_FC_51_P).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o $(FILE_PARSER).o $(SEVEN_SEG_P).o $(INFRARED_FC_51_P).o

$(TARGET).o: $(SRC)/$(TARGET).c $(INCLUDE_DIR)/$(TARGET).h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC)/$(TARGET).c

$(FILE_PARSER).o: $(SRC)/$(FILE_PARSER).c $(INCLUDE_DIR)/$(FILE_PARSER).h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC)/$(FILE_PARSER).c

$(SEVEN_SEG_P).o: $(SRC)/$(SEVEN_SEG_P).c $(INCLUDE_DIR)/$(SEVEN_SEG_P).h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC)/$(SEVEN_SEG_P).c

$(INFRARED_FC_51_P).o: $(SRC)/$(INFRARED_FC_51_P).c $(INCLUDE_DIR)/$(INFRARED_FC_51_P).h
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC)/$(INFRARED_FC_51_P).c

clean:
	$(RM) $(TARGET)
	$(RM) $(TARGET).o
	$(RM) $(TARGET).S
