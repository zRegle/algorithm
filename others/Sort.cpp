/* 各种排序算法集合 */
#include <vector>
#include <algorithm>
using namespace std;

/* 归并排序 */
vector<int> merge(vector<int>& a, vector<int>& b) {
    int l1 = a.size(), l2 = b.size();
    vector<int> v(l1 + l2);
    int i = 0, j = 0, idx = 0;
    while (i < l1 && j < l2) {
        if (a[i] < b[i]) {
            v[idx] = a[i];
            i++;
        } else {
            v[idx] = b[j];
            j++;
        }
        idx++;
    }
    while (i < l1)
        v[idx++] = a[i++];
    while (j < l2)
        v[idx++] = b[j++];
    return v;
}

vector<int> merge_sort(int left, int right, vector<int>& nums) {
    if (left < right) {
        int mid = (left + right) / 2;
        auto a = merge_sort(left, mid, nums);
        auto b = merge_sort(mid+1, right, nums);
        return merge(a, b);
    }
    return {nums[left]};
}

/* 快速排序
 * 选择一个基准值, 将大于它的放到它右边, 小于它的放在左边
 */
void quick_sort_1(int left, int right, vector<int>& nums) {
    if (left < right) {
        int i = left, j = right;
        int tmp = nums[left]; /* nums[left]已经挖空, 找数填 */
        while (i < j) {
            while (i < j && nums[j] >= tmp)
                j--;
            if (i < j) {
                /* 填nums[i]的坑
                 * nums[j]已经挖空, 找数填
                 */
                nums[i] = nums[j];
                i++;
            }
            while (i < j && nums[i] <= tmp)
                i++;
            if (i < j) {
                nums[j] = nums[i];
                j--;
            }
        }
        /* 填最后一个坑, 此时i = j */
        nums[i] = tmp;
        quick_sort_1(left, i-1, nums);
        quick_sort_1(i+1, right, nums);
    }
}

void quick_sort_2(int left, int right, vector<int>& nums) {
    if (left < right) {
        int pivot = nums[left];
        int start = left, end = right;
        while (left < right) {
            /* 从后往前找, 找到第一个小于pivot的数字 */
            while (left < right && nums[right] >= pivot) right--;
            /* 从前往后找, 找到第一个大于pivot的数字 */
            while (left < right && nums[left] <= pivot) left++;
            if (left >= right) break;
            /* 交换这两个数字 */
            swap(nums[left], nums[right]);
        }
        /* pivot归位 */
        swap(nums[start], nums[left]);
        quick_sort_2(start, left-1, nums);
        quick_sort_2(left+1, end, nums);
    }
}

/* 堆排序
 * 先将数组构造成一个最大堆(根节点的值大于它孩子节点的值)
 * 然后不断pop堆顶元素(pop之后要调整最大堆), 从后往前地填入到数组里
 */
void heap_down(int cur, vector<int>& nums, int length) {
    int child = 2 * cur + 1;
    for (; child <= length; cur = child, child = child * 2 + 1) {
        if (child < length && nums[child] < nums[child+1])
            /* 挑选左右孩子中较大的值 */
            child++;
        if (nums[cur] >= nums[child])
            break;
        else {
            /* 较大的孩子up, 父节点down */
            swap(nums[cur], nums[child]);
        }
    }
}

void heap_sort(vector<int>& nums) {
    int len = nums.size();
    /* 从最后一个非叶子节点开始, 初始化为大顶堆 */
    for (int i = len/2-1; i >= 0; i--)
        heap_down(i, nums, len-1);
    for (int i = len-1; i > 0; i--) {
        swap(nums[0], nums[i]);
        heap_down(0, nums, i-1);
    }
}

/* 计数排序 —— 时间O(n), 空间O(n)
 * 统计各个数字出现的次数
 * 往结果数组中填数字 
 */
vector<int> countSort(vector<int>& arr) {
    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());
    /* 数组中元素范围是[minVal, maxVal], 建立哈希表 */
    vector<int> cnt(maxVal - minVal + 1);
    /* 统计元素出现的次数 */
    for (int x : arr) {
        cnt[x - minVal]++;
    }
    int n = arr.size();
    vector<int> res(n);
    int idx = 0;
    /* 往结果数组中填数字 */
    for (int i = 0; i < cnt.size(); i++) {
        while (cnt[i]--) 
            res[idx++] = i + minVal;
    }
    return res;
}

/* 插入排序:
 * 考察元素i, 在已经排好序的[0, i-1]区间中寻找合适的位置插入 */
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    /* 从第二个元素开始遍历, 区间[0,0]是已经排好序的 */
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) {
            /* 在[0, i-1]区间寻找适合arr[i]插入的位置 */
            int tmp = arr[i];
            int j;
            /* j从i-1开始 */
            for (j = i-1; j >= 0; j--) {
                if (arr[j] > tmp)
                    /* arr[j] > tmp, arr[j]需要后移 */
                    arr[j+1] = arr[j];
                else
                    break;
            }
            /* 找到合适的位置, 插入 */
            arr[j+1] = tmp;
        }
    }
}