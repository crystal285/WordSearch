#ifndef ABSTRACTSEARCH_H
#define ABSTRACTSEARCH_H

#include "trieTree.h"
#include "node.h"
#include <string>
#include <vector>

class AbstractSearch{
private:
	Trie* dict;
public:
	AbstractSearch();
	virtual ~AbstractSearch();
	Trie* getDict();
	virtual void searchDict(const std::string&, Trie*, CWords&) = 0;
	virtual std::string printResults(const CWords&) = 0;
	std::string searchWord(const std::string&);
};
#endif
