#ifndef MAINITEMS_H_
#define MAINITEMS_H_

#include <vector>

class MainItems
{
public:
	void Add(int itemID, int itemQuality)
	{
		main.push_back(itemID);
		mainQuality.push_back(itemQuality);
	}
	void EraseToBegin(int erasePos)
	{
		main.erase(main.begin() + erasePos);
		mainQuality.erase(mainQuality.begin() + erasePos);
	}
	void EraseToEnd(int erasePos)
	{
		main.erase(main.end() - erasePos);
		mainQuality.erase(mainQuality.end() - erasePos);
	}
	void clear()
	{
		main.clear();
		mainQuality.clear();
	}
	size_t size() const
	{
		return main.size();
	}
	int item_back() const
	{
		return main.back();
	}
	int quality_back() const
	{
		return mainQuality.back();
	}
	std::vector<int> item_copy() const
	{
		return main;
	}
	std::vector<int> quality_copy() const
	{
		return mainQuality;
	}
	int get_item_element(int getPos) const
	{
		return main[getPos];
	}
	int get_quality_element(int getPos) const
	{
		return mainQuality[getPos];
	}

private:
	std::vector<int> main;
	std::vector<int> mainQuality;

};


#endif