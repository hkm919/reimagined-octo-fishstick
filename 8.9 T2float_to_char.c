#include <stdio.h>
#include <string.h>

int main() {
    // 定义两个float类型的原始值
    float f1 = 59.622f;
    float f2 = 92.6327f;
    
    // 定义长度为4*2=8的char数组（每个float占4字节）
    char arr[8];
    
    // 将float值存入char数组
    // 方法1：使用memcpy进行内存拷贝（更安全）
    memcpy(arr, &f1, sizeof(float));
    memcpy(arr + sizeof(float), &f2, sizeof(float));
    
    // 从char数组中提取float值
    float extracted_f1, extracted_f2;
    memcpy(&extracted_f1, arr, sizeof(float));
    memcpy(&extracted_f2, arr + sizeof(float), sizeof(float));
    
    // 输出结果并比较误差
    printf("原始值1: %.10f\n", f1);
    printf("提取值1: %.10f\n", extracted_f1);
    printf("误差1:   %.10f\n\n", extracted_f1 - f1);
    
    printf("原始值2: %.10f\n", f2);
    printf("提取值2: %.10f\n", extracted_f2);
    printf("误差2:   %.10f\n", extracted_f2 - f2);
    
    return 0;
}
