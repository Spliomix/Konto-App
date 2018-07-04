#pragma once
#include<string>
#include<memory>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include"Bank.h"
#include"Konto.h"

class Bank;
class Konto;


class Person:public std::enable_shared_from_this<Person>{
	std::string name;
	std::vector<std::shared_ptr<Konto>> konten; //beliebig viele mind. 1
	bool alternate{ false };//jedes zweite Konto ist ein Girokonto
public:
	Person(){}
	Person(std::string name);
	bool konto_teilen(std::shared_ptr<Konto> k, Person& p);
	std::shared_ptr<Konto> neues_konto(bool type);
	std::shared_ptr<Konto> neues_konto(std::shared_ptr<Konto>);
	std::string get_name();
	std::vector<std::shared_ptr<Konto>> get_konten();//gibt alle Konten dieser Person zurück
	void kuendigen();//alle Konten werden gekündigt
	std::ostream& print (std::ostream&) const;
};
std::ostream& operator<<(std::ostream&, const Person&);