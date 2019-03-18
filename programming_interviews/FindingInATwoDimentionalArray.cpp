#include <vector>

using namespace std;

class FindingInATwoDimentionalArray {
public:
    vector<vector<int> > input_array;
    const static int col_d = 0, row_d = 1;
    int cur_d, cur_row, cur_col;

    FindingInATwoDimentionalArray(vector<vector<int> > input_array) {
        this->input_array = input_array;
    }

    bool Find(int target, vector<vector<int> > array) {
        input_array = array;
        int rows = input_array.size();
        int cols = input_array[0].size();
        cur_row = 0; cur_col = cols - 1;
        bool found = false;
        while (cur_row < rows && cur_col >= 0) {
            int low, high, idx;

            // col scan
            cur_d = col_d; low = cur_row; high = rows;
            idx = b_search(target, low, high);
            if (idx < low) {
                cur_col--;
            }
            else if (idx >= high) {
                return false;
            }
            else {
                if (input_array[idx][cur_col] == target) {
                    return true;
                }
                else {
                    cur_row = idx;
                }
            }
            if (!(cur_row < rows && cur_col >= 0)) return false;

            // row scan
            cur_d = row_d;
            low = 0; high = cur_col + 1;
            idx = b_search(target, low, high);
            if (idx < low) {
                return false;
            }
            else if (idx >= high) {
                cur_row--;
            }
            else {
                if (input_array[cur_row][idx] == target) {
                    return true;
                }
                else {
                    cur_col = idx - 1;
                }
            }
        }
        return found;
    }

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

    int get_element(int idx) {
        if (cur_d == row_d) return input_array[cur_row][idx];
        else                return input_array[idx][cur_col];
    }

};
