CPP=g++
CPPFLAGS=-g -Wall -std=c++0x
LDFLAGS=-lpthread
EXECUTABLE=example

SRCS=main.ccp bitmap.ccp hsv_helper.cpp led_strip.cpp spi.cpp
OBJS=$(subst .ccp,.o,$(SRCS))

all: clean example

example: $(OBJS)
	$(CPP) $(CPPFLAGS) -o $(EXECUTABLE) $(OBJS) $(LDFLAGS)

clean:
	rm -rf *.o