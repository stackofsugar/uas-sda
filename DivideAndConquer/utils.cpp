#include "include/pch.h"
using namespace std;

// Swapper Algorithm
void _swap(int &lhs, int &rhs) {
    int temp = lhs;
    lhs = rhs;
    rhs = temp;
}

// QS' Partition Algorithm
int _partition(vector<int> &vec, int l_elem, int u_elem) {
    int pivot = vec[u_elem];
    int i = (l_elem - 1);

    for (int j = l_elem; j <= (u_elem - 1); j++) {
        if (vec[j] <= pivot) {
            _swap(vec[++i], vec[j]);
        }
    }
    _swap(vec[i + 1], vec[u_elem]);
    return (i + 1);
}

// Quick Sort Algorithm
void _quickSort(vector<int> &vec, int l_elem, int u_elem) {
    if (l_elem < u_elem) {
        int part_index = _partition(vec, l_elem, u_elem);
        _quickSort(vec, l_elem, (part_index - 1));
        _quickSort(vec, (part_index + 1), u_elem);
    }
}

// Quick Sort Wrapper
void quickSort(vector<int> &vec) {
    _quickSort(vec, 0, (vec.size() - 1));
}

// Sum Element Algorithm
int _sum(vector<int> &vec, int l_elem, int u_elem) {
    if (l_elem == u_elem) return vec[u_elem];
    else {
        int m_elem = ((u_elem + l_elem) / 2);
        return (_sum(vec, l_elem, m_elem) + _sum(vec, m_elem + 1, u_elem));
    }
}

// Sum Element Wrapper
int sumElems(vector<int> &vec) {
    return _sum(vec, 0, (vec.size() - 1));
}

// MinMax Algorithm
void _minMax(vector<int> &vec, int l_elem, int u_elem, int &min, int &max) {
    if (l_elem == u_elem) {
        max = (max < vec[u_elem]) ? vec[u_elem] : max;
        min = (min > vec[u_elem]) ? vec[u_elem] : min;
    }
    else if ((u_elem - l_elem) == 1) {
        if (vec[l_elem] < vec[u_elem]) {
            min = (min > vec[l_elem]) ? vec[l_elem] : min;
            max = (max < vec[u_elem]) ? vec[u_elem] : max;
        }
        else {
            min = (min > vec[u_elem]) ? vec[u_elem] : min;
            max = (max < vec[l_elem]) ? vec[l_elem] : max;
        }
    }
    else {
        int m_elem = ((u_elem + l_elem) / 2);
        _minMax(vec, l_elem, m_elem, min, max);
        _minMax(vec, m_elem + 1, u_elem, min, max);
    }
}

// MinMax Wrapper
void findMinMax(vector<int> &vec, int **min_max) {
    **min_max = INT_INF;            // min
    *(*min_max + 1) = M_INT_INF;    // max

    _minMax(vec, 0, (vec.size() - 1), **min_max, *(*min_max + 1));
}