/**
 * 870. 优势洗牌
 * 给定两个大小相等的数组 A 和 B，A 相对于 B 的优势可以用满足 A[i] > B[i] 的索引 i 的数目来描述。
 * 返回 A 的任意排列，使其相对于 B 的优势最大化。
 *
 * 示例 1：
 *  输入：A = [2,7,11,15], B = [1,10,4,11]
 *  输出：[2,11,7,15]
 * 示例 2：
 *  输入：A = [12,24,8,32], B = [13,25,32,11]
 *  输出：[24,32,8,12]
 *
 * 提示：
 *  (1)1 <= A.length = B.length <= 10000
 *  (2)0 <= A[i] <= 10^9
 *  (3)0 <= B[i] <= 10^9
 */
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

/**
 * 贪心: 田忌赛马
 * 对于每个下标idx, 用nums1中刚好大于nums2[idx]的值填充
 */
class Solution0 {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> v(n), ans(n, -1);
        /* iota: 不断value++来填充容器 */
        iota(v.begin(), v.end(), 0);
        /* 按照nums[i]的大小来对下标进行升序排序 */
        sort(v.begin(), v.end(), [&nums2](int i, int j) -> bool {
            return nums2[i] < nums2[j];
        });
        sort(nums1.begin(), nums1.end());
        for (int i = 0; i < n; i++) {
            int val = nums2[v[i]];
            /* 找到nums1中第一个大于val的值 */
            auto it = upper_bound(nums1.begin(), nums1.end(), val);
            if (it != nums1.end()) {
                /* 找到就填充到对应的index */
                ans[v[i]] = *it;
                *it = -1;
            } else {
                /* 找不到, 剩下的数字都不可能找到 */
                break;
            }
        }
        /* 如果ans中还有未被填充的位置
         * 从nums1中随便找未使用过数字填充进去
         * 因为这些位置都不可能使得nums1[i] > nums2[i] */
        for (int i = 0, j = 0; i < n; i++) {
            if (ans[i] == -1) {
                for (; j < n; j++) {
                    if (nums1[j] != -1) {
                        ans[i] = nums1[j];
                        nums1[j] = -1;
                        break;
                    }
                }
            }
        }
        return ans;
    }
};

/**
 * 更加优雅的做法
 * 优先beat nums2中的最大值, 因为这是最难beat的
 * 如果num1中的最大值无法beat nums2中的当前最大值
 * 则剩下的数字就可以随便填了
 */
class Solution1 {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> v(n), ans(n);
        iota(v.begin(), v.end(), 0);
        /* 按照nums[i]的大小来对下标进行降序排序 */
        sort(v.begin(), v.end(), [&nums2](int i, int j) -> bool {
           return nums2[i] > nums2[j];
        });
        sort(nums1.begin(), nums1.end());
        int low = 0, high = n-1;
        for (int i = 0; i < n; i++) {
            int val = nums2[v[i]];
            if (nums1[high] > val)
                ans[v[i]] = nums1[high--];
            else
                ans[v[i]] = nums1[low++];
        }
        return ans;
    }
};
