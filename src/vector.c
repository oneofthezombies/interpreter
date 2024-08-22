#include "vector.h"

#include <stdlib.h>
#include <string.h>

typedef struct impl {
  void *data;
  int32_t capacity;
  int32_t element_size;
  int32_t size;
} impl;

vector_code _vector_validate_self(vector *self) {
  if (self == NULL) {
    return VECTOR_CODE_SELF_IS_NULL;
  }

  if (self->impl == NULL) {
    return VECTOR_CODE_IMPL_IS_NULL;
  }

  if (self->impl->data == NULL) {
    return VECTOR_CODE_DATA_IS_NULL;
  }

  return VECTOR_CODE_OK;
}

vector_code vector_create(const int32_t capacity, const int32_t element_size,
                          OUT vector **self) {
  if (capacity <= 0) {
    return VECTOR_CODE_INVALID_ARGUMENT_CAPACITY;
  }

  if (element_size <= 0) {
    return VECTOR_CODE_INVALID_ARGUMENT_ELEMENT_SIZE;
  }

  if (self == NULL) {
    return VECTOR_CODE_INVALID_ARGUMENT_OUT_VECTOR;
  }

  *self = (vector *)malloc(sizeof(vector));
  if (*self == NULL) {
    return VECTOR_CODE_ALLOCATION_FAILED_VECTOR_SELF;
  }

  (*self)->impl = malloc(sizeof(impl));
  if ((*self)->impl == NULL) {
    SAFE_FREE(*self);
    return VECTOR_CODE_ALLOCATION_FAILED_VECTOR_IMPL;
  }

  (*self)->impl->data = malloc(capacity * element_size);
  if ((*self)->impl->data == NULL) {
    SAFE_FREE((*self)->impl);
    SAFE_FREE(*self);
    return VECTOR_CODE_ALLOCATION_FAILED_VECTOR_DATA;
  }

  (*self)->impl->capacity = capacity;
  (*self)->impl->element_size = element_size;
  (*self)->impl->size = 0;
  return VECTOR_CODE_OK;
}

vector_code vector_destroy(vector *self) {
  if (self == NULL) {
    return VECTOR_CODE_SELF_IS_NULL;
  }

  if (self->impl == NULL) {
    SAFE_FREE(self);
    return VECTOR_CODE_IMPL_IS_NULL;
  }

  if (self->impl->data == NULL) {
    SAFE_FREE(self->impl);
    SAFE_FREE(self);
    return VECTOR_CODE_DATA_IS_NULL;
  }

  SAFE_FREE(self->impl->data);
  SAFE_FREE(self->impl);
  SAFE_FREE(self);
  return VECTOR_CODE_OK;
}

vector_code vector_capacity(vector *self, OUT int32_t *capacity) {
  const vector_code code = _vector_validate_self(self);
  if (code != VECTOR_CODE_OK) {
    return code;
  }

  if (capacity == NULL) {
    return VECTOR_CODE_INVALID_ARGUMENT_OUT_CAPACITY;
  }

  *capacity = self->impl->capacity;
  return VECTOR_CODE_OK;
}

vector_code vector_size(vector *self, OUT int32_t *size) {
  const vector_code code = _vector_validate_self(self);
  if (code != VECTOR_CODE_OK) {
    return code;
  }

  if (size == NULL) {
    return VECTOR_CODE_INVALID_ARGUMENT_OUT_SIZE;
  }

  *size = self->impl->size;
  return VECTOR_CODE_OK;
}

vector_code vector_element_size(vector *self, OUT int32_t *element_size) {
  const vector_code code = _vector_validate_self(self);
  if (code != VECTOR_CODE_OK) {
    return code;
  }

  if (element_size == NULL) {
    return VECTOR_CODE_INVALID_ARGUMENT_OUT_ELEMENT_SIZE;
  }

  *element_size = self->impl->element_size;
  return VECTOR_CODE_OK;
}

vector_code vector_at(vector *self, const int32_t index, OUT void **element) {
  const vector_code code = _vector_validate_self(self);
  if (code != VECTOR_CODE_OK) {
    return code;
  }

  if (index >= self->impl->size) {
    return VECTOR_CODE_INDEX_OUT_OF_RANGE;
  }

  if (element == NULL) {
    return VECTOR_CODE_INVALID_ARGUMENT_OUT_ELEMENT;
  }

  *element =
      (void *)((u8 *)self->impl->data + (self->impl->element_size * index));
  return VECTOR_CODE_OK;
}

vector_code vector_push_back(vector *self, void *element) {
  const vector_code code = _vector_validate_self(self);
  if (code != VECTOR_CODE_OK) {
    return code;
  }

  if (element == NULL) {
    return VECTOR_CODE_INVALID_ARGUMENT_ELEMENT;
  }

  if (self->impl->capacity == self->impl->size) {
    const int32_t next_capacity = self->impl->capacity * 2;
    void *data = malloc(next_capacity * self->impl->element_size);
    if (data == NULL) {
      return VECTOR_CODE_ALLOCATION_FAILED_VECTOR_DATA;
    }

    self->impl->capacity = next_capacity;
    memcpy(data, self->impl->data, self->impl->size * self->impl->element_size);
    SAFE_FREE(self->impl->data);
    self->impl->data = data;
  }

  memcpy((void *)((u8 *)self->impl->data +
                  (self->impl->size * self->impl->element_size)),
         element, self->impl->element_size);
  self->impl->size++;
  return VECTOR_CODE_OK;
}

vector_code vector_pop_back(vector *self, OUT void *element) {
  const vector_code code = _vector_validate_self(self);
  if (code != VECTOR_CODE_OK) {
    return code;
  }

  if (element == NULL) {
    return VECTOR_CODE_INVALID_ARGUMENT_OUT_ELEMENT;
  }

  if (self->impl->size == 0) {
    return VECTOR_CODE_VECTOR_IS_EMPTY;
  }

  const int32_t last_index = self->impl->size - 1;
  memcpy(element,
         (void *)((u8 *)self->impl->data +
                  (self->impl->element_size * last_index)),
         self->impl->element_size);
  self->impl->size--;
  return VECTOR_CODE_OK;
}
