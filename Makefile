.PHONY: all clean install

all: bf2c gen_bf

hdr = parsetree.h
obj = bf2c.o parsetree.o token.o tree.o

parsetree.o: parsetree.h
token.o: token.h
tree.o: tree.h
bf2c.o: $(hdr)

bf2c: $(obj)
	$(CXX) -o $@ $(obj)

clean:
	rm bf2c gen_bf $(obj)

install:
	install bf2c gen_bf $(PREFIX)/bin
