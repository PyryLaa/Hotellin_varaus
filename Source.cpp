#include <iostream>
#include <string>

//N�m� kaksi seuraavaa mahdollistavat varausnumeron satunnaisgeneroinnin ja ajan k�ytt�misen generoinnin seedin�
#include <cstdlib>
#include <time.h>

//T�m�n kirjaston avulla voidaan k�ytt�� mm. isdigit() funktiota sy�tteen tarkistukseen
#include <ctype.h>

struct Hotellihuone { //Jokainen hotellihuone on struct joka pit�� sis�ll��n tiedot huoneen varaajasta yms. Varaustilanne muuttuu true jos huoneeseen on tehty varaus
	bool varaustilanne;
	int varausnumero;
	int yot;
	int hinta;
	std::string varaaja, sposti, puhnro;
};

const int huonemaara = 260; //Hotellihuonetaulukon koko eli hotellihuoneiden m��r�
Hotellihuone huone_lista[huonemaara];

//Aliohjelmien alustus
Hotellihuone Huoneiden_teko();
int Main_menu();
Hotellihuone Huoneen_varaus(Hotellihuone h[]);
void Varauksen_tarkastelu(Hotellihuone h[]);

 



int main() { //Main funktio vain kutsuu muita aliohjelmia riippuen mit� main_menu aliohjelma palauttaa

	setlocale(LC_ALL, "fi_FI"); //Setlocale antaa mahdollisuuden k�ytt�� ��kk�si� ohjelman tulostuksissa

	

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
			std::cout << "N�kemiin!";
			break;
		}
	}
	return 0;
}


int Main_menu() {//P��valikko aliohjelma, t�st� liikutaan muihin aliohjelmiin mainin kautta k�ytt�j�n valinnan mukaisesti
	char valinta;

	do {
		std::cout << "Tervetuloa Rantahotellin varausj�rjestelm��n!\n";
		std::cout << "Mit� haluaisit tehd�? (Valitse numeron�pp�imill� ja painamalla enter)\n";
		std::cout << "1. Varaa huone\n2. Tarkastele varausta\n3. Sulje j�rjestelm�\n";
		std::cin >> valinta;

		int tarkistus = isdigit(valinta); //Tarkistetaan sy�te isdigit() funktiolla, funktio k�ytt�� parametrina char tyyppi� ja palauttaa int tyypin 0 tai joku muu kuin 0 riippuen onko false vai true

		while (tarkistus == 0) {
			std::cout << "Virheellinen sy�te, sy�t� 1, 2 tai 3 ja paina enter. \n";
			std::cout << std::endl;
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cout << "1. Varaa huone\n2. Tarkastele varausta\n3. Sulje j�rjestelm�\n";
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


Hotellihuone Huoneiden_teko() { //T�m� aliohjelma alustaa hotellihuone taulukon joillain l�ht�arvoilla, jotka muuttuvat kun k�ytt�j� antaa uudet tiedot
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


Hotellihuone Huoneen_varaus(Hotellihuone h[]) {
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
				std::cout << "Virheellinen sy�te, valitse 1 tai 2 ja paina enter.\n";
				std::cin.clear();
				std::cin.ignore(80, '\n');
				std::cin >> valinta;
				tarkistus = isdigit(valinta);
			}
			if (valinta == '1') {
				do { //Satunnaisgeneroi huonenumeron ja tarkistaa onko t�lle tietylle numerolle jo varattu huone. Yritt�� niin kauan kunnes vapaa huone l�ytyy
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

		//T�nne tullaan kun huonenumero on valittu onnistuneesti

		h[huonenumero].varaustilanne = true;

		//Varaajan tiedot
		std::cout << "Anna nimesi: ";
		std::cin.ignore(); //cin.ignore tarvitaan vain kerran, muuten seuraavista stringeist� puuttuu ensimm�inen kirjain
		std::getline(std::cin, h[huonenumero].varaaja);
		std::cout << "Anna puhelinnumerosi (numero muotoa 0400123456, ei maakoodia): ";
		std::getline(std::cin, h[huonenumero].puhnro);
		std::cout << "Anna s�hk�postiosoitteesi: ";
		std::getline(std::cin, h[huonenumero].sposti);

		std::cout << "Kuinka monta y�t� haluat y�py� hotellissa? Hinta on 100e per y�.\n";
		std::cin >> h[huonenumero].yot;
		h[huonenumero].hinta = h[huonenumero].yot * 100;

		srand(time(0)); //srand time k�ytt�� aikaa satunnaisgeneroinnin seedin�, eli generoitu luku perustuu aina ajan hetkeen. T�ten saadaan aina eri luku.
		h[huonenumero].varausnumero = 10000 + (rand() % 89999);

		std::cout << "\nT�ss� varauksesi tiedot, otathan n�m� yl�s!\n";
		std::cout << "Nimi: " << h[huonenumero].varaaja << "\nPuhelinnumero: " << h[huonenumero].puhnro << "\nS�hk�posti: " << h[huonenumero].sposti << "\nHuoneen numero: " <<
			huonenumero << "\n�iden m��r�: " << h[huonenumero].yot << "\nVarausnumero: " << h[huonenumero].varausnumero
			<< "\nY�pymisen hinta: " << h[huonenumero].hinta << " euroa\n" << std::endl;

		return h[huonenumero];//Palautetaan varatun huoneen tiedot hotellihuonetaulukkoon
	}
	if (henkilot == '2') { //Kahden hengen huoneen varaaminen, muuten sama kuin yhden hengen mutta hinta ja huonenumerot eri

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
				while (h[huonenumero].varaustilanne == true) { //Tarkistetaan onko huone vapaana
					std::cout << "Valitettavasti huone ei ole vapaana, valitse toinen huone\n";
					std::cout << "Valitse huonenumero (131-260)\n";
					std::cin >> huonenumero;
				}
				break;
			}
		} while (true);

		//T�nne tullaan kun huonenumero on valittu onnistuneesti

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
			<< "\nY�pymisen hinta: " << h[huonenumero].hinta << " euroa\n" << std::endl;

		return h[huonenumero];
	}

}
void Varauksen_tarkastelu(Hotellihuone h[]) { //T�ss� aliohjelmassa voi hakea tehtyj� varauksia varausnumerolla tai nimell�. Jos varausta ei l�ydy, kertoo ohjelma t�m�n ja palaa p��valikkoon
	int varausnumero, i, tarkistus;
	std::string nimi;
	char valinta;
	bool lippu = false; //T�t� muuttujaa k�ytet��n tarkistamaan, onko yht��n varausta l�ytynyt. Mik�li arvo pysyy false, ei varauskai annetuilla tiedoilla l�ytynyt

	do {

		std::cout << "Haluatko hakea nimell� vai varausnumerolla?" << std::endl << "1. Nimell�\n2. Varausnumerolla\n";
		std::cin >> valinta;
		tarkistus = isdigit(valinta);

		while (tarkistus == 0) {
			std::cout << "Virheellinen sy�te, paina 1 tai 2 ja enter!\n";
			std::cin.clear();
			std::cin.ignore(80, '\n');
			std::cin >> valinta;
			tarkistus = isdigit(valinta);
		}

		if (valinta == '1') {
			std::cout << "\nAnna nimi mill� haetaan: ";
			std::cin.ignore();
			std::getline(std::cin, nimi);

			for (i = 0; i < huonemaara; i++) { //K�y l�pi hotellihuonetaulukon ja tulostaa kaikki annetulla nimell� l�ytyneet varaukset
				if (h[i].varaaja == nimi) {
					int laskuri = 1; //Laskuri kertoo monennen varauksen tiedot ovat kyseess�
					std::cout << "\nT�ss� varauksen"<< laskuri << "tiedot: \n";
					laskuri++;
					std::cout << "Nimi: " << h[i].varaaja << "\nPuhelinnumero: " << h[i].puhnro << "\nS�hk�posti: " << h[i].sposti
						<< "\nHuoneen numero: " << i << "\n�iden m��r�: " << h[i].yot << "\nVarausnumero: " << h[i].varausnumero
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

			for (i = 0; i < huonemaara; i++) {//K�y l�pi huonetaulukon ja tulostaa annetulla varausnumerolla tehdyn varauksen
				//T��ll� ei laskuria koska yksi varausnumero voi olla vain yhdell� huoneella, ei useammalla

				if (h[i].varausnumero == varausnumero) {
					std::cout << "\nT�ss� varauksen tiedot: \n";
					std::cout << "Nimi: " << h[i].varaaja << "\nPuhelinnumero: " << h[i].puhnro << "\nS�hk�posti: " << h[i].sposti
						<< "\nHuoneen numero: " << i << "\n�iden m��r�: " << h[i].yot << "\nVarausnumero: " << h[i].varausnumero
						<< "\nY�pymisen hinta: " << h[i].hinta << " euroa\n";
					std::cout << std::endl;
					lippu = true;
				}


			}
			if (lippu == false) {
				std::cout << "Valitettavasti varausnumerolla " << varausnumero << " ei l�ytynyt yht��n varausta.\n";
				std::cout << std::endl;
			}
		}
	} while (lippu == false);
}