FLAGS = -Wall -Wextra -Werror
FILES = model/graph.cc \
		model/graph_algorithms.cc \
		model/algorithms/aco.cc \
		model/algorithms/ant.cc \
		model/algorithms/sa.cc \
		model/matrix/matrix.cc \

all: clean graph.a run

graph.a: clean
	g++ -c $(FILES)
	ar rcs graph.a *.o
	rm -rf *.o

run: clean graph.a
	g++ $(FLAGS) main.cc view/console_interface.cc graph.a -o run -std=c++17
	./run

test: clean graph.a
	g++ $(FLAGS) view/console_interface.cc graph.a tests/tests.cc -o test -lgtest -std=c++17
	./test

gcov_report: clean graph.a
	g++ $(FLAGS) --coverage $(FILES) tests/tests.cc -o test -lgtest -std=c++17
	./test
	lcov -t "test" --no-external -o test.info -c -d ./
	genhtml -o report test.info
	open ./report/index.html

check: test
	cp -f ../materials/linters/.clang-format .clang-format
	clang-format -i *.cc */*.cc */*.h */*/*.cc */*/*.h
	clang-format -n *.cc */*.cc */*.h */*/*.cc */*/*.h
	cppcheck --language=c++ --enable=all --suppressions-list=suppresionlist.cfg *.cc */*.cc */*.h */*/*.cc */*/*.h
	rm -rf .clang-format
	CK_FORK=no leaks --atExit -- ./test
	
clean: 
	rm -rf run test *.a *.o *.dot
	rm -rf *.gcda *.gcno *.info
	rm -rf ./report
