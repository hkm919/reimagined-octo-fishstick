#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// 矩阵结构体定义
typedef struct MParam {
    uint8_t row;       // 矩阵行数
    uint8_t column;    // 矩阵列数
    float **data;      // 矩阵数据
} *Matrix;

// 创建指定大小的矩阵
Matrix createMatrix(uint8_t row, uint8_t column) {
    // 为矩阵结构体分配内存
    Matrix mat = (Matrix)malloc(sizeof(struct MParam));
    if (mat == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }
    
    // 设置矩阵维度
    mat->row = row;
    mat->column = column;
    
    // 为行指针分配内存
    mat->data = (float **)malloc(row * sizeof(float *));
    if (mat->data == NULL) {
        printf("内存分配失败！\n");
        free(mat);
        return NULL;
    }
    
    // 为每行数据分配内存
    for (uint8_t i = 0; i < row; i++) {
        mat->data[i] = (float *)malloc(column * sizeof(float));
        if (mat->data[i] == NULL) {
            printf("内存分配失败！\n");
            // 释放已分配的内存
            for (uint8_t j = 0; j < i; j++) {
                free(mat->data[j]);
            }
            free(mat->data);
            free(mat);
            return NULL;
        }
    }
    
    return mat;
}

// 从键盘输入矩阵元素
void inputMatrix(Matrix mat) {
    if (mat == NULL) return;
    
    printf("请输入%d行%d列矩阵的元素：\n", mat->row, mat->column);
    for (uint8_t i = 0; i < mat->row; i++) {
        for (uint8_t j = 0; j < mat->column; j++) {
            printf("第%d行第%d列元素：", i + 1, j + 1);
            scanf("%f", &mat->data[i][j]);
        }
    }
}

// 计算矩阵的转置矩阵
Matrix transposeMatrix(Matrix mat) {
    if (mat == NULL) return NULL;
    
    // 创建转置矩阵（行列互换）
    Matrix transposed = createMatrix(mat->column, mat->row);
    if (transposed == NULL) return NULL;
    
    // 填充转置矩阵数据
    for (uint8_t i = 0; i < mat->row; i++) {
        for (uint8_t j = 0; j < mat->column; j++) {
            transposed->data[j][i] = mat->data[i][j];
        }
    }
    
    return transposed;
}

// 计算两个矩阵的乘积
Matrix multiplyMatrix(Matrix mat1, Matrix mat2) {
    // 检查矩阵是否可以相乘（mat1的列数必须等于mat2的行数）
    if (mat1 == NULL || mat2 == NULL || mat1->column != mat2->row) {
        printf("矩阵无法相乘！\n");
        return NULL;
    }
    
    // 创建结果矩阵
    Matrix result = createMatrix(mat1->row, mat2->column);
    if (result == NULL) return NULL;
    
    // 计算矩阵乘积
    for (uint8_t i = 0; i < result->row; i++) {
        for (uint8_t j = 0; j < result->column; j++) {
            result->data[i][j] = 0;
            for (uint8_t k = 0; k < mat1->column; k++) {
                result->data[i][j] += mat1->data[i][k] * mat2->data[k][j];
            }
        }
    }
    
    return result;
}

// 打印矩阵
void printMatrix(Matrix mat, const char *name) {
    if (mat == NULL) return;
    
    printf("\n%s矩阵 (%d行%d列)：\n", name, mat->row, mat->column);
    for (uint8_t i = 0; i < mat->row; i++) {
        for (uint8_t j = 0; j < mat->column; j++) {
            printf("%8.4f ", mat->data[i][j]);
        }
        printf("\n");
    }
}

// 释放矩阵占用的内存
void freeMatrix(Matrix mat) {
    if (mat == NULL) return;
    
    // 释放每行数据
    for (uint8_t i = 0; i < mat->row; i++) {
        free(mat->data[i]);
        mat->data[i] = NULL;
    }
    
    // 释放行指针
    free(mat->data);
    mat->data = NULL;
    
    // 释放矩阵结构体
    free(mat);
}

int main() {
    uint8_t row, column;
    
    // 输入矩阵的行数和列数
    printf("请输入矩阵的行数：");
    scanf("%hhu", &row);
    printf("请输入矩阵的列数：");
    scanf("%hhu", &column);
    
    // 创建并输入矩阵
    Matrix mat = createMatrix(row, column);
    if (mat == NULL) {
        return 1;
    }
    inputMatrix(mat);
    printMatrix(mat, "原始");
    
    // 计算转置矩阵
    Matrix transposed = transposeMatrix(mat);
    if (transposed == NULL) {
        freeMatrix(mat);
        return 1;
    }
    printMatrix(transposed, "转置");
    
    // 计算原始矩阵与转置矩阵的乘积
    Matrix product = multiplyMatrix(mat, transposed);
    if (product == NULL) {
        freeMatrix(mat);
        freeMatrix(transposed);
        return 1;
    }
    printMatrix(product, "原始矩阵与转置矩阵的乘积");
    
    // 释放所有矩阵内存
    freeMatrix(mat);
    freeMatrix(transposed);
    freeMatrix(product);
    
    return 0;
}
