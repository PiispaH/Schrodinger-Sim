#include <stdio.h>

void test_schrodinger();
void test_utils();
void test_window();

int main() {
    test_schrodinger();
    test_utils();
    test_window();
    printf("\nAll tests passed\n\n");

    return 0;
}
