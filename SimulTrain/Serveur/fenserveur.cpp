#include "fenserveur.h"
#include "ui_fenserveur.h"

FenServeur::FenServeur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenServeur)
{
    ui->setupUi(this);

    // Gestion du serveur
        serveur = new QTcpServer(this);//objet du serveur

        serveur->listen(QHostAddress::Any, 1234); // Démarrage du serveur sur toutes les IP disponibles et sur le port

        ui->etatServeur->setText(("Le serveur a démarré sur le port ")+ QString::number(serveur->serverPort()));
        connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));

        tailleMessage = 0;

}

FenServeur::~FenServeur()
{
    delete ui;
}

void FenServeur::nouvelleConnexion()
{

    QTcpSocket *nouveauClient = serveur->nextPendingConnection();
    clients << nouveauClient;
    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
}


void FenServeur::donneesRecues()
{

        QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

        // Si tout va bien, on continue : on récupère le message
        QDataStream in(socket);
        if (tailleMessage == 0) // Si on ne connaît pas encore la taille du message, on essaie de la récupérer
        {
            if (socket->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas reçu la taille du message en entier
                 return;
            in >> tailleMessage; // Si on a reçu la taille du message en entier, on la récupère
        }
        // Si on connaît la taille du message, on vérifie si on a reçu le message en entier
        if (socket->bytesAvailable() < tailleMessage) // Si on n'a pas encore tout reçu, on arrête la méthode
            return;
        // Si ces lignes s'exécutent, c'est qu'on a reçu tout le message : on peut le récupérer !
        QString message;
        QString s1,s2,s3,s4;
        QString para;
        in >>s1>>message>>s2>>s3>>para>>s4;

        ui->BoiteDialog->append(s1+message+s2+s3+para+s4);

        //remise de la taille du message à 0 pour permettre la réception des futurs messages
        tailleMessage = 0;



}
