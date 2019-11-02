# Data-Structures-and-Algorithm-Analysis (Based on C++11 standard)
- Highly optimized Data Structures and Algorithm Analysis.
- When programming, I would try to get rid of the shackles of textbooks. I am not saying that those codes written in textbooks are terrible. It's simply not enough better and excessively common. If using a sentence to describe it, I would say - "Those codes may be just the most fundamental implementation of data-structures-and-algorithm-analysis' theory, which doesn't consider the program's **efficiency and memory allocation** that is extremely significant, especially if you're using `C/C++`." Of course, `Java` would be another situation. I have few used ever `Java` worked for my programming, tho, everyone tells me that you don't need to ponder because Java would allocate memory automatically.

## String
* Use `object-oriented` and `pointer` to implement String, whose definition implemented in sqstring.cpp
* The class String highly reloads the operator for the fundamental function of String.
* To use `String.cpp`, please create a new file named `String.h`. Below is a sample:
```C++
/*
* Neglect the sample if you're using Microsoft Visual Studio.
*/
#ifndef _STRING_H_
#define _STRING_H_

#include "String.cpp"

#endif
```
* Below is a String sample in your codes:
```C++
#include <iostream>
#include <string>
using namespace ::std;
#include "String.h"

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
## Sparse Matrix
* Implemented by **Three Tuple**.
* Support the Matrix basic operations using the operator reloaded.
