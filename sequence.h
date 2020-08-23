#pragma once

#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__
#include <iostream>

#define _LETTER_CASE_CONVERT_FAST_

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
    CharSequence<_Mystr_>& toLower();
    CharSequence<_Mystr_>& toUpper();
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

char *cslower(char *const _s)
{
#ifdef _LETTER_CASE_CONVERT_FAST_
    const unsigned char map[] = {
         0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13,  14,  15,
         16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
         32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
         48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
         64,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
        112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  91,  92,  93,  94,  95,
         96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
        112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
        128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
        144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
        160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
        176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
        192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
        208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
        224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
        240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
    };

    register unsigned char *p = (unsigned char *)_s;
    while (*p = map[*p]) { p++; }
#else
    char *p = _s;

    while (*p)
    {
        if (*p > 65 && *p < 90)
        {
            *p += 32;
        }
        p++;
    }
#endif
    return _s;
}

char *csupper(char *const _s)
{
#ifdef _LETTER_CASE_CONVERT_FAST_
    const unsigned char map[] = {
          0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,
         16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
         32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
         48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
         64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
         80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
         96,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
         80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90, 123, 124, 125, 126, 127,
        128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
        144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
        160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
        176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
        192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
        208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
        224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
        240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
    };
    register unsigned char *p = (unsigned char *)_s;
    while (*p = map[*p]) { p++; }
#else
    char *p = _s;
    while (*p)
    {
        if (*p > 97 && *p < 122)
        {
            *p -= 32;
        }
        p++;
    }
#endif
    return _s;
}

template <class _Mystr_>
inline CharSequence<_Mystr_>& CharSequence<_Mystr_>::toLower()
{
    if (this->next && this->normalize());
    cslower(this->data);
    return *this;
}

template <class _Mystr_>
inline CharSequence<_Mystr_>& CharSequence<_Mystr_>::toUpper()
{
    if (this->next && this->normalize());
    csupper(this->data);
    return *this;
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
    CharSequence<_Mystr_> *_cs_ = NULL;
    while (cs != NULL)
    {
        free(cs->data);
        _cs_ = cs->next;
        free(cs);
        cs = _cs_;
    }
}

template <class _Mystr_>
CharSequence<_Mystr_>& CharSequence<_Mystr_>::operator =(CharSequence<_Mystr_> &_cs)
{
    CharSequence *cs = NULL;
    if (&_cs != this)
    {
        if (cs = (_cs.preop & PREVIOUS_OPERATOR_ADD) ? &_cs : new CharSequence<_Mystr_>(_cs))
        {
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
    CharSequence<_Mystr_> *cs   = nullptr;
    CharSequence<_Mystr_> *_cs_ = nullptr;

    if ((cs = new CharSequence<_Mystr_>(*this)) && (_cs_ = new CharSequence<_Mystr_>()))
    {
        _cs_->data          = cs->data;
        _cs_->size          = cs->size;
        _cs_->threshhold    = cs->threshhold;
        _cs_->next          = cs->next;

        cs->data            = this->data;
        cs->size            = this->size;
        cs->threshhold      = this->threshhold;
        cs->next            = this->next;

        this->data          = _cs_->data;
        this->size          = _cs_->size;
        this->threshhold    = _cs_->threshhold;
        this->next          = _cs_->next;

        _cs_->data = NULL;
        _cs_->next = NULL;
        cs->destroy();
        delete _cs_;
        return true;
    }
    return false;
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
        index = 0;
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
