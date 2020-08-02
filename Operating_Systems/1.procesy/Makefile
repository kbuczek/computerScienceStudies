programa: identyfikatory.o identyfikatory.h procesy_a.o
	gcc identyfikatory.o procesy_a.o -o programa

programb: identyfikatory.o identyfikatory.h procesy_b.o
	gcc identyfikatory.o procesy_b.o -o programb

programc: identyfikatory.o identyfikatory.h procesy_c.o
	gcc identyfikatory.o procesy_c.o -o programc

programd: identyfikatory.o identyfikatory.h procesy_d.o
	gcc identyfikatory.o procesy_d.o -o programd

runa: programa
	./programa

runb: programb
	./programb

runc: programc
	./programc

rund: programd
	./programd

clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
