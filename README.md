# Data-Structures-and-Algorithm-Analysis (Based on C++11 standard)

## String
* Using `object-oriented` and `LIST` to implement String, whose definition implemented in sequence.h.
* The class String overloaded the operator of the fundamental function of String.
* To use `sequnence.h`, below is a String sample in your codes:
```C++
#include <iostream>
using namespace ::std;
#include "squnence.h"

int main()
{
	String s = "abcdefghefghijklmn";
	String s1 = "xyz";

	s = s + s1;
	s1 = s;
	if (s == s1)
	{
		cout << s << endl;
	}

	cin.get();
	return 0;
}
```
