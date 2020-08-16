#pragma once

#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__
#include <iostream>

constexpr unsigned int PREVIOUS_OPERATOR_ADD = 0x10U;

template<class __Mystr>
class _Charsequnce_iterator {
public:
    using value_type        = __Mystr;
    using reference         = value_type&;
};

template <class __Mystr>
class CharSequence {
public:
    CharSequence();
    CharSequence(const __Mystr *_s);
    CharSequence(const CharSequence<__Mystr> &_cs);
    ~CharSequence();

    size_t length() const;
    void destroy();

    CharSequence<__Mystr> &operator =(CharSequence<__Mystr> &_cs);
    CharSequence<__Mystr> &operator +=(const __Mystr *_s);
    __Mystr& operator[](std::size_t _index);
    CharSequence<__Mystr>& operator +(CharSequence<__Mystr> &_csnd);
    CharSequence<__Mystr>& operator +(const __Mystr *_s);
    bool operator ==(CharSequence<__Mystr> &_cs);
    bool operator ==(const __Mystr *_s);
    bool operator !=(CharSequence<__Mystr> &_cs);
    bool operator !=(const __Mystr *_s);
    bool operator >(CharSequence<__Mystr> &_cs);
    bool operator >(const __Mystr *_s);
    bool operator <(CharSequence<__Mystr> &_cs);
    bool operator <(const __Mystr *_s);

    template <class _T>
    friend std::ostream& operator <<(std::ostream &_os, CharSequence<_T> *_cs);
    template <class _T>
    friend std::istream& operator >>(std::istream &_is, CharSequence<_T> &_cs);

public:
    using iterator = _Charsequnce_iterator<__Mystr &>;
    iterator begin() noexcept;
    iterator end() noexcept;

private:
    bool normalize();

private:
    __Mystr        *str;
    size_t         size;
    int            threshhold;
    int            preop;
    CharSequence   *next;
};

template <class __Mystr>
size_t cslen(const __Mystr *s);

template <class __Mystr>
int cscomp(const __Mystr *_s, const __Mystr *_t);

template <class __Mystr>
inline std::ostream& operator <<(std::ostream &_os, CharSequence<__Mystr> &_cs)
{
    return (_os << &_cs);
}

template <class __Mystr>
inline CharSequence<__Mystr>& CharSequence<__Mystr>::operator+(const __Mystr *_s)
{
    return (*this + *(new CharSequence<__Mystr>(_s)));
}

template <class __Mystr>
inline CharSequence<__Mystr>& operator +(const __Mystr *_s, CharSequence<__Mystr> &_cs)
{
    return (*(new CharSequence<__Mystr>(_s)) + _cs);
}

using String = CharSequence<char>;

template <class __Mystr>
typename CharSequence<__Mystr>::iterator CharSequence<__Mystr>::begin() noexcept
{
    // return (this->str[0]);
}

template <class __Mystr>
typename CharSequence<__Mystr>::iterator CharSequence<__Mystr>::end() noexcept
{
    CharSequence<__Mystr> *cs = this;
    while (cs->next != NULL)
    {
        cs = cs->next;
    }
    // return *(cs->str + cs->size);
}

template <class __Mystr>
size_t cslen(const __Mystr *s)
{
    const register __Mystr *p = s;
    while (*p) { p++; }
    return (size_t)(p - s);
}

template <class __Mystr>
int cscomp(const __Mystr *_s, const __Mystr *_t)
{
    register const __Mystr *p0 = _s;
    register const __Mystr *p1 = _t;

    while (*p0 == *p1)
    {
        if (*p0 == '\0')
        {
            return 0;
        }
        p0++;
        p1++;
    }
    return (size_t)(*p0 - *p1);
}

template <class __Mystr>
CharSequence<__Mystr>::CharSequence() : str(NULL), next(NULL), size(0), threshhold(0), preop(0) { }

template <class __Mystr>
CharSequence<__Mystr>::CharSequence(const CharSequence<__Mystr> &_cs) : CharSequence()
{
    this->str = (__Mystr *)malloc((_cs.length() + 1) * sizeof(__Mystr));
    const CharSequence<__Mystr> *cs = &_cs;
    while (cs)
    {
        if (cs->str[0] != '\0')
        {
            memcpy(this->str + this->size, cs->str, cs->size * sizeof(__Mystr));
            this->size += cs->size;
        }
        cs = cs->next;
    }
    this->str[this->size] = '\0';
}

template <class __Mystr>
CharSequence<__Mystr>::CharSequence(const __Mystr *_s) : CharSequence<__Mystr>()
{
    this->size = _s ? cslen(_s) : 0;
    this->str = (__Mystr *)malloc((this->size + 1) * sizeof(_s));
    if (this->size > 0)
    {
        memcpy(this->str, _s, (this->size + 1) * sizeof(_s));
    }
    *(this->str + this->size) = '\0';
}

template <class __Mystr>
CharSequence<__Mystr>::~CharSequence() 
{
    if (this->str) { free(this->str); }
    this->next->destroy();
}

template <class __Mystr>
void CharSequence<__Mystr>::destroy()
{
    CharSequence<__Mystr> *cs = this;
    CharSequence<__Mystr> *__cs = NULL;
    while (cs != NULL)
    {
        free(cs->str);
        __cs = cs->next;
        free(cs);
        cs = __cs;
    }
}

template <class __Mystr>
CharSequence<__Mystr>& CharSequence<__Mystr>::operator =(CharSequence<__Mystr> &_cs)
{
    CharSequence *cs = (_cs.preop & PREVIOUS_OPERATOR_ADD) ? &_cs : new CharSequence<__Mystr>(_cs);
    if (this->next) { this->next->destroy(); }
    if (this->str) { free(this->str); }
    this->str           = cs->str;
    this->size          = cs->size;
    this->threshhold    = cs->threshhold;
    this->next          = cs->next;
    this->preop         = 0;
    
    cs->str     = NULL;
    cs->next    = NULL;
    delete cs;
    return *this;
}

template <class __Mystr>
CharSequence<__Mystr>& CharSequence<__Mystr>::operator +=(const __Mystr *_s)
{
    if (_s[0] == '\0') { return *this; }
    CharSequence<__Mystr> *_next = new CharSequence<__Mystr>(_s);
    CharSequence<__Mystr> *cs = this;
    
    while (cs->next != NULL)
    {
        cs->threshhold++;
        cs = cs->next;
    }
    cs->threshhold++;
    cs->next = _next;
    
    if (this->threshhold > 0x10) { this->normalize(); }

    return *this;
}

template <class __Mystr>
bool CharSequence<__Mystr>::normalize()
{
    CharSequence<__Mystr> *cs =  new CharSequence<__Mystr>(*this);
    CharSequence<__Mystr> *__cs = new CharSequence<__Mystr>();

    __cs->str           = cs->str;
    __cs->size          = cs->size;
    __cs->threshhold    = cs->threshhold;
    __cs->next          = cs->next;

    cs->str             = this->str;
    cs->size            = this->size;
    cs->threshhold      = this->threshhold;
    cs->next            = this->next;

    this->str           = __cs->str;
    this->size          = __cs->size;
    this->threshhold    = __cs->threshhold;
    this->next          = __cs->next;

    __cs->str = NULL;
    __cs->next = NULL;
    cs->destroy();
    delete __cs;
    return true;
}

template <class __Mystr>
__Mystr& CharSequence<__Mystr>::operator[](size_t _index)
{
    CharSequence<__Mystr> *cs = this;
    while (cs && _index >= cs->size)
    {
        _index -= cs->size;
        cs = cs->next;
    }
    return *(cs->str + _index);
}

template <class __Mystr>
size_t CharSequence<__Mystr>::length() const
{
    const CharSequence<__Mystr> *_cs = this;
    size_t length = 0;
    while (_cs)
    {
        length += _cs->size;
        _cs = _cs->next;
    }
    return length;
}

template <class __Mystr>
std::ostream& operator <<(std::ostream &_os, CharSequence<__Mystr> *_cs)
{
    while (_cs != NULL)
    {
        if (_cs->str) { _os << _cs->str; }
        _cs = _cs->next;
    }
    return _os;
}

template <class __Mystr>
std::istream& operator >>(std::istream &_is, CharSequence<__Mystr> &_cs)
{
    char mbuf[1024 + 1];
    char *pos0 = mbuf;
    
    _cs.next->destroy();
    if (_cs.str) 
    { 
        free(_cs.str);
        _cs.str = NULL;
    }
    _cs.size        = 0;
    _cs.threshhold  = 0;
    _cs.next        = NULL;
    
    while (_is.get(*pos0))
    {
        if (*pos0 == 32 || *pos0 == 10)
        {
            *pos0 = '\0';
            _cs += (__Mystr *)mbuf;
            pos0 = mbuf;
            break;
        }
        else if((pos0 - mbuf) >= 1024)
        {
            *++pos0 = '\0';
            _cs += (__Mystr *)mbuf;
            pos0 = mbuf;
            continue;
        }
        pos0++;
    }

    return _is;
}

template <class __Mystr>
CharSequence<__Mystr>& CharSequence<__Mystr>::operator +(CharSequence<__Mystr> &_csnd)
{
    CharSequence<__Mystr> *_csst    = this;
    CharSequence<__Mystr> *cs       = NULL;
    CharSequence<__Mystr> **join    = &_csst;

    while (*join)
    {
        join = &((*join)->next);
    }
    *(join) = &_csnd;
    cs = new CharSequence<__Mystr>(*_csst);
    *(join) = NULL;
    cs->preop |= PREVIOUS_OPERATOR_ADD;
    return *cs;
}

template <class __Mystr>
bool CharSequence<__Mystr>::operator ==(CharSequence<__Mystr> &_cs)
{
    if ((this->next && this->normalize()) || (_cs.next && _cs.normalize()));
    return !cscomp(this->str, _cs.str);
}

template <class __Mystr>
bool CharSequence<__Mystr>::operator ==(const __Mystr *_s)
{
    if ((this->next && this->normalize()));
    return !cscomp(this->str, _s ? _s : "");
}

template <class __Mystr>
inline bool operator ==(const __Mystr *_s, CharSequence<__Mystr> &_cs)
{
    return (_cs == _s);
}

template <class __Mystr>
bool CharSequence<__Mystr>::operator !=(CharSequence<__Mystr> &_cs)
{
    if ((this->next && this->normalize()) || (_cs.next && _cs.normalize()));
    return cscomp(this->str, _cs.str);
}

template <class __Mystr>
bool CharSequence<__Mystr>::operator !=(const __Mystr *_s)
{
    if ((this->next && this->normalize()));
    return cscomp(this->str, _s ? _s : "");
}

template <class __Mystr>
inline bool operator !=(const __Mystr *_s, CharSequence<__Mystr> &_cs)
{
    return (_cs != _s);
}

template <class __Mystr>
bool CharSequence<__Mystr>::operator >(CharSequence<__Mystr> &_cs)
{
    if ((this->next && this->normalize()) || (_cs.next && _cs.normalize()));
    return (cscomp(this->str, _cs.str) > 0) ? true : false;
}

template <class __Mystr>
bool CharSequence<__Mystr>::operator >(const __Mystr *_s)
{
    if ((this->next && this->normalize()));
    return (cscomp(this->str, _s ? _s : "") > 0) ? true : false;
}

template <class __Mystr>
inline bool operator >(const __Mystr *_s, CharSequence<__Mystr> &_cs)
{
    return (_cs < _s);
}

template <class __Mystr>
bool CharSequence<__Mystr>::operator <(CharSequence<__Mystr> &_cs)
{
    if ((this->next && this->normalize()) || (_cs.next && _cs.normalize()));
    return (cscomp(this->str, _cs.str) < 0) ? true : false;
}

template <class __Mystr>
bool CharSequence<__Mystr>::operator <(const __Mystr *_s)
{
    if ((this->next && this->normalize()));
    return (cscomp(this->str, _s ? _s : "") < 0) ? true : false;
}

template <class __Mystr>
inline bool operator <(const __Mystr *_s, CharSequence<__Mystr> &_cs)
{
    return (_cs > _s);
}

#endif
