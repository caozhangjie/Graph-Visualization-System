#include "paperconferenceauthorgraph.h"
#include "paperconferenceauthornode.h"
#include "directededge.h"
#include <fstream>
int PaperConferenceAuthorGraph::findNode(int id)
{
    int i;
    int len = node.size();
    for(i = 0; i < len; i++)
    {
        if(node[i]->getIdOfNode() == id)
        {
            return i;
        }
    }
    return -1;
}

int PaperConferenceAuthorGraph::getRealId(int id)
{
    if(id < node_num && id >= 0)
        return node[id]->getIdOfNode();
    else
        return -1;
}

void PaperConferenceAuthorGraph::readInNode(const char * file_name)
{
    ifstream fin;
    PaperConferenceAuthorNode * temp_base;
    fin.open(file_name);
    if(!fin.is_open())
    {
        cout << "The file isn't open." << endl;
        return;
    }
    int id;
    char * buffer = new char[1024];
    int k = 0;
    while(1)
    {
        getNodeIn().push_back(vector<int>());
        getNodeOut().push_back(vector<int>());

        readSTD(fin, buffer, temp_base, id, k);
        addNode(temp_base);
        if(!fin.eof())
        {

        }
        else
        {
           break;
        }
    }
    delete buffer;
}

void PaperConferenceAuthorGraph::readInEdge(const char * file_name)
{
    ifstream fin;
    DirectedEdge * temp_base;
    fin.open(file_name);
    if(!fin.is_open())
    {
        cout << "The file isn't open." << endl;
        return;
    }
    int id;
    int find1;
    int find2;
    char buffer[100];
    vector<int> find3;
    vector<int> temp_pair;
    int k = 0;
    while(1)
    {
        temp_base = new DirectedEdge;
        fin >> id;
        find1 = findNode(id);
        temp_base->setSource(id);
        fin >> id;
        find2 = findNode(id);
        getNodeOut()[find2].push_back(find1);
        getNodeIn()[find1].push_back(find2);
        temp_base->setTarget(id);
        addEdge(temp_base);
        find3.push_back(find1);
        find3.push_back(find2);
        getEdgeNode().push_back(find3);
        find3.clear();
        temp_pair.push_back(find1);
        temp_pair.push_back(find2);
        node_to_edge.insert(pair<vector<int>, int>(temp_pair, k));
        temp_pair.clear();
        k++;
        fin.getline(buffer, 100);
        if(fin.eof())
        {
            break;
        }
    }
}

void PaperConferenceAuthorGraph::readSTD(ifstream & fin, char * buffer, PaperConferenceAuthorNode * & temp_base, int & id, int & k)
{
    fin >> id;
    fin.get();
    fin.getline(buffer, 100, ':');
    fin.get();
    fin.getline(buffer, 100);
    if(!strcmp(buffer, "paper"))
    {
        temp_base = new PaperConferenceAuthorNode();
        temp_base->setIdOfNode(id);
        temp_base->setType(PaperConferenceAuthorNode::PAPER);
        fin.getline(buffer, 100, ':');
        fin >> id;
        temp_base->setYear(id);
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setExtra(string(buffer));
        fin.getline(buffer, 100, ':');
        fin >> id;
        temp_base->setDateFrom(id);
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setId(string(buffer));
        if(k != 163)
        {
            fin.getline(buffer, 100, ':');
            fin >> id;
            temp_base->setPageFrom(id);
        }
        else
        {
            temp_base->setPageFrom(-1);
        }
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setName(string(buffer));
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setNameShort(string(buffer));
        vector<int> x = vector<int>();
        fin.getline(buffer, 100, '(');
        fin >> id;
        x.push_back(id);
        fin.getline(buffer, 100, ',');
        fin >> id;
        x.push_back(id);
        fin.getline(buffer, 100, ',');
        fin >> id;
        x.push_back(id);
        fin.getline(buffer, 100, ',');
        fin >> id;
        x.push_back(id);
        temp_base->setViewColor(x);
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setViewLabel(string(buffer));
        vector<double> y = vector<double>();
        double t;
        fin.getline(buffer, 100, '(');
        fin >> t;
        y.push_back(t);
        fin.getline(buffer, 100, ',');
        fin >> t;
        y.push_back(t);
        fin.getline(buffer, 100, ',');
        fin >> t;
        y.push_back(t);
        temp_base->setViewLayout(y);
    }
    else if(!strcmp(buffer, "conference"))
    {
        //读入conference节点
        temp_base = new PaperConferenceAuthorNode();
        temp_base->setIdOfNode(id);
        temp_base->setType(PaperConferenceAuthorNode::CONFERENCE);
        fin.getline(buffer, 100, ':');
        fin >> id;
        temp_base->setYear(id);
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setId(string(buffer));
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setName(string(buffer));
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setNameShort(string(buffer));
        vector<int> x = vector<int>();
        fin.getline(buffer, 100, '(');
        fin >> id;
        x.push_back(id);
        fin.getline(buffer, 100, ',');
        fin >> id;
        x.push_back(id);
        fin.getline(buffer, 100, ',');
        fin >> id;
        x.push_back(id);
        fin.getline(buffer, 100, ',');
        fin >> id;
        x.push_back(id);
        temp_base->setViewColor(x);
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setViewLabel(string(buffer));
        vector<double> y = vector<double>();
        double t;
        fin.getline(buffer, 100, '(');
        fin >> t;
        y.push_back(t);
        fin.getline(buffer, 100, ',');
        fin >> t;
        y.push_back(t);
        fin.getline(buffer, 100, ',');
        fin >> t;
        y.push_back(t);
        temp_base->setViewLayout(y);
    }
    else if(!strcmp(buffer, "author"))
    {
        //读入author节点
        temp_base = new PaperConferenceAuthorNode();
        temp_base->setIdOfNode(id);
        temp_base->setType(PaperConferenceAuthorNode::AUTHOR);
        fin.getline(buffer, 100, ':');
        fin >> id;
        temp_base->setYear(id);
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setId(string(buffer));
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setName(string(buffer));
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setNameShort(string(buffer));
        vector<int> x = vector<int>();
        fin.getline(buffer, 100, '(');
        fin >> id;
        x.push_back(id);
        fin.getline(buffer, 100, ',');
        fin >> id;
        x.push_back(id);
        fin.getline(buffer, 100, ',');
        fin >> id;
        x.push_back(id);
        fin.getline(buffer, 100, ',');
        fin >> id;
        x.push_back(id);
        temp_base->setViewColor(x);
        fin.getline(buffer, 100, ':');
        fin.get();
        fin.getline(buffer, 200);
        temp_base->setViewLabel(string(buffer));
        vector<double> y = vector<double>();
        double t;
        fin.getline(buffer, 100, '(');
        fin >> t;
        y.push_back(t);
        fin.getline(buffer, 100, ',');
        fin >> t;
        y.push_back(t);
        fin.getline(buffer, 100, ',');
        fin >> t;
        y.push_back(t);
        temp_base->setViewLayout(y);
    }
    else
    {
        return;
    }
    k++;
    fin.getline(buffer, 100);
    fin.getline(buffer, 100);
    fin.peek();
}

void PaperConferenceAuthorGraph::deleteNode()
{
    for(int i = 0; i < node_num; i++)
    {
        delete node[i];
    }
    node.clear();
}

void PaperConferenceAuthorGraph::deleteEdge()
{
    for(int i = 0; i < node_num; i++)
    {
        node_in[i].clear();
        node_out[i].clear();       
    }
    edge_node.clear();
    node_to_edge.clear();
    for(int i = 0; i < node_num; i++)
    {
        delete edge[i];
    }
    edge.clear();
}
