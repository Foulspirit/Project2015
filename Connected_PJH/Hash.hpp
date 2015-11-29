#include <stdint.h>


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
		void print_Bucket();		//prints local depth and current cells
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

class Node{
		Bucket * data;
		Node * next;
	public:
		Node(Bucket*);
		~Node();
		Node* get_next();
		Bucket* get_data();
		void set_next(Node*);
		void print_Node();	
};

class List{
		Node *head;
		Node *tail;
	public:
		List();
		~List();
		void push(Bucket*);	
		Node* pop();
		int is_empty();
		void print_List();
};

class Hashtable{
		int global;
		Table_Cell * table;
		uint64_t hash;
		uint64_t size;
	public:
		Hashtable();
		~Hashtable();	
		int insertHashRecord(uint64_t, uint64_t, long long int, long long int, List*);
		uint64_t hash_function(uint64_t);
		long long int lastins(uint64_t);
		void double_hash();
		void printHash();
};





