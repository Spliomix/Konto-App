

#include<string>
#include<memory>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<algorithm>

class Person;
class Bank;
class Konto;

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
	void einzahlen (unsigned betrag);//geht
	bool auszahlen (unsigned betrag);//geht
	bool ueberweisen (unsigned betrag, Konto& ziel);//geht
	int get_kontostand();//geht
	std::string get_kn();//geht
	bool add_zeichnungsberechtigt(std::shared_ptr<Person> p);//geht
	std::shared_ptr<Konto> get_shared();
	std::ostream& print (std::ostream&) const;//geht
};

class Person:public std::enable_shared_from_this<Person>{
	std::string name;
	std::vector<std::shared_ptr<Konto>> konten; //beliebig viele mind. 1
public:
	Person(){}
	Person(std::string name);
	bool konto_teilen(Konto& k, Person& p);//geht
	std::shared_ptr<Konto> neues_konto();//geht
	std::shared_ptr<Konto> neues_konto(Konto&);//geht
	std::string get_name();
	std::vector<std::shared_ptr<Konto>> get_konten();//geht
	void kuendigen();//alle Konten werden gekündigt
	std::ostream& print (std::ostream&) const;//geht
};


class Bank{
	std::unordered_map<std::string, std::shared_ptr<Person>> kunden;
	std::unordered_map<std::string, std::shared_ptr<Konto>> konten;//sortiert nach kontoNR
public:
	std::string neuerKunde(std::string name);//geht
	std::shared_ptr<Person> get_kunde(std::string);//geht
	std::string neues_konto(Person& p, Konto& k);//geht
	std::string neues_konto(Person& p);//geht
	std::ostream& print(std::ostream&) const;//geht
	std::shared_ptr<Konto> get_Konto(std::string);//geht
};

class Girokonto{
};

class Businesskonto{
};

std::ostream& operator<<(std::ostream&, const Bank&);
std::ostream& operator<<(std::ostream&, const Person&);
std::ostream& operator<<(std::ostream&, const Konto&);


