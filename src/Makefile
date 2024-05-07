CC = gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11
LDFLAGS = -O2 -Wall -Wextra -Werror -std=c11
SOURCE = $(wildcard s21_*.c)
OBJECTS = $(patsubst %.c,%.o, ${SOURCE}) 
FILE_FOR_TEST = $(wildcard *tests.c)

UNAME:=$(shell uname -s)

ifeq ($(UNAME),Linux) 
	OPEN_OC = xdg-open
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif

ifeq ($(UNAME),Darwin) 
	OPEN_OC = open
	ADD_LIB = -lcheck
endif

GCOV = --coverage  
PATH := $(PATH):$(BREW)/bin 

all: clean s21_matrix.a test gcov_report style

s21_matrix.a: ${SOURCE}     
	${CC} $(CFLAGS) ${SOURCE} -lncurses   
	ar rcs $@ ${OBJECTS}	

test: clean ${SOURCE} 
	${CC} ${GCOV} ${SOURCE} ./${FILE_FOR_TEST} -o test $(ADD_LIB)
	./test

gcov_report: lcov test
	lcov -t "./gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	$(OPEN_OC) ./report/index.html

leaks: test
	CK_FORK=no leaks --atExit -- ./test

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./test
	valgrind -s --tool=memcheck --leak-check=yes ./test	

lcov:
ifeq ("", "$(shell PATH=$(PATH) which lcov)")
	$(error Need to install lcov)
endif

style:
	cp ../materials/linters/.clang-format .
	clang-format -style=Google -i *.c *.h
	clang-format -n *.c *.h
	rm -rf .clang-format

clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf s21_*.o
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf s21_*.a && rm -rf test-s21_*.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./gcov_report
	-rm -rf ./report/
	-rm -rf *.out

.PHONY: all clean check lcov test
