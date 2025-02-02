#include <bits/stdc++.h>
using namespace std;

class BigInt
{
    string digits;

public:
    // Constructors:
    BigInt(unsigned long long n = 0);
    BigInt(const string &s);     // Constructor for std::string
    BigInt(const char *s);       // Constructor for C-style string
    BigInt(const BigInt &other); // Copy constructor

    // Helper Functions:
    friend void divide_by_2(BigInt &a);
    friend bool Null(const BigInt &);
    friend int Length(const BigInt &);
    char &operator[](const int); 

    /* * * * Operator Overloading * * * */

    // Direct assignment
    BigInt &operator=(const BigInt &);

    // Addition and Subtraction
    friend BigInt &operator+=(BigInt &, const BigInt &); // for chaining
    friend BigInt operator+(const BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt &operator-=(BigInt &, const BigInt &); // for chaining

    // Comparison operators
    friend bool operator==(const BigInt &, const BigInt &);
    friend bool operator!=(const BigInt &, const BigInt &);

    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);
    friend bool operator<(const BigInt &, const BigInt &);
    friend bool operator<=(const BigInt &, const BigInt &);

    // Multiplication and Division
    friend BigInt &operator*=(BigInt &, const BigInt &);
    friend BigInt operator*(const BigInt &, const BigInt &);
    friend BigInt &operator/=(BigInt &, const BigInt &);
    friend BigInt operator/(const BigInt &, const BigInt &);

    // Modulo
    friend BigInt operator%(const BigInt &, const BigInt &);
    friend BigInt &operator%=(BigInt &, const BigInt &);

    // Power Function
    friend BigInt &operator^=(BigInt &, const BigInt &);
    friend BigInt operator^(BigInt &, const BigInt &);

    // Square Root Function
    friend BigInt sqrt(BigInt &a);

    // Read and Write
    friend ostream &operator<<(ostream &, const BigInt &); // for chaining
    friend istream &operator>>(istream &, BigInt &);       // we are modifying the input object

    // Others
    BigInt NthFibonacci(int n);
    BigInt Factorial(int n);
};

BigInt::BigInt(const string &s)
{
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0; i--)
    {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}

BigInt::BigInt(unsigned long long nr)
{
    do
    {
        digits.push_back(nr % 10);
        nr /= 10;
    } while (nr);
}
BigInt::BigInt(const char *s)
{
    digits = "";
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        if (!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}

BigInt::BigInt(const BigInt &a)
{
    digits = a.digits;
}

bool Null(const BigInt &a)
{
    if (a.digits.size() == 1 && a.digits[0] == 0)
        return true;
    return false;
}
int Length(const BigInt &a)
{
    return a.digits.size();
}
char &BigInt::operator[](const int index)
{
    if (digits.size() <= index || index < 0)
        throw("ERROR");
    return digits[index];
}
bool operator==(const BigInt &a, const BigInt &b)
{
    return a.digits == b.digits;
}
bool operator!=(const BigInt &a, const BigInt &b)
{
    return !(a == b);
}
bool operator<(const BigInt &a, const BigInt &b)
{
    int n = Length(a), m = Length(b);
    if (n != m)
        return n < m;
    while (n--)
        if (a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
    return false;
}
bool operator>(const BigInt &a, const BigInt &b)
{
    return b < a;
}
bool operator>=(const BigInt &a, const BigInt &b)
{
    return !(a < b);
}
bool operator<=(const BigInt &a, const BigInt &b)
{
    return !(a > b);
}

BigInt &BigInt::operator=(const BigInt &a)
{
    digits = a.digits;
    return *this;
}

BigInt &operator+=(BigInt &a, const BigInt &b)
{
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if (m > n)
        a.digits.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n; i++)
    {
        if (i < m)
            s = (a.digits[i] + b.digits[i]) + t;
        else
            s = a.digits[i] + t;
        t = s / 10;
        a.digits[i] = (s % 10);
    }
    if (t)
        a.digits.push_back(t);
    return a;
}
BigInt operator+(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp += b;
    return temp;
}

BigInt &operator-=(BigInt &a, const BigInt &b)
{
    if (a < b)
        throw("UNDERFLOW");
    int n = Length(a), m = Length(b);
    int i, t = 0, s;
    for (i = 0; i < n; i++)
    {
        if (i < m)
            s = a.digits[i] - b.digits[i] + t;
        else
            s = a.digits[i] + t;
        if (s < 0)
            s += 10,
                t = -1;
        else
            t = 0;
        a.digits[i] = s;
    }
    while (n > 1 && a.digits[n - 1] == 0) // removing leading zeroes
        a.digits.pop_back(),
            n--;
    return a;
}
BigInt operator-(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp -= b;
    return temp;
}

BigInt &operator*=(BigInt &a, const BigInt &b) // O(n*m)
{
    if (Null(a) || Null(b))
    {
        a = BigInt();
        return a;
    }
    int n = a.digits.size(), m = b.digits.size();
    vector<int> v(n + m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            v[i + j] += (a.digits[i]) * (b.digits[j]);
        }
    n += m;
    a.digits.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++)
    {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.digits[i] = v[i];
    }
    for (int i = n - 1; i >= 1 && !v[i]; i--) // removing leading zeroes
        a.digits.pop_back();
    return a;
}
BigInt operator*(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp *= b;
    return temp;
}

BigInt &operator/=(BigInt &a, const BigInt &b) // O(n*m)
{
    if (Null(b))
        throw("Arithmetic Error: Division By 0");
    if (a < b)
    {
        a = BigInt();
        return a;
    }
    if (a == b)
    {
        a = BigInt(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0); // to store quotients
    BigInt t;              // remainder
    for (i = n - 1; t * 10 + a.digits[i] < b; i--)
    {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--)
    {
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t; cc--)
            ;
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a.digits.resize(cat.size());
    for (i = 0; i < lgcat; i++)
        a.digits[i] = cat[lgcat - i - 1];
    a.digits.resize(lgcat);
    return a;
}
BigInt operator/(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp /= b;
    return temp;
}

BigInt &operator%=(BigInt &a, const BigInt &b)
{
    if (Null(b))
        throw("Arithmetic Error: Division By 0");
    if (a < b)
    {
        return a;
    }
    if (a == b)
    {
        a = BigInt();
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b; i--)
    {
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--)
    {
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t; cc--)
            ;
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a = t;
    return a;
}
BigInt operator%(const BigInt &a, const BigInt &b)
{
    BigInt temp;
    temp = a;
    temp %= b;
    return temp;
}

BigInt &operator^=(BigInt &a, const BigInt &b) // O(log(b) * m^2)     m -> no.of digits in a
{
    BigInt Exponent, Base(a);
    Exponent = b;
    a = 1;
    while (!Null(Exponent))
    {
        if (Exponent[0] & 1)
            a *= Base;
        Base *= Base;
        divide_by_2(Exponent);
    }
    return a;
}
BigInt operator^(BigInt &a, BigInt &b)
{
    BigInt temp(a);
    temp ^= b;
    return temp;
}

void divide_by_2(BigInt &a) // O(m)
{
    int add = 0;
    for (int i = a.digits.size() - 1; i >= 0; i--)
    {
        int digit = (a.digits[i] >> 1) + add;
        add = ((a.digits[i] & 1) * 5);
        a.digits[i] = digit;
    }
    while (a.digits.size() > 1 && !a.digits.back())
        a.digits.pop_back();
}

BigInt sqrt(BigInt &a) // o(m^2 log a)
{
    BigInt left(1), right(a), v(1), mid, prod;
    divide_by_2(right);
    while (left <= right)
    {
        mid += left;
        mid += right;
        divide_by_2(mid);
        prod = (mid * mid);
        if (prod <= a)
        {
            v = mid;
            mid += 1;
            left = mid;
        }
        else
        {
            mid -= 1;
            right = mid;
        }
        mid = BigInt();
    }
    return v;
}

BigInt NthFibonacci(int n) // o(n*m)        m->no.of digits in largest number
{
    BigInt a(1), b(1), c;
    if (!n)
        return c;
    n--;
    while (n--)
    {
        c = a + b;
        b = a;
        a = c;
    }
    return b;
}

BigInt Factorial(int n) // O(n^2logn)
{
    BigInt f(1);
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}

istream &operator>>(istream &in, BigInt &a)
{
    string s;
    in >> s;
    int n = s.size();
    for (int i = n - 1; i >= 0; i--)
    {
        if (!isdigit(s[i]))
            throw("INVALID NUMBER");
        a.digits[n - i - 1] = s[i];
    }
    return in;
}

ostream &operator<<(ostream &out, const BigInt &a)
{
    for (int i = a.digits.size() - 1; i >= 0; i--)
        cout << (short)a.digits[i];
    return cout;
}

// Driver code with some examples
int main()
{
    BigInt first("12345");
    cout << "The number of digits"
         << " in first big integer = "
         << Length(first) << '\n';
    BigInt second(12345);
    if (first == second)
    {
        cout << "first and second are equal!\n";
    }
    else
        cout << "Not equal!\n";
    BigInt third("10000");
    BigInt fourth("100000");
    if (third < fourth)
    {
        cout << "third is smaller than fourth!\n";
    }
    BigInt fifth("10000000");
    if (fifth > fourth)
    {
        cout << "fifth is larger than fourth!\n";
    }

    // Printing all the numbers
    cout << "first = " << first << '\n';
    cout << "second = " << second << '\n';
    cout << "third = " << third << '\n';
    cout << "fourth = " << fourth << '\n';
    cout << "fifth = " << fifth << '\n';

    BigInt sum;
    sum = (fourth + fifth);
    cout << "Sum of fourth and fifth = "
         << sum << '\n';
    BigInt product;
    product = second * third;
    cout << "Product of second and third = "
         << product << '\n';

    // Print the fibonacci number from 1 to 100
    cout << "-------------------------Fibonacci"
         << "------------------------------\n";
    for (int i = 0; i <= 100; i += 10)
    {
        BigInt Fib;
        Fib = NthFibonacci(i);
        cout << "Fibonacci " << i << " = " << Fib << '\n';
    }

    // Calculating factorial of from 1 to 100
    cout << "-------------------------Factorial"
         << "------------------------------\n";
    for (int i = 0; i <= 100; i += 10)
    {
        BigInt fact;
        fact = Factorial(i);
        cout << "Factorial of "
             << i << " = ";
        cout << fact << '\n';
    }
}
