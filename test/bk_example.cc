#include <bk/test.h>
#include <bk/helper.h>

#include <stdio.h>
#include <assert.h>

int some_test(void **data);

int main(void){
  bk_test("some test", some_test, NULL);
  return 0;
}

int some_test(void **data) {
  (void) data;
  return 0;
}
