#include <iostream>
using namespace std;

#include "string.h"

void test_string(int size);
void test_operator_add(String &str, int size);
void test_substr(String &str);
void test_prefix(String &str);
void test_suffix(String &str);
void test_concat(String &str);
void test_equal(String &str);
void test_match_brute(String &str);
void test_match_kmp(String &str);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <test size>" << endl;
        return -1;
    }

    test_string(atoi(argv[1]));
    return 0;
}

void test_string(int size) {
    srand(time(0));
    String str;

    test_operator_add(str, size);
    test_substr(str);
    test_prefix(str);
    test_suffix(str);
    test_concat(str);
    test_equal(str);
    test_match_brute(str);
    test_match_kmp(str);
}

void test_operator_add(String &str, int size) {
    cout << endl << "test1 operator +=" << endl;
    cout << "before add: " << str;
    for (int i = 0; i < size; i++) {
        int r = rand() % LEN;
        str += alphabet[r];
    }
    cout << "after add: " << endl <<  str << endl;
}

void test_substr(String &str) {
    String sub1 = str.substr(0, 5);
    String sub2 = str.substr(5, 4);
    String sub3 = str.substr(0, str.length());
    cout << "test2 substring" << endl;
    cout << "substr(0, 5): " << endl << sub1;
    cout << "substr(5, 4): " << endl << sub2;
    cout << "substr(0, " << str.length() << "): " << endl << sub3 << endl;
}

void test_prefix(String &str) {
    String pre1 = str.prefix(0);
    String pre2 = str.prefix(5);
    String pre3 = str.prefix(10);
    String pre4 = str.prefix(str.length());
    cout << "test3 prefix" << endl;
    cout << "prefix(0): " << endl << pre1;
    cout << "prefix(5): " << endl << pre2;
    cout << "prefix(10): " << endl << pre3;
    cout << "prefix(" << str.length() << "): " << endl << pre4 << endl;
}

void test_suffix(String &str) {
    String suf1 = str.suffix(0);
    String suf2 = str.suffix(5);
    String suf3 = str.suffix(10);
    String suf4 = str.suffix(str.length());
    cout << "test4 suffix" << endl;
    cout << "suffix(0):" << endl << suf1;
    cout << "suffix(5):" << endl << suf2;
    cout << "suffix(10):" << endl << suf3;
    cout << "suffix(" << str.length() << "):" << endl << suf4 << endl;
}

void test_concat(String &str) {
    String str1("", 0);
    String str2("123", 3);
    cout << "test5 concat" << endl;
    str.concat(str1);
    cout << "concat \"\"(empty string): " << endl << str;
    str.concat(str2);
    cout << "concat \"123\": " << endl << str << endl;
}

void test_equal(String &str) {
    String str1("123", 3);
    String str2 = str;
    bool flag1 = str.equal(str1);
    bool flag2 = str.equal(str2);
    cout << "test6 equal" << endl;
    cout << str << "||" << endl << str1 << ": " << (flag1 ? "true" : "false") << endl;
    cout << str << "==" << str2 << ": " << (flag2 ? "true\n\n" : "false\n\n");
}

void test_match_brute(String &str) {
    String p = str.substr(10, 10);
    int res = str.match_brute(p);
    cout << "test7 brute force match" << endl;
    cout << "pattern string: " << p;
    cout << "text string: " << str;
    cout << "match result: " << res << endl << endl;
}

void test_match_kmp(String &str) {
    String p = str.substr(20, 10);
    int res = str.match_kmp(p);
    cout << "test8 kmp match" << endl;
    cout << "pattern string: " << p;
    cout << "text string: " << str;
    cout << "match result: " << res << endl;
}
