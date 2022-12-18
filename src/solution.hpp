#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED
#include <vector>

#include "function_class.h"

#define Matrix(n, m)    std::vector<std::vector<float>> (n, std::vector<float>(m)) 
#define MatrixType          std::vector<std::vector<float>>


class Solution
{
private:
    std::size_t _size;
    std::vector<float> _vec_x; 
    std::vector<float> _vec_y;

    float _func_count;
    std::vector<CalculatorFunction*> _functions;

    std::vector<std::vector<float>> _matrix_a;

    std::vector<float> _vector_b;


    void create_a_matrix();
    void create_b_vector();

    void create_inverse_matrix(MatrixType&);


    std::vector<float> gauss(MatrixType);
    void resize_matrix_for_gauss(MatrixType&, std::vector<float>);
    void forward_gauss(MatrixType&);
    std::vector<float> reverse_gauss(MatrixType matrix);
    void swap_rows(MatrixType&, int, int);

    MatrixType transpose_matrix(MatrixType&);
    MatrixType multiply_matrices(MatrixType, MatrixType);
    
    void print_matrix(MatrixType);
    void print_matrix(std::vector<float>);

    void last_vivod(MatrixType);
public:
    Solution(std::size_t, std::vector<float>, std::vector<float>, std::vector<CalculatorFunction*>);
    ~Solution();
    void solve();

};

#endif // SOLUTION_H_INCLUDED
