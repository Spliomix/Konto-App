//#include"stdafx.h"

#include"Konto.h"


///////////////////KONTO
int Konto::k = 0;
Konto::Konto(std::shared_ptr<Person> p){
	kontonummer="AT"+std::to_string(++k);
	zeichnungsberechtigt.push_back(p);
}
	std::string Konto::get_kn(){
		return kontonummer;
	}

bool Konto::add_zeichnungsberechtigt(std::shared_ptr<Person> p){
	if (zeichnungsberechtigt.size()>=10)return false;
	zeichnungsberechtigt.push_back(p);
	return true;
}

	void Konto::einzahlen (unsigned betrag){
		kontostand=kontostand+betrag;
	}

	bool Konto::auszahlen (unsigned betrag){
		if(kontostand+disporahmen<betrag)
			return false;
		kontostand=kontostand-betrag;
		return true;
}
	bool Konto::ueberweisen (unsigned betrag, Konto& ziel){
		if(kontostand+disporahmen<betrag)
			return false;
		kontostand=kontostand-betrag;
		ziel.einzahlen(betrag);
		return true;
}

std::shared_ptr<Konto> Konto::get_shared(){
	return shared_from_this();
}

int Konto::get_kontostand() {
	return kontostand;
}

std::ostream& Konto::print (std::ostream& os) const{
	for(auto& elem : zeichnungsberechtigt){
		if(!elem.expired()){
				auto observe =elem.lock();
				os<<(*observe).get_name();
		}

	}
return os;
}




	Girokonto::Girokonto(std::shared_ptr<Person> p):Konto(p){
}

	void Girokonto::berechnung_geb(unsigned u){
	geb+=2;
}


std::ostream& Girokonto::print(std::ostream & os) const {
		os<<"Giro Gebühren\n"<<geb<<"\n";
		return os;
	}

bool Girokonto::ueberweisen(unsigned betrag, Konto& ziel) {
	
	if (ziel.auszahlen(betrag)) {
		berechnung_geb(betrag);
		return true;
	}
	return false;
}





Businesskonto::Businesskonto(std::shared_ptr<Person> p) :Konto(p) {
}

void Businesskonto::berechnung_geb(unsigned u) {
	geb =geb+ 0.2*u;
}

bool Businesskonto::ueberweisen(unsigned betrag, Konto& ziel) {

	if (ziel.auszahlen(betrag)) {
		berechnung_geb(betrag);
		return true;
	}
	return false;
}


std::ostream& Businesskonto::print(std::ostream & os) const {
	os << "Businesskonto Gebühren:\n" << geb << "\n";
	return os;
}


std::ostream& operator<<(std::ostream& os, const Konto& k) {
	k.print(os);
	return os;
}

std::ostream& operator<<(std::ostream& os, const Girokonto& g) {
	g.print(os);
	return os;
}




