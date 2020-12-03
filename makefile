#<<compiler
CC = g++
#<<file type
TYPE=cc
#<<out bin
TARGET = AESAPPLY
#<<out directory
OUTDIR = ./bin

#<< flags -w去除警告   -Wall 添加警告
CFLAGS = -g -std=c++11 -w 

#FILE DISK


#<< head file
INCS = -I ./inc
INCS += -I /$(DISK)/soft/openssl/OpenSSL-Win64include/openssl
INCS += -I $(DISK):\soft\openssl\OpenSSL-Win64\include
INCS += -I $(DISK):\soft\openssl\OpenSSL-Win64\include\openssl
#<< linkpath
LINKPATH = -L $(DISK):\soft\openssl\OpenSSL-Win64\lib
#<< link
LINK  = 
#LINK  += -ltommath 
LINK  += -llibssl 
LINK  += -llibcrypto
#<< creat forld
CREAT_FORLD = XXX

CFLAGS += $(INCS)


SRC = ./src
OBJ = $(SRC)/obj

#<< all source file(*.c *.cc)
SOURCE =  $(wildcard $(SRC)/*.$(TYPE))
SOURCE := $(notdir $(SOURCE))

#<< all object file (*.o)
OBJS   =  $(patsubst %.$(TYPE),%.o,$(SOURCE))
OBJS   := $(foreach X,$(OBJS),$(OBJ)/$(X))


.PHONY:all
all:$(CREAT_FORLD) $(TARGET)
$(CREAT_FORLD):
	mkdir -p $(OBJ) $(OUTDIR)
#<< creat *.o file
$(OBJ)/%.o:$(SRC)/%.$(TYPE) 
	$(CC) $(CFLAGS) -c -o  $@ $<

#<< creat bin file
$(TARGET):$(OBJS)
	$(CC) -o $(OUTDIR)/$(TARGET) $(OBJS) $(LINKPATH) $(LINK)


.PHONY:clean
clean:
	rm -rf $(OBJ) $(OUTDIR)


