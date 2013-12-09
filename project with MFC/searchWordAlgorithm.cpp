#include "stdafx.h"
#include "searchWordAlgorithm.h"
#include <iostream>
#include "stdio.h"
#include <sstream>
# include <stdlib.h>
using namespace std;

int SearchWordAlgorithm::countBitError(char dc, char sc){
    char error = dc ^ sc;
    int i=0;
/*    while(error != 0){
        ++i;
        error = error & (error-1);
    }
    return i;*/
    if(dc!=sc)
      return 1;
      else
      return 0;
}


string SearchWordAlgorithm::retrieveWord(Node* n){
    vector<char> word;
    while(n!=root){
        word.push_back(n->content());
        n=n->parent();
    }

    return string(word.rbegin(),word.rend());

}





void Exact_Search::searchWord(const string& s, CWords& cw){
    cw.clear();
    Node* current = root;
    while ( current != NULL ){
        for ( int i = 0; i < s.length(); i++ ){
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return;
            current = tmp;
        }
        if ( current->wordMarker() ){
            cw.push_back(retrieveWord(current));
            return;
        }
        else
            return;
    }

    return;

}



string Exact_Search::print(const CWords& cw)
{

    string output;

      if(cw.size()!=0)
        {
            output+="the word you input is:\r\n";
            for(int i = 0; i < cw.size(); ++i){
            output+= cw[i].mWord + "\r\n" ;
            }
        }
    else
      output+= "this word don't exist in dictionary";

     return output;

}

void BER_Search::searchWord(const string& s, CWords& cw){
    searchWord(root, s, s.size(), -1, 0, cw);
}

void BER_Search::searchWord(Node* n, const string& s, int size, int i, int eCount, CWords& cw){
    if(i==size-1){
        if(!n->wordMarker())
            return;
        eCount += countBitError(n->content(),s[i]);
        if(eCount > mBER)
            return;
        cw.push_back(WordNode(retrieveWord(n),eCount,n->probability()));
        return;
    }
    if(n && n!=root){
        eCount += countBitError(n->content(),s[i]);
        if(eCount > mBER){
            return;
        }
    }
    for(int j = 0; j < n->children().size(); ++j){
       searchWord(n->children()[j], s, size, i+1, eCount, cw);
    }
    return;
}


string BER_Search::print(const  CWords& cw)
{


        string output,s,snum,snum2;
        char str[25];
        //stringstream ss(s);
       output="BER_Search\r\n" ;
    if(cw.size()!=0){
        // ss<<cw.size();
        snum=string(itoa(cw.size(),str,10));
        output+="there are "+snum+"words that could be the correct input:\r\n" ;

        for(int i = 0; i < cw.size(); ++i){
            snum=string(itoa(cw[i].mBitError,str,10));
            snum2=string(itoa(cw[i].mPR,str,10));
            output+= cw[i].mWord +"\r\n with " +snum +" letter different from the input and" + snum2 +"\r\n";
        }
    }
    else
        output+=  "there is no word similar to the input:\r\n";

        return output;


}

void letter_Search::searchWord(const string& s, CWords& cw){
    cw.clear();
    candidate=0;
    Node* current = root;
        for ( int i = 0; i < s.length(); i++ ){
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
            	return;
            current = tmp;
        }
    searchWord(current, cw);
}


void letter_Search::searchWord(Node* n,   CWords& cw){

    if ( n->wordMarker() && candidate<limit ){
	candidate++;
    cw.push_back(retrieveWord(n));
    }


    	for(int j = 0; j < n->children().size(); ++j){
       	searchWord(n->children()[j],  cw);
   		 }


    return;
}


string letter_Search::print(const  CWords& cw)
{
        string output,snum;
        char str[25];
    output="letter_Search\r\n" ;
	if(cw.size()!=0)
    {
         snum=string(itoa(cw.size(),str,10));
        output+="the "+snum+" possible candidates are :\r\n" ;
        for(int i = 0; i < cw.size(); ++i){
            output+= cw[i].mWord +"\r\n";
        }
    }
    else
        output+="there is no possible word of input:\r\n" ;

  return output;

}


void BER_PR_Search::searchWord(const string& s, CWords& cw){
    mMAX_PR=0.0;
    searchWord(root,s,s.size(),-1,0,cw);
}

void BER_PR_Search::searchWord(Node* n, const string& s, int size, int i, int eCount, CWords& cw){
    if(i==size-1){
        if(!n->wordMarker())
            return;
        eCount += countBitError(n->content(),s[i]);
        if(eCount > mBER)
            return;
        if(n->probability()<mMAX_PR)
            return;
        cw.push_back(WordNode(retrieveWord(n),eCount,n->probability()));
        mMAX_PR=n->probability();
        return;
    }
    if(n && n!=root){
        if(n->probability()<mMAX_PR){
            return;
        }
        eCount += countBitError(n->content(),s[i]);
        if(eCount > mBER){
            return;
        }
    }
    for(int j = 0; j < n->children().size(); ++j){
       searchWord(n->children()[j], s, size, i+1, eCount, cw);
    }
    return;
}

string BER_PR_Search::print(const CWords& cw)
{

         string output,s,snum,snum2;
//		 char s[100];
        char str[25];
        //stringstream ss(s);
       output="BER_PR_Search\r\n" ;

    if(cw.size()!=0){
        // ss<<cw.size();
        snum=string(itoa(cw.size(),str,10));
        output+="there are "+snum+"words that could be the correct input:\r\n" ;

        for(int i = 0; i < cw.size(); ++i){
            snum=string(itoa(cw[i].mBitError,str,10));
            //snum2=string(itoa(cw[i].mPR,str,));
			//memset(str, 0, 100);
			//sprintf(s, "%f", cw[i].mPR);
			
			snum2 = std::to_string((long double)cw[i].mPR);
            output+= cw[i].mWord +"\r\n with " +snum +" letter different from the input and" + snum2 +"\r\n";
        }
    }
    else
        output+=  "there is no word similar to the input:\r\n";

        return output;

}
