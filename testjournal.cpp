#include<iostream>
#include<cstdlib>
#include<time.h>
#include"journal.h"

using namespace std;

int main(void){
	int i,j;
	int * array; 
	Journal jour;
	srand(time(NULL));
	for(j=0;j<13;j++){
		array=new int[4];
		for(i=0;i<4;i++){
			array[i]=rand()%4;
		}
		for(i=0;i<4;i++){
			cout<<array[i]<<"    ";		
		}
		cout<<endl;
		JournalRecord* rel=new JournalRecord(0,array,4);
		delete[] array;
		//rel.printRecord();
	
		jour.insertJournalRecord(rel);
	}
	jour.printJournal();
	return 0;
}
