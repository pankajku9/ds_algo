#include <iostream>
using namespace std;
int recur_search(int arr[], int beg, int end , int key);
void sub_array(int arr[], int beg, int end);


int main(int argc, char** argv)
{
    cout<<" Give Me some hope.. Give me some light.. I wanna fight tonight.."<<endl;
    //int arr[] = { 1,2,3,4,5,6,7,8,9};
    int arr[] = {4,3,2,8,1,5,7};
    
    //int index = recur_search(arr, 0, 8, 11);
    //sub_array(arr, 0, 4);
    bubble_sort(arr, 0, 6);
    
    cout<<"Sorted :"; 
    for(int k = 0; k <= 6 ; k++){
        cout<< arr[k]<<" ";   
    }           
    cout<<endl;
    return 0;
    
}




void sub_array(int arr[], int beg, int end) 
{
    for(int i = beg; i <= end ; i++){
        
        for(int j = i+1; j <= end ; j++){
          
        cout<<"Subarray ("<<i<<" "<<j<<"): "; 
        for(int k = i; k <= j ; k++){
                cout<< arr[k]<<" ";   
            }           
        cout<<endl;
        }
    }
}


int recur_search(int arr[], int beg, int end , int key)
{   
    static int recus_depth = -1;
    recus_depth++;
    cout<<" Entering ["<<recus_depth<<"]"<<beg<<" " <<end<<endl;
    int ret_val;
    
    if(beg > end)
        ret_val = -1;
    else if(arr[beg] == key)
        ret_val = beg;
    else ret_val = recur_search(arr, beg + 1, end, key);
    
    cout<<" Returning ["<<recus_depth<<"] "<< ret_val<<endl;
    recus_depth--;
    return ret_val;
}
    