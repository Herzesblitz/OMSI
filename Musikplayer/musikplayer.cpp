/*
 * musikplayer.cpp
 *
 * 
 *      Author: Devin Kleiner 564838, Johannes Grobelski 565530, Ijjas Mihaly 569951
 */

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <array>

using namespace std;

int index=10;

double generiere_zufallszahl(){

				double z1= rand() %1000000+1;
				z1=z1/1000000;
				return z1;
 	}

int generiere_zufallszahl_bis_anzahl_der_Lieder(int anzahl_der_Lieder){

				int z1= rand() %anzahl_der_Lieder+1;
				return z1;
 	}
  


class Lied
{

	public:
	int index_Name;
	Lied(int i){
		index_Name = i;
	}



};




class Playlist
{
	public:
	int index_Anzahl;
	Lied* playlist[10]; //Zeiger fuer Lied
	double wichtung[10];
	int reihenfolge[10];



	Playlist()
	{
		index_Anzahl=0;
	}

  double getWichtung(int a) {
    return wichtung[a];
  }
  int getReihenfolge(int a) {
    return reihenfolge[a];
  }


	//Initialisierung
	void erstelle_Playlist(int platz)
	{
		index_Anzahl=10;
		for(int i=0; i<platz; i++){
			playlist[i] = new Lied(i);
			wichtung[i] = 0;
			reihenfolge[i] = i;
		}
	};

		//Bestimmt die neue Reihenfolge
	void generiere_Playlist()
	{
		double zufallszahl[10];
		for(int i=0; i<index;i++)
		{
			zufallszahl[i]= generiere_zufallszahl()*(wichtung[i]+1)*(wichtung[i]+1)*(wichtung[i]+1)*(wichtung[i]+1);
		}
		double max_zufallszahl = 0;
		int max_index;
		for(int i=0; i<index;i++)
		{

			for(int j=0; j<index;j++)
					{
						if (zufallszahl[j]>max_zufallszahl) {
							max_index = j;
							max_zufallszahl = zufallszahl[j];
						}
					}
			reihenfolge[index-1-i] = max_index;
			zufallszahl[max_index] = 0;
			max_zufallszahl=0;
		}

	};

	void next(double rank[]){
		for(int i=0; i<index;i++)
		{
			double zz=rank[i]*(1.0*generiere_zufallszahl_bis_anzahl_der_Lieder(index));
			//Anhand von einer Zufallszahl und der Wichtung wird errechnet, ob ein Lied uebersprungen wird
			if(zz<=5)
			{
				wichtung[i] += 1;
			}
			
		}


	}
};


class Musikspieler
{
	public:

	Playlist playlist;
	double like_Rang[10];

	Musikspieler(){
  };

  int getWichtung(int a) {
    return playlist.getWichtung(a);
  }
  Playlist getPlaylist() {
    return playlist;
  }

		void play()//Lernphase: die Playlist wird 1000-mal gespielt
		 {
			playlist.generiere_Playlist();
			for(int i=0;i<1000;i++)
			{
				playlist.next(like_Rang);
				playlist.generiere_Playlist();
			}

		 };

		void get_like_Rang(double Rank[])
		{
			for(int i=0;i<index;i++)
			{
				like_Rang[i]=Rank[i];
			}
		}

};


void pruefePlaylist(Musikspieler ms) { // Ausgabe der Matrix


  printf("Die Praeferenzen sind: \n");
  double matrix[10][10];
  //printf("GUT.\n");
  for (int i = 0; i < 10; i++) {
  printf(" %.2f,", ms.like_Rang[i]);
    for (int j = 0; j < 10; j++) {
      matrix[i][j]=0.0;
    }
  }
  
  for (int i = 0; i< 10000; i++) {
    ms.playlist.generiere_Playlist();
    for (int j = 0; j < 10; j++) {
      matrix[ms.getPlaylist().getReihenfolge(j)][j]++;
    }
  }
  printf("\n");
  for (int i = 0; i< 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf(" %4d ", (int) matrix[j][i]);
    }
    printf("\n");
  }
}



class Benutzer
{
		public:

	Musikspieler M;
	int anzahl_der_Lieder;
	double like_Rang[10]; //Benutzerpraeferenz




	public:


	Benutzer()
	{
		anzahl_der_Lieder=10; //Skalierung

				for(int i=0;i<index;i++)
				{
					like_Rang[i]=1;
				};
	}

	virtual void rang_bestimmen()
	{

	};

	void start() // die "main"-Funktion des Benutzers
	{
		M.get_like_Rang(like_Rang);
		M.play();
   
   
   pruefePlaylist(M);
	};



};

class Rang_Benutzer:Benutzer
{
public:

	Rang_Benutzer()
	{
								for(int i=0;i<index;i++)
								{
									like_Rang[i]=0;
								};
        rang_bestimmen();
	}

	void rang_bestimmen()
	{
		// erstelle like_Rang fuer die praeferierung der Lieder fuer den Benutzer
             int zufallszahl_rang[anzahl_der_Lieder];
             for (int j = 0; j < anzahl_der_Lieder; j++) {
               like_Rang[j] = generiere_zufallszahl();
             }
             
	}
	void start()
				{
          M.getPlaylist().erstelle_Playlist(index);
					M.get_like_Rang(like_Rang);
					M.play();
          pruefePlaylist(M);
				}
};

class AllvsOne_Benutzer:Benutzer
{
public:

	AllvsOne_Benutzer()
		{
									for(int i=0;i<index;i++)
									{
										like_Rang[i]=0;
									};
         rang_bestimmen();
		}
	void rang_bestimmen()
	{
		//Lied Nr.4 wird nie uebersprungen,Rest wird immer
		like_Rang[3]=1;
	}

	void start()
				{
					M.get_like_Rang(like_Rang);
					M.play();
          pruefePlaylist(M);
				}
};

class Gleichwarscheinlich_Benutzer:Benutzer
{
public:
	Gleichwarscheinlich_Benutzer()
{

							for(int i=0;i<index;i++)
							{
								like_Rang[i]=0;
							};
       rang_bestimmen();
}


	void rang_bestimmen()
	{
		for(int i=0;i<index;i++)
		{
			like_Rang[i]=0.1;
		};
	}
	void start()
				{
					M.get_like_Rang(like_Rang);
					M.play();
					         
          pruefePlaylist(M);
				}
	};
 
 
 class SchwererPraeferenz_Benutzer:Benutzer
{
public:
	SchwererPraeferenz_Benutzer()
{

							for(int i=0;i<index;i++)
							{
								like_Rang[i]=0;
							};
       rang_bestimmen();
}


	void rang_bestimmen()
	{
		for(int i=0;i<index;i++)
		{
			like_Rang[i]=(1-generiere_zufallszahl()/5)*((double)(i+1))*0.1;
		};
	}
	void start()
				{
					M.get_like_Rang(like_Rang);
					M.play();
					         
          pruefePlaylist(M);
				}
	};

int main(){
srand(time(NULL));


  printf("\n\n\n\n\n\n\n\n\n");
  printf("Benutzer:\n");
	Benutzer b1;
	b1.start();
	//--------
 
  printf("-----------------------------------------------------------\n");
  printf("Rang_Benutzer:\n");
	Rang_Benutzer b2;
	b2.start();
	//---------
 
  printf("-----------------------------------------------------------\n");
  printf("AllvsOne_Benutzer:\n");
	AllvsOne_Benutzer b3;
	b3.start();
	//--------------
 
  printf("-----------------------------------------------------------\n");
  printf("Gleichwahrscheinlich_Benutzer:\n");
	Gleichwarscheinlich_Benutzer b4;
	b4.start();
	//---------
 
  printf("-----------------------------------------------------------\n");
  printf("SchwererPraeferenz_Benutzer:\n");
	SchwererPraeferenz_Benutzer b5;
	b5.start();
	//---------


}
