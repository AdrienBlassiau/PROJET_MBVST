#----------------------------------------------------------------------
# Copyright (c) 2019-2020, Adrien BLASSIAU

# Permission to use, copy, modify, and/or distribute this software
# for any purpose with or without fee is hereby granted, provided
# that the above copyright notice and this permission notice appear
# in all copies.

# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
# WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
# AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
# CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
# CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#----------------------------------------------------------------------


CC=g++ -Wall -Wextra -O2 -lboost_system -lboost_date_time -lboost_thread -lm -lglpk

all : main

main : main.o graph.o tools.o heuristic.o random_graph.o lp.o
	cd obj/ && $(CC) $^ -o ../bin/$@ -lboost_system -lboost_date_time -lboost_thread -lm -lglpk

test : main_test.o graph.o random_graph.o tools.o heuristic.o test_unit.o
	cd obj/ && $(CC) $^ -o ../bin/$@ -lboost_system -lboost_date_time -lboost_thread -lm -lcunit

main.o : src/main.c
	$(CC) -c $< -o obj/$@

main_test.o : test/main_test.c
	$(CC) -c $< -o obj/$@

graph.o : src/graph.c
	$(CC) -c $< -o obj/$@

random_graph.o : src/random_graph.c
	$(CC) -c $< -o obj/$@

tools.o : src/tools.c
	$(CC) -c $< -o obj/$@

heuristic.o : src/heuristic.c
	$(CC) -c $< -o obj/$@

lp.o : src/lp.c
	$(CC) -c $< -o obj/$@

test_unit.o : test/test_unit.c src/include.h
	$(CC) -c $< -o obj/$@

doxygen : doc/Doxyfile
	cd doc && doxygen ../$<

.PHONY: clean
clean :
	rm -f obj/*
	rm -rf doc/html/*
	rm -rf doc/latex/*
	rm -rf bin/*
