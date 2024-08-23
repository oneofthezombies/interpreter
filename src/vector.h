#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>

#include "common.h"

typedef struct impl impl;

typedef struct {
  impl *impl;
} vector;

typedef enum {
  VECTOR_CODE_OK = 0,
  VECTOR_CODE_INVALID_ARGUMENT_CAPACITY,
  VECTOR_CODE_INVALID_ARGUMENT_ELEMENT_SIZE,
  VECTOR_CODE_INVALID_ARGUMENT_ELEMENT,
  VECTOR_CODE_INVALID_ARGUMENT_OUT_VECTOR,
  VECTOR_CODE_INVALID_ARGUMENT_OUT_CAPACITY,
  VECTOR_CODE_INVALID_ARGUMENT_OUT_SIZE,
  VECTOR_CODE_INVALID_ARGUMENT_OUT_ELEMENT_SIZE,
  VECTOR_CODE_INVALID_ARGUMENT_OUT_ELEMENT,
  VECTOR_CODE_ALLOCATION_FAILED_VECTOR_SELF,
  VECTOR_CODE_ALLOCATION_FAILED_VECTOR_IMPL,
  VECTOR_CODE_ALLOCATION_FAILED_VECTOR_DATA,
  VECTOR_CODE_SELF_IS_NULL,
  VECTOR_CODE_IMPL_IS_NULL,
  VECTOR_CODE_DATA_IS_NULL,
  VECTOR_CODE_INDEX_OUT_OF_RANGE,
  VECTOR_CODE_VECTOR_IS_EMPTY,
} vector_code;

vector_code vector_create(const i32 capacity, const i32 element_size,
                          OUT vector **self);
vector_code vector_destroy(vector *self);
vector_code vector_capacity(vector *self, OUT i32 *capacity);
vector_code vector_size(vector *self, OUT i32 *size);
vector_code vector_element_size(vector *self, OUT i32 *element_size);
vector_code vector_at(vector *self, const i32 index, OUT void **element);
vector_code vector_push_back(vector *self, void *element);
vector_code vector_pop_back(vector *self, OUT void *element);

#endif // VECTOR_H
