
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class BigInt {
private:
    vector<int> digits;
    bool negative;

    void removeLeadingZeros() {
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        if (digits.size() == 1 && digits[0] == 0)
            negative = false;
    }

public:
    BigInt() : negative(false) {}

    BigInt(string num) {
        negative = false;
        if (num[0] == '-') {
            negative = true;
            num = num.substr(1);
        }
        for (int i = num.size() - 1; i >= 0; --i)
            digits.push_back(num[i] - '0');
        removeLeadingZeros();
    }

    void print() const {
        if (negative && !(digits.size() == 1 && digits[0] == 0)) cout << "-";
        for (auto it = digits.rbegin(); it != digits.rend(); ++it)
            cout << *it;
        cout << endl;
    }

    BigInt operator+(const BigInt& other) const {
        if (negative == other.negative) {
            BigInt result;
            result.negative = negative;
            int carry = 0;
            for (size_t i = 0; i < max(digits.size(), other.digits.size()) || carry; ++i) {
                int sum = carry;
                if (i < digits.size()) sum += digits[i];
                if (i < other.digits.size()) sum += other.digits[i];
                result.digits.push_back(sum % 10);
                carry = sum / 10;
            }
            return result;
        }
        return *this - (-other);
    }

    BigInt operator-(const BigInt& other) const {
        if (negative != other.negative) {
            return *this + (-other);
        }

        if (abs() < other.abs()) {
            return -(other - *this);
        }

        BigInt result;
        result.negative = negative;
        int borrow = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            int sub = digits[i] - borrow - (i < other.digits.size() ? other.digits[i] : 0);
            if (sub < 0) {
                sub += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits.push_back(sub);
        }
        result.removeLeadingZeros();
        return result;
    }

    BigInt operator*(const BigInt& other) const {
        BigInt result;
        result.digits.resize(digits.size() + other.digits.size());
        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < other.digits.size() || carry; ++j) {
                long long mul = result.digits[i + j] + (long long)digits[i] * (j < other.digits.size() ? other.digits[j] : 0) + carry;
                result.digits[i + j] = mul % 10;
                carry = mul / 10;
            }
        }
        result.negative = negative != other.negative;
        result.removeLeadingZeros();
        return result;
    }

    BigInt operator/(const BigInt& other) const {
        if (other == BigInt("0"))
            throw runtime_error("Division by zero");

        BigInt dividend = abs();
        BigInt divisor = other.abs();
        BigInt result, current;
        result.digits.resize(dividend.digits.size());

        for (int i = dividend.digits.size() - 1; i >= 0; --i) {
            current.digits.insert(current.digits.begin(), dividend.digits[i]);
            current.removeLeadingZeros();
            int x = 0, l = 0, r = 9;
            while (l <= r) {
                int m = (l + r) / 2;
                BigInt temp = divisor * BigInt(to_string(m));
                if (temp <= current) {
                    x = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
            result.digits[i] = x;
            current = current - divisor * BigInt(to_string(x));
        }
        result.negative = negative != other.negative;
        result.removeLeadingZeros();
        return result;
    }

    BigInt operator%(const BigInt& other) const {
        return *this - (*this / other) * other;
    }

    BigInt pow(BigInt exp) const {
        BigInt base = *this;
        BigInt result("1");
        while (exp < BigInt("0")) {
            if ((exp.digits[0] % 2) == 1)
                result = result * base;
            base = base * base;
            exp = exp / BigInt("2");
        }
        return result;
    }

    BigInt operator-() const {
        BigInt result = *this;
        if (digits.size() == 1 && digits[0] == 0) return result;
        result.negative = !negative;
        return result;
    }

    bool operator<(const BigInt& other) const {
        if (negative != other.negative)
            return negative;

        if (digits.size() != other.digits.size())
            return negative ? digits.size() > other.digits.size() : digits.size() < other.digits.size();

        for (int i = digits.size() - 1; i >= 0; --i) {
            if (digits[i] != other.digits[i])
                return negative ? digits[i] > other.digits[i] : digits[i] < other.digits[i];
        }
        return false;
    }

    bool operator==(const BigInt& other) const {
        return digits == other.digits && negative == other.negative;
    }

    bool operator<=(const BigInt& other) const {
        return *this < other || *this == other;
    }

    BigInt abs() const {
        BigInt result = *this;
        result.negative = false;
        return result;
    }
};

int main() {
    BigInt a, b;
    string num1, num2;
    cout << "Enter first big number: ";
    cin >> num1;
    cout << "Enter second big number: ";
    cin >> num2;

    a = BigInt(num1);
    b = BigInt(num2);

    cout << "\nSum: ";
    (a + b).print();

    cout << "Difference: ";
    (a - b).print();

    cout << "Product: ";
    (a * b).print();

    cout << "Quotient: ";
    try {
        (a / b).print();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    cout << "Remainder: ";
    try {
        (a % b).print();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    cout << "Power (a^b): ";
    try {
        a.pow(b).print();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
