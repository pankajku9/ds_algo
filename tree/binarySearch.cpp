#include<stdlib.h>
#include<assert.h>
#include<stdio.h>

#define DEBUG 1
#ifdef DEBUG
#define dprintf(fmt, ...)    fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define dprintf(fmt, args...)
#endif

int run_bsearch(int* arr, int& beg, int& end, int x){
	int mid = -1;
	while(beg <= end){
		mid = beg + (end-beg)/2;
		dprintf("%d %d %d \n", beg, mid, end);
		if(arr[mid] == x)
			break;

		else if(arr[mid] > x)
			end = mid -1;

		else
			beg = mid+1;
	}
	return mid;
}

bool bin_search(int* arr, int n, int x){

	dprintf("Arr: ");
	for(int i = 0; i<n ; i++)
		dprintf(" %d", arr[i]);
	dprintf(" X : %d\n", x);

	int beg = 0;
	int end = n-1;
	int mid = run_bsearch(arr, beg, end, x);
	dprintf("%d %d %d \n", beg, mid, end);

	if( beg <= end){
		dprintf(" element is found at %d\n", mid);
		return true;
	}
	else{
		dprintf(" element not found, can inserted at at %d\n", beg);
		return false;
	}
}


void test1(int n){
	int* arr = (int*) malloc(sizeof(int)*n);
	for(int i = 0; i<n ; i++)
		arr[i] = 2*i+1;

	int even = rand()%n;
	if(even%2 == 1)
		even = even-1;

	int odd = rand()%n;
	if(odd%2 == 0)
		odd = odd+1;

	assert(false == bin_search(arr, n, 0));
	assert(false == bin_search(arr, n, 2*n));
	assert(true==bin_search(arr, n, odd));
	assert(false== bin_search(arr, n, even));

}

void test2(){
	dprintf("------------------------------------------\n");
	int arr[] = {3,4,4,4,4,4,4,7,7,7,7,7,8};
	dprintf("Found:%d \n", bin_search(arr, 13, 3));
	dprintf("Found:%d \n", bin_search(arr, 13, 4));
	dprintf("Found:%d \n", bin_search(arr, 13, 7));
	dprintf("Found:%d \n", bin_search(arr, 13, 8));
	dprintf("Found:%d \n", bin_search(arr, 13, 5));
}
bool bin_search_rec(int* arr, int beg, int end, int x){

	int mid = beg + (end-beg)/2;
	if(arr[mid] == x)
		return true;
	else if(arr[mid] > x)
		return bin_search_rec(arr, beg, mid-1, x);
	else
		return bin_search_rec(arr, mid+1, end, x);
}
int smaller_then(int* arr, int n, int x){

	int beg = 0;
	int end = n-1;
	int mid = run_bsearch(arr, beg, end, x);
	dprintf("%d %d %d \n", beg, mid, end);

	if(beg <= end){
		while(mid >= 0 && arr[mid-1] == x)
			mid--;

		return mid;
	}
	else{
		return beg;
	}
}

void test3(){
	int arr[] = {3,4,4,4,4,4,4,7,7,7,7,7,8};
	dprintf("Smaller then %d :%d \n", 3,  smaller_then(arr, 13, 3));
	dprintf("Smaller then %d :%d \n", 4,  smaller_then(arr, 13, 4));
	dprintf("Smaller then %d :%d \n", 7, smaller_then(arr, 13, 7));
	dprintf("Smaller then %d :%d \n", 8,  smaller_then(arr, 13, 8));
	dprintf("Smaller then %d :%d \n", 5, smaller_then(arr, 13, 5));
}

int equal_to(int* arr, int n, int x){

	int beg = 0;
	int end = n-1;
	int mid = run_bsearch(arr, beg, end, x);
	dprintf("%d %d %d \n", beg, mid, end);

	int cnt = 0;
	if(beg <= end){
		while(mid >= 0 && arr[mid-1] == x)
			mid--;

		while(arr[mid] == x){
			cnt++;
			mid++;
		}
	}
	return cnt;
}

void test4(){
	int arr[] = {3,4,4,4,4,4,4,7,7,7,7,7,8};
	dprintf("equal_to %d :%d \n", 3,  equal_to(arr, 13, 3));
	dprintf("equal_to %d :%d \n", 4,  equal_to(arr, 13, 4));
	dprintf("equal_to %d :%d \n", 7, equal_to(arr, 13, 7));
	dprintf("equal_to %d :%d \n", 8,  equal_to(arr, 13, 8));
	dprintf("equal_to %d :%d \n", 5, equal_to(arr, 13, 5));
}

int lt_equal_to(int* arr, int n, int x){

	int beg = 0;
	int end = n-1;
	int mid = run_bsearch(arr, beg, end, x);
	dprintf("%d %d %d \n", beg, mid, end);

	if(beg <= end){
		while(mid+1 < n && arr[mid+1] == x)
			mid++;
	}
	else{
		 while (arr[mid] > x)
		        mid--;
	}
	return mid+1;
}

int pow_(int x, int y){

	if(y == 0)
		return 1;
	else if(y%2 ==0)
		return pow_(x, y/2) * pow_(x, y/2);
	else
		return x*pow_(x, y/2) * pow_(x, y/2);
}

long long pow_1(int x, int n) {

	//Function exp_by_squaring_iterative(x, n)
	if (n < 0) {
		x = 1 / x;
		n = -n;
	}
	if (n == 0)
		return 1;

	int y = 1;
	while (n > 1) {
		printf(" %d \n", n);
		if (n % 2 == 0) { // n is even then
			x = x * x;
			n = n / 2;
		} else {
			y = x * y;
			x = x * x;
			n = (n - 1) / 2;
		}
	}
	return x * y;

}

void test7(){
	printf("%d \n", pow_1(4,31));
}

void test5(){
	int arr[] = {3,4,4,4,4,4,4,7,7,7,7,7,8};
	dprintf("lt_equal_to %d :%d \n", 3,  lt_equal_to(arr, 13, 3));
	dprintf("lt_equal_to %d :%d \n", 4,  lt_equal_to(arr, 13, 4));
	dprintf("lt_equal_to %d :%d \n", 7, lt_equal_to(arr, 13, 7));
	dprintf("lt_equal_to %d :%d \n", 8,  lt_equal_to(arr, 13, 8));
	dprintf("lt_equal_to %d :%d \n", 5, lt_equal_to(arr, 13, 5));
	dprintf("lt_equal_to %d :%d \n", 1, lt_equal_to(arr, 13, 1));
	dprintf("lt_equal_to %d :%d \n", 15, lt_equal_to(arr, 13, 15));
}

void test(){

}
int main(){
	test1(10);
	test2();
	test3();
	test4();
	test7();
	//printf("%d\n", pow_(-2,4));
}
