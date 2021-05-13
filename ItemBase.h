#ifndef ITEMBASE_H_
#define ITEMBASE_H_

#include "Image.h"

class ItemBase
{
public:
	int imageHandle;
	int quality;

	ItemBase() 
	{
		quality = 0;
		imageHandle = -1;
	};

	virtual ~ItemBase() {};

};

#endif

