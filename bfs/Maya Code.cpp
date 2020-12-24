#include <iostream>
#include <queue>
#include <string>
#include <map>
using namespace std;

/*
 * 给定一个只包含0,1,2的字符串, 每次只能移动相邻的两位
 * 问最少需要多少步能够使字符串包含"2012"
 * 输入: 第一行N表示字符串长度
 *       第二行字符串
 * 输出: 最少的步数, 若无论移动多少位都不可能, 则返回-1
 *
 * 思路: 如何用队列bfs遍历所有可能性(QUEUE)+如何判别并标示某串是否访问过(MAP)+
 * 如何记录某串已经交换字符的次数(MAP)+子串2012是否存在
 */

string swap(string& str, int i, int j) {
    string res = str;
    char tmp = res[i];
    res[i] = res[j];
    res[j] = tmp;
    return res;
}

int bfs(string& str, int length) {
    if (str.find("2012") != string::npos) return 0;
    queue<string> q;
    q.push(str);
    map<string, int> map;
    map.insert(pair<string,int>(str, 0));
    while (!q.empty()) {
        string s = q.front();
        q.pop();
        for (int i = 0; i < length - 1; ++i) {
            int count = map[s];
            string newStr = swap(s, i, i + 1);
            if (newStr.find("2012") != string::npos) 
                return count + 1;
            if (map.find(newStr) == map.end()) {
                q.push(newStr);
                map.insert(pair<string, int>(newStr, count + 1));
            }
        }
    }
    return -1;
}

int main() {
    int length;
    string s;
    cin>>length>>s;
    cout<<bfs(s, length)<<endl;
    return 0;
}