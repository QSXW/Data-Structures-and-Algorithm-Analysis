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
## Debug
* 新手必经之路，`UTF-8` 和 `GBK` 的爱恨纠缠。（Visual Studio 用户可以跳过此段）
* 在代码开始前添加 `Debug::SetEncoding("UTF-8")` 避免中文乱码。
```C++
#include <iostream>
using namespace ::std;
#include "debug.h"

int main()
{
	Debug::SetEncoding("UTF-8");

	String hello_world = "你好，世界！";
        cout << hello_world << endl;

	Debug::Pause();
	return 0;
}
```
* 输出效果
![image](https://github.com/QSXW/Miscellaneous-Thinking/blob/master/Image%20Set/debug-example-terminal-output-result-202002821.png)
