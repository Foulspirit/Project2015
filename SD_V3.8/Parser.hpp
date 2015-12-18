#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <iostream>

//#include "Modes.hpp"
#include "Utils.hpp"


using namespace std;

static void processDefineSchema(DefineSchema_t *s){
	int i;
	//printf("DefineSchema %d |", s->relationCount);

	for(i = 0; i < s->relationCount; i++) {
		//printf(" %d ",s->columnCounts[i]);
	}

	////cout<< endl;
}

static void processTransaction(Transaction_t *t, Journal **j_array, Hashtable **h_array, Lista<Bucket> **l_array, ofstream *debug){
	int i,j,k;
	const char* reader = t->operations;
	int rel_colcount;
	JournalRecord * rec;
	uint64_t* temparray;
	uint64_t tempkey;
	long long int pos_h, pos_j;

	////cout << "Transaction "<< t->transactionId << " (" << t->deleteCount << ", " << t->insertCount <<") |";

	for(i=0; i < t->deleteCount; i++) {
		const TransactionOperationDelete_t* o = (TransactionOperationDelete_t*)reader;
		////cout<< "opdel rid " << o->relationId << " #rows " << o->rowCount << " ";

		for(j=0; j< o->rowCount; j++){

			tempkey = o->keys[j];
			pos_h = h_array[o->relationId]->lastins(tempkey);

			if (pos_h != -1){
				JournalRecord * rec2 = j_array[o->relationId]->getFromOffset(pos_h);
				rec = new JournalRecord();
				rec->setCopy(rec2->getRecsize(), rec2->getRecord());
				rec->setTransactionID(t->transactionId);
				if(h_array[o->relationId]->currentdel(rec->getPrimaryKey())==0)
					rec->setdirty(1);
				pos_j = j_array[o->relationId]->insertJournalRecord(rec);
				if(rec->getdirty()!=1)
					h_array[o->relationId]->insertHashRecord(rec->getPrimaryKey(), rec->getTransactionID(), pos_j-1, -1, l_array[o->relationId]);
				
			}
		}
		
		reader += 2*sizeof(uint32_t) + (sizeof(uint64_t)*o->rowCount);
	}
	////cout << " \t| ";

	for(i=0; i < t->insertCount; i++) {
		const TransactionOperationInsert_t* o = (TransactionOperationInsert_t*)reader;
		////cout<< "opins rid " << o->relationId << " #rows " << o->rowCount << " |";
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
	////cout << endl;
  
}
static void processValidationQueries(ValidationQueries_t *v, Lista<VQueries> *v_array, ofstream *debug){
	////cout << "ValidationQueries " << v->validationId << " [" <<v->from << ", "<< v->to << "] "<<v->queryCount << endl;
	
	const char* reader = v->queries;
	int i, j;
	VQueries * vq = new VQueries(v->validationId, v->from, v->to, v->queryCount);
	//*debug << "ValidationQueries " << v->validationId << " [" <<v->from << ", "<< v->to << "] "<<v->queryCount << endl;

	for (i=0; i< v->queryCount; i++){

		const Query_t* q = (Query_t*)reader;
		Query * qq = new Query(q->relationId, q->columnCount);

		//*debug << "\t" << q->relationId;

		for (j=0; j< q->columnCount; j++){
			Column * cc = new Column(q->columns[j].column, q->columns[j].op, q->columns[j].value);
			qq->setColumn(cc, j);
			//*debug << " (C"<< q->columns[j].column <<" "<< q->columns[j].op <<" "<< q->columns[j].value <<")";
		}
		//if (q->columnCount==0)
			//*debug << "ValidationQueries " << v->validationId << " [" <<v->from << ", "<< v->to << "] "<<v->queryCount << endl;

		vq->setQuery(qq, i);

		reader += 2*sizeof(uint32_t) + (sizeof(Column_t)*q->columnCount);

		//*debug << endl;

	}

	v_array->push(vq);

}


static void processFlush(Flush_t *fl, Lista<VQueries> *v_array, Journal **j_array, Hashtable **h_array, ofstream *results, ofstream* debug){
	//cout << "Flush " << fl->validationId << endl;
	
	uint32_t i=0, j=0;

	VQueries* v;

	v = v_array->preview();
	if (v==NULL) return;
	
	while(v->getVid() <= fl->validationId){				//gia validations
		
		v = v_array->pop();
/*
		if(v->getVid()==19631){
			j_array[27]->printJournal();
			cout << endl<<endl << "-------------------------------------------"<<endl<<endl;
			j_array[26]->printJournal();

		}
*/

		bool answer = 0;

		Lista<JournalRecord> * lista = NULL;

		for (i=0; i< v->getQueryCount(); i++){					//gia queries

			Query * q = v->getQuery(i);
			Column * c;

			///////////////////////////// 
			///*
			for (j=0; j< q->getColCount(); j++){
				c =  q->getColumn(j);
				if((c->getCol() == 0)&&(c->getOp() == Equal)){
					lista = h_array[q->getRelId()]->getHashJR(j_array[q->getRelId()], v->getFrom(), v->getTo(), c->getVal());
					break;
				}
			}
			//*/
			/////////////////////////////////
			
			if(lista == NULL){
				lista = j_array[q->getRelId()]->getJournalJR(v->getFrom(), v->getTo());	
			}
			else if(lista->getCounter()==0){
				delete lista;
				lista = j_array[q->getRelId()]->getJournalJR(v->getFrom(), v->getTo());	
			}

			answer = 1; //OR MAYBE answer = 1|1 of course;

			for (j=0; j< q->getColCount(); j++){

				c = q->getColumn(j);

				uint64_t elemcount = lista->getCounter();
				uint64_t elemptr;

				uint32_t c1 = c->getCol();
				uint64_t value = c->getVal();
				Op_t op = c->getOp();

				JournalRecord * rec;

				for(elemptr=0; elemptr<elemcount; elemptr++){
					rec = lista->pop();
					if (rec==NULL) break;
					switch(op){
						case Equal:	
							if(rec->getSpecCol(c1+1)==value){
								lista->push(rec);
							}
							break;
						case NotEqual:
							if(rec->getSpecCol(c1+1)!=value){
								lista->push(rec);
							}
							break;
						case Less:
							if(rec->getSpecCol(c1+1)<value){
								lista->push(rec);
							}
							break;
						case LessOrEqual:
							if(rec->getSpecCol(c1+1)<=value){
								lista->push(rec);
							}
							break;
						case Greater:
							if(rec->getSpecCol(c1+1)>value){
								lista->push(rec);
							}
							break;
						case GreaterOrEqual:
							if(rec->getSpecCol(c1+1)>=value){
								lista->push(rec);
							}
							break;
						default: return;
					}
				}
				if(lista->getCounter() == 0){
					answer = 0; //OR MAYBE answer = 0|0  :P ;
					break;
				}

			}
			
			if (v->getQueryCount()>1){
				if(q->getColCount()==0)
					answer = 0;
			}

			if (answer == 1)
				break;
		}

		if (v->getQueryCount()==0)
			answer = 1;

		lista->popall();
		delete lista;

		*results << answer;

		delete v;
		v = v_array->preview();
		if (v==NULL) return;
		
	}
}

static void processForget(Forget_t *fo){
	////cout << "Forget " << fo->transactionId << endl;
}
