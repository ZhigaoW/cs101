// Define f(-1) == false and f(n) == true.
// Invariant(不变的): f(i-1) == false, f(j) == true.
int mysearch(int n, function<bool(int)> f){
        int i = 0, j = n;
        for(; i < j; ) {
        int h = i + (j - i) / 2;
        if (!f(h)) {
                // i ≤ h < j
                i = h + 1; // preserves f(i-1) == false
        } else {
                j = h; // preserves f(j) == true
        }
        }
        // i == j, f(i-1) == false, and f(j) (= f(i)) == true  =>  answer is i.
        // 在[0, i)条件f都为false,在[i, n)条件都为true
        return i; 
}

int main() {
        int target;
        vector<int> nums;

        // search lower bound
        int lowerbound = mysearch(n, [&nums, target](int i){
            return nums[i] >= target; 
        });

        // search upper bound
        int upperbound = mysearch(n, [&nums, target, n](int i) {
            return nums[i] > target;
        });
        upperbound = upperbound + 1;

        return 0;
}
