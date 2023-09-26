#include <iostream>
using namespace std;
     
int nOddSum(int n)
{
    if (n <= 0) {
       return 0;
    }
    if (n % 2 == 0) {
        return nOddSum(n-1);
    }
    else {
        int res = n + nOddSum(n - 2); 
        return res;
    } 
}

int main() {
    int n = 3;
    int sum = nOddSum(n);
    cout << "Sum of Odd Numbers = " << sum; return 0;
}

/*
Line 6: Replace if (n == 0) -> if (n <= 0)
Line 7: Replace return 1; -> return 0;
Line 10: Replace return n; -> return nOddSum(n-1);
Line 13: Replace int res = n + nOddSum(n - 1); -> int res = n + nOddSum(n - 2); 
*/