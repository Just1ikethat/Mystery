#include <iostream>  
#include <fstream>//ofstream类的头文件
using namespace std;  
//可选数字  
int candidate[] = {1,2,3,4,5,6,7,8,9};  
//标记这个空格是否为原始数据  
int g_a[9][9] = {0};  
//打印函数  
void print( int (*a)[9] )  
{  
	ofstream mycout("sudoku.txt");   
    for( int i = 0; i < 9; i++ )  
    {  
        for( int j = 0; j < 9; j++ )  
        {  
           mycout<<a[i][j]<<' ';
        }  
        mycout << endl;  
    }  
    mycout.close(); 
}  
//判断可以放哪些数字  
void ConfirmCandidate( int (*a)[9], int i, int j )  
{  
    for( int i_candidate = 0; i_candidate < 9; i_candidate++ )  
        candidate[i_candidate] = i_candidate+1;  
    for( int colm = 0; colm < 9; colm++ )  
    {  
        if( a[i][colm] != 0 )  
            candidate[a[i][colm]-1] = 0;  
    }  
    for( int line = 0; line < 9; line++ )  
    {  
        if( a[line][j] != 0 )  
            candidate[a[line][j]-1] = 0;  
    }  
    for( int line = i/3*3; line < i/3*3+3; line++ )  
    {  
        for( int colm = j/3*3; colm < j/3*3+3; colm++ )  
            if( a[line][colm] != 0 )  
                candidate[a[line][colm]-1] = 0;  
    }  
}  
//标记每个空格位置  
void TotalNumbers( int (*a)[9], int i, int j )  
{  
    for( int line = 0; line < i; line++ )  
    {  
        for( int colm = 0; colm < j; colm++ )  
            if( a[line][colm] == 0 )  
            {  
                g_a[line][colm] = 1;  
            }  
    }  
}  
//判断所填数字是否正确  
bool JudgeValue( int (*a)[9],int i, int j )  
{  
    //同一行有无重复数字  
    for( int colm = 0; colm < 9; colm++ )  
    {  
        if( a[i][colm] == a[i][j] && j != colm )  
            return false;  
    }  
    //同一列有无重复数字  
    for( int line = 0; line < 9; line++ )  
    {  
        if( a[line][j] == a[i][j] && i != line )  
            return false;  
    }  
    //一个3*3的方格内有无重复数字  
    for( int line = i/3*3; line < i/3*3+3; line++ )  
    {  
        for( int colm = j/3*3; colm < j/3*3+3; colm++ )  
            if( a[line][colm] == a[i][j] && i != line && j != colm )  
                return false;  
    }  
    return true;  
}  
//判断是否成功  
bool success( int(*a)[9], int i, int j )  
{  
    if( i < 0 || j < 0 ) return false;  
    int line = i;  
    int colm = j;  
    for( ; line < 9; line++, colm = 0 )  
    {  
        for( ; colm < 9; colm++ )  
        {  
            //cout << "line = " << line <<"  colm = " << colm << endl;  
            //if( colm == 8 && line == 8 ) return true;  
            if( a[line][colm] != 0 && g_a[line][colm] == 0 ) continue;  
            ConfirmCandidate(a, line, colm);  
            for(int c = 0; c < 9; c++ )  
            {  
                if( candidate[c] > a[line][colm] )  
                {  
                    a[line][colm] = candidate[c];  
                    /* 
                    *TEST 
                    *测试可选数字 
                    */  
                    /* 
                    for(int i = 0; i < 9; i++ ) 
                        cout << candidate[i] << " "; 
                    cout << endl << endl; 
                    */  
                    //print(a);  
                    //判断放入的值是否正确  
                    bool bRet = JudgeValue( a, line, colm );  
                    if(!bRet)   
                    {  
                        //cout << "bRet  is  false" << endl;  
                    }  
                    else{  
                        //cout << "bRet  is  true" << endl;  
                        break;  
                    }  
                }  
                else if( c == 8 && candidate[c] <= a[line][colm] )  
                {  
                    //cout << "line = " << line <<"  colm = " << colm << endl;  
                    int set_colm = 8;  
                    a[line][colm] = 0;  
                    if( colm == 0 )  
                    {  
                        while( g_a[line-1][set_colm] == 0)  
                        {  
                            if( set_colm == 0)   
                            {  
                                line--;  
                                set_colm = 8;  
                            }  
                            else set_colm--;  
                        }  
                        return success( a, line - 1, set_colm);  
                    }  
                    else{  
                        while( g_a[line][colm-1] == 0)  
                        {  
                            if( colm-1 == 0)   
                            {  
                                line--;  
                                colm = 9;  
                            }  
                            else colm--;  
                        }  
                        return success( a ,line, colm-1 );  
                    }  
                }  
            }  
        }  
    }  
    return true;  
}  
  
int main()  
{  
    //initialization  
/* 
    int a[9][9] = { 
        {8,0,0,0,0,0,0,0,0}, 
        {0,0,3,6,0,0,0,0,0}, 
        {0,7,0,0,9,0,2,0,0}, 
        {0,5,0,0,0,7,0,0,0}, 
        {0,0,0,0,4,5,7,0,0}, 
        {0,0,7,1,0,0,0,3,0}, 
        {0,0,1,0,0,0,0,6,8}, 
        {0,0,8,5,0,0,0,1,0}, 
        {0,9,0,0,0,0,4,0,0} 
    }; 
*/  
    //test  
    int t;
	cin>>t; 
	while(t--)
	{
    int a[9][9] = {  
        {0,5,0,0,0,0,0,0,0},  
        {0,7,3,1,0,0,2,5,0},  
        {1,0,2,5,0,0,7,6,0},  
        {0,0,0,0,0,8,0,2,0},  
        {0,8,0,0,2,1,0,0,0},  
        {0,3,4,7,6,0,8,0,0},  
        {0,0,0,6,8,0,0,4,1},  
        {0,0,0,0,0,7,0,0,0},  
        {0,0,0,0,1,4,0,0,0}  
    };  
  
    TotalNumbers( a, 9, 9 );  
    success( a, 0, 0 );  
    print(a); 
	}
}  
