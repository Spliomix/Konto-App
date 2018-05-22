// KontoApp.cpp : Defines the entry point for the console application.
//

//#include"stdafx.h"
//#include"Bank.h"
#include"Konto.h"
//#include"Person.h"
#include <sstream>
#include <fstream>
#include <iomanip>
#include <numeric>

std::string login(std::shared_ptr<Bank> b, bool &logged_in) {
	std::string cmd;
	std::cout << "Geben sie die Kontonummer ein, falls sie diese nicht wissen drucken sie die Taste >R<: ";
	std::cin >> cmd;
	if (cmd == "R") {
		std::cout << "Geben sie den Namen der Person ein: ";
		std::cin >> cmd;
		std::cout << "Folgende Konten stehen zur Auswahl: ";
		for (auto &elem : b->get_kunde(cmd)->get_konten())
			std::cout << elem->get_kn() << "\n";
		std::cout << "Geben sie die Kontonummer ein: \n";
		std::cin >> cmd;
	}
	logged_in = true;
	return cmd;
}

enum class Code { quit = 0, change_bank,logout,kuendigen, einzahlen, auszahlen, transfer, teilen, konto_erstellen, person_erstellen, all, help };

struct Command {
	Code code;
	std::string name, info;
	bool need_bank, key_args;
};



std::vector<Command> commands = {
{ Code::change_bank, "change_bank", "change the actual bank", false, false },
{ Code::einzahlen, "einzahlen", "bring money on the bank", true, false },
{ Code::logout, "logout", "logout", true, false },
{ Code::kuendigen, "kuendigen", "kuendigen", true, false },
{ Code::teilen, "teilen", "share Konto", true, false },
{ Code::konto_erstellen, "new_konto", "create new konto", true, false },
{ Code::all, "all", "show alle person/Kontos who are created by this bank", true, false },
{ Code::auszahlen, "auszahlen", "take money", true, false },
{ Code::transfer, "transfer", "transfer money", true, false },
{ Code::person_erstellen, "new_pers", "create new person", true, false },
{ Code::help, "help", "Hilfe", false, false },
{ Code::quit, "quit (or EOF)", "quit program (deletes set)", false, false }
};
int main()
{
	std::shared_ptr<Bank>Raiffeisen(new Bank);
	std::shared_ptr<Bank>Bank_austria(new Bank);
	std::shared_ptr<Bank>Erste(new Bank);
	std::shared_ptr<Bank>Western_union(new Bank);
	std::unordered_map<std::string, std::shared_ptr<Bank>> Banks = { {"Raiffeisen",Raiffeisen}, {"Bank Austria",Bank_austria},{ "Erste Bank",Erste},{ "Western Union",Western_union} };


	std::shared_ptr<Bank> akt_bank;
	bool logged_in{ false };
	std::string akt_knr;

	std::string input;
	std::string show_line = "Konto App";
	int temp_choose{ 0 };
	std::string temp_str_choose;
	
	while (std::cout << "\n"<< show_line<<" >", std::getline(std::cin, input)) {
		std::istringstream line_stream(input);
		std::string cmd;
		line_stream >> cmd;
		if (!cmd.size()) continue;
		auto cmd_it = find_if(commands.begin(), commands.end(), [&cmd](const Command& c) {return !c.name.find(cmd); });
		if (cmd_it == commands.end()) {
			std::cout << cmd << "? ERROR - try 'help'";
			continue;
		}
		if (cmd_it->code == Code::quit) break;
		if (cmd_it->need_bank && !temp_choose) {
			std::cout << "ERROR - no bank (use 'change_bank')";
			continue;
		}
		switch (cmd_it->code) {

		case Code::help: {
			std::cout << '\n' << std::right << std::setfill('.');
			size_t maxw{ std::accumulate(commands.begin(), commands.end(), size_t{ 0 }, [](const size_t& m, const Command& c) { return std::max(m,c.name.size()); }) };
			for (const auto& x : commands)
				std::cout << x.name << ' ' << std::setw(maxw - x.name.size() + 3) << ' ' << x.info << '\n';
			std::cout << std::setfill(' ') << "\narguments surrounded by [] are optional\n";
			break;
		}case Code::change_bank: {
			while (true) {
				std::cout << "choose one of the banks: \n" <<
					"1: Raiffeisen\n" <<
					"2: Bank Austria\n" <<
					"3: Erste Bank\n" <<
					"4: Western Union\n" <<
					"Choose the number: ";

				std::cin >> temp_choose;
				if (temp_choose == 1) {
					temp_str_choose = "Raiffeisen";
					std::cout << "You choosed: Raiffeisen" << "\n\n";
					show_line = temp_str_choose;
				}
				else if (temp_choose == 2) {
					temp_str_choose = "Bank Austria";
					std::cout << "You choosed: Bank Austria" << "\n\n";
					show_line = temp_str_choose;
				}
				else if (temp_choose == 3) {
					temp_str_choose = "Erste Bank";
					std::cout << "You choosed: Erste Bank" << "\n\n";
					show_line = temp_str_choose;
				}
				else if (temp_choose == 4) {
					temp_str_choose = "Western Union";
					std::cout << "You choosed: Western Union" << "\n\n";
					show_line = temp_str_choose;
				}
				if (temp_choose < 5 || temp_choose>0) {
						akt_bank = Banks.find(temp_str_choose)->second;
					break;
				}

			}
			break;
		}case Code::person_erstellen: {
			std::cout << "Geben Sie bitte den Namen der Person ein: ";
			std::cin >> cmd;
			std::cout << "Ihre Kontonummer lautet: " << akt_bank->neuerKunde(cmd)<<"\n";
			break;
		}case Code::konto_erstellen: {
			std::cout << "Geben Sie bitte den Namen der Person ein für ein neues Konto angelegt werden soll: ";
			std::cin >> cmd;
			std::cout << "Ihre Kontonummer lautet: " << akt_bank->neues_konto(*(akt_bank->get_kunde(cmd))) << "\n";
			break;
		}case Code::all: {//not tested
			std::cout << "Personen und Konten: ";
			std::cout <<*akt_bank << "\n";
			break;
		}case Code::einzahlen: {
			if(!logged_in)
				akt_knr = login(akt_bank, logged_in);
			std::cout << "Aktueller Kontostand: " << akt_bank->get_Konto(akt_knr)->get_kontostand() << "€\n";
			unsigned betrag;
			std::cout << "Geben Sie den gewünschten Betrag ein: ";
			std::cin >> betrag;
			if (!std::cin)break;
			akt_bank->get_Konto(akt_knr)->einzahlen(betrag);
			std::cout << "Aktueller Kontostand: " << akt_bank->get_Konto(akt_knr)->get_kontostand() << "€\n";
			break;
		}case Code::auszahlen: {
			if (!logged_in)
				akt_knr = login(akt_bank, logged_in);
			std::cout << "logTEst: " << logged_in << "\n";
			std::cout << "Aktueller Kontostand: " << akt_bank->get_Konto(akt_knr)->get_kontostand() << "€\n";
			std::cout << "Geben Sie den gewünschten Betrag ein: ";
			unsigned betrag;
			while (1) {
				std::cin >> betrag;
				if (!std::cin)break;
				if(akt_bank->get_Konto(akt_knr)->auszahlen(betrag))break;
				std::cout << "Nicht genug Guthaben\n";
			}
			if (!std::cin)break;
			std::cout << "Aktueller Kontostand: " << akt_bank->get_Konto(akt_knr)->get_kontostand() << "€\n";
			break;
		}case Code::transfer: {
			if (!logged_in)
				akt_knr = login(akt_bank, logged_in);
			std::cout << "Aktueller Kontostand: " << akt_bank->get_Konto(akt_knr)->get_kontostand() << "€\n";
			unsigned betrag;
			std::string knr;
			std::cout << "Geben Sie den gewünschten Betrag ein: ";
			std::cin >> betrag;
			if (!std::cin)break;
			std::cout << "Geben Sie das gewünschte Konto ein: ";
			std::cin >> knr;

			//1 Probleme
			//1. überweisen geht so nur in innerhalb einer Bank
			akt_bank->get_Konto(akt_knr)->ueberweisen(betrag, *(akt_bank->get_Konto(knr)));
			break;
		}case Code::logout: {//not tested
			logged_in = false;
			break;
		}case Code::teilen: {//not tested
			if (!logged_in)
				akt_knr = login(akt_bank, logged_in);
			std::cout << "Geben Sie bitte ihren Namen ein: \n";
			std::cin >> cmd;
			auto temp_p = akt_bank->get_kunde(cmd);
			std::cout << "Geben Sie bitte die Kontonummer an: \n";
			std::cin >> cmd;
			std::string temp_knr = cmd;
			std::cout << "Geben Sie bitte den Namen an mit dem das Konto geteilt werden soll: \n";
			std::cin >> cmd;
			temp_p->konto_teilen(akt_bank->get_Konto(temp_knr), *(akt_bank->get_kunde(cmd)));
			break;
		}case Code::kuendigen: {//not tested
			std::cout << "Geben Sie bitte den Namen an der gekündigt wird: \n";
			std::cin >> cmd;
			akt_bank->kuendigen(*akt_bank->get_kunde(cmd));
			break;
		}


		}
	}
	
    return 0;
}

