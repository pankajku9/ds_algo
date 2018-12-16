#include <algorithm>
#include <chrono>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>
void print_arr(int* arr, int len, const char* text) {
  printf(" %s :", text);
  for (int i = 0; i < len; i++) {
    printf(" %d", arr[i]);
  }
  printf("\n");
}
void swap(int* x, int* y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

/**************************************************************/
int bubble_sort(int* arr, int len) {
  for (int i = 0; i < len; i++) {
    // Note: starts from 1 and end till N-len
    for (int j = 1; j < len - i; j++) {
      if (arr[j - 1] > arr[j]) {
        swap(&arr[j - 1], &arr[j]);
      }
    }
  }
  return 0;
}

int selection_sort(int* arr, int len) {
  for (int i = 0; i < len; i++) {
    int max = INT_MIN, max_idx = -1;
    int j = 0;
    for (j = 0; j < len - i; j++) {
      if (arr[j] > max) {
        max = arr[j];
        max_idx = j;
      }
    }
    swap(&arr[max_idx], &arr[j - 1]);
  }

  return 0;
}

int insertion_sort(int* arr, int len) {
  for (int i = 1; i < len; i++) {
    int curr = arr[i];
    int j = 0;
    // move in reverse direction
    for (j = i - 1; j >= 0; j--) {
      if (arr[j] >= curr)
        arr[j + 1] = arr[j];
      else
        break;
    }
    arr[j + 1] = curr;
  }

  return 0;
}
/**************************************************************/
int merge_sorted_array(int* arr, int start, int mid, int end) {
  for (int i = mid; i <= end; i++) {
    int curr = arr[i];
    int j = 0;
    // move in reverse direction
    for (j = i - 1; j >= start; j--) {
      if (arr[j] >= curr)
        arr[j + 1] = arr[j];
      else
        break;
    }
    arr[j + 1] = curr;
  }
}

int merge_sort1(int* arr, int start, int end) {
  if (start >= end) return 0;

  int mid = (start + end) / 2;

  merge_sort1(arr, start, mid);
  merge_sort1(arr, mid + 1, end);

  merge_sorted_array(arr, start, mid, end);
}

int merge_sort(int* arr, int len) {
  merge_sort1(arr, 0, len - 1);
  return 0;
}
/**************************************************************/
int partion(int* arr, int start, int end) {
  int pivot = arr[end];

  // printf("%d -%d %d-",pivot, start, end);
  while (start < end) {
    while (start < end && arr[start] <= pivot) start++;

    while (end > start && arr[end] > pivot) end--;

    if (start < end) {
      swap(&arr[start], &arr[end]);
      start++;
      end--;
    }
  }

  return start;
}
int quick_sort1(int* arr, int start, int end) {
  if (start >= end) return 0;

  int part_idx = partion(arr, start, end);
  // printf("%d ", part_idx );

  quick_sort1(arr, start, part_idx - 1);
  quick_sort1(arr, part_idx, end);

  return 0;
}

int quick_sort(int* arr, int len) {
  quick_sort1(arr, 0, len - 1);
  return 0;
}

/**************************************************************/
void heapify(int* arr, int len, int i) {
  int max_idx = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < len && arr[left] > arr[max_idx]) {
    max_idx = left;
  }

  if (right < len && arr[right] > arr[max_idx]) {
    max_idx = right;
  }

  if (max_idx != i) {
    swap(&arr[i], &arr[max_idx]);
    heapify(arr, len, max_idx);
  }
}

void make_heap(int* arr, int len) {
  for (int i = (len - 1) / 2; i >= 0; i--) {
    heapify(arr, len, i);
  }
}

int pop(int* arr, int len) {
  int max = arr[0];
  arr[0] = arr[len - 1];
  heapify(arr, len - 1, 0);
  return max;
}

int heap_sort(int* arr, int len) {
  make_heap(arr, len);
  for (int i = len; i > 0; i--) {
    int max = pop(arr, i);
    arr[i - 1] = max;
  }
  return 0;
}
/**************************************************************/
int find_max(int* arr, int len) {
  int max = INT_MIN;
  for (int i = 0; i < len; i++) {
    if (arr[i] > max) max = arr[i];
  }
  return max;
}

int counting_sort(int* arr, int len) {
  // return if negative number
  for (int i = 0; i < len; i++) {
    if (arr[i] < 0) return -1;
  }

  int count_len = find_max(arr, len) + 1;
  int* count = (int*)calloc(count_len, sizeof(int));
  int* output = (int*)calloc(len, sizeof(int));

  for (int i = 0; i < len; i++) {
    ++count[arr[i]];
  }

  for (int i = 1; i < count_len; i++) {
    count[i] += count[i - 1];
  }

  for (int i = 0; i < len; i++) {
    int idx = count[arr[i]] - 1;
    output[idx] = arr[i];
    count[arr[i]] = idx;
  }

  for (int i = 0; i < len; i++) {
    arr[i] = output[i];
  }

  free(count);
  free(output);
  return 0;
}
void  count_sort(int* arr, int len){
    if(arr == NULL || len == 0)
        return;

    int mx= INT_MIN, mi = INT_MAX;

    for(int i = 0; i <len; i++){
        if(arr[i] > mx)
            mx = arr[i];
        if(arr[i] < mi)
            mi = arr[i];
    }

    int aux_len = mx-mi +1;

    printf("%d %d %d %d \n", len, mi, mx, aux_len);

    int *aux = (int*)calloc(aux_len, sizeof(int));

    for(int i= 0; i < len;i++){
        int pos = arr[i] -mi;
        aux[pos]++;
    }

    int cnt = 0;
    for(int i = 0; i < aux_len; i++){
        int  j = aux[i] ;
        int n = i+mi;

        while(j){
            arr[cnt] = n;
            cnt++;
            j--;
        }
    }
    free(aux);
}
/**************************************************************/

typedef struct Tnode {
  int data;
  int count;
  Tnode* left;
  Tnode* right;
} tnode;

tnode* new_node(int i) {
  tnode* temp = (tnode*)calloc(1, sizeof(tnode));

  if (!temp) return NULL;

  temp->data = i;
  temp->left = NULL;
  temp->right = NULL;
  temp->count = 1;
  return temp;
}

int insert_node(tnode* root, int i) {
  if (!root) return -1;

  tnode* ptr = root;
  while (ptr) {
    if (i < ptr->data) {
      if (ptr->left) {
        ptr = ptr->left;
      } else {
        ptr->left = new_node(i);
        if (!ptr->left) return -1;
        break;
      }
    } else if (i > ptr->data) {
      if (ptr->right) {
        ptr = ptr->right;
      } else {
        ptr->right = new_node(i);
        if (!ptr->right) return -1;
        break;
      }
    } else {
      ++(ptr->count);
      break;
    }
  }

  return 0;
}
int read_sorted(tnode* root, int* arr, int* i, int len) {
  if (!root) return -2;

  if (root->left) {
    int ret = read_sorted(root->left, arr, i, len);
    if (ret != 0) return ret;
  }

  for (int j = 0; j < root->count; j++) {
    if (*i >= len) return -4;
    arr[*i] = root->data;
    *i = (*i) + 1;
  }

  if (root->right) {
    int ret = read_sorted(root->right, arr, i, len);
    if (ret != 0) return ret;
  }

  return 0;
}

void delete_tree(tnode* root) {
  if (!root) return;
  if (root->left) delete_tree(root->left);
  if (root->right) delete_tree(root->right);
  free(root);
}

int btree_sort(int* arr, int len) {
  tnode* root = new_node(arr[0]);
  if (!root) return -1;

  for (int i = 1; i < len; i++) {
    int ret = insert_node(root, arr[i]);
    if (ret != 0) {
      delete_tree(root);
      return ret;
    }
  }

  int i = 0;
  int ret = read_sorted(root, arr, &i, len);
  delete_tree(root);

  return ret;
}

/**************************************************************/
#define MAX_ALGO 10
typedef int (*sorting_fun_ptr)(int* arr, int len);

struct __sorting_func {
  const char* name;
  sorting_fun_ptr func;
};

struct sorting_algo {
  int num_algo;
  __sorting_func algo[MAX_ALGO];
};

static sorting_algo algo_list = {.num_algo = 8,
                                 .algo = {
                                     {"Bubble Sort", bubble_sort},
                                     {"Insertion Sort", insertion_sort},
                                     {"Selection Sort", selection_sort},
                                     {"Merge Sort", merge_sort},
                                     {"Quick Sort", quick_sort},
                                     {"heap_sort", heap_sort},
                                     {"counting_sort", counting_sort},
                                     {"btree_sort", btree_sort},
                                 }};

#define FAILED_IF_NON_ZERO(x, test)                                       \
  do {                                                                    \
    if (x < 0) {                                                          \
      printf(" %s failed at  %s, %s:%d \n", test, __FUNCTION__, __FILE__, \
             __LINE__);                                                   \
      return -1;                                                          \
    }                                                                     \
  } while (0)

#define FAILED_IF_NOT_EQUAL(x, y, arr, len, test)                        \
  do {                                                                   \
    print_arr(arr, len, test);                                           \
    if (x != y) {                                                        \
      printf(" %s failed at: %s,%s:%d \n", test, __FUNCTION__, __FILE__, \
             __LINE__);                                                  \
    } else {                                                             \
      printf(" %s passed at:%s,%s:%d \n", test, __FUNCTION__, __FILE__,  \
             __LINE__);                                                  \
    }                                                                    \
  } while (0)

int is_sorted(int* arr, int len) {
  for (int i = 1; i < len; i++) {
    if (arr[i] < arr[i - 1]) return -1;
  }
  return 0;
}

int exec_sort_algo(sorting_fun_ptr run_sort, int* arr, int len,
                   const char* test) {
  int ret;
  ret = run_sort(arr, len);
  FAILED_IF_NON_ZERO(ret, test);
  ret = is_sorted(arr, len);
  FAILED_IF_NOT_EQUAL(ret, 0, arr, len, test);
  return 0;
}
int test_sort_algo(sorting_fun_ptr sorter) {
  int ret;
  int arr1[1] = {1};
  exec_sort_algo(sorter, arr1, 1, "1.single_input_test");

  int arr2[4] = {1, 2, 3, 4};
  exec_sort_algo(sorter, arr2, 4, "2.sorted_input_test");

  int arr3[4] = {1, 1, 1, 1};
  exec_sort_algo(sorter, arr3, 4, "3.equal_input_test ");

  int arr4[4] = {91, 81, 71, 61};
  exec_sort_algo(sorter, arr4, 4, "4.rev_sorted_test  ");

  int arr5[4] = {91, -81, 71, -61};
  exec_sort_algo(sorter, arr5, 4, "5.negt_test        ");
#if 0
		int arr6[1000];
		for(int i =0; i <1000; i++){
			arr6[i] = rand()/1000;
		}
		exec_sort_algo(sorter, arr6, 1000, "6.random_test      ");
#endif
  return 0;
}

void unit_test() {
  for (int i = 0; i < algo_list.num_algo; i++) {
    printf("------------Testing %s------------------ \n",
           algo_list.algo[i].name);
    test_sort_algo(algo_list.algo[i].func);
  }
}
/**************************************************************/

int random_fill(std::vector<int>& vec) {
  int num = vec.capacity();
  // First create an instance of an engine.
  std::random_device rnd_device;
  // Specify the engine and distribution.
  std::mt19937 mersenne_engine{rnd_device()};  // Generates random integers
  std::uniform_int_distribution<int> dist{1, num};
  auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };
  generate(begin(vec), end(vec), gen);
  return 0;
}

/* runs all the sorting algo's for with a data of given size and return time in
 * us*/
std::vector<int> perfrm_single_run(int size) {
  using time_point = std::chrono::high_resolution_clock::time_point;
  using clock = std::chrono::high_resolution_clock;
  using microsec = std::chrono::microseconds;
  std::vector<int> perf_count;
  for (int i = 0; i < algo_list.num_algo; i++) {
    std::vector<int> vec(size);
    random_fill(vec);
    time_point start_ = clock::now();
    ;
    // execute the algo
    algo_list.algo[i].func(vec.data(), vec.size());
    time_point end_ = clock::now();
    auto tms = std::chrono::duration_cast<microsec>(end_ - start_).count();
    perf_count.push_back(tms);
    vec.clear();
  }
  return perf_count;
}

using perfm_pair = std::pair<int, std::vector<int>>;

void print_perfrm_stats(std::vector<perfm_pair>& result) {
  printf(" Test name          ");
  for (int i = 0; i < result.size(); i++) {
    printf("%10d ", result[i].first);
  }
  printf("\n");
  for (int i = 0; i < algo_list.num_algo; i++) {
    printf("%20s", algo_list.algo[i].name);
    for (int j = 0; j < result.size(); j++) {
      printf("%10d ", result[j].second[i]);
    }
    printf("\n");
  }
}
void performence_test() {
  std::vector<perfm_pair> result;

  for (int i = 1; i <= 5; i++) {
    perfm_pair p1;
    int sz = 2000 * i;
    std::vector<int> pef_count = perfrm_single_run(sz);
    result.push_back(std::make_pair(sz, pef_count));
  }
  for (int i = 2; i <= 10; i++) {
    perfm_pair p1;
    int sz = 10000 * i;
    std::vector<int> pef_count = perfrm_single_run(sz);
    result.push_back(std::make_pair(sz, pef_count));
  }
  print_perfrm_stats(result);
}

int sort_main() {
#if 0
  std::vector<int> vec(1000);
  random_fill(vec);
  container_::merge_sort<int>(vec);
  std::cout << " After sorting vector is sorted:"
            << std::is_sorted(vec.begin(), vec.end());
#else
  unit_test();
  performence_test();
  printf("Hello, I am What I am");
#endif

  return 0;
}

int main() {
  sort_main();
  return 0;
}
