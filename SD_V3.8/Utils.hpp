#include <stdint.h>
#include "Lista.hpp"
#include "Modes.hpp"


//------------------------------------------------JOURNAL------------------------------------------------//


class JournalRecord{
	uint64_t * record;
	int recsize;
	bool dirty;
	public:
		JournalRecord(uint64_t, uint64_t *, int);
		JournalRecord();

		~JournalRecord();
		void printData();
		uint64_t getPrimaryKey();
		uint64_t getTransactionID();
		uint64_t getSpecCol(uint32_t);
		bool getdirty();
		void setdirty(bool);
		void setTransactionID(uint64_t);
		void setRecord(uint64_t *);
		void setRecsize(int);
		void setCopy(int, uint64_t *);
		int getRecsize();
		uint64_t * getRecord();
};

class Journal{
	JournalRecord ** journal;
	int colnum;
	long long int maxsize;
	long long int current;	
	public:
		Journal();
		Journal(int);
		~Journal();
		void printJournal();
		long long int insertJournalRecord(JournalRecord*);
		int increaseJournal();	
		int getColnum();
		Lista<JournalRecord> * getJournalJR(uint64_t,uint64_t);	
		JournalRecord * findLastEntry(uint64_t);
		JournalRecord * getFromOffset(long long int);
};

//------------------------------------------------HASH------------------------------------------------//

class Cell{					//---NOTES-------------------//
		uint64_t trans_id;			//transaction id
		long long int offset_del;			//offset for deletion record
		long long int offset_ins;			//offset for insertion record
	public:
		Cell();				
		~Cell();
		uint64_t get_trans_id();
		long long int get_offset_del();
		long long int get_offset_ins();
		void set_trans_id(uint64_t);
		void set_offset_del(long long int);
		void set_offset_ins(long long int);	
		void print_Cell();
		
};

class Bucket{
		Cell* cells;			//array aka transaction range 2 offsets maximum 4 each id
		int local;			//local depth
		long int current;			//which cell to fill
		long int size;			//array size
	public:
		Bucket();
		~Bucket();
		void print_Bucket();		//prints local depth and current cells.
		void printData();		//prints local depth and current cells when on a list.
		int get_local();
		long int get_current();
		Cell* get_cells();	
		void set_local(int);
		void expand_Bucket();		//doubles the size of cells array
		int insert_Bucket(uint64_t, long long int, long long int);
			
};

class Table_Cell{	
		uint64_t key;			//pk of the record
		Bucket * b_ptr;			//ptr to the bucket
	public:
		Table_Cell();
		~Table_Cell();
		uint64_t get_key();
		Bucket * get_Bucket();
		void set_key(uint64_t);
		void set_Bucket(Bucket *);
		void print_Table_Cell(uint64_t);
};

class Hashtable{
		int global;
		Table_Cell * table;
		uint64_t hash;
		uint64_t size;
	public:
		Hashtable();
		~Hashtable();	
		int insertHashRecord(uint64_t, uint64_t, long long int, long long int, Lista<Bucket> *);
		uint64_t hash_function(uint64_t);
		long long int lastins(uint64_t);
		int currentdel(uint64_t);
		int currentins(uint64_t);
		void double_hash();
		void printHash();
		Lista<JournalRecord> * getHashJR(Journal* ,long long int, long long int, uint64_t);
};

//------------------------------------------------VALIDATIONS------------------------------------------------//

class Column {
	uint32_t col;
	Op_t op;
	uint64_t value;

public:
	Column();
	Column(uint32_t, Op_t, uint64_t);
	~Column();
	void setCol(uint32_t);
	void setOp(Op_t);
	void setValue(uint64_t);
	uint32_t getCol();
	Op_t getOp();
	uint64_t getVal();

};

//---------------------------------------------------------------------------
class Query {
   uint32_t relationId;
   uint32_t columnCount;
   Column ** columns;

public:
	Query();
	Query(uint32_t, uint32_t);
	~Query();
	void setRelId(uint32_t);
	void setColCount(uint32_t);
	void setColumn(Column *, uint32_t);
	uint32_t getRelId();
	uint32_t getColCount();
	Column * getColumn(uint32_t);


};

//---------------------------------------------------------------------------

class VQueries {
   uint64_t validationId;
   uint64_t from;
   uint64_t to;
   uint32_t queryCount;
   Query ** queries;

public:
	VQueries();
	VQueries(uint64_t, uint64_t, uint64_t, uint32_t);
	~VQueries();
	void setVid(uint64_t);
	void setFrom(uint64_t);
	void setTo(uint64_t);
	void setQueryCount(uint32_t);
	void setQuery(Query *, uint32_t);
   	uint64_t getVid();
   	uint64_t getFrom();
   	uint64_t getTo();
   	uint32_t getQueryCount();
   	Query * getQuery(uint32_t);

};
