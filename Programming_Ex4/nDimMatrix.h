//#pragma once
//#pragma warning(disable:4996)
//
//#include <string>
//#include <unordered_map>
//#include <set>
//#include <algorithm>
//
//using namespace std;
//
//template<size_t dimcount, typename T>
//struct nDimVector
//{
//	typedef vector< typename nDimVector<dimcount - 1, T>::type > type;
//};
//
//template<typename T>
//struct nDimVector<0, T>
//{
//	typedef T type;
//};
//
//template<typename S>
//typedef void(*vFunctionCall)(S arg1, S arg2);
//
//template<class T, size_t dimcount>
//class nDimMatrix
//{
//private:
//	nDimVector<dimcount, T> matrix = nDimVector<dimcount, T>();
//
//public:
//	nDimMatrix() {};
//	~nDimMatrix(){};
//	nDimMatrix<T, dimcount>& operator= (const nDimMatrix<T, dimcount>&);
//	vector<pair<auto, vector<vector<int>>>> groupValues(vFunctionCall<T> func);
//};
//
//template<class T, size_t dimcount>
//inline nDimMatrix<T, dimcount>& nDimMatrix<T, dimcount>::operator=(const nDimMatrix<T, dimcount>&)
//{
//	// TODO: insert return statement here
//}
//
//template <class T, size_t dimcount>
//vector<pair<auto, vector<vector<int>>>> nDimMatrix<T, dimcount>::groupValues(vFunctionCall<T> func)
//{
//	size_t dim = 0;
//	nDimVector<dimcount, T> tempMatrix = nDimVector<dimcount, T>(this->matrix);
//	
//	while (dim < dimcount)
//	{
//		nDimVector<dimcount, T> matrix	
//	}
//}
//
//
//template<class T>
//using Matrix2d = nDimMatrix<T, 2>;
//
//template<class T>
//using Matrix3d = nDimMatrix<T, 3>;
