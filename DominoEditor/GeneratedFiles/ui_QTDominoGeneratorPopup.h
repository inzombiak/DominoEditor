/********************************************************************************
** Form generated from reading UI file 'QTDominoGeneratorPopup.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDOMINOGENERATORPOPUP_H
#define UI_QTDOMINOGENERATORPOPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qtbulletobjectsettingswidget.h"
#include "qtgridview.h"

QT_BEGIN_NAMESPACE

class Ui_QTDominoGeneratorPopup
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *columns;
    QLabel *label_2;
    QSpinBox *rows;
    QLabel *label_4;
    QDoubleSpinBox *xSpacing;
    QLabel *label_5;
    QDoubleSpinBox *zSpacing;
    QLabel *label_3;
    QDoubleSpinBox *heightSpacing;
    QPushButton *pushButton;
    QTBulletObjectSettingsWidget *objectSettings;
    QPushButton *pushButton_2;
    QTGridView *graphicsView;

    void setupUi(QWidget *QTDominoGeneratorPopup)
    {
        if (QTDominoGeneratorPopup->objectName().isEmpty())
            QTDominoGeneratorPopup->setObjectName(QStringLiteral("QTDominoGeneratorPopup"));
        QTDominoGeneratorPopup->resize(876, 596);
        horizontalLayout = new QHBoxLayout(QTDominoGeneratorPopup);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetFixedSize);
        label = new QLabel(QTDominoGeneratorPopup);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(39, 20));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        columns = new QSpinBox(QTDominoGeneratorPopup);
        columns->setObjectName(QStringLiteral("columns"));
        sizePolicy.setHeightForWidth(columns->sizePolicy().hasHeightForWidth());
        columns->setSizePolicy(sizePolicy);
        columns->setMinimumSize(QSize(75, 20));
        columns->setMinimum(1);
        columns->setMaximum(100);
        columns->setValue(10);

        formLayout->setWidget(0, QFormLayout::FieldRole, columns);

        label_2 = new QLabel(QTDominoGeneratorPopup);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(39, 20));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        rows = new QSpinBox(QTDominoGeneratorPopup);
        rows->setObjectName(QStringLiteral("rows"));
        sizePolicy.setHeightForWidth(rows->sizePolicy().hasHeightForWidth());
        rows->setSizePolicy(sizePolicy);
        rows->setMinimumSize(QSize(75, 20));
        rows->setMinimum(1);
        rows->setMaximum(100);
        rows->setValue(10);

        formLayout->setWidget(1, QFormLayout::FieldRole, rows);

        label_4 = new QLabel(QTDominoGeneratorPopup);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        xSpacing = new QDoubleSpinBox(QTDominoGeneratorPopup);
        xSpacing->setObjectName(QStringLiteral("xSpacing"));
        sizePolicy.setHeightForWidth(xSpacing->sizePolicy().hasHeightForWidth());
        xSpacing->setSizePolicy(sizePolicy);
        xSpacing->setDecimals(1);
        xSpacing->setMinimum(0.1);
        xSpacing->setMaximum(2);
        xSpacing->setSingleStep(0.1);

        formLayout->setWidget(2, QFormLayout::FieldRole, xSpacing);

        label_5 = new QLabel(QTDominoGeneratorPopup);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        zSpacing = new QDoubleSpinBox(QTDominoGeneratorPopup);
        zSpacing->setObjectName(QStringLiteral("zSpacing"));
        sizePolicy.setHeightForWidth(zSpacing->sizePolicy().hasHeightForWidth());
        zSpacing->setSizePolicy(sizePolicy);
        zSpacing->setDecimals(1);
        zSpacing->setMinimum(0.1);
        zSpacing->setMaximum(2);
        zSpacing->setSingleStep(0.1);

        formLayout->setWidget(3, QFormLayout::FieldRole, zSpacing);

        label_3 = new QLabel(QTDominoGeneratorPopup);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_3);

        heightSpacing = new QDoubleSpinBox(QTDominoGeneratorPopup);
        heightSpacing->setObjectName(QStringLiteral("heightSpacing"));
        sizePolicy.setHeightForWidth(heightSpacing->sizePolicy().hasHeightForWidth());
        heightSpacing->setSizePolicy(sizePolicy);
        heightSpacing->setDecimals(1);
        heightSpacing->setMinimum(0.1);
        heightSpacing->setMaximum(0.9);
        heightSpacing->setSingleStep(0.1);

        formLayout->setWidget(4, QFormLayout::FieldRole, heightSpacing);


        verticalLayout->addLayout(formLayout);

        pushButton = new QPushButton(QTDominoGeneratorPopup);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(75, 23));
        pushButton->setMaximumSize(QSize(75, 23));

        verticalLayout->addWidget(pushButton);

        objectSettings = new QTBulletObjectSettingsWidget(QTDominoGeneratorPopup);
        objectSettings->setObjectName(QStringLiteral("objectSettings"));

        verticalLayout->addWidget(objectSettings);

        pushButton_2 = new QPushButton(QTDominoGeneratorPopup);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(75, 23));
        pushButton_2->setMaximumSize(QSize(75, 23));

        verticalLayout->addWidget(pushButton_2);


        horizontalLayout->addLayout(verticalLayout);

        graphicsView = new QTGridView(QTDominoGeneratorPopup);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout->addWidget(graphicsView);


        retranslateUi(QTDominoGeneratorPopup);
        QObject::connect(pushButton, SIGNAL(clicked(bool)), QTDominoGeneratorPopup, SLOT(GenerateGrid()));
        QObject::connect(pushButton_2, SIGNAL(clicked(bool)), QTDominoGeneratorPopup, SLOT(Save()));

        QMetaObject::connectSlotsByName(QTDominoGeneratorPopup);
    } // setupUi

    void retranslateUi(QWidget *QTDominoGeneratorPopup)
    {
        QTDominoGeneratorPopup->setWindowTitle(QApplication::translate("QTDominoGeneratorPopup", "QTDominoGeneratorPopup", 0));
        label->setText(QApplication::translate("QTDominoGeneratorPopup", "Columns", 0));
        label_2->setText(QApplication::translate("QTDominoGeneratorPopup", "Rows", 0));
        label_4->setText(QApplication::translate("QTDominoGeneratorPopup", "X Spacing", 0));
        label_5->setText(QApplication::translate("QTDominoGeneratorPopup", "Z Spacing", 0));
        label_3->setText(QApplication::translate("QTDominoGeneratorPopup", "Height Spacing", 0));
        pushButton->setText(QApplication::translate("QTDominoGeneratorPopup", "Generate", 0));
        pushButton_2->setText(QApplication::translate("QTDominoGeneratorPopup", "Save", 0));
    } // retranslateUi

};

namespace Ui {
    class QTDominoGeneratorPopup: public Ui_QTDominoGeneratorPopup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDOMINOGENERATORPOPUP_H
