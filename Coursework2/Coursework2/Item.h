#pragma once
#ifndef ITEM_9_H_
#define ITEM_9_H_

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string.h>
#include "headers/Items.h"
#include "headers/DateTime.h"

class Item {
	char* pID;
	unsigned long int Code;
	TIME* pTime;
	int pIDLen;

public:
	Item();
	Item(ITEM2* p);
	Item(Item& orig);
	Item(std::string pid, unsigned long int code, int hour, int min, int sec);
	~Item();
	char* GetItemID() const { return this->pID; }
	Item& operator=(const Item& right);
	bool operator==(const Item& other) const;
	void Write(std::ofstream& outFile);


	friend std::ostream& operator<<(std::ostream& ostr, const Item& str);
};

#endif // ITEM_9_H_
