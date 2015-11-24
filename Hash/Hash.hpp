class Cell{					//---NOTES-------------------//
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
		Cell* cells;			//array aka transaction range 2 offsets maximum 4 each id
		int local;			//local depth
		int current;			//which cell to fill
		int size;			//array size
	public:
		Bucket();
		~Bucket();
		void print_Bucket();		//prints local depth and current cells
		int get_local();
		int get_current();
		Cell* get_cells();	
		void set_local(int );
		void expand_Bucket();		//doubles the size of cells array
		int insert_Bucket(int,int,int);
			
};

class Table_Cell{	
		int key;			//pk of the record
		Bucket * b_ptr;			//ptr to the bucket
	public:
		Table_Cell();
		~Table_Cell();
		int get_key();
		Bucket * get_Bucket();
		void set_key(int);
		void set_Bucket(Bucket *);
		void print_Table_Cell();
};

class Hashtable{
		int global;
		Table_Cell * table;
		int hash;
		int size;
	public:
		Hashtable();
		~Hashtable();	
		int insertHashRecord(int,int,int,int);
		int hash_function(int);
		int lastins(int);
		void double_hash();
		void printhash();
};
