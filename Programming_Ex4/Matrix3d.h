#pragma once
#pragma warning(disable:4996)

#include <unordered_map>
#include <set>
#include <initializer_list>
#include <array>
#include <iostream>

using namespace std;

template<class T>
class Matrix3d
{
private:
	// Recursivley collect all adjacent cells with the same Func result
	template<class Func>
	void _collect_cells(int z, int i, int j, set<array<int, 3>>* s, Func func) const
	{
		T curr = matrix[z][i][j];
		s->insert({ z, i, j });

		if (z + 1 < d3_size && func(matrix[z + 1][i][j]) == func(curr) && s->find({ z + 1, i, j }) == s->end()) _collect_cells(z + 1, i, j, s, func);
		if (z > 0 && func(matrix[z - 1][i][j]) == func(curr) && s->find({ z - 1, i, j }) == s->end()) _collect_cells(z - 1, i, j, s, func);

		if (i + 1 < d2_size && func(matrix[z][i + 1][j]) == func(curr) && s->find({ z, i + 1, j }) == s->end()) _collect_cells(z, i + 1, j, s, func);
		if (i > 0 && func(matrix[z][i - 1][j]) == func(curr) && s->find({ z, i - 1, j }) == s->end()) _collect_cells(z, i - 1, j, s, func);

		if (j + 1 < d1_size && func(matrix[z][i][j + 1]) == func(curr) && s->find({ z, i, j + 1 }) == s->end()) _collect_cells(z, i, j + 1, s, func);
		if (j > 0 && func(matrix[z][i][j - 1]) == func(curr) && s->find({ z, i, j - 1 }) == s->end()) _collect_cells(z, i, j - 1, s, func);

		return;
	}
public:
	vector<vector<vector<T>>> matrix;
	size_t d1_size;
	size_t d2_size;
	size_t d3_size;

	Matrix3d() : matrix(vector<vector<vector<T>>>()), d1_size(0), d2_size(0), d3_size(0) {}

	Matrix3d(initializer_list<initializer_list<initializer_list<T>>> init)
	{
		d3_size = init.size();
		matrix = vector<vector<vector<T>>>();
		for (auto list2d : init)
		{
			if (list2d.size() > d2_size) d2_size = list2d.size();
			for (auto row : list2d)
				if (row.size() > d1_size) d1_size = row.size();
		}

		for (auto list2d : init)
		{
			matrix.push_back(vector<vector<T>>());
			for (auto row : list2d)
			{
				matrix[matrix.size() - 1].push_back(vector<T>(row.begin(), row.end()));
				if (matrix[matrix.size() - 1][matrix[matrix.size() - 1].size() - 1].size() < d1_size) matrix[matrix.size() - 1][matrix[matrix.size() - 1].size() - 1].resize(d1_size);
			}

			while (matrix[matrix.size() - 1].size() < d2_size) matrix[matrix.size() - 1].push_back(vector<T>(d1_size));
		}
	}

	~Matrix3d() {}

	template<class Func, class Group = typename result_of<Func(T)>::type>
	unordered_map<Group, vector<vector<array<int, 3>>>> groupValues(Func func) const
	{
		set<array<int, 3>> collected_cells = {};
		set<array<int, 3>> group = {};
		unordered_map<Group, vector<vector<array<int, 3>>>> result;

		for (int z = 0; z < d3_size; z++)
		{
			for (int i = 0; i < d2_size; i++)
			{
				for (int j = 0; j < d1_size; j++)
				{
					array<int, 3> curr = { z, i, j };
					if (collected_cells.find(curr) == collected_cells.end())
					{
						collected_cells.insert(curr);
						group = {};
						_collect_cells(z, i, j, &group, func);
						if (!group.empty())
						{
							Group currGroup = func(matrix[z][i][j]);
							if (result.find(currGroup) == result.end()) result[currGroup] = vector<vector<array<int, 3>>>();
							vector<array<int, 3>> temp = vector<array<int, 3>>();
							for (const auto item : group)
							{
								temp.push_back(item);
								collected_cells.insert(item);
							}
							result[currGroup].push_back(temp);
							sort(result[currGroup].begin(),
								result[currGroup].end(),
								[](auto x, auto&& y) { return (x[0] < y[0] || (x[0] == y[0] && x[1] < y[1]) || (x[0] == y[0] && x[1] == y[1] && x[2] < y[2])); }
							);
						}
					}
				}
			}
		}

		return result;
	}
};
