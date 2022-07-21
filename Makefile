CC = gcc
GCC = $(CC) -Wall -Wextra -Werror
OBJECT = s21_matrix.o
SCORE = s21_matrix.c
TEST_LIBS = -lcheck

all: clean s21_matrix.a

test: s21_matrix.a s21_matrix_test.o
	$(CC) s21_matrix_test.o s21_matrix.a $(TEST_LIBS) -o test
	./test

s21_matrix_test.o:
	$(GCC) s21_matrix_test.c -c

s21_matrix.a: $(OBJECT)
	ar -rcs s21_matrix.a $(OBJECT)


$(OBJECT): $(SCORE)
	$(GCC) $(SCORE) -c

s21_%.h: *.c
	sed -i '/generated/,$$d' $@
	echo "//  generated_by_makefile" >> $@
	cat s21_*.c | grep -E "^\w+.*[)] [{]" | grep -v "main(" | sed 's/ {/;/' >> $@

clean:
	rm -rf *.o
	rm -rf test
	rm -rf a.*

gcov_report: s21_matrix.a
	$(GCC)  --coverage s21_matrix_test.c s21_matrix.c  s21_matrix.a $(TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html

debug : 
	$(GCC) main.c s21_matrix_reduction.c -g
#lo:
#	for i in `seq 100 $(OP)`;	do ./test; done;

vg: s21_matrix.a
    	CK_FORK=no valgrind --tool=memcheck ./test

lik: s21_matrix.a
	CK_FORK=no leaks -atExit -- ./test

check: s21_matrix.a
	cppcheck *.h *.c
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	$(CC) s21_matrix_test.c s21_matrix.a -lcheck
	$(CC) $(CC_FLAGS) -c s21_matrix_test.c -o test.o
	$(CC) test.o s21_matrix.a $(TEST_LIBS) -o test
	CK_FORK=no leaks --atExit -- ./test

install lcov:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov