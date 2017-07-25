#ifndef MATRIX_ERROR_H
#define MATRIX_ERROR_H

#include <string>
#include <map>
#include <stdexcept>

namespace iat {
    enum class MatrixErrorCode
    {
        DOT_PRODUCT_OF_BIDIMENSIONAL_MATRIXES = 100,   //100 "Operands must be row-matrixes"
        CROSS_PRODUCT_OF_BIDIMENSIONAL_MATRIXES = 101, //101 "Operands must be row-matrixes and each of them must have only three elements"
        NEGATIVE_MATRIX_SIZE_PARAMETERS = 102,         //102 "Could not create matrix with negative number of rows or columns"
        COULD_NOT_READ_MATRIX_INPUT_FILE = 103,        //103 "File with matrix data not found"
        INDEXES_OUT_OF_BOUNDS = 104,                   //104 "Indexes out of bounds"
        ROW_INDEX_OUT_OF_BOUNDS = 105,                 //105 "Row index out of bounds"
        COLUMN_INDES_OUT_OF_BOUNDS = 106,              //106 "Column index out of bounds"
        COMPLEX_NUMBER_COMPARISON = 107,               //107 "Comparison operation for complex number is not defined"
        RIGHT_HAND_SIDE_OPERAND_ROW_COUNT_ERROR = 108, //108 "Row counts of the operands are not equal
        SINGULAR_MATRIX_INVERSION = 109,               //109 "Could not inverse matrix with zero determinant"
        RECTANGULAR_MATRIX_INVERSION = 110,            //110 "Could not inverse rectangular matrix"
        RECTANGULAR_MATRIX_DETERMINANT = 111,          //111"Rectangular matrix has no determinant"
        NEGATIVE_EXPONENT = 112,                       //112std::invalid_argument("exponent");
        COULD_NOT_POWER_RECTANGULAR_MATRIX = 120,      //Could not power rectangular matrix"
        NON_QUADRATIC_MATRIX_OF_EQUATION_SYSTEM = 113, //113"Matrix of the system must be quadratic"
        SINGULAR_MATRIX_OF_EQUATION_SYSTEM = 114,      //114"Matrix rows is linearly dependent"
        NORM_OF_BIDIMENSIONAL_MATRIX = 115,            //115"Matrix must have only one row"
        NOT_EQUAL_OPERANDS_DIMENSIONS = 116,           //116"Dimensions of the operands do not coincide"
        MATRIX_MULTIPLICATION_ERROR = 117,             //117"Row count of the first matrix and column count of the second matrix are not equal"
        MATRIX_DIVISION_BY_ZERO = 118,                  //118"Division by zero"
        DIRECION_COSINES_OF_BIMENSIONAL_MATRIX = 121,  //121"Matrix must be a 3D-vector to calculate direction cosines"
        UNKNOWN_ERROR = 119
    };

    class ErrorMatrix : public std::runtime_error
    {
        public:
            explicit ErrorMatrix():
            std::runtime_error("ErrorMatrix"),
            _reason(MatrixErrorCode::UNKNOWN_ERROR) {}
            explicit ErrorMatrix(MatrixErrorCode code):
            std::runtime_error("ErrorMatrix"),
            _reason(code) {}
            const char* what() const throw() override;
        private:
            MatrixErrorCode _reason;
            static const std::map<MatrixErrorCode, std::string> _matrixErrors;
            static std::map<MatrixErrorCode, std::string> createMap();
    };
}
#endif // MATRIX_ERROR_H
