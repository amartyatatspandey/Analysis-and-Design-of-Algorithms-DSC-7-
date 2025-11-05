#include <iostream>
#include <vector>
#include <cmath>

// Use the namespace as requested in your preferences
using namespace std;

// Define a simple matrix type using vector of vectors
typedef vector<vector<int>> Matrix;

// Define the crossover point for switching to standard multiplication
// For a real-world use case, this would be much larger (e.g., 64 or 128)
// and found through performance testing.
#define LEAF_SIZE 2

/**
 * @brief Prints a matrix to the console.
 * @param mat The matrix to print.
 */
void printMatrix(const Matrix& mat) {
    int n = mat.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
}

/**
 * @brief Performs standard (naive) matrix multiplication.
 * Used as the base case for the recursion.
 * @param A The first matrix.
 * @param B The second matrix.
 * @return The resulting matrix C = A * B.
 */
Matrix standardMultiplication(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

/**
 * @brief Adds two matrices: C = A + B.
 * @param A The first matrix.
 * @param B The second matrix.
 * @return The resulting matrix.
 */
Matrix add(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

/**
 * @brief Subtracts two matrices: C = A - B.
 * @param A The first matrix.
 * @param B The second matrix.
 * @return The resulting matrix.
 */
Matrix subtract(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

/**
 * @brief Implements Strassen's divide and conquer algorithm.
 * @param A The first N x N matrix.
 * @param B The second N x N matrix.
 * @return The resulting matrix C = A * B.
 */
Matrix strassen(const Matrix& A, const Matrix& B) {
    int n = A.size();

    // Base Case: If the matrix is small enough, use standard multiplication
    if (n <= LEAF_SIZE) {
        return standardMultiplication(A, B);
    }

    // --- Divide Phase ---
    // Divide matrices into 4 sub-matrices of size n/2
    int newSize = n / 2;
    Matrix A11(newSize, vector<int>(newSize));
    Matrix A12(newSize, vector<int>(newSize));
    Matrix A21(newSize, vector<int>(newSize));
    Matrix A22(newSize, vector<int>(newSize));
    Matrix B11(newSize, vector<int>(newSize));
    Matrix B12(newSize, vector<int>(newSize));
    Matrix B21(newSize, vector<int>(newSize));
    Matrix B22(newSize, vector<int>(newSize));

    // Fill the sub-matrices
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            A11[i][j] = A[i][j];             // Top-Left
            A12[i][j] = A[i][j + newSize];   // Top-Right
            A21[i][j] = A[i + newSize][j];   // Bottom-Left
            A22[i][j] = A[i + newSize][j + newSize]; // Bottom-Right

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // --- Conquer Phase ---
    // Calculate the 7 Strassen products recursively.
    
    // P1 = (A11 + A22) * (B11 + B22)
    Matrix P1 = strassen(add(A11, A22), add(B11, B22));
    
    // P2 = (A21 + A22) * B11
    Matrix P2 = strassen(add(A21, A22), B11);
    
    // P3 = A11 * (B12 - B22)
    Matrix P3 = strassen(A11, subtract(B12, B22));
    
    // P4 = A22 * (B21 - B11)
    Matrix P4 = strassen(A22, subtract(B21, B11));
    
    // P5 = (A11 + A12) * B22
    Matrix P5 = strassen(add(A11, A12), B22);
    
    // P6 = (A21 - A11) * (B11 + B12)
    Matrix P6 = strassen(subtract(A21, A11), add(B11, B12));
    
    // P7 = (A12 - A22) * (B21 + B22)
    Matrix P7 = strassen(subtract(A12, A22), add(B21, B22));

    // --- Combine Phase ---
    // Calculate the 4 sub-matrices of the result C

    // C11 = P1 + P4 - P5 + P7
    Matrix C11 = add(subtract(add(P1, P4), P5), P7);
    
    // C12 = P3 + P5
    Matrix C12 = add(P3, P5);
    
    // C21 = P2 + P4
    Matrix C21 = add(P2, P4);
    
    // C22 = P1 - P2 + P3 + P6
    Matrix C22 = add(add(subtract(P1, P2), P3), P6);

    // Join the 4 sub-matrices into the final result matrix C
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
    
    return C;
}


int main() {
    // Example with 4x4 matrices (will trigger one level of recursion)
    Matrix A = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 1, 2, 3},
        {4, 5, 6, 7}
    };

    Matrix B = {
        {8, 7, 6, 5},
        {4, 3, 2, 1},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    };

    cout << "Matrix A:" << endl;
    printMatrix(A);
    cout << "\nMatrix B:" << endl;
    printMatrix(B);

    // Calculate result using Strassen
    Matrix C_Strassen = strassen(A, B);

    // Calculate result using standard multiplication for verification
    Matrix C_Standard = standardMultiplication(A, B);

    cout << "\nResult from Strassen's Algorithm (C = A * B):" << endl;
    printMatrix(C_Strassen);

    cout << "\nResult from Standard Multiplication (for verification):" << endl;
    printMatrix(C_Standard);

    // Verification check
    bool correct = true;
    int n = A.size();
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if (C_Strassen[i][j] != C_Standard[i][j]) {
                correct = false;
                break;
            }
        }
        if(!correct) break;
    }

    if(correct) {
        cout << "\nVerification: SUCCESS! Strassen's result matches standard result." << endl;
    } else {
        cout << "\nVerification: FAILED! Results do not match." << endl;
    }

    return 0;
}