/*
* GNU gdb (GDB) 8.1
* Copyright (C) 2018 Free Software Foundation, Inc.
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
* This is free software: you are free to change and redistribute it.
* There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
* and "show warranty" for details.
* This GDB was configured as "x86_64-w64-mingw32".
* Type "show configuration" for configuration details.
* For bug reporting instructions, please see:
* <http://www.gnu.org/software/gdb/bugs/>.
* Find the GDB manual and other documentation resources online at:
* <http://www.gnu.org/software/gdb/documentation/>.
*/
#include <iostream>
using namespace ::std;

#define MAXSIZE 500

class String
{
public:
	String()
	{
		this->data = new char[MAXSIZE];
		this->pos = data;
		*this->pos = '\0';
	}
	/* Constructor: the string use to initialize, capacity defaluted 500  */
	String(const char *cstr, size_t capacity = MAXSIZE)
	{
		this->data = new char[capacity];
		this->pos = data;

		while (*cstr != '\0' && ((this->pos - this->data) / sizeof(char) < MAXSIZE))
		{
			*this->pos++ = *cstr++;
		}
		*this->pos = *cstr;
	}

	/* Declaration Area */
	friend ostream & operator <<(ostream &os, const String &s);
	friend istream & operator>>(istream &is, String &s);
	
	/* Definition Area */
	void destroyStr()
	{
		delete this->data;
		this->pos = nullptr;
	}

	void strCpy(String *s)
	{
		char *p = s->data;
		this->pos = this->data;
		while (*this->pos = *p)
		{
			this->pos++;
			p++;
		}
	}

	inline size_t length()
	{
		return ((this->pos - this->data) / sizeof(char));
	}

	bool equals(String s)
	{
		char *p1 = this->data;
		char *p2 = s.data;
		if (this->length() != s.length())
		{
			return false;
		}
		while (*p1 == *p2)
		{
			if (*p1 == '\0' && *p2 == '\0')
			{
				return true;
			}
			p1++;
			p2++;
		}
		return false;
	}

	String concat(String &s)
	{
		char *p = s.data;
		while (*this->pos = *p)
		{
			this->pos++;
			p++;
		}
		return *this;
	}

	String subStr(size_t i, size_t j)
	{
		String *str = new String("");
		char *p = this->data;

		if (i < 0 || (p + i) >= this->pos || j < 0)
		{
			return *str;
		}

		while (j-- > 0 && (p + i) != this->pos)
		{
			*str->pos++ = *(p + i++);
		}
		*str->pos = '\0';

		return *str;
	}

	String insert(size_t i, String s)
	{
		String str = this->subStr(i, MAXSIZE);
		char *p = s.data;

		this->pos = this->data + i;
		while (*p != '\0' && ((this->pos - this->data) / sizeof(char) <= MAXSIZE))
		{
			*this->pos++ = *p++;
		}
		*this->pos = '\0';
		*this += str;

		return *this;
	}

	String & delStr(size_t i, size_t j)
	{
		if (i <= 0 || i > this->length())
		{
			return *(new String(""));
		}

		if (j >= (this->length() - i))
		{
			this->pos = this->data + i;
			*this->pos = '\0';
		}
		else
		{
			this->pos = this->data + i;
			size_t k = i + j;
			while (*this->pos = *(this->data + k))
			{
				this->pos++;
				k++;
			}
		}

		return *this;
	}

	String & replace(size_t i, size_t j, String *s)
	{
		String *str = new String("");

		if (i <= 0 || i > s->length())
		{
			return *str;
		}

		if (j >= (this->length() - i))
		{
			this->pos = this->data + i;
			*str = *this += *s;
		}
		else
		{
			this->pos = this->data + i;
			size_t k = i + j;
			while (*this->pos = *(this->data + k))
			{
				this->pos++;
				k++;
			}
			*str = *this + *s;
		}
		return *str;
	}

	inline String & replace(size_t i, size_t j, String s)
	{
		return (this->replace(i, j, &s));
	}

	int compareTo(const String *s)
	{
		register const char *p1 = this->data;
		register const char *p2 = s->data;
		
		while (*p1 == *p2)
		{
			if (*p1 == '\0')
			{
				return 0;
			}
			p1++;
			p2++;
		}

		return ((unsigned char)*p1 > (unsigned char)*p2) ? 1 : -1;
	}

	inline int compareTo(const String &s)
	{
		return (this->compareTo(&s));
	}

	inline String operator=(String s)
	{
		this->strCpy(&s);
		return *this;
	}

	inline bool operator ==(String s)
	{
		return (this->equals(s));
	}

	inline String operator+(String s)
	{
		return (this->concat(s));
	}

	inline String operator+(String *s)
	{
		return (this->concat(*s));
	}

	inline String operator+=(String s)
	{
		this->concat(s);
		return *this;
	}

	inline const char & operator[](size_t index)
	{
		return *(this->data + index);
	}

	inline bool __cdecl operator>(const String &s)
	{
		return ((this->compareTo(s) > 0) ? true : false);	
	}

	inline bool __cdecl operator<(const String &s)
	{
		return ((this->compareTo(s) < 0) ? true : false);
	}

private:
	char *data;
	char *pos;
};

ostream & operator<<(ostream &os, const String &s)
{
	os << s.data;
	return os;
}

istream & operator>>(istream &is, String &s)
{
	char c;
	s.pos = s.data;
	while (is.get(c))
	{
		*s.pos++ = c;
	}
	*s.pos = '\0';
	is.clear();
	return is;
}