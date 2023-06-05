#pragma once
#ifndef HEADER_A_
#define HEADER_A_

#include "Item.h"
#include "headers/Headers.h"
#include <list>
#include <fstream>


class Header
{
	std::list<Item*> items;
	char cBegin; //First letter of second word of item->id;

public:


	Header();
	Header(Header& orig);
	~Header();

	char GetCBegin() const { return this->cBegin; }
	int GetItemsNumber () const;
	Item* GetItem(const char* pID) const;
	void operator+=(Item* i);
	void operator-=(const char* pID);
	Header& operator=(const Header& right);
	bool operator==(const Header& Other) const;
	void Write(std::ofstream& outFile);

	friend std::ostream& operator<<(std::ostream& ostr, const Header& str);

};

#endif // !HEADER_A
