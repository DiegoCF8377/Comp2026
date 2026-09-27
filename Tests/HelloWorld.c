#include <stdio.h>
int sum(int a, int b){
    return a + b;
}
int main() {
    //comentario
    /*Comentarios */
    printf("%d suma", sum(10,20));
    int num = 22;
    printf("%zu bytes ", sizeof(num));
    num = 12888;
    printf("%zu bytes pf 128 ", sizeof(num));
    return 0;
}