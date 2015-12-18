#include <iostream>
#include "Utils.hpp"

//------------------------------------------------VALIDATIONS------------------------------------------------//

VQueries::VQueries(){
	//obsolete for now
	validationId = 0;
	from = 0;
	to = 0;
	queryCount = 0;
	queries = NULL;
}
VQueries::VQueries(uint64_t val, uint64_t f, uint64_t t, uint32_t qc){
	validationId = val;
	from = f;
	to = t;
	queryCount = qc;
	queries = new Query*[qc];		
}
VQueries::~VQueries(){
	uint32_t i;
	for(i=0;i<queryCount; i++){
		delete queries[i];
	}
	delete [] queries;
}

void VQueries::setVid(uint64_t v){ validationId = v;}
void VQueries::setFrom(uint64_t f){ from = f;}
void VQueries::setTo(uint64_t t){ to = t;}
void VQueries::setQueryCount(uint32_t qc){ queryCount = qc;}
void VQueries::setQuery(Query * q, uint32_t offset){ queries[offset] = q;}

uint64_t VQueries::getVid(){ return validationId;}
uint64_t VQueries::getFrom(){ return from;}
uint64_t VQueries::getTo(){ return to;}
uint32_t VQueries::getQueryCount(){ return queryCount;}
Query * VQueries::getQuery(uint32_t offset){ return queries[offset];}


//---------------------------------------------------------------------------

Column::Column(){
	//obsolete for now
	col = 0;
	op = Equal;
	value = 0;
}
Column::Column(uint32_t c, Op_t o, uint64_t v){
	col = c;
	op = o;
	value = v;
}

Column::~Column(){}

void Column::setCol(uint32_t c){ col = c;}
void Column::setOp(Op_t o){ op =  o;}
void Column::setValue(uint64_t v){ value = v;}
uint32_t Column::getCol(){ return col;}
Op_t Column::getOp(){ return op;}
uint64_t Column::getVal(){ return value;}


//---------------------------------------------------------------------------

Query::Query(){
	//obsolete for now
	relationId = 0;
	columnCount = 0;
	columns = NULL;
}

Query::Query(uint32_t rid, uint32_t cc){
	relationId = rid;
	columnCount = cc;
	columns = new Column * [cc];
}

Query::~Query(){
	uint32_t i;
	for(i=0;i<columnCount; i++){
		delete columns[i];
	}
	delete [] columns;
}

void Query::setRelId(uint32_t r){ relationId = r;}
void Query::setColCount(uint32_t cc){ columnCount = cc;}
void Query::setColumn(Column * c, uint32_t offset){ columns[offset] = c; }

uint32_t Query::getRelId(){ return relationId;}
uint32_t Query::getColCount(){ return columnCount;}
Column * Query::getColumn(uint32_t offset){ return columns[offset];}
