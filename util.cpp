// [lo, hi]
int partition(Comparable[] a, int lo, int hi) {
    Comparable v = a[lo];
    while (lo < hi) {
        while (lo < hi && less(v, a[hi]))   hi--;
        a[lo] = a[hi];
        while (lo < hi && less(a[lo], v))   high--;
        a[hi] = a[lo];
    }
    a[lo] = v;
    return lo;
}

// [low_bound, high_bound)
int b_search(int target, int low_bound, int high_bound) {
    int low = low_bound, high = high_bound - 1;
    while(low <= high) {
        int mid = (low + high) / 2;
        int mid_val = get_element(mid);
        if (target < mid_val)      high = mid - 1;
        else if (target > mid_val) low = mid + 1;
        else                       return mid;
    }
    if (high == low_bound - 1)  return high;
    else if (low == high_bound) return low;
    else                        return low;
}