#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

class Node {
public:
    inline Node() : mPR(0.0),mContent(' '), mMarker(false) {}
    inline ~Node() {}
    inline char content() { return mContent; }
    inline void setContent(char c) { mContent = c; }
    inline bool wordMarker() { return mMarker; }
    inline void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    inline void appendChild(Node* child) { mChildren.push_back(child); }
    inline std::vector<Node*> children() { return mChildren; }
    void setParent(Node* n){mParent=n;}
    Node* parent(){return mParent;}
    void setProbability(const double& d){mPR=d;}
    double probability(){return mPR;}
private:
    double mPR;
    Node* mParent;
    char mContent;
    bool mMarker;
    std::vector<Node*> mChildren;
};

class WordNode{
public:
    std::string mWord;
    int mBitError;
    double mPR;
    WordNode(const std::string& s, int b=0, double p=1):mWord(s),mBitError(b),mPR(p){}
};

typedef std::vector<WordNode> CWords;
#endif
