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
		void expand_Bucket();		//doubles the size of cells array
		int insert_Bucket(int,int,int);
			
};

/*class Hashtable{
		int global;
		Bucket ** table;
	public:
		Hashtable();
		~Hashtable();	
		int insertHashRecord();
}*/
