all: test test_p test_p1 test_p2
test: sequential.cpp
	g++ -o test sequential.cpp -lomp
test_p: SOR_p.cpp
	clang++ -Xpreprocessor -fopenmp -o test_p SOR_p.cpp -lomp
test_p1: SOR_P1.cpp
	clang++ -Xpreprocessor -fopenmp -o test_p1 SOR_P1.cpp -lomp
test_p2: SOR_P2.cpp
	clang++ -Xpreprocessor -fopenmp -o test_p2 SOR_P2.cpp -lomp
clean: test test_p
	rm test test_p
