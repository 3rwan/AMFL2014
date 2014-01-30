#ifndef FENCLIENT_H
#define FENCLIENT_H

#include <QMainWindow>
#include <QtNetwork>
#include <QDesktopWidget>




namespace Ui {
class FenClient;
}

class FenClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenClient(QWidget *parent = 0);
    ~FenClient();

private slots:
    void redimension();
    void on_BoutonConnexion_clicked();
    void donneesRecues();
    void connecte();
    void deconnecte();
    void erreurSocket(QAbstractSocket::SocketError erreur); 
    void on_Feux_clicked();
    void envoiFonction(const QString &message,int param);
    void on_SliderVitesse_sliderReleased();
    void on_SliderFrein_sliderReleased();

    void on_SensMarche_clicked();

    void on_Klaxonne_clicked();

    void on_ArretUrgence_clicked();

private:
    Ui::FenClient *ui;
    QTcpSocket *socket; //socket qui représentera la connexion au serveur,on l'utilise pour envoyer des paquets au serveur
    quint16 tailleMessage;//quint16 permet souvenir de la taille du message qu'il est en train de recevoir dans son slot donneesRecues()
};

#endif // FENCLIENT_H
