#include <iostream>
#include <vector>
#include <cassert>

#include "solution.hpp"
#include "function_class.h"

#define Matrix(n, m)    std::vector<std::vector<float>> (n, std::vector<float>(m)) 
#define MatrixType          std::vector<std::vector<float>>

Solution::Solution(
        std::size_t n, 
        std::vector<float> vec_x, 
        std::vector<float> vec_y,
        std::vector<CalculatorFunction *> functions
        )
{
    _size = n;
    _vec_x = vec_x;
    _vec_y = vec_y;
    _functions = functions;
    _func_count = _functions.size();

    _matrix_a = Matrix(_func_count, _func_count);
   // _matrix_a = std::vector<std::vector<float>> (_func_count, std::vector<float>(_func_count));
    _vector_b = std::vector<float> (_func_count);
};
        

Solution::~Solution()
{
};


void Solution::solve()
{
    std::cout << "Start solve" << std::endl;
    // 1) посчитать aij

    std::cout << "Create a_matirx" << std::endl;
    create_a_matrix();
    // 2) посчитать bj

    std::cout << "Create b_vector" << std::endl;
    create_b_vector();

    // 3) создать обратную матрицу
    std::cout << "create_inverse_matrix" << std::endl;
    MatrixType reverse_matrix=Matrix(_func_count, _func_count);
    create_inverse_matrix(reverse_matrix);

    // 4) перемножить обратную матрицу и bj
    std::cout << "multiply_matrices" << std::endl;
    MatrixType mat_vector_b = Matrix(_func_count, 1);
    for (int i=0; i<_func_count; i++) 
        mat_vector_b[i][0] = _vector_b[i];
    MatrixType answer; 
    answer = multiply_matrices(reverse_matrix, mat_vector_b);

    std::cout << "new koefecients:\n";
    print_matrix(answer);
    // 5) пересчитать новые y

    // 6) найти delta 
    // 7) Посчитать j
    last_vivod(answer);
};

void Solution::create_a_matrix()
{
    float temp, phi_k, phi_l;
    for (int k=0; k<_func_count; k++) {
        for (int l=0; l <  _func_count; l++) {
            temp = 0;
            for (int i=0; i<_size; i++) {
                phi_k = _functions[k]->calc(_vec_x[i]);
                phi_l = _functions[l]->calc(_vec_x[i]);
                temp += phi_k * phi_l;
            }
            _matrix_a[k][l] = temp;
            std::cout << _matrix_a[k][l] << " ";
        }
        std::cout << std::endl;
    } 
};


void Solution::create_b_vector()
{
    float temp;
    for (int k=0; k<_func_count; k++) {
        temp = 0;
        for (int i=0; i<_size; i++)
            temp += _vec_y[i] * _functions[k]->calc(_vec_x[i]);
        _vector_b[k] = temp;
        std::cout << _vector_b[k] << " ";
    }
};


void Solution::create_inverse_matrix(MatrixType& reverse_matrix)
{
    int n = _func_count;
    MatrixType matrix = Matrix(n, n+1);
    std::vector<float> answer(n);
    for (int i=0; i<n; i++) 
        for (int j=0; j<n; j++) 
            matrix[i][j] = _matrix_a[i][j];
    
    for (int i=0; i < n; i++) {
        for (int k=0; k<n; k++) {
            matrix[k][n] = 0;
        } 
        matrix[i][n] = 1;
        answer = gauss(matrix);
        for (int k=0; k<n; k++) {
            reverse_matrix[i][k] = answer[k];
        }
    }
};

std::vector<float> Solution::gauss(MatrixType matrix) {
    MatrixType copy_matrix = matrix;
    forward_gauss(copy_matrix);
    return reverse_gauss(copy_matrix);
}

void Solution::forward_gauss(MatrixType &matrix) {
    int n = matrix.size();
    float koef, max_value;
    int max_value_index;
    for (int k=0; k<n; k++) {
        max_value=abs(matrix[k][k]);
        max_value_index=k;

        // Выбор строки
        for (int i=k+1; i<n; i++)
            if (abs(matrix[i][k]) > max_value) {
                max_value = abs(matrix[i][k]);
                max_value_index = i;
            }

        // Ведущий элемент не равен нулю
        assert(matrix[max_value_index][k] != 0);

        // Если необходимо поменять строки местами, то меняем
        if (k != max_value_index) {
            swap_rows(matrix, k, max_value_index);
        }

        /* logging
        std::cout << "\n ***\n"; 
        print_matrix(matrix);
        */
        for (int i=n; i>=k; i--) {
            matrix[k][i] /= matrix[k][k];
        }
        for (int i=k+1; i<n; i++) {
            koef = matrix[i][k]/matrix[k][k];
            for (int j=k+1; j <= n; j++) {
                matrix[i][j] -= matrix[k][j] * koef;
            }
            matrix[i][k] = 0;
        }
    }
}

std::vector<float> Solution::reverse_gauss(MatrixType matrix)
{
    int n = matrix.size();
    std::vector<float> answer(n);
    for (int k=n - 1; k >= 0; k--) {
        for (int i=k+1; i < n; i++) {
            matrix[k][n] -= matrix[k][i] * answer[i];
        }   
        answer[k] = matrix[k][n];
    }
    return answer;
}


void Solution::resize_matrix_for_gauss(MatrixType& matrix, std::vector<float> b)
{
    int n=matrix.size();
    for (int i=0; i<n; i++) {
        matrix[i].push_back(b[i]);
    }
}


MatrixType Solution::multiply_matrices(MatrixType matrix1, MatrixType matrix2)
{
    assert(matrix1[0].size() == matrix2.size());
    int n=matrix1.size(), m=matrix2.size(), k=matrix2[0].size();

    MatrixType answer = Matrix(n, k);
    float temp=0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<k; j++) {
            temp = 0;
            for (int k=0; k<m; k++) {
                temp += matrix1[i][k] * matrix2[k][j];
            }
            answer[i][j] = temp;
        }
    }
    return answer;
}


void Solution::swap_rows(MatrixType &matrix, int i, int j)
{
    int n = matrix.size();
    for (int k=0; k<=n; k++)
        std::swap(matrix[i][k], matrix[j][k]);
}

void Solution::print_matrix(std::vector<float> vec)
{
    int n = vec.size();
    for (int i=0; i<n; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void Solution::print_matrix(MatrixType matrix)
{
    int n = matrix.size(), m = matrix[0].size();
    for (int i=0; i<n; i++) {
        for (int j=0; j < m; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


void Solution::last_vivod(MatrixType koef)
{
    float new_y, delta, max_delta, j=0;
    int max_delta_index;

    for (int i=0; i < _size; i++) {
        new_y = 0;
        for (int k=0; k<_func_count; k++) {
            new_y += koef[k][0] * _functions[k]->calc(_vec_x[i]); 
        }
        delta = new_y - _vec_y[i];
        delta = delta * delta;
        if (i == 0) {
            max_delta_index = i;
            max_delta = delta;
        }
        if (max_delta < delta){
            max_delta = delta;
            max_delta_index = i;
        }
        j += delta;
        std::cout << "new_y and delta: " << new_y << " " << delta << std::endl;
    } 
    std::cout << "max_delta and max_delta_index: " << max_delta << " " << max_delta_index;
    std::cout << std::endl << "J = " << j << std::endl;
}