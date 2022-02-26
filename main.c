/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2021年05月20日 星期四 01时16分06秒
 ************************************************************************/

#include <stdio.h>
#include <haizei/test.h>

double add(double a, double b) {
    return a + b;
}

// 一组测试用例
TEST(testfunc, add) { // testfunc.add
    EXPECT_EQ(add(2, 3), 5); // 断言EXPECT_EQ
    EXPECT_NE(add(1, 3), 4);
    EXPECT_EQ(add(2, 2), 3);
    EXPECT_EQ(add(0, 1), 1);
}

TEST(testfunc, add2) {
    EXPECT_EQ(add(2, 0), 2);
    EXPECT_GE(add(1, 3), 4);
    EXPECT_EQ(add(2, 2), 4);
    EXPECT_GT(add(0, 1), 1);
}

TEST(test, funcadd) { // test.funcadd
    EXPECT_EQ(add(0, 1), 1);
    EXPECT_LE(add(-2, -3), -5);
    EXPECT_LT(add(0, -3), 3);
    EXPECT_EQ(add(1, -1), 0);
}

int main() {
    return RUN_ALL_TESTS(); // 运行且输出
    // return 0; 可以运行不输出
}
