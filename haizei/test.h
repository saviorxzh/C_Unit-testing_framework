/*************************************************************************
	> File Name: test.h
	> Author: xuzheheng
	> Mail: 
	> Created Time: 2021年08月23日 星期一 06时20分44秒
 ************************************************************************/

#ifndef _TEST_H
#define _TEST_H
#include <haizei/linklist.h>

// #运算符将一个宏的参数转换为字符串字面量
// "\033[" "32" "m" --> "\033[32m", 否则等于"\033[" (space) "m", a不加#因为a本身就是字符串
#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
#define COLOR_HL(a, b) "\033[1;" #b "m" a "\033[0m" // 1高亮

#define GREEN(a) COLOR(a, 32)
#define RED(a) COLOR(a, 31)
#define BLUE(a) COLOR(a, 34)
#define YELLOW(a) COLOR(a, 33)
#define PURPLE(a) COLOR(a, 35)

#define GREEN_HL(a) COLOR_HL(a, 32)
#define RED_HL(a) COLOR_HL(a, 31)
#define BLUE_HL(a) COLOR_HL(a, 34)
#define YELLOW_HL(a) COLOR_HL(a, 33)
#define PURPLE_HL(a) COLOR_HL(a, 35)

// TEST宏展开：声明 + 注册函数(名字必须不同)
// ##运算符可以将两个记号（例如标识符）“粘”在一起，成为一个记号(注意不是粘为字符串)
// add_function()参数1为函数指针，参数2为字符串
#define TEST(a, b) \
void a##_haizei_##b();\
__attribute__((constructor))\
void add##_haizei_##a##_haizei_##b() {\
    add_function(a##_haizei_##b, #a "." #b);\
}\
void a##_haizei_##b()

// 泛型宏
#define Type(a) _Generic((a),\
    int : "%d",\
    double : "%lf",\
    float : "%f",\
    long long : "%lld",\
    const char * : "%s",\
    char * : "%s"\
)

#define P(a, color) {\
    char frm[1000];\
    sprintf(frm, color("%s"), Type(a));\
    printf(frm, a);\
}

#define EXPECT(a, b, comp) {\
    haizei_test_info.total += 1;\
    __typeof(a) _a = (a);\
    __typeof(b) _b = (b);\
    if (_a comp _b) haizei_test_info.success += 1;\
    else {\
        printf("\n");\
        printf(YELLOW("\t%s:%d: failure\n"), __FILE__, __LINE__);\
        printf(YELLOW_HL("\t\texpect : " #a " " #comp " " #b "\n\t\t" "actual : "));\
        P(_a, YELLOW_HL);\
        printf(YELLOW_HL(" vs "));\
        P(_b, YELLOW_HL);\
        printf("\n\n");\
    }\
    printf(GREEN("[-----------] "));\
    printf("%s %s %s  %s\n", #a, #comp, #b, _a comp _b ? GREEN("True") : RED("Flase"));\
}

#define EXPECT_EQ(a, b) EXPECT(a, b, ==)
#define EXPECT_NE(a, b) EXPECT(a, b, !=)
#define EXPECT_LT(a, b) EXPECT(a, b, <)
#define EXPECT_LE(a, b) EXPECT(a, b, <=)
#define EXPECT_GT(a, b) EXPECT(a, b, >)
#define EXPECT_GE(a, b) EXPECT(a, b, >=)

typedef void (*TestFuncT)(); // typedef提升为类型，TestFuncT为函数指针类型
typedef struct Function {
    TestFuncT func;    // 函数指针
    const char *str;   // 记录函数名的字符串
    struct LinkNode p; // 指向下一个节点p值
} Function;

struct FunctionInfo {
    int total, success;
};
extern struct FunctionInfo haizei_test_info; // 变量声明，后面肯定有定义

void add_function(TestFuncT, const char *);
int RUN_ALL_TESTS();
#endif
