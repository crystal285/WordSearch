#ifndef SEARCHWORDALGORITHM_H
#define SEARCHWORDALGORITHM_H

#include<string>
#include<vector>
#include "node.h"
class SearchWordAlgorithm{
    public:
        virtual ~SearchWordAlgorithm(){};
        SearchWordAlgorithm(){};
        virtual void searchWord(const std::string&, CWords&)=0;
        std::string retrieveWord(Node*);
        int countCharError(char, char);
        void setRoot(Node* n){root=n;}
        virtual std::string printResults(const CWords&)=0;
    protected:
        Node* root;
};

class Exact_Search:public SearchWordAlgorithm{
    public:
        void searchWord(const std::string&, CWords&);
       std::string printResults(const  CWords&);
};

class BER_Search:public SearchWordAlgorithm{
    public:
        virtual ~BER_Search(){};
        BER_Search(int ber):mBER(ber){}
        void searchWord(const std::string&, CWords&);
        void searchWord(Node*, const std::string&, int, int, int, CWords&);
        void setBER(int b){mBER=b;}
       std::string printResults(const CWords&);
    protected:
        int mBER;
};

class BER_PR_Search:public SearchWordAlgorithm{
    public:
        ~BER_PR_Search(){};
        BER_PR_Search(int ber):mBER(ber){}
        void searchWord(const std::string&, std::vector<WordNode>&);
        void searchWord(Node*, const std::string&, int, int, int, std::vector<WordNode>&);
        std::string printResults(const CWords&);
    private:
        int mBER;
        double mMAX_PR;
};

class letter_Search:public SearchWordAlgorithm{
    public:
    	 ~letter_Search(){};
        letter_Search(int ber):limit(ber){}
        void searchWord(const std::string&, CWords&);
        void searchWord(Node* n,   CWords& cw);
        std::string printResults(const CWords&);
	private:
        int limit;
        int candidate;

};



#endif

