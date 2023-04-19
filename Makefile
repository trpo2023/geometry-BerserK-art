CFLAGS = -Wall
CPPFLAGS = -MMD

bin/geometry: obj/src/geometry/geometry.o obj/src/libgeometry/libgeometry.a
	gcc $(CFLAGS) -o $@ $^ -lm
	
test: bin/test
	
bin/test: obj/src/test/test.o obj/src/test/main.o
	gcc $(CFLAGS) -o $@ $^ -lm

obj/src/test/test.o: test/parser_test.c 
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -I thirdparty -o $@ $<
		
obj/src/test/main.o: test/main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -I thirdparty -o $@ $<
	
obj/src/geometry/geometry.o: src/geometry/main.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $<
#библиотека
obj/src/libgeometry/libgeometry.a: obj/src/libgeometry/lexer.o obj/src/libgeometry/parser.o obj/src/libgeometry/figures.o
	ar rcs $@ $^

obj/src/libgeometry/lexer.o: src/libgeometry/lexer.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $<
        
obj/src/libgeometry/parser.o: src/libgeometry/parser.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $<
	
obj/src/libgeometry/figures.o: src/libgeometry/figures.c
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -o $@ $< -lm

clean:
	rm obj/*/*.[oad] bin/*

.PHONY: clean test
	
-include obj/src/geometry/geometry.d obj/src/libgeometry/lexer.d obj/src/libgeometry/parser.d
