#include <iostream>
#include "Utils.hpp"
#define buck_size 2
#define hash_size 1024
using namespace std;


//------------------------------Cell functions------------------------------//
Cell::Cell(){
	//trans_id=-1;
	//offset_del=-1;
	//offset_ins=-1;
	//cout<<"A cell has just been created\n"<<endl;
}

Cell::~Cell(){
	//cout<<"A cell has just been destroyed\n"<<endl;	
}

uint64_t Cell::get_trans_id(){
	return trans_id;
}
long long int Cell::get_offset_del(){
	return offset_del;
}
long long int Cell::get_offset_ins(){
	return offset_ins;
}

void Cell::set_trans_id(uint64_t id){
	trans_id=id;
}
void Cell::set_offset_del(long long int del){
	offset_del=del;
}
void Cell::set_offset_ins(long long int ins){
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

long int Bucket::get_current(){
	return current;
}

Cell* Bucket::get_cells(){
	return cells;
}

void Bucket::print_Bucket(){
	long int i;
	cout<<"local depth         : "<<local<<endl;
	cout<<"size of range array : "<<size<<endl;
	cout<<"currently filled    : "<<current<<endl;
	for(i=0;i<current;i++)
		cells[i].print_Cell();
	cout<<endl;
}

void Bucket::printData(){
	long int i;
	cout<<"local depth         : "<<local<<endl;
	cout<<"size of range array : "<<size<<endl;
	cout<<"currently filled    : "<<current<<endl;
	for(i=0;i<current;i++)
		cells[i].print_Cell();
	cout<<endl;
}

int Bucket::insert_Bucket(uint64_t trid, long long int del, long long int ins){
	if(current==size)
		expand_Bucket();				
	cells[current].set_trans_id(trid);
	cells[current].set_offset_del(del);
	cells[current].set_offset_ins(ins);
	current++;
	return 0;
}

void Bucket::expand_Bucket(){				//BARELI DIXWS PATO
	long int i;
	uint64_t id;
	long long int del, ins;
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
	//key=-1;
	key = 0;
	b_ptr=NULL;
	//cout<<"A table cell has just been created!\n";
}

Table_Cell::~Table_Cell(){
	if(b_ptr!=NULL)
		delete(b_ptr);
	//cout<<"A table cell has just been destroyed!\n";
}

uint64_t Table_Cell::get_key(){
	return key;
}

Bucket * Table_Cell::get_Bucket(){
	return b_ptr;
}
				
void Table_Cell::set_key(uint64_t k){
	key=k;
}
		
void Table_Cell::set_Bucket(Bucket * buck){	
	b_ptr=buck;
}

void Table_Cell::print_Table_Cell(uint64_t myhs){
	if(b_ptr != NULL){
		cout << "My Hash is:" << myhs << endl;
		cout << "My key is :" << key << endl;
		cout << "I'm pointing at :" << b_ptr << endl;
		cout << "With data:\n" << endl;
		b_ptr->print_Bucket();
	}
}
//------------------------------Hashtable functions------------------------------//

Hashtable::Hashtable(){
	size = hash_size;
	global = 10;
	hash = 1024;
	table = new Table_Cell[size];
	//cout<<"A hashtable has just been created!\n";	
}
uint64_t Hashtable::hash_function(uint64_t key){
	return key%hash;
}
/*Hashtable::~Hashtable(){
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
*/
Hashtable::~Hashtable(){
	uint64_t i;
	for(i=0;i<size;i++){
		table[i].set_Bucket(NULL);
	}
	delete[] table;

	//cout<<"A hashtable has just been destroyed!\n";
}

int Hashtable::insertHashRecord(uint64_t pk, uint64_t tr_id, long long int del, long long int ins, Lista<Bucket> * lista){
	//cout<<"INSERTING..."<<endl;
	uint64_t res;
	res = hash_function(pk);					//position of pk%hash
	if(table[res].get_Bucket()==NULL){				//case NULL		
		table[res].set_key(pk);					//set pk 
		Bucket* buck=new Bucket();				//create bucket
		lista->push(buck);					//push to the list
		buck->insert_Bucket(tr_id,del,ins);			//insert data
		buck->set_local(global);				//set the depth
		table[res].set_Bucket(buck);				//set buck
		return 0;
	}
	else{							//case not NULL
		if(table[res].get_key()==pk){			//subcase same key 
			Bucket* buck;
			buck=table[res].get_Bucket();		//get buck
			buck->insert_Bucket(tr_id,del,ins);	//insert data
			return 0;	
		}
		else{						//subcase different key
			int templ;
			uint64_t tempk;
			uint64_t tempres,newres;
			Bucket * tempb;
			Bucket * newbuck;
			tempb=table[res].get_Bucket();		//get prev bucket
			tempk=table[res].get_key();		//get prev key
			templ=tempb->get_local();		//get local depth
			tempres=hash_function(tempk);		//get position of the prev key
			newres=hash_function(pk);		//get position of the new key where it should go
			while(tempres==newres){			//if same
				double_hash();
				tempres=hash_function(tempk);	//get again
				newres=hash_function(pk);	
			}					//until they re not same
				
			newbuck=new Bucket();
			newbuck->set_local(global);
			newbuck->insert_Bucket(tr_id,del,ins);	
			lista->push(newbuck);
			table[newres].set_key(pk);		//newres is the needed position
			table[newres].set_Bucket(newbuck);
				
		}	
	}
}

void Hashtable::double_hash(){
	//cout<<"DOUBLE..."<<endl;

	uint64_t i,tempk;
	Bucket * tempb;
	Table_Cell * table2;
	table2 = new Table_Cell[size*2];
	global++;
	hash = hash*2;
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
	table = table2;
	size = size*2;	
}


void Hashtable::printHash(){
	uint64_t i;
	for(i=0;i<size;i++){
		//cout<<"My hash is : "<<i<<endl;
		table[i].print_Table_Cell(i);
	}
}

long long int Hashtable::lastins(uint64_t pk){
	uint64_t res;
	long long int offins;
	long int i, counter;
	Bucket * buck;
	Cell* cells;
	
	res=hash_function(pk);
	if(table[res].get_Bucket() == NULL)
		return -1;
	if(table[res].get_key() != pk)
		return -1;
	buck=table[res].get_Bucket();

	cells=buck->get_cells();
	counter=buck->get_current();
	for(i=counter-1;i>=0;i--){
		offins=cells[i].get_offset_ins();
		if(offins!=-1)
			return offins;
	}
	return -1;
}

int Hashtable::currentdel(uint64_t pk){
	uint64_t res;
	long long int offdel;
	long int i, counter;
	Bucket * buck;
	Cell* cells;
	
	res = hash_function(pk);
	if(table[res].get_Bucket() == NULL)
		return 0;
	if(table[res].get_key() != pk)
		return 0;
	buck = table[res].get_Bucket();

	cells = buck->get_cells();
	counter = buck->get_current()-1;
	offdel = cells[counter].get_offset_del();
	if(offdel!=-1)
		return 0;
	return -1;
}

int Hashtable::currentins(uint64_t pk){
	uint64_t res;
	long long int offdel;
	long long int offins;
	long int i, counter;
	Bucket * buck;
	Cell* cells;
	
	res=hash_function(pk);
	if(table[res].get_Bucket() == NULL)
		return -1;
	if(table[res].get_key() != pk)
		return -1;
	
	buck=table[res].get_Bucket();

	cells=buck->get_cells();
	counter=buck->get_current();
	offdel=cells[counter].get_offset_del();
	offins=cells[counter].get_offset_ins();
	if(offins!=-1)
		return 0;
	return -1;
}


Lista<JournalRecord> * Hashtable::getHashJR(Journal * jour, long long int start, long long int end, uint64_t pk){
    Lista<JournalRecord> * lista = new Lista<JournalRecord>;
    JournalRecord * temp;
    uint64_t pos;
    long int left=0;
    long int right;
    Cell * cellarray;
    long int curr;
    long int ptr=-1;
    Bucket * buck;
    pos=hash_function(pk);
    if((buck=table[pos].get_Bucket())!=NULL){

        cellarray=buck->get_cells();
        curr=buck->get_current();
        right=curr-1;

        while(left<=right){
            long int middle = (left + right) / 2;
            if ((cellarray[middle].get_trans_id() >= start)&&(cellarray[middle].get_trans_id()<= end)){
                //cout<<"if"<<endl;
                ptr=middle;
                break;
       		}
            else if (cellarray[middle].get_trans_id()>end){
                //cout<<"elif"<<endl;
                  right = middle - 1;
        	}
            else{
                //cout<<"else"<<endl;
                 left = middle + 1;
        	}
        }

        if(ptr!=-1){
            long long int del;
            long long int ins;
            
            if((del=cellarray[ptr].get_offset_del())!=-1){
            	temp = jour->getFromOffset(del);
            	if(temp->getdirty()!=1)
					lista->push(temp);
            }
            if((ins=cellarray[ptr].get_offset_ins())!=-1){
				temp = jour->getFromOffset(ins);
            	if(temp->getdirty()!=1)
					lista->push(temp);
			}

            left=ptr-1;
            right=ptr+1;
            while(left>=0){
                if(cellarray[left].get_trans_id()>= start){
                    if((del=cellarray[left].get_offset_del())!=-1){
                            temp = jour->getFromOffset(del);
                        	if(temp->getdirty()!=1)
								lista->push(temp);
                    }
                    if((ins=cellarray[left].get_offset_ins())!=-1){
                    	temp = jour->getFromOffset(ins);
                    	if(temp->getdirty()!=1)
							lista->push(temp);
                    }        
                }
                else
                    break;
                left--;
            }
            while(right<curr){
                if(cellarray[right].get_trans_id()<= end){
                    if((del=cellarray[right].get_offset_del())!=-1){
						temp = jour->getFromOffset(del);
                    	if(temp->getdirty()!=1)
							lista->push(temp);  
                    }
                    if((ins=cellarray[right].get_offset_ins())!=-1){
						temp = jour->getFromOffset(ins);
                    	if(temp->getdirty()!=1)
							lista->push(temp);
					}        
                }
                else
                    break;
                right++;
            }
        }
    }
    return lista;


}
