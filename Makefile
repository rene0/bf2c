.PHONY: all clean

all: bf2c

hdr = parsetree.h
obj = bf2c.o parsetree.o token.o tree.o

parsetree.o: parsetree.h
token.o: token.h
tree.o: tree.h
bf2c.o: $(hdr)

bf2c: $(obj)
	$(CXX) -o $@ $(obj)

clean:
	rm bf2c $(obj)
