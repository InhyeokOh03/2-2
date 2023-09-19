#include <iostream>
using namespace std;

int main() {
    // "NEWS" 출력
    const char* sentence[] = { "HELLO CLASS", "GOOD NIGHT WORLD", "BE HAPPY" };

    cout << (char)*(sentence[1] + 5);
    cout << (char)(*(*(sentence + 2) + 1)); 
    cout << (char)(*(*(sentence + 1) + 11));
    cout << (char)(*(*sentence + 10));  

    return 0;
}