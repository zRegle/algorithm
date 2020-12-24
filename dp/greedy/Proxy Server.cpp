#include <iostream>
#include <string>
using namespace std;

/* 给定一系列代理服务器的IP地址和服务器的IP地址
 * 要求用代理服务器按顺序访问服务器, 代理服务器的IP不能与服务器的IP相同
 * 给出切换代理服务器最少的次数, 若无法满足要求, 则返回-1
 * 例子:
 * 3(代理服务器的个数)
 * 166.111.4.100 (代理服务器的IP)
 * 162.105.131.113
 * 202.112.128.69
 * 6(服务器的个数)
 * 72.14.235.104 (服务器的IP)
 * 166.111.4.100
 * 207.46.19.190
 * 202.112.128.69
 * 162.105.131.113
 * 118.214.226.52
 * 
 * 输出: 3
 *
 * 思路: 贪心算法, 每次选出能够走最长的代理服务器
 */

int find(string* proxy, string* server, int proxy_num, int server_num) {
    if (proxy_num == 1) {
    	//若代理服务器只有一个, 并且服务器列表中含有与其相等的IP地址, 返回-1
        for (int i = 0; i < server_num; ++i) {
            if (proxy[0] == server[i])
                return -1;
        }
        return 0;
    } else {
        int _switch = 0;
        int last_proxy = -1, last_server = 0, cur_max_server = 0;
        //上一次用的代理服务器, 上一次停住的服务器, 当前代理服务器能够走到的最远的服务器
        while (true) {
            int max = 0;	//能够走最长的步数
            //每次选出能够走最长的代理服务器
            for (int cur_proxy = 0; cur_proxy < proxy_num; ++cur_proxy) {
                if (cur_proxy == last_proxy) continue;
                int count = 0;
                int cur_server = last_server;   //每次从上一次能够走到最远的服务器开始
                while (proxy[cur_proxy] != server[cur_server] && cur_server < server_num) {
                    count++;
                    cur_server++;
                }
                if (cur_server == server_num) return _switch;
                if (count > max) {
                    max = count;
                    last_proxy = cur_proxy;
                    cur_max_server = cur_server;
                }
            }
            last_server = cur_max_server;	//挑好了能够走到最远的服务器了
            _switch++;	//切换次数+1
        }
    }
}

int main() {
    int proxy_num = -1, server_num = -1;
    cin>>proxy_num;
    string* proxy = new string[proxy_num];
    for (int i = 0; i < proxy_num; ++i) {
        cin>>proxy[i];
    }
    cin>>server_num;
    string* server = new string[server_num];
    for (int j = 0; j < server_num; ++j) {
        cin>>server[j];
    }
    cout<<find(proxy, server, proxy_num, server_num);
    delete[] proxy;
    delete[] server;
    return 0;
}