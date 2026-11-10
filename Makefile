CXX ?= g++
CXXFLAGS ?= -Wall -std=c++17 -O2

all: a4 a5

a4: a4-big-integer-addition/main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

a5: a5-rpn-to-infix/main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

test: all
	@check() { out=$$(printf "$$2" | ./$$1); [ "$$out" = "$$3" ] && echo "PASS $$1 -> $$3" || { echo "FAIL $$1: got $$out, want $$3"; exit 1; }; }; \
	check a4 '535953791669899051588630937807\n40058549908817013181945150931\n' 576012341578716064770576088738; \
	check a4 '999\n1\n' 1000; \
	check a4 '0\n0\n' 0; \
	check a5 '10/3+\n' '((1/0)+3)'; \
	check a5 '123*4-+\n' '(1+((2*3)-4))'

clean:
	$(RM) a4 a5

.PHONY: all test clean
