#include"stdafx.h"
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
	//if person schon vorhanden return false;
	//std::cout << "Zeichnungsbrechntigt: p : " << p->get_name()<<std::endl;
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

/////////////////////////////////Person
Person::Person(std::string name) {
	this->name = name;
}
	bool Person::konto_teilen(Konto& k, Person& p){
		//Zeichnungsberechtigten ergänzen
		auto sp = std::make_shared<Person>(p);
		k.add_zeichnungsberechtigt(sp);
		p.neues_konto(k);
		return true;//checken
}
	std::shared_ptr<Konto> Person::neues_konto(){
		std::shared_ptr<Konto> k{std::make_shared<Konto>(shared_from_this())};
		konten.push_back(k);
		return k;//checken
	}
	std::shared_ptr<Konto> Person::neues_konto(Konto& k) {
		std::shared_ptr<Konto> ko{ std::make_shared<Konto>(k) };
		konten.push_back(ko);
		return ko;//checken
	}
	void Person::kuendigen() {
		;
	}

std::string Person::get_name(){
	return name;
}

std::vector<std::shared_ptr<Konto>> Person::get_konten() {
	return konten;
}

std::ostream& Person::print(std::ostream & os) const {
	os << "Name: " << name << "\n";
	for (auto &elem : konten) {
		os << "Konto Nummer: "<<elem->get_kn()<<"\n";
	}
		
		return os;
	}


////////////////////////Bank
std::ostream& Bank::print(std::ostream & os) const {
	for(auto & elem: kunden)
				os<<"Inhalt der Bank Unordered Map -kunden-"<<elem.first<<"\n";
	for (auto & elem : konten)
		os << "Inhalt der Bank Unordered Map -Konto-" << elem.first << *(elem.second) << "\n";
		return os;
	}

	std::string Bank::neuerKunde(std::string name){
		auto it=kunden.emplace(name, std::make_shared<Person>(name));
		auto k=it.first->second->neues_konto();//erstelle für die frisch erstellte Person ein Konto
		konten.emplace(k->get_kn(), k);
		return k->get_kn();
	}

	std::shared_ptr<Person> Bank::get_kunde(std::string name) {
		auto it=kunden.find(name);
		return it->second;
	}
	std::string Bank::neues_konto(Person& p, Konto& k) {
		//ordnet ein bestehendes Konto der Person zu
		//fügt das neu erstelle Konto in die unordered map
			konten.emplace(p.neues_konto(k)->get_kn(), p.neues_konto(k));
			return k.get_kn();
	}
	std::string Bank::neues_konto(Person& p) {
		//erstellt ein neues Konto für diese Person
		//fügt das neu erstelle Konto in die unordered map
		auto temp = p.neues_konto()->get_kn();
		konten.emplace(temp, p.neues_konto());
		return temp;
	}
	std::shared_ptr<Konto> Bank::get_Konto(std::string knr) {
		return (konten.find(knr)->second);
	}








std::ostream& operator<<(std::ostream& os, const Bank& b) {
	b.print(os);
	return os;
}

std::ostream& operator<<(std::ostream& os, const Person& p) {
	p.print(os);
	return os;
}

std::ostream& operator<<(std::ostream& os, const Konto& k) {
	k.print(os);
	return os;
}



