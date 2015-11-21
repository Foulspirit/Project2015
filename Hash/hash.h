class Cell{
		int trans_id;			//transaction id
		int offset_del;			//offset for deletion record
		int offset_ins;			//offset for insertion record
	public:
		Cell();
		~Cell();
		int get_trans_id();
		int get_offset_del();
		int get_offset_ins();
		void set_trans_id(int);
		void set_offset_del(int);
		void set_offset_ins(int);	
		void print_Cell();
		
};

class Bucket{
		Cell* cells;
		int local;
		int current;
		int size;
	public:
		Bucket();
		~Bucket();
		void print_Bucket();
		int get_local();
		/*int insertBucket(int);
		int getlocal();	*/	
};

/*class Hashtable{
		int global;
		Bucket ** table;
	public:
		Hashtable();
		~Hashtable();	
		int insertHashRecord();
}*/
