all: compile

compile:
	g++ -o ask Main.cpp Journal.cpp Hash.cpp VQueries.cpp -g3
	g++ -o compare Compare.cpp

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
	./ask < medium.bin

run3totxt:
	./ask < medium.bin > txtme.txt

c1:
	./compare basic.out.bin

c2:
	./compare small.out.bin

c3:	
	./compare medium.out.bin
