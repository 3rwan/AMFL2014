#ifndef FENSERVEUR_H
#define FENSERVEUR_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtGui>

namespace Ui {
class FenServeur;
}

class FenServeur : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenServeur(QWidget *parent = 0);
    ~FenServeur();


private slots:
    void donneesRecues();
    void nouvelleConnexion();




private:
    Ui::FenServeur *ui;
    QTcpServer *serveur;
    QTcpSocket *socket;
    QList<QTcpSocket *> clients; //un tableau dynamique qui contient la liste des clients connectés,chaque QTcpSocket de ce tableau représentera une connexion à un client.
    quint16 tailleMessage;
};

#endif // FENSERVEUR_H
