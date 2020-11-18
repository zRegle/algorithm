/* Leetcode 278. 第一个错误的版本
 * 你是产品经理，目前正在带领一个团队开发新的产品。不幸的是，你的产品的最新版本没有通过质量检测。
 * 由于每个版本都是基于之前的版本开发的，所以错误的版本之后的所有版本都是错的。
 * 假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。
 * 你可以通过调用 bool isBadVersion(version) 接口来判断版本号 version 是否在单元测试中出错。
 * 实现一个函数来查找第一个错误的版本。你应该尽量减少对调用 API 的次数。
 * 示例:
 * 给定 n = 5，并且 version = 4 是第一个错误的版本。
 * 调用 isBadVersion(3) -> false
 * 调用 isBadVersion(5) -> true
 * 调用 isBadVersion(4) -> true
 * 所以，4 是第一个错误的版本。
 */

/* 没啥好说的, 二分搜索 */
class Solution {
public:
    Solution(int x) {
        first = x;
    }

    int firstBadVersion(int n) {
        unsigned int left = 1, right = n;
        while (left < right) {
            /* 位运算求平均值
             * 本质上可以分为两部分计算
             * 我们不妨设left = x + y, right = x + z
             * 第一部分left & right就是x
             *  (left和right对应bit都为1代表的数字)
             * 第二部分left ^ right就是y + z
             *  (left和right对应bit不相同代表的数字相加)
             * 平均值就是x + (y + z) / 2
             */
            int mid = (left & right) + ((left ^ right) >> 1);
            if (isBadVersion(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

private:
    int first;
    bool isBadVersion(int version) {
        return version >= first;
    }
};