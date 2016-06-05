#define CATCH_CONFIG_MAIN
#include <unordered_map>
#include "FileSystem.h"
#include "../lib/catch.hpp"

SCENARIO("Parse a path", "") {
  GIVEN("A path") {
    string path = "/home/ziqi/FileSystem/src/Dir.c/";
    WHEN("Path parsed") {
      auto elems = FileSystem::parse(path);
      REQUIRE(elems.size() == 6);
      REQUIRE(elems[0] == "");
      REQUIRE(elems[1] == "home");
      REQUIRE(elems[2] == "ziqi");
      REQUIRE(elems[3] == "FileSystem");
      REQUIRE(elems[4] == "src");
      REQUIRE(elems[5] == "Dir.c");
      //REQUIRE(elems[6] == "");
    }
  }
}

SCENARIO("Dir test", "") {
  GIVEN("An instance of Dir") {
    auto dir = new Dir("/");
    unordered_map<string, bool> m;
    WHEN("Append some children") {
      dir->appendChild(new File("a.txt", "Hello, world"));
      dir->appendChild(new Dir("src"));
      dir->appendChild(new Dir("out"));
      dir->appendChild(new File("b.out", ""));

      REQUIRE(dir->getSize() == 4);

      dir->forEach([&m](File* p) -> void {
        m[p->getName()] = p->isDir();
      });
      REQUIRE(m["a.txt"] == 0);
      REQUIRE(m["src"] == 1);
      REQUIRE(m["out"] == 1);
      REQUIRE(m["b.out"] == 0);

      THEN("Find dir or file by name") {
        auto elem = dir->getElementByName("a.txt");
        REQUIRE(elem->getName() == "a.txt");
        REQUIRE(elem->getContent() == "Hello, world");
        elem = dir->getElementByName("src");
        REQUIRE(elem->getName() == "src");
        elem = dir->getElementByName("out");
        REQUIRE(elem->getName() == "out");
        elem = dir->getElementByName("b.out");
        REQUIRE(elem->getName() == "b.out");
        REQUIRE(elem->getContent() == "");
      }
    }
  }
}

SCENARIO( "mkdir", "") {
  auto fs = new FileSystem();
  unordered_map<string, bool> m;
  WHEN( "Created at current dir") {
    fs->makeDir("src");
    fs->makeDir("out");
    REQUIRE(fs->getCurrentDir()->getSize() == 2);
    fs->getCurrentDir()->forEach([&m](File* p) -> void {
      m[p->getName()] = p->isDir();
    });
    REQUIRE(m["src"] == 1);
    REQUIRE(m["out"] == 1);
  }
  WHEN("Created by absolute dir") {
    REQUIRE(fs->makeDir("src/headers") == NULL);
    auto src = fs->makeDir("/src/");
    REQUIRE(src != NULL);
    REQUIRE(src->getName() == "src");
    auto headers = fs->makeDir("/src/headers/");
    REQUIRE(headers != NULL);
    REQUIRE(headers->getName() == "headers");
    src->forEach([&m](File* p) -> void {
      m[p->getName()] = p->isDir();
    });
    REQUIRE(m["headers"] == 1);
  }
}