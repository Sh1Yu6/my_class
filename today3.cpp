
/************************************************
#
#      Filename: test2.cpp
#
#        Author: Sh1Yu6
#   Description: ---
#        Create: 2020-05-10 11:37:23
# Last Modified: 2020-05-14 20:04:23
#***********************************************/
#include <NTL/vec_ZZ_p.h>
#include <NTL/vec_lzz_p.h>
#include <atomic>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <NTL/ZZ.h>
#include <NTL/mat_ZZ.h>
#include <NTL/LLL.h>
#include <NTL/vec_ZZ.h>
#include <sstream>
#include <NTL/BasicThreadPool.h>
using namespace NTL;
using namespace std;

ZZ my_length[10][4] = {
    {ZZ{1000}, ZZ{1000}, ZZ{1000}, ZZ{1000}},
    {ZZ{1000}, ZZ{1000}, ZZ{1000}, ZZ{1000}},
    {ZZ{1000}, ZZ{1000}, ZZ{1000}, ZZ{1000}},
    {ZZ{1000}, ZZ{1000}, ZZ{1000}, ZZ{1000}},
    {ZZ{1000}, ZZ{1000}, ZZ{1000}, ZZ{1000}},
    {ZZ{1000}, ZZ{1000}, ZZ{1000}, ZZ{1000}},
    {ZZ{1000}, ZZ{1000}, ZZ{1000}, ZZ{1000}},
    {ZZ{1000}, ZZ{1000}, ZZ{1000}, ZZ{1000}},
    {ZZ{1000}, ZZ{1000}, ZZ{1000}, ZZ{1000}},
    {ZZ{1000}, ZZ{1000}, ZZ{1000}, ZZ{1000}},
};



template<typename T>
void create_m(T& B, int row, vector<ZZ>& v, int n)
{
    for (int outer_loop_index = 0; outer_loop_index < row-1; ++outer_loop_index)
    {
        for (int inner_loop_index = 0; inner_loop_index < row; ++inner_loop_index)
        {
            if(inner_loop_index == row - 1)   // 最后一列
            {
                B[outer_loop_index][inner_loop_index] = v[outer_loop_index]*n;
            }
            else if(outer_loop_index == row - 1 && inner_loop_index != row)  //最后一行 
            {
                B[outer_loop_index][inner_loop_index] = 0;
            }
            else if(outer_loop_index == inner_loop_index)
            {
                B[outer_loop_index][inner_loop_index] = 1;
            }
            else
            {
                B[outer_loop_index][inner_loop_index] = 0;
            }
        }
    }

    B[0][0] *= -1 ;			//把S置为正数

}

// 输出结果
template<typename T>
bool print_2(T& B, int row, vector<ZZ>& v, int bol, int k, int pure, int n, bool& fff, int length_row, int length_col)
{

    ZZ sum{ 0 };
    int k_c = 0;  	// 汉明重量
    int k_z = 0; 	// 	0的数量
    int k_cc = 0;	//  -1的数量
    ZZ length{ 0 };
    ZZ mm{ 1000000 };


    //for (int outer_loop_index = 0; outer_loop_index < row - 1; ++outer_loop_index)
    //{
        if ( B[0][row - 2] == 1)
        {
            cout << B[0] <<endl;
            fff = false;
            for (int inner_loop_index = 0; inner_loop_index < row - 2; ++inner_loop_index)
            {
                sum += B[0][inner_loop_index]*B[0][inner_loop_index];
            }
            if(sum < my_length[length_row][length_col])
            {
                my_length[length_row][length_col] = sum;
                cout << "模长度是: " << sum << endl;
            }

            return true;
        }
        else
        {
            for (int inner_loop_index = 0; inner_loop_index < row - 2; ++inner_loop_index)
            {
                sum += B[0][inner_loop_index]*B[0][inner_loop_index];
            }
            if(sum < my_length[length_row][length_col])
            {
                my_length[length_row][length_col] = sum;
                cout << "模长度是: " << sum << endl;
            }

        }


        ////cout << B[outer_loop_index] << endl;
        //sum = 0;
        //length = 0;
        //k_c = 0;
        //k_z = 0;
        //k_cc = 0;
        //// 计算某行是否等于S
        //for (int inner_loop_index = 0; inner_loop_index < row - 2; ++inner_loop_index)
        //{
            //if (B[outer_loop_index][inner_loop_index] == -2)  // 汉明重量
            //{
                //++k_c;
            //}
            //else if (B[outer_loop_index][inner_loop_index] != 0)
            //{
                //++k_c;
            //}
        //}

        //if (fff == true && k == k_c)
        //{
            //fff = false;
            //cout << "倍数C: " << n;
            //cout << " 最小值:" << length << " === " << " k :" << k_c;
            //cout << " bol: " << bol << " pure:" << pure << endl;
            //cout << B[outer_loop_index] << endl;
        //}
    //}
    return false;
}

// 执行LLL算法
void test(int row, vector<ZZ>& v, int bol, int pure, int k, bool& fff, int length_row, int length_col, int n)
{
    mat_ZZ BB;
    ZZ det;
    BB.SetDims(row-1, row);
    create_m(BB, row, v, n);
    G_LLL_XD(BB);
    G_BKZ_XD(BB, 0.99, bol, pure);
    print_2(BB, row, v, bol, k, pure, n, fff, length_row, length_col);
}

// 读取数据
void input_data(vector<ZZ>& v, int i)
{
    string b{ "data" };
    b = b + to_string(i);
    b = b + ".txt";

    ifstream in{ b };
    string ns;
    int index = 0;
    for (string s; in >> s;)
    {
        auto i = s.find('=');
        ns = s.substr(i + 1, 150);
        auto nn = conv<ZZ>(ns.c_str());
        v.push_back(nn);
    }
    in.close();
}

// 运行 
void run(int question_num, int arg1, int arg2, int length_row, int length_col)
{
    ZZ a;
    vector<ZZ> v;
    int row = arg1;	// 矩阵维度
    int k = arg2;	// 汉明重量

    input_data(v, question_num);

    bool fff = true;
    NTL_EXEC_RANGE(10, first, last);    // 数字为循环大小
        for (int bol = first; bol < last; ++bol)
        {
            for (int pure = 0; pure < 15; ++pure)
            {
                for (int n = 1; n < row; ++n)
                {
                    test(row, v, bol+10, pure, k, fff, length_row, length_col, n);
                    if (!fff)
                        break;
                }
            if (!fff)
                break;
            }
        if (!fff)
            break;
        }
    NTL_EXEC_RANGE_END;

    
}


int main(int argc, char* argv[])
{

    SetNumThreads(3); //几个线程

    vector<int> k{ 5, 7, 10, 12, 15, 17, 20, 22, 25 };
    int k_j = 0;

    for (int row =40; row <= 200; row += 20)
    {
        for (int col = 1; col <= 4; ++col)
        {
            cout << "\n维数: " << row << " 题目: " << col << endl;

            //第几小题 矩阵维度 汉明重量 两个计算模长度my_length 行 列
            run(row + col, row + 2, k[k_j], k_j, col);
        }
        ++k_j;
    }

    return 0;
}
