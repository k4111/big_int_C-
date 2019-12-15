#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctype.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include "bigIntNum.h"
using namespace std;

void bigIntNum::deleteDigit0(bigIntNum &a) const
{
    if (a.bigNum.size() == 1) // trường hợp là số 1 chữ số
        return;
    for (int i = a.bigNum.size() - 1; i >= 1; --i)
    {
        if (a.bigNum[i] == '0')
            a.bigNum.pop_back(); // xóa số 0
        else
        {
            return;
        }
    }
}
inline void bigIntNum::signOfZero(bigIntNum &a) const
{
    if (a.bigNum.size() == 1 && a.bigNum[0] == '0') // chỉnh dấu số 0
    {
        a.sign = false;
    }
}
bigIntNum::bigIntNum() : sign(false) // Khởi tạo mặc định là 0.
{
    bigNum.push_back('0');
}
bigIntNum::bigIntNum(const string &str) // khởi tạo bằng string
{
    if (str.length() == 0)
    {
        cout << "ERROR String Length is invalid\n";
        throw("ERROR");
    }
    if (str.at(0) == '-')
    {
        if (str.length() == 2 && str.at(1) == '0') // trường hợp bằng -0
            this->sign = false;
        else
            this->sign = true;
    }
    else
    {
        this->sign = false;
    }
    for (int i = str.length() - 1; i >= 0; --i)
    {
        if (!isdigit(str.at(i)) && str.at(0) != '-')
        {
            cout << "ERROR String Length is invalid\n";
            throw("ERROR");
        }
        if (str.at(i) == '-')
            break;
        bigNum.push_back(str.at(i));
    }
    deleteDigit0(*this); // xóa số 0 nếu chuỗi có số 0 đằng trc
}
bigIntNum::bigIntNum(const bigIntNum &r) // copy constucter
{
    if (this != &r)
    {
        bigNum.clear();
        sign = r.sign;
        if (r.bigNum.size() == 1) // giải quyết khi chỉ có 1 phần tử trong r
        {
            bigNum.push_back(r.bigNum[0]);
        }
        else
            bigNum.assign(r.bigNum.begin(), r.bigNum.end());
    }
}
bigIntNum::bigIntNum(long long int a)
{
    this->bigNum.clear();
    if (a == 0)
    {
        this->sign = false;
        this->bigNum.push_back('0');
    }
    else if (a < 0)
    {
        this->sign = true;
    }
    else
    {
        this->sign = false;
    }
    a = abs(a);
    while (a != 0)
    {
        this->bigNum.push_back((a % 10) + 48);
        a /= 10;
    }
}
ostream &operator<<(ostream &os, const bigIntNum &r) // chồng chập toán tử xuất
{
    if (r.sign == true)
    {
        os << '-';
    }
    for (int i = r.bigNum.size() - 1; i >= 0; --i)
    {
        os << r.bigNum[i];
    }
    return os;
}
istream &operator>>(istream &is, bigIntNum &r) // chồng chập toán tử nhập
{
    r.bigNum.clear();
    string buffer;
    is >> buffer;
    if (buffer.length() == 0)
    {
        cout << "ERROR String Length is invalid\n";
        throw("ERROR");
    }
    if (buffer.at(0) == '-')
    {
        r.sign = true;
    }
    else
    {
        r.sign = false;
    }
    for (int i = buffer.length() - 1; i >= 0; --i)
    {
        if (!isdigit(buffer.at(i)) && buffer.at(0) != '-')
        {
            cout << "ERROR String Length is invalid\n";
            throw("ERROR");
        }
        if (buffer.at(i) == '-')
            break;
        r.bigNum.push_back(buffer.at(i));
    }
    r.deleteDigit0(r);
    r.signOfZero(r);
    return is;
}
const bigIntNum &bigIntNum::operator=(long long int a)
{
    this->bigNum.clear();
    if (a == 0)
    {
        this->sign = false;
        this->bigNum.push_back('0');
        return *this;
    }
    else if (a < 0)
    {
        this->sign = true;
    }
    else
    {
        this->sign = false;
    }
    a = abs(a);
    while (a != 0)
    {
        this->bigNum.push_back((a % 10) + 48);
        a /= 10;
    }
    return *this;
}
const bigIntNum &bigIntNum::operator=(const bigIntNum &r)
{
    if (this != &r)
    {
        bigNum.clear();
        sign = r.sign;
        if (r.bigNum.size() == 1) // giải quyết khi chỉ có 1 phần tử trong r
        {
            bigNum.push_back(r.bigNum[0]);
        }
        else
            bigNum.assign(r.bigNum.begin(), r.bigNum.end());
    }
    return *this;
}
bool bigIntNum::operator==(long long int a)
{
    bigIntNum temp = a;
    return *this == temp;
}
bool operator==(const bigIntNum &a, const bigIntNum &b)
{
    if (a.sign != b.sign)
        return false;
    if (a.bigNum.size() != b.bigNum.size())
        return false;
    for (int i = 0; i < a.bigNum.size(); ++i)
    {
        if (a.bigNum[i] != b.bigNum[i])
            return false;
    }
    return true;
}
bool operator!=(const bigIntNum &a, const bigIntNum &b)
{
    return !(a == b);
}
bool operator>(const bigIntNum &a, const bigIntNum &b)
{
    if (a == b)
        return false;
    //sign 0 là + , sign 1 là -
    if (a.sign == false && b.sign == true)
        return true;
    if (a.sign == true && b.sign == false)
        return false;
    if (a.sign == false) // dấu của 2 số đều là dương.
    {
        if (a.bigNum.size() > b.bigNum.size())
        {
            return true;
        }
        else if (a.bigNum.size() < b.bigNum.size())
            return false;
        else
        {
            for (int i = a.bigNum.size() - 1; i >= 0; --i)
            {
                if (a.bigNum[i] > b.bigNum[i])
                    return true;
                if (a.bigNum[i] < b.bigNum[i])
                    return false;
            }
        }
    }
    return !((-a) > (-b));
}
bool operator<(const bigIntNum &a, const bigIntNum &b)
{
    if (a == b || a > b)
        return false;
    return true;
}
bool operator<=(const bigIntNum &a, const bigIntNum &b)
{
    return !(a > b);
}
bool operator>=(const bigIntNum &a, const bigIntNum &b)
{
    return !(a < b);
}
bigIntNum bigIntNum::operator-() const
{
    bigIntNum temp = *this;
    if (temp == 0)
        return temp;
    temp.sign = !this->sign;
    signOfZero(temp);
    return temp;
}
bigIntNum bigIntNum::operator+(const bigIntNum &a) const
{
    if (this->sign == a.sign) // chỉ xét cộng số cùng dấu
    {
        if (this->bigNum.size() <= a.bigNum.size())
        {
            short carry = 0; // tạo biến nhớ.
            int length = a.bigNum.size();
            bigIntNum temp = a; // gán biến temp cho số mình cộng
            for (int i = 0; i < length; ++i)
            {
                int tempInt = 0;
                tempInt = (i < this->bigNum.size() ? (this->bigNum[i] - 48) : 0) + (temp.bigNum[i] - 48) + carry; // kiểm tra khi mà số t cộng hết chữ số thì + 0
                if (tempInt > 9)
                {
                    temp.bigNum[i] = (tempInt - 10) + 48;
                    carry = 1;
                }
                else
                {
                    temp.bigNum[i] = tempInt + 48;
                    carry = 0;
                }
            }
            if(carry !=0)
            {
                temp.bigNum.push_back('1');
            }
            signOfZero(temp);
            deleteDigit0(temp);
            return temp;
        }
        return (a+*this);
    }
    return *this - (-a); // trường hợp cộng 2 số trái dấu đưa về phép trừ.
    // ví dụ *this là -, a là + thì sẽ thành - - - thành trừ 2 số cùng dấu.
    // ví dụ *this là + ,a là - thì thành + - + thành trừ 2 số cùng dấu.
}
bigIntNum operator+(long long int k, const bigIntNum &a)
{
    return (a + k);
}
bigIntNum bigIntNum::Babs(int) const // lấy giá trị tuyệt đối.
{
    bigIntNum temp = *this;
    temp.sign = false;
    return temp;
}
bigIntNum bigIntNum::operator-(const bigIntNum &a) const
{
    if (this->sign == a.sign) // chỉ xét trừ 2 số cùng dấu.
    {
        if (this->Babs() >= a.Babs()) // chỉ xét với số bị trừ có giá trị tuyệt đối lớn hơn số trừ ( đồng nghĩa số chữ số lớn hơn hoặc = )
        {
            bigIntNum temp = *this; // mình gán temp = this;
            short carry = 0;        // tạo biến nhớ.
            int length = this->bigNum.size() > a.bigNum.size() ? this->bigNum.size() : a.bigNum.size();
            for (int i = 0; i < length || carry == 1; ++i)
            {
                int tempInt = 0;
                tempInt = (temp.bigNum[i] - 48) - carry - (i < a.bigNum.size() ? (a.bigNum[i] - 48) : 0); // kiểm tra nếu bắt đầu số trừ mà hết chữ số thì trừ đi 0
                if (tempInt < 0)
                {
                    temp.bigNum[i] = tempInt + 10 + 48;
                    carry = 1;
                }
                else
                {
                    temp.bigNum[i] = tempInt + 48;
                    carry = 0;
                }
            }
            signOfZero(temp);
            deleteDigit0(temp);
            return temp;
        }
        else
        {
            return -(a - *this); // ( truong hop this có số phần tử nhỏ hơn a). tính a - *this xong đảo dấu :))~.
            // do bên trên gán temp = this. nên mình luôn coi là this có số phần tử > a;
            // khi ta dùng a - *this là coi như t truyền một lần nữa với a->this, this->a do a có chữ số nhiều hơn
            // xong t đảo dấu thì sẽ ra đáp án
        }
    }
    else
    {
        return *this + (-a);
        // trường hợp trừ 2 số trái dấu đưa về phép cộng.
        // ví dụ nếu this -, a + thì sẽ thành - + - là thành cộng 2 số âm(cùng dấu)
        // ví dụ nếu this +, a- thì thành +  + + là cộng 2 số dương.
    }
}
bigIntNum operator-(long long int k, const bigIntNum &a)
{
    return -(a - k);
}
bigIntNum bigIntNum::operator*(long long int k) const
{
    if (k == 0)
    {
        return bigIntNum();
    }
    bigIntNum temp = *this;
    int carry = 0;                                             // biến nhớ.
    for (int i = 0; i < temp.bigNum.size() || carry != 0; ++i) // khi mà vẫn còn carry thì vẫn thêm phần tử vào vector để lưu trữ
    {
        int tempInt = 1;
        if (i == temp.bigNum.size()) // nếu thiếu chữ số thì tăng thêm
        {
            temp.bigNum.push_back('0');
        }
        tempInt = (temp.bigNum[i] - 48) * k + carry; // phép nhân
        if (tempInt / 10 != 0)                       // thuật toán để thêm.
        {
            carry = tempInt / 10;
            temp.bigNum[i] = (tempInt % 10) + 48;
        }
        else
        {
            temp.bigNum[i] = tempInt + 48;
            carry = 0;
        }
    }
    return temp;
}
bigIntNum operator*(long long int k, const bigIntNum &a)
{
    if (k == 0)
    {
        return bigIntNum();
    }
    bigIntNum temp = a;
    int carry = 0; // biến nhớ.
    for (int i = 0; i < temp.bigNum.size() || carry != 0; ++i)
    {
        int tempInt = 1;
        if (i == temp.bigNum.size())
        {
            temp.bigNum.push_back('0');
        }
        tempInt = (temp.bigNum[i] - 48) * k + carry;
        if (tempInt / 10 != 0)
        {
            carry = tempInt / 10;
            temp.bigNum[i] = (tempInt % 10) + 48;
        }
        else
        {
            temp.bigNum[i] = tempInt + 48;
            carry = 0;
        }
    }
    return temp;
}
bigIntNum bigIntNum::operator*(const bigIntNum &a) const
{
    if (this->sign == a.sign) // cùng dấu
    {
        if (this->Babs() >= a.Babs()) // lấy số có chữ số lớn hơn làm mốc.
        {
            bigIntNum temp;
            bigIntNum temp2 = this->Babs();           // gán giá trị dương của this cho temp2
            bigIntNum tempAdd;                        // biến để biểu diễn phép nhân từng số cho this
            for (int i = 0; i < a.bigNum.size(); ++i) // chỉ nhân đén hết chữ số của a
            {
                tempAdd = temp2 * (a.bigNum[i] - 48);
                for (int j = 0; j < i; ++j) // sau mỗi lần nhân thì số đó sẽ nhiều chữ số hơn số trc nó 1 chữ số 0;
                {
                    tempAdd.bigNum.insert(tempAdd.bigNum.begin(), '0');
                }
                temp = temp + tempAdd; // cộng các phép tính nhân riêng lẻ
            }
            return temp;
        }
        else
        {
            return a * (*this); // t mặc định cho this nhiều số hơn. nếu a nhiều hơn thì cho ngược lại
        }
    }
    else
    {
        return -(this->Babs() * a.Babs()); // trường hợp 2 số trái dấu.
    }
}
const bigIntNum &bigIntNum::operator*=(const bigIntNum &a)
{
    bigIntNum temp = *this;
    *this = temp * a;
    return *this;
}
const bigIntNum &bigIntNum::operator/=(const bigIntNum &a)
{
    bigIntNum temp = *this;
    *this = temp / a;
    return *this;
}
const bigIntNum &bigIntNum::operator-=(const bigIntNum &a)
{
    bigIntNum temp = *this;
    *this = temp - a;
    return *this;
}
const bigIntNum &bigIntNum::operator+=(const bigIntNum &a)
{
    bigIntNum temp = *this; // tạo biến tạm
    *this = temp + a;
    return *this;
}
const bigIntNum &bigIntNum::operator++()
{
    bigIntNum temp = *this;
    *this = temp + 1;
    return *this;
}
bigIntNum bigIntNum::operator++(int)
{
    bigIntNum temp = *this;
    ++(*this);
    return temp;
}
const bigIntNum &bigIntNum::operator--()
{
    bigIntNum temp = *this;
    *this = temp - 1;
    return *this;
}
bigIntNum bigIntNum::operator--(int)
{
    bigIntNum temp = *this;
    --(*this);
    return temp;
}
bigIntNum bigIntNum::operator/(const bigIntNum &a) const
{
    if (a == 0)
        throw("WRONG !!! cannot /0");
    if (this->sign == a.sign)
    {
        if (a.sign == false)
        {
            if (this->bigNum.size() < a.bigNum.size()) // trường hợp chia số có ít chữ  số hơn
                return bigIntNum();                    // trả về 0;
            bigIntNum temp = a, final;
            temp.bigNum.assign(this->bigNum.end() - a.bigNum.size(), this->bigNum.end()); // khởi tạo temp sao cho có số chữ số bằng với số chia
            int i = this->bigNum.size() - a.bigNum.size(), j;                             // đánh dấu vị trí i là độ dài điểm cuối mình lấy chữ số
            while (i != -1)
            {
                for (j = 1; j <= 10; ++j) // chạy tìm thương
                {
                    if (a * j > temp)
                    {
                        temp = temp - a * (j - 1);
                        final.bigNum.push_back(j - 1 + 48);
                        break;
                    }
                }
                if (i != 0)
                    temp.bigNum.insert(temp.bigNum.begin(), this->bigNum[i - 1]); // ngăn trường hợp tiến đến vector vị trí -1;
                deleteDigit0(temp);                                               // xóa 0 ở temp
                --i;
            }
            reverse(final.bigNum.begin(), final.bigNum.end()); // đảo chiều của vector // thư viên algorithm
            deleteDigit0(final);
            return final;
        }
        else
        {
            return (-*this) / (-a);
        }
    }
    return -(this->Babs() / a.Babs());
}
bigIntNum bigIntNum::operator%(const bigIntNum &a) const
{
    if (a == 0)
        throw("WRONG !!! cannot /0");
    if (this->sign == a.sign)
    {
        if (a.sign == false)
        {
            if (this->bigNum.size() < a.bigNum.size()) // trường hợp chia số có ít chữ  số hơn
                return *this;
            bigIntNum temp = a;
            temp.bigNum.assign(this->bigNum.end() - a.bigNum.size(), this->bigNum.end()); // khởi tạo temp sao cho có số chữ số bằng với số chia
            int i = this->bigNum.size() - a.bigNum.size(), j;                             // đánh dấu vị trí i là độ dài điểm cuối mình lấy chữ số
            while (i != -1)
            {
                for (j = 1; j <= 10; ++j) // chạy tìm thương
                {
                    if (a * j > temp)
                    {
                        temp = temp - a * (j - 1);
                        break;
                    }
                }
                if (i != 0)
                    temp.bigNum.insert(temp.bigNum.begin(), this->bigNum[i - 1]); // ngăn trường hợp tiến đến vector vị trí -1;
                deleteDigit0(temp);                                               // xóa 0 ở temp
                --i;
            }
            return temp;
        }
        return (-*this) % (-a);
    }
    return -(this->Babs() % a.Babs());
}
bigIntNum operator/(long long int a,const bigIntNum& k)
{
    bigIntNum temp = a;
    return temp/k;
}