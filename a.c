# 0 "test/includes/fortest/main.c"
# 0 "<interno>"
# 0 "<línea-de-órdenes>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<línea-de-órdenes>" 2
# 1 "test/includes/fortest/main.c"
# 1 "test/includes/fortest/res.h" 1
int res(int a, int b);
# 2 "test/includes/fortest/main.c" 2
# 1 "test/includes/fortest/sum.h" 1
int sum(int a, int b);
# 3 "test/includes/fortest/main.c" 2

int main() {
      int sum_ = sum(1, 2);
      int rest_ = res(2, 1);
      return 0;
}
