using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using System.Text.RegularExpressions;


namespace projet1
{
    class ComRrail
    {
        public MainWindow windowe;
            //Adresse IP du serveur
        public String IP = "127.0.0.1";
            //port serveur
        public int port = 8051;

        public bool threadstatut = false;

            //Statut des fonctions gardées dans la classe/fenêtre
        public bool f0 = true, f1 = true, f2 = true, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28;
            
            //Taille de la chaine qui sera mise dans le XML
        public int taille;

            //Identifiant du wagon
        public string id = "E03";

            //Entête de la trame XML
        public string entete = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><xmlh>\n<xml size=\"";

            //Chaines Finales et temporaires
        public string chaineF;
        public string chaineT;
        public string chainerecue;
        Socket sock;
        IPEndPoint iep;
        Thread getReadClients = null;
        System.IO.StreamWriter file = null;

        public ComRrail(MainWindow wee)
        {
            windowe = wee;
            getReadClients = new Thread(new ThreadStart(getRead));
            file = new System.IO.StreamWriter(@"D:\IRIS2014\paphassarangc\WriteText.txt", true);
        }

        private void getRead()
        {
            byte[] buffers = new byte[1024];
            while (true)
            {
                sock.Receive(buffers);
                Console.WriteLine(System.Text.ASCIIEncoding.ASCII.GetString(buffers));
                chainerecue = System.Text.ASCIIEncoding.ASCII.GetString(buffers);
                traitement(chainerecue);
                file.Write(chainerecue);
            }
        }

        public int traitement(string texte)
        {
            string re1 = "id=\"(.*?)\""; // Identifiant du train
            string re2 = "V=\"(.*?)\""; //Vitesse du train 
            string re3 = "f.?=\"(.*?)\"";

            Regex r = new Regex(re1);
            Regex r1 = new Regex(re2);
            Regex r2 = new Regex(re3);

            Match m = r.Match(texte);
            if (m.Success)
            {
                String string1 = m.Groups[1].ToString();          
            }

            Match m1 = r1.Match(texte);
            if (m1.Success)
            {
                String string2 = m.Groups[1].ToString();
            }

            Match m2 = r2.Match(texte);
            if (m2.Success)
            {
                String string3 = m.Groups[1].ToString();
                String string4 = m.Groups[2].ToString();
                Console.WriteLine(string3);
                Console.WriteLine(string4);
            }
            
            return 0;
        }

        public String getChaine()
        {
            return chainerecue;
        }

        //Generateur : Génère une chaine en fonction des différents statuts de booléens. 
        //Peut aller jusqu'a 28 fonctions rocrail prises en charges (true or false)
        //Param d'entrée: Booléens de  f0 à f28
        //Param Sortie: chaineF chaine finie et générée
        public String generateur()
        {
            chaineT = "<fn group=\"1\" fnchanged=\"1\" fncnt=\"4\" id=\"" + id + "\" " + "f0=\"" + f0 + "\" " + "f1=\"" + f1 + "\" " + "f2=\"" + f2 + "\" " + "f3=\"" + f3 + "\" " + "f4=\"" + f4 + "\" " + "f5=\"" + f5 + "\" " + "f6=\"" + f6 + "\" " + "f7=\"" + f7 + "\" " + "f8=\"" + f8 + "\" " + "f9=\"" + f9 + "\" " + "f10=\"" + f10 + "\" " + "f11=\"" + f11 + "\" " + "f12=\"" + f12 + "\" " + "f13=\"" + f13 + "\" " + "f14=\"" + f14 + "\" " + "f15=\"" + f15 + "\" " + "f16=\"" + f16 + "\" " + "f17=\"" + f17 + "\" " + "f18=\"" + f18 + "\" " + "f19=\"" + f19 + "\" " + "f20=\"" + f20 + "\" " + "f21=\"" + f21 + "\" " + "f22=\"" + f22 + "\" " + "f23=\"" + f23 + "\" " + "f24=\"" + f24 + "\" " + "f25=\"" + f25 + "\" " + "f26=\"" + f26 + "\" " + "f27=\"" + f27 + "\" " + "f28=\"" + f28 + "\"/>";
            taille = chaineT.Length + 2;
            chaineF = entete + taille + "\"/>" + "\n" + "</xmlh>" + chaineT;
            return chaineF;
        }

        public bool connexion()
        {
            sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            iep = new IPEndPoint(IPAddress.Parse(IP), port);
            sock.Connect(iep);
            if (sock.Connected)
            {
                byte[] buffer = new byte[512];
                buffer = System.Text.ASCIIEncoding.ASCII.GetBytes(generateur());
                sock.Send(buffer);                
                chaineF = "\0";
                if (threadstatut == false)
                {
                    getReadClients.Start();
                    threadstatut = true;
                }

                return true;
                
            }
            return false;

        }

    }
}
