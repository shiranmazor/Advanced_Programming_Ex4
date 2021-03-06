#pragma once
#pragma warning(disable:4996)

#include <unordered_map>
#include <set>
#include <initializer_list>
#include <array>
#include <iostream>

using namespace std;

template<class T>
class Matrix2d
{
private:
	// Recursivley collect all adjacent cells with the same Func result
	template<class Func>
	void _collect_cells(int i, int j, set<array<int, 2>>* s, Func func) const
	{
		T curr = matrix[i][j];
		s->insert({ i, j });

		if (i + 1 < d2_size && func(matrix[i + 1][j]) == func(curr) && s->find({ i + 1, j }) == s->end()) _collect_cells(i + 1, j, s, func);
		if (i > 0 && func(matrix[i - 1][j]) == func(curr) && s->find({ i - 1, j }) == s->end()) _collect_cells(i - 1, j, s, func);
		if (j + 1 < d1_size && func(matrix[i][j + 1]) == func(curr) && s->find({ i, j + 1 }) == s->end()) _collect_cells(i, j + 1, s, func);
		if (j > 0 && func(matrix[i][j - 1]) == func(curr) && s->find({ i, j - 1 }) == s->end()) _collect_cells(i, j - 1, s, func);

		return;
	}
public:
	vector<vector<T>> matrix;
	size_t d1_size;
	size_t d2_size;

	Matrix2d() : matrix(vector<vector<T>>()), d1_size(0), d2_size(0) {}

	Matrix2d(initializer_list<initializer_list<T>> init)
	{
		d2_size = init.size();
		matrix = vector<vector<T>>();
		for (auto row : init)
			if (row.size() > d1_size) d1_size = row.size();

		for (auto row : init)
		{
			matrix.push_back(vector<T>(row.begin(), row.end()));
			if (matrix[matrix.size() - 1].size() < d1_size) matrix[matrix.size() - 1].resize(d1_size);
		}
	}

	~Matrix2d() {}

	template<class Func, class Group = typename result_of<Func(T)>::type>
	unordered_map<Group, vector<vector<array<int, 2>>>> groupValues(Func func) const
	{
		set<array<int, 2>> collected_cells = {};
		set<array<int, 2>> group = {};
		unordered_map<Group, vector<vector<array<int, 2>>>> result;
	  
		for (int i=0; i < d2_size; i++)
		{
			for (int j=0; j < d1_size; j++)
			{
				array<int, 2> curr = { i, j };
				if (collected_cells.find(curr) == collected_cells.end())
				{
					collected_cells.insert(curr);
					group = {};
					_collect_cells(i, j, &group, func);
					if (!group.empty())
					{
						Group currGroup = func(matrix[i][j]);
						if (result.find(currGroup) == result.end()) result[currGroup] = vector<vector<array<int, 2>>>();
						vector<array<int, 2>> temp = vector<array<int, 2>>();
						for (const auto item : group)
						{
							temp.push_back(item);
							collected_cells.insert(item);
						}
						result[currGroup].push_back(temp);
						sort(result[currGroup].begin(), 
							 result[currGroup].end(), 
							 [](auto x, auto&& y) { return (x[0] < y[0] || (x[0] == y[0] && x[1] < y[1])); }
						);
					}
				}
			}
		}

		return result;
	}
};
