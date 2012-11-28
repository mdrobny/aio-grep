# 365c7aaf41106d365b3d73185278c08e
CFLAGS=-O$(O) -std=c++11
O=2
LFLAGS=-l rt
OBJS=objs/filereader.o objs/fileinfo.o objs/synchronousfilereader.o objs/cpp11regexfinder.o objs/regexfinder.o objs/dummyregexfinder.o objs/asynchronousfilereader.o objs/main.o objs/resultline.o


.PHONY: all
all: objs aio-grep

./aio-grep: $(OBJS)
	@ echo "    LINK ./aio-grep"
	@ $(CXX) $(OBJS) -o "./aio-grep" $(LFLAGS)

objs/filereader.o: src/filereader.cpp src/filereader.h src/resultline.h \
 src/regexfinder.h
	@ echo "    CXX  src/filereader.cpp"
	@ $(CXX) $(CFLAGS) -c "src/filereader.cpp" -o $@
objs/fileinfo.o: src/fileinfo.cpp src/fileinfo.h
	@ echo "    CXX  src/fileinfo.cpp"
	@ $(CXX) $(CFLAGS) -c "src/fileinfo.cpp" -o $@
objs/synchronousfilereader.o: src/synchronousfilereader.cpp \
 src/synchronousfilereader.h src/filereader.h src/resultline.h \
 src/regexfinder.h
	@ echo "    CXX  src/synchronousfilereader.cpp"
	@ $(CXX) $(CFLAGS) -c "src/synchronousfilereader.cpp" -o $@
objs/cpp11regexfinder.o: src/cpp11regexfinder.cpp src/cpp11regexfinder.h \
 src/regexfinder.h src/resultline.h
	@ echo "    CXX  src/cpp11regexfinder.cpp"
	@ $(CXX) $(CFLAGS) -c "src/cpp11regexfinder.cpp" -o $@
objs/regexfinder.o: src/regexfinder.cpp src/regexfinder.h src/resultline.h
	@ echo "    CXX  src/regexfinder.cpp"
	@ $(CXX) $(CFLAGS) -c "src/regexfinder.cpp" -o $@
objs/dummyregexfinder.o: src/dummyregexfinder.cpp src/dummyregexfinder.h \
 src/regexfinder.h src/resultline.h
	@ echo "    CXX  src/dummyregexfinder.cpp"
	@ $(CXX) $(CFLAGS) -c "src/dummyregexfinder.cpp" -o $@
objs/asynchronousfilereader.o: src/asynchronousfilereader.cpp \
 src/asynchronousfilereader.h src/filereader.h src/resultline.h \
 src/regexfinder.h src/fileinfo.h
	@ echo "    CXX  src/asynchronousfilereader.cpp"
	@ $(CXX) $(CFLAGS) -c "src/asynchronousfilereader.cpp" -o $@
objs/main.o: src/main.cpp src/synchronousfilereader.h src/filereader.h \
 src/resultline.h src/regexfinder.h src/dummyregexfinder.h
	@ echo "    CXX  src/main.cpp"
	@ $(CXX) $(CFLAGS) -c "src/main.cpp" -o $@
objs/resultline.o: src/resultline.cpp src/resultline.h
	@ echo "    CXX  src/resultline.cpp"
	@ $(CXX) $(CFLAGS) -c "src/resultline.cpp" -o $@

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
