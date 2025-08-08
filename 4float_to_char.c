#include <stdio.h>
#include <string.h>
#include <math.h>

// 方法1：使用指针类型转换
void method1(float a, float b, char arr[8]) {
    // 将第一个float存入数组前4个字节
    char* ptr = (char*)&a;
    for (int i = 0; i < 4; i++) {
        arr[i] = ptr[i];
    }
    
    // 将第二个float存入数组后4个字节
    ptr = (char*)&b;
    for (int i = 0; i < 4; i++) {
        arr[i + 4] = ptr[i];
    }
}

void extract1(const char arr[8], float* a, float* b) {
    *a = *(float*)&arr[0];
    *b = *(float*)&arr[4];
}

// 方法2：使用memcpy函数
void method2(float a, float b, char arr[8]) {
    memcpy(arr, &a, 4);       // 复制第一个float
    memcpy(arr + 4, &b, 4);   // 复制第二个float
}

void extract2(const char arr[8], float* a, float* b) {
    memcpy(a, arr, 4);
    memcpy(b, arr + 4, 4);
}

// 方法3：使用联合体(union)
union FloatToChar {
    float f;
    char c[4];
};

void method3(float a, float b, char arr[8]) {
    union FloatToChar converter;
    
    converter.f = a;
    for (int i = 0; i < 4; i++) {
        arr[i] = converter.c[i];
    }
    
    converter.f = b;
    for (int i = 0; i < 4; i++) {
        arr[i + 4] = converter.c[i];
    }
}

void extract3(const char arr[8], float* a, float* b) {
    union FloatToChar converter;
    
    for (int i = 0; i < 4; i++) {
        converter.c[i] = arr[i];
    }
    *a = converter.f;
    
    for (int i = 0; i < 4; i++) {
        converter.c[i] = arr[i + 4];
    }
    *b = converter.f;
}

// 计算两个float的绝对差值
float calculateDifference(float original, float extracted) {
    return fabsf(original - extracted);
}

int main() {
    // 原始的两个float数值
    float original1 = 3.1415926535f;
    float original2 = 2.7182818284f;
    char array[8];
    
    // 存储提取出的数值
    float extracted1, extracted2;
    
    // 测试方法1
    method1(original1, original2, array);
    extract1(array, &extracted1, &extracted2);
    printf("方法1:\n");
    printf("  原始值: %.10f, %.10f\n", original1, original2);
    printf("  提取值: %.10f, %.10f\n", extracted1, extracted2);
    printf("  差值:   %.10e, %.10e\n\n", 
           calculateDifference(original1, extracted1),
           calculateDifference(original2, extracted2));
    
    // 测试方法2
    method2(original1, original2, array);
    extract2(array, &extracted1, &extracted2);
    printf("方法2:\n");
    printf("  原始值: %.10f, %.10f\n", original1, original2);
    printf("  提取值: %.10f, %.10f\n", extracted1, extracted2);
    printf("  差值:   %.10e, %.10e\n\n", 
           calculateDifference(original1, extracted1),
           calculateDifference(original2, extracted2));
    
    // 测试方法3
    method3(original1, original2, array);
    extract3(array, &extracted1, &extracted2);
    printf("方法3:\n");
    printf("  原始值: %.10f, %.10f\n", original1, original2);
    printf("  提取值: %.10f, %.10f\n", extracted1, extracted2);
    printf("  差值:   %.10e, %.10e\n", 
           calculateDifference(original1, extracted1),
           calculateDifference(original2, extracted2));
    
    return 0;
}
