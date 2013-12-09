#ifndef TRIETREE_H
#define TRIETREE_H

#include <vector>
#include <string>
#include "node.h"
class Trie {
public:
    Trie();
    ~Trie();
    void feedTree(const char*);
    void addWord(std::string& s, double pr=1.0);
    void deleteWord(std::string& s);
	Node* getRoot(){return root;};
	
private:

    void destroyTree(Node* n);
    Node* root;
};
#endif
