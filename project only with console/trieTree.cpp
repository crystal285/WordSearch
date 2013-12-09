#include "trieTree.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib> //includes std::atof
using namespace std;

Trie::Trie(){
    root = new Node();
}

void Trie::destroyTree(Node* n){
    int size=(n->children()).size();
    
    for(int i=0; i<size;++i){
        destroyTree((n->children())[i]);
    }
    
    delete n;
}

Trie::~Trie(){
    destroyTree(root);
}

void _splitString(vector<string>& components, string& l, char d){
	int i = 0, j;
	while(i < l.size()){
		if(l[i] == d){
			++i;
			continue;
		}
		j = i + 1;
		while(j < l.size()){
			if(l[j] == d){
				break;
			}
			else
				++j;
		}
		components.push_back(l.substr(i, j-i));
		i = j;
	}
}
void Trie::feedTree(const char* dict){
	ifstream rf(dict);
	string line;
    vector<string> components;
	while(getline(rf,line)){
        components.clear();
        _splitString(components,line,' ');
        switch(components.size()){
            case 1:
                addWord(components[0]);
                break;
            case 2:
		        addWord(components[0],atof(components[1].c_str()));
                break;
            default:
                break;
        }
	}
	rf.close();
}

void Trie::addWord(std::string& s, double prob){
    Node* current = root;
    if ( s.length() == 0 ){
        //an empty word
        current->setWordMarker();
        return;
    }

    for ( int i = 0; i < s.length(); i++ ){       
        Node* child = current->findChild(s[i]);
        if ( child != NULL ){
            current = child;
            if(prob>child->probability())
                child->setProbability(prob);
        }
        else{
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            tmp->setParent(current);
            tmp->setProbability(prob);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setWordMarker();
    }
}


