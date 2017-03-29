/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCircular;
    QAction *actionForce;
    QAction *actionPaper;
    QAction *actionTopic;
    QAction *actionFilter;
    QAction *actionSearch;
    QAction *actionPass_through;
    QAction *actionFast_2D;
    QAction *actionRandom;
    QAction *actionSimple_2D;
    QAction *actionClustering_2D;
    QAction *actionCone;
    QAction *actionCommunity_2D;
    QAction *actionSave;
    QAction *actionLoad_layout;
    QAction *actionStart;
    QAction *actionEdge_bundling;
    QAction *actionSave_paper_node;
    QAction *actionSave_paper_edge;
    QAction *actionSave_topic_node;
    QAction *actionSave_topic_edge;
    QAction *actionSave_document_node;
    QAction *actionLoad_paper_node;
    QAction *actionLoad_paper_edge;
    QAction *actionLoad_topic_node;
    QAction *actionLoad_topic_edge;
    QAction *actionLoad_document_node;
    QAction *actionReset;
    QAction *actionInteraction_edge_bundling;
    QAction *actionCartoon;
    QWidget *centralWidget;
    QScrollBar *verticalScrollBar;
    QScrollBar *horizontalScrollBar;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *tool_box_layout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_3;
    QVBoxLayout *verticalLayout;
    QSlider *node_out_slider;
    QSlider *node_in_slider;
    QSlider *node_sum_slider;
    QSlider *weight_slider;
    QVBoxLayout *verticalLayout_5;
    QSpinBox *toSpinBox;
    QSpinBox *fromSpinBox;
    QSpinBox *sumSpinBox;
    QDoubleSpinBox *weightSpinBox;
    QPushButton *start_btn;
    QMenuBar *menuBar;
    QMenu *menuFiel;
    QMenu *menuSave_data;
    QMenu *menuLoad_data;
    QMenu *menuChange;
    QMenu *menuChange_mode;
    QMenu *menuTool;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(625, 476);
        MainWindow->setMouseTracking(true);
        actionCircular = new QAction(MainWindow);
        actionCircular->setObjectName(QStringLiteral("actionCircular"));
        actionForce = new QAction(MainWindow);
        actionForce->setObjectName(QStringLiteral("actionForce"));
        actionPaper = new QAction(MainWindow);
        actionPaper->setObjectName(QStringLiteral("actionPaper"));
        actionTopic = new QAction(MainWindow);
        actionTopic->setObjectName(QStringLiteral("actionTopic"));
        actionFilter = new QAction(MainWindow);
        actionFilter->setObjectName(QStringLiteral("actionFilter"));
        actionSearch = new QAction(MainWindow);
        actionSearch->setObjectName(QStringLiteral("actionSearch"));
        actionPass_through = new QAction(MainWindow);
        actionPass_through->setObjectName(QStringLiteral("actionPass_through"));
        actionFast_2D = new QAction(MainWindow);
        actionFast_2D->setObjectName(QStringLiteral("actionFast_2D"));
        actionRandom = new QAction(MainWindow);
        actionRandom->setObjectName(QStringLiteral("actionRandom"));
        actionSimple_2D = new QAction(MainWindow);
        actionSimple_2D->setObjectName(QStringLiteral("actionSimple_2D"));
        actionClustering_2D = new QAction(MainWindow);
        actionClustering_2D->setObjectName(QStringLiteral("actionClustering_2D"));
        actionCone = new QAction(MainWindow);
        actionCone->setObjectName(QStringLiteral("actionCone"));
        actionCommunity_2D = new QAction(MainWindow);
        actionCommunity_2D->setObjectName(QStringLiteral("actionCommunity_2D"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionLoad_layout = new QAction(MainWindow);
        actionLoad_layout->setObjectName(QStringLiteral("actionLoad_layout"));
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        actionEdge_bundling = new QAction(MainWindow);
        actionEdge_bundling->setObjectName(QStringLiteral("actionEdge_bundling"));
        actionSave_paper_node = new QAction(MainWindow);
        actionSave_paper_node->setObjectName(QStringLiteral("actionSave_paper_node"));
        actionSave_paper_edge = new QAction(MainWindow);
        actionSave_paper_edge->setObjectName(QStringLiteral("actionSave_paper_edge"));
        actionSave_topic_node = new QAction(MainWindow);
        actionSave_topic_node->setObjectName(QStringLiteral("actionSave_topic_node"));
        actionSave_topic_edge = new QAction(MainWindow);
        actionSave_topic_edge->setObjectName(QStringLiteral("actionSave_topic_edge"));
        actionSave_document_node = new QAction(MainWindow);
        actionSave_document_node->setObjectName(QStringLiteral("actionSave_document_node"));
        actionLoad_paper_node = new QAction(MainWindow);
        actionLoad_paper_node->setObjectName(QStringLiteral("actionLoad_paper_node"));
        actionLoad_paper_edge = new QAction(MainWindow);
        actionLoad_paper_edge->setObjectName(QStringLiteral("actionLoad_paper_edge"));
        actionLoad_topic_node = new QAction(MainWindow);
        actionLoad_topic_node->setObjectName(QStringLiteral("actionLoad_topic_node"));
        actionLoad_topic_edge = new QAction(MainWindow);
        actionLoad_topic_edge->setObjectName(QStringLiteral("actionLoad_topic_edge"));
        actionLoad_document_node = new QAction(MainWindow);
        actionLoad_document_node->setObjectName(QStringLiteral("actionLoad_document_node"));
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        actionInteraction_edge_bundling = new QAction(MainWindow);
        actionInteraction_edge_bundling->setObjectName(QStringLiteral("actionInteraction_edge_bundling"));
        actionCartoon = new QAction(MainWindow);
        actionCartoon->setObjectName(QStringLiteral("actionCartoon"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMouseTracking(true);
        verticalScrollBar = new QScrollBar(centralWidget);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(390, 10, 16, 160));
        verticalScrollBar->setOrientation(Qt::Vertical);
        horizontalScrollBar = new QScrollBar(centralWidget);
        horizontalScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(60, 240, 160, 16));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 20, 531, 261));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(208, 208, 208, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(231, 231, 231, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(104, 104, 104, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(139, 139, 139, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        groupBox->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Palatino Linotype"));
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setAlignment(Qt::AlignCenter);
        verticalLayoutWidget_3 = new QWidget(groupBox);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 20, 461, 191));
        tool_box_layout = new QVBoxLayout(verticalLayoutWidget_3);
        tool_box_layout->setSpacing(6);
        tool_box_layout->setContentsMargins(11, 11, 11, 11);
        tool_box_layout->setObjectName(QStringLiteral("tool_box_layout"));
        tool_box_layout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(verticalLayoutWidget_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setFamily(QStringLiteral("Palatino Linotype"));
        font1.setPointSize(12);
        font1.setItalic(true);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        label_4 = new QLabel(verticalLayoutWidget_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(verticalLayoutWidget_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_5);

        label_3 = new QLabel(verticalLayoutWidget_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        node_out_slider = new QSlider(verticalLayoutWidget_3);
        node_out_slider->setObjectName(QStringLiteral("node_out_slider"));
        node_out_slider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(node_out_slider);

        node_in_slider = new QSlider(verticalLayoutWidget_3);
        node_in_slider->setObjectName(QStringLiteral("node_in_slider"));
        node_in_slider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(node_in_slider);

        node_sum_slider = new QSlider(verticalLayoutWidget_3);
        node_sum_slider->setObjectName(QStringLiteral("node_sum_slider"));
        node_sum_slider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(node_sum_slider);

        weight_slider = new QSlider(verticalLayoutWidget_3);
        weight_slider->setObjectName(QStringLiteral("weight_slider"));
        weight_slider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(weight_slider);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        toSpinBox = new QSpinBox(verticalLayoutWidget_3);
        toSpinBox->setObjectName(QStringLiteral("toSpinBox"));

        verticalLayout_5->addWidget(toSpinBox);

        fromSpinBox = new QSpinBox(verticalLayoutWidget_3);
        fromSpinBox->setObjectName(QStringLiteral("fromSpinBox"));

        verticalLayout_5->addWidget(fromSpinBox);

        sumSpinBox = new QSpinBox(verticalLayoutWidget_3);
        sumSpinBox->setObjectName(QStringLiteral("sumSpinBox"));

        verticalLayout_5->addWidget(sumSpinBox);

        weightSpinBox = new QDoubleSpinBox(verticalLayoutWidget_3);
        weightSpinBox->setObjectName(QStringLiteral("weightSpinBox"));

        verticalLayout_5->addWidget(weightSpinBox);


        horizontalLayout->addLayout(verticalLayout_5);


        tool_box_layout->addLayout(horizontalLayout);

        start_btn = new QPushButton(centralWidget);
        start_btn->setObjectName(QStringLiteral("start_btn"));
        start_btn->setGeometry(QRect(250, 380, 91, 31));
        QPalette palette1;
        QBrush brush7(QColor(240, 240, 240, 0));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush7);
        start_btn->setPalette(palette1);
        QFont font2;
        font2.setFamily(QStringLiteral("Palatino Linotype"));
        font2.setPointSize(14);
        font2.setItalic(true);
        start_btn->setFont(font2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 625, 26));
        menuFiel = new QMenu(menuBar);
        menuFiel->setObjectName(QStringLiteral("menuFiel"));
        menuFiel->setMaximumSize(QSize(159, 150));
        menuSave_data = new QMenu(menuFiel);
        menuSave_data->setObjectName(QStringLiteral("menuSave_data"));
        menuLoad_data = new QMenu(menuFiel);
        menuLoad_data->setObjectName(QStringLiteral("menuLoad_data"));
        menuChange = new QMenu(menuBar);
        menuChange->setObjectName(QStringLiteral("menuChange"));
        menuChange_mode = new QMenu(menuBar);
        menuChange_mode->setObjectName(QStringLiteral("menuChange_mode"));
        menuTool = new QMenu(menuBar);
        menuTool->setObjectName(QStringLiteral("menuTool"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFiel->menuAction());
        menuBar->addAction(menuChange->menuAction());
        menuBar->addAction(menuChange_mode->menuAction());
        menuBar->addAction(menuTool->menuAction());
        menuFiel->addAction(actionSave);
        menuFiel->addAction(menuSave_data->menuAction());
        menuFiel->addAction(actionLoad_layout);
        menuFiel->addAction(menuLoad_data->menuAction());
        menuSave_data->addAction(actionSave_paper_node);
        menuSave_data->addAction(actionSave_paper_edge);
        menuSave_data->addAction(actionSave_topic_node);
        menuSave_data->addAction(actionSave_topic_edge);
        menuSave_data->addAction(actionSave_document_node);
        menuLoad_data->addAction(actionLoad_paper_node);
        menuLoad_data->addAction(actionLoad_paper_edge);
        menuLoad_data->addAction(actionLoad_topic_node);
        menuLoad_data->addAction(actionLoad_topic_edge);
        menuLoad_data->addAction(actionLoad_document_node);
        menuChange->addAction(actionCircular);
        menuChange->addAction(actionForce);
        menuChange->addAction(actionPass_through);
        menuChange->addAction(actionFast_2D);
        menuChange->addAction(actionRandom);
        menuChange->addAction(actionSimple_2D);
        menuChange->addAction(actionClustering_2D);
        menuChange->addAction(actionCone);
        menuChange->addAction(actionCommunity_2D);
        menuChange->addAction(actionStart);
        menuChange_mode->addAction(actionPaper);
        menuChange_mode->addAction(actionTopic);
        menuTool->addAction(actionFilter);
        menuTool->addAction(actionSearch);
        menuTool->addAction(actionEdge_bundling);
        menuTool->addAction(actionReset);
        menuTool->addAction(actionInteraction_edge_bundling);
        menuTool->addAction(actionCartoon);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionCircular->setText(QApplication::translate("MainWindow", "circular", 0));
        actionForce->setText(QApplication::translate("MainWindow", "force directed", 0));
        actionPaper->setText(QApplication::translate("MainWindow", "paper", 0));
        actionTopic->setText(QApplication::translate("MainWindow", "topic", 0));
        actionFilter->setText(QApplication::translate("MainWindow", "filter", 0));
        actionSearch->setText(QApplication::translate("MainWindow", "search", 0));
        actionPass_through->setText(QApplication::translate("MainWindow", "pass through", 0));
        actionFast_2D->setText(QApplication::translate("MainWindow", "fast 2D", 0));
        actionRandom->setText(QApplication::translate("MainWindow", "random", 0));
        actionSimple_2D->setText(QApplication::translate("MainWindow", "simple 2D", 0));
        actionClustering_2D->setText(QApplication::translate("MainWindow", "clustering 2D", 0));
        actionCone->setText(QApplication::translate("MainWindow", "new layout", 0));
        actionCommunity_2D->setText(QApplication::translate("MainWindow", "line layout", 0));
        actionSave->setText(QApplication::translate("MainWindow", "save layout", 0));
        actionLoad_layout->setText(QApplication::translate("MainWindow", "load layout", 0));
        actionStart->setText(QApplication::translate("MainWindow", "start", 0));
        actionEdge_bundling->setText(QApplication::translate("MainWindow", "edge bundling", 0));
        actionSave_paper_node->setText(QApplication::translate("MainWindow", "save paper node", 0));
        actionSave_paper_edge->setText(QApplication::translate("MainWindow", "save paper edge", 0));
        actionSave_topic_node->setText(QApplication::translate("MainWindow", "save topic node", 0));
        actionSave_topic_edge->setText(QApplication::translate("MainWindow", "save topic edge", 0));
        actionSave_document_node->setText(QApplication::translate("MainWindow", "save document node", 0));
        actionLoad_paper_node->setText(QApplication::translate("MainWindow", "load paper node", 0));
        actionLoad_paper_edge->setText(QApplication::translate("MainWindow", "load paper edge", 0));
        actionLoad_topic_node->setText(QApplication::translate("MainWindow", "load topic node", 0));
        actionLoad_topic_edge->setText(QApplication::translate("MainWindow", "load topic edge", 0));
        actionLoad_document_node->setText(QApplication::translate("MainWindow", "load document node", 0));
        actionReset->setText(QApplication::translate("MainWindow", "reset", 0));
        actionInteraction_edge_bundling->setText(QApplication::translate("MainWindow", "interaction edge bundling", 0));
        actionCartoon->setText(QApplication::translate("MainWindow", "cartoon", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Tool Box", 0));
        label_2->setText(QApplication::translate("MainWindow", "line to the node :", 0));
        label_4->setText(QApplication::translate("MainWindow", "line from the node :", 0));
        label_5->setText(QApplication::translate("MainWindow", "line sum :", 0));
        label_3->setText(QApplication::translate("MainWindow", "edge weight :", 0));
        start_btn->setText(QApplication::translate("MainWindow", "start", 0));
        menuFiel->setTitle(QApplication::translate("MainWindow", "file", 0));
        menuSave_data->setTitle(QApplication::translate("MainWindow", "save data", 0));
        menuLoad_data->setTitle(QApplication::translate("MainWindow", "load data", 0));
        menuChange->setTitle(QApplication::translate("MainWindow", "layout", 0));
        menuChange_mode->setTitle(QApplication::translate("MainWindow", "data", 0));
        menuTool->setTitle(QApplication::translate("MainWindow", "tool", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
