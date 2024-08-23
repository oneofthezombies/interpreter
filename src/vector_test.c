#include <assert.h>
#include <stddef.h>

#include "vector.h"

int main() {
  vector *vector = NULL;
  vector_code code = VECTOR_CODE_OK;
  {
    code = vector_create(0, sizeof(i32), &vector);
    assert(code == VECTOR_CODE_INVALID_ARGUMENT_CAPACITY);
  }
  {
    code = vector_create(1, 0, &vector);
    assert(code == VECTOR_CODE_INVALID_ARGUMENT_ELEMENT_SIZE);
  }
  {
    code = vector_create(1, sizeof(i32), NULL);
    assert(code == VECTOR_CODE_INVALID_ARGUMENT_OUT_VECTOR);
  }
  {
    code = vector_create(1, sizeof(i32), &vector);
    assert(code == VECTOR_CODE_OK);
    assert(vector != NULL);
  }
  {
    i32 capacity = 0;
    code = vector_capacity(vector, &capacity);
    assert(code == VECTOR_CODE_OK);
    assert(capacity == 1);
  }
  {
    code = vector_capacity(vector, NULL);
    assert(code == VECTOR_CODE_INVALID_ARGUMENT_OUT_CAPACITY);
  }
  {
    i32 size = 1;
    code = vector_size(vector, &size);
    assert(code == VECTOR_CODE_OK);
    assert(size == 0);
  }
  {
    code = vector_size(vector, NULL);
    assert(code == VECTOR_CODE_INVALID_ARGUMENT_OUT_SIZE);
  }
  {
    i32 element_size = 0;
    code = vector_element_size(vector, &element_size);
    assert(code == VECTOR_CODE_OK);
    assert(element_size == sizeof(i32));
  }
  {
    code = vector_element_size(vector, NULL);
    assert(code == VECTOR_CODE_INVALID_ARGUMENT_OUT_ELEMENT_SIZE);
  }
  {
    i32 *element = NULL;
    code = vector_at(vector, 0, (void **)&element);
    assert(code == VECTOR_CODE_INDEX_OUT_OF_RANGE);
  }
  {
    i32 element = 0;
    code = vector_pop_back(vector, (void *)&element);
    assert(code == VECTOR_CODE_VECTOR_IS_EMPTY);
  }
  {
    i32 element = 1;
    code = vector_push_back(vector, &element);
    assert(code == VECTOR_CODE_OK);
  }
  {
    code = vector_push_back(vector, NULL);
    assert(code == VECTOR_CODE_INVALID_ARGUMENT_ELEMENT);
  }
  {
    code = vector_at(vector, 0, NULL);
    assert(code == VECTOR_CODE_INVALID_ARGUMENT_OUT_ELEMENT);
  }
  {
    i32 size = 0;
    code = vector_size(vector, &size);
    assert(code == VECTOR_CODE_OK);
    assert(size == 1);
  }
  {
    i32 element = 0;
    code = vector_pop_back(vector, (void *)&element);
    assert(code == VECTOR_CODE_OK);
    assert(element == 1);
  }
  {
    i32 element = 1;
    code = vector_push_back(vector, (void *)&element);
    assert(code == VECTOR_CODE_OK);
    i32 size = 0;
    code = vector_size(vector, &size);
    assert(code == VECTOR_CODE_OK);
    assert(size == 1);
    i32 capacity = 0;
    code = vector_capacity(vector, &capacity);
    assert(code == VECTOR_CODE_OK);
    assert(capacity == 1);
    element = 2;
    code = vector_push_back(vector, (void *)&element);
    assert(code == VECTOR_CODE_OK);
    code = vector_size(vector, &size);
    assert(code == VECTOR_CODE_OK);
    assert(size == 2);
    code = vector_capacity(vector, &capacity);
    assert(code == VECTOR_CODE_OK);
    assert(capacity == 2);
    i32 *element_ptr = NULL;
    code = vector_at(vector, 0, (void **)&element_ptr);
    assert(code == VECTOR_CODE_OK);
    assert(element_ptr != NULL);
    assert(*element_ptr = 1);
    code = vector_at(vector, 1, (void **)&element_ptr);
    assert(code == VECTOR_CODE_OK);
    assert(element_ptr != NULL);
    assert(*element_ptr = 2);
  }
  {
    code = vector_destroy(vector);
    assert(code == VECTOR_CODE_OK);
  }
  {
    code = vector_destroy(NULL);
    assert(code == VECTOR_CODE_SELF_IS_NULL);
  }
  return 0;
}
