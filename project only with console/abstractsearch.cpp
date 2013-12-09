#include "abstractsearch.h";

AbstractSearch::AbstractSearch():dict(0){}
AbstractSearch::~AbstractSearch(){if(dict) delete dict;}

Trie* AbstractSearch::getDict(){
	if(dict)
		return dict;
	else{
		dict = new Trie();
        dict->feedTree("dict.txt");
		return dict;
	}
}

std::string  AbstractSearch::searchWord(const std::string& w){
    Trie* dict = getDict();
	CWords cwords;
    searchDict(w, dict, cwords);
    return printResults(cwords);
    //return std::string("hello");
}
