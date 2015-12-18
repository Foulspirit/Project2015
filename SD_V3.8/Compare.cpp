#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h> // for exit()

using namespace std;
int main(int argc, char **argv){

	char buff1[100000];
	char buff2[100000];
	long int i=0, c1=0, c2=0;
	long int fal=0;
	long int tru=0;
    long double p1, p2;

    ifstream myfile ("results.txt");

    if (myfile.is_open()){
        while ( !myfile.eof()){
            myfile >> buff1[i];
            i++;
            c1++;
        }  
    }  
    myfile.close();

    ifstream myfile2;

    if (argc == 1)
        myfile2.open("small.bin.out");
    else
        myfile2.open(argv[1]);
    
    i=0;
    if (myfile2.is_open()){
        while ( !myfile2.eof()){
            myfile2 >> buff2[i];
            i++;
            c2++;
        } 
    }   
    myfile2.close();

    i=0;
	while((buff1[i]=='0')||(buff1[i]=='1')){
		if(buff1[i]!=buff2[i]){
			fal++;
            cout<<fal<<": validationId "<< i << ": "<< buff1[i] << " VS " << buff2[i] << endl;
        }
		else
			tru++;
		i++;
	}
    p1 = ((long double)tru/(long double)i)*100;
    p2 = ((long double)fal/(long double)i)*100;
	cout << endl << "true: " << tru << " out of : "<< i << endl;
    cout << "Percentage: " << p1 << "%" << endl << endl;
    cout << "false: " << fal << " out of : "<< i << endl;
    cout << "Percentage: " << p2 << "%" << endl;

return 0;
}
