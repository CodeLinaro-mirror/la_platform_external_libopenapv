#ifndef OAPV_FUZZER_H
#define OAPV_FUZZER_H

#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

#endif /* OAPV_FUZZER_H */