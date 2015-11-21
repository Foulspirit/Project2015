
class Bucket{
		int* cells;
		int local;
	public:
		Bucket();
		~Bucket();
		void printBucket();
		int insertBucket(int);
		int getlocal();		
};

class Hashtable{
		int global;
		Bucket ** table;
	public:
		Hashtable();
		~Hashtable();	
		int insertHashRecord();
}
