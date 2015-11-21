all: compile

compile:
	g++ -o ask TestParser.cpp Parser.cpp -g3

clean:
	rm -f ask

run1:
	./ask < basic.bin

run2:
	./ask < small.bin

run3:
	./ask < try.bin