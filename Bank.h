#pragma once
#include<string>
#include<memory>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include"Konto.h"
#include"Person.h"
class Konto;
class Person;

class Bank{
	std::unordered_map<std::string, std::shared_ptr<Person>> kunden;
	std::unordered_map<std::string, std::shared_ptr<Konto>> konten;//sortiert nach kontoNR
public:
/*neuer Kunde- zuerst wird Person erstellt diese Person wird in die unordered_map kunden gespeichert [name, Person]
danach wird für die Person ein neues Konto erstellt, dieses wird dann in unordered_map konten gespeichert[kontonummer, konto]
*/
	std::string neuerKunde(std::string name, bool type);

	std::shared_ptr<Person> get_kunde(std::string);
	std::string neues_konto(Person& p, std::shared_ptr<Konto>);//neues konto wird erstellt und in der unordered_map gespeichert
	std::string neues_konto(Person& p, bool type);//selbe wie oben
	std::ostream& print(std::ostream&) const;//geht
	std::shared_ptr<Konto> get_Konto(std::string);//geht
	void kuendigen(Person& p);//löscht die Person aus den maps raus
};
std::ostream& operator<<(std::ostream&, const Bank&);