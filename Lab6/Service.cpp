#pragma once
#include "Service.h"
#include <assert.h>
#include <iostream>
#include <algorithm>
using std::cout;
void Service::adauga(string denumire, string producator, string substanta_activa, double pret) {
	Medicament m{ denumire, producator, substanta_activa, pret };
	string err = val.valideaza(m);
	if (err.size() > 0)
		throw ValidationException(err);
	repo.add(m);
}

const vector<Medicament>& Service::get_all() {
	return repo.get_all();
}

void Service::sterge(string denumire, string producator) {
	string subs_act = "subs";
	double pret = 1;
	Medicament m{ denumire, producator, subs_act, pret };
	repo.delete_medicine(m);
}


void Service::modifica(string denumire, string producator, string substanta_activa, double pret)
{
	Medicament m{ denumire, producator, substanta_activa, pret };
	string err = val.valideaza(m);
	if (err.size() > 0)
		throw ValidationException(err);
	repo.modify(m);
}

const Medicament& Service::find(string denumire, string producator) {
	return repo.find_medicine(denumire, producator);
}

const vector<Medicament> Service::filter_pret(double pret) {
	vector<Medicament> v;
	for (auto m : get_all())
		if (m.get_pret() > pret)
			v.push_back(m);
	if (v.size() == 0)
		throw RepoException("Nu exista medicamente cu pretul mai mare decat cel dat!\n");
	return v;
}

const vector<Medicament> Service::filter_sub(string subs_act) {
	vector<Medicament> v;
	for (auto m : get_all())
		if (m.get_substanta_activa() == subs_act)
			v.push_back(m);
	if (v.size() == 0)
		throw RepoException("Nu exista medicamente cu aceasta substanta activa!\n");
	return v;
}

const vector<Medicament> Service::sort_by_denumire() {
	vector <Medicament> sorted;
	sorted = get_all();
	int g = 0;
	do {
		g = 0;
		for(int i=0;i<sorted.size()-1;i++)
			if (sorted[i].get_denumire() > sorted[i + 1].get_denumire()) {
				auto aux = sorted[i];
				sorted[i] = sorted[i + 1];
				sorted[i + 1] = aux;
				g = 1;
			}
	} while (g == 1);
	return sorted;
}

const vector<Medicament> Service::sort_by_subAndPrice() {
	vector <Medicament> sorted;
	sorted = get_all();
	int g = 0;
	do {
		g = 0;
		for (int i = 0; i < sorted.size() - 1; i++) {
			if (sorted[i].get_substanta_activa() > sorted[i + 1].get_substanta_activa()) {
				auto aux = sorted[i];
				sorted[i] = sorted[i + 1];
				sorted[i + 1] = aux;
				g = 1;
			}
			if (sorted[i].get_substanta_activa() == sorted[i + 1].get_substanta_activa())
				if (sorted[i].get_pret() > sorted[i + 1].get_pret()) {
					auto aux = sorted[i];
					sorted[i] = sorted[i + 1];
					sorted[i + 1] = aux;
					g = 1;
				}
		}
	} while (g == 1);
	return sorted;
}

const vector<Medicament> Service::sort_by_producator() {
	vector <Medicament> sorted;
	sorted = get_all();
	int g = 0;
	do {
		g = 0;
		for (int i = 0; i < sorted.size() - 1; i++)
			if (sorted[i].get_producator() > sorted[i + 1].get_producator()) {
				auto aux = sorted[i];
				sorted[i] = sorted[i + 1];
				sorted[i + 1] = aux;
				g = 1;
			}
	} while (g == 1);
	return sorted;
}


void test_add_service()
{
	Repo repo;
	Validate val;
	Service serv{ repo, val };
	serv.adauga("Paracetamol", "Farmacisti", "nuj", 25);
	serv.adauga("Ceva", "Baieti", "subs", 456);
	assert(serv.get_all().size() == 2);
	try {
		serv.adauga("Paracetamol", "Farmacisti", "nuj", 25);
	}
	catch (RepoException& re) {
		assert(re.get_errorMsg() == "Medicamentul exista deja in lista!\n");
	}
	try {
		serv.adauga("", "dap", "ceva", 25);
	}
	catch (ValidationException& ve) {
		assert(ve.get_error() == "Medicamentul are o denumire invalida!\n");
	}
}

void test_sterge_service()
{
	Repo repo;
	Validate val;
	Service serv{ repo, val };
	serv.adauga("Paracetamol", "Farmacisti", "nuj", 25);
	serv.adauga("Ceva", "Baieti", "subs", 456);
	serv.sterge("Paracetamol", "Farmacisti");
	assert(serv.get_all().size() == 1);
	try {
		serv.sterge("Paracetamol", "Farmacisti");
	}
	catch (RepoException&) {
		assert(true);
	}
}

void test_modifica_service() {
	Repo repo;
	Validate val;
	Service serv{ repo, val };
	serv.adauga("Paracetamol", "Farmacisti", "nuj", 25);
	serv.adauga("Ceva", "Baieti", "subs", 456);
	serv.modifica("Paracetamol", "oameni", "da", 35);
	assert(serv.get_all()[0].get_denumire() == "Paracetamol");
	assert(serv.get_all()[0].get_producator() == "oameni");
	assert(serv.get_all()[0].get_substanta_activa() == "da");
	assert(serv.get_all()[0].get_pret() == 35);
	
	try{
		serv.modifica("Ceva", "Baieti", "subs", 456);
	}
	catch (RepoException& re) {
		assert(re.get_errorMsg() == "Medicamentul exista deja in lista!\n");
	}

	try {
		serv.modifica("Dap", "ceva", "subs", 456);
	}
	catch (RepoException& re) {
		assert(re.get_errorMsg() == "Medicamentul cu denumirea data nu exista in lista!\n");
	}
	try {
		serv.modifica("Ceva", "", "", 45);
	}
	catch (ValidationException& ve) {
		assert(ve.get_error() == "Medicamentul are un producator invalid!\nMedicamentul are o substanta activa invalida!\n");
	}
}

void test_find()
{
	Repo repo;
	Validate val;
	Service serv{ repo, val };
	serv.adauga("Paracetamol", "Farmacisti", "nuj", 25);
	serv.adauga("Ceva", "Baieti", "subs", 456);
	auto m = serv.find("Paracetamol", "Farmacisti");
	assert(m.get_substanta_activa() == "nuj");
	assert(m.get_pret() == 25);
}
void test_filter_pret()
{
	Repo repo;
	Validate val;
	Service serv{ repo, val };
	serv.adauga("Paracetamol", "Farmacisti", "nuj", 25);
	serv.adauga("Ceva", "Baieti", "subs", 456);
	serv.adauga("da", "nu", "fdsfs", 401);
	assert(serv.filter_pret(400).size() == 2);
	try {
		serv.filter_pret(500);
	}
	catch (RepoException& re) {
		assert(re.get_errorMsg() == "Nu exista medicamente cu pretul mai mare decat cel dat!\n");
	}
}

void test_filter_sub()
{
	Repo repo;
	Validate val;
	Service serv{ repo, val };
	serv.adauga("Paracetamol", "Farmacisti", "da", 25);
	serv.adauga("Ceva", "Baieti", "da", 456);
	serv.adauga("da", "nu", "fdsfs", 401);
	assert(serv.filter_sub("da").size() == 2);
	try {
		serv.filter_sub("fdg");
	}
	catch (RepoException& re) {
		assert(re.get_errorMsg() == "Nu exista medicamente cu aceasta substanta activa!\n");
	}
}

void test_sort()
{
	Repo repo;
	Validate val;
	Service serv{ repo, val };
	serv.adauga("v", "nu", "fdsfs", 401);
	serv.adauga("da", "Farmacisti", "da", 345);
	serv.adauga("ceva", "Baieti", "da", 45);
	
	auto v = serv.sort_by_denumire();
	assert(v.size() == 3);
	assert(v[0].get_denumire() == "ceva");
	assert(v[1].get_denumire() == "da");
	assert(v[2].get_denumire() == "v");
	
	v = serv.sort_by_producator();
	assert(v[0].get_producator() == "Baieti");
	assert(v[1].get_producator() == "Farmacisti");
	assert(v[2].get_producator() == "nu");

	v = serv.sort_by_subAndPrice();
	assert(v[0].get_pret() == 45);
	assert(v[1].get_pret() == 345);
	assert(v[2].get_pret() == 401);
}
