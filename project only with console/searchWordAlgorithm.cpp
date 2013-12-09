#include "searchWordAlgorithm.h"
#include <string>
#include <cstdio>
using namespace std;

int SearchWordAlgorithm::countCharError(char dc, char sc){
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



string Exact_Search::printResults(const CWords& cw)
{

    string output;

      if(cw.size()!=0)
        {
            output+="the word you input is:<br/>";
            for(int i = 0; i < cw.size(); ++i){
            output+= "<b><font color=red>" +cw[i].mWord + "</font></b>";
            }
        }
    else
      output+= "Sorry, I cannot find this word in the dictionary :(";

     return output;

}

void BER_Search::searchWord(const string& s, CWords& cw){
    searchWord(root, s, s.size(), -1, 0, cw);
}

void BER_Search::searchWord(Node* n, const string& s, int size, int i, int eCount, CWords& cw){
    if(i==size-1){
        if(!n->wordMarker())
            return;
        eCount += countCharError(n->content(),s[i]);
        if(eCount > mBER)
            return;
        cw.push_back(WordNode(retrieveWord(n),eCount,n->probability()));
        return;
    }
    if(n && n!=root){
        eCount += countCharError(n->content(),s[i]);
        if(eCount > mBER){
            return;
        }
    }
    for(int j = 0; j < n->children().size(); ++j){
       searchWord(n->children()[j], s, size, i+1, eCount, cw);
    }
    return;
}


string BER_Search::printResults(const  CWords& cw)
{


        string output,snum;

        char str[25];
       output="BER_Search<br/>" ;
    if(cw.size()!=0){
        sprintf(str,"%d",cw.size());
        snum=string(str);
        output+="There are <b><font color=red>"+snum+"</font></b> words that could be the correct input:<br/><br/>" ;

        for(int i = 0; i < cw.size(); ++i){
            sprintf(str,"%d",cw[i].mBitError);
            snum=string(str);
            output+= "<b><font color=red>"+cw[i].mWord +"</font></b><br/> with <b><font color=red>" +snum +"</font></b> different characters from the input<br/><br/>";
        }
    }
    else
        output+=  "there is no word similar to the input";

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


string letter_Search::printResults(const  CWords& cw)
{
    string output;
    for(int i=0;i<cw.size();++i){
       output+=cw[i].mWord +"\n";
    }

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
        eCount += countCharError(n->content(),s[i]);
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
        eCount += countCharError(n->content(),s[i]);
        if(eCount > mBER){
            return;
        }
    }
    for(int j = 0; j < n->children().size(); ++j){
       searchWord(n->children()[j], s, size, i+1, eCount, cw);
    }
    return;
}

string BER_PR_Search::printResults(const CWords& cw)
{

    string output, snum, snum2;
    char str[25];
    if(cw.size()==0)
        return output;
    sprintf(str,"%d",cw.back().mBitError);
    snum=string(str);
    sprintf(str,"%5.5f",cw.back().mPR);
    snum2=string(str);
    output="BER_PR_Search<br/>The most likely word is:<br/><br/><b><font color=red>"+cw.back().mWord+"</font></b><br/>with <b><font color=red>"+snum+"</font></b> different characters and its probability is <b><font color=red>" + snum2+"</font><b>";
    return output;

}
