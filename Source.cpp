//Hotellihuoneen varausj�rjestelm�
#include <iostream>
#include <string>

//N�m� kaksi viimeist� mahdollistavat satunnaisen varausnumeron generoinnin sek� ohjelman lopettamisen ilman return 0
#include <cstdlib>
#include <time.h>



int main_menu();
void huoneen_valinta(int num);
void varaus_tarkastelu();

struct Hotellihuone {
	int huonemaara[260];
	int huonenumero;
	int varausnumero;
	std::string varaaja;
};

int main() {
	setlocale(LC_ALL, "fi_FI");

	while (true) { //P��silmukka, jonka sis�ll� ohjelma py�rii

		if (main_menu() == 0) {
			break;
		}	

	}
	return 0;
}

int main_menu() { //P��valikon aliohjelma
	int valinta;

	std::cout << "Tervetuloa Rantahotellin varausj�rjestelm��n!\n";

	std::cout << "Valitse jokin seuraavista toiminnoista jatkaaksesi\n";
	std::cout << "1. Tee varaus\n" << "2. Tarkastele varausta\n" << "3. Lopeta varausj�rjestelm�n k�ytt�\n";
	std::cin >> valinta;
	if (valinta == 1) {
		int henkilot;
		std::cout << "Haluatko varata 1 vai 2 hengen huoneen?"
			<< "(Paina 1 tai 2, jos haluat takaisin p��valikkoon, paina 3)\n";
		std::cin >> henkilot;
		huoneen_valinta(henkilot);
	}
	else if (valinta == 2) {
		std::cout << "Nyt tultiin kakkoseen!";
	}
	else if (valinta == 3) {
		std::cout << "N�kemiin!";
		return 0;
	}
	return 0;
}



void huoneen_valinta(int num) { //T�ss� aliohjelmassa valitaan huoneen numero ja tehd��n varausnumero sek� kysyt��n varaajan nimi

	Hotellihuone hotellihuone;

	if (num == 1) {
		std::cout << "Valitse huonenumero (1 - 130): ";
		std::cin >> hotellihuone.huonenumero;
		std::cout << "Anna nimesi: ";
		std::cin.ignore();
		std::getline (std::cin, hotellihuone.varaaja);
		srand(time(0));
		hotellihuone.varausnumero = 10000 + (rand() % 89999);
		std::cout << "Varauksesi tiedot: " << std::endl;
		std::cout << "Huoneen numero: " << hotellihuone.huonenumero << std::endl;
		std::cout << "Varaajan nimi: " << hotellihuone.varaaja << std::endl;
		std::cout << "Varausnumero: " << hotellihuone.varausnumero << " otathan t�m�n talteen!" << std::endl;
	
	}
	else if (num == 2) {
		std::cout << "Valitse huonenumero (131-260): ";
		std::cin >> hotellihuone.huonenumero;
		std::cout << "Anna nimesi: ";
		std::cin.ignore();
		std::getline(std::cin, hotellihuone.varaaja);
		srand(time(0));
		hotellihuone.varausnumero = 10000 + (rand() % 89999);
		std::cout << "Varauksesi tiedot: " << std::endl;
		std::cout << "Huoneen numero: " << hotellihuone.huonenumero << std::endl;
		std::cout << "Varaajan nimi: " << hotellihuone.varaaja << std::endl;
		std::cout << "Varausnumero: " << hotellihuone.varausnumero << " otathan t�m�n talteen!" << std::endl;
	}
	main_menu();
}

void varaus_tarkastelu() {
	

}