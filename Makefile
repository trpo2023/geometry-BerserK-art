CFLAGS = -Wall
CPPFLAGS = -MMD

bin/geometry: obj/src/geometry/geometry.o obj/src/libgeometry/libgeometry.a
	gcc $(CFLAGS) -o $@ $^ -lm
	
test: bin/parser_test bin/lexer_test bin/calc_test
	
bin/parser_test: obj/src/test/parser_test.o obj/src/test/main.o obj/src/libgeometry/libgeometry.a
	gcc $(CFLAGS) -o $@ $^ -lm
	
bin/lexer_test: obj/src/test/lexer_test.o obj/src/test/main.o obj/src/libgeometry/libgeometry.a
	gcc $(CFLAGS) -o $@ $^ -lm
	
bin/calc_test: obj/src/test/calc_test.o obj/src/test/main.o obj/src/libgeometry/libgeometry.a
	gcc $(CFLAGS) -o $@ $^ -lm
	
obj/src/test/parser_test.o: test/parser_test.c 
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -I thirdparty -o $@ $<

obj/src/test/lexer_test.o: test/lexer_test.c 
	gcc -c $(CFLAGS) $(CPPFLAGS) -I src -I thirdparty -o $@ $<

obj/src/test/calc_test.o: test/calc_test.c 
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
	rm obj/*/*/*.[oad] bin/*

.PHONY: clean test
	
-include obj/src/geometry/geometry.d obj/src/libgeometry/lexer.d obj/src/libgeometry/parser.d obj/src/test/parser_test.d obj/src/test/lexer_test.d obj/src/test/main.d obj/src/test/calc_test.d
