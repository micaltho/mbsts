/* This file is auto generated from Rhapsody do not edit! */

#ifndef RXF_MACROS_H
#define RXF_MACROS_H

/* @MISRA_16-0-2,16-0-4,16-0-6,16-2-1,16-2-2,16-3-2=OFF ID-0007: Function-like Macros must be used for Rhapsody code generation compatibility. */

#define GEN(EVENT) send_##EVENT

#define OUT_PORT(PORT) (&PORT)
#define OUT_PORT_AT(PORT,INDEX) (&PORT[INDEX])

/* @MISRA_16-0-2,16-0-4,16-0-6,16-2-1,16-2-2,16-3-2=ON (end of ID-0007) */

#endif /* RXF_MACROS_H */
