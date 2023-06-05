#include "DataStrcuture.h"
#include "Item.h"
#include <string>

#define NUMBER_OF_HEADERS 26
//default constructor
DataStructure::DataStructure() : headers() { };

//default destructor
DataStructure::~DataStructure()
{
	for (int i = 0; i < HEADER_COUNT; i++)
	{
		std::list<Header*>& headerList = this->headers[i];
		for (Header* h : headerList)
		{
			delete h;
		}
		headerList.clear();
	}
}

DataStructure::DataStructure(const char* pFilename)
{
	std::ifstream inFile(pFilename);
	while (!inFile.eof())
	{
		std::string pid;
		unsigned long int code;
		int hour, min, sec;
		char c;
		std::getline(inFile, pid, ';');
		inFile >> code >> c >> hour >> c >> min >> c >> sec >> c;
		c = inFile.get();
		Item* i = new Item(pid, code, hour, min, sec);
		*this += i;
	}
}

//Copy constructor
DataStructure::DataStructure(DataStructure& orig) : headers()
{
	//initalize datastructure vector with 26 headers
	for (int i = 0; i < HEADER_COUNT; i++)
	{
		std::list<Header*> headerList = orig.headers[i];

		for (Header* h : headerList)
		{
			Header* cpy = (h ? new Header(*h) : nullptr);
			this->headers[i].push_back(cpy);
		}

	}

}

int DataStructure::GetItemsNumber() const
{
	int count = 0;
	for (std::list<Header*> h : headers)
	{
		for (Header* i : h)
		{
			count += i->GetItemsNumber();
		}
	}

	return count;
}

Item* DataStructure::GetItem(const char* pID) const
{
	if (pID && strlen(pID)) {
		char _1 = pID[0];
		int idx = _1 - 'A';
		Item* item = nullptr;

		std::list<Header*> headerList = headers[idx];
		for (Header* header : headerList)
		{
			item = header->GetItem(pID);
			if (item) {
				return item;
			}
		}

		return nullptr;

	}
	else {
		throw std::runtime_error("Invalid item ID");
	}
}

void DataStructure::Write(const char* pFilename)
{
	std::ofstream outFile(pFilename);

	for (int i = 0; i < NUMBER_OF_HEADERS; i++)
	{
		std::list<Header*> headerList = this->headers[i];

		for (Header* h : headerList)
		{
			h->Write(outFile);
		}
	}
}

void DataStructure::operator+=(Item* i)
{
	char* pID = i->GetItemID();

	if (pID && strlen(pID)) {
		const char* tmp = strchr(pID, ' ');
		if (!tmp) 
		{
			throw std::runtime_error("Invalid Item ID");
		}

		char _1 = pID[0];
		char _2 = tmp[1];
		int idx = _1 - 'A';
		bool existing = false;
		std::list<Header*>& headerList = this->headers[idx];

		for (Header* header : headerList)
		{
			if (header->GetCBegin() == _2)
			{
				*header += i;
				return;
			}
		}


		Header* newHeader = new Header();
		*newHeader += i;
		auto beg = headerList.begin();
		auto end = headerList.end();

		while (beg != end && (*beg)->GetCBegin() < _2)
		{
			beg++;
		}

		if (beg == end)
		{
			headerList.push_back(newHeader);
		}
		else
		{
			headerList.insert(beg, newHeader);
		}


	}
}

void DataStructure::operator-=(const char* pID)
{
	if (pID && strlen(pID)) 
	{
		const char* tmp = strchr(pID, ' ');
		if (!tmp) 
		{
			throw std::runtime_error("Invalid Item ID");
		}

		char _1 = pID[0];
		char _2 = tmp[1];
		int idx = _1 - 'A';

		std::list<Header*>& headerList = this->headers[idx];

		for (Header* header : headerList)
		{
			if (header->GetCBegin() == _2)
			{
				*header -= pID;
			}
		}
		headerList.remove_if([](Header* h) {
			return !h->GetItemsNumber();
		});

	}
}


DataStructure& DataStructure::operator=(const DataStructure& right)
{
	if (*this == right)
	{
		return *this;
	}

	for (int i = 0; i < HEADER_COUNT; i++)
	{
		std::list<Header*>& headerList = this->headers[i];
		for (Header* h : headerList)
		{
			delete h;
		}
		headerList.clear();
	}

	for (int i = 0; i < HEADER_COUNT; i++)
	{
		std::list<Header*> headerList = right.headers[i];
		
		for (Header* h : headerList)
		{
			Header* cpy = (h ? new Header(*h) : nullptr);
			this->headers[i].push_back(cpy);
		}
	}

	return *this;
}



bool DataStructure::operator==(const DataStructure& other) const
{
	bool res = false;
	if (this->GetItemsNumber() != other.GetItemsNumber()) {
		return false;
	}

	for (int i = 0; i < NUMBER_OF_HEADERS; i++)
	{
		std::list<Header*> thisHeaderList = this->headers[i];
		std::list<Header*> otherHeaderList = other.headers[i];
		if (thisHeaderList.size() == otherHeaderList.size()) {
			res = std::equal(thisHeaderList.cbegin(),
				thisHeaderList.cend(),
				otherHeaderList.cbegin(),
				[](Header* h1, Header* h2) {
					return *h1 == *h2;
				}
			);

			if (!res) {
				return false;
			}
		}
		else {
			return false;
		}
	}

	return true;
}

void DataStructure::operator+=(ITEM2* item)
{
	Item* i = new Item(item);
	*this += i;
}


std::ostream& operator<<(std::ostream& ostr, const DataStructure& str)
{
	for (std::list<Header*> headerList : str.headers)
	{
		for (Header* h : headerList)
		{
			ostr << *h;
		}
	}
	return ostr;
}
