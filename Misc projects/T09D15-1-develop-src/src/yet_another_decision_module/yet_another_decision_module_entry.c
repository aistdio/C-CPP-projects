#include "../data_libs/data_io.h"
#include "../data_module/data_process.h"
#include "decision.h"

int main() {
    double *data = NULL;
    int n = 0;
    int error = input(&data, &n);

    if (!error) {
        if (make_decision(data, n))
            printf("YES");
        else
            printf("NO");
    } else {
        printf("ERROR");
    }
    if (n > 0) free(data);
    return 0;
}