CC=gcc
CFLAGS=  -Wall 
CSTATICLINK= -lm
SRCS= benzetim.c compute.c
OBJS := $(SRCS:%.c=%.o)
TARGET=benzetim
DEBUG=-g #You can include debug instruction or not

all: $(TARGET)


$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


clean:
	rm *.o
	

