#include <iostream>
#include <stdint.h>

using namespace std;

//-----------------------Node-----------------------//
template <class T> class Node
{
    T* data; //the object information
    Node* next; //pointer to the next node element

public:
	Node(){
		data = NULL;
		next = NULL;
	}
	~Node(){
		next = NULL;
		data = NULL;
	}
	void setData(T* info){
		data = info;
	}
	void setNext(Node * n){
		next = n;
	}
	T* getData(){
		return data;
	}
	Node* getNext(){
		return next;
	}
	void printNode(){
		data->printData();
	}
    //Methods omitted for brevity
};


//-----------------------Lista-----------------------//
template <class T> class Lista
{
    Node<T> *head, *tail;
    uint64_t counter; 

public:

    Lista()
    {
    	counter = 0;
        head = NULL;
        tail = NULL;
    }

    ~Lista() /// NOT COOL ///
    {
    	while (counter > 0){
    		pop();
    	}
    }

    void deleteLista(){
        T* temp;

		while (counter > 0){
    		temp = pop();
    		delete temp;
    	}
    }

    //Method adds info to the end of the list
    void push(T* info){
        if(head == NULL) //if our list is currently empty
        {
        	counter = 1;
            head = new Node<T>; //Create new node of type T
            head->setData(info);
            tail = head;
        }
        else //if not empty add to the end and move the tail
        {
        	counter++;
            Node<T>* temp = new Node<T>;
            temp->setData(info);
            tail->setNext(temp);
            tail = tail->getNext();
        }
    }

    void popall(){
        if(head == NULL){ //if our list is currently empty
        	//EMPTY LIST
        	return;
        }
		while (counter > 0){
    		pop();
    	}
    }

    T* pop(){
        if(head == NULL){ //if our list is currently empty
        	//EMPTY LIST
        	return NULL;
        }
		
		counter--;
		Node<T>* temp = head;
		T* ret = temp->getData();
		head = head->getNext();
		delete temp;
		return ret;
    }

    T* preview(){
        if(head == NULL){ //if our list is currently empty
        	//EMPTY LIST
        	return NULL;
        }
		
		T* ret = head->getData();
		return ret;
    }

	uint64_t getCounter(){
		return counter;
	} 

    void printList(){
    	Node<T>* cur = head;
    	while (cur!=NULL){
    		cur->printNode();
    		cur = cur->getNext();
    	}
    }
};