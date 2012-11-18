# 0b0b08037efde7615f9c94c7b75e8d8c
CFLAGS=-O$(O) 
O=2
LFLAGS=
OBJS=objs/main.o objs/ResultLine.o objs/filereader.o objs/synchronousfilereader.o objs/asynchronousfilereader.o


.PHONY: all
all: objs a.out

./a.out: $(OBJS)
	@ echo "    LINK ./a.out"
	@ $(CXX) $(OBJS) -o "./a.out" $(LFLAGS)

objs/main.o: main.cpp synchronousfilereader.h
	@ echo "    CXX  ./main.cpp"
	@ $(CXX) $(CFLAGS) -c "./main.cpp" -o $@
objs/ResultLine.o: ResultLine.cpp ResultLine.h
	@ echo "    CXX  ./ResultLine.cpp"
	@ $(CXX) $(CFLAGS) -c "./ResultLine.cpp" -o $@
objs/filereader.o: filereader.cpp filereader.h ResultLine.h
	@ echo "    CXX  ./filereader.cpp"
	@ $(CXX) $(CFLAGS) -c "./filereader.cpp" -o $@
objs/synchronousfilereader.o: synchronousfilereader.cpp \
 synchronousfilereader.h
	@ echo "    CXX  ./synchronousfilereader.cpp"
	@ $(CXX) $(CFLAGS) -c "./synchronousfilereader.cpp" -o $@
objs/asynchronousfilereader.o: asynchronousfilereader.cpp \
 asynchronousfilereader.h filereader.h ResultLine.h
	@ echo "    CXX  ./asynchronousfilereader.cpp"
	@ $(CXX) $(CFLAGS) -c "./asynchronousfilereader.cpp" -o $@

objs:
	@ mkdir "objs"
.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./a.out"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././a.out

.PHONY: d debug
d: debug
debug: CFLAGS += -DDEBUG -g3 -Wall -Wextra
debug: O=0
debug: all

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S $(CHK_SOURCES)
