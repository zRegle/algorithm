/* 各种排序算法集合 */
#include <vector>
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