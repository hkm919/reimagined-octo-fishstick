#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比较函数，用于qsort
int compareFloats(const void *a, const void *b) {
    // 将void指针转换为float指针，再取值
    float floatA = *(const float *)a;
    float floatB = *(const float *)b;
    
    // 比较两个float值
    if (floatA < floatB) return -1;
    if (floatA > floatB) return 1;
    return 0;
}

int main() {
    float *numbers = NULL;
    int count = 0;
    float input;
    char buffer[100];
    
    printf("请输入float类型的数据（每行一个，输入非数字结束）：\n");
    
    // 读取输入直到用户输入非数字
    while (1) {
        // 读取一行输入
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }
        
        // 检查是否为空行（仅回车）
        if (buffer[0] == '\n') {
            break;
        }
        
        // 尝试将输入转换为float
        if (sscanf(buffer, "%f", &input) != 1) {
            break;
        }
        
        // 重新分配内存以容纳新元素
        float *temp = (float *)realloc(numbers, (count + 1) * sizeof(float));
        if (temp == NULL) {
            printf("内存分配失败！\n");
            free(numbers);
            return 1;
        }
        
        numbers = temp;
        numbers[count] = input;
        count++;
    }
    
    // 使用qsort排序
    if (count > 0) {
        qsort(numbers, count, sizeof(float), compareFloats);
        
        // 输出排序结果
        printf("\n排序后的结果（从小到大）：\n");
        for (int i = 0; i < count; i++) {
            printf("%.6f ", numbers[i]);
        }
        printf("\n");
    } else {
        printf("没有输入有效的数据！\n");
    }
    
    // 释放分配的内存
    free(numbers);
    return 0;
}
    