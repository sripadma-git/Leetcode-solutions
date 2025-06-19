class Solution {
public:
    bool isPalindrome(int n) {
     if (n < 0) return false;  // Negative numbers are not palindromes

    int original = n;
    long long reversed = 0;

    while (n > 0) {
        int digit = n % 10;
        reversed = reversed * 10 + digit;

        // Optional check to prevent overflow
        if (reversed > INT32_MAX) return false;

        n = n / 10;
    }

    return reversed == original;
}

};