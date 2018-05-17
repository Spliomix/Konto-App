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
	bool alternate{ false };
public:
	Person(){}
	Person(std::string name);
	bool konto_teilen(std::shared_ptr<Konto> k, Person& p);//geht
	std::shared_ptr<Konto> neues_konto();//geht
	std::shared_ptr<Konto> neues_konto(std::shared_ptr<Konto>);//geht
	std::string get_name();
	std::vector<std::shared_ptr<Konto>> get_konten();//geht
	void kuendigen();//alle Konten werden gekündigt
	std::ostream& print (std::ostream&) const;//geht
};
std::ostream& operator<<(std::ostream&, const Person&);