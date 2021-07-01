#ifndef HANDLEITEMS_H_
#define HANDLEITEMS_H_

#include <vector>

class HandleItems
{
public:
	void Add(int itemID, int itemQuality)
	{
		handles.push_back(itemID);
		handlesQuality.push_back(itemQuality);
	}
	void EraseToBegin(int erasePos)
	{
		handles.erase(handles.begin() + erasePos);
		handlesQuality.erase(handlesQuality.begin() + erasePos);
	}
	void EraseToEnd(int erasePos)
	{
		handles.erase(handles.end() - erasePos);
		handlesQuality.erase(handlesQuality.end() - erasePos);
	}
	void clear()
	{
		handles.clear();
		handlesQuality.clear();
	}
	size_t size() const
	{
		return handles.size();
	}
	int item_back() const
	{
		return handles.back();
	}
	int quality_back() const
	{
		return handlesQuality.back();
	}
	std::vector<int> item_copy() const
	{
		return handles;
	}
	std::vector<int> quality_copy() const
	{
		return handlesQuality;
	}
	int get_item_element(int getPos) const
	{
		return handles[getPos];
	}
	int get_quality_element(int getPos) const
	{
		return handlesQuality[getPos];
	}

private:
	std::vector<int> handles;
	std::vector<int> handlesQuality;

};

#endif