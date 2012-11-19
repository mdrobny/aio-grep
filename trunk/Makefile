# 5a402f5258a93cb590aad0869dbdc3bf
CFLAGS=-O$(O) 
O=2
LFLAGS=-lrt
OBJS=objs/main.o objs/ResultLine.o objs/filereader.o objs/synchronousfilereader.o objs/asynchronousfilereader.o


.PHONY: all
all: objs aio-grep

./aio-grep: $(OBJS)
	@ echo "    LINK ./aio-grep"
	@ $(CXX) $(OBJS) -o "./aio-grep" $(LFLAGS)

objs/main.o: src/main.cpp src/synchronousfilereader.h src/filereader.h \
 src/ResultLine.h
	@ echo "    CXX  src/main.cpp"
	@ $(CXX) $(CFLAGS) -c "src/main.cpp" -o $@
objs/ResultLine.o: src/ResultLine.cpp src/ResultLine.h
	@ echo "    CXX  src/ResultLine.cpp"
	@ $(CXX) $(CFLAGS) -c "src/ResultLine.cpp" -o $@
objs/filereader.o: src/filereader.cpp src/filereader.h src/ResultLine.h
	@ echo "    CXX  src/filereader.cpp"
	@ $(CXX) $(CFLAGS) -c "src/filereader.cpp" -o $@
objs/synchronousfilereader.o: src/synchronousfilereader.cpp \
 src/synchronousfilereader.h src/filereader.h src/ResultLine.h
	@ echo "    CXX  src/synchronousfilereader.cpp"
	@ $(CXX) $(CFLAGS) -c "src/synchronousfilereader.cpp" -o $@
objs/asynchronousfilereader.o: src/asynchronousfilereader.cpp \
 src/asynchronousfilereader.h src/filereader.h src/ResultLine.h
	@ echo "    CXX  src/asynchronousfilereader.cpp"
	@ $(CXX) $(CFLAGS) -c "src/asynchronousfilereader.cpp" -o $@

objs:
	@ mkdir "objs"
.PHONY: c clean
c: clean
clean:
	@ if [ -d "objs" ]; then rm -r "objs"; fi
	@ rm -f "./aio-grep"
	@ echo "    CLEAN"
.PHONY: f fresh
f: fresh
fresh: clean
	@ make all --no-print-directory
.PHONY: r run
r: run
run: all
	@ ././aio-grep

.PHONY: d debug
d: debug
debug: CFLAGS += -DDEBUG -g3 -Wall -Wextra
debug: O=0
debug: all

.PHONY: check-syntax
check-syntax:
	$(CXX) $(CFLAGS) -fsyntax-only -Wall -o /dev/null -S $(CHK_SOURCES)
