
/************************************************
#
#      Filename: test6.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2020-05-12 10:01:56
# Last Modified: 2020-05-12 10:22:28
#***********************************************/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <NTL/ZZ.h>   // ntl库
using namespace std;
using namespace NTL;

void input(int i, int arg1, int arg2)
{
    int row = arg1;
    int z = arg2;
    vector<ZZ> v;

    // 准备数据
    string b{"data"};
    b = b + to_string(i);
    b = b + ".txt";
    ifstream in{b};
    string ns;
    int index = 0;
    for(string s; in >> s;)
    {
        auto i = s.find('=');
        ns = s.substr(i+1, 150);
        auto nn = conv<ZZ> (ns.c_str());
        v.push_back(nn);
    }
    //for(auto d: v)
    //{
        //cout << d << endl;
    //}
    //cout << "=====================================\n=====================================\n" << endl;
    in.close();

}

int main(int argc, char *argv[])
{
    vector<int> k{5, 7, 10, 12, 15, 17, 20, 22, 25}; //汉明重量
    int k_j = 0;

    for(int i = 40; i <= 200; i += 20)
    {
        for(int j = 1; j <= 4; ++j)
        {
            cout << "维数: " << i << " 题目: " << j << endl;
            input(i+j, i+1, k[k_j]);
        }
        ++k_j;
    } 
    
    return 0;
}
