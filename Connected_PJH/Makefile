all: compile

compile:
	g++ -o ask Main.cpp Journal.cpp Hash.cpp -g3

clean:
	rm -f ask

run1:
	./ask < basic.bin

run1totxt:
	./ask < basic.bin > txtbc.txt

run2:
	./ask < small.bin

run2totxt:
	./ask < small.bin > txtsm.txt

run3:
	./ask < try.bin