/* Leetcode 260.只出现一次的数字 III
 * 给定一个整数数组 nums，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。
 * 示例 :
 *  输入: [1,2,1,3,2,5]
 *  输出: [3,5]
 */
#include <vector>
using namespace std;

/* 小白哈希表就不说了, 直接上掩码版 */
class Solution {
public:
	/* 设结果为x, y */
    vector<int> singleNumber(vector<int>& nums) {
		int mask = 0;
		/* 全部异或, 最后就是x ^ y */
		for (int n : nums)
			mask ^= n;

		/* 获取mask最右边的1, 并且将其他bit置0. 那么这个1来自x或者y, 这里假设为x
		 * (实际上, 我们可以随便挑mask中任意的一个1, 然后将其他bit清零也可以)
		 */
		int diff = mask & (-mask);

		/* 将所有在这个bit为1的数字异或, 最后剩下的必定为x */
		int x = 0;
		for (int n : nums)
			if (n & diff)
				x ^= n;
		
		/* 找到x后, 只需要 x ^ mask就能还原y */
		return vector<int>{x, x ^= mask};
    }
};