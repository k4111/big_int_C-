
#ifndef _BIGINTNUM_H_
#define _BIGINTNUM_H_
#include<string.h>
#include<iostream>
#include<vector>
using namespace std;
class bigIntNum
{
private:
    vector<char> bigNum;
    bool sign; // true là - flase là +
    void deleteDigit0(bigIntNum &) const;
    void signOfZero(bigIntNum &) const;

public:
    long long int digit()
    {
        return    bigNum.size();
    }
    bigIntNum();                                                 // constructor mặc định
    bigIntNum(const string &);                                   // constructor khởi tạo bằng string
    bigIntNum(const bigIntNum &);                                // copy constructor
    bigIntNum(long long int);                                    // constructor khởi tạo bằng long long int cho phép chuyển kiểu ngầm định
    const bigIntNum &operator=(const bigIntNum &);               // chồng chập toán tử gán
    const bigIntNum &operator=(long long int);                   // có thể không cần do đã có constructer copy tự chuyển kiểu
    friend ostream &operator<<(ostream &, const bigIntNum &);    // toán tử  xuất
    friend istream &operator>>(istream &, bigIntNum &);          // toán tử nhập
    friend bool operator>(const bigIntNum &, const bigIntNum &); // so sánh
    friend bool operator<(const bigIntNum &, const bigIntNum &); // so sánh
    friend bool operator==(const bigIntNum &, const bigIntNum &);
    friend bool operator!=(const bigIntNum &, const bigIntNum &);
    friend bool operator>=(const bigIntNum &, const bigIntNum &);
    friend bool operator<=(const bigIntNum &, const bigIntNum &);
    bool operator==(long long int);                               // có thể không cần do đã có constructer copy tự chuyển kiểu
    bigIntNum Babs(int = 0) const;                                // toán tử lấy giá trị tuyệt đối
    bigIntNum operator-() const;                                  // toán tử đảo dấu.
    bigIntNum operator*(const bigIntNum &)const;                  // toán tử nhân
    bigIntNum operator*(long long int)const;                      // toán tử nhân số nguyên
    friend bigIntNum operator*(long long int, const bigIntNum &); // toán tử nhân số nguyên giao hoán
    bigIntNum operator-(const bigIntNum &) const;                 // toán tử +
    bigIntNum operator+(const bigIntNum &) const;
    bigIntNum operator%(const bigIntNum &) const;                 // toán tử -
    friend bigIntNum operator+(long long int, const bigIntNum &); // hoán vị
    friend bigIntNum operator-(long long int, const bigIntNum &); // hoán vị
    const bigIntNum &operator*=(const bigIntNum &);
    const bigIntNum &operator-=(const bigIntNum &);
    const bigIntNum &operator+=(const bigIntNum &);
    const bigIntNum &operator/=(const bigIntNum &);
    const bigIntNum &operator++(); // prefix
    bigIntNum operator++(int);     // postfix
    const bigIntNum &operator--(); // prefix
    bigIntNum operator--(int);     //postfix
    bigIntNum operator/(const bigIntNum &) const;
    friend bigIntNum operator/(long long int,const bigIntNum&);

};
#endif