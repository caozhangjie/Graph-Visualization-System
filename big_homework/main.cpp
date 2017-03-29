#include "paperconferenceauthorgraph.h"
#include "topicgraph.h"
#include "pointcolor.h"
#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PaperConferenceAuthorGraph graph1;
    TopicGraph graph2;
    graph1.readInNode("Nodes.txt");
    graph1.readInEdge("Edges.txt");
    graph1.initialize();
    graph2.readInTopicNode("TopicNodes.txt");
    graph2.readInTopicEdge("TopicEdges.txt");
    graph2.readInDocNode("DocumentContent.txt");
    graph2.initialize();

    MainWindow win(graph1, graph2);

    win.show();

    app.exec();
}
