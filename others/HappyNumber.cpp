/* Leetcode 202.快乐数
 * 编写一个算法来判断一个数 n 是不是快乐数。
 * 「快乐数」定义为：
 * 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和，然后重复这个过程直到这个数变为 1，
 * 也可能是无限循环但始终变不到 1。如果可以变为 1，那么这个数就是快乐数。
 */

/* 先说结论: 如果一个数不是快乐数, 那么它必定会陷入循环
 * 首先假设平方和的结果不会越来越大, 那么就相当于平方和结果有一个范围, 只要不是快乐数, 必定会在这个范围里循环
 * 接着说明为什么平方和结果不会越来越大:
 *    9 ->  81
 *   99 -> 162
 *  999 -> 243
 * 9999 -> 324
 * 可以看到, 当数字位数一定, 对应的最大数字的平方和都比本身要小, 比如999 > 243
 * 那么其他小于999的数字的平方和也一定小于243
 * 严谨的证明在这:
 * https://leetcode-cn.com/problems/happy-number/solution/kuai-le-de-zhi-shi-dian-zeng-jia-liao-by-sweetiee/
 * 
 * 当我们明白这点后, 就可以用判断链表是否有环的方法来解决即可
 */
class Solution {
public:
    bool isHappy(int n) {
        int fast = n, slow = n;
        do {
            fast = squareSum(squareSum(fast));
            slow = squareSum(slow);
        } while (fast != 1 && slow != fast);
        return fast == 1;
    }

private:
    int squareSum(int n) {
        int sum = 0, digit;
        while (n) {
            digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        return sum;
    }
};