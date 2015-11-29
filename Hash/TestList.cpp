#include<iostream>
#include"Hash.hpp"

using namespace std;


int main(void){
	Bucket * ftr1=new Bucket();
	Bucket * ftr2=new Bucket();
	Bucket * ftr3=new Bucket();
	Bucket * ftr4=new Bucket();
	Bucket * ftr5=new Bucket();
	Bucket * ftr6=new Bucket();

	List * lista;
	Node * nd;
	lista = new List;
	lista->push(ftr1);
	lista->push(ftr2);
	lista->push(ftr3);
	lista->push(ftr4);
	lista->push(ftr5);
	lista->push(ftr6);

lista->print_List();


	delete lista;	
	
return 0;
}
