#define CATCH_CONFIG_MAIN
#include <unordered_map>
#include "FileSystem.h"
#include "../lib/catch.hpp"

SCENARIO ("Parse a path", "") {
  GIVEN ("A path") {
    string path = "/home/ziqi/FileSystem/src/Dir.c/";
    WHEN ("Path parsed") {
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

SCENARIO ("Dir test", "") {
  GIVEN ("An instance of Dir") {
    auto dir = new Dir("/");
    unordered_map<string, bool> m;
    WHEN ("Append some children") {
      auto a_txt = dir->appendChild(new File("a.txt", "Hello, world"));
      auto src = dir->appendChild(new Dir("src"));
      auto out = dir->appendChild(new Dir("out"));
      auto b_out = dir->appendChild(new File("b.out", ""));

      REQUIRE(dir->getSize() == 4);

      dir->forEach([&m](File* p) -> void {
        m[p->getName()] = p->isDir();
      });
      REQUIRE(m["a.txt"] == 0);
      REQUIRE(m["src"] == 1);
      REQUIRE(m["out"] == 1);
      REQUIRE(m["b.out"] == 0);

      THEN ("Find dir or file by name") {
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
      
      THEN ("Remove children") {
        dir->removeChild(src);
        dir->removeChild(b_out);
        REQUIRE(dir->getSize() == 2);
        m.clear();
        dir->forEach([&m](File* p) -> void {
          m[p->getName()] = p->isDir();
        });
        REQUIRE(m["a.txt"] == 0);
        REQUIRE(m["out"] == 1);
        REQUIRE(m.find("src") == m.end());
        REQUIRE(m.find("b.out") == m.end());
      }
    }
  }
}

SCENARIO ("mkdir", "") {
  auto fs = new FileSystem();
  unordered_map<string, bool> m;
  WHEN ("Created at current dir") {
    fs->makeDir("src");
    fs->makeDir("out");
    REQUIRE(fs->getCurrentDir()->getSize() == 2);
    fs->getCurrentDir()->forEach([&m](File* p) -> void {
      m[p->getName()] = p->isDir();
    });
    REQUIRE(m["src"] == 1);
    REQUIRE(m["out"] == 1);
  }
  WHEN ("Created by absolute dir") {
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

SCENARIO ("Switch to some dir", "mkdir") {
  GIVEN ("Dirs") {
    auto fs = new FileSystem();
    auto src = fs->makeDir("src");
    auto out = fs->makeDir("src/out/");
    WHEN ("Switch to relative path") {
      fs->switchToDir("src");
      REQUIRE(fs->getCurrentDir() == src);
      fs->switchToDir("out");
      REQUIRE(fs->getCurrentDir() == out);
      THEN ("Switch to parent") {
        fs->switchToDir("..");
        REQUIRE(fs->getCurrentDir() == src);
        fs->switchToDir("../");
        REQUIRE(fs->getCurrentDir() == fs->getRootDir());
      }
    }
    WHEN ("Switch to absolute path") {
      fs->switchToDir("/src/out/");
      REQUIRE(fs->getCurrentDir() == out);
      fs->switchToDir("..");
      fs->switchToDir("/src/out");
      REQUIRE(fs->getCurrentDir() == out);
    }
  }
}

SCENARIO ("touch" , "mkdir") {
  auto fs = new FileSystem();
  unordered_map<string, bool> m;
  
  WHEN ("Created by relative path") {
    fs->makeFile("MakeFile");
    fs->makeDir("src");
    fs->getCurrentDir()->forEach([&m](File* p) -> void {
      m[p->getName()] = p->isDir();
    });
    REQUIRE(fs->getCurrentDir()->getSize() == 2);
    REQUIRE(m["MakeFile"] == 0);
    REQUIRE(m["src"] == 1);
  }
  
  WHEN ("Created by absolute path") {
    fs->makeDir("/src");
    fs->makeFile("/src/File.c");
    fs->switchToDir("/src/");
    REQUIRE(fs->getCurrentDir()->getSize() == 1);
    fs->getCurrentDir()->forEach([&m](File* p) -> void {
      m[p->getName()] = p->isDir();
    });
    REQUIRE(m["File.c"] == 0);
  }
}

SCENARIO ("rm cp", "mkdir touch") {
  auto fs = new FileSystem();
  unordered_map<string, bool> m;
  auto src = fs->makeDir("src");
  fs->makeDir("src/headers");
  fs->makeFile("src/headers/File.h");
  fs->makeFile("src/File.c");
  auto out = fs->makeDir("out");
  
  WHEN ("Remove file or dir") {
    fs->switchToDir("src");
    fs->remove("File.c");
    REQUIRE(fs->getCurrentDir()->getSize() == 1);
    fs->getCurrentDir()->forEach([&m](File* p) -> void {
      m[p->getName()] = p->isDir();
    });
    REQUIRE(m["headers"] == 1);
    REQUIRE(m.find("File.c") == m.end());
    fs->switchToDir("..");
    fs->remove("src");
    REQUIRE(fs->getCurrentDir()->getSize() == 1);
    m.clear();
    fs->getCurrentDir()->forEach([&m](File* p) -> void {
      m[p->getName()] = p->isDir();
    });
    REQUIRE(m.find("src") == m.end());
    REQUIRE(m["out"] == 1);
  }
  
  WHEN ("Copy file or dir") {
    fs->copy("/src/headers/", "/out/headers/");
    fs->switchToDir("out");
    REQUIRE(out->getSize() == 1);
    fs->getCurrentDir()->forEach([&m](File* p) -> void {
      m[p->getName()] = p->isDir();
    });
    for (auto item : m) {
      cout<<item.first<<endl;
    }
    REQUIRE(m["headers"] == 1);
    fs->switchToDir("headers");
    m.clear();
    fs->getCurrentDir()->forEach([&m](File* p) -> void {
      m[p->getName()] = p->isDir();
    });
    REQUIRE(m["File.c"] == 0);
  }
}

