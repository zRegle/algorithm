/* Leetcode 854.相似度为K的字符串
 * 如果可以通过将A中的两个小写字母精确地交换位置K次得到与B相等的字符串，我们称字符串A和B的相似度为K
 * 给定两个字母异位词A和B ，返回A和B的相似度K的最小值。
 */
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int kSimilarity(string A, string B) {
		int k = 0;
		int len = A.length();
		queue<string> q;
		unordered_set<string> set;
		q.push(A); set.insert(A);
		while (!q.empty()) {
			int size = q.size();
			while (size--) {
				auto s = q.front(); q.pop();
				if (s == B)
					return k;
				int i = 0;
				while (s[i] == B[i]) i++;
				for (int j = i + 1; j < len; j++) {
                    /* 我们进行一次交换, 如果可以让至少一个字符正确地归位, 那么这次交换就是有意义的
					 * 只有当s[i] != B[i]和s[j] != B[j](字符s[i]和s[j]都不应该出现在该的位置)
                     * 并且刚好s[j] == B[i](字符s[j]应该出现为位置i时)时,
                     * 才进行交换, 使得s[j]出现在正确的位置, s更接近B, 否则交换是没意义的
                     */
					if (s[j] == B[j] || s[j] != B[i]) continue;
					swap(s[i], s[j]);
					if (set.find(s) == set.end()) {
						set.insert(s);
						q.push(s);
					}
					swap(s[i], s[j]);
				}
			}
			k++;
		}
		return 0;
    }
};