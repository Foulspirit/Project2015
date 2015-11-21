#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include "Modes.hpp"

using namespace std;

static uint32_t* schema = NULL;
static void processDefineSchema(DefineSchema_t *s){
	int i;
	printf("DefineSchema %d |", s->relationCount);
	if ( schema == NULL) free(schema);
	schema = new uint32_t(sizeof(uint32_t)*s->relationCount);

	for(i = 0; i < s->relationCount; i++) {
		printf(" %d ",s->columnCounts[i]);
		schema[i] = s->columnCounts[i];
	}
	cout<< endl;
}

static void processTransaction(Transaction_t *t){
	int i;
	const char* reader = t->operations;

	cout << "Transaction "<< t->transactionId << " (" << t->deleteCount << ", " << t->insertCount <<") |";

	for(i=0; i < t->deleteCount; i++) {
		const TransactionOperationDelete_t* o = (TransactionOperationDelete_t*)reader;
		cout<< "opdel rid " << o->relationId << " #rows " << o->rowCount << " ";
		reader+=sizeof(TransactionOperationDelete_t)+(sizeof(uint64_t)*o->rowCount);
	}
	cout << " \t| ";
	for(i=0; i < t->insertCount; i++) {
		const TransactionOperationInsert_t* o = (TransactionOperationInsert_t*)reader;
		cout<< "opins rid " << o->relationId << " #rows " << o->rowCount << " |";
		reader+=sizeof(TransactionOperationInsert_t)+(sizeof(uint64_t)*o->rowCount*schema[o->relationId]);
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

