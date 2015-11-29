#include <stdint.h>

class JournalRecord{
	uint64_t * record;
	int recsize;
	public:
		JournalRecord(uint64_t, uint64_t *, int);
		JournalRecord();

		~JournalRecord();
		void printRecord();
		uint64_t getPrimaryKey();
		uint64_t getTransactionID();
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
		JournalRecord * findLastEntry(uint64_t);
		JournalRecord * getFromOffset(long long int);
};


