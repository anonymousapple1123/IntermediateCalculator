#include <iostream>
#include <vector>
using namespace std;

class Matrix {
    vector<vector<int>> data;

public:
    Matrix(vector<vector<int>> d) : data(d) {}

    void print() const {
        for (const auto& row : data) {
            for (int val : row) {
                cout << val << " "; // Added missing semicolon here
            }
            cout << endl;
        }
    }

    Matrix add(const Matrix& other) const {        vector<vector<int>> result(data.size(), vector<int>(data[0].size()));
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                result[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return Matrix(result);
    }

    Matrix subtract(const Matrix& other) const {
        vector<vector<int>> result(data.size(), vector<int>(data[0].size()));
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                result[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return Matrix(result);
    }

    Matrix multiply(const Matrix& other) const {
        vector<vector<int>> result(data.size(), vector<int>(other.data[0].size(), 0));
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < other.data[0].size(); ++j) {
                for (size_t k = 0; k < data[0].size(); ++k) {
                    result[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return Matrix(result);
    }

    Matrix transpose() const {
        vector<vector<int>> result(data[0].size(), vector<int>(data.size()));
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                result[j][i] = data[i][j];
            }
        }
        return Matrix(result);
    }
};

int main() {
    Matrix A({{1, 2, 3}, {4, 5, 6}});
    Matrix B({{7, 8, 9}, {10, 11, 12}});

    cout << "Matrix A:" << endl;
    A.print();
    cout << "Matrix B:" << endl;
    B.print();

    Matrix C = A.add(B);
    cout << "A + B:" << endl;
    C.print();

    Matrix D = A.subtract(B);
    cout << "A - B:" << endl;
    D.print();

    Matrix E = A.multiply(Matrix({{1, 2}, {3, 4}, {5, 6}}));
    cout << "A * B:" << endl; // Corrected output label
    E.print();

    Matrix F = A.transpose();
    cout << "Transpose of A:" << endl;
    F.print();

    return 0;
}
