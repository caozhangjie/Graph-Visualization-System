#ifndef DOCNODE
#define DOCNODE

#include "node.h"

class DocNode: public Node
{
private:
    string title;
    string content;
public:
    void setTitle(string & temp){title = temp;}
    void setContent(string & temp){content = temp;}
    string & getTitle(){return title;}
    string & getContent(){return content;}
    void abstract(){}
};

#endif // DOCNODE

