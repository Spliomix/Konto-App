
#include"Bank.h"




////////////////////////Bank
std::ostream& Bank::print(std::ostream & os) const {
	for(auto & elem: kunden)
				os<<"Inhalt der Bank Unordered Map -kunden-"<<elem.first<<"\n";
	for (auto & elem : konten)
		os << "Inhalt der Bank Unordered Map -Konto-" << elem.first << *(elem.second) << "\n";
		return os;
	}

	std::string Bank::neuerKunde(std::string name, bool type){
		if (kunden.find(name) != kunden.end())return "0";
		auto it=kunden.emplace(name, std::make_shared<Person>(name));
		auto k=it.first->second->neues_konto(type);//erstelle für die frisch erstellte Person ein Konto
		konten.emplace(k->get_kn(), k);
		return k->get_kn();
	}

	std::shared_ptr<Person> Bank::get_kunde(std::string name) {
		auto it=kunden.find(name);
		if (it == kunden.end())return nullptr;
		return it->second;
	}
	std::string Bank::neues_konto(Person& p, std::shared_ptr<Konto> k) {
		//ordnet ein bestehendes Konto der Person zu
		//fügt das neu erstelle Konto in die unordered map
		if (konten.find(k->get_kn()) == konten.end())return "0";
			konten.emplace(p.neues_konto(k)->get_kn(), p.neues_konto(k));
			return k->get_kn();
	}
	std::string Bank::neues_konto(Person& p, bool type) {
		//erstellt ein neues Konto für diese Person
		//fügt das neu erstelle Konto in die unordered map
		auto temp = p.neues_konto(type)->get_kn();
		konten.emplace(temp, p.neues_konto(type));
		return temp;
	}
	std::shared_ptr<Konto> Bank::get_Konto(std::string knr) {
		if (konten.find(knr) == konten.end())return nullptr;
		return (konten.find(knr)->second);
	}
	void Bank::kuendigen(Person& p) {
		p.kuendigen();
		for(auto & elem : p.get_konten()){
			if(konten.find(elem->get_kn())->second.use_count()==1)
				konten.erase(elem->get_kn());
		}
		kunden.erase(kunden.find(p.get_name()));
	}







std::ostream& operator<<(std::ostream& os, const Bank& b) {
	b.print(os);
	return os;
}
