all: test test_p
test: sequential.cpp
	g++ -o test sequential.cpp -lomp
test_p: parall.cpp
	clang++ -Xpreprocessor -fopenmp -o test_p parall.cpp -lomp
clean: test test_p
	rm test test_p
