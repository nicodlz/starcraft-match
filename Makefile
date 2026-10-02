.PHONY: all analyze candidate match task status test check proof
all: candidate test
analyze:
	./tools/decomp analyze
candidate:
	./tools/decomp build-all
match:
	./tools/match function 0x004020B0
task:
	./tools/decomp task 0x004020B0
status:
	./tools/decomp status
test:
	python3 -m unittest discover -s tests -v
check:
	./tools/check-publication

proof:
	./tools/decomp verify-matches
