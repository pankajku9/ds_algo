/*
 * genericSort.cpp
 *
 *  Created on: Oct 22, 2018
 *      Author: pankajku
 */

#include <algorithm>
#include <vector>

namespace iter_ {

template <typename Iterator_>
void buuble_sort(Iterator_ first, Iterator_ last) {
  auto mylast = last;
  for (auto i = first; i != last; ++i) {
    for (auto j = first + 1; j != mylast; ++j) {
      if (*(i - 1) > *j) std::iter_swap(i - 1, i);
    }
    mylast--;
  }
}

template <class Iter>
void mergeSort(Iter first, Iter last) {
  if (last - first > 1) {
    Iter middle = first + (last - first) / 2;
    merge_sort(first, middle);
    merge_sort(middle, last);
    std::inplace_merge(first, middle, last);
  }
}
template <typename T>
void insertion_sort(std::vector<T>& v){
	// insertion sort
	for (auto i = v.begin(); i != v.end(); ++i) {
		std::rotate(std::upper_bound(v.begin(), i, *i), i, i+1);
	}
}

template <typename T>
int quick_sort(std::vector<T>& input) {
  int len = input.size();
  merge_sort1<T>(input, 0, len - 1);
  return 0;
}

template <class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last) {
  if (first == last) return;
  auto pivot = *std::next(first, std::distance(first, last) / 2);
  ForwardIt middle1 = std::partition(
      first, last, [pivot](const auto& em) { return em < pivot; });
  ForwardIt middle2 = std::partition(
      middle1, last, [pivot](const auto& em) { return !(pivot < em); });
  quicksort(first, middle1);
  quicksort(middle2, last);
}

}  // namespace iter_
