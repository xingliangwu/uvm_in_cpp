INCLUDES= -I. -Ibase -Ireg
CFLAGS=-std=c++1z

uvm_pkg.so : uvm_pkg.o
	$(CC) -shared -o $@ $^

uvm_pkg.o : uvm_pkg.hh
	$(CXX) $(CFLAGS) $(LDFLAGS) ${INCLUDES} -o $@ $^ $(LDLIBS)
 
test.o : test.cc
	$(CXX) $(CFLAGS) $(LDFLAGS) ${INCLUDES} -o $@ $^ $(LDLIBS)

clean:
	rm -f *.o *.so
