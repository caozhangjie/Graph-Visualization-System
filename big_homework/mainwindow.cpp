#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pointcolor.h"
#include "filterdialog.h"
#include "filtertopicdialog.h"
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QColor>
#include<QKeyEvent>
#include<Qt>
#include<QPoint>
#include<QSize>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QRect>
#include <QDebug>
#include "dialog.h"
#include "nobezierdialog.h"
#include "cartoondialog.h"

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(PaperConferenceAuthorGraph & temp, TopicGraph & temp1, QWidget * parent):QMainWindow(parent),
    t_graph(temp1), p_graph(temp), layout_timer(this), ui(new Ui::MainWindow), strategy_num(9), edge_color(140)
{
    ui->setupUi(this);
    is_in_local = false;
    int node_num = p_graph.getNodeNum();
    //设置虚拟原点及放缩比
    my_scale = 1;
    Opoint = vector<int>(3);
    Opoint[0] = 0;
    Opoint[1] = 0;
    Opoint[2] = 0;
    height = 0;
    radis = 5;
    //设定初始布局
    strategy = START;
    
    //bool值得初始化
    in_cartoon = false;    
    is_highlight = false;
    is_pull = false;
    is_key_v_pressed = false;
    is_key_h_pressed = false;
    is_in_filter = false;
    is_dragging = false;
    is_single = false;
    is_mouse_pressed = false;
    is_in_start = true;
    is_spinBox_changed = false;
    
    //选中的点的id的初始化
    full_big = 0;
    highlight_number = 0;
    alpha_degree = -1;    
    data_change = 0;    
    //设置所有初始选定值
    id_move_point = 0;
    id_select_point = -1;
    id_select_edge = -1;
    
    //设置窗口大小及调节滚动条位置
    resize(1920, 1000);
    main_length = 1920;
    main_width = 1000;
    ui->verticalScrollBar->setSliderPosition(50);
    ui->horizontalScrollBar->setSliderPosition(50);
    last_posi_vertical = 50;
    last_posi_horizantol = 50;
    alpha_start = 0;
    //设置背景色
    setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0,0,0));
    setPalette(palette);

    //设置控件
    QPalette my_palette;
    my_palette.setColor(QPalette::WindowText, QColor(210,210,210));
    ui->start_btn->setGeometry(920, 800, 80, 60);
    ui->groupBox->setPalette(my_palette);
    ui->node_out_slider->setRange(0, 72);
    ui->node_in_slider->setRange(0, 32);
    ui->node_sum_slider->setRange(0, 82);
    ui->weight_slider->setRange(0, 73);
    ui->toSpinBox->setMinimum(0);
    ui->toSpinBox->setMaximum(72);
    ui->fromSpinBox->setMinimum(0);
    ui->fromSpinBox->setMaximum(82);
    ui->sumSpinBox->setMinimum(0);
    ui->sumSpinBox->setMaximum(73);
    ui->weightSpinBox->setMinimum(0);
    ui->weightSpinBox->setMaximum(0.73);
    ui->weightSpinBox->setSingleStep(0.01);

    //设置edge weight
    int number = t_graph.getEdgeNum();
    edge_state_t.resize(number);
    for(int i =0 ;i < number; i++)
    {
        edge_weight.push_back(t_graph.getEdge()[i]->getWeight());
        edge_state_t[i] = true;
    }

    //初始为paper图
    has_weight = false;

    //设置动画时间器间隔
    layout_timer.setInterval(20);
    connect(&layout_timer, SIGNAL(timeout()), this, SLOT(changeLayout()));

    //设置切换数据渐变效果
    data_timer.setInterval(10);
    connect(&data_timer, SIGNAL(timeout()), this, SLOT(changeData()));

    //设置开始动画
    start_timer.setInterval(10);
    connect(&start_timer, SIGNAL(timeout()), this, SLOT(changeDataStart()));

    //设置两种数据三种度数
    point_weight.resize(2);
    point_weight[0].resize(3);
    point_weight[1].resize(3);

    point_num_edge_state.resize(2);
    point_num_edge_state[0].resize(3);
    point_num_edge_state[1].resize(3);
    //设置各节点数组大小
    setPointSize(node_num);


    //设置个节点初始属性
    for(int i= 0; i < node_num; i++)
    {
        point_num_edge_state[0][0][i] = true;
        point_num_edge_state[0][1][i] = true;
        point_num_edge_state[0][2][i] = true;
        point_num_edge_state[1][0][i] = true;
        point_num_edge_state[1][1][i] = true;
        point_num_edge_state[1][2][i] = true;
        velocity[i].resize(3);
        temp_point[i].resize(3);
        point_state[i] = true;
        point_state_t[i] = true;
        switch(p_graph.getNode()[i]->getType())
        {
        case PaperConferenceAuthorNode::PAPER:
            point_type[i] = POINT_PAPER;
            break;
        case PaperConferenceAuthorNode::CONFERENCE:
            point_type[i] = POINT_CONFERENCE;
            break;
        case PaperConferenceAuthorNode::AUTHOR:
            point_type[i] = POINT_AUTHOR;
            break;
        }
        point_weight[0][0][i] = p_graph.getSumNum(i);
        point_weight[0][1][i] = p_graph.getInNum(i);
        point_weight[0][2][i] = p_graph.getOutNum(i);
        point_weight[1][0][i] = t_graph.getSumNum(i);
        point_weight[1][1][i] = t_graph.getInNum(i);
        point_weight[1][2][i] = t_graph.getOutNum(i);
    }
    
    //初始化各种布局算法
    initializeForStrategyP();
    initializeForStrategyT();
}


//初始化与Topic data相关的布局算法
void MainWindow::initializeForStrategyT()
{
    const int strategy_num = 10;  // strategy数量
    double min_x = 0;
    double min_y = 0;
    double min_z = 0;
    vtkSmartPointer<vtkMutableDirectedGraph> vtk_graph1 = vtkSmartPointer<vtkMutableDirectedGraph>::New();
    vtkGraph* vtk_s_graph1;
    vtkSmartPointer<vtkGraphLayout> layout = vtkSmartPointer<vtkGraphLayout>::New();
    vtkSmartPointer<vtkForceDirectedLayoutStrategy> strategy2 = vtkSmartPointer<vtkForceDirectedLayoutStrategy>::New();
    vtkSmartPointer<vtkCircularLayoutStrategy> strategy1 = vtkSmartPointer<vtkCircularLayoutStrategy>::New();
    vtkSmartPointer<vtkClustering2DLayoutStrategy>strategy7 = vtkSmartPointer<vtkClustering2DLayoutStrategy>::New();
    vtkSmartPointer<vtkFast2DLayoutStrategy> strategy4 = vtkSmartPointer<vtkFast2DLayoutStrategy>::New();
    vtkSmartPointer<vtkRandomLayoutStrategy> strategy5 = vtkSmartPointer<vtkRandomLayoutStrategy>::New();
    vtkSmartPointer<vtkSimple2DLayoutStrategy> strategy6 = vtkSmartPointer<vtkSimple2DLayoutStrategy>::New();   
    int node_num = p_graph.getNodeNum();
    forceLayout my_layout1(t_graph, node_num);
    weightLayout my_layout2(t_graph);

    helloLayout start_layout(node_num);

    double temp_point[3] = {0.0, 0.0, 0.0};
    int edge_num = t_graph.getEdgeNum();
    for(int i = 0; i < node_num; i++)
    {
        vtk_graph1->AddVertex();
    }
    for(int i = 0; i < edge_num; i++)
    {
        vtk_graph1->AddEdge(t_graph.getEdgeNode()[i][0], t_graph.getEdgeNode()[i][1]);
    }
    layout->SetInputData(vtk_graph1);
    layout->SetLayoutStrategy(strategy1);
    layout->Update();
    vtk_s_graph1 = layout->GetOutput();
    t_point.resize(strategy_num);
    for(int i = 0; i < strategy_num; i++)
    {
        t_point[i].resize(node_num);
    }


    //自定义layout
    start_layout.calcLayout();
    start_layout.getPoint(t_point[START]);
    my_layout1.calcLayout();
    my_layout1.getPoint(t_point[MYLAYOUT2]);
    my_layout2.setFactor(100);
    my_layout2.calcLayout();
    my_layout2.getPoint(t_point[MYLAYOUT1]);

    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += t_point[MYLAYOUT2][i][0];
        min_y += t_point[MYLAYOUT2][i][1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        t_point[MYLAYOUT2][i][0] -= min_x;
        t_point[MYLAYOUT2][i][1] -= min_y;
    }

    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += t_point[MYLAYOUT1][i][0];
        min_y += t_point[MYLAYOUT1][i][1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        t_point[MYLAYOUT1][i][0] -= min_x;
        t_point[MYLAYOUT1][i][1] -= min_y;
    }

    //vtklayout
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        t_point[CICLE][i].resize(3);
        t_point[CICLE][i][0] = temp_point[0] * main_length / 2.4;
        t_point[CICLE][i][1] = temp_point[1] * main_width / 2.4;
        t_point[CICLE][i][2] = temp_point[2];
    }

    layout->SetLayoutStrategy(strategy2);
    layout->Update();
    vtk_s_graph1 = layout->GetOutput();
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        t_point[FORCE][i].resize(3);
        t_point[FORCE][i][0] = temp_point[0] * main_length / 1.1;
        t_point[FORCE][i][1] = temp_point[1] * main_width / 1.1;
        t_point[FORCE][i][2] = temp_point[2];
    }
    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += t_point[FORCE][i][0];
        min_y += t_point[FORCE][i][1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        t_point[FORCE][i][0] -= min_x;
        t_point[FORCE][i][1] -= min_y;
    }

    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    qrand() % 100 / 100 - 0.5;
    for(int i = 0; i < node_num; i++)
    {
        t_point[MYLAYOUT1][i].resize(3);
        t_point[MYLAYOUT1][i][0] = (double(qrand() % 100) / 100 - 0.5) * main_length / 1.5;
        t_point[MYLAYOUT1][i][1] = (double(qrand() % 100) / 100 - 0.5) * main_width / 1.5;
        t_point[MYLAYOUT1][i][2] = (double(qrand() % 100) / 100 - 0.5);
    }


    layout->SetLayoutStrategy(strategy4);
    layout->Update();
    vtk_s_graph1 = layout->GetOutput();
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        t_point[FAST2D][i].resize(3);
        t_point[FAST2D][i][0] = temp_point[0] * main_length / 19;
        t_point[FAST2D][i][1] = temp_point[1] * main_width / 19;
        t_point[FAST2D][i][2] = temp_point[2];
    }
    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += t_point[FAST2D][i][0];
        min_y += t_point[FAST2D][i][1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        t_point[FAST2D][i][0] -= min_x;
        t_point[FAST2D][i][1] -= min_y;
    }

    layout->SetLayoutStrategy(strategy5);
    layout->Update();
    vtk_s_graph1 = layout->GetOutput();
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        t_point[RANDOM][i].resize(3);
        t_point[RANDOM][i][0] = temp_point[0] * main_length / 1.3;
        t_point[RANDOM][i][1] = temp_point[1] * main_width / 1.3;
        t_point[RANDOM][i][2] = temp_point[2];
    }
    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += t_point[RANDOM][i][0];
        min_y += t_point[RANDOM][i][1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        t_point[RANDOM][i][0] -= min_x;
        t_point[RANDOM][i][1] -= min_y;
    }

    layout->SetLayoutStrategy(strategy6);
    layout->Update();
    vtk_s_graph1 = layout->GetOutput();
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        t_point[SIMPLE2D][i].resize(3);
        t_point[SIMPLE2D][i][0] = temp_point[0] * main_length / 44;
        t_point[SIMPLE2D][i][1] = temp_point[1] * main_width / 44;
        t_point[SIMPLE2D][i][2] = temp_point[2];
    }
    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += t_point[SIMPLE2D][i][0];
        min_y += t_point[SIMPLE2D][i][1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        t_point[SIMPLE2D][i][0] -= min_x;
        t_point[SIMPLE2D][i][1] -= min_y;
    }

    layout->SetLayoutStrategy(strategy7);
    layout->Update();
    vtk_s_graph1 = layout->GetOutput();
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        t_point[CLUSTERING2D][i].resize(3);
        t_point[CLUSTERING2D][i][0] = temp_point[0] * main_length / 23;
        t_point[CLUSTERING2D][i][1] = temp_point[1] * main_width / 37;
        t_point[CLUSTERING2D][i][2] = temp_point[2];
    }
    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += t_point[CLUSTERING2D][i][0];
        min_y += t_point[CLUSTERING2D][i][1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        t_point[CLUSTERING2D][i][0] -= min_x;
        t_point[CLUSTERING2D][i][1] -= min_y;
    }

    for(int i = 0; i < node_num; i++)
    {
        t_point[PASSTHROUGH][i].resize(3);
        t_point[PASSTHROUGH][i][0] = 0;
        t_point[PASSTHROUGH][i][1] = 0;
        t_point[PASSTHROUGH][i][2] = 0;
    }

    t_point_copy = t_point;
}

//初始化与Paper Conference Author data相关的布局算法
void MainWindow::initializeForStrategyP()
{
    const int strategy_num = 10;
    double min_x = 0;
    double min_y = 0;
    vtkSmartPointer<vtkMutableDirectedGraph> vtk_graph1 = vtkSmartPointer<vtkMutableDirectedGraph>::New();
    vtkGraph* vtk_s_graph1;
    vtkSmartPointer<vtkGraphLayout> layout = vtkSmartPointer<vtkGraphLayout>::New();
    vtkSmartPointer<vtkForceDirectedLayoutStrategy> strategy2 = vtkSmartPointer<vtkForceDirectedLayoutStrategy>::New();
    vtkSmartPointer<vtkCircularLayoutStrategy> strategy1 = vtkSmartPointer<vtkCircularLayoutStrategy>::New();
    vtkSmartPointer<vtkClustering2DLayoutStrategy>strategy7 = vtkSmartPointer<vtkClustering2DLayoutStrategy>::New();
    vtkSmartPointer<vtkFast2DLayoutStrategy> strategy4 = vtkSmartPointer<vtkFast2DLayoutStrategy>::New();
    vtkSmartPointer<vtkRandomLayoutStrategy> strategy5 = vtkSmartPointer<vtkRandomLayoutStrategy>::New();
    vtkSmartPointer<vtkSimple2DLayoutStrategy> strategy6 = vtkSmartPointer<vtkSimple2DLayoutStrategy>::New();

    circleLineLayout my_layout(p_graph);
    lineLineLayout my_layout2(p_graph);
    int node_num = p_graph.getNodeNum();
    helloLayout start_layout(node_num);

    double temp_point[3] = {0.0, 0.0, 0.0};

    int edge_num = p_graph.getEdgeNum();
    for(int i = 0; i < node_num; i++)
    {
        vtk_graph1->AddVertex();
    }
    for(int i = 0; i < edge_num; i++)
    {
        vtk_graph1->AddEdge(p_graph.getEdgeNode()[i][0], p_graph.getEdgeNode()[i][1]);
    }
    layout->SetInputData(vtk_graph1);
    layout->SetLayoutStrategy(strategy1);
    layout->Update();
    vtk_s_graph1 = layout->GetOutput();
    p_point.resize(strategy_num);
    for(int i = 0; i < strategy_num; i++)
    {
        p_point[i].resize(node_num);
    }

    //mylayout加入
    my_layout.calcLayout();
    my_layout.getPoint(p_point[MYLAYOUT1]);
    my_layout2.calcLayout();
    my_layout2.getPoint(p_point[MYLAYOUT2]);
    start_layout.calcLayout();
    start_layout.getPoint(p_point[START]);

    //vtklayout加入
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        p_point[CICLE][i].resize(3);
        p_point[CICLE][i][0] = temp_point[0] * main_length / 2.5;
        p_point[CICLE][i][1] = temp_point[1] * main_width / 2.5;
        p_point[CICLE][i][2] = temp_point[2];
    }
    layout->SetLayoutStrategy(strategy2);
    layout->Update();
    vtk_s_graph1 = layout->GetOutput();
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        p_point[FORCE][i].resize(3);
        p_point[FORCE][i][0] = temp_point[0] * main_length / 1.1;
        p_point[FORCE][i][1] = temp_point[1] * main_width / 1.1;
        p_point[FORCE][i][2] = temp_point[2];
    }
    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += p_point[FORCE][i][0];
        min_y += p_point[FORCE][i][1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        p_point[FORCE][i][0] -= min_x;
        p_point[FORCE][i][1] -= min_y;
    }

    //将坐标正规化
    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += p_graph.getNode()[i]->getViewLayout()[0];
        min_y += p_graph.getNode()[i]->getViewLayout()[1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        p_point[PASSTHROUGH][i].resize(3);
        p_point[PASSTHROUGH][i][0] = (p_graph.getNode()[i]->getViewLayout()[0] - min_x) * 8;
        p_point[PASSTHROUGH][i][1] = (p_graph.getNode()[i]->getViewLayout()[1] - min_y) * 4;
        p_point[PASSTHROUGH][i][2] = p_graph.getNode()[i]->getViewLayout()[2];
    }
    layout->SetLayoutStrategy(strategy4);
    layout->Update();
    vtk_s_graph1 = layout->GetOutput();
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        p_point[FAST2D][i].resize(3);
        p_point[FAST2D][i][0] = temp_point[0] * main_length / 3.5;
        p_point[FAST2D][i][1] = temp_point[1] * main_width / 3.5;
        p_point[FAST2D][i][2] = temp_point[2];
    }
    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += p_point[FAST2D][i][0];
        min_y += p_point[FAST2D][i][1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        p_point[FAST2D][i][0] -= min_x;
        p_point[FAST2D][i][1] -= min_y;
    }

    layout->SetLayoutStrategy(strategy5);
    layout->Update();
    vtk_s_graph1 = layout->GetOutput();
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        p_point[RANDOM][i].resize(3);
        p_point[RANDOM][i][0] = temp_point[0] * main_length / 1.2;
        p_point[RANDOM][i][1] = temp_point[1] * main_width / 1.2;
        p_point[RANDOM][i][2] = temp_point[2];
    }
    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += p_point[RANDOM][i][0];
        min_y += p_point[RANDOM][i][1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        p_point[RANDOM][i][0] -= min_x;
        p_point[RANDOM][i][1] -= min_y;
    }

    layout->SetLayoutStrategy(strategy6);
    layout->Update();
    vtk_s_graph1 = layout->GetOutput();
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        p_point[SIMPLE2D][i].resize(3);
        p_point[SIMPLE2D][i][0] = temp_point[0] * main_length / 13.7;
        p_point[SIMPLE2D][i][1] = temp_point[1] * main_width / 13.7;
        p_point[SIMPLE2D][i][2] = temp_point[2];
    }
    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += p_point[SIMPLE2D][i][0];
        min_y += p_point[SIMPLE2D][i][1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        p_point[SIMPLE2D][i][0] -= min_x;
        p_point[SIMPLE2D][i][1] -= min_y;
    }

    layout->SetLayoutStrategy(strategy7);
    layout->Update();
    vtk_s_graph1 = layout->GetOutput();
    for(int i = 0; i < node_num; i++)
    {
        vtk_s_graph1->GetPoint(i, temp_point);
        p_point[CLUSTERING2D][i].resize(3);
        p_point[CLUSTERING2D][i][0] = temp_point[0] * main_length / 3;
        p_point[CLUSTERING2D][i][1] = temp_point[1] * main_width / 2;
        p_point[CLUSTERING2D][i][2] = temp_point[2];
    }
    min_x = 0;
    min_y = 0;
    for(int i = 0; i < node_num; i++)
    {
        min_x += p_point[CLUSTERING2D][i][0];
        min_y += p_point[CLUSTERING2D][i][1];
    }
    min_x /= node_num;
    min_y /= node_num;
    for(int i = 0; i < node_num; i++)
    {
        p_point[CLUSTERING2D][i][0] -= min_x;
        p_point[CLUSTERING2D][i][1] -= min_y;
    }
    p_point_copy = p_point;
}


//设置各种向量的大小
void MainWindow::setPointSize(int size)
{
    for(int i = 0; i < 2; i++)               //2,3均为该数据集相关参数，可根据数据集不同来修改,2代表两种数据,3代表总度数，出度以及入度
    {
        for(int j = 0; j < 3; j++)
        {
            point_weight[i][j].resize(size);
            point_num_edge_state[i][j].resize(size);
        }
    }
    point_state_t.resize(size);
    point_type.resize(size);
    velocity.resize(size);
    point_state.resize(size);
    point_highlight.resize(size);
    temp_point.resize(size);
}


//放大缩小
void MainWindow::ChangeScale(double scale)
{
    my_scale *= scale;
    if(my_scale < 0.1)
    {
        if(full_big == 0)
        {
            full_big = 1;
            my_last_scale = my_scale / scale;
        }
        else
        {
            full_big = 2;
        }
        my_scale = 0.1;
        return;
    }
    else if(my_scale > 18)
    {
        if(full_big == 0)
        {
            full_big = 1;
            my_last_scale = my_scale / scale;
        }
        else
        {
            full_big = 2;
        }
        my_scale = 18;
        return;
    }
    full_big = 0;
    length = int(length * scale);
    width = int(width * scale);
    height = int(height * scale);
    radis *= scale;
}


//Event List
void MainWindow::keyPressEvent(QKeyEvent * ev)
{
    if(is_in_start)
        return;
    switch(ev->key())
    {
    //放大键
    case Qt::Key_Q:ChangeScale(1.1);
        if(full_big == 0)
        {
            setOpoint(Opoint[0] + 0.1 * (Opoint[0] + main_length / 2 - QPoint(cursor().pos()).x()), Opoint[1] + 0.1 * (Opoint[1] + main_width / 2 - QPoint(cursor().pos()).y()));
            update();
        }
        else if(full_big == 2)
            return;
        else
        {
            setOpoint(Opoint[0] + (my_scale / my_last_scale - 1) * (Opoint[0] + main_length / 2 - QPoint(cursor().pos()).x()), Opoint[1] + (my_scale / my_last_scale - 1) * (Opoint[1] + main_width / 2 - QPoint(cursor().pos()).y()));
            update();
        }
       break;
    //缩小键
    case Qt::Key_R:ChangeScale(0.9);
        if(full_big == 0)
        {
            setOpoint(Opoint[0] - 0.1 * (Opoint[0] + main_length / 2 - QPoint(cursor().pos()).x()), Opoint[1] - 0.1 * (Opoint[1] + main_width / 2 - QPoint(cursor().pos()).y()));
            update();
        }
        else if(full_big == 2)
            return;
        else
        {
            setOpoint(Opoint[0] - (my_scale / my_last_scale - 1) * (Opoint[0] + main_length / 2 - QPoint(cursor().pos()).x()), Opoint[1] - (my_scale / my_last_scale - 1) * (Opoint[1] + main_width / 2 - QPoint(cursor().pos()).y()));
            update();
        }
       break;
    //左移键
    case Qt::Key_A:
        Opoint[0] += 200;
        update();
        break;
    //右移键
    case Qt::Key_D:
        Opoint[0] -= 200;
        update();
        break;
    //下移键
    case Qt::Key_S:
        Opoint[1] -= 200;
        update();
        break;
    //上移键
    case Qt::Key_W:
        Opoint[1] += 200;
        update();
        break;
    //单点拖移模式开启键
    case Qt::Key_B:
        if(is_single)
        {
            is_single = false;
            update();
        }
        else
        {
            is_single = true;
            update();
        }
        break;
    //垂直滚动条控制键，按下可用滚轮控制垂直滚动条
    case Qt::Key_V:
        is_key_v_pressed = true;
        break;
    //水平滚动条控制键，按下可用滚轮控制水平滚动条
    case Qt::Key_H:
        is_key_h_pressed = true;
        break;
    //局部分析模式开启键，按下可忽略其他点，再按下可取消功能
    case Qt::Key_C:       
        if(!is_in_local)
        {
            if(id_select_point == -1)
                return;
            is_in_local = true;
            if(!has_weight)
            {
                if(is_single && id_select_point)
                {
                    point_state_copy = point_state;
                }
                int node_num = p_graph.getNodeNum();
                for(int i = 0; i < node_num; i++)
                {
                    point_state[i] = false;
                }
                int neighbor_in_number = p_graph.getInNum(id_select_point);
                int neighbor_out_number = p_graph.getOutNum(id_select_point);
                for(int j = 0; j < neighbor_in_number; j++)
                {
                    point_state[p_graph.getNodeIn()[id_select_point][j]] = true;
                }
                for(int j = 0; j < neighbor_out_number; j++)
                {
                    point_state[p_graph.getNodeOut()[id_select_point][j]] = true;
                }
                point_state[id_select_point] = true;
                update();
                }
             else
             {
                 if(is_single && id_select_point)
                 {
                     point_state_t_copy = point_state_t;
                 }
                 int node_num = t_graph.getNodeNum();
                 for(int i = 0; i < node_num; i++)
                 {
                     point_state_t[i] = false;
                 }
                 int neighbor_in_number = t_graph.getInNum(id_select_point);
                 int neighbor_out_number = t_graph.getOutNum(id_select_point);
                 for(int j = 0; j < neighbor_in_number; j++)
                 {
                     point_state_t[t_graph.getNodeIn()[id_select_point][j]] = true;
                 }
                 for(int j = 0; j < neighbor_out_number; j++)
                 {
                     point_state_t[t_graph.getNodeOut()[id_select_point][j]] = true;
                 }
                 point_state_t[id_select_point] = true;
                 update();
             }
             break;
        }
        else
        {
            is_in_local = false;
            if(!has_weight)
            {
                if(is_single)
                {
                    point_state = point_state_copy;
                }
                update();
            }
            else
            {
                if(is_single)
                {
                    point_state_t = point_state_t_copy;
                }
                update();
            }

        }
    }
}


//键盘释放事件
void MainWindow::keyReleaseEvent(QKeyEvent * ev)
{
    switch(ev->key())
    {
    //释放滚动条，滚轮重新控制放大缩小
    case Qt::Key_V:
        is_key_v_pressed = false;
        break;
    case Qt::Key_H:
        is_key_h_pressed = false;
        break;
    }
}


//鼠标按下事件
void MainWindow::mousePressEvent(QMouseEvent * ev)
{
    if(is_in_start)
        return;
    int candidate1 = -1;
    int candidate2 = -1;
    temp_x = ev->pos().x();
    temp_y = ev->pos().y();
    //paper下的鼠标事件，topic下相同
    if(!has_weight)
    {
        //鼠标左键事件
        if(ev->button() == Qt::LeftButton)
        {
            if(highlight_number > 0)
            {
                highlight_number = 0;
                is_highlight = false;
                update();
                return;
            }
            //设置为鼠标左键已按下，若鼠标在点区，则拖点，次之在边区，拖边，次之拖图
            is_mouse_pressed = true;
            //寻找鼠标是否在点区
            int len = p_point[0].size();
            int i;
            for(i = 0; i < len; i++)
            {
                if(isInCicle(ev->pos().x(), ev->pos().y(), calcX(my_scale * p_point[strategy][i][0]), calcY(my_scale * p_point[strategy][i][1]), radis))
                {
                    if(candidate1 == -1)
                    {
                        candidate1 = i;
                    }
                    else if(candidate2 == -1)
                    {
                        candidate2 = i;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if(candidate1 == -1)
            {
                if(id_select_edge != -1)
                {
                    is_dragging = true;
                    setCursor(Qt::ClosedHandCursor);
                }
                return;
            }
            else if(candidate2 == -1)
            {
                is_dragging = true;
                setCursor(Qt::ClosedHandCursor);
                id_move_point = candidate1;
            }
            else
            {
                if(calcInstance(calcX(my_scale * p_point[strategy][candidate1][0]),ev->pos().x(), calcY(my_scale * p_point[strategy][candidate1][1]), ev->pos().y()) >
                        calcInstance(calcX(my_scale * p_point[strategy][candidate2][0]),ev->pos().x(), calcY(my_scale * p_point[strategy][candidate2][1]), ev->pos().y()))
                {
                    is_dragging = true;
                    setCursor(Qt::ClosedHandCursor);
                    id_move_point = candidate2;
                }
                else
                {
                    is_dragging = true;
                    setCursor(Qt::ClosedHandCursor);
                    id_move_point = candidate1;
                }
            }
        }
        //鼠标右键事件
        else if(ev->button() == Qt::RightButton && !is_in_local)
        {
            //存储当前点坐标，为拉索准备
            if(!is_highlight && highlight_number == 0)
            {
                pull_vector.push_back(QPoint(ev->pos().x(), ev->pos().y()));
                is_pull = true;  //将状态至于拉索模式
            }
            else  //已拉索，可以拖移所有选中的点
            {
                temp_x_highlight = ev->pos().x();
                temp_y_highlight = ev->pos().y();
                is_highlight = true;
            }
        }
    }
    else
    {
        if(ev->button() == Qt::LeftButton)
        {
            if(highlight_number > 0)
            {
                highlight_number = 0;
                is_highlight = false;
                update();
                return;
            }
            is_mouse_pressed = true;
            temp_x = ev->pos().x();
            temp_y = ev->pos().y();
            int len = p_point[0].size();
            int i;

            for(i = 0; i < len; i++)
            {
                if(isInCicle(ev->pos().x(), ev->pos().y(), calcX(my_scale * t_point[strategy][i][0]), calcY(my_scale * t_point[strategy][i][1]), radis))
                {
                    if(candidate1 == -1)
                    {
                        candidate1 = i;
                    }
                    else if(candidate2 == -1)
                    {
                        candidate2 = i;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if(candidate1 == -1)
            {
                if(id_select_edge != -1)
                {
                    is_dragging = true;
                    setCursor(Qt::ClosedHandCursor);
                }
                return;
            }
            else if(candidate2 == -1)
            {
                is_dragging = true;
                setCursor(Qt::ClosedHandCursor);
                id_move_point = candidate1;
            }
            else
            {
                if(calcInstance(calcX(my_scale * t_point[strategy][candidate1][0]),ev->pos().x(), calcY(my_scale * t_point[strategy][candidate1][1]), ev->pos().y()) >
                        calcInstance(calcX(my_scale * t_point[strategy][candidate2][0]),ev->pos().x(), calcY(my_scale * t_point[strategy][candidate2][1]), ev->pos().y()))
                {
                    is_dragging = true;
                    id_move_point = candidate2;
                    setCursor(Qt::ClosedHandCursor);
                }
                else
                {
                    is_dragging = true;
                    setCursor(Qt::ClosedHandCursor);
                    id_move_point = candidate1;
                }
            }
        }
        else if(ev->button() == Qt::RightButton && !is_in_local)
        {
            if(!is_highlight && highlight_number == 0)
            {
                is_pull = true;
                temp_x_highlight = ev->pos().x();
                temp_y_highlight = ev->pos().y();
            }
            else if(!is_highlight)
            {
                temp_x_highlight = ev->pos().x();
                temp_y_highlight = ev->pos().y();
                is_highlight = true;
            }
        }        
    }
}


//鼠标双击事件
void MainWindow::mouseDoubleClickEvent(QMouseEvent * ev)
{
    if(is_in_start)
        return;
    if(!has_weight)
    {
        bool is_point = false;
        //左键双击，显示属性
        if(ev->button() == Qt::LeftButton)
        {
            int len = p_point[0].size();
            int i;
            for(i = 0; i < len; i++)
            {
                if(isInCicle(ev->pos().x(), ev->pos().y(), calcX(my_scale * p_point[strategy][i][0]), calcY(my_scale * p_point[strategy][i][1]), radis))
                {
                    is_point = true;
                    break;
                }
            }
            if(is_point)
            {
                listPaperInformation(i);
            }
            else
                return;
        }
        //右键双击，将已拉索的点外的点过滤，或者恢复其他的点
        else if(ev->button() == Qt::RightButton)
        {
            //过滤
            if(highlight_number > 0)
            {
                highlight_number = 0;
                point_state_copy_fil.push_back(point_state);
                point_state = point_highlight;
            }
            //恢复
            else
            {
                if(point_state_copy_fil.size() >= 1)
                {
                    point_state = point_state_copy_fil[point_state_copy_fil.size() - 1];
                    point_state_copy_fil.pop_back();
                }
            }
        }
    }
    else
    {
        if(ev->button() == Qt::LeftButton)
        {
            bool is_point = false;
            int len = t_point[0].size();
            int i;
            for(i = 0; i < len; i++)
            {
                if(isInCicle(ev->pos().x(), ev->pos().y(), calcX(my_scale * t_point[strategy][i][0]), calcY(my_scale * t_point[strategy][i][1]), radis))
                {
                    is_point = true;
                    break;
                }
            }
            if(is_point)
            {
                listPaperInformation(i);
            }
            else
                return;
        }
        else if(ev->button() == Qt::RightButton)
        {
            if(highlight_number > 0)
            {
                highlight_number = 0;
                point_state_t_copy_fil.push_back(point_state_t);
                point_state_t = point_highlight;
            }
            else
            {
                if(point_state_t_copy_fil.size() >= 1)
                {
                    point_state_t = point_state_t_copy_fil[point_state_t_copy_fil.size() - 1];
                    point_state_t_copy_fil.pop_back();
                }
            }
        }
    }
}


//判断一个位置是否在某条边上，前四个参数代表边，后两个为位置
bool MainWindow::inEdgeArea(double src_x, double src_y, double des_x, double des_y, double pos_x, double pos_y)
{
    if(!(fabs((des_y - pos_y) * (pos_x - src_x) - (des_x - pos_x) * (pos_y - src_y)) <= 1000 * my_scale))
    {
        return false;
    }
    else  //防止点在边的延长线上
    {
        if((src_x - pos_x) * (des_x - pos_x) < 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}


//虚拟坐标到画布坐标的变换
int MainWindow::calcX(int x)
{
    return (x + Opoint[0] + main_length / 2);
}

int MainWindow::calcY(int y)
{
    return (y + Opoint[1] + main_width / 2);
}


//某位置是否在点区
bool MainWindow::isInCicle(int tx, int ty, int x, int y, int r)
{
    if(((tx - x) * (tx - x) + (ty - y) * (ty - y)) > r * r)
        return false;
    else
        return true;
}


//计算两个点的欧几里得距离
double MainWindow::calcInstance(double x1, double x2, double y1, double y2)
{
    return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


//展示点的属性，i为选中节点的id
void MainWindow::listPaperInformation(int i)
{
    if(!has_weight)
    {
        InformationDialog dlg(*(p_graph.getNode()[i]));
        dlg.exec();
    }
    else
    {
        *(t_graph.getNode()[i]);
        topicdialog dlg(t_graph, *(t_graph.getNode()[i]));
        dlg.exec();
    }
}


//绘制事件，分为各种模式
void MainWindow::paintEvent(QPaintEvent * ev)
{
    QPainter painter(this);
    PointColor my_color;
    QPen pen;
    //画边用的点
    QPointF point1;
    QPointF point2;
    QFont my_font;
    vector<int> temp_pair;
    painter.save();
    int node_num = p_point[0].size();

    //正在拉索模式
    if(is_pull && !is_in_start)
    {
        pen.setColor(QColor(255,0,0,255));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawPolygon(poly);
        painter.translate(Opoint[0] + main_length / 2, Opoint[1] + main_width / 2);
        pen.setColor(QColor(0,0,0,232));
        pen.setWidth(1);
        painter.setPen(pen);
        if(!has_weight)
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state[i])
                    continue;
                if(point_highlight[i])
                {
                    my_color.setColor(int(point_weight[0][0][i]), point_type[i], 200);
                    painter.setBrush(my_color.getColor());
                    painter.drawEllipse(my_scale * p_point[strategy][i][0] - radis * 2, my_scale * p_point[strategy][i][1] - radis * 2,
                            radis * 4, radis * 4);
                }
                else
                {
                    my_color.setColor(int(point_weight[0][0][i]), point_type[i], 200);
                    painter.setBrush(my_color.getColor());
                    painter.drawEllipse(my_scale * p_point[strategy][i][0] - radis, my_scale * p_point[strategy][i][1] - radis,
                            radis * 2, radis * 2);
                }
            }
            int edge_num = p_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(point_state[p_graph.getEdgeNode()[j][0]] && point_state[p_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,edge_color));
                    painter.setPen(pen);
                    point1.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
        else
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state_t[i])
                    continue;
                if(point_highlight[i])
                {
                    my_color.setColor(int(point_weight[1][0][i]), 0, 200);
                    painter.setBrush(my_color.getColor());
                    painter.drawEllipse(my_scale * t_point[strategy][i][0] - radis * 2, my_scale * t_point[strategy][i][1] - radis * 2,
                            radis * 4, radis * 4);
                }
                else
                {
                    my_color.setColor(int(point_weight[1][0][i]), 0, 200);
                    painter.setBrush(my_color.getColor());
                    painter.drawEllipse(my_scale * t_point[strategy][i][0] - radis, my_scale * t_point[strategy][i][1] - radis,
                            radis * 2, radis * 2);
                }
            }
            int edge_num = t_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(!edge_state_t[j])
                    continue;
                if(point_state_t[t_graph.getEdgeNode()[j][0]] && point_state_t[t_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230, edge_color));
                    painter.setPen(pen);
                    point1.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
        painter.restore();
        return;
    }
    painter.translate(Opoint[0] + main_length / 2, Opoint[1] + main_width / 2);       

    //局部分析模式，只显示这个点和与其相连的边
    if(is_in_local && is_single && !is_in_start && !in_cartoon)
    {
        if(!has_weight)
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state[i])
                    continue;
                my_color.setColor(int(point_weight[0][0][i]), point_type[i]);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * p_point[strategy][i][0] - radis, my_scale * p_point[strategy][i][1] - radis,
                        radis * 2, radis * 2);
            }
            if(id_select_point != -1 && point_state[id_select_point])
            {
                pen.setColor(QColor(230,230,230,232));
                painter.setPen(pen);
                my_font.setBold(true);
                my_font.setPointSize(9 * my_scale);
                painter.setFont(my_font);
                painter.drawText(my_scale * p_point[strategy][id_select_point][0] , my_scale * p_point[strategy][id_select_point][1] - radis * 4,
                        QString::number(p_graph.getNode()[id_select_point]->getIdOfNode(), 10));
                pen.setColor(QColor(0,0,0,232));
                painter.setPen(pen);
                my_color.setColor(int(point_weight[0][0][id_select_point]), point_type[id_select_point]);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * p_point[strategy][id_select_point][0] - radis * 2, my_scale * p_point[strategy][id_select_point][1] - radis * 2,
                        radis * 4, radis * 4);
            }
            int edge_num = p_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(point_state[p_graph.getEdgeNode()[j][0]] && point_state[p_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,edge_color));
                    painter.setPen(pen);
                    point1.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
        else
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state_t[i])
                    continue;
                my_color.setColor(int(point_weight[1][0][i]), 0);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * t_point[strategy][i][0] - radis, my_scale * t_point[strategy][i][1] - radis,
                        radis * 2, radis * 2);
            }
            if(id_select_point != -1 && point_state_t[id_select_point])
            {
                pen.setColor(QColor(230,230,230,232));
                painter.setPen(pen);
                my_font.setBold(true);
                my_font.setPointSize(9 * my_scale);
                painter.setFont(my_font);
                painter.drawText(my_scale * t_point[strategy][id_select_point][0] , my_scale * t_point[strategy][id_select_point][1] - radis * 4,
                        QString::number(t_graph.getNode()[id_select_point]->getIdOfNode(), 10));
                pen.setColor(QColor(0,0,0,0));
                painter.setPen(pen);
                my_color.setColor(int(point_weight[1][0][id_select_point]), 0);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * t_point[strategy][id_select_point][0] - radis * 2, my_scale * t_point[strategy][id_select_point][1] - radis * 2,
                        radis * 4, radis * 4);
            }
            int edge_num = t_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(!edge_state_t[j])
                    continue;
                if(point_state_t[t_graph.getEdgeNode()[j][0]] && point_state_t[t_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,edge_color));
                    painter.setPen(pen);
                    point1.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
        if(id_select_edge != -1)
        {            
            if(!has_weight && point_state[p_graph.getEdgeNode()[id_select_edge][1]]
                    && point_state[p_graph.getEdgeNode()[id_select_edge][0]])
            {
                temp_pair.push_back(p_graph.getEdgeNode()[id_select_edge][1]);
                temp_pair.push_back(p_graph.getEdgeNode()[id_select_edge][0]);
                pen.setColor(QColor(255,0,0,232));
                painter.setPen(pen);
                my_font.setBold(true);
                my_font.setPointSize(9 * my_scale);
                painter.setFont(my_font);
                painter.drawText(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][0] , my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][1] + radis * 4, "source");
                painter.drawText(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][0] , my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][1] + radis * 4, "target");
                if(p_graph.getNodeToEdge().find(temp_pair) != p_graph.getNodeToEdge().end())
                {
                    painter.drawText(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][0] , my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][1] - 9 * my_scale, "target");
                    painter.drawText(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][0] , my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][1] - 9 * my_scale, "source");

                }
                pen.setColor(QColor(0,0,0,232));
                painter.setPen(pen);
                painter.setBrush(QColor(255,0,0,232));
                painter.drawEllipse(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][0] - radis * 2, my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][1] - radis * 2,
                        radis * 4, radis * 4);
                painter.drawEllipse(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][0] - radis * 2, my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][1] - radis * 2,
                        radis * 4, radis * 4);
                pen.setColor(QColor(255,0,0,232));
                pen.setWidth(3);
                painter.setPen(pen);
                point1.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][0]);
                point1.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][1]);
                point2.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][0]);
                point2.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][1]);
                painter.drawLine(point1, point2);
                pen.setWidth(1);
                painter.setPen(pen);
            }
            else if(has_weight && edge_state_t[id_select_edge]
                    && point_state_t[t_graph.getEdgeNode()[id_select_edge][1]]
                    && point_state_t[t_graph.getEdgeNode()[id_select_edge][0]])
            {
                pen.setColor(QColor(255,0,0,232));
                painter.setPen(pen);
                my_font.setBold(true);
                my_font.setPointSize(9 * my_scale);
                painter.setFont(my_font);
                painter.drawText((my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][0] + my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][0]) / 2,
                        (my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][1] - radis * 4 + my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][1] - radis * 4) / 2,
                        QString::number(t_graph.getEdge()[id_select_edge]->getWeight()));
                pen.setColor(QColor(0,0,0,0));
                painter.setPen(pen);
                painter.setBrush(QColor(255,0,0,232));
                painter.drawEllipse(my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][0] - radis * 2, my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][1] - radis * 2,
                        radis * 4, radis * 4);
                painter.setBrush(QColor(255,0,0,232));
                painter.drawEllipse(my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][0] - radis * 2, my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][1] - radis * 2,
                        radis * 4, radis * 4);
                pen.setColor(QColor(255,0,0,232));
                pen.setWidth(3);
                painter.setPen(pen);
                point1.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][0]);
                point1.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][1]);
                point2.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][0]);
                point2.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][1]);
                painter.drawLine(point1, point2);
                pen.setWidth(1);
                painter.setPen(pen);
            }
        }

        painter.restore();
        return;
    }

    //数据切换模式
    if(data_change > 0 && !is_in_start)
    {
        if(!has_weight)
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state[i])
                    continue;
                my_color.setColor(int(point_weight[0][0][i]), point_type[i], alpha_degree * 1.3);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * p_point[strategy][i][0] - radis, my_scale * p_point[strategy][i][1] - radis,
                        radis * 2, radis * 2);
            }           
            int edge_num = p_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(point_state[p_graph.getEdgeNode()[j][0]] && point_state[p_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,alpha_degree));
                    painter.setPen(pen);
                    point1.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
        else
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state_t[i])
                    continue;
                my_color.setColor(int(point_weight[1][0][i]), 0, alpha_degree * 1.3);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * t_point[strategy][i][0] - radis, my_scale * t_point[strategy][i][1] - radis,
                        radis * 2, radis * 2);
            }
            int edge_num = t_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(!edge_state_t[j])
                    continue;
                if(point_state_t[t_graph.getEdgeNode()[j][0]] && point_state_t[t_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,alpha_degree));
                    painter.setPen(pen);
                    point1.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
        painter.restore();
        return;
    }

    //高亮态模式
    if(highlight_number > 0 && !is_in_start)
    {
        if(!has_weight)
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state[i])
                    continue;
                if(point_highlight[i])
                {
                    my_color.setColor(int(point_weight[0][0][i]), point_type[i], 200);
                    painter.setBrush(my_color.getColor());
                    painter.drawEllipse(my_scale * p_point[strategy][i][0] - radis * 2, my_scale * p_point[strategy][i][1] - radis * 2,
                            radis * 4, radis * 4);
                }
                else
                {
                    my_color.setColor(int(point_weight[0][0][i]), point_type[i], 200);
                    painter.setBrush(my_color.getColor());
                    painter.drawEllipse(my_scale * p_point[strategy][i][0] - radis, my_scale * p_point[strategy][i][1] - radis,
                            radis * 2, radis * 2);
                }
            }
            int edge_num = p_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(point_state[p_graph.getEdgeNode()[j][0]] && point_state[p_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,edge_color));
                    painter.setPen(pen);
                    point1.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
        else
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state_t[i])
                    continue;
                if(point_highlight[i])
                {
                    my_color.setColor(int(point_weight[1][0][i]), 0, 200);
                    painter.setBrush(my_color.getColor());
                    painter.drawEllipse(my_scale * t_point[strategy][i][0] - radis * 2, my_scale * t_point[strategy][i][1] - radis * 2,
                            radis * 4, radis * 4);
                }
                else
                {
                    my_color.setColor(int(point_weight[1][0][i]), 0, 200);
                    painter.setBrush(my_color.getColor());
                    painter.drawEllipse(my_scale * t_point[strategy][i][0] - radis, my_scale * t_point[strategy][i][1] - radis,
                            radis * 2, radis * 2);
                }
            }
            int edge_num = t_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(!edge_state_t[j])
                    continue;
                if(point_state_t[t_graph.getEdgeNode()[j][0]] && point_state_t[t_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,edge_color));
                    painter.setPen(pen);
                    point1.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
        painter.restore();
        return;
    }

    //选中模式，被选中的点会放大
    if(id_select_point != -1 && !is_single && !is_in_start)
    {
        if(!has_weight)
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state[i])
                    continue;
                my_color.setColor(int(point_weight[0][0][i]), point_type[i]);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * p_point[strategy][i][0] - radis, my_scale * p_point[strategy][i][1] - radis,
                        radis * 2, radis * 2);
            }
            if(point_state[id_select_point])
            {
                pen.setColor(QColor(230,230,230,232));
                painter.setPen(pen);
                my_font.setBold(true);
                my_font.setPointSize(9 * my_scale);
                painter.setFont(my_font);
                painter.drawText(my_scale * p_point[strategy][id_select_point][0] , my_scale * p_point[strategy][id_select_point][1] - radis * 4,
                        QString::number(p_graph.getNode()[id_select_point]->getIdOfNode(), 10));
                pen.setColor(QColor(0,0,0,0));
                painter.setPen(pen);
                my_color.setColor(38, point_type[id_select_point]);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * p_point[strategy][id_select_point][0] - radis * 2, my_scale * p_point[strategy][id_select_point][1] - radis * 2,
                        radis * 4, radis * 4);
            }
            else
            {
                setCursor(Qt::ArrowCursor);
            }
            int edge_num = p_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(point_state[p_graph.getEdgeNode()[j][0]] && point_state[p_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,edge_color));
                    painter.setPen(pen);
                    point1.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
        else
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state_t[i])
                    continue;
                my_color.setColor(int(point_weight[1][0][i]), 0);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * t_point[strategy][i][0] - radis, my_scale * t_point[strategy][i][1] - radis,
                        radis * 2, radis * 2);
            }
            if(point_state_t[id_select_point])
            {
                pen.setColor(QColor(230,230,230,232));
                painter.setPen(pen);
                my_font.setBold(true);
                my_font.setPointSize(9 * my_scale);
                painter.setFont(my_font);
                painter.drawText(my_scale * t_point[strategy][id_select_point][0] , my_scale * t_point[strategy][id_select_point][1] - radis * 4,
                        QString::number(t_graph.getNode()[id_select_point]->getIdOfNode(), 10));
                pen.setColor(QColor(0,0,0,0));
                painter.setPen(pen);
                my_color.setColor(int(point_weight[1][0][id_select_point]), 0);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * t_point[strategy][id_select_point][0] - radis * 2, my_scale * t_point[strategy][id_select_point][1] - radis * 2,
                        radis * 4, radis * 4);
            }
            else
            {
                setCursor(Qt::ArrowCursor);
            }
            int edge_num = t_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(!edge_state_t[j])
                    continue;
                if(point_state_t[t_graph.getEdgeNode()[j][0]] && point_state_t[t_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,edge_color));
                    painter.setPen(pen);
                    point1.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
        painter.restore();
        return;
    }

    //单点拖动模式，拖动时只显示这个点和与其相连的边
    if(id_select_point != -1 && is_single && !is_in_start)
    {
        if(!has_weight)
        {
            if(!point_state[id_select_point])
            {
                setCursor(Qt::ArrowCursor);
                painter.restore();
                return;
            }
            int neighbor_in_number = p_graph.getInNum(id_select_point);
            int neighbor_out_number = p_graph.getOutNum(id_select_point);
            for(int j = 0; j < neighbor_in_number; j++)
            {
                my_color.setColor(38 , point_type[p_graph.getNodeIn()[id_select_point][j]]);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * p_point[strategy][p_graph.getNodeIn()[id_select_point][j]][0] - radis,
                        my_scale * p_point[strategy][p_graph.getNodeIn()[id_select_point][j]][1] - radis,
                            radis * 2, radis * 2);
            }
            for(int j = 0; j < neighbor_out_number; j++)
            {
                my_color.setColor(38 , point_type[p_graph.getNodeOut()[id_select_point][j]]);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * p_point[strategy][p_graph.getNodeOut()[id_select_point][j]][0] - radis,
                        my_scale * p_point[strategy][p_graph.getNodeOut()[id_select_point][j]][1] - radis,
                            radis * 2, radis * 2);
            }
            my_color.setColor(38, point_type[id_select_point]);
            painter.setBrush(my_color.getColor());
            painter.drawEllipse(my_scale * p_point[strategy][id_select_point][0] - radis * 2, my_scale * p_point[strategy][id_select_point][1] - radis * 2,
                        radis * 4, radis * 4);
            int edge_num = p_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(p_graph.getEdgeNode()[j][0] == id_select_point || p_graph.getEdgeNode()[j][1] == id_select_point)
                {
                    if(point_state[p_graph.getEdgeNode()[j][0]] && point_state[p_graph.getEdgeNode()[j][1]])
                    {
                        pen.setColor(QColor(230,230,230,edge_color));
                        painter.setPen(pen);
                        point1.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][0]);
                        point1.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][1]);
                        point2.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][0]);
                        point2.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][1]);
                        painter.drawLine(point1, point2);
                    }
                }
            }
        }
        else
        {
            if(!point_state[id_select_point])
            {
                setCursor(Qt::ArrowCursor);
                painter.restore();
                return;
            }
            int neighbor_in_number = t_graph.getInNum(id_select_point);
            int neighbor_out_number = t_graph.getOutNum(id_select_point);
            for(int j = 0; j < neighbor_in_number; j++)
            {
                my_color.setColor(int(point_weight[1][0][t_graph.getNodeIn()[id_select_point][j]]), 0);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * t_point[strategy][t_graph.getNodeIn()[id_select_point][j]][0] - radis,
                        my_scale * t_point[strategy][t_graph.getNodeIn()[id_select_point][j]][1] - radis,
                            radis * 2, radis * 2);
            }
            for(int j = 0; j < neighbor_out_number; j++)
            {
                my_color.setColor(int(point_weight[1][0][t_graph.getNodeIn()[id_select_point][j]]), 0);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * t_point[strategy][t_graph.getNodeOut()[id_select_point][j]][0] - radis,
                        my_scale * t_point[strategy][t_graph.getNodeOut()[id_select_point][j]][1] - radis,
                            radis * 2, radis * 2);
            }
            my_color.setColor(38, point_type[id_select_point]);
            painter.setBrush(my_color.getColor());
            painter.drawEllipse(my_scale * t_point[strategy][id_select_point][0] - radis * 2, my_scale * t_point[strategy][id_select_point][1] - radis * 2,
                        radis * 4, radis * 4);
            int edge_num = t_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(!edge_state_t[j])
                    continue;
                if(t_graph.getEdgeNode()[j][0] == id_select_point || t_graph.getEdgeNode()[j][1] == id_select_point)
                {
                    if(point_state_t[t_graph.getEdgeNode()[j][0]] && point_state_t[t_graph.getEdgeNode()[j][1]])
                    {
                        pen.setColor(QColor(230,230,230,edge_color));
                        painter.setPen(pen);
                        point1.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][0]);
                        point1.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][1]);
                        point2.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][0]);
                        point2.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][1]);
                        painter.drawLine(point1, point2);
                    }
                }
            }
        }

        painter.restore();
        return;
    }

    //切换layout动画模式
    if(in_cartoon && !is_in_start)
    {
        if(!has_weight)
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state[i])
                    continue;
                my_color.setColor(int(point_weight[0][0][i]), point_type[i]);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * temp_point[i][0] - radis , my_scale * temp_point[i][1] - radis,
                        radis * 2, radis * 2);
            }
            int edge_num = p_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(point_state[p_graph.getEdgeNode()[j][0]] && point_state[p_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,edge_color));
                    painter.setPen(pen);
                    point1.setX(my_scale * temp_point[p_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * temp_point[p_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * temp_point[p_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * temp_point[p_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
        else
        {            
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state_t[i])
                    continue;
                my_color.setColor(int(point_weight[1][0][i]), 0);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * temp_point[i][0] - radis , my_scale * temp_point[i][1] - radis,
                        radis * 2, radis * 2);
            }
            int edge_num = t_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(!edge_state_t[j])
                    continue;
                if(point_state_t[t_graph.getEdgeNode()[j][0]] && point_state_t[t_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,edge_color));
                    painter.setPen(pen);
                    point1.setX(my_scale * temp_point[t_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * temp_point[t_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * temp_point[t_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * temp_point[t_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
    }

    //普通绘制模式
    else
    {
        //初始界面
        if(is_in_start)
        {
            if(!has_weight)
            {
                for(int i = 0; i < node_num; i++)
                {
                    if(!point_state[i])
                        continue;
                    my_color.setColor(int(point_weight[0][0][i]), point_type[i]);
                    painter.setBrush(my_color.getColor());
                    painter.drawEllipse(my_scale * p_point[strategy][i][0] - radis, my_scale * p_point[strategy][i][1] - radis,
                            radis * 2, radis * 2);
                }
                int edge_num = p_graph.getEdgeNum();
                for(int j = 0; j < edge_num; j++)
                {
                    pen.setColor(QColor(230,230,230,alpha_start));
                    painter.setPen(pen);
                    point1.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
            else
            {
                for(int i = 0; i < node_num; i++)
                {
                    if(!point_state_t[i])
                        continue;
                    my_color.setColor(int(point_weight[1][0][i]), 0);
                    painter.setBrush(my_color.getColor());
                    painter.drawEllipse(my_scale * t_point[strategy][i][0] - radis, my_scale * t_point[strategy][i][1] - radis,
                            radis * 2, radis * 2);
                }
                int edge_num = t_graph.getEdgeNum();
                for(int j = 0; j < edge_num; j++)
                {

                    pen.setColor(QColor(230,230,230,alpha_start));
                    painter.setPen(pen);
                    point1.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
            painter.restore();
            return;
        }
        if(!has_weight)
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state[i])
                    continue;
                my_color.setColor(int(point_weight[0][0][i]), point_type[i]);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * p_point[strategy][i][0] - radis, my_scale * p_point[strategy][i][1] - radis,
                        radis * 2, radis * 2);
            }
            int edge_num = p_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(point_state[p_graph.getEdgeNode()[j][0]] && point_state[p_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,edge_color));
                    painter.setPen(pen);
                    point1.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
        else
        {           
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state_t[i])
                    continue;
                my_color.setColor(int(point_weight[1][0][i]), 0);
                painter.setBrush(my_color.getColor());
                painter.drawEllipse(my_scale * t_point[strategy][i][0] - radis, my_scale * t_point[strategy][i][1] - radis,
                        radis * 2, radis * 2);
            }
            int edge_num = t_graph.getEdgeNum();
            for(int j = 0; j < edge_num; j++)
            {
                if(!edge_state_t[j])
                    continue;
                if(point_state_t[t_graph.getEdgeNode()[j][0]] && point_state_t[t_graph.getEdgeNode()[j][1]])
                {
                    pen.setColor(QColor(230,230,230,edge_color));
                    painter.setPen(pen);
                    point1.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][0]);
                    point1.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][0]][1]);
                    point2.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][0]);
                    point2.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[j][1]][1]);
                    painter.drawLine(point1, point2);
                }
            }
        }
    }

    if(id_select_edge != -1)
    {
        if(!has_weight && point_state[p_graph.getEdgeNode()[id_select_edge][1]]
                && point_state[p_graph.getEdgeNode()[id_select_edge][0]])
        {
            temp_pair.push_back(p_graph.getEdgeNode()[id_select_edge][1]);
            temp_pair.push_back(p_graph.getEdgeNode()[id_select_edge][0]);
            pen.setColor(QColor(255,0,0,232));
            painter.setPen(pen);
            my_font.setBold(true);
            my_font.setPointSize(9 * my_scale);
            painter.setFont(my_font);
            painter.drawText(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][0] , my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][1] + radis * 4, "source");
            painter.drawText(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][0] , my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][1] + radis * 4, "target");
            if(p_graph.getNodeToEdge().find(temp_pair) != p_graph.getNodeToEdge().end())
            {
                painter.drawText(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][0] , my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][1] - 9 * my_scale, "target");
                painter.drawText(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][0] , my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][1] - 9 * my_scale, "source");

            }
            pen.setColor(QColor(0,0,0,0));
            painter.setPen(pen);
            painter.setBrush(QColor(255,0,0,232));
            painter.drawEllipse(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][0] - radis * 2, my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][1] - radis * 2,
                    radis * 4, radis * 4);
            painter.drawEllipse(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][0] - radis * 2, my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][1] - radis * 2,
                    radis * 4, radis * 4);
            pen.setColor(QColor(255,0,0,232));
            pen.setWidth(3);
            painter.setPen(pen);
            point1.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][0]);
            point1.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][1]);
            point2.setX(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][0]);
            point2.setY(my_scale * p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][1]);
            painter.drawLine(point1, point2);
            pen.setWidth(1);
            painter.setPen(pen);
        }
        else if(has_weight && edge_state_t[id_select_edge]
                && point_state_t[t_graph.getEdgeNode()[id_select_edge][1]]
                && point_state_t[t_graph.getEdgeNode()[id_select_edge][0]])
        {
            pen.setColor(QColor(255,0,0,232));
            painter.setPen(pen);
            my_font.setBold(true);
            my_font.setPointSize(9 * my_scale);
            painter.setFont(my_font);
            painter.drawText((my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][0] + my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][0]) / 2,
                    (my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][1] - radis * 4 + my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][1] - radis * 4) / 2,
                    QString::number(t_graph.getEdge()[id_select_edge]->getWeight()));
            pen.setColor(QColor(0,0,0,0));
            painter.setPen(pen);
            painter.setBrush(QColor(255,0,0,232));
            painter.drawEllipse(my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][0] - radis * 2, my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][1] - radis * 2,
                    radis * 4, radis * 4);
            painter.setBrush(QColor(255,0,0,232));
            painter.drawEllipse(my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][0] - radis * 2, my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][1] - radis * 2,
                    radis * 4, radis * 4);
            pen.setColor(QColor(255,0,0,232));
            pen.setWidth(3);
            painter.setPen(pen);
            point1.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][0]);
            point1.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][1]);
            point2.setX(my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][0]);
            point2.setY(my_scale * t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][1]);
            painter.drawLine(point1, point2);
            pen.setWidth(1);
            painter.setPen(pen);
        }
    }

    painter.restore();
}


//鼠标移动事件
void MainWindow::mouseMoveEvent(QMouseEvent * ev)
{
    if(is_in_start)
        return;
    //拖点拖边，更新位置
    if (is_dragging && id_select_point != -1)
    {
        if(!has_weight)
        {
            if(!point_state[id_move_point])
                return;
            p_point[strategy][id_move_point][0] += (ev->pos().x() - temp_x) / my_scale;
            p_point[strategy][id_move_point][1] += (ev->pos().y() - temp_y) / my_scale;
            temp_x = ev->pos().x();
            temp_y = ev->pos().y();
            update();
        }
        else
        {
            if(!point_state_t[id_move_point])
                return;
            t_point[strategy][id_move_point][0] += (ev->pos().x() - temp_x) / my_scale;
            t_point[strategy][id_move_point][1] += (ev->pos().y() - temp_y) / my_scale;
            temp_x = ev->pos().x();
            temp_y = ev->pos().y();
            update();
        }
    }
    else if(is_dragging && id_select_edge != -1)
    {
        if(!has_weight)
        {
            if(!point_state[p_graph.getEdgeNode()[id_select_edge][0]] ||
                    !point_state[p_graph.getEdgeNode()[id_select_edge][1]])
                return;
            p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][0] += (ev->pos().x() - temp_x) / my_scale;
            p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][0] += (ev->pos().x() - temp_x) / my_scale;
            p_point[strategy][p_graph.getEdgeNode()[id_select_edge][0]][1] += (ev->pos().y() - temp_y) / my_scale;
            p_point[strategy][p_graph.getEdgeNode()[id_select_edge][1]][1] += (ev->pos().y() - temp_y) / my_scale;
            temp_x = ev->pos().x();
            temp_y = ev->pos().y();
            update();
        }
        else
        {
            if(!point_state_t[t_graph.getEdgeNode()[id_select_edge][0]] ||
                    !point_state_t[t_graph.getEdgeNode()[id_select_edge][1]]
                    || !edge_state_t[id_select_edge])
                return;
            t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][0] += (ev->pos().x() - temp_x) / my_scale;
            t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][0] += (ev->pos().x() - temp_x) / my_scale;
            t_point[strategy][t_graph.getEdgeNode()[id_select_edge][0]][1] += (ev->pos().y() - temp_y) / my_scale;
            t_point[strategy][t_graph.getEdgeNode()[id_select_edge][1]][1] += (ev->pos().y() - temp_y) / my_scale;
            temp_x = ev->pos().x();
            temp_y = ev->pos().y();
            update();
        }
    }
    //拉索模式，存储拉索坐标，并寻找在拉索圈内的点
    else if(is_pull)
    {
        pull_vector.push_back(QPoint(ev->pos().x(), ev->pos().y()));
        QPolygon temp_poly(pull_vector);
        poly = temp_poly;
        int node_num = p_graph.getNodeNum();
        if(!has_weight)
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state[i])
                    continue;
                if(poly.containsPoint(QPoint(calcX(my_scale * p_point[strategy][i][0]), calcY(my_scale * p_point[strategy][i][1])), Qt::OddEvenFill))
                {
                    point_highlight[i] = true;
                    highlight_number ++;
                }
                else
                {
                    point_highlight[i] = false;
                }
            }
        }
        else
        {
            for(int i = 0; i < node_num; i++)
            {
                if(!point_state_t[i])
                    continue;
                if(poly.containsPoint(QPoint(calcX(my_scale * t_point[strategy][i][0]), calcY(my_scale * t_point[strategy][i][1])), Qt::OddEvenFill))
                {
                    point_highlight[i] = true;
                    highlight_number ++;
                }
                else
                {
                    point_highlight[i] = false;
                }
            }
        }
        update();
    }
    //高亮模式下等点群的拖动
    else if(is_highlight)
    {
        id_select_point = -1;
        int node_num = p_graph.getNodeNum();
        if(!has_weight)
        {
            for(int i = 0; i < node_num; i++)
            {
                if(point_highlight[i])
                {
                    p_point[strategy][i][0] += (ev->pos().x() - temp_x_highlight) / my_scale;
                    p_point[strategy][i][1] += (ev->pos().y() - temp_y_highlight) / my_scale;
                }
            }
            temp_x_highlight = ev->pos().x();
            temp_y_highlight = ev->pos().y();
            update();
        }
        else
        {
            for(int i = 0; i < node_num; i++)
            {
                if(point_highlight[i])
                {
                    t_point[strategy][i][0] += (ev->pos().x() - temp_x_highlight) / my_scale;
                    t_point[strategy][i][1] += (ev->pos().y() - temp_y_highlight) / my_scale;
                }
            }
            temp_x_highlight = ev->pos().x();
            temp_y_highlight = ev->pos().y();
            update();
        }
    }
    //不再以上模式，但按下鼠标，进行整图拖动
    else if(is_mouse_pressed)
    {
        Opoint[0] += ev->pos().x() - temp_x;
        Opoint[1] += ev->pos().y() - temp_y;
        temp_x = ev->pos().x();
        temp_y = ev->pos().y();
        update();
    }
    else if(highlight_number > 0)
    {
        id_select_point = -1;
    }
    //普通未按下鼠标模式，实时更新鼠标是否在某点区或边区
    else
    {
        id_select_edge = -1;
        int candidate1 = -1;
        int candidate2 = -1;
        if(!has_weight)
        {
            temp_x = ev->pos().x();
            temp_y = ev->pos().y();
            int len = p_point[0].size();
            int i;

            for(i = 0; i < len; i++)
            {
                if(isInCicle(ev->pos().x(), ev->pos().y(), calcX(my_scale * p_point[strategy][i][0]), calcY(my_scale * p_point[strategy][i][1]), radis))
                {
                    if(candidate1 == -1)
                    {
                        candidate1 = i;
                    }
                    else if(candidate2 == -1)
                    {
                        candidate2 = i;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if(candidate1 == -1)
            {
                if(id_select_point != -1)
                {
                    id_select_point = -1;               
                }               
                setCursor(Qt::ArrowCursor);
                int edge_num = p_graph.getEdgeNum();
                for(int i = 0; i < edge_num; i++)
                {
                    if(point_state[p_graph.getEdgeNode()[i][0]] && point_state[p_graph.getEdgeNode()[i][1]])
                    {
                        if(inEdgeArea(calcX(my_scale * p_point[strategy][p_graph.getEdgeNode()[i][0]][0]),
                                      calcY(my_scale * p_point[strategy][p_graph.getEdgeNode()[i][0]][1]),
                                      calcX(my_scale * p_point[strategy][p_graph.getEdgeNode()[i][1]][0]),
                                      calcY(my_scale * p_point[strategy][p_graph.getEdgeNode()[i][1]][1]),
                                      ev->pos().x(), ev->pos().y()))
                        {
                            id_select_edge = i;
                            setCursor(Qt::PointingHandCursor);
                            break;
                        }
                    }
                }

                update();
                return;
            }
            else if(candidate2 == -1)
            {
                id_select_point = candidate1;
                setCursor(Qt::PointingHandCursor);
                update();
            }
            else
            {
                if(calcInstance(calcX(my_scale * p_point[strategy][candidate1][0]),ev->pos().x(), calcY(my_scale * p_point[strategy][candidate1][1]), ev->pos().y()) >
                        calcInstance(calcX(my_scale * p_point[strategy][candidate2][0]),ev->pos().x(), calcY(my_scale * p_point[strategy][candidate2][1]), ev->pos().y()))
                {
                    id_select_point = candidate2;
                }
                else
                {
                    id_select_point = candidate1;
                }
                setCursor(Qt::PointingHandCursor);
                update();
            }
        }
        else
        {
             temp_x = ev->pos().x();
             temp_y = ev->pos().y();
             int len = p_point[0].size();
             int i;

             for(i = 0; i < len; i++)
             {
                 if(isInCicle(ev->pos().x(), ev->pos().y(), calcX(my_scale * t_point[strategy][i][0]), calcY(my_scale * t_point[strategy][i][1]), radis))
                 {
                     if(candidate1 == -1)
                     {
                         candidate1 = i;
                     }
                     else if(candidate2 == -1)
                     {
                         candidate2 = i;
                     }
                     else
                     {
                         break;
                     }
                 }
             }
             if(candidate1 == -1)
             {
                 if(id_select_point != -1)
                 {
                     id_select_point = -1;                  
                 }
                 setCursor(Qt::ArrowCursor);
                 int edge_num = t_graph.getEdgeNum();
                 for(int i = 0; i < edge_num; i++)
                 {
                     if(point_state_t[t_graph.getEdgeNode()[i][0]] && point_state_t[t_graph.getEdgeNode()[i][1]])
                     {
                         if(inEdgeArea(calcX(my_scale * t_point[strategy][t_graph.getEdgeNode()[i][0]][0]),
                                       calcY(my_scale * t_point[strategy][t_graph.getEdgeNode()[i][0]][1]),
                                       calcX(my_scale * t_point[strategy][t_graph.getEdgeNode()[i][1]][0]),
                                       calcY(my_scale * t_point[strategy][t_graph.getEdgeNode()[i][1]][1]),
                                       ev->pos().x(), ev->pos().y()))
                         {                             
                             id_select_edge = i;
                             if(!edge_state_t[id_select_edge])
                                 continue;
                             setCursor(Qt::PointingHandCursor);
                             break;
                         }
                     }
                 }                
                 update();
                 return;
             }
             else if(candidate2 == -1)
             {
                 id_select_point = candidate1;
                 setCursor(Qt::PointingHandCursor);
                 update();
             }
             else
             {
                 if(calcInstance(calcX(my_scale * t_point[strategy][candidate1][0]),ev->pos().x(), calcY(my_scale * t_point[strategy][candidate1][1]), ev->pos().y()) >
                         calcInstance(calcX(my_scale * t_point[strategy][candidate2][0]),ev->pos().x(), calcY(my_scale * t_point[strategy][candidate2][1]), ev->pos().y()))
                 {
                     id_select_point = candidate2;
                 }
                 else
                 {
                     id_select_point = candidate1;
                 }
                 setCursor(Qt::PointingHandCursor);
                 update();
             }
        }
    }
}


//鼠标释放事件
void MainWindow::mouseReleaseEvent(QMouseEvent * ev)
{
    if(is_in_start)
        return;
    is_mouse_pressed = false;
    //左键释放，解除拖动
    if(ev->button() == Qt::LeftButton)
    {
        if(is_dragging)
        {
            if(!has_weight)
            {
                is_dragging = false;
                setCursor(Qt::PointingHandCursor);
                update();
            }
            else
            {
                is_dragging = false;
                setCursor(Qt::PointingHandCursor);
                update();
            }
        }
    }
    //右键释放
    else if(ev->button() == Qt::RightButton)
    {
        is_pull = false;
        //若正在拉索，则高亮圈内的点
        if(!is_highlight)
        {
            highlight_number = 0;
            int node_num = p_graph.getNodeNum();
            pull_vector.push_back(QPoint(ev->pos().x(), ev->pos().y()));
            QPolygon temp_poly(pull_vector);
            poly = temp_poly;
            if(!has_weight)
            {
                for(int i = 0; i < node_num; i++)
                {
                    if(!point_state[i])
                        continue;
                    if(poly.containsPoint(QPoint(calcX(my_scale * p_point[strategy][i][0]), calcY(my_scale * p_point[strategy][i][1])), Qt::OddEvenFill))
                    {
                        point_highlight[i] = true;
                        highlight_number ++;
                    }
                    else
                    {
                        point_highlight[i] = false;
                    }
                }
            }
            else
            {
                for(int i = 0; i < node_num; i++)
                {
                    if(!point_state_t[i])
                        continue;
                    if(poly.containsPoint(QPoint(calcX(my_scale * t_point[strategy][i][0]), calcY(my_scale * t_point[strategy][i][1])), Qt::OddEvenFill))
                    {
                        point_highlight[i] = true;
                        highlight_number ++;
                    }
                    else
                    {
                        point_highlight[i] = false;
                    }
                }
            }
            pull_vector.clear();
            update();
        }
        //若在拖动高亮点，则停止拖动
        else if(is_highlight)
        {
            is_highlight = false;
        }
    }
}


//滚轮事件
void MainWindow::wheelEvent(QWheelEvent * ev)
{
    if(is_in_start)
        return;
    //键盘的v h键未按下，放大缩小
    if(!is_key_v_pressed && !is_key_h_pressed)
    {
        if(ev->delta() > 0)
        {
            ChangeScale(1.1);
            if(full_big == 0)
            {
                setOpoint(Opoint[0] + 0.1 * (Opoint[0] + main_length / 2 - QPoint(cursor().pos()).x()), Opoint[1] + 0.1 * (Opoint[1] + main_width / 2 - QPoint(cursor().pos()).y()));
                update();
            }
            else if(full_big == 2)
                return;
            else
            {
                setOpoint(Opoint[0] + (my_scale / my_last_scale - 1) * (Opoint[0] + main_length / 2 - QPoint(cursor().pos()).x()), Opoint[1] + (my_scale / my_last_scale - 1) * (Opoint[1] + main_width / 2 - QPoint(cursor().pos()).y()));
                update();
            }
        }
        else
        {
            ChangeScale(0.9);
            if(full_big == 0)
            {
                setOpoint(Opoint[0] - 0.1 * (Opoint[0] + main_length / 2 - QPoint(cursor().pos()).x()), Opoint[1] - 0.1 * (Opoint[1] + main_width / 2 - QPoint(cursor().pos()).y()));
                update();
            }
            else if(full_big == 2)
                return;
            else
            {
                setOpoint(Opoint[0] - (my_scale / my_last_scale - 1) * (Opoint[0] + main_length / 2 - QPoint(cursor().pos()).x()), Opoint[1] - (my_scale / my_last_scale - 1) * (Opoint[1] + main_width / 2 - QPoint(cursor().pos()).y()));
                update();
            }
        }
    }
    //键盘的v键按下，控制垂直滚动条
    else if(is_key_v_pressed)
    {
        if(ev->delta() > 0)
        {
            ui->verticalScrollBar->setSliderPosition(last_posi_vertical - 1);
        }
        else
        {
            ui->verticalScrollBar->setSliderPosition(last_posi_vertical + 1);
        }
    }
    //键盘的h键按下，控制水平滚动条
    else if(is_key_h_pressed)
    {
        if(ev->delta() > 0)
        {
            ui->horizontalScrollBar->setSliderPosition(last_posi_horizantol - 1);
        }
        else
        {
            ui->horizontalScrollBar->setSliderPosition(last_posi_horizantol + 1);
        }
    }
}


//窗口大小重置事件，改变控件位置与大小
void MainWindow::resizeEvent(QResizeEvent *ev)
{
    ui->verticalScrollBar->setGeometry(ev->size().width() - 25, 0, 25,
                                       ev->size().height() - 25 - ui->menuBar->height());
    ui->horizontalScrollBar->setGeometry(0, ev->size().height() - 50, ev->size().width() - 25, 25);
    ui->groupBox->setGeometry(ev->size().width() - 545, 0, 490, 210);
}


//切换layout
void MainWindow::setStrategy(Strategy s)
{
    if(is_in_start)
        return;
    if(s == strategy)
    {
        return;
    }
    else
    {
        in_cartoon = true;
        int node_num = p_point[0].size();
        if(has_weight)
        {
            direction.clear();
            direction.resize(node_num);
            for(int i = 0; i < node_num; i++)
            {
                //设置动画方向及动画初始位置（点）
                temp_point[i][0] = t_point[strategy][i][0];
                temp_point[i][1] = t_point[strategy][i][1];
                temp_point[i][2] = t_point[strategy][i][2];
                direction[i].push_back(t_point[s][i][0] - t_point[strategy][i][0]);
                direction[i].push_back(t_point[s][i][1] - t_point[strategy][i][1]);
                direction[i].push_back(t_point[s][i][2] - t_point[strategy][i][2]);
            }
            phase = 0;
            for(int i = 0; i < node_num; i++)
            {
                //设置动画速度（点）
                velocity[i][0] = direction[i][0] / 50;
                velocity[i][1] = direction[i][1] / 50;
                velocity[i][2] = direction[i][2] / 50;
            }
            layout_timer.start();
        }
        else
        {
            direction.clear();
            direction.resize(node_num);
            for(int i = 0; i < node_num; i++)
            {
                temp_point[i][0] = p_point[strategy][i][0];
                temp_point[i][1] = p_point[strategy][i][1];
                temp_point[i][2] = p_point[strategy][i][2];
                direction[i].push_back(p_point[s][i][0] - p_point[strategy][i][0]);
                direction[i].push_back(p_point[s][i][1] - p_point[strategy][i][1]);
                direction[i].push_back(p_point[s][i][2] - p_point[strategy][i][2]);
            }
            phase = 0;
            for(int i = 0; i < node_num; i++)
            {
                velocity[i][0] = direction[i][0] / 50;
                velocity[i][1] = direction[i][1] / 50;
                velocity[i][2] = direction[i][2] / 50;
            }
            layout_timer.start();

        }
        strategy = s;
    }
}


//layout切换动画
void MainWindow::changeLayout()
{
    int node_num = p_point[0].size();
    phase ++;
    if(phase <= 50) //50帧动画
    {
        for(int i = 0; i < node_num; i++)
        {
            changeX(i, velocity[i][0]);
            changeY(i, velocity[i][1]);
            changeZ(i, velocity[i][2]);
        }
        update();
    }
    else
    {
        layout_timer.stop();
        in_cartoon = false;
        update();
    }

}


//切换数据动画
void MainWindow::changeData()
{
    int delta;
    //用alpha透明度大小来控制渐变
    if(alpha_degree == 0)
    {
        if(has_weight)
        {
            ui->toSpinBox->setMaximum(72);
            ui->fromSpinBox->setMaximum(82);
            ui->sumSpinBox->setMaximum(73);
            has_weight = false;
            layout_timer.setInterval(20);
        }
        else
        {
            ui->toSpinBox->setMaximum(17);
            ui->fromSpinBox->setMaximum(17);
            ui->sumSpinBox->setMaximum(17);
            has_weight = true;
            layout_timer.setInterval(30);
        }
    }
    //两边数据的动画渐变速度不同，由于绘制时间的问题
    if(!has_weight)
    {
        delta = 10;
    }
    else
    {
        delta = 5;
    }
    if(alpha_degree == -1)
    {
        data_timer.start();
        data_change = 1;
        alpha_degree = edge_color; //在这里用到了可调alpha值
        update();
    }
    else if(alpha_degree > 0 && data_change == 1)
    {
        alpha_degree -= delta;
        update();
    }
    else if(alpha_degree <= 0)
    {
        alpha_degree += delta;
        data_change = 2;
        update();
    }
    else if(alpha_degree > 0 && alpha_degree < edge_color && data_change == 2)
    {
        alpha_degree += delta;
        update();
    }
    else if(alpha_degree == edge_color && data_change == 2)
    {
        data_change = 0;
        alpha_degree = -1;
        data_timer.stop();
        update();
    }
}


//layout切换菜单
void MainWindow::on_actionCircular_triggered()
{
    if(is_in_start)
        return;
    setStrategy(CICLE);
}

void MainWindow::on_actionPass_through_triggered()
{
    if(is_in_start)
        return;
    setStrategy(PASSTHROUGH);
}

void MainWindow::on_actionFast_2D_triggered()
{
    if(is_in_start)
        return;
    setStrategy(FAST2D);
}

void MainWindow::on_actionRandom_triggered()
{
    if(is_in_start)
        return;
    setStrategy(RANDOM);
}

void MainWindow::on_actionSimple_2D_triggered()
{
    if(is_in_start)
        return;
    setStrategy(SIMPLE2D);
}

void MainWindow::on_actionForce_triggered()
{
    if(is_in_start)
        return;
    setStrategy(FORCE);
}

void MainWindow::on_actionClustering_2D_triggered()
{
    if(is_in_start)
        return;
    setStrategy(CLUSTERING2D);
}

void MainWindow::on_actionCone_triggered()
{
    if(is_in_start)
        return;
    setStrategy(MYLAYOUT1);
}

void MainWindow::on_actionCommunity_2D_triggered()
{
    if(is_in_start)
        return;
    setStrategy(MYLAYOUT2);
}

void MainWindow::on_actionStart_triggered()
{
    if(is_in_start)
        return;
    setStrategy(START);
}


//data切换菜单
void MainWindow::on_actionPaper_triggered()
{
    if(is_in_local)
        return;
    if(is_in_start)
        return;
    if(has_weight)
    {
        changeData();
    }
    else
    {
        return;
    }
}

void MainWindow::on_actionTopic_triggered()
{
    if(is_in_local)
        return;
    if(is_in_start)
        return;
    if(has_weight)
    {
        return;
    }
    else
    {
        changeData();
    }
}


//tools菜单
//属性过滤器
void MainWindow::on_actionFilter_triggered()
{
    if(is_in_start)
        return;
    if(is_in_local)
        return;
    if(!has_weight)
    {
        filterDialog dlg(p_graph, point_state);
        dlg.exec();
        update();
    }
    else
    {
        filterTopicDialog dlg(t_graph, point_state_t);
        dlg.exec();
        update();
    }
}

//search及列表显示
void MainWindow::on_actionSearch_triggered()
{
    if(is_in_start)
        return;
    if(is_in_local)
        return;
    int node_num = p_graph.getNodeNum();
    vector<int> temp;
    if(!has_weight)
    {
        point_state_copy = point_state;
        filterDialog dlg(p_graph, point_state);
        dlg.exec();
        for(int i = 0; i < node_num; i++)
        {
            if(point_state[i])
            {
                temp.push_back(i);
            }
        }
        point_state = point_state_copy;
        searchResultDialog dialog(p_graph, temp);
        dialog.exec();
    }
    else
    {
        point_state_t_copy = point_state_t;
        filterTopicDialog dlg(t_graph, point_state_t);
        dlg.exec();
        for(int i = 0; i < node_num; i++)
        {
            if(point_state_t[i])
            {
                temp.push_back(i);
            }
        }
        point_state_t = point_state_t_copy;
        searchResultDialog dialog(t_graph, temp);
        dialog.exec();
    }
}

//重置按钮
void MainWindow::on_actionReset_triggered()
{
    is_in_local = false;
    int node_num = p_graph.getNodeNum();
    my_scale = 1;
    Opoint[0] = 0;
    Opoint[1] = 0;
    Opoint[2] = 0;
    height = 0;
    radis = 5;
    in_cartoon = false;
    strategy = START;
    is_highlight = false;
    is_pull = false;
    full_big = 0;
    highlight_number = 0;
    alpha_degree = -1;
    is_key_v_pressed = false;
    is_key_h_pressed = false;
    data_change = 0;
    is_in_filter = false;
    is_dragging = false;
    is_single = false;
    id_move_point = 0;
    id_select_point = -1;
    id_select_edge = -1;
    is_mouse_pressed = false;
    alpha_start = 0;

    ui->node_out_slider->setValue(0);
    ui->node_in_slider->setValue(0);
    ui->node_sum_slider->setValue(0);
    ui->weight_slider->setValue(0);

    //设置edge weight
    int number = t_graph.getEdgeNum();
    for(int i =0 ;i < number; i++)
    {
        edge_state_t[i] = true;
    }

    //初始为paper图
    has_weight = false;

    //设置个节点初始属性
    for(int i= 0; i < node_num; i++)
    {
        point_num_edge_state[0][0][i] = true;
        point_num_edge_state[0][1][i] = true;
        point_num_edge_state[0][2][i] = true;
        point_num_edge_state[1][0][i] = true;
        point_num_edge_state[1][1][i] = true;
        point_num_edge_state[1][2][i] = true;
        point_state[i] = true;
        point_state_t[i] = true;
    }
    update();
}

//带贝塞尔曲线的边束化，交互比较慢
void MainWindow::on_actionEdge_bundling_triggered()
{
    int edge_num;
    vector<int> temp1;
    if(has_weight)
    {
        edge_num = t_graph.getEdgeNum();
        vector<vector<int> > temp2(edge_num);
        for(int i = 0; i < edge_num; i++)
        {
            temp1.push_back(t_graph.getEdgeNode()[i][0]);
            temp1.push_back(t_graph.getEdgeNode()[i][1]);
            temp2[i] = temp1;
            temp1.clear();
        }
        Dialog meb(edge_num, t_point[strategy], temp2);
        meb.calcXYZForPaint();
        meb.exec();
    }
    else
    {
        edge_num = p_graph.getEdgeNum();
        vector<vector<int> > temp2(edge_num);
        for(int i = 0; i < edge_num; i++)
        {
            temp1.push_back(p_graph.getEdgeNode()[i][0]);
            temp1.push_back(p_graph.getEdgeNode()[i][1]);
            temp2[i] = temp1;
            temp1.clear();
        }
        Dialog meb(edge_num, p_point[strategy], temp2);
        meb.calcXYZForPaint();
        meb.exec();
    }
}

//不带贝塞尔曲线的边束化，交互较快
void MainWindow::on_actionInteraction_edge_bundling_triggered()
{
    int edge_num;
    vector<int> temp1;
    if(has_weight)
    {
        edge_num = t_graph.getEdgeNum();
        vector<vector<int> > temp2(edge_num);
        for(int i = 0; i < edge_num; i++)
        {
            temp1.push_back(t_graph.getEdgeNode()[i][0]);
            temp1.push_back(t_graph.getEdgeNode()[i][1]);
            temp2[i] = temp1;
            temp1.clear();
        }
        noBezierDialog meb(edge_num, t_point[strategy], temp2);
        meb.calcXYZForPaint();
        meb.exec();
    }
    else
    {
        edge_num = p_graph.getEdgeNum();
        vector<vector<int> > temp2(edge_num);
        for(int i = 0; i < edge_num; i++)
        {
            temp1.push_back(p_graph.getEdgeNode()[i][0]);
            temp1.push_back(p_graph.getEdgeNode()[i][1]);
            temp2[i] = temp1;
            temp1.clear();
        }
        noBezierDialog meb(edge_num, p_point[strategy], temp2);
        meb.calcXYZForPaint();
        meb.exec();
    }
}


//file菜单
//存储layout
void MainWindow::on_actionSave_triggered()
{
    if(is_in_start)
        return;
    bool is_original;
    QMessageBox msg_box(this);
    msg_box.addButton(QMessageBox::Yes);
    msg_box.addButton(QMessageBox::No);
    msg_box.setText("Do you want to save all the modification ?\nPress \"Yes\" to save, \"No\" to save the original layout.");
    msg_box.setWindowTitle("warning");
    msg_box.addButton(QMessageBox::Cancel);
    QString file_name; //要保存的文件名
    QFile file; //打开的文件
    int flag; //存储各种对话框返回值状态
    while(1)
    {
        flag = msg_box.exec();
        if(flag == QMessageBox::Cancel)
        {
            return;
        }
        else if(flag == QMessageBox::Yes)
        {
             is_original = false;
             file_name = QFileDialog::getSaveFileName(this, "save", "", tr("*.txt"));
             file.setFileName(file_name);
             if(file.open(QFile::ReadOnly))
             {
                 flag = QMessageBox::warning(this, "warning", "The file has existed. Do you want to replace it.",
                                      QMessageBox::Yes, QMessageBox::No);
                 if(flag == QMessageBox::Yes)
                 {
                     break;
                 }
                 else
                 {
                     continue;
                 }
             }
             else
             {
                 file.close();
                 break;
             }
        }
        else
        {
            is_original = true;
            file_name = QFileDialog::getSaveFileName(this, "save", "", tr("*.txt"));
            file.setFileName(file_name);
            if(file.open(QFile::ReadOnly))
            {
                flag = QMessageBox::warning(this, "warning", "The file has existed. Do you want to replace it.",
                                     QMessageBox::Yes, QMessageBox::No);
                if(flag == QMessageBox::Yes)
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                file.close();
                break;
            }
        }
    }
    file.open(QFile::WriteOnly);
    QTextStream out(&file);
    int node_num = p_graph.getNodeNum();
    if(is_original)
    {
        out << "PaperConferenceAuthorGraph" << endl;
        for(int j = 0; j < strategy_num; j++)
        {
            out << j << endl;
            for(int i = 0; i < node_num; i++)
            {
                out << p_point_copy[j][i][0] << endl;
                out << p_point_copy[j][i][1] << endl;
            }
        }
        out << "TopicGraph" << endl;
        for(int j = 0; j < strategy_num; j++)
        {
            out << j << endl;
            for(int i = 0; i < node_num; i++)
            {
                out << t_point_copy[j][i][0] << endl;
                out << t_point_copy[j][i][1] << endl;
            }
        }
        QMessageBox::information(this, "save success", "The file has been saved successfully.");
    }
    else
    {
        out << "PaperConferenceAuthorGraph" << endl;
        for(int j = 0; j < strategy_num; j++)
        {
            out << j << endl;
            for(int i = 0; i < node_num; i++)
            {
                out << p_point[j][i][0] << endl;
                out << p_point[j][i][1] << endl;
            }
        }
        out << "TopicGraph" << endl;
        for(int j = 0; j < strategy_num; j++)
        {
            out << j << endl;
            for(int i = 0; i < node_num; i++)
            {
                out << t_point[j][i][0] << endl;
                out << t_point[j][i][1] << endl;
            }
        }
        QMessageBox::information(this, "save success", "The file has been saved successfully.");
    }
}

//加载layout
void MainWindow::on_actionLoad_layout_triggered()
{
    QString file_name = readFileName(); //要打开的文件名
    QFile file; //打开的文件
    if(!file_name.length() <= 0)
    {
        return;
    }
    else
    {
        file.setFileName(file_name);
        QTextStream in(&file);
        in.readLine();
        int node_num = p_graph.getNodeNum();
        for(int j = 0; j < strategy_num; j++)
        {
            in.readLine();
            for(int i = 0; i < node_num; i++)
            {
                p_point_copy[j][i][0]  = in.readLine().toDouble();
                p_point_copy[j][i][1]  = in.readLine().toDouble();
            }
        }
        for(int j = 0; j < strategy_num; j++)
        {
            in.readLine();
            for(int i = 0; i < node_num; i++)
            {
                t_point_copy[j][i][0]  = in.readLine().toDouble();
                t_point_copy[j][i][1]  = in.readLine().toDouble();
            }
        }
        QMessageBox::information(this, "load success", "The file has been loaded successfully.");
    }
}


//存储data，五种选项
void MainWindow::on_actionSave_paper_node_triggered()
{
    QString file_name = writeFileName(); //要保存的文件名
    if(file_name.length() <= 0)
        return;
    QFile file(file_name); //打开的文件
    file.open(QFile::WriteOnly);
    QTextStream out(&file);
    int node_num = p_graph.getNodeNum();
    for(int j = 0; j < node_num; j++)
    {
        out << p_graph.getNode()[j]->getIdOfNode() << endl;
        switch(p_graph.getNode()[j]->getType())
        {
        case PaperConferenceAuthorNode::PAPER:
            out << "type: paper" << endl;
            out << "year: " << p_graph.getNode()[j]->getYear() << endl;
            out << "author: " << p_graph.getNode()[j]->getExtra().c_str() << endl;
            out << "dateFrom: " << p_graph.getNode()[j]->getDateFrom() << endl;
            out << "id: " << p_graph.getNode()[j]->getId().c_str() << endl;
            out << "pageFrom: " << p_graph.getNode()[j]->getPageFrom() << endl;
            out << "paperTitle: " << p_graph.getNode()[j]->getName().c_str() << endl;
            out << "paperTitleShort: " << p_graph.getNode()[j]->getNameShort().c_str() << endl;
            break;
        case PaperConferenceAuthorNode::CONFERENCE:
            out << "type: conference" << endl;
            out << "year: " << p_graph.getNode()[j]->getYear() << endl;
            out << "id: " << p_graph.getNode()[j]->getId().c_str() << endl;
            out << "conferenceName: " << p_graph.getNode()[j]->getName().c_str() << endl;
            out << "conferenceNameShort: " << p_graph.getNode()[j]->getNameShort().c_str() << endl;
            break;
        case PaperConferenceAuthorNode::AUTHOR:
            out << "type: conference" << endl;
            out << "year: " << p_graph.getNode()[j]->getYear() << endl;
            out << "id: " << p_graph.getNode()[j]->getId().c_str() << endl;
            out << "authorName: " << p_graph.getNode()[j]->getName().c_str() << endl;
            out << "authorNameShort: " << p_graph.getNode()[j]->getNameShort().c_str() << endl;
            break;
        }
        out << "viewColor: (" << p_graph.getNode()[j]->getViewColor()[0] << ","
            << p_graph.getNode()[j]->getViewColor()[1] << ","
            << p_graph.getNode()[j]->getViewColor()[2] << ","
            << p_graph.getNode()[j]->getViewColor()[3] << ")" << endl;
        out << "viewLabel: " << p_graph.getNode()[j]->getViewLabel().c_str() << endl;
        out << "viewLayout: (" << p_graph.getNode()[j]->getViewLayout()[0] << ","
            << p_graph.getNode()[j]->getViewLayout()[1] << ","
            << p_graph.getNode()[j]->getViewLayout()[2] << ")" << endl;
        out << endl;
    }
    file.close();
    QMessageBox::information(this, "save success", "The file has been saved successfully.");
}

void MainWindow::on_actionSave_paper_edge_triggered()
{
    QString file_name = writeFileName(); //要保存的文件名
    if(file_name.length() <= 0)
        return;
    QFile file(file_name); //打开的文件
    file.open(QFile::WriteOnly);
    QTextStream out(&file);
    int edge_num = p_graph.getEdgeNum();
    out.setDevice(&file);
    for(int j = 0; j < edge_num; j++)
    {
        out << p_graph.getEdge()[j]->getSource() << " " << p_graph.getEdge()[j]->getTarget() << endl;
    }
    out << endl;
    file.close();
    QMessageBox::information(this, "save success", "The file has been saved successfully.");
}

void MainWindow::on_actionSave_topic_node_triggered()
{
    QString file_name = writeFileName(); //要保存的文件名
    if(file_name.length() <= 0)
        return;
    QFile file(file_name); //打开的文件
    file.open(QFile::WriteOnly);
    QTextStream out(&file);
    int node_num = t_graph.getNodeNum();
    out.setDevice(&file);
    for(int j = 0; j < node_num; j++)
    {
        out << t_graph.getNode()[j]->getIdOfNode() << endl;
        out << "TopicWords: ";
        for(auto iter = t_graph.getNode()[j]->getWords().begin(); iter != t_graph.getNode()[j]->getWords().end(); iter++)
        {
            out << (*iter).c_str() << " ";
        }
        out << endl;
        out << "TopicDocuments: ";
        for(auto iter = t_graph.getNode()[j]->getDoc().begin(); iter != t_graph.getNode()[j]->getDoc().end(); iter++)
        {
            out << *iter << " ";
        }
        out << endl;
        out << endl;
    }
    file.close();
    QMessageBox::information(this, "save success", "The file has been saved successfully.");
}

void MainWindow::on_actionSave_topic_edge_triggered()
{
    QString file_name = writeFileName(); //要保存的文件名
    if(file_name.length() <= 0)
        return;
    QFile file(file_name); //打开的文件
    file.open(QFile::WriteOnly);
    QTextStream out(&file);
    int edge_num = t_graph.getEdgeNum();
    out.setDevice(&file);
    for(int j = 0; j < edge_num; j++)
    {
        out << t_graph.getEdge()[j]->getSource() << " " << t_graph.getEdge()[j]->getTarget() << " " << t_graph.getEdge()[j]->getWeight() << endl;
    }
    out << endl;
    file.close();
    QMessageBox::information(this, "save success", "The file has been saved successfully.");
}

void MainWindow::on_actionSave_document_node_triggered()
{
    QString file_name = writeFileName(); //要保存的文件名
    if(file_name.length() <= 0)
        return;
    QFile file(file_name); //打开的文件
    file.open(QFile::WriteOnly);
    QTextStream out(&file);
    out.setDevice(&file);
    int node_num = t_graph.getAllDoc().size();
    for(int j = 0; j < node_num; j++)
    {
        out << t_graph.getDocNode(j).getIdOfNode() << endl;
        out << t_graph.getDocNode(j).getTitle().c_str() << endl;
        out << t_graph.getDocNode(j).getContent().c_str() << endl;
        out << endl;
    }
    out << endl;
    file.close();
    QMessageBox::information(this, "save success", "The file has been saved successfully.");
}


//加载data，五种选项
void MainWindow::on_actionLoad_paper_node_triggered()
{
    string file_name = readFileName().toStdString();
    if(file_name.length() <= 0)
        return;
    ifstream fin;
    PaperConferenceAuthorNode * temp_base;
    p_graph.deleteNode();
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
        p_graph.readSTD(fin, buffer, temp_base, id, k);
        p_graph.addNode(temp_base);
        if(!fin.eof())
        {

        }
        else
        {
           break;
        }
    }
    delete buffer;
    p_graph.initialize();
    update();
}

void MainWindow::on_actionLoad_paper_edge_triggered()
{
    string file_name = readFileName().toStdString();
    if(file_name.length() <= 0)
        return;
    p_graph.deleteEdge();
    p_graph.readInEdge(file_name.c_str());
    p_graph.initialize();
    update();
}

void MainWindow::on_actionLoad_topic_node_triggered()
{
    string file_name = readFileName().toStdString();
    if(file_name.length() <= 0)
        return;
    ifstream fin;
    TopicNode * temp_base;
    t_graph.deleteNode();
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
        t_graph.getNodeIn().push_back(vector<int>());
        t_graph.getNodeOut().push_back(vector<int>());
        t_graph.readSTD(fin, buffer, temp_base, id);
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
    t_graph.initialize();
    update();
}

void MainWindow::on_actionLoad_topic_edge_triggered()
{
    string file_name = readFileName().toStdString();
    if(file_name.length() <= 0)
        return;
    t_graph.deleteEdge();
    t_graph.readInTopicEdge(file_name.c_str());
    t_graph.initialize();
    update();
}

void MainWindow::on_actionLoad_document_node_triggered()
{
    string file_name = readFileName().toStdString();
    if(file_name.length() <= 0)
        return;
    qDebug() << file_name.c_str();
    t_graph.deleteDocNode();
    t_graph.readInDocNode(file_name.c_str());
}


//存储辅助函数，获取文件名来写
QString MainWindow::writeFileName()
{
    if(is_in_start)
        return "";
    QString file_name; //要保存的文件名
    file_name = QFileDialog::getSaveFileName(this, "save topic edge", "", tr("*.txt"));
    return file_name;
}

//存储辅助函数，获取文件名来读
QString MainWindow::readFileName()
{
    if(is_in_start)
        return "";
    QString file_name; //要打开的文件名
    QFile file; //打开的文件
    int flag; //存储各种对话框返回值状态
    while(1)
    {
        file_name = QFileDialog::getOpenFileName(this, "open", "", tr("*.txt"));
        if(file_name.length() <= 0)
            return "";
        file.setFileName(file_name);
        if(!file.open(QFile::ReadOnly))
        {
            flag = QMessageBox::warning(this, "warning", "The file isn't existed.\nPress \"ok\" to check.",
                                 QMessageBox::Ok, QMessageBox::Cancel);
            if(flag == QMessageBox::Ok)
            {
                continue;
            }
            else
            {

                return "";
            }
        }
        else
        {
            break;
        }
    }
    return file_name;
}


//滚动条控件变化对应图的平移并与滚轮事件连接
void MainWindow::on_horizontalScrollBar_valueChanged(int position)
{
    if(is_in_start)
        return;
    if(last_posi_horizantol > position)
    {
        Opoint[0] += 50 * my_scale;
        update();
    }
    else
    {
        Opoint[0] -= 50 * my_scale;
        update();
    }
    last_posi_horizantol = position;
}

void MainWindow::on_verticalScrollBar_valueChanged(int position)
{
    if(is_in_start)
        return;
    if(last_posi_vertical > position)
    {
        Opoint[1] += 50 * my_scale;
        update();
    }
    else
    {
        Opoint[1] -= 50 * my_scale;
        update();
    }
    last_posi_vertical = position;
}


//toolbox过滤器控件设置
void MainWindow::on_node_out_slider_valueChanged(int value)
{
    if(is_in_start)
        return;
    if(is_in_local)
        return;
    int node_num = p_graph.getNodeNum();
    if(!has_weight)
    {
        for(int i = 0; i < node_num; i++)
        {
            if(p_graph.getOutNum(i) >= value)
            {
                point_num_edge_state[0][2][i] = true;
            }
            else
            {
                point_num_edge_state[0][2][i] = false;
            }
        }
        for(int i = 0; i < node_num; i++)
        {
            point_state[i] = point_num_edge_state[0][0][i] && point_num_edge_state[0][1][i] && point_num_edge_state[0][2][i];
        }
    }
    else
    {
        for(int i = 0; i < node_num; i++)
        {          
            if(t_graph.getOutNum(i) >= value / 4.1)
            {
                point_num_edge_state[1][2][i] = true;
            }
            else
            {
                point_num_edge_state[1][2][i] = false;
            }
        }
        for(int i = 0; i < node_num; i++)
        {
            point_state_t[i] = point_num_edge_state[1][0][i] && point_num_edge_state[1][1][i] && point_num_edge_state[1][2][i];
        }
    }
    if(!is_spinBox_changed)
    {
        is_spinBox_changed = true;
        if(!has_weight)
            ui->toSpinBox->setValue(value);
        else
            ui->toSpinBox->setValue(int(value / 4.1));
    }
    else
    {
        is_spinBox_changed = false;
    }
    update();
}

void MainWindow::on_node_in_slider_valueChanged(int value)
{
    if(is_in_start)
        return;
    if(is_in_local)
        return;
    int node_num = p_graph.getNodeNum();
    if(!has_weight)
    {
        for(int i = 0; i < node_num; i++)
        {
            if(p_graph.getInNum(i) >= value)
            {
                point_num_edge_state[0][1][i] = true;
            }
            else
            {
                point_num_edge_state[0][1][i] = false;
            }
        }
        for(int i = 0; i < node_num; i++)
        {
            point_state[i] = point_num_edge_state[0][0][i] && point_num_edge_state[0][1][i] && point_num_edge_state[0][2][i];
        }
    }
    else
    {
        for(int i = 0; i < node_num; i++)
        {
            if(t_graph.getInNum(i) >= value / 1.9)
            {
                point_num_edge_state[1][1][i]= true;
            }
            else
            {
                point_num_edge_state[1][1][i] = false;
            }
        }
        for(int i = 0; i < node_num; i++)
        {
            point_state_t[i] = point_num_edge_state[1][0][i] && point_num_edge_state[1][1][i] && point_num_edge_state[1][2][i];
        }
    }
    if(!is_spinBox_changed)
    {
        is_spinBox_changed = true;
        if(!has_weight)
            ui->fromSpinBox->setValue(value);
        else
            ui->fromSpinBox->setValue(int(value / 1.9));
    }
    else
    {
        is_spinBox_changed = false;
    }
    update();
}

void MainWindow::on_node_sum_slider_valueChanged(int value)
{
    if(is_in_start)
        return;
    if(is_in_local)
        return;
    int node_num = p_graph.getNodeNum();
    if(!has_weight)
    {
        for(int i = 0; i < node_num; i++)
        {
            if(p_graph.getSumNum(i) >= value)
            {
                point_num_edge_state[0][0][i] = true;
            }
            else
            {
                point_num_edge_state[0][0][i] = false;
            }
        }
        for(int i = 0; i < node_num; i++)
        {
            point_state[i] = point_num_edge_state[0][0][i] && point_num_edge_state[0][1][i] && point_num_edge_state[0][2][i];
        }
    }
    else
    {
        for(int i = 0; i < node_num; i++)
        {
            if(t_graph.getSumNum(i) >= value / 4.6)
            {
                point_num_edge_state[1][0][i] = true;
            }
            else
            {
                point_num_edge_state[1][0][i] = false;
            }
        }
        for(int i = 0; i < node_num; i++)
        {
            point_state_t[i] = point_num_edge_state[1][0][i] && point_num_edge_state[1][1][i] && point_num_edge_state[1][2][i];
        }
    }
    if(!is_spinBox_changed)
    {
        is_spinBox_changed = true;
        if(!has_weight)
            ui->sumSpinBox->setValue(value);
        else
            ui->sumSpinBox->setValue(int(value / 4.6));
    }
    else
    {
        is_spinBox_changed = false;
    }
    update();
}

void MainWindow::on_weight_slider_valueChanged(int value)
{
    if(is_in_start)
        return;
    if(is_in_local)
        return;
    int edge_num = t_graph.getEdgeNum();
    if(!has_weight)
    {
        return;
    }
    else
    {
        for(int i = 0; i < edge_num; i++)
        {
            if(t_graph.getEdge()[i]->getWeight() > (double)value / 100)
            {
                edge_state_t[i] = true;
            }
            else
            {
                edge_state_t[i] = false;
            }
        }
    }
    if(!is_spinBox_changed)
    {
        is_spinBox_changed = true;
        if(!has_weight)
            return;
        else
            ui->weightSpinBox->setValue(double(value) / 100);
    }
    else
    {
        is_spinBox_changed = false;
    }
    update();
}


//显示过滤器的数值，与其前面的slider过滤器连接
void MainWindow::on_toSpinBox_valueChanged(int value)
{
    if(!is_spinBox_changed)
    {
        is_spinBox_changed = true;
        if(!has_weight)
            ui->node_out_slider->setValue(value);
        else
            ui->node_out_slider->setValue(int(4.1 * value));
    }
    else
        is_spinBox_changed = false;
}

void MainWindow::on_fromSpinBox_valueChanged(int value)
{
    if(!is_spinBox_changed)
    {
        is_spinBox_changed = true;
        if(!has_weight)
            ui->node_in_slider->setValue(value);
        else
            ui->node_in_slider->setValue(int(1.9 * value));
    }
    else
        is_spinBox_changed = false;
}

void MainWindow::on_sumSpinBox_valueChanged(int value)
{
    if(!is_spinBox_changed)
    {
        is_spinBox_changed = true;
        if(!has_weight)
            ui->node_sum_slider->setValue(value);
        else
            ui->node_sum_slider->setValue(int(4.6 * value));
    }
    else
        is_spinBox_changed = false;
}

void MainWindow::on_weightSpinBox_valueChanged(double value)
{
    if(!is_spinBox_changed)
    {
        is_spinBox_changed = true;
        if(!has_weight)
             return;
        else
            ui->weight_slider->setValue(int(value * 100));
    }
    else
        is_spinBox_changed = false;
}


//开始键
void MainWindow::on_start_btn_clicked()
{
    start_timer.start();
    changeDataStart();
}

//开始动画，渐变效果
void MainWindow::changeDataStart()
{
    if(alpha_start < edge_color)
        alpha_start += 14;
    else
    {
        is_in_start = false;
        start_timer.stop();
        ui->start_btn->setGeometry(3000, 2000, 10, 10);
    }
    update();
}


//布局算法变换动画
void MainWindow::on_actionCartoon_triggered()
{
    cartoonDialog dlg(t_graph);
    dlg.exec();
}
