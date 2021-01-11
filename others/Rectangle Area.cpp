/* Leetcode 223.矩形面积
 * 在二维平面上计算出两个由直线构成的矩形重叠后形成的总面积。
 * 每个矩形由其左下顶点和右上顶点坐标表示。
 * 示例:
 *  输入: -3, 0, 3, 4, 0, -1, 9, 2
 *  输出: 45
 */
#include <algorithm>
using namespace std;

/* 记两个矩形分别为矩形A和B */
class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        /* 总是让矩形A靠最左边 */
        if (A > E) {
            return computeArea(E, F, G, H, A, B, C, D);
        }
        /* 先分别计算两者的面积 */
        int a1 = (C - A) * (D - B), a2 = (G - E) * (H - F);

        /* 两者没有相交的部分
         * 分别为:
         * 1.A矩形和B矩形左右分开
         * 2.A矩形在B矩形上面
         * 3.A矩形在B矩形下面
         */
        if (C <= E || B >= H || D <= F)
            return a1 + a2;

        /* 两者有相交的部分, 记为duplicate
         * 它的左边界取A和B的最大值
         * 右边界取A和B的最小值
         * 上边界取A和B的最小值
         * 下边界取A和B的最大值
         */
        int up = min(D, H);
        int left = max(A, E);
        int right = min(C, G);
        int down = max(B, F);

        int duplicate = (right - left) * (up - down);
        /* 先减后加是为了防止溢出 */
        return a1 - duplicate + a2;
    }
};

/* my solution */
class Solution1 {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        if (A > E) {
            return computeArea(E, F, G, H, A, B, C, D);
        }
        int a1 = getArea(A, B, C, D);
        int a2 = getArea(E, F, G, H);
        if (a1 == 0 || a2 == 0)
            /* 如果两者有一个面积为0, 直接返回 */
            return a1 + a2;
        if (C <= E || B >= H || D <= F) 
            return a1 + a2;
        int duplicate = 0;
        /* 如果B矩形的右边界在A矩形右边界的右边
         * 那么相交的长度就是B矩形的长
         * 如果不是, 相交长度就是A矩形右边界横坐标 - B矩形左边界横坐标
         */
        int length = G <= C ? G - E : C - E;
        int width = 0;
        if (F <= B && B <= H && H <= D) {
            /* B矩形的上部分与A矩形相交, 并没有超出A矩形的上边界 */
            width = H - B;
        } else if (B <= F && H <= D) {
            /* A矩形的宽包含了B矩形的宽 */
            width = H - F;
        } else if (B <= F && F <= D && D <= H) {
            /* B矩形的下部分与A矩形相交, 并没有超出A矩形的下边界 */
            width = D - F;
        } else if (F < B && D < H) {
            /* B矩形的宽包含了A矩形的宽 */
            width = D - B;
        }
        duplicate = length * width;
        return a1 - duplicate + a2;
    }

    /* 计算矩形面积 */
    inline int getArea(int a, int b, int c, int d) {
        int length = c - a, width = d - b;
        return length * width;
    }
};