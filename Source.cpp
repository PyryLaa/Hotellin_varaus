#include <iostream>
#include <string>

//Nämä kaksi seuraavaa mahdollistavat varausnumeron satunnaisgeneroinnin ja ajan käyttämisen generoinnin seedinä
#include <cstdlib>
#include <time.h>

//Tämän kirjaston avulla voidaan käyttää mm. isdigit() funktiota syötteen tarkistukseen
#include <ctype.h>

struct Hotellihuone { //Jokainen hotellihuone on struct joka pitää sisällään tiedot huoneen varaajasta yms. Varaustilanne muuttuu true jos huoneeseen on tehty varaus
	bool varaustilanne;
	int varausnumero;
	int yot;
	int hinta;
	std::string varaaja, sposti, puhnro;
};

const int huonemaara = 260; //Hotellihuonetaulukon koko eli hotellihuoneiden määrä
Hotellihuone huone_lista[huonemaara];

//Aliohjelmien alustus
Hotellihuone Huoneiden_teko();
int Main_menu();
Hotellihuone Huoneen_varaus(Hotellihuone h[]);
void Varauksen_tarkastelu(Hotellihuone h[]);

 



int main() { //Main funktio vain kutsuu muita aliohjelmia riippuen mitä main_menu aliohjelma palauttaa

	setlocale(LC_ALL, "fi_FI"); //Setlocale antaa mahdollisuuden käyttää ääkkösiä ohjelman tulostuksissa

	

	for (int i = 0; i < huonemaara; i++) { //Silmukassa kutsutaan jokaisella hotellihuoneella aliohjelmaa jossa annetaan huoneen tiedoille jokin alkuarvo
		huone_lista[i] = Huoneiden_teko();
	}

	while (true) {
		int palautus = Main_menu();

		if (palautus == 1) {
			Huoneen_varaus(huone_lista);
		}
		else if (palautus == 2) {
			Varauksen_tarkastelu(huone_lista);
		}
		else if (palautus == 3) {
			std::cout << "Näkemiin!";
			break;
		}
	}
	return 0;
}


int Main_menu() {//Päävalikko aliohjelma, tästä liikutaan muihin aliohjelmiin mainin kautta käyttäjän valinnan mukaisesti
	char valinta;

	do {
		std::cout << "Tervetuloa Rantahotellin varausjärjestelmään!\n";
		std::cout << "Mitä haluaisit tehdä? (Valitse numeronäppäimillä ja painamalla enter)\n";
		std::cout << "1. Varaa huone\n2. Tarkastele varausta\n3. Sulje järjestelmä\n";
		std::cin >> valinta;

		int tarkistus = isdigit(valinta); //Tarkistetaan syöte isdigit() funktiolla, funktio käyttää parametrina char tyyppiä ja palauttaa int tyypin 0 tai joku muu kuin 0 riippuen onko false vai true

		while (tarkistus == 0) {
			std::cout << "Virheellinen syöte, syötä 1, 2 tai 3 ja paina enter. \n";
			std::cout << std::endl;
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cout << "1. Varaa huone\n2. Tarkastele varausta\n3. Sulje järjestelmä\n";
			std::cin >> valinta;
			tarkistus = isdigit(valinta);
		}

		if (valinta == '1') {
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


Hotellihuone Huoneiden_teko() { //Tämä aliohjelma alustaa hotellihuone taulukon joillain lähtöarvoilla, jotka muuttuvat kun käyttäjä antaa uudet tiedot
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


Hotellihuone Huoneen_varaus(Hotellihuone h[]) {
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
			std::cin.clear();
			std::cin.ignore(80, '\n');
		}
	} while (tarkistus == 0);


	if (henkilot == '1') {
		do {
			std::cout << "Haluatko valita huonenumeron itse vai annatko koneen valita sen?\n" << "1. Tietokone valitsee\n2. Itse\n";
			std::cin >> valinta;

			tarkistus = isdigit(valinta);
			while (tarkistus == 0) {
				std::cout << "Virheellinen syöte, valitse 1 tai 2 ja paina enter.\n";
				std::cin.clear();
				std::cin.ignore(80, '\n');
				std::cin >> valinta;
				tarkistus = isdigit(valinta);
			}
			if (valinta == '1') {
				do { //Satunnaisgeneroi huonenumeron ja tarkistaa onko tälle tietylle numerolle jo varattu huone. Yrittää niin kauan kunnes vapaa huone löytyy
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
				while (h[huonenumero].varaustilanne == true) { //Tarkistetaan onko huone vapaana
					std::cout << "Valitettavasti huone ei ole vapaana, valitse toinen huone\n";
					std::cout << "Valitse huonenumero (1-130)\n";
					std::cin >> huonenumero;
				}
				break;
			}
		} while (true);

		//Tänne tullaan kun huonenumero on valittu onnistuneesti

		h[huonenumero].varaustilanne = true;

		//Varaajan tiedot
		std::cout << "Anna nimesi: ";
		std::cin.ignore(); //cin.ignore tarvitaan vain kerran, muuten seuraavista stringeistä puuttuu ensimmäinen kirjain
		std::getline(std::cin, h[huonenumero].varaaja);
		std::cout << "Anna puhelinnumerosi (numero muotoa 0400123456, ei maakoodia): ";
		std::getline(std::cin, h[huonenumero].puhnro);
		std::cout << "Anna sähköpostiosoitteesi: ";
		std::getline(std::cin, h[huonenumero].sposti);

		std::cout << "Kuinka monta yötä haluat yöpyä hotellissa? Hinta on 100e per yö.\n";
		std::cin >> h[huonenumero].yot;
		h[huonenumero].hinta = h[huonenumero].yot * 100;

		srand(time(0)); //srand time käyttää aikaa satunnaisgeneroinnin seedinä, eli generoitu luku perustuu aina ajan hetkeen. Täten saadaan aina eri luku.
		h[huonenumero].varausnumero = 10000 + (rand() % 89999);

		std::cout << "\nTässä varauksesi tiedot, otathan nämä ylös!\n";
		std::cout << "Nimi: " << h[huonenumero].varaaja << "\nPuhelinnumero: " << h[huonenumero].puhnro << "\nSähköposti: " << h[huonenumero].sposti << "\nHuoneen numero: " <<
			huonenumero << "\nÖiden määrä: " << h[huonenumero].yot << "\nVarausnumero: " << h[huonenumero].varausnumero
			<< "\nYöpymisen hinta: " << h[huonenumero].hinta << " euroa\n" << std::endl;

		return h[huonenumero];//Palautetaan varatun huoneen tiedot hotellihuonetaulukkoon
	}
	if (henkilot == '2') { //Kahden hengen huoneen varaaminen, muuten sama kuin yhden hengen mutta hinta ja huonenumerot eri

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
				while (h[huonenumero].varaustilanne == true) { //Tarkistetaan onko huone vapaana
					std::cout << "Valitettavasti huone ei ole vapaana, valitse toinen huone\n";
					std::cout << "Valitse huonenumero (131-260)\n";
					std::cin >> huonenumero;
				}
				break;
			}
		} while (true);

		//Tänne tullaan kun huonenumero on valittu onnistuneesti

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
			<< "\nYöpymisen hinta: " << h[huonenumero].hinta << " euroa\n" << std::endl;

		return h[huonenumero];
	}

}
void Varauksen_tarkastelu(Hotellihuone h[]) { //Tässä aliohjelmassa voi hakea tehtyjä varauksia varausnumerolla tai nimellä. Jos varausta ei löydy, kertoo ohjelma tämän ja palaa päävalikkoon
	int varausnumero, i, tarkistus;
	std::string nimi;
	char valinta;
	bool lippu = false; //Tätä muuttujaa käytetään tarkistamaan, onko yhtään varausta löytynyt. Mikäli arvo pysyy false, ei varauskai annetuilla tiedoilla löytynyt

	do {

		std::cout << "Haluatko hakea nimellä vai varausnumerolla?" << std::endl << "1. Nimellä\n2. Varausnumerolla\n";
		std::cin >> valinta;
		tarkistus = isdigit(valinta);

		while (tarkistus == 0) {
			std::cout << "Virheellinen syöte, paina 1 tai 2 ja enter!\n";
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cin >> valinta;
			tarkistus = isdigit(valinta);
		}

		if (valinta == '1') {
			std::cout << "\nAnna nimi millä haetaan: ";
			std::cin.ignore();
			std::getline(std::cin, nimi);

			for (i = 0; i < huonemaara; i++) { //Käy läpi hotellihuonetaulukon ja tulostaa kaikki annetulla nimellä löytyneet varaukset
				if (h[i].varaaja == nimi) {
					int laskuri = 1; //Laskuri kertoo monennen varauksen tiedot ovat kyseessä
					std::cout << "\nTässä varauksen"<< laskuri << "tiedot: \n";
					laskuri++;
					std::cout << "Nimi: " << h[i].varaaja << "\nPuhelinnumero: " << h[i].puhnro << "\nSähköposti: " << h[i].sposti
						<< "\nHuoneen numero: " << i << "\nÖiden määrä: " << h[i].yot << "\nVarausnumero: " << h[i].varausnumero
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

			for (i = 0; i < huonemaara; i++) {//Käy läpi huonetaulukon ja tulostaa annetulla varausnumerolla tehdyn varauksen
				//Täällä ei laskuria koska yksi varausnumero voi olla vain yhdellä huoneella, ei useammalla

				if (h[i].varausnumero == varausnumero) {
					std::cout << "\nTässä varauksen tiedot: \n";
					std::cout << "Nimi: " << h[i].varaaja << "\nPuhelinnumero: " << h[i].puhnro << "\nSähköposti: " << h[i].sposti
						<< "\nHuoneen numero: " << i << "\nÖiden määrä: " << h[i].yot << "\nVarausnumero: " << h[i].varausnumero
						<< "\nYöpymisen hinta: " << h[i].hinta << " euroa\n";
					std::cout << std::endl;
					lippu = true;
				}


			}
			if (lippu == false) {
				std::cout << "Valitettavasti varausnumerolla " << varausnumero << " ei löytynyt yhtään varausta.\n";
				std::cout << std::endl;
			}
		}
	} while (lippu == false);
}