CC_FLAGS = -Wall -Werror -Wextra
CC = gcc
NAME = s21_matrix.a test
TEST_LIBS = -lcheck -lm -lpthread
OBJECTS =  s21_matrix.o
SOURSES =  s21_matrix.c

.PHONY: all clean test s21_matrix.a gcov_report

all: $(NAME)

test: s21_matrix_test.o s21_matrix.a $(OBJECTS)
	$(CC) $(OBJECTS) s21_matrix_test.o s21_matrix.a $(TEST_LIBS) -o test
	./test

s21_matrix.o: s21_matrix.c
	$(CC) $(CC_FLAGS) -c s21_matrix.c -g

s21_matrix_test.o: s21_matrix_test.c	
	$(CC) $(CC_FLAGS) -c  s21_matrix_test.c

gcov_report: s21_matrix.a 
	$(CC) $(CC_FLAGS) --coverage s21_matrix_test.c s21_matrix.c  s21_matrix.a $(TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

check: s21_matrix.a
	cppcheck *.h *.c
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	$(CC) s21_matrix_test.c s21_matrix.a -lcheck
	$(CC) $(CC_FLAGS) -c s21_matrix_test.c -o test.o
	$(CC) test.o s21_matrix.a $(TEST_LIBS) -o test
	CK_FORK=no leaks --atExit -- ./test

s21_matrix.a: s21_matrix.o
	$(CC) -c $(SOURSES)
	ar rcs s21_matrix.a $(OBJECTS)

clean:
	rm -rf *.o test s21_matrix.a s21_matrix_test.gcov s21_matrix.gcov s21_matrix_test.gc* s21_matrix.gc* report gcov_report.info CPPLINT.cfg a.out gcov_test* main

lo:
	for i in `seq 100 $(OP)`;	do ./test; done;

vg: s21_matrix.a
	CK_FORK=no valgrind --tool=memcheck ./test
	 
lik: s21_matrix.a
	CK_FORK=no leaks -atExit -- ./test

install lcov:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov