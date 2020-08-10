
/* Leetcode 215.数组中的第K个最大元素
 * 在未排序的数组中找到第k个最大的元素。
 * 请注意，你需要找的是数组排序后的第k个最大的元素，而不是第k个不同的元素。
 */
#include <vector>
#include <queue>
using namespace std;

/* 直接用优先级队列, 其实就是堆排序 */
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<>> q;
        for (int n : nums) {
            q.push(n);
            if (q.size() > k)
                q.pop();
        }
        return q.top();
    }
};


/* 基于快速排序
 * 快速排序每次都会确定pivot值的位置
 * 如果某次递归的pivot正好是倒数第k个数字, 那么直接返回即可
 */
class QuickSortBase {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums, 0, nums.size()-1, k);
    }
private:
    int quickSelect(vector<int>& nums, int left, int right, int k) {
        if (left < right) {
            int i = left, j = right, tmp = nums[left];
            while (i < j) {
                while (i < j && nums[j] >= tmp) j--;
                if (i < j) {
                    nums[i] = nums[j];
                    i++;
                }
                while (i < j && nums[i] <= tmp) i++;
                if (i < j) {
                    nums[j] = nums[i];
                    j--;
                }
            }
            /* pivot是倒数第count个 */
            int count = right - i + 1;
            if (count == k)
                return tmp;
            nums[i] = tmp;
            if (count > k)
                /* count比k大, 选择的pivot在k的左边, 递归右边继续找 */
                return quickSelect(nums, i+1, right, k);
            else
                /* count比k小, 选择的pivot在k的右边, 递归左边继续找
                 * 注意此时我们已经找到了数组中最大的count个数
                 * 现在要找第k大的数, 所以k要减去count用于下次递归
                 */
                return quickSelect(nums, left, i-1, k-count);
        }
        return nums[left];
    }
};

/* 基于最大堆的排序
 * 基于最大堆的排序从后往前排数字
 * 那么我们只需要排到倒数第k个即可
 */
class HeapSortBase {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int len = nums.size();
        /* 建立最大堆 */
        for (int i = len/2-1; i >= 0; i--)
            heap_down(i, nums, len-1);
        /* 注意终止条件, 排到第k个 */
        for (int i = len-1; i >= len-k; i--) {
            swap(nums[0], nums[i]);
            heap_down(0, nums, i-1);
        }
        return nums[len-k];
    }
private:
    void heap_down(int idx, vector<int>& nums, int length) {
        int cur = idx, child = 2 * cur + 1, tmp = nums[cur];
        for (; child <= length; cur = child, child = child * 2 + 1) {
            if (child < length && nums[child] < nums[child+1])
                child++;
            if (tmp >= nums[child])
                break;
            else {
                nums[cur] = nums[child];
                nums[child] = tmp;
            }
        }
    }
};