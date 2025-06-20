class Solution {
public:
    int countDigits(int n) {
        int original = n;
        int count = 0;

        while(n > 0){
            int digit = n % 10; // Use % to get last digit
            if(digit != 0 && original % digit == 0){
                count++;
            }
            n = n / 10; // Move to the next digit
        }

        return count;
    }
};
