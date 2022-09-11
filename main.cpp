#include <iostream>
#include <vector>

class big_integer {
    int m_size;
    int* m_nums;
public:
    big_integer(const std::string str) {
        m_size = str.length();
        m_nums = new int[m_size + 1];
        for (int i = 0; i < m_size; i++) {
            m_nums[i] = str[m_size - 1 - i] - 48;
        }
    }
    big_integer(const big_integer& other) {
        m_size = other.m_size;
        m_nums = new int[other.m_size * 1.25];
        for (int i=0; i<other.m_size; i++) {
            m_nums[i] = other.m_nums[i];
        }
    }
    big_integer(big_integer&& other) {
        m_size = other.m_size;
        m_nums = new int[other.m_size * 1.25];
        for (int i=0; i<other.m_size; i++) {
            m_nums[i] = other.m_nums[i];
        }
    }
    ~big_integer() {
        delete[] m_nums;
        m_nums = nullptr;
    }
    big_integer& operator =(big_integer &other) {
        if (this != &other) {
            m_size = other.m_size;
            delete[] m_nums;
            m_nums = new int[other.m_size + 1];
            for (int i=0; i<other.m_size; i++) {
                m_nums[i] = other.m_nums[i];
            }
        }
        return *this;
    }
    big_integer& operator =(big_integer &&other) {
        if (this != &other) {
            m_size = other.m_size;
            delete[] m_nums;
            m_nums = new int[other.m_size + 1];
            for (int i=0; i<other.m_size; i++) {
                m_nums[i] = other.m_nums[i];
            }
        }
        return *this;
    }
    big_integer operator +(big_integer &other) {
        for (int i = 0; i < std::max(m_size,other.m_size); i++) {
            if ((i < m_size) && (i < other.m_size)) {
                m_nums[i] = m_nums[i] + other.m_nums[i];
            }
            if ((i < m_size) && (i >= other.m_size)) {
                m_nums[i] = m_nums[i];
            }
            if ((i >= m_size) && (i < other.m_size)) {
                m_nums[i] = other.m_nums[i];
            }
            if (m_nums[i] > 9) {
                m_nums[i] -= 10;
                m_nums[i+1] += 1;
            }
        }
        return *this;
    }
    big_integer operator *(big_integer &other) {
        for (int i = 0; i < std::max(m_size,other.m_size); i++) {
            if ((i < m_size) && (i < other.m_size)) {
                m_nums[i] = m_nums[i] * other.m_nums[i];
            }
            if ((i < m_size) && (i >= other.m_size)) {
                m_nums[i] = m_nums[i];
            }
            if ((i >= m_size) && (i < other.m_size)) {
                m_nums[i] = other.m_nums[i];
            }
            while (m_nums[i] > 9) {
                m_nums[i] -= 10;
                m_nums[i+1] += 1;
            }
        }
        return *this;
    }
    friend std::ostream& operator <<(std::ostream& stream, const big_integer integer) {
        for (int i=integer.m_size-1; i>=0 ; i--) {
            stream << integer.m_nums[i];
        }
        return stream;
    }
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << std::endl;; // 193099
    return 0;
}