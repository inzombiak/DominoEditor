/********************************************************************************
** Form generated from reading UI file 'QTBulletObjectSettingsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTBULLETOBJECTSETTINGSWIDGET_H
#define UI_QTBULLETOBJECTSETTINGSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTBulletObjectSettingsWidget
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_19;
    QLineEdit *objectName;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *shapeType;
    QSpacerItem *horizontalSpacer_6;
    QStackedWidget *shapeProperties;
    QWidget *page1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_16;
    QDoubleSpinBox *width;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_5;
    QDoubleSpinBox *height;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_17;
    QDoubleSpinBox *length;
    QSpacerItem *horizontalSpacer_10;
    QWidget *page2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_18;
    QDoubleSpinBox *radius;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QDoubleSpinBox *rotationX;
    QLabel *label_10;
    QDoubleSpinBox *rotationY;
    QLabel *label_9;
    QDoubleSpinBox *rotationZ;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_12;
    QDoubleSpinBox *positionX;
    QLabel *label_13;
    QDoubleSpinBox *positionY;
    QLabel *label_14;
    QDoubleSpinBox *positionZ;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QDoubleSpinBox *mass;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QDoubleSpinBox *friction;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_15;
    QDoubleSpinBox *rollingFriction;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *QTBulletObjectSettingsWidget)
    {
        if (QTBulletObjectSettingsWidget->objectName().isEmpty())
            QTBulletObjectSettingsWidget->setObjectName(QStringLiteral("QTBulletObjectSettingsWidget"));
        QTBulletObjectSettingsWidget->resize(303, 337);
        QTBulletObjectSettingsWidget->setMinimumSize(QSize(303, 0));
        QTBulletObjectSettingsWidget->setMaximumSize(QSize(303, 337));
        verticalLayout_4 = new QVBoxLayout(QTBulletObjectSettingsWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_19 = new QLabel(QTBulletObjectSettingsWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_19->setFont(font);

        horizontalLayout_13->addWidget(label_19);

        objectName = new QLineEdit(QTBulletObjectSettingsWidget);
        objectName->setObjectName(QStringLiteral("objectName"));
        sizePolicy.setHeightForWidth(objectName->sizePolicy().hasHeightForWidth());
        objectName->setSizePolicy(sizePolicy);

        horizontalLayout_13->addWidget(objectName);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_7);


        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(QTBulletObjectSettingsWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        shapeType = new QComboBox(QTBulletObjectSettingsWidget);
        shapeType->setObjectName(QStringLiteral("shapeType"));
        sizePolicy.setHeightForWidth(shapeType->sizePolicy().hasHeightForWidth());
        shapeType->setSizePolicy(sizePolicy);
        shapeType->setDuplicatesEnabled(false);

        horizontalLayout->addWidget(shapeType);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);


        verticalLayout_4->addLayout(horizontalLayout);

        shapeProperties = new QStackedWidget(QTBulletObjectSettingsWidget);
        shapeProperties->setObjectName(QStringLiteral("shapeProperties"));
        page1 = new QWidget();
        page1->setObjectName(QStringLiteral("page1"));
        verticalLayout_3 = new QVBoxLayout(page1);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_16 = new QLabel(page1);
        label_16->setObjectName(QStringLiteral("label_16"));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);
        label_16->setFont(font);

        horizontalLayout_9->addWidget(label_16);

        width = new QDoubleSpinBox(page1);
        width->setObjectName(QStringLiteral("width"));
        sizePolicy.setHeightForWidth(width->sizePolicy().hasHeightForWidth());
        width->setSizePolicy(sizePolicy);
        width->setValue(2.4);

        horizontalLayout_9->addWidget(width);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);


        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_5 = new QLabel(page1);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setFont(font);

        horizontalLayout_10->addWidget(label_5);

        height = new QDoubleSpinBox(page1);
        height->setObjectName(QStringLiteral("height"));
        sizePolicy.setHeightForWidth(height->sizePolicy().hasHeightForWidth());
        height->setSizePolicy(sizePolicy);
        height->setValue(4.8);

        horizontalLayout_10->addWidget(height);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_9);


        verticalLayout_3->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_17 = new QLabel(page1);
        label_17->setObjectName(QStringLiteral("label_17"));
        sizePolicy.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy);
        label_17->setFont(font);

        horizontalLayout_11->addWidget(label_17);

        length = new QDoubleSpinBox(page1);
        length->setObjectName(QStringLiteral("length"));
        sizePolicy.setHeightForWidth(length->sizePolicy().hasHeightForWidth());
        length->setSizePolicy(sizePolicy);
        length->setValue(0.75);

        horizontalLayout_11->addWidget(length);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_10);


        verticalLayout_3->addLayout(horizontalLayout_11);

        shapeProperties->addWidget(page1);
        page2 = new QWidget();
        page2->setObjectName(QStringLiteral("page2"));
        verticalLayout_2 = new QVBoxLayout(page2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_18 = new QLabel(page2);
        label_18->setObjectName(QStringLiteral("label_18"));
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        label_18->setFont(font);

        horizontalLayout_12->addWidget(label_18);

        radius = new QDoubleSpinBox(page2);
        radius->setObjectName(QStringLiteral("radius"));
        sizePolicy.setHeightForWidth(radius->sizePolicy().hasHeightForWidth());
        radius->setSizePolicy(sizePolicy);

        horizontalLayout_12->addWidget(radius);


        verticalLayout_2->addLayout(horizontalLayout_12);

        shapeProperties->addWidget(page2);

        verticalLayout_4->addWidget(shapeProperties);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(QTBulletObjectSettingsWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(QTBulletObjectSettingsWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_8 = new QLabel(QTBulletObjectSettingsWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_8);

        rotationX = new QDoubleSpinBox(QTBulletObjectSettingsWidget);
        rotationX->setObjectName(QStringLiteral("rotationX"));
        sizePolicy.setHeightForWidth(rotationX->sizePolicy().hasHeightForWidth());
        rotationX->setSizePolicy(sizePolicy);
        rotationX->setMaximum(360);

        horizontalLayout_2->addWidget(rotationX);

        label_10 = new QLabel(QTBulletObjectSettingsWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_10);

        rotationY = new QDoubleSpinBox(QTBulletObjectSettingsWidget);
        rotationY->setObjectName(QStringLiteral("rotationY"));
        sizePolicy.setHeightForWidth(rotationY->sizePolicy().hasHeightForWidth());
        rotationY->setSizePolicy(sizePolicy);
        rotationY->setMaximum(360);

        horizontalLayout_2->addWidget(rotationY);

        label_9 = new QLabel(QTBulletObjectSettingsWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_9);

        rotationZ = new QDoubleSpinBox(QTBulletObjectSettingsWidget);
        rotationZ->setObjectName(QStringLiteral("rotationZ"));
        sizePolicy.setHeightForWidth(rotationZ->sizePolicy().hasHeightForWidth());
        rotationZ->setSizePolicy(sizePolicy);
        rotationZ->setMaximum(360);

        horizontalLayout_2->addWidget(rotationZ);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(QTBulletObjectSettingsWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_12 = new QLabel(QTBulletObjectSettingsWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_12);

        positionX = new QDoubleSpinBox(QTBulletObjectSettingsWidget);
        positionX->setObjectName(QStringLiteral("positionX"));
        sizePolicy.setHeightForWidth(positionX->sizePolicy().hasHeightForWidth());
        positionX->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(positionX);

        label_13 = new QLabel(QTBulletObjectSettingsWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_13);

        positionY = new QDoubleSpinBox(QTBulletObjectSettingsWidget);
        positionY->setObjectName(QStringLiteral("positionY"));
        sizePolicy.setHeightForWidth(positionY->sizePolicy().hasHeightForWidth());
        positionY->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(positionY);

        label_14 = new QLabel(QTBulletObjectSettingsWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_14);

        positionZ = new QDoubleSpinBox(QTBulletObjectSettingsWidget);
        positionZ->setObjectName(QStringLiteral("positionZ"));
        sizePolicy.setHeightForWidth(positionZ->sizePolicy().hasHeightForWidth());
        positionZ->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(positionZ);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_4->addLayout(verticalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(QTBulletObjectSettingsWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setFont(font);

        horizontalLayout_6->addWidget(label_6);

        mass = new QDoubleSpinBox(QTBulletObjectSettingsWidget);
        mass->setObjectName(QStringLiteral("mass"));
        sizePolicy.setHeightForWidth(mass->sizePolicy().hasHeightForWidth());
        mass->setSizePolicy(sizePolicy);
        mass->setValue(1);

        horizontalLayout_6->addWidget(mass);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(QTBulletObjectSettingsWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setFont(font);

        horizontalLayout_7->addWidget(label_7);

        friction = new QDoubleSpinBox(QTBulletObjectSettingsWidget);
        friction->setObjectName(QStringLiteral("friction"));
        sizePolicy.setHeightForWidth(friction->sizePolicy().hasHeightForWidth());
        friction->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(friction);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_15 = new QLabel(QTBulletObjectSettingsWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        sizePolicy.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy);
        label_15->setFont(font);

        horizontalLayout_8->addWidget(label_15);

        rollingFriction = new QDoubleSpinBox(QTBulletObjectSettingsWidget);
        rollingFriction->setObjectName(QStringLiteral("rollingFriction"));
        sizePolicy.setHeightForWidth(rollingFriction->sizePolicy().hasHeightForWidth());
        rollingFriction->setSizePolicy(sizePolicy);

        horizontalLayout_8->addWidget(rollingFriction);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_8);


        retranslateUi(QTBulletObjectSettingsWidget);
        QObject::connect(shapeType, SIGNAL(currentIndexChanged(int)), shapeProperties, SLOT(setCurrentIndex(int)));
        QObject::connect(rotationY, SIGNAL(valueChanged(double)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(shapeType, SIGNAL(currentTextChanged(QString)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(width, SIGNAL(valueChanged(double)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(height, SIGNAL(valueChanged(double)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(length, SIGNAL(valueChanged(double)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(rotationZ, SIGNAL(valueChanged(double)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(rotationX, SIGNAL(valueChanged(double)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(positionX, SIGNAL(valueChanged(double)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(positionY, SIGNAL(valueChanged(double)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(positionZ, SIGNAL(valueChanged(double)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(mass, SIGNAL(valueChanged(double)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(friction, SIGNAL(valueChanged(QString)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(rollingFriction, SIGNAL(valueChanged(double)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(radius, SIGNAL(valueChanged(double)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));
        QObject::connect(objectName, SIGNAL(textChanged(QString)), QTBulletObjectSettingsWidget, SLOT(SettingsChanged()));

        shapeProperties->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QTBulletObjectSettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *QTBulletObjectSettingsWidget)
    {
        QTBulletObjectSettingsWidget->setWindowTitle(QApplication::translate("QTBulletObjectSettingsWidget", "QTBulletObjectSettingsWidget", 0));
        label_19->setText(QApplication::translate("QTBulletObjectSettingsWidget", "Object Name", 0));
        label->setText(QApplication::translate("QTBulletObjectSettingsWidget", "Shape Type", 0));
        shapeType->clear();
        shapeType->insertItems(0, QStringList()
         << QApplication::translate("QTBulletObjectSettingsWidget", "Box", 0)
         << QApplication::translate("QTBulletObjectSettingsWidget", "Sphere", 0)
        );
        label_16->setText(QApplication::translate("QTBulletObjectSettingsWidget", "Width", 0));
        label_5->setText(QApplication::translate("QTBulletObjectSettingsWidget", "Height", 0));
        label_17->setText(QApplication::translate("QTBulletObjectSettingsWidget", "Length", 0));
        label_18->setText(QApplication::translate("QTBulletObjectSettingsWidget", "Radius", 0));
        label_2->setText(QApplication::translate("QTBulletObjectSettingsWidget", "Motion State", 0));
        label_3->setText(QApplication::translate("QTBulletObjectSettingsWidget", "Rotation", 0));
        label_8->setText(QApplication::translate("QTBulletObjectSettingsWidget", "x", 0));
        label_10->setText(QApplication::translate("QTBulletObjectSettingsWidget", "y", 0));
        label_9->setText(QApplication::translate("QTBulletObjectSettingsWidget", "z", 0));
        label_4->setText(QApplication::translate("QTBulletObjectSettingsWidget", "Position", 0));
        label_12->setText(QApplication::translate("QTBulletObjectSettingsWidget", "x", 0));
        label_13->setText(QApplication::translate("QTBulletObjectSettingsWidget", "y", 0));
        label_14->setText(QApplication::translate("QTBulletObjectSettingsWidget", "z", 0));
        label_6->setText(QApplication::translate("QTBulletObjectSettingsWidget", "Mass", 0));
        label_7->setText(QApplication::translate("QTBulletObjectSettingsWidget", "Friction", 0));
        label_15->setText(QApplication::translate("QTBulletObjectSettingsWidget", "Rolling Friction", 0));
    } // retranslateUi

};

namespace Ui {
    class QTBulletObjectSettingsWidget: public Ui_QTBulletObjectSettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTBULLETOBJECTSETTINGSWIDGET_H
