// Coursework1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DateTime.h"
#include "Headers.h"
#include "ICS0017DataSource.h"
#include "Items.h"

#define ITEM_TYPE 2
#define ITEM_COUNT 90

typedef ITEM2 ITEM;

/*------------------------- printItem ------------------------- */
void PrintItemsInItemList(ITEM* items, int* count)
{
	while (items)
	{
		printf("%d) %s \t\t\t %lu \t\t\t %02d:%02d:%02d\n",
			*count, items->pID, items->Code, items->pTime->Hour, items->pTime->Min, items->pTime->Sec);

		items = items->pNext;
		++(*count);
	}
}

/* ------------------------- printDataStructure -------------------------*/

void PrintDataStructure(HEADER_A** arrayOfHeaders)
{
	//null check
	if (arrayOfHeaders == nullptr)
		throw "Null pointer exception!";

	int count = 1;
	for (int i = 0; i < 26; i++)
	{
		HEADER_A* headerNode = arrayOfHeaders[i];
		while (headerNode)
		{
			ITEM* items = (ITEM*)headerNode->pItems;
			PrintItemsInItemList(items, &count);
			headerNode = headerNode->pNext;
		}
	}
	return;

}

char* ReturnItemInitials(char* id)
{
	if (id && strlen(id)) {
		char* retChars = (char*)calloc(2, sizeof(char));
		if (retChars) {
			retChars[0] = id[0];
			retChars[1] = strchr(id, ' ')[1];
			return retChars;
		}
		else {
			throw "Callod failed! in Line 64";
		}
	}
	else {
		throw "Invalid Item ID";
	}
}

/*------------------------- FindMatchingItem -------------------------*/

void FindPositionAndInsert(ITEM* itemToInsert, HEADER_A** arrayOfHeaders)
{
	char* itemID = itemToInsert->pID;
	char* c = ReturnItemInitials(itemID);
	int i = (int)c[0] - 'A';

	HEADER_A* header = arrayOfHeaders[i];
	HEADER_A* headerNode = header;

	HEADER_A* newHeader = nullptr;
	newHeader = (HEADER_A*)calloc(1, sizeof(HEADER_A));
	newHeader->cBegin = c[1];
	newHeader->pItems = itemToInsert;
	newHeader->pNext = nullptr;
	itemToInsert->pNext = nullptr;

	//if no header exists with the starting character c0
	if (headerNode == nullptr)
	{
		arrayOfHeaders[i] = newHeader;
	}
	else
	{
		//check if there is a header->cBegin that matches the 2nd word	
		for (;headerNode->cBegin != c[1]; headerNode = headerNode->pNext)
		{
			//if no header with matching 2nd word found, add the item and return.
			if (headerNode->pNext == nullptr)
			{
				headerNode->pNext = newHeader;
				return;
			}
		}
		//if there is a node where 2nd letter matches itemToInserts 2nd letter
		if (headerNode)
		{
			ITEM* item = (ITEM*)headerNode->pItems;

			//check if there is an item with matching itemID
			for (;strcmp(itemID, item->pID) != 0; item = item->pNext)
			{
				if (item->pNext == nullptr)
				{
					item->pNext = itemToInsert;
					return;

				}

			}

			puts("Item already exists in the data structure!");
			free(newHeader);
			return;

		}

	}
}


/*------------------------- InsertItem -------------------------*/
HEADER_A** InsertItem(HEADER_A** arrayOfHeaders, char* newItemID = nullptr)
{
	ITEM* itemToInsert = (ITEM*)GetItem(ITEM_TYPE, newItemID);

	if (itemToInsert == nullptr) {
		throw "Illegal Item ID, aborting insertion!";
	}

	FindPositionAndInsert(itemToInsert, arrayOfHeaders);

	return arrayOfHeaders;
}


HEADER_A** RemoveItem(HEADER_A** arrayOfHeaders, char* itemID)
{
	char* c = ReturnItemInitials(itemID);
	unsigned int i = (int)c[0] - 'A';

	HEADER_A* header = arrayOfHeaders[i];
	HEADER_A* headerNode = header;
	HEADER_A* prevHeader = header;
	if (!headerNode) //is null
	{
		return NULL;
	}
	else
	{
		for (;headerNode->cBegin != c[1]; headerNode = headerNode->pNext) //as long as the characters dont match
		{
			prevHeader = headerNode;
			if (headerNode->pNext == nullptr)
				return NULL;
		}

		ITEM* item = (ITEM*)headerNode->pItems;
		ITEM* prevItem = nullptr;

		for (; strcmp(itemID, item->pID) != 0; item = item->pNext)
		{
			prevItem = item;
			if (item->pNext == nullptr)
				return NULL;
		}

		//if the first item is the one to be removed
		if (prevItem == nullptr)
		{
			//if its the only item in itemList
			if (item->pNext == nullptr)
			{
				//if header was the first item to be removed
				//if header was also the first header to be removed
				if (prevHeader == headerNode) {
					arrayOfHeaders[i] = headerNode->pNext;
					free(item);
					free(headerNode);
				}
				else {

					prevHeader->pNext = headerNode->pNext;
					free(item);
					free(headerNode);
				}
				//if headerwas the only node in headerList
				if (!header->pNext)
				{
					arrayOfHeaders[i] = nullptr;
				}


			}
			else
			{
				headerNode->pItems = item->pNext;
				free(item);
			}
		}
		else
		{
			prevItem->pNext = item->pNext; // bypass the item(which is to be removed)
			free(item); // free the item.
		}
	}

	return arrayOfHeaders;
}

/*------------------------- main ------------------------ - */
int main()
{
	std::cout << "Hello World!\n";
	HEADER_A** dataStructure = GetStruct3(ITEM_TYPE, ITEM_COUNT);;

	char test[][4] = {
		"W Z",
		"W A",
		"W K",
		"A Z",
		"A A",
		"A K",
		"Z A",
		"Z Z",
		"Z U"
	};

	try
	{
		// insert
		for (char* itemID : test) {
			HEADER_A** tmp = InsertItem(dataStructure, itemID);
			if (tmp) {
				dataStructure = tmp;
			}
			else {
				throw "Insertion failiure!";
			}
		}

		//remove inserted
		for (char* itemID : test) {
			HEADER_A** tmp = RemoveItem(dataStructure, itemID);
			if (tmp) {
				dataStructure = tmp;
			}
			else {
				throw "Remove failiure failiure!";
			}
		}

		//try double remove
		HEADER_A** tmp = RemoveItem(dataStructure, test[4]);
		if (!tmp) {
			std::cout << "could not remove item as it does not exist in datastructure!" << std::endl;
		}
	}
	catch (const char* e)
	{
		std::cout << e << std::endl;
	}

	PrintDataStructure(dataStructure);


}