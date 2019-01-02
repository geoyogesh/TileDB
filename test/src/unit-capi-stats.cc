/**
 * @file   unit-capi-stats.cc
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2017-2018 TileDB Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * Tests the C API for stats.
 */

#include "catch.hpp"
#include "tiledb/sm/c_api/tiledb.h"

#include <cstring>

TEST_CASE("C API: Test stats", "[capi], [stats]") {
  REQUIRE(tiledb_stats_enable() == TILEDB_OK);
  char* stats_str = nullptr;
  REQUIRE(tiledb_stats_dump_str(&stats_str) == TILEDB_OK);
  REQUIRE(stats_str != nullptr);
  REQUIRE(strlen(stats_str) == 8736);

  // Check a small sample of the output
  std::string beginning(stats_str, 16);
  REQUIRE(beginning == "{\n  \"functions\":");

  REQUIRE(tiledb_stats_free_str(&stats_str) == TILEDB_OK);
  REQUIRE(stats_str == nullptr);
  REQUIRE(tiledb_stats_disable() == TILEDB_OK);
}