#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <iostream>

#include "Modes.hpp"
#include "Journal.hpp"
#include "Hash.hpp"


using namespace std;

static void processDefineSchema(DefineSchema_t *s){
	int i;
	printf("DefineSchema %d |", s->relationCount);

	for(i = 0; i < s->relationCount; i++) {
		printf(" %d ",s->columnCounts[i]);
	}

	cout<< endl;
}

static void processTransaction(Transaction_t *t, Journal **j_array, Hashtable **h_array, List **l_array){
	int i,j,k;
	const char* reader = t->operations;
	int rel_colcount;
	JournalRecord * rec;
	uint64_t* temparray;
	uint64_t tempkey;
	long long int pos_h, pos_j;

	cout << "Transaction "<< t->transactionId << " (" << t->deleteCount << ", " << t->insertCount <<") |";

	for(i=0; i < t->deleteCount; i++) {
		const TransactionOperationDelete_t* o = (TransactionOperationDelete_t*)reader;
		cout<< "opdel rid " << o->relationId << " #rows " << o->rowCount << " ";

		for(j=0; j< o->rowCount; j++){

			tempkey = o->keys[j];
			pos_h = h_array[o->relationId]->lastins(tempkey);

			if (pos_h != -1){
				JournalRecord * rec2 = j_array[o->relationId]->getFromOffset(pos_h);
				rec = new JournalRecord();
				rec->setCopy(rec2->getRecsize(), rec2->getRecord());
				rec->setTransactionID(t->transactionId);
				pos_j = j_array[o->relationId]->insertJournalRecord(rec);
				h_array[o->relationId]->insertHashRecord(rec->getPrimaryKey(), rec->getTransactionID(), pos_j-1, -1, l_array[o->relationId]);

			}
		}
		
		reader += 2*sizeof(uint32_t) + (sizeof(uint64_t)*o->rowCount);
	}
	cout << " \t| ";

	for(i=0; i < t->insertCount; i++) {
		const TransactionOperationInsert_t* o = (TransactionOperationInsert_t*)reader;
		cout<< "opins rid " << o->relationId << " #rows " << o->rowCount << " |";
		rel_colcount = j_array[o->relationId]->getColnum();
		temparray = new uint64_t[rel_colcount];

		for(j=0; j< o->rowCount; j++){

			for(k=0; k<rel_colcount; k++){
				temparray[k] = o->values[j*rel_colcount + k];
			}

			rec = new JournalRecord(t->transactionId, temparray, rel_colcount);
			pos_j = j_array[o->relationId]->insertJournalRecord(rec);
			h_array[o->relationId]->insertHashRecord(rec->getPrimaryKey(), rec->getTransactionID(), -1, pos_j-1, l_array[o->relationId]);


		}
		reader += 2*sizeof(uint32_t) + (sizeof(uint64_t)*o->rowCount*rel_colcount);
		delete [] temparray;
	}
	cout << endl;
  
}
static void processValidationQueries(ValidationQueries_t *v){
	cout << "ValidationQueries " << v->validationId << " [" <<v->from << ", "<< v->to << "] "<<v->queryCount << endl;
	const char* reader = v->queries;
	int i, j;

	for (i=0; i< v->queryCount; i++){
		const Query_t* q = (Query_t*)reader;
		cout << "\t" << q->relationId<< " ";

		for (j=0; j< q->columnCount; j++){
			cout<< "(C"<< q->columns[j].column <<" "<< q->columns[j].op <<" "<< q->columns[j].value <<") ";
		}
		reader += 2*sizeof(uint32_t) + (sizeof(Column_t)*q->columnCount);

		cout<<endl;

	}
}

static void processFlush(Flush_t *fl){
	cout << "Flush " << fl->validationId << endl;
}

static void processForget(Forget_t *fo){
	cout << "Forget " << fo->transactionId << endl;
}