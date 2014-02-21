.PHONY: all clean install install-strip uninstall

INSTALL_PROGRAM?=install

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
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	$(INSTALL_PROGRAM) bf2c gen_bf $(DESTDIR)$(PREFIX)/bin

install-strip:
	$(MAKE) INSTALL_PROGRAM='install -s' install

uninstall:
	rm -rf $(DESTDIR)$(PREFIX)/bin
