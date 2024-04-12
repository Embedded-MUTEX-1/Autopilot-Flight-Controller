#ifndef DPSREGISTER_H_INCLUDED
#define DPSREGISTER_H_INCLUDED

#include <string.h>
#include <cstdint>
#include <cmath>

typedef struct
{
    uint8_t regAddress;
    uint8_t mask;
    uint8_t shift;
} RegMask_t;

typedef struct
{
    uint8_t regAddress;
    uint8_t length;
} RegBlock_t;

#endif