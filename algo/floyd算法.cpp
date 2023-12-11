#include <bits/stdc++.h>
using namespace std;
/**
 * Floyd算法用来求任意两点之间的最短路
 * 复杂度高n3, 但是常数小, 容易实现
 * 适用于任何图, 不管有向无向边权正负, 但是最短路必须存在, 不能有负环
 * f[k][x][y]表示只允许经过[0, k),此时节点x到y的最短路长度
*/
int main(){
    const int N = 101;
    int dis[N][N];
    // 初始化dis矩阵
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j) dis[i][j] = 0;
            else dis[i][j] = INT_MAX;
        }
    }
    // 初始化边权 
    
    // 开始floyd迭代, 数组压缩
    for (int k = 0; k < N; ++k) {
        for (int x = 0; x < N; ++x) {
            for (int y = 0; y < N; ++y) {
                dis[x][y] = min(dis[x][y],  dis[x][k] + dis[k][y]);
            }
        }
    }
}