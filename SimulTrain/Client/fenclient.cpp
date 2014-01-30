#include "fenclient.h"
#include "ui_fenclient.h"


FenClient::FenClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenClient)
{
    ui->setupUi(this);

    redimension();

    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));
    connect(ui->SliderVitesse, SIGNAL(valueChanged(int)),ui->lcdNumber, SLOT(display(int)));
    connect(ui->SliderFrein, SIGNAL(valueChanged(int)),ui->lcdNumber2, SLOT(display(int)));
    connect(ui->SliderVitesse, SIGNAL(sliderReleased()),this, SLOT(on_SliderVitesse_valueChanged()));
    connect(ui->SliderFrein, SIGNAL(sliderReleased()),this, SLOT(on_SliderFrein_valueChanged()));

    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat); //pour être plus lisible
    ui->lcdNumber2->setSegmentStyle(QLCDNumber::Flat);

    ui->verticalLayout->alignment();

    tailleMessage = 0;// pour permettre la réception de nouveaux messages.
}

FenClient::~FenClient()
{
    delete ui;
}

void FenClient::redimension()
{
   int hauteurEcran=QApplication::desktop()->screenGeometry().height();
   int largeurEcran=QApplication::desktop()->screenGeometry().width();


   this->setGeometry((largeurEcran-largeurEcran*0.95), (hauteurEcran-hauteurEcran*0.95), largeurEcran*0.85, hauteurEcran*0.85);
   //this->setGeometry(0, 0, largeurEcran*0.85, hauteurEcran*0.85); // Pour Android

   ui->BoiteDialog->append(QString::number(hauteurEcran)+"/"+QString::number(largeurEcran));
}



void FenClient::on_BoutonConnexion_clicked()
{
    ui->BoiteDialog->append("Tentative de connexion..."); //append mettre à la suite
    ui->BoutonConnexion->setEnabled(false);// désactive temporairement le bouton "Connexion"

    socket->abort();// On désactive les connexions précédentes s'il y en a
    socket->connectToHost(ui->serveurIP->text(), ui->serveurPort->value()); // On se connecte au serveur demandé

}

void FenClient::donneesRecues()
{
    //on recupere la taille du message on compare avec la taille annoncé tailleMessage
    QDataStream in(socket);
    if (tailleMessage == 0)
       {
           if (socket->bytesAvailable() < (int)sizeof(quint16))
                return;
            in >> tailleMessage;
       }

        if (socket->bytesAvailable() < tailleMessage)
            return;

        //recupere le message entier
        QString messageRecu;
        in >> messageRecu;

        //on l'affiche dans la textbox
        ui->BoiteDialog->append(messageRecu);

        //remet la taille du message à 0 pour pouvoir recevoir de futurs messages
         tailleMessage = 0;
}

void FenClient::connecte()
{
    //quand conection au serveur
    ui->BoiteDialog->append("Connecté");

    ui->BoutonConnexion->setEnabled(true);//réactive le bouton connexion pour permettre un nouvelle connexion

}

void FenClient::deconnecte()
{
    ui->BoiteDialog->append("Déconnecté du serveur");
}


void FenClient::erreurSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
    {
        case QAbstractSocket::HostNotFoundError:
            ui->BoiteDialog->append("ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.");
            break;
        case QAbstractSocket::ConnectionRefusedError:
             ui->BoiteDialog->append("ERREUR : le serveur a refusé la connexion. Vérifiez si le programme serveur a bien été lancé. Vérifiez aussi l'IP et le port.");
            break;
        case QAbstractSocket::RemoteHostClosedError:
             ui->BoiteDialog->append("ERREUR : le serveur a coupé la connexion.");
            break;
        default:
             ui->BoiteDialog->append(("ERREUR : ")  + socket->errorString());//affiche le message d'erreur envoyé par la socket
    }
    ui->BoutonConnexion->setEnabled(true);
}


void FenClient::envoiFonction(const QString &fonction , int param)
{
    QByteArray paquet;//dans QByteArray on va écrire le paquet qu'on veut envoyer.
    QDataStream out(&paquet,QIODevice::WriteOnly);

    ui->BoiteDialog->append(fonction + " " + QString::number(param));

    //Calcule la taille du message
    out<<(quint16) 0;// On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out<<QString("<fonct>")<<fonction<<QString("</fonct>")<<QString("<para>")<<QString::number(param)<<QString("</para>"); // On ajoute le message à la suite
    out.device()->seek(0);// On se replace au début du paquet
    out<<(quint16) (paquet.size()-sizeof(quint16));// On écrase le 0 qu'on avait réservé par la longueur du message paquet.size()taille de la trame total -sizeof(quint16)c'est le paquet taillemessage

    socket->write(paquet);//On envoie le paquet
}


bool b = false;
void FenClient::on_Feux_clicked()
{
    if(b == false){
        b=true;
        ui->Feux->setText("Feux Off");
        envoiFonction("feux",1);
    }
    else{
        b=false;
        ui->Feux->setText("Feux On");
        envoiFonction("feux",0);
    }

}


bool a = false;
void FenClient::on_SensMarche_clicked()
{
    if(a == false){
        a=true;
        ui->SensMarche->setText("Avant");
        envoiFonction("sens",0);
    }
    else{
        a=false;
        ui->SensMarche->setText("Arriére");
        envoiFonction("sens",1);
    }

}


void FenClient::on_Klaxonne_clicked()
{
    envoiFonction("klaxonne",1);
}


void FenClient::on_ArretUrgence_clicked()
{
    envoiFonction("ArretUrgence",1);
}



void FenClient::on_SliderVitesse_sliderReleased()
{
    envoiFonction("vitesse",ui->SliderVitesse->value());
}



void FenClient::on_SliderFrein_sliderReleased()
{
    envoiFonction("frein",ui->SliderFrein->value());
}




