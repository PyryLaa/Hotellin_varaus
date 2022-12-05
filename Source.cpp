#include <iostream>
#include <string>

//Nämä kaksi seuraavaa mahdollistavat varausnumeron satunnaisgeneroinnin ja ajan käyttämisen generoinnin seedinä
#include <cstdlib>
#include <time.h>

//Tämän kirjaston avulla voidaan käyttää mm. isdigit() funktiota syötteen tarkistukseen
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

const int huonemaara = 260; //Hotellihuone taulukon koko eli hotellihuoneiden määrä



int main() { //Main funktio vain kutsuu muita aliohjelmia riippuen mitä main_menu aliohjelma palauttaa
	setlocale(LC_ALL, "fi_FI"); //Setlocale antaa mahdollisuuden käyttää ääkkösiä ohjelman tulostuksissa
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
			std::cout << "Näkemiin!";
			break;
		}
	}
	return 0;
}
int main_menu() {//Päävalikko aliohjelma, tästä liikutaan muihin aliohjelmiin mainin kautta käyttäjän valinnan mukaisesti
	char valinta;
	do {
		std::cout << "Tervetuloa Rantahotellin varausjärjestelmään!\n";
		std::cout << "Mitä haluaisit tehdä? (Valitse numeronäppäimillä ja painamalla enter)\n";
		std::cout << "1. Varaa huone\n2. Tarkastele varausta\n3. Sulje järjestelmä\n";
		std::cin >> valinta;

		int tarkistus = isdigit(valinta); //Tarkistetaan syöte isdigit() funktiolla, funktio käyttää parametrina char tyyppiä ja palauttaa int tyypin 0 tai joku muu kuin 0 riippuen onko false vai true
		
		if (tarkistus == 0) {
			std::cout << "Virheellinen syöte, syötä 1, 2 tai 3 ja paina enter. \n";
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

Hotellihuone huoneiden_teko() { //Tämä aliohjelma alustaa hotellihuone taulukon joillain lähtöarvoilla, jotka muuttuvat kun käyttäjä antaa uudet tiedot
	//Kun taulukko on alustettu tässä aliohjelmassa, tiedot säilyvät siellä niin kauan kuin ohjelma on käynnissä
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
	//Tässä tehdään varaus, kysytään varaajan tiedot ja tallennetaan ne hotellihuone taulukkoon
	int huonenumero, tarkistus;
	char henkilot, valinta;
	
	do {
		std::cout << "Haluatko 1 vai 2 hengen huoneen?\n";
		std::cin >> henkilot;
		tarkistus = isdigit(henkilot);

		if (tarkistus == 0) {
			std::cout << "Virheellinen syöte, syötä 1 tai 2 ja paina enter.\n";
			std::cout << std::endl;
		}
	} while (tarkistus == 0);
	

	if (henkilot == '1') {
		do {
			std::cout << "Haluatko valita huonenumeron itse vai annatko koneen valita sen?\n" << "1. Tietokone valitsee\n2. Itse\n";
			std::cin >> valinta;

			tarkistus = isdigit(valinta);
			if (tarkistus == 0) {
				std::cout << "Virheellinen syöte, valitse 1 tai 2 ja paina enter.\n";
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
				while (h[huonenumero].varaustilanne == true) { //Tarkistetaan onko huone vapaana, jos ei ole, palataan päävalikkoon
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
		std::cout << "Anna sähköpostiosoitteesi: ";
		std::getline(std::cin, h[huonenumero].sposti);

		std::cout << "Kuinka monta yötä haluat yöpyä hotellissa? Hinta on 100e per yö.\n";
		std::cin >> h[huonenumero].yot;
		h[huonenumero].hinta = h[huonenumero].yot * 100;
		srand(time(0));
		h[huonenumero].varausnumero = 10000 + (rand() % 89999);

		std::cout << "\nTässä varauksesi tiedot, otathan nämä ylös!\n";
		std::cout << "Nimi: " << h[huonenumero].varaaja << "\nPuhelinnumero: "<< h[huonenumero].puhnro<< "\nSähköposti: " << h[huonenumero].sposti << "\nHuoneen numero: "<<
			huonenumero<< "\nÖiden määrä: " << h[huonenumero].yot<< "\nVarausnumero: " << h[huonenumero].varausnumero
			<< "\nYöpymisen hinta: " << h[huonenumero].hinta << " euroa\n"<<std::endl;
		return h[huonenumero];
	}
	if (henkilot == '2') { //Kahden hengen huoneen varaaminen, muuten sama kuin edellinen mutta hinta ja huonenumerot eri
		
		do {
			std::cout << "Haluatko valita huonenumeron itse vai annatko koneen valita sen?\n" << "1. Tietokone valitsee\n2. Itse\n";
			std::cin >> valinta;

			tarkistus = isdigit(valinta);
			if (tarkistus == 0) {
				std::cout << "Virheellinen syöte, valitse 1 tai 2 ja paina enter.\n";
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
				while (h[huonenumero].varaustilanne == true) { //Tarkistetaan onko huone vapaana, jos ei ole, palataan päävalikkoon
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
		std::cin.ignore(); //cin.ignore() vain kerran, muuten seuraavista stringeistä puuttuu ensimmäinen merkki
		std::getline(std::cin, h[huonenumero].varaaja);
		std::cout << "Anna puhelinnumerosi (numero muotoa 0400123456, ei maakoodia): ";
		std::getline(std::cin, h[huonenumero].puhnro);
		std::cout << "Anna sähköpostiosoitteesi: ";
		std::getline(std::cin, h[huonenumero].sposti);

		std::cout << "Kuinka monta yötä haluat yöpyä hotellissa? Hinta on 150e per yö.\n";
		std::cin >> h[huonenumero].yot;
		h[huonenumero].hinta = h[huonenumero].yot * 150;
		srand(time(0));
		h[huonenumero].varausnumero = 10000 + (rand() % 89999);

		std::cout << "\nTässä varauksesi tiedot, otathan nämä ylös!\n";
		std::cout << "Nimi: " << h[huonenumero].varaaja << "\nPuhelinnumero: " << h[huonenumero].puhnro << "\nSähköposti: " << h[huonenumero].sposti << "\nHuoneen numero: " <<
			huonenumero << "\nÖiden määrä: " << h[huonenumero].yot << "\nVarausnumero: " << h[huonenumero].varausnumero
			<< "\nYöpymisen hinta: " << h[huonenumero].hinta << " euroa\n"<<std::endl;
		
		return h[huonenumero];
	}

}
void varauksen_tarkastelu(Hotellihuone h[]) { //Tässä aliohjelmassa voi hakea tehtyjä varauksia varausnumerolla tai nimellä. Jos varausta ei löydy, kertoo ohjelma tämän ja palaa päävalikkoon
	int varausnumero, i, tarkistus;
	std::string nimi;
	char valinta;
	bool lippu = false; //Tätä muuttujaa käytetään tarkistamaan, onko yhtään varausta löytynyt. Mikäli arvo pysyy false, ei varauskai annetuilla tiedoilla löytynyt

	std::cout << "Haluatko hakea nimellä vai varausnumerolla?" << std::endl << "1. Nimellä\n2. Varausnumerolla\n";
	std::cin >> valinta;
	tarkistus = isdigit(valinta);

	if (valinta == '1') {
		std::cout << "\nAnna nimi millä haetaan: ";
		std::cin.ignore();
		std::getline(std::cin, nimi);

		for (i = 0; i < huonemaara; i++) {
			if (h[i].varaaja == nimi) {
				std::cout << "\nTässä varauksen tiedot: \n";
				std::cout << "Nimi: " << h[i].varaaja << "\nPuhelinnumero: " << h[i].puhnro << "\nSähköposti: " << h[i].sposti
					<< "\nHuoneen numero: "<< i << "\nÖiden määrä: " << h[i].yot << "\nVarausnumero: " << h[i].varausnumero
					<< "\nYöpymisen hinta: " << h[i].hinta << " euroa\n";
				std::cout << std::endl;
				lippu = true;
				
			}
			
		}
		if (lippu == false) {
			std::cout << "\nValitettavasti nimellä " << nimi << " ei löytynyt yhtään varausta.\n";
			std::cout << std::endl;
		}
	}
	if (valinta == '2') {
		std::cout << "\nAnna varausnumero millä haetaan: ";
		std::cin >> varausnumero;

		for (i = 0; i < huonemaara; i++) {
			if (h[i].varausnumero == varausnumero) {
				std::cout << "\nTässä varauksen tiedot: \n";
				std::cout << "Nimi: " << h[i].varaaja << "\nPuhelinnumero: " << h[i].puhnro << "\nSähköposti: " << h[i].sposti
					<< "\nHuoneen numero: " << i << "\nÖiden määrä: " << h[i].yot << "\nVarausnumero: " << h[i].varausnumero
					<< "\nYöpymisen hinta: " << h[i].hinta << " euroa\n";
				std::cout << std::endl;
				lippu == true;
			}
			
			
		}
		if (lippu == false) {
			std::cout << "Valitettavasti varausnumerolla " << varausnumero << " ei löytynyt yhtään varausta.\n";
			std::cout << std::endl;
		}
	}

}
