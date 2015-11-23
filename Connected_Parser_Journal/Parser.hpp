#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <iostream>

#include "Modes.hpp"
#include "Journal.hpp"


using namespace std;

static void processDefineSchema(DefineSchema_t *s){
	int i;
	printf("DefineSchema %d |", s->relationCount);

	for(i = 0; i < s->relationCount; i++) {
		printf(" %d ",s->columnCounts[i]);
	}

	cout<< endl;
}

static void processTransaction(Transaction_t *t, Journal **j_array){
	int i,j,k;
	const char* reader = t->operations;
	int rel_colcount;
	JournalRecord * rec;
	int* temparray;
	int tempkey;

	cout << "Transaction "<< t->transactionId << " (" << t->deleteCount << ", " << t->insertCount <<") |";

	for(i=0; i < t->deleteCount; i++) {
		const TransactionOperationDelete_t* o = (TransactionOperationDelete_t*)reader;
		cout<< "opdel rid " << o->relationId << " #rows " << o->rowCount << " ";

		for(j=0; j< o->rowCount; j++){

			tempkey = o->keys[j];
			JournalRecord * rec2 = j_array[o->relationId]->findLastEntry(tempkey);
			rec = new JournalRecord();
			rec->setCopy(rec2->getRecsize(), rec2->getRecord());
			rec->setTransactionID(t->transactionId);
			j_array[o->relationId]->insertJournalRecord(rec);

		}
		
		reader += 2*sizeof(uint32_t) + (sizeof(uint64_t)*o->rowCount);
	}
	cout << " \t| ";

	for(i=0; i < t->insertCount; i++) {
		const TransactionOperationInsert_t* o = (TransactionOperationInsert_t*)reader;
		cout<< "opins rid " << o->relationId << " #rows " << o->rowCount << " |";
		rel_colcount = j_array[o->relationId]->getColnum();
		temparray = new int[rel_colcount];

		for(j=0; j< o->rowCount; j++){

			for(k=0; k<rel_colcount; k++){
				temparray[k] = o->values[j*rel_colcount + k];
			}

			rec = new JournalRecord(t->transactionId, temparray, rel_colcount);
			j_array[o->relationId]->insertJournalRecord(rec);

		}
		reader += 2*sizeof(uint32_t) + (sizeof(uint64_t)*o->rowCount*rel_colcount);
		delete temparray;
	}
	cout << endl;
  
}
static void processValidationQueries(ValidationQueries_t *v){
	cout << "ValidationQueries " << v->validationId << " [" <<v->from << ", "<< v->to << "] "<<v->queryCount << endl;
}

static void processFlush(Flush_t *fl){
	cout << "Flush " << fl->validationId << endl;
}

static void processForget(Forget_t *fo){
	cout << "Forget " << fo->transactionId << endl;
}