using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net.Sockets;
using System.Net;
using System.Threading;

namespace projet1
{
    /// <summary>
    /// Logique d'interaction pour MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ComRrail communication = null;
       String stats;

        //Constructeur: Initialisation des différents paramètres nécéssaires au moment du lancement de la fenêtre
        public MainWindow()
        {
           communication = new ComRrail(this);
            InitializeComponent();
            /*Thread comm = new Thread(new ThreadStart(ThreadStartingPoint));
            comm.SetApartmentState(ApartmentState.STA);
            comm.IsBackground = true;
            comm.Start();*/
        }

       /* private void ThreadStartingPoint()
        {
            Window win = new Window();
            win.Show();
            System.Windows.Threading.Dispatcher.Run();
        }*/

        //OnKeyDownHandler : Détecte et active les bouttons en fonction de la touche appuyée
        //Param d'entrée : object sender -> KeyDown, KeyEventArgs e -> Clavier
        //Param Sortie : 
        private void OnKeyDownHandler(object sender, KeyEventArgs e)
        {
            //Activation du disjoncteur principal
            if (e.Key == Key.D)
            {
                if (DDR1.IsChecked == false)
                    DDR1.IsChecked = true;
                else if (DDR1.IsChecked == true)
                    DDR1.IsChecked = false;
            }
            //Si le dijoncteur est allumé alors...
            if (DDR1.IsChecked == true)
            {
                //Allumage des feux
                if (e.Key == Key.F)
                {
                    if (VoyantFeu.IsChecked == false)
                        VoyantFeu.IsChecked = true;
                    else if (VoyantFeu.IsChecked == true)
                        VoyantFeu.IsChecked = false;
                }
                //Allumage des essuies glaces
                else if (e.Key == Key.S)
                {
                    if (BPEG.IsChecked == false)
                        BPEG.IsChecked = true;
                    else if (BPEG.IsChecked == true)
                        BPEG.IsChecked = false;
                }
                //Appui pour désactiver le vacma
                else if (e.Key == Key.E)
                {
                    if (VVacma.IsChecked == true)
                        VVacma.IsChecked = false;
                }
            }
        }
        
        //
        //
        private void EGSt(object sender, RoutedEventArgs e)
        {
            BPEG.IsEnabled = true;
            communication.connexion();
            stats = communication.getChaine();
            fff.Text = stats;
        }

        private void BPFeuclicked(object sender, RoutedEventArgs e)
        {
            if (BPFeu.IsChecked == true)
                communication.f1 = false;
            else
                communication.f1 = true;
            communication.connexion();
            stats = communication.getChaine();
            fff.Text = stats;
        }
        
    }

}
