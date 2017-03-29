#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "stdafx.h"
#include <QMainWindow>
#include <iostream>
#include <QEvent>
#include <QTimer>
#include <QVector>
#include <QPoint>
#include <QPolygon>
#include "informationdialog.h"
#include "topicdialog.h"
#include "mainwindow.h"
#include "paperconferenceauthorgraph.h"
#include "topicgraph.h"
#include "searchresultdialog.h"

#include "vtkMutableDirectedGraph.h"
#include "vtkGraph.h"
#include "vtkGraphLayout.h"
#include "vtkGraphLayoutStrategy.h"
#include "vtkSmartPointer.h"

//stratrgy
#include "vtkCircularLayoutStrategy.h"
#include "vtkPassThroughLayoutStrategy.h"
#include "vtkForceDirectedLayoutStrategy.h"
#include "vtkFast2DLayoutStrategy.h"
#include "vtkRandomLayoutStrategy.h"
#include "vtkSimple2DLayoutStrategy.h"
#include "vtkClustering2DLayoutStrategy.h"
#include "vtkConeLayoutStrategy.h"
#include "vtkCommunity2DLayoutStrategy.h"
#include "vtkConstrained2DLayoutStrategy.h"
#include "circlelinelayout.h"
#include "linelinelayout.h"
#include "hellolayout.h"
#include "forcelayout.h"
#include "weightlayout.h"

#define POINT_PAPER 0
#define POINT_CONFERENCE 1
#define POINT_AUTHOR 2

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    Ui::MainWindow *ui;

private:
    const int edge_color;
    //滚动条位置存储
    int last_posi_vertical;
    int last_posi_horizantol;
    //控制放大缩小范围，防止过大过小
    int full_big;
    double my_last_scale;
    //引入图
    TopicGraph & t_graph;
    PaperConferenceAuthorGraph & p_graph;

    //策略个数
    const int strategy_num;
    //存储所有策略所有点的坐标
    vector<vector<vector<double> > >p_point;
    vector<vector<vector<double> > >t_point;
    vector<vector<vector<double> > >p_point_copy;
    vector<vector<vector<double> > >t_point_copy;

    //存储动画中间变量
    vector<vector<double> > temp_point;
    //point相关画图属性
    vector<int> point_type;
    vector<bool> point_state;
    vector<bool> point_state_t;
    vector<bool> point_state_copy;
    vector<bool> point_state_t_copy;
    vector<vector<bool> >point_state_copy_fil;
    vector<vector<bool> > point_state_t_copy_fil;
    vector<vector<vector<double> > >point_weight;
    vector<bool> point_highlight;
    vector<bool> edge_state_t;
    vector<vector<vector<bool> > >point_num_edge_state; //表示入度，出度，总度数筛选的结果，整合后才是筛选结果

    //处于高亮态的点的总数
    int highlight_number;
    //是否正在拉索
    bool is_pull;
    QVector<QPoint> pull_vector;
    QPolygon poly;
    //记录右键按下的起始位置
    int temp_x_highlight;
    int temp_y_highlight;

    //只在topic下有效
    vector<double> edge_weight;

    //stragety有关变量
    enum Strategy{CICLE, FORCE, PASSTHROUGH, FAST2D, RANDOM, SIMPLE2D, CLUSTERING2D, MYLAYOUT1, MYLAYOUT2, START};
    Strategy strategy;

    //layout切换用的timer
    QTimer layout_timer;

    //data切换用的代码
    QTimer data_timer;

    //start时切换到真实模式所用的代码
    QTimer start_timer;
    int alpha_start;

    //点的移动方向
    bool in_cartoon;
    vector<vector<double> > direction;
    int phase;
    vector<vector<double> > velocity;

    //bool量释义
    bool is_single; //拖动时仅显示拖动点
    bool is_dragging; //检测是否处于点拖移的状态
    bool is_mouse_pressed;//检测鼠标是否被按下    
    bool has_weight;    //表示处于哪一种data状态下，topic的边有weight
    bool is_highlight;  //表示是否处于拉索高亮选择阶段
    bool is_key_v_pressed;  //表示v键是否被按下,便于用鼠标控制竖直滚动条
    bool is_key_h_pressed;  //表示h键是否被按下,便于用鼠标控制水平滚动条
    bool is_in_local;       //表示是否处于local分析状态，即只选中一批与中心点相连的点
    bool is_in_start;       //是否处于初始状态
    bool is_in_filter;      //是否处于过滤状态
    bool is_spinBox_changed; //连接spinbox和slider

    int id_move_point; //代表被拖动点的id
    int id_select_point; //代表被选中的点的id
    int id_select_edge; //代表被选中的边

    int alpha_degree; //用于改变透明度达到切换渐变效果
    int data_change; //表示切换数据的阶段

    //点跟着鼠标走时，存储上一次事件鼠标位置，决定本次点的坐标变换
    int temp_x;
    int temp_y;

    //代表放大缩小比
    double my_scale;

    //虚拟画布尺寸
    int length;
    int width;
    int height;

    //存储主窗口大小
    int main_length;
    int main_width;

    //虚拟原点坐标
    vector<int> Opoint;

    //点的半径
    double radis;
    void setRadis(int temp){radis = temp;}

public:
    //构造析构函数
    explicit MainWindow(PaperConferenceAuthorGraph
 & temp, TopicGraph & temp1, QWidget * parent = 0);
    ~MainWindow();

    //设置点坐标并做动画
    void changeX(int i = 0, double d = 0){temp_point[i][0] += d;}
    void changeY(int i = 0, double d = 0){temp_point[i][1] += d;}
    void changeZ(int i = 0, double d = 0){temp_point[i][2] += d;}
    //void setPointWeight(int i = 0, double weight = 1){point_weight[i] = weight;}

    //初始化函数
    void setPointSize(int size);
    void initializeForStrategyP();
    void initializeForStrategyT();

private:
    void listPaperInformation(int i);
    //切换strategy的函数
    void setStrategy(Strategy s);
    QString readFileName();
    QString writeFileName();


private slots:
    void setMain(int x, int y){main_length = x; main_width = y;}
    void moveHonrizantly(int x){Opoint[0] += x; update();}
    void moveVerticly(int y){Opoint[1] += y; update();}
    //layout切换的动画函数
    void changeLayout();
    //切换数据的函数
    void changeData();
    //开始动画函数
    void changeDataStart();

    void on_actionCircular_triggered();

    void on_actionForce_triggered();

    void on_actionPaper_triggered();

    void on_actionTopic_triggered();

    void on_actionFilter_triggered();

    void on_actionPass_through_triggered();

    void on_actionFast_2D_triggered();

    void on_actionRandom_triggered();

    void on_actionSimple_2D_triggered();

    void on_actionClustering_2D_triggered();

    void on_actionCone_triggered();

    void on_actionCommunity_2D_triggered();

    void on_actionSave_triggered();

    void on_actionLoad_layout_triggered();

    void on_horizontalScrollBar_valueChanged(int value);

    void on_verticalScrollBar_valueChanged(int value);

    void on_actionStart_triggered();

    void on_node_out_slider_valueChanged(int value);

    void on_node_in_slider_valueChanged(int value);

    void on_node_sum_slider_valueChanged(int value);

    void on_weight_slider_valueChanged(int value);

    void on_actionSearch_triggered();

    void on_start_btn_clicked();

    void on_actionEdge_bundling_triggered();

    void on_actionSave_paper_node_triggered();

    void on_actionSave_paper_edge_triggered();

    void on_actionSave_topic_node_triggered();

    void on_actionSave_topic_edge_triggered();

    void on_actionSave_document_node_triggered();

    void on_actionLoad_paper_node_triggered();

    void on_actionLoad_paper_edge_triggered();

    void on_actionLoad_topic_node_triggered();

    void on_actionLoad_topic_edge_triggered();

    void on_actionLoad_document_node_triggered();

    void on_actionReset_triggered();

    void on_actionInteraction_edge_bundling_triggered();

    void on_toSpinBox_valueChanged(int arg1);

    void on_fromSpinBox_valueChanged(int arg1);

    void on_sumSpinBox_valueChanged(int arg1);

    void on_weightSpinBox_valueChanged(double arg1);

    void on_actionCartoon_triggered();

protected:
    //Event 列表
    void paintEvent(QPaintEvent * ev);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    bool isInCicle(int tx, int ty, int x, int y, int r);
    void mouseDoubleClickEvent(QMouseEvent * ev);
    //判断鼠标是否在某条边上
    bool inEdgeArea(double src_x, double src_y, double des_x, double des_y, double pos_x, double pos_y);
    //辅助坐标变换函数，从Opoint到实际画布坐标
    int calcX(int x);
    int calcY(int y);
    double calcInstance(double x1, double x2, double y1, double y2);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent * ev);
    void wheelEvent(QWheelEvent * ev);
    void resizeEvent(QResizeEvent *ev);

public:
    void setScale(int temp_l, int temp_w, int temp_h = 0){length = temp_l; width = temp_w; height = temp_h; radis = length / 300;} // 300为可调参数，调整点的大小
    void ChangeScale(double scale = 1);
    void setWidth(int temp_w){width = temp_w;}
    void setLength(int temp_l){length = temp_l;}
    void setHeight(int temp_h){height = temp_h;}

    void setOpoint(int x, int y, int z = 0){Opoint[0] = x; Opoint[1] = y; Opoint[2] = z;}
    int getWidth(){return width;}
    int getLength(){return length;}
    int getHeight(){return height;}



};

#endif // MAINWINDOW_H



