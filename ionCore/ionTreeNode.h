
#pragma once

#include <set>


template <typename Implementation>
class ITreeNode
{

	static_assert(std::is_base_of<ITreeNode<Implementation>, Implementation>, "ITreeNode<Implementation> must be a base of implementation type.");

public:

	Implementation const * const GetParent() const
	{
		return Parent;
	}

	std::set<Implementation *> const & GetChildren() const
	{
		return Children;
	}

	void AddChild(Implementation * child)
	{
		child->SetParent(this);
	}

	void RemoveChild(Implementation * child)
	{
		child->SetParent(0);
	}

	void SetParent(Implementation * parent)
	{
		if (Parent)
			Parent->Children.erase(this);
		
		Parent = parent;

		if (Parent)
			Parent->Children.insert(this);
	}

	void RemoveAllChildren()
	{
		for (auto Child : Children)
			Child->Parent = 0;
		Children.clear();
	}

protected:

	Implementation * Parent;
	std::set<Implementation *> Children;

};
