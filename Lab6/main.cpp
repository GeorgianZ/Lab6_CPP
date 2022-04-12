#include "UI.h"
#include <iostream>
using std::cout;

void test_all();

int main()
{
	Repo repo;
	Validate val;
	Service serv{ repo, val };
	Console consola{ serv };
	test_all();
	consola.run();
}

void test_all()
{
	cout << "Start tests!\n";
	test_domain();
	test_repoExp();
	test_repo();
	test_add_service();
	test_sterge_service();
	test_modifica_service();
	test_find();
	test_filter_pret();
	test_filter_sub();
	test_sort();
	test_reteta();
	test_map();
	cout << "Finish tests!\n";
}