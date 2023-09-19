#include<iostream>
#include<stdio.h>
#include<string>
#include<stack>

using namespace std;
string str;

/* 입력예제
So when I die (the [first] I will see in (heaven) is a score list).
[ first in ] ( first out ).
Half Moon tonight (At least it is better than no Moon at all].
A rope may form )( a trail in a maze.
Help( I[m being held prisoner in a fortune cookie factory)].
([ (([( [ ] ) ( ) (( ))] )) ]).
 .
.
*/

int main()
{
	while (1)
	{
		getline(cin, str); // 공백까지 입력받아야 하므로 scanf사용은 부적절하다고 생각했습니다.
		stack<char> a;
		if (str[0] == '.') break;

		for (int i = 0; i < str.length() - 1; i++)
		{
			if (str[i] == '(') a.push('(');
			if (str[i] == '[') a.push('[');
			if (str[i] == ']')
			{
				if (!a.empty() && a.top() == '[') a.pop();
				else { printf("no\n"); break; } // "]hello[" 같은 예외 문장들 방지
			}

			if (str[i] == ')')
			{
				if (!a.empty() && a.top() == '(') a.pop();
				else { printf("no\n"); break; } // ")hello(" 같은 예외 문장들 방지
			}

			if (a.empty() && i == str.length() - 2) printf("yes\n"); // str[str.length() - 1] = '.' 이므로 검사할 필요가 없다.
			else if (!a.empty() && i == str.length() - 2) printf("no\n");
		}

	}
}