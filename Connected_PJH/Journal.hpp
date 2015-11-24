
class JournalRecord{
	int * record;
	int recsize;
	public:
		JournalRecord(int,int *,int);
		JournalRecord();

		~JournalRecord();
		void printRecord();
		int getPrimaryKey();
		int getTransactionID();
		void setTransactionID(int);
		void setRecord(int *);
		void setRecsize(int);
		void setCopy(int, int *);
		int getRecsize();
		int * getRecord();
};


class Journal{
	JournalRecord ** journal;
	int colnum;
	int maxsize;
	int current;	
	public:
		Journal();
		Journal(int);
		~Journal();
		void printJournal();
		int insertJournalRecord(JournalRecord*);
		int increaseJournal();	
		int getColnum();	
		JournalRecord * findLastEntry(int);
		JournalRecord * getFromOffset(int);
};


