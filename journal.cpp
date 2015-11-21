#include<iostream>
#include"journal.h"
#define init_size 3
using namespace std;

JournalRecord::JournalRecord(int noRel,int * array,int size){
	int i;
	recsize=size+1;
	record=new int[recsize];
	record[0]=noRel;
	for(i=1;i<(size+1);i++)
		record[i]=array[i-1];
	cout<<"A JournalRecord has just been created!!\n"<<endl;
}

JournalRecord::~JournalRecord(){
	delete[] record;
	cout<<"A JournalRecord has just been destroyed!!\n"<<endl;
}

void JournalRecord::printRecord(){
	int i;
	for(i=0;i<recsize;i++)
		cout<<record[i]<<"     ";
	cout<<endl;
} 

Journal::Journal(){
	int i;
	maxsize=init_size;
	current=0;
	journal=new JournalRecord*[init_size];
	for(i=0;i<maxsize;i++)
		journal[i]=NULL;
	cout<<"A Journal has just been created!!\n"<<endl;
}

Journal::~Journal(){
	int i;
	for(i=0;i<current;i++)
		delete journal[i];
	delete[] journal;
	cout<<"A Journal has just been destroyed!!\n"<<endl;
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
	return 0;
}

int Journal::increaseJournal(){
	cout<<"The journal is increasing"<<endl;
	
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
	cout<<"the new max size is: "<<maxsize<<endl;
	cout<<"the current is: "<<current<<endl;
	return 0;
}











