#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "Vector.h"

#include "Matrix.h"

/**********************/
/*   MAIN FUNCTIONS   */
/**********************/

Matrix *createMatrix(const size_t num_rows, const size_t num_cols, const float value)
{
    if (num_rows == 0u || num_cols == 0u)
        return NULL;

    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));

    if (matrix == NULL)
        return NULL;

    size_t array_size = (num_cols * num_rows);

    matrix->data = (float *)malloc(array_size * sizeof(float));

    if (matrix->data == NULL)
    {
        free(matrix);
        return NULL;
    }

    matrix->num_cols = num_cols;
    matrix->num_rows = num_rows;

    for (size_t i = 0u; i < array_size; i++)
    {
        matrix->data[i] = value;
    }

    return matrix;
}

Matrix *freeMatrix(Matrix *matrix)
{
    if (matrix == NULL)
        return NULL;

    if (matrix->data != NULL)
    {
        free(matrix->data);
        matrix->data = NULL;
    }

    free(matrix);
    return NULL;
}

/**********************/
/*  HELPER FUNCTIONS  */
/**********************/

size_t matrixIndex(const size_t num_cols, const size_t i, const size_t j)
{
    if (num_cols == 0u)
        return 0u;

    return ((i * num_cols) + j);
}

size_t matrixNumElements(const Matrix *matrix)
{
    if (matrix == NULL || matrix->data == NULL)
        return 0u;

    return (matrix->num_cols * matrix->num_rows);
}

bool matrixSameSize(const Matrix *matrix1, const Matrix *matrix2)
{
    if (matrix1 == NULL || matrix1->data == NULL || matrix2 == NULL || matrix2->data == NULL)
        return false;

    return (matrixNumElements(matrix1) == matrixNumElements(matrix2));
}

bool matrixMultiplyPossible(const Matrix *matrix1, const Matrix *matrix2)
{
    if (matrix1 == NULL || matrix1->data == NULL || matrix2 == NULL || matrix2->data == NULL)
        return false;

    return (matrix1->num_cols == matrix2->num_rows);
}

/**********************/
/*  I/O FUNCTIONS     */
/**********************/

void printMatrix(const Matrix *matrix)
{
    if (matrix == NULL || matrix->data == NULL)
        return;

    printf("\n\n[");

    for (size_t i = 0u; i < matrix->num_rows; i++)
    {

        printf("[");

        for (size_t j = 0u; j < matrix->num_cols; j++)
        {
            size_t idx = matrixIndex(matrix->num_cols, i, j);

            printf("%f", matrix->data[idx]);

            if (j < (matrix->num_cols - 1u))
            {
                printf(", ");
            }
        }

        printf("]");

        if (i < (matrix->num_rows - 1u))
        {
            printf("\n");
        }
    }

    printf("]\n");
}

/**********************/
/*  MATH FUNCTIONS    */
/**********************/

Matrix *addMatrix(const Matrix *matrix1, const Matrix *matrix2)
{
    if (matrix1 == NULL || matrix1->data == NULL || matrix2 == NULL || matrix2->data == NULL)
        return NULL;

    if (!matrixSameSize(matrix1, matrix2))
        return NULL;

    Matrix *result = createMatrix(matrix1->num_rows, matrix1->num_cols, 0.0f);

    if (result == NULL)
        return NULL;

    for (size_t i = 0u; i < matrixNumElements(matrix1); i++)
    {
        result->data[i] = (matrix1->data[i] + matrix2->data[i]);
    }

    return result;
}

Matrix *subMatrix(const Matrix *matrix1, const Matrix *matrix2)
{
    if (matrix1 == NULL || matrix1->data == NULL || matrix2 == NULL || matrix2->data == NULL)
        return NULL;

    if (!matrixSameSize(matrix1, matrix2))
        return NULL;

    Matrix *result = createMatrix(matrix1->num_rows, matrix1->num_cols, 0.0f);

    if (result == NULL)
        return NULL;

    for (size_t i = 0u; i < matrixNumElements(matrix1); i++)
    {
        result->data[i] = (matrix1->data[i] - matrix2->data[i]);
    }

    return result;
}

Matrix *multiplyMatrix(const Matrix *matrix1, const Matrix *matrix2)
{
    if (matrix1 == NULL || matrix1->data == NULL || matrix2 == NULL || matrix2->data == NULL)
        return NULL;

    if (!matrixMultiplyPossible(matrix1, matrix2))
        return NULL;

    Matrix *result = createMatrix(matrix1->num_rows, matrix2->num_cols, 0.0f);

    if (result == NULL)
        return NULL;

    for (size_t i = 0u; i < result->num_rows; i++)
    {
        for (size_t j = 0u; j < result->num_cols; j++)
        {
            size_t idx_re = matrixIndex(result->num_cols, i, j);

            for (size_t k = 0u; k < matrix1->num_cols; k++)
            {
                size_t idx_m1 = matrixIndex(matrix1->num_cols, i, k);
                size_t idx_m2 = matrixIndex(matrix2->num_cols, k, j);

                result->data[idx_re] += (matrix1->data[idx_m1] * matrix2->data[idx_m2]);
            }
        }
    }

    return result;
}

Matrix *multiplyMatrixByScalar(const Matrix *matrix, const float scalar)
{
    if (matrix == NULL || matrix->data == NULL)
        return NULL;

    Matrix *result = createMatrix(matrix->num_rows, matrix->num_cols, 0.0f);

    if (result == NULL)
        return NULL;

    for (size_t i = 0u; i < matrixNumElements(matrix); i++)
    {
        result->data[i] = (matrix->data[i] * scalar);
    }

    return result;
}

Matrix *divideMatrixByScalar(const Matrix *matrix, const float scalar)
{
    if (matrix == NULL || matrix->data == NULL || scalar == 0.0f)
        return NULL;

    Matrix *result = createMatrix(matrix->num_rows, matrix->num_cols, 0.0f);

    if (result == NULL)
        return NULL;

    for (size_t i = 0u; i < matrixNumElements(matrix); i++)
    {
        result->data[i] = (matrix->data[i] / scalar);
    }

    return result;
}
