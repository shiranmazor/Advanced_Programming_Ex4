//#pragma once
//#include <iostream>
//#include <vector>
//#include <map>
//#include <cassert>
//#include <cctype>
//using namespace std;
//
//
//typedef std::vector<int> coord;
//typedef std::vector<coord> coordGroup;
//typedef std::vector<coordGroup> matchingGroups;
//
//
//bool isCoordNear(coord c1, coord c2)
//{
//	bool diffOccured = false;
//	assert(c1.size() == c2.size());
//
//	for (size_t i = 0; i < c1.size(); i++)
//	{
//		if (abs(c1[i] - c2[i]) == 1)
//		{
//			if (diffOccured)
//			{
//				return false;
//			}
//			diffOccured = true;
//		}
//		else if (abs(c1[i] - c2[i]) > 1)
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//
//void compareAndUpdateVectors(vector<int> &toUpdate, vector<int> from)
//{
//	for (auto i = 0; i < from.size(); i++)
//	{
//		if (i < toUpdate.size())
//		{
//			toUpdate[i] = (toUpdate[i] > from[i]) ? toUpdate[i] : from[i];
//		}
//		else
//		{
//			toUpdate.push_back(from[i]);
//		}
//	}
//}
//
//
//template<class T, size_t DIMENSIONS>
//class Matrix
//{
//	typedef Matrix<T, DIMENSIONS - 1> itemType;
//	std::vector<itemType> _elements;
//
//	vector<int> lengths()
//	{
//		vector<int> allLengths;
//
//		for (auto &child : _elements)
//		{
//			compareAndUpdateVectors(allLengths, child.lengths());
//		}
//
//		allLengths.push_back(_elements.size());
//
//		return allLengths;
//	}
//
//
//	void resize(vector<int> newSizes)
//	{
//		for (auto i = _elements.size(); i < newSizes.back(); i++)
//		{
//			_elements.push_back(itemType());
//		}
//
//		newSizes.pop_back();
//
//		for (auto &elem : _elements)
//		{
//			elem.resize(newSizes);
//		}
//
//	}
//
//public:
//	itemType& operator[](int idx)
//	{
//		return _elements[idx];
//	}
//
//	const itemType& operator[](int idx) const
//	{
//		return _elements[idx];
//	}
//
//
//	Matrix(std::initializer_list<itemType> other)
//	{
//		_elements.insert(_elements.begin(), other.begin(), other.end());
//
//		vector<int> maxDims;
//		for (itemType &elem : _elements)
//		{
//			compareAndUpdateVectors(maxDims, elem.lengths());
//		}
//
//		for (itemType &elem : _elements)
//		{
//			elem.resize(maxDims);
//		}
//	}
//
//	Matrix() : Matrix(std::initializer_list<itemType>())
//	{
//	}
//
//	template<class Func, class Group = typename std::result_of<Func(T)>::type>
//	std::vector<pair<Group, coordGroup>> groupByLambda(Func f)
//	{
//		std::vector<pair<Group, coordGroup>> result;
//		std::map<Group, coordGroup> tmpResult;
//
//		for (auto i = 0; i < _elements.size(); i++)
//		{
//			std::vector<pair<Group, coordGroup>> cordResult = _elements[i].groupByLambda(f);
//			for (auto &elem : cordResult)
//			{
//				for (auto &coord : elem.second)
//				{
//					coord.insert(coord.begin(), i);
//					tmpResult[elem.first].push_back(coord);
//				}
//			}
//		}
//
//		for (auto const &ent : tmpResult)
//		{
//			result.push_back(pair<Group, coordGroup>(ent.first, ent.second));
//		}
//
//		return result;
//	}
//
//	template<class Func, class Group = typename std::result_of<Func(T)>::type>
//	std::vector<pair<Group, matchingGroups>> groupValues(Func f)
//	{
//
//		std::vector<pair<Group, matchingGroups>> result;
//		std::vector<pair<Group, coordGroup>> lambdaResults = groupByLambda(f);
//		for (auto &tup : lambdaResults)
//		{
//			Group group = tup.first;
//			coordGroup g_gag = tup.second;
//			matchingGroups mg;
//			while (g_gag.size() > 0)
//			{
//				coordGroup gi;
//				auto last_gi_size = gi.size();
//				while (true)
//				{
//					coordGroup::iterator it = g_gag.begin();
//					while (it != g_gag.end())
//					{
//						bool inserted = false;
//						if (gi.size() == 0)
//						{
//							gi.push_back(*it);
//							it = g_gag.erase(it);
//							inserted = true;
//						}
//						else
//						{
//							for (auto &elem : gi)
//							{
//								if (isCoordNear(*it, elem))
//								{
//									gi.push_back(*it);
//									it = g_gag.erase(it);
//									inserted = true;
//									break;
//								}
//							}
//						}
//						if (!inserted)
//						{
//							++it;
//						}
//					}
//
//					if (gi.size() == last_gi_size)
//					{
//						break;
//					}
//
//					last_gi_size = gi.size();
//				}
//				mg.push_back(gi);
//			}
//			result.push_back(pair<Group, matchingGroups>(group, mg));
//		}
//		return result;
//	}
//
//	friend class Matrix<T, DIMENSIONS + 1>;
//};
//
//
//template<class T>
//class Matrix<T, 1>
//{
//	typedef T itemType;
//	std::vector<itemType> _elements;
//
//	vector<int> lengths()
//	{
//		vector<int> allLengths;
//		allLengths.push_back(_elements.size());
//
//		return allLengths;
//	}
//
//
//	void resize(vector<int> newSizes)
//	{
//		for (auto i = _elements.size(); i < newSizes.back(); i++)
//		{
//			_elements.push_back(itemType());
//		}
//	}
//
//public:
//	itemType& operator[](int idx)
//	{
//		return _elements[idx];
//	}
//
//	const itemType& operator[](int idx) const
//	{
//		return _elements[idx];
//	}
//
//	Matrix(std::initializer_list<T> other)
//	{
//		_elements.insert(_elements.begin(), other.begin(), other.end());
//	}
//
//	Matrix() : Matrix(std::initializer_list<T>()) {}
//
//	template<class Func, class Group = typename std::result_of<Func(T)>::type>
//	std::vector<pair<Group, coordGroup>> groupByLambda(Func f)
//	{
//		std::vector<pair<Group, coordGroup>> result;
//		std::map<Group, coordGroup> tmpResult;
//
//		for (auto i = 0; i < _elements.size(); i++)
//		{
//			Group resF = f(_elements[i]);
//			coord resV = { i };
//			tmpResult[resF].push_back(resV);
//		}
//
//		for (auto const &ent : tmpResult)
//		{
//			result.push_back(pair<Group, coordGroup>(ent.first, ent.second));
//		}
//
//		return result;
//	}
//
//	template<class Func, class Group = typename std::result_of<Func(T)>::type>
//	std::vector<pair<Group, matchingGroups>> groupValues(Func f)
//	{
//
//		std::vector<pair<Group, matchingGroups>> result;
//		std::vector<pair<Group, coordGroup>> lambdaResults = groupByLambda(f);
//		for (auto &tup : lambdaResults)
//		{
//			Group group = tup.first;
//			coordGroup g_gag = tup.second;
//			matchingGroups mg;
//			while (g_gag.size() > 0)
//			{
//				coordGroup gi;
//				auto last_gi_size = gi.size();
//				while (true)
//				{
//					coordGroup::iterator it = g_gag.begin();
//					while (it != g_gag.end())
//					{
//						bool inserted = false;
//						if (gi.size() == 0)
//						{
//							gi.push_back(*it);
//							it = g_gag.erase(it);
//							inserted = true;
//						}
//						else
//						{
//							for (auto &elem : gi)
//							{
//								if (isCoordNear(*it, elem))
//								{
//									gi.push_back(*it);
//									it = g_gag.erase(it);
//									inserted = true;
//									break;
//								}
//							}
//						}
//						if (!inserted)
//						{
//							++it;
//						}
//					}
//
//					if (gi.size() == last_gi_size)
//					{
//						break;
//					}
//
//					last_gi_size = gi.size();
//				}
//				mg.push_back(gi);
//			}
//			result.push_back(pair<Group, matchingGroups>(group, mg));
//		}
//		return result;
//	}
//
//	friend class Matrix<T, 2>;
//};
//
///*template<class T>
//using Matrix2d = Matrix<T, 2>;
//
//template<class T>
//using Matrix3d = Matrix<T, 3>;
//
//
//
//template<typename Groups>
//void print(const Groups& all_groups) {
//	for (const auto& groupType : all_groups) {
//		cout << groupType.first << ":" << endl;
//		for (const auto& groupOfType : groupType.second) {
//			for (const auto& coord : groupOfType) {
//				cout << "{ ";
//				for (int i : coord) {
//					cout << i << ' ';
//				}
//				cout << "} ";
//			}
//			cout << endl;
//		}
//	}
//}
//
//int main() {
//	Matrix2d<char> m = { { 'a', 'A', 'a' },{ 'B', 'a', 'B' },{ 'B', 'a', 'B' } };
//	auto all_groups = m.groupValues([](auto i) {return std::islower(i) ? "L" : "U"; });
//	print(all_groups);
//	Matrix3d<int> m2 = { { { 1, 2, 3 },{ 1, 2 },{ 1, 2 } },{ { 1, 2 },{ 1, 2, 3, 4 } } };
//	auto groups = m2.groupValues([](auto i) {return i % 3 ? "!x3" : "x3"; });
//	print(groups);
//}*/
//
