// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <limits.h>
#include <openenclave/host.h>
#include <openenclave/internal/error.h>
#include <openenclave/internal/tests.h>
#include <openenclave/bits/report.h>
#include <openenclave/internal/report.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../host/strings.h"

int main(int argc, const char* argv[])
{
    (void)argc;
    (void)argv;


    const size_t max_length = 10000;
    uint8_t buffer[max_length];
    FILE *ptr;
    oe_result_t retval1;
    oe_report_t oe_report = {0};
    size_t fsize;

    // Positive test
    ptr = fopen("../../../tests/qv/host/generated_report.bytes","rb");
    OE_TEST(ptr != NULL);

    fseek(ptr, 0, SEEK_END);
    fsize = (size_t)ftell(ptr);
    fseek(ptr, 0, SEEK_SET);

    OE_TEST(fread(buffer, fsize, 1, ptr) > 0);
    fclose(ptr);

    retval1 = oe_verify_report(NULL, buffer, fsize, &oe_report);

    OE_TEST(retval1 == OE_OK);


    // Negative test
    ptr = fopen("../../../tests/qv/host/generated_report.bytes_bad","rb");
    OE_TEST(ptr != NULL);

    fseek(ptr, 0, SEEK_END);
    fsize = (size_t)ftell(ptr);
    fseek(ptr, 0, SEEK_SET);

    OE_TEST(fread(buffer, fsize, 1, ptr) > 0);
    fclose(ptr);

    retval1 = oe_verify_report(NULL, buffer, fsize, &oe_report);

    OE_TEST(retval1 != OE_OK);
    

    printf("=== passed all tests (qv)\n");

    return 0;
}
