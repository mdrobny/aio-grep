# 363fc217e4b72268182a2924478a3399
CFLAGS=-O$(O) 
O=2
LFLAGS=-lrt -lboost_regex
OBJS=objs/resultline.o objs/timer.o objs/mmapfilereader.o objs/main.o objs/filereader.o objs/dummyregexfinder.o objs/synchronousfilereader.o objs/fileinfo.o objs/asynchronousfilereader.o objs/flags.o objs/agrep.o objs/regexfinder.o objs/output.o objs/boostregexfinder.o


.PHONY: all
all: objs aio-grep

./aio-grep: $(OBJS)
	@ echo "    LINK ./aio-grep"
	@ $(CXX) $(OBJS) -o "./aio-grep" $(LFLAGS)

objs/resultline.o: src/resultline.cpp src/resultline.h
	@ echo "    CXX  src/resultline.cpp"
	@ $(CXX) $(CFLAGS) -c "src/resultline.cpp" -o $@
objs/timer.o: src/timer.cpp src/timer.h
	@ echo "    CXX  src/timer.cpp"
	@ $(CXX) $(CFLAGS) -c "src/timer.cpp" -o $@
objs/mmapfilereader.o: src/mmapfilereader.cpp src/mmapfilereader.h \
 src/filereader.h src/resultline.h src/regexfinder.h
	@ echo "    CXX  src/mmapfilereader.cpp"
	@ $(CXX) $(CFLAGS) -c "src/mmapfilereader.cpp" -o $@
objs/main.o: src/main.cpp src/agrep.h src/flags.h src/synchronousfilereader.h \
 src/filereader.h src/resultline.h src/regexfinder.h \
 src/asynchronousfilereader.h src/fileinfo.h src/mmapfilereader.h \
 src/dummyregexfinder.h src/output.h src/timer.h
	@ echo "    CXX  src/main.cpp"
	@ $(CXX) $(CFLAGS) -c "src/main.cpp" -o $@
objs/filereader.o: src/filereader.cpp src/filereader.h src/resultline.h \
 src/regexfinder.h
	@ echo "    CXX  src/filereader.cpp"
	@ $(CXX) $(CFLAGS) -c "src/filereader.cpp" -o $@
objs/dummyregexfinder.o: src/dummyregexfinder.cpp src/dummyregexfinder.h \
 src/regexfinder.h src/resultline.h
	@ echo "    CXX  src/dummyregexfinder.cpp"
	@ $(CXX) $(CFLAGS) -c "src/dummyregexfinder.cpp" -o $@
objs/synchronousfilereader.o: src/synchronousfilereader.cpp \
 src/synchronousfilereader.h src/filereader.h src/resultline.h \
 src/regexfinder.h
	@ echo "    CXX  src/synchronousfilereader.cpp"
	@ $(CXX) $(CFLAGS) -c "src/synchronousfilereader.cpp" -o $@
objs/fileinfo.o: src/fileinfo.cpp src/fileinfo.h
	@ echo "    CXX  src/fileinfo.cpp"
	@ $(CXX) $(CFLAGS) -c "src/fileinfo.cpp" -o $@
objs/asynchronousfilereader.o: src/asynchronousfilereader.cpp \
 src/asynchronousfilereader.h src/filereader.h src/resultline.h \
 src/regexfinder.h src/fileinfo.h
	@ echo "    CXX  src/asynchronousfilereader.cpp"
	@ $(CXX) $(CFLAGS) -c "src/asynchronousfilereader.cpp" -o $@
objs/flags.o: src/flags.cpp src/flags.h src/synchronousfilereader.h \
 src/filereader.h src/resultline.h src/regexfinder.h \
 src/asynchronousfilereader.h src/fileinfo.h src/mmapfilereader.h \
 src/dummyregexfinder.h
	@ echo "    CXX  src/flags.cpp"
	@ $(CXX) $(CFLAGS) -c "src/flags.cpp" -o $@
objs/agrep.o: src/agrep.cpp src/agrep.h src/flags.h \
 src/synchronousfilereader.h src/filereader.h src/resultline.h \
 src/regexfinder.h src/asynchronousfilereader.h src/fileinfo.h \
 src/mmapfilereader.h src/dummyregexfinder.h src/output.h src/timer.h
	@ echo "    CXX  src/agrep.cpp"
	@ $(CXX) $(CFLAGS) -c "src/agrep.cpp" -o $@
objs/regexfinder.o: src/regexfinder.cpp src/regexfinder.h src/resultline.h
	@ echo "    CXX  src/regexfinder.cpp"
	@ $(CXX) $(CFLAGS) -c "src/regexfinder.cpp" -o $@
objs/output.o: src/output.cpp src/output.h src/resultline.h src/timer.h
	@ echo "    CXX  src/output.cpp"
	@ $(CXX) $(CFLAGS) -c "src/output.cpp" -o $@
objs/boostregexfinder.o: src/boostregexfinder.cpp src/boostregexfinder.h \
 src/regexfinder.h src/resultline.h
	@ echo "    CXX  src/boostregexfinder.cpp"
	@ $(CXX) $(CFLAGS) -c "src/boostregexfinder.cpp" -o $@

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
