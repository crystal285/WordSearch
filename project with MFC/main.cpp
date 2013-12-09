#include <climits>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include "node.h"
#include "concretesearch.h"
using namespace std;

#define _AFXDLL

int main(int argc, char* argv[]){
    int choice;
    string s;

	ConcreteSearch cs(new letter_Search(10));  //10 candidate letter
	cout<<"please select the searching algorithm"<<"\n1.BER_Search\n2.Exact_Search\n3.BER_PR_Search\n4.letter_Search\n";
    cin>>choice;
	switch(choice){
	    case 1:
            cs.setSearchWordAlgorithm(new BER_Search(3));
            break;
	    case 2:
            cs.setSearchWordAlgorithm(new Exact_Search());
            break;
		case 3:
            cs.setSearchWordAlgorithm(new BER_PR_Search(3));
            break;
		case 4:
            cs.setSearchWordAlgorithm(new letter_Search(10));
            break;}
	string line;
	cout<<"Please enter a word for search: ['qqq' to exit]\n"<<endl;
    getline(cin, line);
	while(getline(cin, line)){
		if(line=="qqq")
			break;
        s=cs.searchWord(line);
        cout<<s;
       cout<<"\nPlease enter a word for search: ['qqq' to exit]\n";
	}


	cout << "bye!" <<endl;
    return 0;
}

