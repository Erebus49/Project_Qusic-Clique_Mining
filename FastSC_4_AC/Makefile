FastSC: wscp.h main.cpp mersenne_rng.cpp
	g++ main.cpp mersenne_rng.cpp -static -O3 -o FastSC

FastSC_parallel: wscp.h main_parallel.cpp mersenne_rng.cpp
	g++ main_parallel.cpp mersenne_rng.cpp -static -O3 -o FastSC_parallel

clean:
	rm -f *~