#include <stdio.h>
#include "vm.h"
#include <string.h>

int main() {
    u_int8_t arr[] = {1, 2, 3, 4};
    Byte_Vector v = byte_vector_from(arr, 4);
    return 0;
}