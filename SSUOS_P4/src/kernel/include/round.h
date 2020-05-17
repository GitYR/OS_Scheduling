#ifndef __LIB_ROUND_H
#define __LIB_ROUND_H

#define ROUND_UP(X, STEP) (((X) + (STEP) - 1) / (STEP) * (STEP))

#define DIV_ROUND_UP(X, STEP) (((X) + (STEP) - 1) / (STEP))

#define ROUND_DOWN(X, STEP) ((X) / (STEP) * (STEP))

#endif 
