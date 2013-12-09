#include "concretesearch.h"
#include <iostream>
using namespace std;

ConcreteSearch::ConcreteSearch(SearchWordAlgorithm* swsw):sw(swsw){
}
ConcreteSearch::~ConcreteSearch(){if(sw) delete sw;}

void ConcreteSearch::setSearchWordAlgorithm(SearchWordAlgorithm* swsw){
	if(sw)
		delete sw;
	sw = swsw;
}

void ConcreteSearch::searchDict(const std::string& w, Trie* dict, CWords& cWords){
	sw->setRoot(dict->getRoot());
	sw->searchWord(w, cWords);
}

string ConcreteSearch::printResults(const CWords& cw){
  return sw->printResults(cw);
}
