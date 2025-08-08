#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int main() {
    // 初始化随机数生成器，使用当前时间作为种子
    srand((unsigned int)time(NULL));
    
    // 定义32位无符号整数，用于存储结果
    uint32_t result = 0;
    
    // 生成32个0~100范围内的随机整数
    for (int n = 1; n <= 32; n++) {
        // 生成0~100的随机整数（rand()%101生成0到100之间的数）
        int num = rand() % 101;
        
        // 如果生成的数大于50，则设置第n位为1
        if (num > 50) {
            // 1左移(n-1)位，然后与result进行或运算，设置第n位为1
            // 注意：第1位对应最低位（2^0），所以需要左移(n-1)位
            result |= (1U << (n - 1));
        }
        
        // 输出当前生成的数和对应位的设置情况（可选，用于验证）
        printf("第%d个数字: %d, 第%d位设置为: %d\n", 
               n, num, n, (num > 50) ? 1 : 0);
    }
    
    // 输出最终结果
    printf("\n最终的32位整数（十进制）: %u\n", result);
    printf("最终的32位整数（十六进制）: 0x%X\n", result);
    printf("最终的32位整数（二进制）: ");
    
    // 以二进制形式输出结果，从最高位到最低位
    for (int i = 31; i >= 0; i--) {
        printf("%d", (result >> i) & 1);
        // 每4位加一个空格，方便阅读
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
    
    return 0;
}
