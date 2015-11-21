
class JournalRecord{
	int * record;
	int recsize;
	public:
		JournalRecord(int,int *,int);
		~JournalRecord();
		void printRecord();
};


class Journal{
	JournalRecord ** journal;
	int maxsize;
	int current;	
	public:
		Journal();
		~Journal();
		void printJournal();
		int insertJournalRecord(JournalRecord*);
		int increaseJournal();		
};

