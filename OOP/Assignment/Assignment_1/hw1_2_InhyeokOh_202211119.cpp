#include <iostream>
#include <cstring>

using namespace std;

void reverse(const char* str) { 
    int stringLen = strlen(str);
    for (int i = stringLen; i >= 0; i--) {
        cout << str[i];
    }
    cout << '\n';
}

int main() {
    const char* str = "DGIST"; 
    reverse(str);
    return 0;
}