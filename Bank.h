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
	std::string neuerKunde(std::string name);//geht
	std::shared_ptr<Person> get_kunde(std::string);//geht
	std::string neues_konto(Person& p, std::shared_ptr<Konto>);//geht
	std::string neues_konto(Person& p);//geht
	std::ostream& print(std::ostream&) const;//geht
	std::shared_ptr<Konto> get_Konto(std::string);//geht
	void kuendigen(Person& p);
};
std::ostream& operator<<(std::ostream&, const Bank&);