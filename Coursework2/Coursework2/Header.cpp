#include "Header.h"
#include <algorithm>

Header::Header() : items(), cBegin(0)
{
}

Header::Header(Header& orig) : items(), cBegin(orig.cBegin)
{

	for (Item* i : orig.items)
	{
		Item* cpy = (i) ? new Item(*i) : nullptr;
		items.push_back(cpy);
	}
}

Header::~Header()
{
	for (Item* i : items)
	{
		delete i;
	}

}

int Header::GetItemsNumber() const
{
	return items.size();
}

Item* Header::GetItem(const char* pID) const
{
	if (pID && strlen(pID))
	{
		const char* tmp = strchr(pID, ' ');
		if (!tmp)
		{
			throw std::runtime_error("Invalid item ID");
		}

		char _2 = tmp[1];
		if (this->cBegin != _2)
		{
			return nullptr;
		}

		auto return_iterator = std::find_if(items.cbegin(),
			items.cend(),
			[pID](Item* i) {
				return !strcmp(i->GetItemID(), pID);
			}
		);

		if (return_iterator != items.cend())
		{
			return *return_iterator;
		}
	}
	return nullptr;
}

void Header::operator+=(Item* i)
{
	char* pID = i->GetItemID();
	if (this->GetItem(pID))
	{
		throw std::runtime_error("Item already exists");
	}

	char _2 = strchr(pID, ' ')[1];
	if (this->cBegin != _2)
	{
		this->cBegin = _2;
	}

	this->items.push_back(i);
}

void Header::operator-=(const char* pID)
{
	if (!this->GetItem(pID))
	{
		throw std::runtime_error("Item does not exist");
	}

	this->items.remove_if(
		[pID](Item* i) {
			return !strcmp(i->GetItemID(), pID);
		}
	);

	if (items.size() == 0) {
		this->cBegin = 0;
	}

}

Header& Header::operator=(const Header& right)
{
	if (*this == right) {
		return *this;
	}

	for (Item* i : items)
	{
		delete i;
	}

	for (Item* i : right.items)
	{
		Item* cpy = (i) ? new Item(*i) : nullptr;
		items.push_back(cpy);
	}

	return *this;
}

bool Header::operator==(const Header& other) const
{
	if (this->GetItemsNumber() == other.GetItemsNumber()) {
		return std::equal(this->items.cbegin(),
			this->items.cend(),
			other.items.cbegin(),
			[](Item* i1, Item* i2) {
				return *i1 == *i2;
			}
		);
	}
	return false;
}

void Header::Write(std::ofstream& outFile)
{
	for (Item* i : this->items)
	{
		i->Write(outFile);
	}
}

std::ostream& operator<<(std::ostream& ostr, const Header& str)
{
	for (Item* i : str.items)
	{
		ostr << *i;
	}
	ostr << std::endl;
	return ostr;
}
