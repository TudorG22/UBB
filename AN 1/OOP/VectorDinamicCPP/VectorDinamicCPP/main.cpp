#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "Pet.h"
#include "../../Lab6-7/include/vector_dinamic.h"
#include "../../Lab6-7/src/vector_dinamic.cpp"
#include <assert.h>
#include <vector>

class LabVectorAdapter {
private:
	VectorDinamic<Pet>* vec = nullptr;
public:
	LabVectorAdapter() : vec{ new VectorDinamic<Pet> } {}

	LabVectorAdapter(const LabVectorAdapter& other) : vec{ new VectorDinamic<Pet>{ *other.vec } } {}

	LabVectorAdapter(LabVectorAdapter&& other) noexcept : vec{ other.vec } {
		other.vec = nullptr;
	}

	LabVectorAdapter& operator=(const LabVectorAdapter& other) {
		if (this == &other) {
			return *this;
		}
		delete vec;
		vec = new VectorDinamic<Pet>{ *other.vec };
		return *this;
	}

	LabVectorAdapter& operator=(LabVectorAdapter&& other) noexcept {
		if (this == &other) {
			return *this;
		}
		delete vec;
		vec = other.vec;
		other.vec = nullptr;
		return *this;
	}

	~LabVectorAdapter() {
		delete vec;
	}

	void add(const Pet& el) {
		vec->push_back(el);
	}

	Pet& get(int poz) const {
		return vec->get(poz);
	}

	int size() const noexcept {
		return static_cast<int>(vec->size());
	}

	Pet* begin() {
		return vec->begin();
	}

	const Pet* begin() const {
		return vec->begin();
	}

	Pet* end() {
		return vec->end();
	}

	const Pet* end() const {
		return vec->end();
	}
};

/*
  Functie folosit in teste
  primeste vector prin valoare -> copy constructor
  returneaza prin valoare -> copy constructor sau move constructor
*/
template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
	double totalPrice = 0;
	for (auto el : v) {
		totalPrice += el.getPrice();
	}
	Pet p{ "total","tt",totalPrice };
	v.add(p);
	return v;
}

template <typename MyVector>
void addPets(MyVector& v, int cate) {
	for (int i = 0; i<cate; i++) {
		Pet p{ std::to_string(i) + "_type",std::to_string(i) + "_spec",i + 10.0 };
		v.add(p);
	}
}

/*
Testare constructori / assignment
E template pentru a refolosi la diferite variante de VectorDinamic din proiect
*/
template <typename MyVector>
void testCreateCopyAssign() {
	MyVector v;//default constructor
	addPets(v, 100);
	assert(v.size() == 100);
	assert(v.get(50).getType() == "50_type");

	MyVector v2{ v };//constructor de copiere
	assert(v2.size() == 100);
	assert(v2.get(50).getType() == "50_type");

	MyVector v3;//default constructor
	v3 = v;//operator=   assignment
	assert(v3.size() == 100);
	assert(v3.get(50).getType() == "50_type");

	auto v4 = testCopyIterate(v3);
	assert(v4.size() == 101);
	assert(v4.get(50).getType() == "50_type");
}

/*
  Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
	std::vector<MyVector> v;
	//adaugam un vector care este o variabila temporara
	//se v-a apela move constructor
	v.push_back(MyVector{});

	//inseram, la fel se apeleaza move costructor de la vectorul nostru
	v.insert(v.begin(),MyVector{});

	assert(v.size() == 2);

	MyVector v2;
	addPets(v2, 50);

	v2 = MyVector{};//move assignment

	assert(v2.size() == 0);

}
template <typename MyVector>
void testAll() {
	testCreateCopyAssign<MyVector>();
	testMoveConstrAssgnment<MyVector>();
}

int main() {
	testAll<LabVectorAdapter>();

#ifdef _MSC_VER
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}
