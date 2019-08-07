/* Leetcode 60 第K个排列
给出集合 [1,2,3,…,n]，其所有元素共有 n! 种排列。
按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：
"123"
"132"
"213"
"231"
"312"
"321"

示例 1:
输入: n = 3, k = 3
输出: "213"
 */

#include <vector>
#include <numeric>
using namespace std;

//朴素的暴力解法, 算出前K个排列, 返回第K个
class Solution {
public:
    string getPermutation(int n, int k) {
        vector<char> nums(n);
        iota(nums.begin(), nums.end(), '1');
        vector<bool> used(nums.size(), false);
        vector<char> tmp;
        int cnt = 0;
        string s;
        permute(nums, used, tmp, cnt, k, s);
        return s;
    }

private:
    void permute(vector<char>& nums, vector<bool>& used, vector<char>& tmp, int& cnt, int k, string& s) {
        if (cnt == k) return;
        int size = nums.size();
        if (tmp.size() == size) {
            cnt++;
            if (cnt == k) {
                for (char n : tmp)
                    s += n;
            }
        } else {
            for (int i = 0; i < size; i++) {
                if (!used[i]) {
                    used[i] = true;
                    tmp.push_back(nums[i]);
                    permute(nums, used, tmp, cnt, k, s);
                    tmp.pop_back();
                    used[i] = false;
                }
            }
        }
    }
};

//我们其实不需要生成前K个序列, 通过适当的剪枝可以增加效率
//有n个数字, 以'1'开头的排列有(n-1)!个, 以'12'开头的有(n-2)!个
//当我们DFS到深度为i时, 如果k > (n-i)!, 那么我们知道第k个排列不在这棵子树里, 我们可以直接跳过
class Solution2 {
public:
    string getPermutation(int n, int k) {
        vector<char> nums(n);
        iota(nums.begin(), nums.end(), '1');
        vector<bool> used(nums.size(), false);
        vector<char> tmp;
        string s;
        permute(nums, used, tmp, 0, k, s);
        return s;
    }

private:
    //计算阶乘
    int factorial(int n) {
        if (n == 1 || !n)
            return 1;
        else
            return n * factorial(n-1);
    }

    void permute(vector<char>& nums, vector<bool>& used, vector<char>& tmp, int depth, int k, string& s) {
        int n = nums.size();
        if (depth == n) {
            for (char num : tmp)
                s += num;
        } else {
            int ps = factorial(n-depth-1);  //当前这棵子树里有多少个叶子节点, 即多少个排列
            for (int i = 0; i < n; i++) {
                if (used[i]) continue;
                if (ps < k) {   //叶子节点不够
                    k -= ps;    //跳过这棵子树
                    continue;
                }
                used[i] = true;
                tmp.push_back(nums[i]);
                permute(nums, used, tmp, depth+1, k, s);
                //不用回溯, 因为我们只要一个叶子节点就可以了
            }
        }
    }
};

//依照第二种的方法, 我们可以直接通过阶乘计算结果, 不用DFS
class Solution3 {
public:
    string getPermutation(int n, int k) {
        vector<char> nums(n);
        iota(nums.begin(), nums.end(), '1');
        vector<int> factorial(n+1);
        factorial[0] = 1;
        for (int i = 1; i <= n; i++) 
            factorial[i] = factorial[i-1] * i;
        k--;
        string s;
        for (int i = 1; i <= n; i++) {
            int idx = k / factorial[n-i];
            s += nums[idx];
            nums.erase(nums.begin() + idx);
            k -= idx * factorial[n-i];
        }
        return s;
    }
};