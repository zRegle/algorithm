#include <iostream>
#include <vector>
using namespace std;

/**
 * leetcode 4. Median of Two Sorted Arrays
 * 给定两个升序数组, 找出这两个数组合并后的中位数
 * 例如:
 * A = [1, 2]
 * B = [3, 4]
 * The median is (2 + 3)/2 = 2.5
 *
 * 思路:
 * 很明显, 合并两个数组再排序求中位数时间和内存肯定会爆
 * 所以需要别的方法来求.
 * 
 * 我们将A, B两个数组各拆成两半
         left_part          |        right_part
 * A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
 * B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]
 * 如果我们可以确保
 * 1) len(left_part) == len(right_part)
 * 2) max(left_part) <= min(right_part)
 * 那么中位数 = (max(left_part) + min(right_part))/2.
 * 要满足这两个要求, 我们只需要满足
 * 1) i+j == (m+n)/2
 * 2) A[i-1] <= B[j] 且 B[j-1] <= A[i]
 */

class Solution {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        int m = A.size();
        int n = B.size();
        if (m > n) {
            /* 因为0 <= i <= m, 且j = (m + n + 1) / 2 - i
             * 为了保证0 <= j <= n, 必须保证m <= n
             * 因此如果m > n, 交换两个数组 */
            return findMedianSortedArrays(B,A);
        }
        //i是A的分割位, j是B的分割位
        int iMin = 0, iMax = m;
        /* m + n + 1是为了合并m + n是偶数和m+n是奇数两种情况
         * 如果m + n是奇数, 保证左半部分的长度比右半部分的长度大1, 即
         * i + j = m - i + n - j + 1, 即j = (m + n + 1) / 2
         * 如果m + n是偶数, 因为用的是int型, +1也不会影响结果 */
        int halfLen = (m + n + 1) / 2;
        while (iMin <= iMax) {
            int i = (iMin + iMax) / 2;	//每次都从中间开始分割
            int j = halfLen - i;	//确保i+j == (m+n)/2
            if (i < iMax && B[j-1] > A[i]){
                iMin++; // i is too small
            }
            else if (i > iMin && A[i-1] > B[j]) {
                iMax--; // i is too big
            }
            else { // i is perfect
                int maxLeft = 0;
                if (i == 0)
                    //A数组最小的元素都比B数组的左半部分大, max_left直接取B[j-1] 
                    maxLeft = B[j-1]; 
                else if (j == 0)
                    //B的最小元素都比A数组的左半部分大, max_left直接取A[i-1]
                    maxLeft = A[i-1]; 
                else  
                    maxLeft = max(A[i-1], B[j-1]); 
                if ((m + n) & 1)  return maxLeft; //如果是奇数, max_left就是中位数

                int minRight = 0;
                if (i == m)
                    //A数组的最大元素都比B数组的右半部分的最小元素要小, min_right直接取B[j]  
                    minRight = B[j]; 
                else if (j == n)
                    //B数组的最大元素都比A数组的右半部分的最小元素要小, min_right直接取A[i]  
                    minRight = A[i];
                else  
                    minRight = min(B[j], A[i]); 

                return (maxLeft + minRight) / 2.0;
            }
        }
        return 0.0;
    }
};