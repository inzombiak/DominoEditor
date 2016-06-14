/********************************************************************************
** Form generated from reading UI file 'dominoeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOMINOEDITOR_H
#define UI_DOMINOEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qtbulletobjectsettingswidget.h>
#include <qtforcesettingswidget.h>
#include "QTOpenGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_DominoEditorClass
{
public:
    QAction *actionForce;
    QAction *actionAdd_Object;
    QAction *actionDomino_Pattern;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter;
    QSplitter *splitter_2;
    QStackedWidget *stackedWidget;
    QTForceSettingsWidget *forceSettings;
    QGridLayout *gridLayout;
    QTBulletObjectSettingsWidget *objectSettings;
    QTBulletObjectSettingsWidget *objectProperties;
    QGridLayout *gridLayout_2;
    QTOpenGLWidget *openGLWidget;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *DominoEditorClass)
    {
        if (DominoEditorClass->objectName().isEmpty())
            DominoEditorClass->setObjectName(QStringLiteral("DominoEditorClass"));
        DominoEditorClass->resize(1140, 479);
        actionForce = new QAction(DominoEditorClass);
        actionForce->setObjectName(QStringLiteral("actionForce"));
        actionAdd_Object = new QAction(DominoEditorClass);
        actionAdd_Object->setObjectName(QStringLiteral("actionAdd_Object"));
        actionDomino_Pattern = new QAction(DominoEditorClass);
        actionDomino_Pattern->setObjectName(QStringLiteral("actionDomino_Pattern"));
        centralWidget = new QWidget(DominoEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter_2 = new QSplitter(splitter);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setMaximumSize(QSize(400, 16777215));
        splitter_2->setOrientation(Qt::Vertical);
        stackedWidget = new QStackedWidget(splitter_2);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setMaximumSize(QSize(400, 400));
        forceSettings = new QTForceSettingsWidget();
        forceSettings->setObjectName(QStringLiteral("forceSettings"));
        forceSettings->setMaximumSize(QSize(400, 400));
        gridLayout = new QGridLayout(forceSettings);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        stackedWidget->addWidget(forceSettings);
        objectSettings = new QTBulletObjectSettingsWidget();
        objectSettings->setObjectName(QStringLiteral("objectSettings"));
        objectSettings->setMinimumSize(QSize(0, 355));
        objectSettings->setMaximumSize(QSize(371, 337));
        stackedWidget->addWidget(objectSettings);
        splitter_2->addWidget(stackedWidget);
        objectProperties = new QTBulletObjectSettingsWidget(splitter_2);
        objectProperties->setObjectName(QStringLiteral("objectProperties"));
        gridLayout_2 = new QGridLayout(objectProperties);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter_2->addWidget(objectProperties);
        splitter->addWidget(splitter_2);
        openGLWidget = new QTOpenGLWidget(splitter);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        splitter->addWidget(openGLWidget);

        horizontalLayout_2->addWidget(splitter);

        DominoEditorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DominoEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DominoEditorClass->setStatusBar(statusBar);
        toolBar = new QToolBar(DominoEditorClass);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        DominoEditorClass->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionForce);
        toolBar->addAction(actionAdd_Object);
        toolBar->addAction(actionDomino_Pattern);

        retranslateUi(DominoEditorClass);
        QObject::connect(actionForce, SIGNAL(triggered(bool)), DominoEditorClass, SLOT(ShowForceEditor()));
        QObject::connect(actionAdd_Object, SIGNAL(triggered(bool)), DominoEditorClass, SLOT(ShowBulletObjectCreator()));
        QObject::connect(actionDomino_Pattern, SIGNAL(triggered(bool)), DominoEditorClass, SLOT(ShowDominoPatternEditor()));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DominoEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *DominoEditorClass)
    {
        DominoEditorClass->setWindowTitle(QApplication::translate("DominoEditorClass", "DominoEditor", 0));
        actionForce->setText(QApplication::translate("DominoEditorClass", "Force", 0));
#ifndef QT_NO_TOOLTIP
        actionForce->setToolTip(QApplication::translate("DominoEditorClass", "Apply force", 0));
#endif // QT_NO_TOOLTIP
        actionAdd_Object->setText(QApplication::translate("DominoEditorClass", "Add Object", 0));
#ifndef QT_NO_TOOLTIP
        actionAdd_Object->setToolTip(QApplication::translate("DominoEditorClass", "Add a basic object", 0));
#endif // QT_NO_TOOLTIP
        actionDomino_Pattern->setText(QApplication::translate("DominoEditorClass", "Domino Pattern", 0));
        toolBar->setWindowTitle(QApplication::translate("DominoEditorClass", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class DominoEditorClass: public Ui_DominoEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOMINOEDITOR_H
