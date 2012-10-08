sources:= parsetree.cc token.cc tree.cc
objects:= $(patsubst %.cc, %.o, $(sources))

all: bf2c

bf2c:
	$(CXX) $(CXXFLAGS) -c parsetree.cc -o parsetree.o
	$(CXX) $(CXXFLAGS) -c token.cc -o token.o
	$(CXX) $(CXXFLAGS) -c tree.cc -o tree.o
	$(CXX) $(CXXFLAGS) bf2c.cc -o $@ $(objects)

clean:
	rm -f $(objects)
	rm -f bf2c
