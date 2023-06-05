#include <iostream>

#include "Item.h"
#include "Header.h"
#include "DataStrcuture.h"
#include "headers/ICS0017DataSource.h";

int main()
{
	DataStructure d;
	
	for (int i = 0; i < 10; i++)
	{
		d += (ITEM2*)GetItem(2, nullptr);
	}

	std::cout << d << std::endl;
	std::cout << "Number of items: " << d.GetItemsNumber() << std::endl;
	
	Item* i = d.GetItem("Light Cyan");
	if (i) {
		std::cout << *i;
	}

	i = d.GetItem("X X");
	if (!i) {
		std::cout << "Item does not exist\n";
	}

	DataStructure d1 = d;

	d -= "Banana Mania";
	d -= "Persian Green";
	d -= "Vegas Gold";
	
	std::cout << ((d == d1) ? "Equal" : "Not Equal") << std::endl;

	const char* f = "lol.txt";
	d.Write(f);
	DataStructure d2(f);
	
	std::cout << d << std::endl;
	std::cout << d2 << std::endl;

	std::cout << ((d == d2) ? "Equal" : "Not Equal") << std::endl;

	d2 = d1;

	std::cout << d2 << std::endl;
	std::cout << d1 << std::endl;

	std::cout << ((d1 == d2) ? "Equal" : "Not Equal") << std::endl;


}
