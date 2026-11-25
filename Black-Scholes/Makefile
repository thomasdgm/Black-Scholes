CXX = g++

CORE_OBJS = obj/normalDistribution.o obj/delta.o obj/gamma.o obj/vega.o obj/theta.o obj/rho.o obj/blackScholes.o obj/volatility.o
LIB_OBJS = obj/bridge.o $(CORE_OBJS)

ifeq ($(OS),Windows_NT)
	LIB = bin/blackScholes.dll
	CLI = bin/blackScholes.exe
	SHARED_FLAG = -shared -static-libgcc -static-libstdc++ -Wl,-Bstatic -lpthread -Wl,-Bdynamic
	MKDIR = @if not exist bin mkdir bin & if not exist obj mkdir obj
	COPY_RUNTIME = @powershell -NoProfile -Command "$$p = Split-Path (Get-Command g++ -ErrorAction SilentlyContinue).Source; if ($$p -and (Test-Path \"$$p\\libwinpthread-1.dll\")) { Copy-Item \"$$p\\libwinpthread-1.dll\" \"bin\\libwinpthread-1.dll\" -Force }"
	CLEAN = cmd /C "if exist obj\*.o del /Q obj\*.o & if exist bin\* del /Q bin\*"
else
	LIB = bin/libblackScholes.so
	CLI = bin/blackScholes
	SHARED_FLAG = -shared -fPIC
	MKDIR = mkdir -p bin obj
	COPY_RUNTIME = @true
	CLEAN = rm -f obj/*.o bin/*
endif

all: dirs bin/blackScholes $(LIB)
lib: dirs $(LIB)

dirs:
	$(MKDIR)

bin/blackScholes: $(CORE_OBJS) obj/main.o | dirs
	$(CXX) -o bin/blackScholes $(CORE_OBJS) obj/main.o -Wl,-Bstatic -lpthread -Wl,-Bdynamic

$(LIB): $(LIB_OBJS) | dirs
	$(CXX) $(SHARED_FLAG) $(LIB_OBJS) -o $(LIB)
	$(COPY_RUNTIME)

obj/main.o: src/main.cpp
	$(CXX) -c src/main.cpp -o obj/main.o

obj/bridge.o: src/bridge.cpp
	$(CXX) -c src/bridge.cpp -o obj/bridge.o

obj/volatility.o: src/volatility.cpp
	$(CXX) -c src/volatility.cpp -o obj/volatility.o

obj/blackScholes.o: src/blackScholes.cpp
	$(CXX) -c src/blackScholes.cpp -o obj/blackScholes.o

obj/rho.o: src/rho.cpp
	$(CXX) -c src/rho.cpp -o obj/rho.o

obj/theta.o: src/theta.cpp
	$(CXX) -c src/theta.cpp -o obj/theta.o

obj/vega.o: src/vega.cpp
	$(CXX) -c src/vega.cpp -o obj/vega.o

obj/gamma.o: src/gamma.cpp
	$(CXX) -c src/gamma.cpp -o obj/gamma.o

obj/delta.o: src/delta.cpp
	$(CXX) -c src/delta.cpp -o obj/delta.o

obj/normalDistribution.o: src/normalDistribution.cpp
	$(CXX) -c src/normalDistribution.cpp -o obj/normalDistribution.o

clean:
	$(CLEAN)