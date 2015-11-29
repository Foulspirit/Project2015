#include<iostream>
#include"Hash.hpp"

using namespace std;


int main(void){
	int pk1=0,tr1=1,offdel1=2,offins1=-1;
	int pk2=1,tr2=3,offdel2=-1,offins2=3;
	int pk3=2,tr3=6,offdel3=5,offins3=-1;
	int pk4=2,tr4=3,offdel4=2,offins4=-1;
	int pk5=4,tr5=1,offdel5=-1,offins5=4;
	Hashtable hash;
	List * lista =new List();
	hash.insertHashRecord(pk1,tr1,offdel1,offins1,lista);
	hash.insertHashRecord(pk2,tr2,offdel2,offins2,lista);
	hash.insertHashRecord(pk3,tr3,offdel3,offins3,lista);
	hash.insertHashRecord(pk4,tr4,offdel4,offins4,lista);
	hash.insertHashRecord(pk5,tr5,offdel5,offins5,lista);
	cout<<"Last ins MADA FAKA : "<<hash.lastins(1)<<endl;
	hash.printHash();
	lista->print_List();
	delete lista;
return 0;
}
