#include <iostream>
#include <string>
using namespace std;

/* leetcode 72
 * Description:
 * Given two words word1 and word2, find the minimum number of operations required to convert word1 to word2.
 * You have the following 3 operations permitted on a word:
 * 1.Insert a character
 * 2.Delete a character
 * 3.Replace a character
 */

int minDistance(string& word1, string& word2) {
    int s1 = word1.length(), s2 = word2.length();
    int** dp = new int*[s1+1];
    for (int i = 0; i <= s1; ++i) {
        dp[i] = new int[s2+1]();
        dp[i][0] = i;
    }
    for (int i = 0; i <= s2; ++i) {
        dp[0][i] = i;
    }
    for (int i = 1; i <= s1; ++i) {
        for (int j = 1; j <= s2; ++j) {
            if (word1[i-1] == word2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else {
                //source:abcde, target: ghijk

                //abcde -> ghij, insert 'k'
                int insert = dp[i][j-1] + 1;
                //abcde -> ghijke, delete 'e'
                int _delete = dp[i-1][j] + 1;
                //abcde -> ghije, replace 'e' with 'k'
                int replace = dp[i-1][j-1] + 1;

                dp[i][j] = min(insert, min(_delete, replace));
            }
        }
    }
    int min_value = dp[s1][s2];
    for (int i = 0; i <= s1; ++i) {
        delete[](dp[i]);
    }
    delete[](dp);
    return min_value;
}

int main() {
	string w1 = "intention";
	string w2 = "execution";
	cout<<minDistance(w1, w2)<<endl;
	return 0;
}