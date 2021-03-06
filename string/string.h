#ifndef __STRING_H_
#define __STRING_H_

#include <string.h>

#include "../vector/vector.h"

const int LEN = 94;

const char alphabet[LEN] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', '`', '~', '!', '@', '#', '$', '%', '^',
    '&', '*', '(', ')', '-', '+', '_', '=', '{', '}', '[', ']', '\\', '|',
    ';', ':', '\'', '"', ',', '<', '>', '.', '?', '/',
};

class String: public Vector<char> {
    protected:
        int max(int a, int b);
        int* get_next(char *p);
        int* get_next(String p);
        int* get_bc(char *p);
        int* get_bc(String p);
        int* get_gs(char *p);
        int* get_gs(String p);
    public:
        String() {}
        String(const char *str, int len);
        String(const String &str);
        String(char *elem, Rank low, Rank high);

        int length();
        char char_at(Rank i);
        String substr(Rank i, Rank k);
        String prefix(Rank k);
        String suffix(Rank k);
        void concat(String str);
        bool equal(String str);

        Rank match_brute(String p);
        Rank match_brute(char *p);
        Rank match_kmp(String p);
        Rank match_kmp(char *p);
        Rank match_bm(String p);
        Rank match_bm(char *p);

        String& operator += (String str);
        String& operator += (char ch);
        friend ostream& operator << (ostream &os, String &str) {
            for (int i = 0; i < str.length(); i++) {
                cout << str._elem[i];
            }
            cout << endl;
            return os;
        }
};

String::String(char *elem, Rank low, Rank high) {
    if (high <= low) {
        _capacity = DEFAULT_CAPACITY;
        _elem = new char[_capacity];
        _size = 0;
    }
    this->copy_from(elem, low, high);
}

String::String(const char *str, int len) {
    this->copy_from(str, 0, len);
}

String::String(const String &str) {
    this->copy_from(str._elem, 0, str._size);
}

int String::length() { return this->_size; }

char String::char_at(Rank i) { return this->_elem[i]; }

// Return substring of length k starting from position i
String String::substr(Rank i, Rank k) {
    return String(this->_elem, i, i + k);
}

String String::prefix(Rank k) {
    return substr(0, k);
}

String String::suffix(Rank k) {
    return substr(this->_size - k, k);
}

void String::concat(String str) {
    for (int i = 0; i < str.length(); i++) {
        this->append(str[i]);
    }
}

bool String::equal(String str) {
    if (this->_size != str.length()) {
        return false;
    }

    for (int i = 0; i < this->_size; i++) {
        if (this->_elem[i] != str[i]) {
            return false;
        }
    }

    return true;
}

String& String::operator += (String str) {
    concat(str);
    return *this;
}

String& String::operator += (char ch) {
    this->append(ch);
    return *this;
}

Rank String::match_brute(String pattern) {
    // length of text string
    int n = this->_size;
    // length of pattern string
    int m = pattern._size;
    // i: index of text string
    int i = 0;
    // j: index of pattern string
    int j = 0;
    while (i < n && j < m) {
        if (_elem[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = 0;
            i -= (j - 1);
        }
    }
    return i - j;
}

Rank String::match_brute(char *p) {
    return match_brute(String(p, strlen(p)));
}

int* String::get_next(char *p) {
    return get_next(String(p, strlen(p)));
}

int* String::get_next(String p) {
    int t;
    int *next = new int[p._size];
    t = next[0] = -1;

    int i = 0;
    while (i < p._size - 1) {
        if (t < 0 || p[i] == p[t]) {
            i++;
            t++;
            if (p[i] == p[t]) {
                next[i] = next[t];
            } else {
                next[i] = t;
            }
            p[++i] = ++t;
        } else {
            t = next[t];
        }
    }
    return next;
}

Rank String::match_kmp(String pattern) {
    int i = 0;
    int j = 0;
    int n = this->_size;
    int m = pattern._size;
    int *next = get_next(pattern);

    while (i < n && j < m) {
        if (j < 0 || _elem[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    delete[] next;
    return i - j;
}

Rank String::match_kmp(char *p) {
    return match_kmp(String(p, strlen(p)));
}

int* String::get_bc(char *p) {
    return get_bc(String(p, strlen(p)));
}

int* String::get_bc(String p) {
    int *bc = new int[256];
    // Initiate bc
    memset(bc, -1, 256);
    int size = p._size;
    for (int i = 0; i < size; i++) {
        bc[p[i]] = i;
    }
    return bc;
}

int* String::get_gs(char *p) {
    return get_gs(String(p, strlen(p)));
}

int* String::get_gs(String p) {
   
}

Rank String::match_bm(char *p) {
    return match_bm(String(p, strlen(p)));
}

Rank String::match_bm(String p) {
    int i, j;
    int m = p._size;
    int n = this->_size;
    int *bc = get_bc(p);
    int *gs = get_gs(p);

    int step;
    for (i = 0; i < n - m + 1; i++) {
        for (j = m - 1; j >= 0; j--) {
            if (_elem[i + j] != p[j]) {
                step = max(j - bc[p[j]], gs[j]);
                i += step;
            }
        }
        if (j == m) {
            break;
        }
    }
    return i;
}

int String::max(int a, int b) {
    return a > b ? a : b;
}

#endif // __STRING_H_
