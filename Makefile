CC=clang++ -std=c++11
OBJ=src/*.cpp

SDIR=src
IDIR=-Iinclude -I/usr/include/rtmidi
ODIR=obj
LDIR=lib

DEPS=$(SDIR)/%.h $(IDIR)/%.h
LIBS=-lrtmidi

CFLAGS=$(IDIR) -L$(LDIR) -g

$(ODIR)/%.o:$(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

MidiMarkov:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm MidiMarkov

run:
	./MidiMarkov MidiMarkov.mid
