#ifndef WEAPON_H_
#define WEAPON_H_

#include <vector>

class Weapon
{
public:
	void Add(int itemID, int itemQuality)
	{
		weapons.push_back(itemID);
		weaponsQuality.push_back(itemQuality);
	}
	void EraseToBegin(int erasePos)
	{
		weapons.erase(weapons.begin() + erasePos);
		weaponsQuality.erase(weaponsQuality.begin() + erasePos);
	}
	void EraseToEnd(int erasePos)
	{
		weapons.erase(weapons.end() - erasePos);
		weaponsQuality.erase(weaponsQuality.end() - erasePos);
	}
	void clear()
	{
		weapons.clear();
		weaponsQuality.clear();
	}
	void resize(int size)
	{
		weapons.resize(size);
		weaponsQuality.resize(size);
	}
	size_t size() const
	{
		return weapons.size();
	}
	int item_back() const
	{
		return weapons.back();
	}
	int quality_back() const
	{
		return weaponsQuality.back();
	}
	std::vector<int> item_copy() const
	{
		return weapons;
	}
	std::vector<int> quality_copy() const
	{
		return weaponsQuality;
	}
	int get_item_element(int getPos) const
	{
		return weapons[getPos];
	}
	int get_quality_element(int getPos) const
	{
		return weaponsQuality[getPos];
	}

private:
	std::vector<int> weapons;
	std::vector<int> weaponsQuality;

};

#endif