#include "topicgraph.h"
#include <fstream>
#include "undirectededge.h"
#include "topicnode.h"
#include "docnode.h"

int TopicGraph::findNode(int id)
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

int TopicGraph::getRealId(int id)
{
    if(id < node_num && id >= 0)
        return node[id]->getIdOfNode();
    else
        return -1;
}

int TopicGraph::getDoc(int id)
{
    if(doc_map.find(id) != doc_map.end())
    {
        return doc_map.at(id);
    }
    else
    {
        return -1;
    }
}

void TopicGraph::readInTopicNode(const char * file_name)
{
    ifstream fin;
    TopicNode * temp_base;
    fin.open(file_name);
    if(!fin.is_open())
    {
        cout << "The file isn't open." << endl;
        return;
    }
    int id;
    char * buffer = new char[1024];
    while(1)
    {
        getNodeIn().push_back(vector<int>());
        getNodeOut().push_back(vector<int>());
        readSTD(fin, buffer, temp_base, id);
        if(!fin.eof())
        {

        }
        else
        {
           break;
        }
    }
    delete buffer;
    fin.close();
}

void TopicGraph::readInDocNode(const char *file_name)
{
    ifstream fin;
    DocNode * temp_base;
    fin.open(file_name);
    if(!fin.is_open())
    {
        cout << "The file isn't open." << endl;
        return;
    }
    int id;
    char * buffer = new char[50000];
    int k = 0;
    while(1)
    {
        temp_base = new DocNode();

        fin >> id;
        fin.get();
        getDocMap().insert(pair<int, int>(id, k));
        temp_base->setIdOfNode(id);
        fin.getline(buffer, 1000);
        temp_base->setTitle(string(buffer));
        fin.getline(buffer, 49000);
        temp_base->setContent(string(buffer));
        fin.getline(buffer, 100);
        addDocNode(temp_base);
        fin.peek();
        if(!fin.eof())
        {

        }
        else
        {
           break;
        }
        k++;
    }
    delete buffer;
}

void TopicGraph::readInTopicEdge(const char * file_name)
{
    ifstream fin;
    UndirectedEdge * temp_base;
    fin.open(file_name);
    if(!fin.is_open())
    {
        cout << "The file isn't open." << endl;
        return;
    }
    int id;
    int find1;
    int find2;
    double weight;
    char buffer[100];
    vector<int> find3;
    vector<int> temp_pair;
    int k = 0;
    while(1)
    {
        temp_base = new UndirectedEdge;
        fin >> id;
        find1 = findNode(id);
        temp_base->setSource(id);
        fin >> id;
        find2 = findNode(id);
        getNodeOut()[find2].push_back(find1);
        getNodeIn()[find1].push_back(find2);
        getNodeOut()[find1].push_back(find2);
        getNodeIn()[find2].push_back(find1);
        temp_base->setTarget(id);
        find3.push_back(find1);
        find3.push_back(find2);
        getEdgeNode().push_back(find3);
        find3.clear();
        temp_pair.push_back(find2);
        temp_pair.push_back(find1);
        node_to_edge.insert(pair<vector<int>, int>(temp_pair, k));
        temp_pair.clear();
        temp_pair.push_back(find1);
        temp_pair.push_back(find2);
        node_to_edge.insert(pair<vector<int>, int>(temp_pair, k));
        temp_pair.clear();
        fin >> weight;
        temp_base->setWeight(weight);
        addEdge(temp_base);
        k++;
        fin.getline(buffer, 100);
        fin.peek();
        if(fin.eof())
        {
            break;
        }
    }
    return ;
}

void TopicGraph::readSTD(ifstream & fin, char * buffer, TopicNode * & temp_base, int & id)
{
    temp_base = new TopicNode();
    fin >> id;
    fin.get();
    temp_base->setIdOfNode(id);

    fin.getline(buffer, 100, ':');
    fin.get();
    while(1)
    {
        fin.getline(buffer, 100, ' ');
        temp_base->addWords(string(buffer));
        if(fin.peek() == '\n')
            break;
    }
    fin.get();
    fin.getline(buffer, 100, ':');
    while(1)
    {
        fin >> id;
        temp_base->addDoc(id);
        fin.get();
        if(!isdigit(fin.peek()))
            break;
    }
    addTopicNode(temp_base);
    fin.get();
    fin.getline(buffer, 100);
    fin.peek();
}

void TopicGraph::deleteNode()
{
    for(int i = 0; i < node_num; i++)
    {
        delete node[i];
    }
    node.clear();
}

void TopicGraph::deleteEdge()
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

void TopicGraph::deleteDocNode()
{
    doc_map.clear();
    for(int i = 0; i < node_num; i++)
    {
        delete doc[i];
    }
    doc.clear();
}
