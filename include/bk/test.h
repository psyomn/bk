/*
   Copyright 2019 Simon (psyomn) Symeonidis

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */
#pragma once

#include <iostream>
#include <ctime>
#include <cstdint>
#include <cstdio>

#define bk_test(l, fn, dt) internal_bk_test(__FILE__ ": " l, fn, dt)

inline void internal_bk_test(const char *label,
                             int (*func)(void **data),
                             void      **data) {
  using std::printf;
  using std::cout;
  using std::endl;
  using std::int64_t;
  using std::time_t;

  const clock_t start        = clock();
  const time_t  time_start   = time(NULL);
  const int     ret          = func(data);
  const clock_t end          = clock();
  const time_t  time_end     = time(NULL);
  const double  elapsed      = (end - start) / (double)CLOCKS_PER_SEC;
  const time_t  elapsed_time = (time_end - time_start);

  printf("%s: %s [wc:%f][tm:%zu]\n",
         label,
         !ret ? "ok" : "fail",
         elapsed,
         elapsed_time);
}
