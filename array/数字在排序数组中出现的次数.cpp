/**
 * 剑指offer - 数字在排序数组中出现的次数
 * 统计一个数字在升序数组中出现的次数。
 * 示例:
 * 输入: nums = {1,2,3,3,3,3,4,5}, target = 3
 * 输出: 数字3出现了4次, 因此返回4
 */
#include <vector>
using std::vector;

/* 二次分查找数字第一次出现和最后一次出现的位置, 相减即可 */
class Solution {
public:
    int GetNumberOfK(vector<int>& data ,int k) {
        int first = getFirst(data, k);
        if (first == -1) return 0;
        int last = getLast(data, k);
        return last - first + 1;
    }

private:
    int getFirst(vector<int>& data, int k) {
        int left = 0, right = data.size()-1;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (data[mid] > k)
                right = mid - 1;
            else if (data[mid] < k)
                left = mid + 1;
            else {
                /* data[mid] = k */
                if (mid > 0) {
                    if (data[mid-1] == k)
                        /* 如果前一个数字也是k, 代表前半段在mid的左边 */
                        right = mid - 1;
                    else
                        /* 前一个数字不是k, 这就是第一个k出现的位置 */
                        return mid;
                } else {
                    return mid;
                }
            }
        }
        return -1;
    }

    int getLast(vector<int>& data, int k) {
        int left = 0, right = data.size()-1;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (data[mid] > k)
                right = mid - 1;
            else if (data[mid] < k)
                left = mid + 1;
            else {
                if (mid < data.size()-1) {
                    if (data[mid+1] == k)
                        /* 如果后一个数字也是k, 代表后半段在mid的右边 */
                        left = mid+1;
                    else
                        /* 后一个数字不是k, 这就是最后一个k出现的位置 */
                        return mid;
                } else {
                    return mid;
                }
            }
        }
        return -1;
    }
};