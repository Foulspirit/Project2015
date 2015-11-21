#include<iostream>
#include"hash.h"
#define buck_size 1
#define hash_size 2
using namespace std;

Cell::Cell(){
	trans_id=-1;
	offset_del=-1;
	offset_ins=-1;
	cout<<"A cell has just been created\n"<<endl;
}

Cell::~Cell(){
	cout<<"A cell has just been destroyed\n"<<endl;	
}

int Cell::get_trans_id(){
	return trans_id;
}
int Cell::get_offset_del(){
	return offset_del;
}
int Cell::get_offset_ins(){
	return offset_ins;
}

void Cell::set_trans_id(int id){
	trans_id=id;
}
void Cell::set_offset_del(int del){
	offset_del=del;
}
void Cell::set_offset_ins(int ins){
	offset_ins=ins;
}

void Cell::print_Cell(){
	cout<<"id : "<<trans_id<<"\n";
	if(offset_del!=-1)
		cout<<"del: "<<offset_del<<"\n";
	else
		cout<<"del: "<<"\n";
	if(offset_ins!=-1)
		cout<<"ins: "<<offset_ins<<"\n";
	else
		cout<<"ins: "<<"\n";
	cout<<"----------"<<"\n";
}

Bucket::Bucket(){
	int i;
	cells=new Cell[buck_size];
	local=1;
	size=buck_size;
	current=0;
	cout<<"A bucket has just been created\n"<<endl;
}

Bucket::~Bucket(){
	delete[] cells; 
	cout<<"A bucket has just been destroyed\n"<<endl;
}

int Bucket::get_local(){
	return local;
}

void Bucket::print_Bucket(){
	int i;
	cout<<"local depth         : "<<local<<endl;
	cout<<"size of range array : "<<size<<endl;
	cout<<"currently filled    : "<<current<<endl;
	for(i=0;i<current;i++)
		cells[i].print_Cell();
	cout<<endl;
}

int Bucket::insert_Bucket(int trid,int del,int ins){
	if(current==size)
		expand_Bucket();				
	cells[current].set_trans_id(trid);
	cells[current].set_offset_del(del);
	cells[current].set_offset_del(ins);
	current++;
	return 0;
}

void Bucket::expand_Bucket(){				//BARELI DIXWS PATO
	int i,id,del,ins;
	Cell * cells2;
	cells2=new Cell[2*size];
	for(i=0;i<current;i++){
		id = cells[i].get_trans_id();
		del= cells[i].get_offset_del();
		ins= cells[i].get_offset_ins();
		cells2[i].set_trans_id(id);
		cells2[i].set_offset_del(del);
		cells2[i].set_offset_ins(ins);
	}
	delete[] cells;
	cells=cells2;
	size=size*2;
}
/*
Hashtable::Hashtable(){
	table= new Bucket*[hash_size];
	global=1;
	int i;
	for(i=0;i<hash_size;i++)
		table[i]=NULL;




}*/
