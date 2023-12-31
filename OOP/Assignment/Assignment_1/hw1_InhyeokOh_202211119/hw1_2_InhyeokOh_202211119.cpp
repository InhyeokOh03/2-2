/*
2 - A. Explain why the code in the bottom executes successfully, while the code in the top does not?

Answer : 
위의 코드는 1부터 1000000까지의 합을 재귀함수로 구현한 것이다.

아래의 코드는 마찬가지로 합을 구하지만, 재귀를 사용하지 않고 루프를 통해 sum에 점점 더해가는 방식으로 진행된다.

아래의 코드는 재대로 작동하지만 위의 코드를 실행 시켜보면, 'Segmentation fault (core dumped)' 라는 문구가 뜬다.

이는 메모리 관리에 있어서, 메모리에 침범이 일어나면 작동을 방지하는 보호기법임을 알 수 있다.

이를 통해 위의 코드는 재귀적 접근이 계속해서 함수를 호출하며 많은 메모리를 사용한다는 것을 짐작할 수 있다.

결국 기본 스택의 사이즈가 제한되어 있으며 stack overflow가 일어나며 멈추게 되는 것이다.
*/

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