//#include "Map.h"
//#include <assert.h>
//
//void Mapare::createMap() {
//	vector<Medicament> v = repo.get_all();
//	for (auto x : v) {
//		map[x.get_substanta_activa()] = 0;
//	}
//	for (auto x : v) {
//		map[x.get_substanta_activa()]++;
//	}
//}
//
//unordered_map<string, int> Mapare::getMap() {
//	return map;
//}
//
//void test_map() {
//	Repo repo;
//	Medicament m1{ "da", "ceva", "s1", 100 };
//	Medicament m2{ "nu", "altceva", "s1", 100 };
//	Medicament m3{ "chestie", "nuj", "s2", 100 };
//	Medicament m4{ "pastile", "oameni", "s2", 100 };
//	Medicament m5{ "nebunie", "lucru", "s2", 100 };
//	Medicament m6{ "ceva", "asa", "s3", 100 };
//	Mapare m;
//	m.createMap();
//	unordered_map<string, int> map = m.getMap();
//	assert(map["s1"] == 2);
//	assert(map["s2"] == 3);
//	assert(map["s3"] == 1);
//}