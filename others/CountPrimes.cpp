/* Leetcode 204.计数质数
 * 统计所有小于非负整数 n 的质数的数量。
 */
#include <vector>
using namespace std;

/* 厄拉多塞筛法
 * 如果2是质数, 那么2x2, 2x3, 2x4都不是质数
 * 同理3是质数, 3x3, 3x4都不是质数
 * 用排除法来统计质数
 */
class Solution {
public:
    int countPrimes(int n) {
        int cnt = 0;
        vector<bool> isPrime(n+1, true);
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) {
                cnt++;
                for (int j = i * i; j < n; j+=i) {
                    isPrime[j] = false;
                }
            }
        }
        return cnt;
    }
};