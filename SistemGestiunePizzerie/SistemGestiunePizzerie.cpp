#include <iostream>
#include <string>
using namespace std;

enum class Marime {
	Mica,
	Medie,
	Mare,
	Party
};
//clasa de baza
class Pizza {
protected:
	string denumirePizza;
	string* ingrediente;
	int nrIngrediente;
	int cantitate;
	double pret;
	Marime marime;
public:
	static int nrPizza;
	Pizza() :denumirePizza("necunoscuta"), nrIngrediente(0), ingrediente(nullptr), cantitate(0), pret(0), marime(Marime::Mica) {}
	Pizza(string denumirea, string* ingredientele, int numarIngrediente, int cantitatea, double pretul, Marime marimea) {
		this->denumirePizza = denumirea;
		this->nrIngrediente = numarIngrediente;
		this->ingrediente = new string[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->ingrediente[i] = ingredientele[i];
		}
		this->cantitate = cantitatea;
		this->pret = pretul;
		this->marime = marimea;
		nrPizza += this->cantitate;
	}

	Pizza(const Pizza& obj) {
		if (this != &obj) {
			this->cantitate = obj.cantitate;
			this->denumirePizza = obj.denumirePizza;
			this->nrIngrediente = obj.nrIngrediente;
			this->pret = obj.pret;
			this->marime = obj.marime;

			delete[] this->ingrediente;
			this->ingrediente = new string[obj.nrIngrediente];
			for (int i = 0; i < obj.nrIngrediente; i++)
				this->ingrediente[i] = obj.ingrediente[i];

			nrPizza += this->cantitate;
		}
		else  cout << "Incercati sa atribuiti unui obiect propriile sale date, nu am facut schimbari" << endl;
	}

	Pizza& operator=(const Pizza& obj) {
		if (this != &obj) {
			nrPizza -= this->cantitate;
			this->cantitate = obj.cantitate;
			nrPizza += this->cantitate;

			this->denumirePizza = obj.denumirePizza;
			this->nrIngrediente = obj.nrIngrediente;
			this->pret = obj.pret;
			this->marime = obj.marime;

			delete[] this->ingrediente;
			this->ingrediente = new string[obj.nrIngrediente];
			for (int i = 0; i < obj.nrIngrediente; i++)
				this->ingrediente[i] = string(obj.ingrediente[i]);
		}
		else cout << "Incercati sa atribuiti unui obiect propriile sale date, nu am facut schimbari" << endl;
		
		return *this;
	}

	string getDenumirePizza() {
		return this->denumirePizza;
	}
	void setDenumirePizza(string denumire) {
		this->denumirePizza = denumire;
	}

	int getNrIngrediente() {
		return this->nrIngrediente;
	}
	void setNrIngrediente(int nrIngr) {
		this->nrIngrediente = nrIngr;
	}

	string* getIngrediente() {
		return this->ingrediente;
	}
	void setIngrediente(string* ingr) {
		this->nrIngrediente = ingr->size();
		this->ingrediente = new string[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++)
			this->ingrediente[i] = string(ingr[i]);
		delete[] ingr;
	}

	int getCantitate() {
		return this->cantitate;
	}
	void setCantitate(int cant) {
		this->cantitate = cant;
	}

	double getPret() {
		return this->pret;
	}
	void setPret(double price) {
		this->pret = price;
	}

	Marime getMarime() {
		return this->marime;
	}
	void setMarime(Marime marimea) {
		this->marime = marimea;
	}

	friend ostream& operator<<(ostream& os, const Pizza& obj); 
	friend istream& operator>>(istream& is, Pizza& obj);

	double pretNormal() {
		return this->pret * this->cantitate;
	}

	void afisarePretFinal() {
		this->pret = reducere();
		cout << "Pretul final dupa aplicarea posibilelor reduceri: " << this->pret << endl;
	}

	double reducere() {
		double price = pretNormal();
		
		if (this->marime == Marime::Party && this->cantitate >= 2)
			return price * 0.93;	// 10% reducere;
		else if (this->marime == Marime::Mare && this->cantitate >= 2)
			return price * 0.93;	// 7% reducere;
		else if (price > 150)
			return price * 0.95;	// 5% reducere;
		else if (price > 100)
			return price * 0.95;	// 3% reducere;
		return price;
	}

	void extraIngrediente() {
		cout << "\nIntroduceti nr de ingrediente extra: ";
		int n; cin >> n;
		cout << "\nIntroduceti pretul unitar per ingredient: ";
		double p; cin >> p;
		if (n > 0) {
			if (p <= 0) cout << "Pretul trebuie sa fie mai mare de 0\n";
			else {
				this->pret += p * n;

				string* extra = new string[this->nrIngrediente + n];
				for (int i = 0; i < this->nrIngrediente; i++)
					extra[i] = this->ingrediente[i];

				for (int i = this->nrIngrediente; i < this->nrIngrediente + n; i++)
				{
					cout << "Introdu Ingredientul extra nr " << i - this->nrIngrediente + 1 << ": ";
					cin >> extra[i];
				}
				delete[] this->ingrediente; 
				this->nrIngrediente += n;
				this->ingrediente = extra;
			}
		}
		else cout << "Nr de ingrediente extra nu poate fi mai mic decat 1\n";
	}


	
	~Pizza() {
		if (this->ingrediente != nullptr) {
			delete[] this->ingrediente;
			this->ingrediente = nullptr; 
		}
		nrPizza -= this->cantitate;
	}
};
int Pizza::nrPizza = 0;

istream& operator>>(istream& is, Pizza& obj) {
	cout << "\n---PIZZA NOUA---\n";
	cout << endl << "Introduceti denumirea: ";
	getline(is,obj.denumirePizza);
	int inc = 0;	//	incercari
	do {
		cout << endl << "Introduceti numarul de ingrediente: ";
		is >> obj.nrIngrediente;
		if (obj.nrIngrediente < 3) cout << "Aveti nevoie de cel putin 3 ingrediente, aveti dreptul la inca " << 3 - inc << " incercari";
		inc++;
	} while (obj.nrIngrediente < 3 && inc != 4);

	if (inc == 4) {
		cout << "\nAm iesit, obiectul va fi declarat default\n";
		Pizza obj2;
		obj = obj2;
		return is;
	}

	is.get();
	cout << endl << "Ingredientele: ";
	delete[] obj.ingrediente;
	obj.ingrediente = new string[obj.nrIngrediente];
	for (int i = 0; i < obj.nrIngrediente; i++) {
		is >> obj.ingrediente[i];
	}

	inc = 0;
	do {
		cout << endl << "Introduceti cantitatea: ";
		is >> obj.cantitate;
		if (obj.cantitate < 1) cout << "Trebuie inregistrata cel putin 1 pizza, aveti dreptul la inca " << 3 - inc << " incercari";
		inc++;
	} while (obj.cantitate < 1 && inc != 4);

	if (inc == 4) {
		cout << "\nAm iesit, obiectul va fi declarat default\n";
		Pizza obj2;
		obj = obj2;
		return is;
	}

	inc = 0;
	do {
		cout << endl << "Introduceti pretul: ";
		is >> obj.pret;
		if (obj.pret < 15) cout << "Trebuie introdus un pret cel putin egal cu 15 lei, aveti dreptul la inca " << 3 - inc << " incercari";
		inc++;
	} while (obj.pret < 15 && inc != 4);

	if (inc == 4) {
		cout << "\nAm iesit, obiectul va fi declarat default\n";
		Pizza obj2;
		obj = obj2;
		return is;
	}

	is.get();
	cout << "Trebuie introdusa marimea (Mica, Medie, Mare sau Party)\n";
	inc = 1;
	string decizie;
	do {
		cout << endl << "Introduceti marimea: ";
		is >> decizie;
		if (decizie == "Mica")
		{
			obj.marime = Marime::Mica; break;
		}
		else if (decizie == "Medie")
		{
			obj.marime = Marime::Medie; break;
		}
		else if (decizie == "Mare")
		{
			obj.marime = Marime::Mare; break;
		}
		else if (decizie == "Party")
		{
			obj.marime = Marime::Party; break;
		}
		else {
			cout << "Trebuie introdusa o varianta valida, aveti dreptul la inca " << 3 - inc << " incercari";
			inc++;
		}
	} while (inc != 4);

	if (inc == 4) {
		cout << "\nAm iesit, obiectul va fi declarat default\n";
		Pizza obj2;
		obj = obj2;
		return is;
	}

	return is;
}

ostream& operator<<(ostream& os, const Pizza& obj)
{
	os << endl;
	os << "Denumire pizza: " << obj.denumirePizza << endl;
	os << "Numarul de ingrediente:  " << obj.nrIngrediente;
	if (obj.nrIngrediente > 0) {
		os << "\nIngredientele: " << endl;
		for (int i = 0; i < obj.nrIngrediente - 1; i++)
			os << obj.ingrediente[i] << ", ";
		os << obj.ingrediente[obj.nrIngrediente - 1] << endl;
	}
	else os << endl;
	os << "Cantitate: " << obj.cantitate << endl;
	os << "Pret unitar: " << obj.pret << endl;
	os << "Status: ";
	switch (obj.marime) {
	case Marime::Mica: os << "Mica"; break;
	case Marime::Medie: os << "Medie"; break;
	case Marime::Mare: os << "Mare"; break;
	case Marime::Party:os << "Party"; break;
	default: os << "Necunoscut";
	}
	os << endl;
	return os;
}


struct Destinatie {
	string den_localitate, strada;
	int nr, ap;		//la ap trec 0 daca e casa
	string bloc;
};

struct Client {
	string nume, prenume;
};

//clasa derivata 1
class PizzaLivrata : public Pizza {
private:
	Destinatie destinatie;
	Client client;
public:

	friend istream& operator>>(istream& is, PizzaLivrata& obj);
	friend ostream& operator<<(ostream& os, const PizzaLivrata& obj); 

	PizzaLivrata() :Pizza(), destinatie({ "Necunoscuta","Str. necunoscuta",0,0,"---"}), client({"Anonimescu","Anonim"}) {}

	PizzaLivrata(string denumirea, string* ingredientele, int numarIngrediente, int cantitatea, double pretul, Marime marimea,	// pentru Pizza
				string den_loc, string stradaP, int numar, int apartament, string bloc)	// pentru ComandaPizza
				 :Pizza(denumirea, ingredientele, numarIngrediente, cantitatea, pretul, marimea)	
	{
		this->destinatie.den_localitate = denumirea;
		this->destinatie.strada = stradaP;
		this->destinatie.nr = numar;
		this->destinatie.ap = apartament;
		this->destinatie.bloc = bloc;

		nrPizza += this->cantitate;
 	}

	PizzaLivrata(const PizzaLivrata& obj):Pizza(obj) {
		if (this != &obj) {
			this->destinatie = obj.destinatie;
			this->client = obj.client;
		}
		else cout << "Incercati sa atribuiti unui obiect propriile sale date, nu am facut schimbari" << endl;
	}

	PizzaLivrata& operator=(const PizzaLivrata& obj){
		if (this != &obj) {

			nrPizza -= this->cantitate;
			Pizza::operator=(obj);
			nrPizza += this->cantitate;

			this->destinatie = obj.destinatie;
			this->client = obj.client;
		}
		else cout << "Incercati sa atribuiti unui obiect propriile sale date, nu am facut schimbari" << endl;

		return *this;
	}	

	~PizzaLivrata() {}

	void afisarePretFinal(double tarif_livrare) {
		this->pret = reducere() + tarif_livrare;
		cout << "Pretul final dupa aplicarea posibilelor reduceri si a tarifului de livrare: " << this->pret << endl;
	} 

	void afisarePretFinalCuCitireDeLaTastatura() {
		double tarif_livrare;
		cout << "Introdu tariful de livrare:";
		cin >> tarif_livrare;
		this->pret = reducere() + tarif_livrare;
		cout << "Pretul final dupa aplicarea posibilelor reduceri si a tarifului de livrare: " << this->pret << endl;
	}

	Destinatie getDestinatie() {
		return this->destinatie;
	}
	void setdestinatie(Destinatie loc) {
		this->destinatie = loc;
	}

	Client getClient() {
		return this->client;
	}
	void setClient(Client cl) {
		this->client = cl;
	}

	void printDetaliiDestinatie() {
		cout << "\nAdresa de livrare:" << this->destinatie.den_localitate << ", strada " 
			<< this->destinatie.strada << ", nr " << this->destinatie.nr;
		if (this->destinatie.ap != 0)
			cout << ",bl " << this->destinatie.bloc << ", ap " << this->destinatie.ap;
	}

};
istream& operator>>(istream& is, PizzaLivrata& obj)
{
	is >> static_cast<Pizza&>(obj);

	cout << "\nIntrodu date despre destinatie\n";
	cout << "Localitatea: ";
	is >> obj.destinatie.den_localitate;

	cout << "Strada: ";
	is >> obj.destinatie.strada;

	cout << "Numarul:\n ";
	do {
		cout << "(valoarea sa fie intre 1 si 1000)\n";
		is >> obj.destinatie.nr;
	} while (obj.destinatie.nr < 1 || obj.destinatie.nr > 1000);

	cout << "Apartamentul: \n";
	do {
		cout << "(0 daca destinatia nu e un bloc)\n(valoarea sa fie intre 0 si 1000)\n";
		is >> obj.destinatie.ap;
	} while (obj.destinatie.ap < 0 || obj.destinatie.ap > 1000);

	if (obj.destinatie.ap == 0) {
		string blocGol = "---";
		obj.destinatie.bloc = blocGol;
	}
	else {
		cout << " Blocul: \n";
		is >> obj.destinatie.bloc;
	}

	cout << "Introdu date despre client\n nume: ";
	
	is >> obj.client.nume;

	cout << "prenume: ";
	
	is >> obj.client.prenume;

	return is;
}
ostream& operator<<(ostream& os, const PizzaLivrata& obj)
{
	os << "\n---Date despre pizza de livrat---\n";
	os << static_cast<const Pizza&>(obj);

	os << "Destinatie este:\nLocalitatea " << obj.destinatie.den_localitate << ", strada " << obj.destinatie.strada << ", nr " << obj.destinatie.nr;
	if (obj.destinatie.ap != -1) {
		os << "\nblocul: " << obj.destinatie.bloc << ", apartamentul: " << obj.destinatie.ap;
	}
	os << "\nClientul este : " << obj.client.nume << " " << obj.client.prenume << endl;

	return os;
}

struct OraRezervare {
	int ora, minut;
};
struct CineRezerva {
	string nume, prenume;
};
//clasa derivata 2
class PizzaRestaurant : public Pizza {
private:
	int nrMasa;
	OraRezervare rezervare;
	CineRezerva clientRestaurant;
public:
	PizzaRestaurant() :nrMasa(0), rezervare({ 0,0 }), clientRestaurant({"Necunoscut", "Necunoscut"}){}
	PizzaRestaurant(string denumirea, string* ingredientele, int numarIngrediente, int cantitatea, double pretul, Marime marimea,	// pentru Pizza)
					int numarMasa,OraRezervare rezerv,CineRezerva cl)	// pentru PizzaRestaurant
					:Pizza(denumirea, ingredientele, numarIngrediente, cantitatea, pretul, marimea)
	{
		this->nrMasa = numarMasa;
		this->rezervare.ora = rezerv.ora;
		this->rezervare.minut = rezerv.minut;
		this->clientRestaurant.nume = cl.nume;
		this->clientRestaurant.prenume = cl.prenume;
	}

	PizzaRestaurant(const PizzaRestaurant& obj) :Pizza(obj) {
		if (this != &obj) {
			this->nrMasa = obj.nrMasa;
			this->rezervare = obj.rezervare;
			this->clientRestaurant = obj.clientRestaurant;
		}
		else cout << "Incercati sa atribuiti unui obiect propriile sale date, nu am facut schimbari" << endl;
	}
	PizzaRestaurant& operator=(const PizzaRestaurant& obj) 
	{
		if (this != &obj) {
			nrPizza -= this->cantitate;
			Pizza::operator=(obj);
			nrPizza += this->cantitate;

 			this->nrMasa = obj.nrMasa;
			this->rezervare = obj.rezervare;
			this->clientRestaurant = obj.clientRestaurant;
		}
		else cout << "Incercati sa atribuiti unui obiect propriile sale date, nu am facut schimbari" << endl;
		
		return *this;
	}
	
	int getNrMasa() {
		return this->nrMasa;
	}
	void setNrMasa(int numarMasa) {
		this->nrMasa = numarMasa;
	}
	OraRezervare getRezervare() {
		return this->rezervare;
	}
	void setRezervare(OraRezervare rezerv) {
		if ((rezerv.ora < 0 || rezerv.ora>23) || (rezerv.minut < 0 || rezerv.minut>59))cout << "Introduceti date corespunzatoare pentru ora,minut\n";
		else if ((rezerv.ora < 8 && rezerv.minut < 30) || (rezerv.ora > 23))cout << "Orar disponibil este intre 8:30 si 23:00\n";
		else this->rezervare = rezerv;
	}
	CineRezerva getClientRestaurant() {
		return this->clientRestaurant;
	}
	void setClientrestaurant(CineRezerva cl) {
		this->clientRestaurant = cl;
	}
	~PizzaRestaurant() {}

	void printDetaliiRezervare() {
		cout << "\nMasa " << this->nrMasa << " a fost rezervata la ora ";
			if (this->rezervare.ora < 10) cout << '0';
			cout << this->rezervare.ora << ':';
			if (this->rezervare.minut < 10) cout << '0';
			cout << this->rezervare.minut;
	}

	friend istream& operator>>(istream& is, PizzaRestaurant& obj);
	friend ostream& operator<<(ostream& os, const PizzaRestaurant& obj);
};

istream& operator>>(istream& is, PizzaRestaurant& obj) {
	is >> static_cast<Pizza&>(obj);

	cout << "Introdu ora rezervarii\n";
	cout << "Orar disponibil este intre 8:30 si 23:00\n";
	do {
		cout << "Introdu datele\nOra:"; is >> obj.rezervare.ora;
		cout << "Minutul:"; is >> obj.rezervare.minut;
		if ((obj.rezervare.ora < 0 || obj.rezervare.ora>23) || (obj.rezervare.minut < 0 || obj.rezervare.minut>59))
			cout << "Introduceti date corespunzatoare pentru ora,minut\n";
		else if ((obj.rezervare.ora < 8 && obj.rezervare.minut < 30) || (obj.rezervare.ora > 23))
			cout << "Orar disponibil este intre 8:30 si 23:00\n";
	} while
		(
			(obj.rezervare.ora < 8 || obj.rezervare.ora > 23) || 
			(obj.rezervare.minut < 0 || obj.rezervare.minut > 59) || 
			(obj.rezervare.ora * 60 + obj.rezervare.minut < 8 * 60 + 30 || obj.rezervare.ora * 60 + obj.rezervare.minut > 23 * 60)
		);
	
	cout << "Introdu datele clientului care face rezervarea:";
	cout << "Numele: ";  is >> obj.clientRestaurant.nume;
	cout << "Prenumele: ";  is >> obj.clientRestaurant.prenume;
	
	cout << "Introdu numarul mesei: ";
	is >> obj.nrMasa;

	return is;
}

ostream& operator<<(ostream& os, const PizzaRestaurant& obj) {

	os << "\n--- date despre rezervare ---\n";
	os << "Ora rezervarii:\n" << obj.rezervare.ora << ':' << obj.rezervare.minut;
	
	os << "\nDe catre clientul: " << obj.clientRestaurant.nume << ' '<<obj.clientRestaurant.prenume;
	
	os << "\nMasa numarul: " << obj.nrMasa;
	os << endl;

	os << static_cast<const Pizza&>(obj);

	return os;
}

class Bucatar {
private:
	string nume;
	string prenume;
	double salariu;
	int nrTipuriPizzaProduse;
	Pizza** tipuriPizzaProduse;
public:
	Bucatar():nume("numeInvalid"),prenume("prenumeInvalid"),salariu(0),nrTipuriPizzaProduse(0),tipuriPizzaProduse(nullptr){}
	Bucatar(string numeP, string prenumeP, double salariuP, int nrPizza, Pizza* pizza[]) {
		
		if (salariuP < 3300) {
			cout << "\nNu putem oferi un salariu mai mic de 3300, am actualizat salariul la 3300 de lei";
			salariuP = 3300;
		}
		else if (salariuP > 18000) {
			cout << "\nNu putem oferi salarii atat de mari, am actualizat salariul la 10000 de lei";
			salariuP = 10000;
		}

		this->nume = numeP; this->prenume = prenumeP;
		this->salariu = salariuP;

		this->nrTipuriPizzaProduse = nrPizza;

		delete[]tipuriPizzaProduse;
		this->tipuriPizzaProduse = new Pizza * [this->nrTipuriPizzaProduse];
		for (int i = 0; i < this->nrTipuriPizzaProduse; i++) 
			this->tipuriPizzaProduse[i] = new Pizza(*pizza[i]);

	}

	Bucatar(const Bucatar& obj) {
		this->nume = obj.nume;
		this->prenume = obj.prenume;
		this->salariu = obj.salariu;
		this->nrTipuriPizzaProduse = obj.nrTipuriPizzaProduse;

		this->tipuriPizzaProduse = new Pizza * [this->nrTipuriPizzaProduse];
		for (int i = 0; i < this->nrTipuriPizzaProduse; i++) {
			this->tipuriPizzaProduse[i] = new Pizza(*obj.tipuriPizzaProduse[i]);
		}
	}

	Bucatar& operator=(const Bucatar& obj) {
		this->nume = obj.nume; 
		this->prenume = obj.prenume;
		this->salariu = obj.salariu;
		this->nrTipuriPizzaProduse = obj.nrTipuriPizzaProduse;

		for (int i = 0; i < this->nrTipuriPizzaProduse; i++)
			delete this->tipuriPizzaProduse[i];
		delete[] this->tipuriPizzaProduse;

		this->tipuriPizzaProduse = new Pizza * [this->nrTipuriPizzaProduse];

		for (int i = 0; i < this->nrTipuriPizzaProduse; i++)
			this->tipuriPizzaProduse[i] = new Pizza(*obj.tipuriPizzaProduse[i]);

		return *this;
	}

	~Bucatar() {
		for (int i = 0; i < this->nrTipuriPizzaProduse; i++) {
			if (this->tipuriPizzaProduse[i] != nullptr) {
				delete this->tipuriPizzaProduse[i];
				this->tipuriPizzaProduse[i] = nullptr;
			}
		}
		delete[] this->tipuriPizzaProduse;
	}

	string getNume() {
		return this->nume;
	}
	void setNume(string numeP) {
		this->nume = numeP;
	}

	string getPrenume() {
		return this->nume;
	}
	void setPrenume(string prenumeP) {
		this->prenume = prenumeP;
	}

	double getSalariu() {
		return this->salariu;
	}
	void setSalariu(double salariuP) {
		this->salariu = salariuP;
	}

	int getNrPizzaProduse() {
		return this->nrTipuriPizzaProduse;
	}
	void setNrPizzaProduse(int nrPizzaProduseP) {
		if (nrPizzaProduseP > this->nrTipuriPizzaProduse) {
			cout << "vectorul are " << this->nrTipuriPizzaProduse << " elemente, vrei sa schimbi valoarea in " << nrPizzaProduseP;
			cout << "\va trebui sa adaugati si elemente in vector, daca doriti sa continuati apasati 1: ";
			bool unu;
			cin >> unu;
			if (unu == 1) {
				this->nrTipuriPizzaProduse = nrPizzaProduseP;
				cout << "\nIn regula, adaugati elementele noi:\n";
				for (int i = this->nrTipuriPizzaProduse; i < nrPizzaProduseP; i++)
				{
					Pizza pTemp;
					cin >> pTemp;
					*this += pTemp;
				}
			}
			else cout << "\nam iesit fara sa facem schimbari\n";
		}
	}

	Pizza** getPizzaProduse() {
		return this->tipuriPizzaProduse;
	}

	Pizza** setPizzaProduse() {
		delete[] this->tipuriPizzaProduse;
		this->tipuriPizzaProduse = new Pizza * [this->nrTipuriPizzaProduse];

		for (int i = 0; i < this->nrTipuriPizzaProduse; i++) {
			Pizza p1;
			cin >> p1;
			*this += p1;
		}

		return this->tipuriPizzaProduse;
	}

	Pizza* operator[](int index) const {
		if (index >= 0 && index < nrTipuriPizzaProduse) {
			return tipuriPizzaProduse[index];
		}
		cout << "\nIndex invalid\n";
		return nullptr;
	}

	double salariuNet() {
		return this->salariu + calcul_bonusuri() 
			- (this->salariu * (100 - 35) 
				+ ( this->salariu + calcul_bonusuri() - this->salariu * (100 - 35) )	 * 10);
	}

	friend ostream& operator<<(ostream& os, const Bucatar& obj);
	friend istream& operator>>(istream& is, Bucatar& obj);

	void printNumarTotalPizza() {
		int nrTotal = 0;
		for (int i = 0; i < this->nrTipuriPizzaProduse; i++)
			nrTotal += this->tipuriPizzaProduse[i]->getCantitate();
		cout << "\nnumarul total de pizza produse de Bucatarul " << this->nume << ' ' << this->prenume 
			<< " este " << this->nrTipuriPizzaProduse << " pizza" << endl;
	}

	int returnNumarTotalPizza() {
		int nrTotal = 0;
		for (int i = 0; i < this->nrTipuriPizzaProduse; i++)
			nrTotal += this->tipuriPizzaProduse[i]->getCantitate();
		cout << "\nnumarul total de pizza produse de Bucatarul " << this->nume << ' ' << this->prenume
			<< " este " << this->nrTipuriPizzaProduse << " pizza" << endl;
		return nrTotal;
	}

	Bucatar& operator+=(const Pizza& newPizza) {
		Pizza** tempTipuriPizzaProduse = new Pizza * [this->nrTipuriPizzaProduse + 1];

		for (int i = 0; i < nrTipuriPizzaProduse; i++) {
			tempTipuriPizzaProduse[i] = this->tipuriPizzaProduse[i];
		}

		tempTipuriPizzaProduse[nrTipuriPizzaProduse] = new Pizza(newPizza);

		delete[] this->tipuriPizzaProduse;
		this->tipuriPizzaProduse = tempTipuriPizzaProduse;

		this->nrTipuriPizzaProduse++;

		return *this;
	}

	Bucatar& operator-=(const int pozitie) {
		
		Pizza** tempTipuriPizzaProduse = new Pizza * [this->nrTipuriPizzaProduse - 1];

		if (pozitie >= 0 && pozitie < this->nrTipuriPizzaProduse) {
			
			int j = 0;
			for (int i = 0; i < nrTipuriPizzaProduse; i++) {
				if (i != pozitie) {
					tempTipuriPizzaProduse[j] = this->tipuriPizzaProduse[i];
					j++;
				}
			}

			delete[] this->tipuriPizzaProduse;
			this->tipuriPizzaProduse = tempTipuriPizzaProduse;

			this->nrTipuriPizzaProduse--;
		}
		
		return *this;
	}

	int calcul_bonusuri() {
		int nrTotal = this->returnNumarTotalPizza();
		if (nrTotal > 105)return this->salariu * 0.12;
		else if (nrTotal > 75)return this->salariu * 0.09;
		else if (nrTotal > 45)return this->salariu * 0.05;
		else return 0;
	}
};

istream& operator>>(istream& is, Bucatar& obj) {
	cout << "Introdu numele bucatarului: ";
	is >> obj.nume;
	cout << "Introdu prenumele bucatarului: ";
	is >> obj.prenume;

	do {
		cout << "Introdu salariul: ";
		is >> obj.salariu;
		if (obj.salariu < 0)cout << "\nNu poti da salariu negativ..\n";
		else if (obj.salariu < 3300) cout << "\nSalariul minim este 3300 de lei brut\n";
		else if (obj.salariu > 10000) cout << "\nSalariul nu poate fi mai mare de 10000\n";
	} while (obj.salariu < 3300 || obj.salariu >10000);

	cout << "\nIntrodu numarul de tipuri de pizza pe care sa le faca bucatarul " << obj.nume << ' ' << obj.prenume << ": ";
	is >> obj.nrTipuriPizzaProduse;
	obj.tipuriPizzaProduse = new Pizza * [obj.nrTipuriPizzaProduse];

	cout << endl;
	for (int i = 0; i < obj.nrTipuriPizzaProduse; i++) {
		obj.tipuriPizzaProduse[i] = new Pizza();
		cout << "Introdu date despre pizza numarul " << i + 1 << ": ";
		is.get();
		is >> *obj.tipuriPizzaProduse[i];
	}

	return is;
}

ostream& operator<<(ostream& os, const Bucatar& obj) 
{
	os << "\n---Date despre bucatari---";
	os << "\nNumele si prenumele: " << obj.nume << ' ' << obj.prenume;
	os << "\nSalariul: " << obj.salariu;
	os << "\nNumarul de tipuri de pizza produse: " << obj.nrTipuriPizzaProduse;
	for (int i = 0; i < obj.nrTipuriPizzaProduse; i++) {
		os << "\nPizza  " << obj.tipuriPizzaProduse[i]->getDenumirePizza();
		os << ", in cantitate de " << obj.tipuriPizzaProduse[i]->getCantitate();
	}
	os << endl;
	return os;
}

int main() {

	string denumire = "Quattro Stagioni";
	string ingrediente[] = {"masline","salam","cascaval","ardei"};
	Pizza p1(denumire, ingrediente, 4, 3, 17, Marime::Medie);

	Pizza p2;
	cin >> p2;
	p1 = p2;
	Pizza p3(p1);
	cout << p3;

	p3.extraIngrediente();
	cin.get();	//golesc buffer-ul
	p3.pretNormal();
	p3.reducere();
	p3.afisarePretFinal();
	cin.get();

	PizzaLivrata pl1;
	cin >> pl1;
	cout << pl1;
	pl1.printDetaliiDestinatie();
	cin.get();
	cout << endl;

	PizzaLivrata pl2 = pl1;
	pl1.afisarePretFinal(4);	//permite tarif pentru ca e cu livrare
	pl2.afisarePretFinalCuCitireDeLaTastatura();
	cin.get();
	cout << endl;

	PizzaRestaurant pr1;
	cin >> pr1;
	PizzaRestaurant pr2(pr1);
	pr2.printDetaliiRezervare();
	cout << endl;

	string nume = "Bucatarescu";
	string prenume = "Stefan";	// chefan
	Pizza* pizzaArray[] = {&p1, &p2, &pl1, &pr1};
	Bucatar b1(nume,prenume,5000,4,pizzaArray);

	cout << b1;
	b1.calcul_bonusuri();
	double salariuNet_b1 = b1.salariuNet();
	cout << salariuNet_b1;
	b1+=p3;	//adaug element in vector
	b1.printNumarTotalPizza();
	b1 -= 2;	//elimin element in functie de pozitie (aici 2)
	b1.printNumarTotalPizza();
	cout<<b1[3];
	
	Bucatar b2;
	cin >> b2;
	cout << b2;

	return 0;
}
