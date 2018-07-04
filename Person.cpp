
#include"Person.h"


/////////////////////////////////Person
Person::Person(std::string name) {
	this->name = name;
}
	bool Person::konto_teilen(std::shared_ptr<Konto> k, Person& p){
		//Zeichnungsberechtigten ergänzen
		auto sp = std::make_shared<Person>(p);
		if (!k->add_zeichnungsberechtigt(sp))return false;
		p.neues_konto(k);
		return true;//checken
}
	std::shared_ptr<Konto> Person::neues_konto(bool type){
		if (type) {
			std::shared_ptr<Girokonto> k{ std::make_shared<Girokonto>(shared_from_this()) };
			konten.push_back(k);
			return k;//checken	
		}
		std::shared_ptr<Businesskonto> k{ std::make_shared<Businesskonto>(shared_from_this()) };
		konten.push_back(k);
		return k;//checken
	}
	std::shared_ptr<Konto> Person::neues_konto(std::shared_ptr<Konto> k) {
		if (k->add_zeichnungsberechtigt(shared_from_this()))
			konten.push_back(k);
		return k;//checken
	}
	void Person::kuendigen() {
		konten.clear();
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

    
std::ostream& operator<<(std::ostream& os, const Person& p) {
	p.print(os);
	return os;
}