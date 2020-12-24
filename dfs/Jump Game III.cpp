/**
 * 1306. 跳跃游戏 III
 * 这里有一个非负整数数组 arr，你最开始位于该数组的起始下标 start 处。
 * 当你位于下标 i 处时，你可以跳到 i + arr[i] 或者 i - arr[i]。
 * 请你判断自己是否能够跳到对应元素值为 0 的 任一 下标处。
 * 注意，不管是什么情况下，你都无法跳到数组之外。
 *  
 * 示例 1：
 * 输入：arr = [4,2,3,0,3,1,2], start = 5
 * 输出：true
 * 解释：
 * 到达值为 0 的下标 3 有以下可能方案： 
 * 下标 5 -> 下标 4 -> 下标 1 -> 下标 3 
 * 下标 5 -> 下标 6 -> 下标 4 -> 下标 1 -> 下标 3 
 */
#include <vector>
#include <queue>
using namespace std;

//bfs方法参考bfs文件夹

//弱智题, 基础中的基础
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        if (arr[start] == 0) return true;
        int back = start - arr[start];
        int front = start + arr[start];
        arr[start] = -1;
        if (back >= 0 && arr[back] != -1) {
            if (canReach(arr, back))
                return true;
        }
        if (front < arr.size() && arr[front] != -1) 
            return canReach(arr, front);
        return true;
    }
};