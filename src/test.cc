#define CATCH_CONFIG_MAIN
#include <unordered_map>
#include "FileSystem.h"
#include "../lib/catch.hpp"

SCENARIO( "mkdir touch", "") {
  auto fs = new FileSystem();
  GIVEN( "A series of file or dir name" ) {
    WHEN( "Created") {
      fs->makeFile("a.txt");
      fs->makeDir("src");
      fs->makeDir("out");
      fs->makeFile("b.out");
      REQUIRE(fs->getCurrentDir()->getSize() == 4);
      unordered_map<string, bool> m;
      fs->getCurrentDir()->forEach([&m](File* p) -> void {
        m[p->getName()] = p->isDir();
      });
      REQUIRE(m["a.txt"] == 0);
      REQUIRE(m["src"] == 1);
      REQUIRE(m["out"] == 1);
      REQUIRE(m["b.out"] == 0);
    }
  }
}