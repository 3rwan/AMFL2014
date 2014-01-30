/********************************************************************************
** Form generated from reading UI file 'fenserveur.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENSERVEUR_H
#define UI_FENSERVEUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FenServeur
{
public:
    QWidget *centralWidget;
    QLabel *etatServeur;
    QTextEdit *BoiteDialog;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FenServeur)
    {
        if (FenServeur->objectName().isEmpty())
            FenServeur->setObjectName(QStringLiteral("FenServeur"));
        FenServeur->resize(538, 394);
        centralWidget = new QWidget(FenServeur);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        etatServeur = new QLabel(centralWidget);
        etatServeur->setObjectName(QStringLiteral("etatServeur"));
        etatServeur->setGeometry(QRect(20, 10, 221, 81));
        BoiteDialog = new QTextEdit(centralWidget);
        BoiteDialog->setObjectName(QStringLiteral("BoiteDialog"));
        BoiteDialog->setGeometry(QRect(60, 150, 391, 151));
        FenServeur->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FenServeur);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 538, 21));
        FenServeur->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FenServeur);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FenServeur->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FenServeur);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FenServeur->setStatusBar(statusBar);

        retranslateUi(FenServeur);

        QMetaObject::connectSlotsByName(FenServeur);
    } // setupUi

    void retranslateUi(QMainWindow *FenServeur)
    {
        FenServeur->setWindowTitle(QApplication::translate("FenServeur", "FenServeur", 0));
        etatServeur->setText(QApplication::translate("FenServeur", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class FenServeur: public Ui_FenServeur {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENSERVEUR_H
