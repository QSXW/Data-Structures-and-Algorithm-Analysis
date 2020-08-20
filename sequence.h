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
    CharSequence(FILE *fp);
    ~CharSequence();

    size_t length() const;
    void destroy();
    const _Mystr_ *c_str() noexcept;

    CharSequence<_Mystr_> &operator =(CharSequence<_Mystr_> &_cs);
    CharSequence<_Mystr_> &operator +=(const _Mystr_ *_s);
    _Mystr_& operator[](std::size_t _index) noexcept;
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

    template <class _T_>
    friend std::ostream& operator <<(std::ostream &_os, CharSequence<_T_> *_cs);
    template <class _T_>
    friend std::istream& operator >>(std::istream &_is, CharSequence<_T_> &_cs);
    template <class _T_>
    friend CharSequence<_T_>& operator <<(CharSequence<_T_>& _cs, std::ifstream &_infile);
    template <class _T_>
    friend std::ofstream& operator <<(std::ofstream &_ofs, CharSequence<_T_> *_cs);

public:
    using iterator = _Charsequnce_iterator<_Mystr_ &>;
    iterator begin() noexcept;
    iterator end() noexcept;

private:
    bool normalize();
    bool reset();
private:
    _Mystr_        *data;
    _Mystr_        *memory_block;
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
    // return (this->data[0]);
}

template <class _Mystr_>
typename CharSequence<_Mystr_>::iterator CharSequence<_Mystr_>::end() noexcept
{
    CharSequence<_Mystr_> *cs = this;
    while (cs->next != NULL)
    {
        cs = cs->next;
    }
    // return *(cs->data + cs->size);
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
CharSequence<_Mystr_>::CharSequence() : data(NULL), memory_block(data), next(NULL), size(0), threshhold(0), preop(0) { }

template <class _Mystr_>
CharSequence<_Mystr_>::CharSequence(const CharSequence<_Mystr_> &_cs) : CharSequence()
{
    this->data = (_Mystr_ *)malloc((_cs.length() + 1) * sizeof(_Mystr_));
    const CharSequence<_Mystr_> *cs = &_cs;
    if (this->data)
    {
        while (cs)
        {
            if (cs->data && cs->data[0] != '\0')
            {
                memcpy(this->data + this->size, cs->data, cs->size * sizeof(_Mystr_));
                this->size += cs->size;
            }
            cs = cs->next;
        }
        this->data[this->size] = '\0';
    }
}

template <class _Mystr_>
CharSequence<_Mystr_>::CharSequence(const _Mystr_ *_s) : CharSequence<_Mystr_>()
{
    this->size = _s ? cslen(_s) : 0;
    this->data = (_Mystr_ *)malloc((this->size + 1) * sizeof(_s));
    if (this->size > 0 && this->data)
    {
        memcpy(this->data, _s, (this->size + 1) * sizeof(_s));
    }
    *(this->data + this->size) = '\0';
}

template <class _Mystr_>
CharSequence<_Mystr_>::CharSequence(int _count, const _Mystr_ _c) : CharSequence<_Mystr_>()
{
    if (this->data = (_Mystr_ *)malloc((_count + 1) * sizeof(_Mystr_)))
    {
        while (_count-- > 0) { this->data[this->size++] = _c; }
        this->data[this->size] = '\0';
    }
}

template <class _Mystr_>
CharSequence<_Mystr_>::CharSequence(FILE *fp) : CharSequence()
{
    size_t fsize = 0;

    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (fsize > 0 && (this->data = (_Mystr_ *)malloc((fsize + 1) * sizeof(_Mystr_))))
    {
        fread(this->data, fsize, 1, fp);
        this->size += fsize;
        this->data[this->size] = 0x0;
    }
}

template <class _Mystr_>
CharSequence<_Mystr_>::~CharSequence() 
{
    if (this->data) { free(this->data); }
    if (this->next) { this->next->destroy(); }
}

template <class _Mystr_>
void CharSequence<_Mystr_>::destroy()
{
    CharSequence<_Mystr_> *cs = this;
    CharSequence<_Mystr_> *__cs = NULL;
    while (cs != NULL)
    {
        free(cs->data);
        __cs = cs->next;
        free(cs);
        cs = __cs;
    }
}

template <class _Mystr_>
CharSequence<_Mystr_>& CharSequence<_Mystr_>::operator =(CharSequence<_Mystr_> &_cs)
{
    CharSequence *cs = NULL;
    if (&_cs != this)
    {
        cs = (_cs.preop & PREVIOUS_OPERATOR_ADD) ? &_cs : new CharSequence<_Mystr_>(_cs);
        if (this->next) { this->next->destroy(); }
        if (this->data) { free(this->data); }
        this->data           = cs->data;
        this->size          = cs->size;
        this->threshhold    = cs->threshhold;
        this->next          = cs->next;
        this->preop         = 0;
        
        cs->data     = NULL;
        cs->next    = NULL;
        delete cs;
    }
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

    __cs->data           = cs->data;
    __cs->size          = cs->size;
    __cs->threshhold    = cs->threshhold;
    __cs->next          = cs->next;

    cs->data             = this->data;
    cs->size            = this->size;
    cs->threshhold      = this->threshhold;
    cs->next            = this->next;

    this->data           = __cs->data;
    this->size          = __cs->size;
    this->threshhold    = __cs->threshhold;
    this->next          = __cs->next;

    __cs->data = NULL;
    __cs->next = NULL;
    cs->destroy();
    delete __cs;
    return true;
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::reset()
{
    if (this->data) { free(this->data); }
    if (this->next) { this->destroy(); }
    this->data           = 0x0;
    this->next          = 0x0;
    this->size          = 0x0;
    this->threshhold    = 0x0;
    this->preop         = 0x0;
    return true;
}

template <class _Mystr_>
_Mystr_& CharSequence<_Mystr_>::operator[](size_t _index) noexcept
{
    CharSequence<_Mystr_> *cs = this;
    while (cs && _index >= cs->size)
    {
        _index -= cs->size;
        cs = cs->next;
    }
    return (cs ? *(cs->data + _index) : *(this->data + this->size));
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
    size_t index;
    while (_cs != NULL)
    {
        while (index < _cs->size)
        {
            putchar(_cs->data[index++]);
        }
        _cs = _cs->next;
    }
    return _os;
}

template <class _Mystr_>
inline std::ofstream& operator <<(std::ofstream &_ofs, CharSequence<_Mystr_> &_cs)
{
    return (_ofs << &_cs);
}

template <class _Mystr_>
std::ofstream& operator <<(std::ofstream &_ofs, CharSequence<_Mystr_> *_cs)
{
    while (_cs != NULL)
    {
        if (!_ofs.bad())
        {
            _ofs << _cs->data;
            _cs = _cs->next;
        }
        else
        {
            break;
        }
    }
    return _ofs;
}

template <class _Mystr_>
std::istream& operator >>(std::istream &_is, CharSequence<_Mystr_> &_cs)
{
    _Mystr_ mbuf[1024 + 1];
    _Mystr_ *pos0 = mbuf;
    
    _cs.reset();
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
CharSequence<_Mystr_>& operator <<(CharSequence<_Mystr_>& _cs, std::ifstream &_infile)
{
    _cs.reset();
    std::filebuf  *fbuf = _infile.rdbuf();
    _cs.size = fbuf->pubseekoff(0, _infile.end, _infile.in);
    fbuf->pubseekpos(0, _infile.in);
    if (_cs.data = (_Mystr_ *)malloc((_cs.size + 1) * sizeof(_Mystr_)))
    {
        fbuf->sgetn(_cs.data, _cs.size);
    }

    return _cs;
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
    return !cscomp(this->data, _cs.data);
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::operator ==(const _Mystr_ *_s)
{
    if ((this->next && this->normalize()));
    return !cscomp(this->data, _s ? _s : "");
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
    return cscomp(this->data, _cs.data);
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::operator !=(const _Mystr_ *_s)
{
    if ((this->next && this->normalize()));
    return cscomp(this->data, _s ? _s : "");
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
    return (cscomp(this->data, _cs.data) > 0) ? true : false;
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::operator >(const _Mystr_ *_s)
{
    if ((this->next && this->normalize()));
    return (cscomp(this->data, _s ? _s : "") > 0) ? true : false;
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
    return (cscomp(this->data, _cs.data) < 0) ? true : false;
}

template <class _Mystr_>
bool CharSequence<_Mystr_>::operator <(const _Mystr_ *_s)
{
    if ((this->next && this->normalize()));
    return (cscomp(this->data, _s ? _s : "") < 0) ? true : false;
}

template <class _Mystr_>
inline bool operator <(const _Mystr_ *_s, CharSequence<_Mystr_> &_cs)
{
    return (_cs > _s);
}

template <class _Mystr_>
inline const _Mystr_ *CharSequence<_Mystr_>::c_str() noexcept
{
    if (this->next && this->normalize());
    return (this->data ? this->data : "");
}

#endif
