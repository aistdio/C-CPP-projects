#include "data_process.h"
#ifndef DATA_STAT_H
#include "../data_libs/data_stat.h"
#endif
#ifndef MATH_H
#include <math.h>
#endif

int normalization(double *data, int n) {
    int result = 1;
    double max_value = 0, min_value = 0;

    max_value = max(data, n);
    min_value = min(data, n);

    double size = max_value - min_value;

    if (fabs(size) > EPS) {
        for (int i = 0; i < n; i++) {
            data[i] = data[i] / size - min_value / size;
        }
    } else {
        result = 0;
    }

    return result;
}
