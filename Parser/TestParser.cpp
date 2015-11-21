#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <iostream>

#include "Parser.cpp"

using namespace std;

int main(int argc, char **argv) {

	MessageHead_t head;
	void *body = NULL;
	DefineSchema_t* DSbody;
	Transaction_t* Tbody;
	ValidationQueries_t* VQbody;
	Flush_t* FLbody;
	Forget_t* FRbody;
	uint32_t len;

	while(1){
		// Retrieve the message head
		if (read(0, &head, sizeof(head)) <= 0) { return -1; } // crude error handling, should never happen
		cout << "HEAD LEN "<< head.messageLen << "\t| HEAD TYPE "<<  head.type << "\t| DESC ";
		
		// Retrieve the message body
		if (body != NULL) free(body);

		if (head.messageLen > 0 ){
			body = malloc(head.messageLen*sizeof(char));

			if (read(0, body, head.messageLen) <= 0) { printf("err");return -1; } // crude error handling, should never happen
			len-=(sizeof(head) + head.messageLen);
		}

		// And interpret it
		switch (head.type) {
			case Done: printf("\n");return 0;
			case DefineSchema: DSbody = (DefineSchema_t*) body; processDefineSchema(DSbody); break;
			case Transaction: Tbody = (Transaction_t*) body; processTransaction(Tbody); break;
			case ValidationQueries: VQbody = (ValidationQueries_t*) body; processValidationQueries(VQbody); break;
			case Flush: FLbody = (Flush_t*) body; processFlush(FLbody); break;
			case Forget: FRbody = (Forget_t*) body; processForget(FRbody); break;
			default: 
		return -1; // crude error handling, should never happen
		}

    }
    
  	return 0;
}
