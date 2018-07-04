
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

class Konto : public std::enable_shared_from_this<Konto> {//: public std::enable_shared_from_this<Konto> damit shared pointer von der Klasse geshared werden darf
private:
	std::string kontonummer;
	int kontostand{0};
	int disporahmen{1000};
	int gebuehren{0};
	std::vector<std::weak_ptr<Person>> zeichnungsberechtigt; //max10 mind. 1
public:
	static int k;//!!!!Danger, das muss noch geändert werden
	Konto(std::shared_ptr<Person>);
	void einzahlen (unsigned betrag);
	bool auszahlen (unsigned betrag);
	virtual bool ueberweisen (unsigned betrag, Konto& ziel);//virtual damit ich von Giro und Buiness drauf zugreifen kann
	int get_kontostand();//geht
	std::string get_kn();//geht
	bool add_zeichnungsberechtigt(std::shared_ptr<Person> p);//fügt im Vektor zeichnungsberechtigt eine neue Person ein
	virtual void berechnung_geb(unsigned)=0;//ähnlich wie überweisen nur muss diese Methode =0 gesetzt werden damit sie pure virtuell ist
	virtual std::ostream& print (std::ostream&) const;
};


class Girokonto:public Konto, public std::enable_shared_from_this<Girokonto>{//Girokonto:public Konto lässt die Klasse Girokonto von Konto erben und da zugriff auf alle public Methoden
	double geb{0};//Gebühren werden bei jeder überweisung aufsummiert
public:
	Girokonto(std::shared_ptr<Person>);
	std::ostream& print (std::ostream&) const;
	void berechnung_geb(unsigned);//Methode die bei Konto Virtuell ist und berechnet die Gebühren
	bool ueberweisen(unsigned betrag, Konto& ziel);//Methode die bei Konto Virtuell ist

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


class Zauberer {
	int zauberwissen=0;
public:
	int virtual lerneffekt(int stunden) const=0;
	bool lerne(int stunden);
	void print()const;
};

class Z_Gryffindor : public Zauberer {
	int lerneffekt(int stunden) const;
};
class Z_Slytherin : public Zauberer {
	int lerneffekt(int stunden) const;
};


class Schule {
	std::vector<std::shared_ptr<Zauberer>>v;
public:
	Schule(std::vector<std::shared_ptr<Zauberer>> v);
	bool unterrichten(int stunden);
};

