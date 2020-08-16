#pragma once

#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__
#include <iostream>

constexpr unsigned int PREVIOUS_OPERATOR_ADD = 0x10U;

template<class _Mystr_>
class _Charsequnce_iterator {
public:
    using value_type        = _Mystr_;
    using reference         = value_type&;
};

template <class _Mystr_>
class CharSequence {
public:
    CharSequence();
    CharSequence(const _Mystr_ *_s);
    CharSequence(const CharSequence<_Mystr_> &_cs);
    CharSequence(int _count, const _Mystr_ _c);
    ~CharSequence();

    size_t length() const;
    void destroy();

    CharSequence<_Mystr_> &operator =(CharSequence<_Mystr_> &_cs);
    CharSequence<_Mystr_> &operator +=(const _Mystr_ *_s);
    _Mystr_& operator[](std::size_t _index);
    CharSequence<_Mystr_>& operator +(CharSequence<_Mystr_> &_csnd);
    CharSequence<_Mystr_>& operator +(const _Mystr_ *_s);
    bool operator ==(CharSequence<_Mystr_> &_cs);
    bool operator ==(const _Mystr_ *_s);
    bool operator !=(CharSequence<_Mystr_> &_cs);
    bool operator !=(const _Mystr_ *_s);
    bool operator >(CharSequence<_Mystr_> &_cs);
    bool operator >(const _Mystr_ *_s);
    bool operator <(CharSequence<_Mystr_> &_cs);
    bool operator <(const _Mystr_ *_s);

    template <class _T>
    friend std::ostream& operator <<(std::ostream &_os, CharSequence<_T> *_cs);
    template <class _T>
    friend std::istream& operator >>(std::istream &_is, CharSequence<_T> &_cs);

public:
    using iterator = _Charsequnce_iterator<_Mystr_ &>;
    iterator begin() noexcept;
    iterator end() noexcept;

private:
    bool normalize();

private:
    _Mystr_        *str;
    size_t         size;
    int            threshhold;
    int            preop;
    CharSequence   *next;
};

using String = CharSequence<char>;

template <class _Mystr_>
inline std::ostream& operator <<(std::ostream &_os, CharSequence<_Mystr_> &_cs)
{
    return (_os << &_cs);
}

template <class _Mystr_>
inline CharSequence<_Mystr_>& CharSequence<_Mystr_>::operator+(const _Mystr_ *_s)
{
    return (*this + *(new CharSequence<_Mystr_>(_s)));
}

template <class _Mystr_>
inline CharSequence<_Mystr_>& operator +(const _Mystr_ *_s, CharSequence<_Mystr_> &_cs)
{
    return (*(new CharSequence<_Mystr_>(_s)) + _cs);
}

template <class _Mystr_>
typename CharSequence<_Mystr_>::iterator CharSequence<_Mystr_>::begin() noexcept
{
    // return (this->str[0]);
}

template <class _Mystr_>
typename CharSequence<_Mystr_>::iterator CharSequence<_Mystr_>::end() noexcept
{
    CharSequence<_Mystr_> *cs = this;
    while (cs->next != NULL)
    {
        cs = cs->next;
    }
    // return *(cs->str + cs->size);
}

template <class _Mystr_>
size_t cslen(const _Mystr_ *s)
{
    const register _Mystr_ *p = s;
    while (*p) { p++; }
    return (size_t)(p - s);
}

template <class _Mystr_>
int cscomp(const _Mystr_ *_s, const _Mystr_ *_t)
{
    register const _Mystr_ *p0 = _s;
    register const _Mystr_ *p1 = _t;

    while (*p0 == *p1)
    {
        if (*p0 == '\0') { return 0; }
        p0++;
        p1++;
    }
    return (*p0 - *p1);
}

template <class _Mystr_>
CharSequence<_Mystr_>::CharSequence() : str(NULL), next(NULL), size(0), threshhold(0), preop(0) { }

template <class _Mystr_>
CharSequence<_Mystr_>::CharSequence(const CharSequence<_Mystr_> &_cs) : CharSequence()
{
    this->str = (_Mystr_ *)malloc((_cs.length() + 1) * sizeof(_Mystr_));
    const CharSequence<_Mystr_> *cs = &_cs;
    while (cs)
    {
        if (cs->str[0] != '\0')
        {
            memcpy(this->str + this->size, cs->str, cs->size * sizeof(_Mystr_));
            this->size += cs->size;
        }
        cs = cs->next;
    }
    this->str[this->size] = '\0';
}

template <class _Mystr_>
CharSequence<_Mystr_>::CharSequence(const _Mystr_ *_s) : CharSequence<_Mystr_>()
{
    this->size = _s ? cslen(_s) : 0;
    this->str = (_Mystr_ *)malloc((this->size + 1) * sizeof(_s));
    if (this->size > 0)
    {
        memcpy(this->str, _s, (this->size + 1) * sizeof(_s));
    }
    *(this->str + this->size) = '\0';
}

template <class _Mystr_>
CharSequence<_Mystr_>::CharSequence(int _count, const _Mystr_ _c) : CharSequence<_Mystr_>()
{
    this->str = (_Mystr_ *)malloc((_count + 1) * sizeof(_Mystr_));
    while (_count-- > 0) { this->str[this->size++] = _c; }
    this->str[this->size] = '\0';
}

template <class _Mystr_>
CharSequence<_Mystr_>::~CharSequence() 
{
    if (this->str) { free(this->str); }
    this->next->destroy();
}

template <class _Mystr_>
void CharSequence<_Mystr_>::destroy()
{
    CharSequence<_Mystr_> *cs = this;
    CharSequence<_Mystr_> *__cs = NULL;
    while (cs != NULL)
    {
        free(cs->str);
        __cs = cs->next;
        free(cs);
        cs = __cs;
    }
}

template <class _Mystr_>
CharSequence<_Mystr_>& CharSequence<_Mystr_>::operator =(CharSequence<_Mystr_> &_cs)
{
    CharSequence *cs = (_cs.preop & PREVIOUS_OPERATOR_ADD) ? &_cs : new CharSequence<_Mystr_>(_cs);
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

template <class _Mystr_>
CharSequence<_Mystr_>& CharSequence<_Mystr_>::operator +=(const _Mystr_ *_s)
{
    if (_s[0] == '\0') { return *this; }
    CharSequence<_Mystr_> *_next = new CharSequence<_Mystr_>(_s);
    CharSequence<_Mystr_> *cs = this;
    
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

template <class _Mystr_>
bool CharSequence<_Mystr_>::normalize()
{
    CharSequence<_Mystr_> *cs =  new CharSequence<_Mystr_>(*this);
    CharSequence<_Mystr_> *__cs = new CharSequence<_Mystr_>();

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

template <class _Mystr_>
_Mystr_& CharSequence<_Mystr_>::operator[](size_t _index)
{
    CharSequence<_Mystr_> *cs = this;
    while (cs && _index >= cs->size)
    {
        _index -= cs->size;
        cs = cs->next;
    }
    return *(cs->str + _index);
}

template <class _Mystr_>
size_t CharSequence<_Mystr_>::length() const
{
    const CharSequence<_Mystr_> *_cs = this;
    size_t length = 0;
    while (_cs)
    {
        length += _cs->size;
        _cs = _cs->next;
    }
    return length;
}

template <class _Mystr_>
std::ostream& operator <<(std::ostream &_os, CharSequence<_Mystr_> *_cs)
{
    while (_cs != NULL)
    {
        if (_cs->str) { _os << _cs->str; }
        _cs = _cs->next;
    }
    return _os;
}

template <class _Mystr_>
std::istream& operator >>(std::istream &_is, CharSequence<_Mystr_> &_cs)
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
            _cs += (_Mystr_ *)mbuf;
            pos0 = mbuf;
            break;
        }
        else if((pos0 - mbuf) >= 1024)
        {
            *++pos0 = '\0';
            _cs += (_Mystr_ *)mbuf;
            pos0 = mbuf;
            continue;
        }
        pos0++;
    }

    return _is;
}

template <class _Mystr_>
CharSequence<_Mystr_>& CharSequence<_Mystr_>::operator +(CharSequence<_Mystr_> &_csnd)
{
    CharSequence<_Mystr_> *_csst    = this;
    CharSequence<_Mystr_> *cs       = NULL;
    CharSequence<_Mystr_> **join    = &_csst;

    while (*join)
    {
        join = &((*join)->next);
    }
    *(join) = &_csnd;
    cs = new CharSequence<_Mystr_>(*_csst);
    *(join) = NULL;
    cs->preop |= PREVIOUS_OPERATOR_ADD;
    return *cs;
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::operator ==(CharSequence<_Mystr_> &_cs)
{
    if ((this->next && this->normalize()) || (_cs.next && _cs.normalize()));
    return !cscomp(this->str, _cs.str);
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::operator ==(const _Mystr_ *_s)
{
    if ((this->next && this->normalize()));
    return !cscomp(this->str, _s ? _s : "");
}

template <class _Mystr_>
inline bool operator ==(const _Mystr_ *_s, CharSequence<_Mystr_> &_cs)
{
    return (_cs == _s);
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::operator !=(CharSequence<_Mystr_> &_cs)
{
    if ((this->next && this->normalize()) || (_cs.next && _cs.normalize()));
    return cscomp(this->str, _cs.str);
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::operator !=(const _Mystr_ *_s)
{
    if ((this->next && this->normalize()));
    return cscomp(this->str, _s ? _s : "");
}

template <class _Mystr_>
inline bool operator !=(const _Mystr_ *_s, CharSequence<_Mystr_> &_cs)
{
    return (_cs != _s);
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::operator >(CharSequence<_Mystr_> &_cs)
{
    if ((this->next && this->normalize()) || (_cs.next && _cs.normalize()));
    return (cscomp(this->str, _cs.str) > 0) ? true : false;
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::operator >(const _Mystr_ *_s)
{
    if ((this->next && this->normalize()));
    return (cscomp(this->str, _s ? _s : "") > 0) ? true : false;
}

template <class _Mystr_>
inline bool operator >(const _Mystr_ *_s, CharSequence<_Mystr_> &_cs)
{
    return (_cs < _s);
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::operator <(CharSequence<_Mystr_> &_cs)
{
    if ((this->next && this->normalize()) || (_cs.next && _cs.normalize()));
    return (cscomp(this->str, _cs.str) < 0) ? true : false;
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::operator <(const _Mystr_ *_s)
{
    if ((this->next && this->normalize()));
    return (cscomp(this->str, _s ? _s : "") < 0) ? true : false;
}

template <class _Mystr_>
inline bool operator <(const _Mystr_ *_s, CharSequence<_Mystr_> &_cs)
{
    return (_cs > _s);
}

#endif
