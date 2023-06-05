#pragma once
#ifndef DATASTRUCTURE_H
#define DATASTRUTRE_H

#include <cstdlib>

#include "DateTime.h"
#include "Headers.h"#include "ICS0017DataSource.h"
#include "Items.h"
#include <vector>


class DataStructure
{

public:
	std::vector<HEADER_A*> arrayOfHeader;
	DataStructure() :arrayOfHeader(27, nullptr) {	};

};




#endif