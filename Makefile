CXX = cc
CFLAGS = -Wall
INCLUDE = -I/usr/local/include -I/usr/include -Iinclude
LDFLAGS = -L/usr/local/lib -I/usr/lib
LDLIBS = -lcurl

SOURCES = app.c
OUT = app

all: build

build: $(SOURCES)
	$(CXX) -o $(OUT) $(INCLUDE) $(LDFLAGS) $(CFLAGS) $(SOURCES) $(LDLIBS)

clean:
	ls

