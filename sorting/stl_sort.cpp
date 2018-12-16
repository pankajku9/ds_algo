#include <algorithm>
#include <iostream>
#include <vector>
namespace container_ {

template <typename T>
int printV(std::vector<T> data) {
  for (auto& a : data) std::cout << a << " ";
  std::cout << std::endl;
}
template <typename T>
int bubble_sort(std::vector<T>& data) {
  int sz = data.size();
  for (int i = 0; i < sz; i++)
    for (int j = 1; j < sz - i; j++)
      if (data[j] < data[j - 1]) std::swap(data[j], data[j - 1]);
  return 0;
}

template <typename T>
int selection_sort(std::vector<T>& data) {
  int sz = data.size();
#if 0
  for (int i = 0; i < sz; i++) {
    auto mItr = std::min_element(data.begin() + i, data.end());
    std::iter_swap(data.begin() + i, mItr);
  }
#endif
  for (int i = sz - 1; i >= 0; i--) {
    auto mItr = std::max_element(data.begin(), data.begin() + i + 1);
    std::iter_swap(data.begin() + i, mItr);
  }
  return 0;
}

template <typename T>
int insertion_sort(std::vector<T>& data) {
  int sz = data.size();
  for (int i = 1; i < sz; i++) {
    int curr = data[i];
    int j = i - 1;
    for (; j >= 0; j--) {
      if (curr < data[j])
        data[j + 1] = data[j];
      else
        break;
    }
    data[j + 1] = curr;
  }

  // insertion sort
      for (auto i = v.begin(); i != v.end(); ++i) {
          std::rotate(std::upper_bound(v.begin(), i, *i), i, i+1);
      }
}

template <typename T>
int merge_sorted(std::vector<T> data, int beg, int mid, int end) {
  for (int i = mid; i++; i < end) {
    int j = mid - 1;
    int curr = data[i];
    for (; j >= beg; j--) {
      if (curr < data[j])
        data[j + 1] = data[j];
      else
        break;
    }
    data[j + 1] = curr;
  }
}

}  // namespace container_

int main() {
  std::vector<int> d = {8, 5, 6, 2, 3, 1, 9};
  // container_::bubble_sort(d);
  container_::insertion_sort(d);
  container_::printV(d);
}
