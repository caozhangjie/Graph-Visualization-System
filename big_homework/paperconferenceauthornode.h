#ifndef PAPERCONFERENCEAUTHORNODE
#define PAPERCONFERENCEAUTHORNODE

#include "node.h"

class PaperConferenceAuthorNode : public Node
{
public:
    void abstract(){}
    enum Type {PAPER, CONFERENCE, AUTHOR};
    PaperConferenceAuthorNode(){}
    void setType(Type temp){type = temp;}
    void setYear(int temp){year = temp;}
    void setViewColor(vector<int> & temp){view_color = temp;}
    void setViewLayout(vector<double> temp){view_layout = temp;}
    void setViewLabel(string & temp){view_label = temp;}
    void setId(string & temp){id = temp;}
    void setName(string & temp){name = temp;}
    void setNameShort(string & temp){name_short = temp;}
    void setExtra(string & temp){extra = temp;}
    void setDateFrom(int temp){date_from = temp;}
    void setPageFrom(int temp){page_from = temp;}
    Type getType(){return type;}
    int getYear(){return year;}
    vector<int> & getViewColor(){return view_color;}
    vector<double> & getViewLayout(){return view_layout;}
    string & getViewLabel(){return view_label;}
    string & getId(){return id;}    
    string & getName(){return name;}
    string & getNameShort(){return name_short;}
    string & getExtra(){return extra;}
    int getDateFrom(){return date_from;}
    int getPageFrom(){return page_from;}    
private:
    Type type;
    int year;
    vector<int> view_color;
    vector<double> view_layout;
    string view_label;
    string id;
    string name;
    string name_short;
    int date_from;
    int page_from;
    string extra;
};

#endif // PAPERCONFERENCEAUTHORNODE

