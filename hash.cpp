#include<iostream>
#include"hash.h"
#define buck_size 3
#define hash_size 2
using namespace std;


Bucket::Bucket(){
	int i;
	cells=new int[buck_size];
	local=1;
	for(i=0;i<buck_size;i++)
		cells[i]=-1;
	cout<<"A bucket has just been created\n"<<endl;
}

Bucket::~Bucket(){
	delete[] cells; 
	cout<<"A bucket has just been destroyed\n"<<endl;
}

int Bucket::getlocal(){
	return local;
}

void Bucket::print(){
	int i;
	for(i=0;i<buck_size;i++)
		cout<<cells[i]<<"         ";
	cout<<endl;
}

int Bucket::insertBucket(int offset){
	int i;
	for(i=0;i<buck_size;i++){
		if(cells[i]==-1){
			cells[i]=offset;
			break;
		}
	}
	if(i==bucksize){
		cout<<"Bucket is full!!!!\n";///split h double
		return 1;
	}
	return 0;
}


Hashtable::Hashtable(){
	table= new Bucket*[hash_size];
	global=1;
	int i;
	for(i=0;i<hash_size;i++)
		table[i]=NULL;




}
