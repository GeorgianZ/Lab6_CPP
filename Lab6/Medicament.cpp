#include "Medicament.h"
#include <assert.h>

string Medicament::get_denumire() const {
	return this->denumire;
}

string Medicament::get_producator() const {
	return this->producator;
}

string Medicament::get_substanta_activa() const {
	return this->substanta_activa;
}

double Medicament::get_pret() const {
	return this->pret;
}

void Medicament::set_denumire(string denumireNoua) {
	this->denumire = denumireNoua;
}

void Medicament::set_producator(string producatorNou) {
	this->producator = producatorNou;
}

void Medicament::set_substanta_activa(string sub_act) {
	this->substanta_activa = sub_act;
}

void Medicament::set_pret(double pretNou) {
	this->pret = pretNou;
}

void test_domain()
{
	Medicament m1{ "Paracetamol","Farmacisti","nuj",25 };
	assert(m1.get_denumire() == "Paracetamol");
	assert(m1.get_producator() == "Farmacisti");
	assert(m1.get_substanta_activa() == "nuj");
	assert(m1.get_pret() == 25);

	m1.set_denumire("Nurofen");
	m1.set_producator("Da");
	m1.set_substanta_activa("Paracetamol");
	m1.set_pret(35);

	assert(m1.get_denumire() == "Nurofen");
	assert(m1.get_producator() == "Da");
	assert(m1.get_substanta_activa() == "Paracetamol");
	assert(m1.get_pret() == 35);

}