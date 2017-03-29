#ifndef TOPICNODE
#define TOPICNODE

#include "node.h"

class TopicNode: public Node
{
private:
    vector<string> words;
    vector<int> doc;
public:
    TopicNode(){}
    void addWords(string & temp){words.push_back(temp);}
    void addDoc(int temp){doc.push_back(temp);}
    vector<string> & getWords(){return words;}
    vector<int> & getDoc(){return doc;}
    void abstract(){}
};

#endif // TOPICNODE


