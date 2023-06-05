#pragma once
#ifndef DATASTRUCTURE_H
#define DATASTRUTRE_H


#include "Header.h"
#include <array>
#include <list>


class DataStructure
{
private:
	const static int HEADER_COUNT = 26;
public:
	std::array<std::list<Header*>, HEADER_COUNT> headers;
	DataStructure();
	DataStructure(DataStructure& orig);
	DataStructure(const char* pFilename);
	~DataStructure();
	
	int GetItemsNumber() const;
	Item* GetItem(const char* pID) const;
	void Write(const char* pFilename);
	void operator+=(ITEM2* item);
	void operator+=(Item* i);
	void operator-=(const char* pID);
	DataStructure& operator=(const DataStructure& Right);
	bool operator==(const DataStructure& other) const;

	friend std::ostream& operator<<(std::ostream& ostr, const DataStructure& str);


};




#endif