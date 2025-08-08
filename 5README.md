# 三维向量运算库（vector3f）说明文档

## 项目简介
本项目实现了一个用于三维向量运算的函数库，支持三维向量的基本运算（加、减、点乘、叉乘等），并提供了基于该库求解几何问题的示例代码。

## 文件结构.
├── vector3f.h      // 向量结构体定义及函数声明
├── vector3f.c      // 向量运算函数的实现
├── solve_cube.c    // 使用向量库求解几何题的示例代码
└── README.md       // 说明文档
## 功能说明

### 向量结构体定义typedef struct {
    float x;  // x分量
    float y;  // y分量
    float z;  // z分量
} vector3f;
### 核心函数列表
| 函数名                  | 功能描述                                   | 函数原型                                      |
|-------------------------|--------------------------------------------|-----------------------------------------------|
| vector3f_add            | 向量加法运算                               | vector3f vector3f_add(const vector3f v1, const vector3f v2) |
| vector3f_sub            | 向量减法运算                               | vector3f vector3f_sub(const vector3f v1, const vector3f v2) |
| vector3f_dot            | 向量点乘运算，返回标量结果                 | float vector3f_dot(const vector3f v1, const vector3f v2) |
| vector3f_cross          | 向量叉乘运算，返回新向量                   | vector3f vector3f_cross(const vector3f v1, const vector3f v2) |
| vector3f_magnitude      | 计算向量的模长                             | float vector3f_magnitude(const vector3f v) |
| vector3f_normalize      | 向量单位化（将向量转换为模长为1的单位向量） | vector3f vector3f_normalize(const vector3f v) |
| vector3f_scale          | 向量数乘运算（向量与标量相乘）             | vector3f vector3f_scale(const vector3f v, float scalar) |
| vector3f_print          | 打印向量内容（调试用）                     | void vector3f_print(const vector3f v) |

## 编译与运行方法

### 命令行编译
1. 确保所有文件在同一目录下
2. 打开命令行终端，进入文件所在目录
3. 执行以下命令进行编译：
   ```bash
   # 编译向量库实现文件
   gcc -c vector3f.c -o vector3f.o
   
   # 编译主程序并链接向量库
   gcc solve_cube.c vector3f.o -o solve_cube
   ```

### 运行程序
编译成功后，执行生成的可执行文件：# Windows系统
solve_cube.exe

# Linux/macOS系统
./solve_cube
### IDE环境使用
如果使用IDE（如Dev-C++、Code::Blocks、Visual Studio等）：
1. 创建一个新项目
2. 将所有文件添加到项目中
3. 编译并运行项目（通常使用F5或菜单栏的运行选项）

## 常见问题解决

### 头文件找不到错误
如果编译时出现类似 `[Error] vector3f.h: No such file or directory` 的错误：
1. 检查所有文件是否在同一目录下
2. 确认文件名拼写正确（C语言区分大小写）
3. 确保在IDE中将文件正确添加到项目中
4. 若文件不在同一目录，需在编译命令中指定头文件路径：
   ```bash
   gcc solve_cube.c vector3f.o -I/path/to/header -o solve_cube
   ```
   其中 `/path/to/header` 替换为实际的头文件路径

### 链接错误
如果出现函数未定义的链接错误：
1. 确保已编译 `vector3f.c` 生成 `vector3f.o` 文件
2. 确保链接时包含了 `vector3f.o` 文件

## 使用示例
`solve_cube.c` 文件展示了如何使用该向量库求解正方体中的几何问题，包括：
1. 点到直线的距离计算
2. 直线到平面的距离计算

通过修改该文件，可以利用向量库解决更多三维空间中的几何问题。
    