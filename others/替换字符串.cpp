/**
 * 面试题4
 * 请实现一个函数，将一个字符串中的每个空格替换成“%20”。
 * 例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
 * 要求原地做修改, 并且保证str已经分配了足够多的空间
 */

class Solution {
public:
    /* length为str的总容量 */
	void replaceSpace(char *str,int length) {
        if (str == nullptr || length <= 0)
            return;
        int origLength = 0; /* 字符串原来的长度 */
        int blankCnt = 0; /* 空格数目 */
        int i = 0;
        /* 统计原字符串长度和空格数目 */
        while (str[i] != '\0') {
            if (str[i] == ' ')
                blankCnt++;
            origLength++;
            i++;
        }
        /* 一个空格被替换成%20, 相当于多了两个字符
         * 替换后的字符串长度 = 原字符串长度 + 2 * 空格数目 */
        int newLength = origLength + 2 * blankCnt;
        if (newLength > length)
            return;
        /* 从后往前遍历 */
        int idxOfOriginal = origLength;
        int idxOfNew = newLength;
        /* idxOfOriginal == idxOfNew相等时, 就已经替换完毕了 */
        while (idxOfOriginal >= 0 && idxOfNew > idxOfOriginal) {
            if (str[idxOfOriginal] == ' ') {
                str[idxOfNew--] = '0';
                str[idxOfNew--] = '2';
                str[idxOfNew--] = '%';
            } else {
                str[idxOfNew] = str[idxOfOriginal];
                idxOfNew--;
            }
            idxOfOriginal--;
        }
	}
};