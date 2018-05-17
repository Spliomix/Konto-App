
#pragma once
#include<string>
#include<memory>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include"Person.h"
#include"Bank.h"
class Person;
class Bank;

class Konto : public std::enable_shared_from_this<Konto> {
private:
	std::string kontonummer;
	int kontostand{0};
	int disporahmen{1000};
	int gebuehren{0};
	std::vector<std::weak_ptr<Person>> zeichnungsberechtigt; //max10 mind. 1
public:
	static int k;//für die Kontonummer
	Konto(std::shared_ptr<Person>);
	Konto(std::shared_ptr<Person>, int);//neu
	void einzahlen (unsigned betrag);//geht
	bool auszahlen (unsigned betrag);//geht
	virtual bool ueberweisen (unsigned betrag, Konto& ziel);//geht
	int get_kontostand();//geht
	std::string get_kn();//geht
	bool add_zeichnungsberechtigt(std::shared_ptr<Person> p);//geht
	std::shared_ptr<Konto> get_shared();
	virtual void berechnung_geb(unsigned)=0;
	virtual std::ostream& print (std::ostream&) const;//geht
};


class Girokonto:public Konto, public std::enable_shared_from_this<Girokonto>{
	double geb{0};
public:
	Girokonto(std::shared_ptr<Person>);
	std::ostream& print (std::ostream&) const;
	void berechnung_geb(unsigned);
	bool ueberweisen(unsigned betrag, Konto& ziel);

};

class Businesskonto:public Konto, public std::enable_shared_from_this<Businesskonto> {
	double geb{ 0 };
public:
	Businesskonto(std::shared_ptr<Person>);
	std::ostream& print(std::ostream&) const;
	void berechnung_geb(unsigned);
	bool ueberweisen(unsigned betrag, Konto& ziel);
};



std::ostream& operator<<(std::ostream&, const Konto&);
std::ostream& operator<<(std::ostream&, const Girokonto&);


