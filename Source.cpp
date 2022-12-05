#include <iostream>
#include <string>

//N�m� kaksi seuraavaa mahdollistavat varausnumeron satunnaisgeneroinnin ja ajan k�ytt�misen generoinnin seedin�
#include <cstdlib>
#include <time.h>

//T�m�n kirjaston avulla voidaan k�ytt�� mm. isdigit() funktiota sy�tteen tarkistukseen
#include <ctype.h>

struct Hotellihuone {
	bool varaustilanne;
	int varausnumero;
	int yot;
	int hinta;
	std::string varaaja, sposti, puhnro;
};

Hotellihuone huoneiden_teko();
int main_menu();
Hotellihuone huoneen_varaus(Hotellihuone h[]);
void varauksen_tarkastelu(Hotellihuone h[]);

const int huonemaara = 260; //Hotellihuone taulukon koko eli hotellihuoneiden m��r�



int main() { //Main funktio vain kutsuu muita aliohjelmia riippuen mit� main_menu aliohjelma palauttaa
	setlocale(LC_ALL, "fi_FI"); //Setlocale antaa mahdollisuuden k�ytt�� ��kk�si� ohjelman tulostuksissa
	Hotellihuone huone_lista[huonemaara];
	for (int i = 0; i < huonemaara; i++) {
		huone_lista[i] = huoneiden_teko();
	}
	while (true) {
		int palautus = main_menu();

		if (palautus == 1) {
			huoneen_varaus(huone_lista);
		}
		else if (palautus == 2) {
			varauksen_tarkastelu(huone_lista);
		}
		else if (palautus == 3){
			std::cout << "N�kemiin!";
			break;
		}
	}
	return 0;
}
int main_menu() {//P��valikko aliohjelma, t�st� liikutaan muihin aliohjelmiin mainin kautta k�ytt�j�n valinnan mukaisesti
	char valinta;
	do {
		std::cout << "Tervetuloa Rantahotellin varausj�rjestelm��n!\n";
		std::cout << "Mit� haluaisit tehd�? (Valitse numeron�pp�imill� ja painamalla enter)\n";
		std::cout << "1. Varaa huone\n2. Tarkastele varausta\n3. Sulje j�rjestelm�\n";
		std::cin >> valinta;

		int tarkistus = isdigit(valinta); //Tarkistetaan sy�te isdigit() funktiolla, funktio k�ytt�� parametrina char tyyppi� ja palauttaa int tyypin 0 tai joku muu kuin 0 riippuen onko false vai true
		
		if (tarkistus == 0) {
			std::cout << "Virheellinen sy�te, sy�t� 1, 2 tai 3 ja paina enter. \n";
			std::cout << std::endl;
			continue;
		}

		else if (valinta == '1') {
			return 1;
		}
		else if (valinta == '2') {
			return 2;
		}
		else if (valinta == '3') {
			return 3;
		}
	} while (true);

}

Hotellihuone huoneiden_teko() { //T�m� aliohjelma alustaa hotellihuone taulukon joillain l�ht�arvoilla, jotka muuttuvat kun k�ytt�j� antaa uudet tiedot
	//Kun taulukko on alustettu t�ss� aliohjelmassa, tiedot s�ilyv�t siell� niin kauan kuin ohjelma on k�ynniss�
	Hotellihuone h;
	h.hinta = 0;
	h.varaaja = " ";
	h.varausnumero = 0;
	h.varaustilanne = false;
	h.yot = 0;
	h.hinta = 0;

	return h;
}
Hotellihuone huoneen_varaus(Hotellihuone h[]) {
	//T�ss� tehd��n varaus, kysyt��n varaajan tiedot ja tallennetaan ne hotellihuone taulukkoon
	int huonenumero, tarkistus;
	char henkilot, valinta;
	
	do {
		std::cout << "Haluatko 1 vai 2 hengen huoneen?\n";
		std::cin >> henkilot;
		tarkistus = isdigit(henkilot);

		if (tarkistus == 0) {
			std::cout << "Virheellinen sy�te, sy�t� 1 tai 2 ja paina enter.\n";
			std::cout << std::endl;
		}
	} while (tarkistus == 0);
	

	if (henkilot == '1') {
		do {
			std::cout << "Haluatko valita huonenumeron itse vai annatko koneen valita sen?\n" << "1. Tietokone valitsee\n2. Itse\n";
			std::cin >> valinta;

			tarkistus = isdigit(valinta);
			if (tarkistus == 0) {
				std::cout << "Virheellinen sy�te, valitse 1 tai 2 ja paina enter.\n";
				continue;
			}
			else if (valinta == '1') {
				do {
					srand(time(0));
					huonenumero = 1 + (rand() % 129);
				} while (h[huonenumero].varaustilanne == true);
				std::cout << "Huonenumerosi on: " << huonenumero;
				std::cout << std::endl;
				break;
			}
			else if (valinta == '2') {
				std::cout << "Valitse huonenumero (1-130)\n";
				std::cin >> huonenumero;
				while (h[huonenumero].varaustilanne == true) { //Tarkistetaan onko huone vapaana, jos ei ole, palataan p��valikkoon
					std::cout << "Valitettavasti huone ei ole vapaana, valitse toinen huone\n";
					std::cout << "Valitse huonenumero (1-130)\n";
					std::cin >> huonenumero;
				}
				break;
			}
		} while (true);
		
		h[huonenumero].varaustilanne = true;

		//Varaajan tiedot
		std::cout << "Anna nimesi: ";
		std::cin.ignore();
		std::getline(std::cin, h[huonenumero].varaaja);
		std::cout << "Anna puhelinnumerosi (numero muotoa 0400123456, ei maakoodia): ";
		std::getline(std::cin, h[huonenumero].puhnro);
		std::cout << "Anna s�hk�postiosoitteesi: ";
		std::getline(std::cin, h[huonenumero].sposti);

		std::cout << "Kuinka monta y�t� haluat y�py� hotellissa? Hinta on 100e per y�.\n";
		std::cin >> h[huonenumero].yot;
		h[huonenumero].hinta = h[huonenumero].yot * 100;
		srand(time(0));
		h[huonenumero].varausnumero = 10000 + (rand() % 89999);

		std::cout << "\nT�ss� varauksesi tiedot, otathan n�m� yl�s!\n";
		std::cout << "Nimi: " << h[huonenumero].varaaja << "\nPuhelinnumero: "<< h[huonenumero].puhnro<< "\nS�hk�posti: " << h[huonenumero].sposti << "\nHuoneen numero: "<<
			huonenumero<< "\n�iden m��r�: " << h[huonenumero].yot<< "\nVarausnumero: " << h[huonenumero].varausnumero
			<< "\nY�pymisen hinta: " << h[huonenumero].hinta << " euroa\n"<<std::endl;
		return h[huonenumero];
	}
	if (henkilot == '2') { //Kahden hengen huoneen varaaminen, muuten sama kuin edellinen mutta hinta ja huonenumerot eri
		
		do {
			std::cout << "Haluatko valita huonenumeron itse vai annatko koneen valita sen?\n" << "1. Tietokone valitsee\n2. Itse\n";
			std::cin >> valinta;

			tarkistus = isdigit(valinta);
			if (tarkistus == 0) {
				std::cout << "Virheellinen sy�te, valitse 1 tai 2 ja paina enter.\n";
				continue;
			}
			else if (valinta == '1') {
				do {
					srand(time(0));
					huonenumero = 131 + (rand() % 129);
				} while (h[huonenumero].varaustilanne == true);
				std::cout << "Huonenumerosi on: " << huonenumero;
				std::cout << std::endl;
				break;
			}
			else if (valinta == '2') {
				std::cout << "Valitse huonenumero (131-260)\n";
				std::cin >> huonenumero;
				while (h[huonenumero].varaustilanne == true) { //Tarkistetaan onko huone vapaana, jos ei ole, palataan p��valikkoon
					std::cout << "Valitettavasti huone ei ole vapaana, valitse toinen huone\n";
					std::cout << "Valitse huonenumero (131-260)\n";
					std::cin >> huonenumero;
				}
				break;
			}
		} while (true);
		

		
		h[huonenumero].varaustilanne = true;

		//Varaajan tiedot
		std::cout << "Anna nimesi: ";
		std::cin.ignore(); //cin.ignore() vain kerran, muuten seuraavista stringeist� puuttuu ensimm�inen merkki
		std::getline(std::cin, h[huonenumero].varaaja);
		std::cout << "Anna puhelinnumerosi (numero muotoa 0400123456, ei maakoodia): ";
		std::getline(std::cin, h[huonenumero].puhnro);
		std::cout << "Anna s�hk�postiosoitteesi: ";
		std::getline(std::cin, h[huonenumero].sposti);

		std::cout << "Kuinka monta y�t� haluat y�py� hotellissa? Hinta on 150e per y�.\n";
		std::cin >> h[huonenumero].yot;
		h[huonenumero].hinta = h[huonenumero].yot * 150;
		srand(time(0));
		h[huonenumero].varausnumero = 10000 + (rand() % 89999);

		std::cout << "\nT�ss� varauksesi tiedot, otathan n�m� yl�s!\n";
		std::cout << "Nimi: " << h[huonenumero].varaaja << "\nPuhelinnumero: " << h[huonenumero].puhnro << "\nS�hk�posti: " << h[huonenumero].sposti << "\nHuoneen numero: " <<
			huonenumero << "\n�iden m��r�: " << h[huonenumero].yot << "\nVarausnumero: " << h[huonenumero].varausnumero
			<< "\nY�pymisen hinta: " << h[huonenumero].hinta << " euroa\n"<<std::endl;
		
		return h[huonenumero];
	}

}
void varauksen_tarkastelu(Hotellihuone h[]) { //T�ss� aliohjelmassa voi hakea tehtyj� varauksia varausnumerolla tai nimell�. Jos varausta ei l�ydy, kertoo ohjelma t�m�n ja palaa p��valikkoon
	int varausnumero, i, tarkistus;
	std::string nimi;
	char valinta;
	bool lippu = false; //T�t� muuttujaa k�ytet��n tarkistamaan, onko yht��n varausta l�ytynyt. Mik�li arvo pysyy false, ei varauskai annetuilla tiedoilla l�ytynyt

	std::cout << "Haluatko hakea nimell� vai varausnumerolla?" << std::endl << "1. Nimell�\n2. Varausnumerolla\n";
	std::cin >> valinta;
	tarkistus = isdigit(valinta);

	if (valinta == '1') {
		std::cout << "\nAnna nimi mill� haetaan: ";
		std::cin.ignore();
		std::getline(std::cin, nimi);

		for (i = 0; i < huonemaara; i++) {
			if (h[i].varaaja == nimi) {
				std::cout << "\nT�ss� varauksen tiedot: \n";
				std::cout << "Nimi: " << h[i].varaaja << "\nPuhelinnumero: " << h[i].puhnro << "\nS�hk�posti: " << h[i].sposti
					<< "\nHuoneen numero: "<< i << "\n�iden m��r�: " << h[i].yot << "\nVarausnumero: " << h[i].varausnumero
					<< "\nY�pymisen hinta: " << h[i].hinta << " euroa\n";
				std::cout << std::endl;
				lippu = true;
				
			}
			
		}
		if (lippu == false) {
			std::cout << "\nValitettavasti nimell� " << nimi << " ei l�ytynyt yht��n varausta.\n";
			std::cout << std::endl;
		}
	}
	if (valinta == '2') {
		std::cout << "\nAnna varausnumero mill� haetaan: ";
		std::cin >> varausnumero;

		for (i = 0; i < huonemaara; i++) {
			if (h[i].varausnumero == varausnumero) {
				std::cout << "\nT�ss� varauksen tiedot: \n";
				std::cout << "Nimi: " << h[i].varaaja << "\nPuhelinnumero: " << h[i].puhnro << "\nS�hk�posti: " << h[i].sposti
					<< "\nHuoneen numero: " << i << "\n�iden m��r�: " << h[i].yot << "\nVarausnumero: " << h[i].varausnumero
					<< "\nY�pymisen hinta: " << h[i].hinta << " euroa\n";
				std::cout << std::endl;
				lippu == true;
			}
			
			
		}
		if (lippu == false) {
			std::cout << "Valitettavasti varausnumerolla " << varausnumero << " ei l�ytynyt yht��n varausta.\n";
			std::cout << std::endl;
		}
	}

}
