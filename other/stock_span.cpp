/*
 * span.cpp
 *
 *  Created on: Nov 19, 2018
 *      Author: pankajku
 */



#include <iostream>

#include <vector>
#include <stack>

using namespace std;

vector<int> cal_span(vector<int>& prices)
{
    stack<int> stk;
    vector<int> span = {1};
    stk.push(prices[0]);

    for(int i =1; i< prices.size(); i++){
        auto x = prices[i];
        int cspan = 1;
        int t = stk.top();
        int j = 1;
        while(!stk.empty() && t <= x){
            stk.pop();
            cspan += span[i-j];
            cout << i <<" " << j <<"\n";
            if(!stk.empty())  t = stk.top();
            j++;
        }
        span.push_back(cspan);
        stk.push(x);
    }

    return span;
}
int main() {
    /*int tc;
    cin >>  tc ;
    for(int i = 0; i < tc; i++){
        int len, temp;
        cin >> len;
        vector<int> input;
        for(int j = 0; j < len ; j++){
            cin >> temp;
            input.push_back(temp);
        }
        vector<int> ans =  cal_span(input);

        for(int j = 0; j < len ; j++){
            cout << ans[i] << " ";
        }

        cout <<"\n";
    }*/

    std::vector<int> price = {100, 80, 60, 70, 60, 75, 85};
    auto ans =  cal_span(price);
    for(auto& a : ans){
        cout<< a <<" ";
    }

    return 0;
}
