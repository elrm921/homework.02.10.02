#include <iostream>
#include <vector>

class big_integer {
    int m_size;
    std::vector<int> m_nums;
public:
    big_integer(const std::string str) {
        m_size = str.length();
        for (auto it = str.rbegin(); it != str.rend(); it++) {
            m_nums.push_back(*it - 48);
        }
    }
    big_integer(const big_integer& other) {
        m_size = other.m_size;
        m_nums.clear();
        for (auto it = other.m_nums.begin(); it != other.m_nums.end(); it++) {
            m_nums.push_back(*it);
        }
    }
    big_integer(big_integer&& other) {
        m_size = other.m_size;
        other.m_size = 0;
        m_nums.resize(m_size);
        m_nums = std::move(other.m_nums);
    }
    ~big_integer() {
        std::cout << "destructor called\n";
    }
    big_integer& operator =(big_integer &other) {
        if (this != &other) {
            m_size = other.m_size;
            m_nums.clear();
            for (auto it = other.m_nums.begin(); it != other.m_nums.end(); it++) {
                m_nums.push_back(*it);
            }
        }
        return *this;
    }
    big_integer& operator =(big_integer &&other) {
        if (this != &other) {
            m_size = other.m_size;
            other.m_size = 0;
            m_nums.resize(m_size);
            m_nums = std::move(other.m_nums);
        }
        return *this;
    }
    big_integer operator +(big_integer &other) {
        big_integer res("");
        res.m_size = std::max(m_size,other.m_size);
        for (int i = 0; i < res.m_size; i++) {
            res.m_nums.push_back(0);
        }
        for (int i = 0; i < res.m_size; i++) {
            if ((i < m_size) && (i < other.m_size)) {
                res.m_nums[i] += (m_nums[i] + other.m_nums[i]);
            }
            if ((i < m_size) && (i >= other.m_size)) {
                res.m_nums[i] += (m_nums[i]);
            }
            if ((i >= m_size) && (i < other.m_size)) {
                res.m_nums[i] += (other.m_nums[i]);
            }
            while (res.m_nums[i] > 9) {
                res.m_nums[i] -= 10;
                if (i == res.m_size - 1) {
                    res.m_nums.push_back(0);
                    res.m_size += 1;
                }
                res.m_nums[i+1] += 1;
            }
        }
        return res;
    }
    big_integer operator *(big_integer &other) {
        big_integer res("");
        res.m_size = std::max(m_size,other.m_size);
        for (int i = 0; i < res.m_size; i++) {
            res.m_nums.push_back(0);
        }
        if (m_size >= res.m_size) {
            for (int i = 0; i < m_size; i++) {
                for (int j = 0; j < other.m_size; j++) {
                    res.m_nums[i] += m_nums[i] * other.m_nums[j];
                }
            }
        }
        if (m_size < res.m_size) {
            for (int i = 0; i < other.m_size; i++) {
                for (int j = 0; j < m_size; j++) {
                    res.m_nums[i] += m_nums[j] * other.m_nums[i];
                }
            }
        }
        for (int i = 0; i < res.m_size; i++) {
            while (res.m_nums[i] > 9) {
                res.m_nums[i] -= 10;
                if (i == res.m_size - 1) {
                    res.m_nums.push_back(0);
                    res.m_size += 1;
                }
                res.m_nums[i+1] += 1;
            }
        }
        return res;
    }
    friend std::ostream& operator <<(std::ostream& stream, const big_integer integer) {
        for (auto it = integer.m_nums.rbegin(); it != integer.m_nums.rend() ; it++) {
            stream << *it;
        }
        return stream;
    }
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    //auto number3 = big_integer("9");
    auto result = number1 + number2;
    std::cout << result << std::endl;; // 193099
    return 0;
}