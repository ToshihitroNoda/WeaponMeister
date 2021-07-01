#ifndef POUCH_H_
#define POUCH_H_

#include <vector>

class Pouch
{
public:
	void Add(int itemID, int itemQuality)
	{
		pouch.push_back(itemID);
		pouchQuality.push_back(itemQuality);
	}
	void EraseToBegin(int erasePos)
	{
		pouch.erase(pouch.begin() + erasePos);
		pouchQuality.erase(pouchQuality.begin() + erasePos);
	}
	void EraseToEnd(int erasePos)
	{
		pouch.erase(pouch.end() - erasePos);
		pouchQuality.erase(pouchQuality.end() - erasePos);
	}
	void clear()
	{
		pouch.clear();
		pouchQuality.clear();
	}
	void resize(int size)
	{
		pouch.resize(size);
		pouchQuality.resize(size);
	}
	size_t size() const
	{
		return pouch.size();
	}
	int item_back() const
	{
		return pouch.back();
	}
	int quality_back() const
	{
		return pouchQuality.back();
	}
	std::vector<int> item_copy() const
	{
		return pouch;
	}
	std::vector<int> quality_copy() const
	{
		return pouchQuality;
	}
	int get_item_element(int getPos) const
	{
		return pouch[getPos];
	}
	int get_quality_element(int getPos) const
	{
		return pouchQuality[getPos];
	}

private:
	std::vector<int> pouch;
	std::vector<int> pouchQuality;
};



#endif