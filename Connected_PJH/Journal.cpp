#include <iostream>
#include "Journal.hpp"

#define init_size 3

using namespace std;

//------------------------------JournalRecord------------------------------//

JournalRecord::JournalRecord(int t_id, int * array,int size){
	int i;
	recsize=size+1;
	record=new int[recsize];
	record[0] = t_id;
	for(i=1;i<(size+1);i++)
		record[i]=array[i-1];
	//cout<<"A JournalRecord has just been created!!\n"<<endl;
}

JournalRecord::JournalRecord(){
	int i;
	recsize = 2;
	record = NULL;
	//cout<<"A JournalRecord EMPTY has just been created!!\n"<<endl;
}

JournalRecord::~JournalRecord(){
	delete [] record ;
	//cout<<"A JournalRecord has just been destroyed!!\n"<<endl;
}

void JournalRecord::printRecord(){
	int i;
	for(i=0;i<recsize;i++)
		cout<<record[i]<<"     ";
	cout<<endl;
} 

int JournalRecord::getPrimaryKey(){
	return record[1];
}

int JournalRecord::getTransactionID(){
	return record[0];
}

void JournalRecord::setTransactionID(int tid){
	record[0] = tid;
}

void JournalRecord::setRecord(int *eggr){
	int i;
	record=new int[recsize];
	for(i=0; i<recsize; i++){
		record[i] = eggr[i];
	}
}
void JournalRecord::setRecsize(int size){
	recsize = size;
}

void JournalRecord::setCopy(int size, int *eggr){
	recsize = size;
	int i;
	record=new int[recsize];
	for(i=0; i<recsize; i++){
		record[i] = eggr[i];
	}	
}

int JournalRecord::getRecsize(){
	return recsize;
}

int * JournalRecord::getRecord(){
	return record;
}



//------------------------------Journal------------------------------//

Journal::Journal(){
	int i;
	maxsize = init_size;
	colnum = 0;
	current = 0;
	journal = new JournalRecord*[init_size];
	for(i=0; i<maxsize; i++)
		journal[i]=NULL;
	//cout << "A Journal has just been created!!\n" << endl;
}

Journal::Journal(int col){
	int i;
	maxsize = init_size;
	colnum = col;
	current = 0;
	journal = new JournalRecord*[init_size];
	for(i=0; i<maxsize; i++)
		journal[i]=NULL;
	//cout << "A Journal has just been created with "<< colnum <<" columns!\n" << endl;
}

Journal::~Journal(){
	int i;
	for(i=0;i<current;i++)
		delete journal[i];
	delete[] journal;
	//cout<<"A Journal has just been destroyed!!\n"<<endl;
}

void Journal::printJournal(){
	int i=0;
	for(i=0;i<current;i++){
		journal[i]->printRecord();
		cout<<endl;			
	}
}

int Journal::insertJournalRecord(JournalRecord * jrec){
	int i;
	if(current==maxsize)
		i=increaseJournal();
	journal[current]=jrec;
	current++;
	return current;
}

int Journal::increaseJournal(){
	//cout<<"The journal is increasing"<<endl;
	
	JournalRecord ** journal2;
	int i;
	journal2=new JournalRecord*[maxsize*2];
	for(i=0;i<maxsize;i++)
		journal2[i]=journal[i];
	for(i=maxsize;i<maxsize*2;i++)
		journal2[i]=NULL;
	delete[] journal;
	journal=journal2;
	maxsize=maxsize*2;
	//cout<<"the new max size is: "<<maxsize<<endl;
	//cout<<"the current is: "<<current<<endl;
	return 0;
}

int Journal::getColnum(){
	return colnum;
}

JournalRecord * Journal::findLastEntry(int key){
	int cur = current-1;
	int temp;
	int i;
	int *array;
	JournalRecord * lala;

	while(cur>=0){
		temp = journal[cur]->getPrimaryKey();
		if (temp == key) {
			lala = journal[cur];
			return lala;
		}
		cur--;
	}

	return NULL;

}	

JournalRecord * Journal::getFromOffset(int offset){
	return journal[offset];

}
