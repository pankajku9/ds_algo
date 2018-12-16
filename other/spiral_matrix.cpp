/*
 * main.cpp
 *
 *  Created on: Nov 27, 2018
 *      Author: pankajku
 */

//#include "../c_concepts/data_structure/linked_list2.h"

#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<vector<int> > generateMatrix(int A) {
    vector<vector<int> > mat(A);
    for(int i = 0; i < A; i++)
        mat[i] = vector<int>(A);

    int last = A-1;
    int s  = 0; // spriral round

    int num = 1;
    while(s < A/2){

        for(int i = s; i <last-s; i++){
            mat[s][i] = num;
            num++;
        }

        for(int i = s; i <last-s; i++){
            mat[i][last-s] = num;
            num++;
        }

        for(int i = last-s; i > s; i--){
            mat[last-s][i] = num;
            num++;
        }
        for(int i = last-s; i > s; i--){
            mat[i][s] = num;
            num++;
        }
        s++;
    }
    if(A/2 % 2 == 1)
        mat[s][s] = num;

    return mat;
}

vector<vector<int> > generateMatrix1(int r, int c) {
    vector<vector<int> > mat(r);
    for(int i = 0; i < r; i++)
        mat[i] = vector<int>(c);

    int row_beg = 0, col_beg = 0, row_end = r-1, col_end = c-1;
    int num = r*c +1;

    while(row_beg < row_end && col_beg < col_end){
        for(int i= col_beg; i < col_end ; i++)
            mat[row_beg][i] = --num;

        for(int i= row_beg; i < row_end ; i++)
            mat[i][col_end] = --num;

        for(int i= col_end; i > col_beg ; i--)
            mat[row_end][i] = --num;

        for(int i= row_end; i > row_beg ; i--)
            mat[i][col_beg] = --num;

        row_beg++; col_beg++; col_end--; row_end--;

    }

    if(r % 2 == 1 and c%2 == 1)
        mat[row_beg][col_beg] = --num;

    return mat;
}

int pascal_val(vector<int>& fact, int n, int r){
    int div = fact[r] * fact[n-r];
    return fact[n]/div;

}

vector<vector<int> > solve(int A) {
    vector<int> fact(A+1);
    fact[0] = 1;
    for(int i = 1; i <= A; i++){
        fact[i] = i * fact[i-1];
    }

    vector<vector<int> > trng(A+1);
    for(int i = 0; i <= A; i++){
        vector<int> vec;
        trng[i] = vector<int>();
        for(int j = 0; j <=i; j++){
            auto val = pascal_val(fact, i, j);
            //printf("%d %d %d \n", i, j, val);
            trng[i].push_back(val);
        }
        //trng.push_back(std::move(vec));
    }
    return trng;
}

int main(int argc, char** argv){

    if(argc < 2)
        return 0;

    int A = stoi(argv[1]);
    auto x2 = solve(A);
    for(int i = 0; i< A; i++){
        for(int j = 0 ; j < x2[i].size(); j++){
           //std::cout<< x[i][j] <<" ";
           printf("%6d ", x2[i][j]);
        }
        cout <<endl;
    }
   /* int A = stoi(argv[1]);
    auto x = generateMatrix(A);
    for(int i = 0; i< A; i++){
            for(int j = 0 ; j < A; j++){
               //std::cout<< x[i][j] <<" ";
               printf("%6d ", x[i][j]);
            }
            cout <<endl;
    }
*/
    /*if(argc < 3)
        return 0;

    int r = stoi(argv[1]);
    int c = stoi(argv[2]);

    auto x1 = generateMatrix1(r, c);
       for(int i = 0; i < r; i++){
               for(int j = 0 ; j < c; j++){
                  //std::cout<< x[i][j] <<" ";
                  printf("%6d ", x1[i][j]);
               }
               cout <<endl;
       }

*/
}

