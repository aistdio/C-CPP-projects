#ifndef DATA_IO_H
#include "../data_libs/data_io.h"
#endif
#ifndef DATA_STAT_H
#include "../data_libs/data_stat.h"
#endif
#ifndef DATA_PROCESS_H
#include "../data_module/data_process.h"
#endif
#ifndef DECISION_H
#include "../yet_another_decision_module/decision.h"
#endif

int main() {
    double *data = NULL;
    int n = 0;

    printf("LOAD DATA...\n");
    int error = input(&data, &n);
    if (error) {
        printf("ERROR");
    } else {
        printf("RAW DATA:\n\t");
        output(data, n);

        printf("\nNORMALIZED DATA:\n\t");
        normalization(data, n);
        output(data, n);

        printf("\nSORTED NORMALIZED DATA:\n\t");
        sort(data, n);
        output(data, n);

        printf("\nFINAL DECISION:\n\t");
        if (make_decision(data, n))
            printf("YES");
        else
            printf("NO");
    }
    if (n > 0) free(data);
    return 0;
}
