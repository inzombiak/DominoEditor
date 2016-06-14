/********************************************************************************
** Form generated from reading UI file 'ForceSettingsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORCESETTINGSWIDGET_H
#define UI_FORCESETTINGSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTForceSettingsWidget
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;

    void setupUi(QWidget *QTForceSettingsWidget)
    {
        if (QTForceSettingsWidget->objectName().isEmpty())
            QTForceSettingsWidget->setObjectName(QStringLiteral("QTForceSettingsWidget"));
        QTForceSettingsWidget->resize(189, 239);
        layoutWidget = new QWidget(QTForceSettingsWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 30, 108, 48));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(layoutWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setMaximum(999);
        doubleSpinBox->setSingleStep(0.5);

        gridLayout->addWidget(doubleSpinBox, 0, 1, 1, 1);


        retranslateUi(QTForceSettingsWidget);
        QObject::connect(doubleSpinBox, SIGNAL(valueChanged(double)), QTForceSettingsWidget, SLOT(ForceValueChanged(double)));

        QMetaObject::connectSlotsByName(QTForceSettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *QTForceSettingsWidget)
    {
        QTForceSettingsWidget->setWindowTitle(QApplication::translate("QTForceSettingsWidget", "Form", 0));
        label->setText(QApplication::translate("QTForceSettingsWidget", "Force", 0));
    } // retranslateUi

};

namespace Ui {
    class QTForceSettingsWidget: public Ui_QTForceSettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORCESETTINGSWIDGET_H
