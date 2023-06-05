#include "Item.h"
#include "headers/Headers.h"
#include "headers/ICS0017DataSource.h"
#include <cstring>
#include <cstdlib>
#include <string>

Item::Item() : pID(nullptr), Code(0), pTime(nullptr), pIDLen(0)
{
	ITEM2* tmp = (ITEM2*)GetItem(2, nullptr);

	this->pIDLen = strlen(tmp->pID);
	this->pID = new char[pIDLen + 1]{};
	memcpy(this->pID, tmp->pID, pIDLen + 1); //+1 to copy the null terminator

	this->Code = tmp->Code;

	this->pTime = new TIME();
	memcpy(this->pTime, tmp->pTime, sizeof(*pTime));

	free(tmp);
}

Item::Item(ITEM2* tmp) : pID(nullptr), Code(0), pTime(nullptr), pIDLen(0)
{
	if (!tmp) {
		throw "Cannot initalize item from null pointer!";
	}

	this->pIDLen = strlen(tmp->pID);

	this->pID = new char[pIDLen + 1]{};
	memcpy(pID, tmp->pID, pIDLen + 1); //+1 to copy the null terminator

	this->Code = tmp->Code;

	this->pTime = new TIME();
	memcpy(this->pTime, tmp->pTime, sizeof(*pTime));


	free(tmp);
}

Item::Item(Item& orig) : pID(nullptr), Code(0), pTime(nullptr), pIDLen(0)
{
	this->pIDLen = orig.pIDLen;

	this->pID = new char[pIDLen + 1]{};
	memcpy(pID, orig.pID, pIDLen + 1); //+1 to copy the null terminator

	this->Code = orig.Code;

	this->pTime = new TIME();
	memcpy(this->pTime, orig.pTime, sizeof(*pTime));

}

Item::~Item()
{
	delete[] pID;
	delete pTime;
}

Item::Item(std::string pid, unsigned long int code, int hour, int min, int sec)
{
	this->pIDLen = strlen(pid.c_str());
	this->pID = new char[pIDLen + 1]{};
	memcpy(this->pID, pid.c_str(), pIDLen + 1); //+1 to copy the null terminator;

	this->Code = code;

	this->pTime = new TIME();
	this->pTime->Hour = hour;
	this->pTime->Min = min;
	this->pTime->Sec = sec;
}


Item& Item::operator=(const Item& right)
{
	if (*this == right) {
		return *this;
	}

	delete this->pID;
	delete this->pTime;

	this->pIDLen = right.pIDLen;

	this->pID = new char[pIDLen + 1]{};
	memcpy(pID, right.pID, pIDLen + 1); //+1 to copy the null terminator

	this->Code = right.Code;

	this->pTime = new TIME();
	memcpy(this->pTime, right.pTime, sizeof(*pTime));

	return *this;
}

bool Item::operator==(const Item& other) const
{
	return this->Code == other.Code && !strcmp(this->pID, other.pID) && !memcmp(this->pTime, other.pTime, sizeof(*pTime));
}

void Item::Write(std::ofstream& outFile)
{
	outFile << this->pID << ";" << this->Code << ";"
		<< this->pTime->Hour << ";" << this->pTime->Min << ";" << this->pTime->Sec << ";" << std::endl;
}

std::ostream& operator<<(std::ostream& ostr, const Item& str)
{
	ostr << str.pID << " " << str.Code << " "
		<< str.pTime->Hour << ":" << str.pTime->Min << ":" << str.pTime->Sec << std::endl;
	return ostr;
}
