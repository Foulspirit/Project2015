#include <iostream>
#include "Hash.hpp"
#define buck_size 2
#define hash_size 2
using namespace std;


//------------------------------Cell functions------------------------------//
Cell::Cell(){
	trans_id=-1;
	offset_del=-1;
	offset_ins=-1;
	//cout<<"A cell has just been created\n"<<endl;
}

Cell::~Cell(){
	//cout<<"A cell has just been destroyed\n"<<endl;	
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
	cout<<"trid : "<<trans_id<<"\n";
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


//------------------------------Bucket functions------------------------------//
Bucket::Bucket(){
	int i;
	cells=new Cell[buck_size];
	local=1;
	size=buck_size;
	current=0;
	//cout<<"A bucket has just been created\n"<<endl;
}

Bucket::~Bucket(){
	delete[] cells;
	//cout<<"A bucket has just been destroyed\n"<<endl;
}

int Bucket::get_local(){
	return local;
}

void Bucket::set_local(int lcl){
	local=lcl;
}

int Bucket::get_current(){
	return current;
}

Cell* Bucket::get_cells(){
	return cells;
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
	cells[current].set_offset_ins(ins);
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

//------------------------------Table Cell functions------------------------------//
Table_Cell::Table_Cell(){
	key=-1;
	b_ptr=NULL;
	//cout<<"A table cell has just been created!\n";
}

Table_Cell::~Table_Cell(){
	if(b_ptr!=NULL)
		delete(b_ptr);
	//cout<<"A table cell has just been destroyed!\n";
}

int Table_Cell::get_key(){
	return key;
}

Bucket * Table_Cell::get_Bucket(){
	return b_ptr;
}
				
void Table_Cell::set_key(int k){
	key=k;
}
		
void Table_Cell::set_Bucket(Bucket * buck){	
	b_ptr=buck;
}

void Table_Cell::print_Table_Cell(){
	if(key!=-1){
		cout<<"My key is :"<<key<<endl;
		cout<<"I'm pointing at :"<<b_ptr<<endl;
		cout<<"With data:\n"<<endl;
		b_ptr->print_Bucket();
	}
}
//------------------------------Hashtable functions------------------------------//

Hashtable::Hashtable(){
	size=hash_size;
	global=1;
	hash=2;
	table=new Table_Cell[size];
	//cout<<"A hashtable has just been created!\n";	
}
int Hashtable::hash_function(int key){
	return key%hash;
}
Hashtable::~Hashtable(){
	int i,j;
	Bucket * tempb;
	for(i=0;i<size;i++){
		tempb=table[i].get_Bucket();
		for(j=i+1;j<size;j++){
			if(table[j].get_Bucket()==tempb)
				table[j].set_Bucket(NULL);
		}
		//delete table[i];
	}
	delete[] table;
	cout<<"A hashtable has just been destroyed!\n";
}

int Hashtable::insertHashRecord(int pk,int tr_id,int del,int ins){
	//cout<<"INSERTING..."<<endl;
	int res;
	res=hash_function(pk);
	if(table[res].get_key()==-1){				//periptwsh NULL		
		table[res].set_key(pk);
		Bucket* buck=new Bucket();
		buck->insert_Bucket(tr_id,del,ins);
		buck->set_local(global);
		table[res].set_Bucket(buck);
		return 0;
	}
	else{							//periptwsh oxi NULL
		if(table[res].get_key()==pk){			//upoperiptwsh idio key 
			Bucket* buck;
			buck=table[res].get_Bucket();
			buck->insert_Bucket(tr_id,del,ins);	
			return 0;	
		}
		else{						//upoperiptwsh diaforetiko key
			int templ,newl;
			int tempk;
			int tempres=-1,newres;
			Bucket * tempb;
			Bucket * newbuck;
			tempb=table[res].get_Bucket();
			templ=tempb->get_local();
			if(global==templ){
				do{
					double_hash();
					tempk=table[res].get_key();
					tempres=hash_function(tempk);
					table[tempres].set_key(tempk);
					table[tempres].set_Bucket(tempb);
					templ=tempb->get_local();
					tempb->set_local(templ+1);
					newres=hash_function(pk);
				}while(tempres==newres);
				tempres=newres;
			}
			if(tempres==-1)
				tempres=hash_function(pk);
			newbuck=new Bucket();
			table[tempres].set_key(pk);
			table[tempres].set_Bucket(newbuck);
			newbuck->set_local(global);
			newbuck->insert_Bucket(tr_id,del,ins);		
		}	
	}
}

void Hashtable::double_hash(){\
	//cout<<"DOUBLE..."<<endl;

	int i,tempk;
	Bucket * tempb;
	Table_Cell * table2;
	table2=new Table_Cell[size*2];
	global++;
	hash=2*hash;
	for(i=0;i<size;i++){
		tempk=table[i].get_key();
		tempb=table[i].get_Bucket();
		table2[i].set_key(tempk);
		table2[i+size].set_key(tempk);
		table2[i].set_Bucket(tempb);
		table2[i+size].set_Bucket(tempb);
		table[i].set_Bucket(NULL);	
	}
	delete[] table;
	table=table2;
	size=size*2;	
}


void Hashtable::printHash(){
	int i;
	for(i=0;i<size;i++){
		cout<<"My hash is : "<<i<<endl;
		table[i].print_Table_Cell();
	}
}

int Hashtable::lastins(int pk){
	int res,offins,i,counter;
	Bucket * buck;
	Cell* cells;
	
	res=hash_function(pk);
	if(table[res].get_key() != pk)
		return -1;
	buck=table[res].get_Bucket();

	cells=buck->get_cells();
	counter=buck->get_current();
	for(i=counter-1;i<=0;i--){
		offins=cells[i].get_offset_ins();
		if(offins!=-1)
			return offins;
	}
}
