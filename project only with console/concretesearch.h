#ifndef CONCRETESEARCH_H
#define CONCRETESEARCH_H

#include "abstractsearch.h"
#include "searchWordAlgorithm.h"

class ConcreteSearch : public AbstractSearch{
private:
	SearchWordAlgorithm* sw;
public:
	ConcreteSearch(SearchWordAlgorithm*);
	~ConcreteSearch();
	void setSearchWordAlgorithm(SearchWordAlgorithm*);
	void searchDict(const std::string&, Trie*, CWords&);
	std::string printResults(const CWords&);
};

#endif

