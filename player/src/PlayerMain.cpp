#include <Walnut.h>
#include <cstdlib>
#include <dlfcn.h>
#include <iostream>
#include <filesystem>
#include <string>

#include <Walnut.h>

// Typedefs for the function pointers
typedef Walnut::Application* (*CreateApplicationPtr)();
typedef void (*UpdatePtr)(Walnut::Application* app);

std::filesystem::path findNewestLibrary(std::string basePath) {
  // Find the library with the newest write time inside the base directory
  time_t maxWriteTime = std::numeric_limits<time_t>::min();
  std::filesystem::path newestLibPath;

  for (const auto& entry: std::filesystem::directory_iterator(basePath)) {
    auto writeTime = std::filesystem::last_write_time(entry.path());
    auto writeTimeClock = decltype(writeTime)::clock::now();
    auto writeTimeSec = std::chrono::time_point_cast<std::chrono::seconds>(writeTimeClock)
      .time_since_epoch().count();
    if (writeTimeSec > maxWriteTime) {
      maxWriteTime = writeTimeSec;
      newestLibPath = entry.path();
    }
  }

  return newestLibPath;
}

void* loadGameLibrary(std::filesystem::path path) {
  auto sharedLib = dlopen(path.c_str(), RTLD_NOW);
  if (!sharedLib) {
    std::cerr << "Couldn't load library at'" << path << "'" << std::endl;
    exit(1);
  }
  return sharedLib;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: ./player [shared library path]" << std::endl;
    exit(1);
  }

  auto sharedLibBasePath = std::string(argv[1]);

  // Load the newest shared library from the path specified in the first argument
  auto sharedLibPath = findNewestLibrary(sharedLibBasePath);
  auto sharedLib = loadGameLibrary(sharedLibPath);

  // Get and call the CreateApplication function
  auto createApplicationFunc = (CreateApplicationPtr) dlsym(sharedLib, "CreateApplication");
  auto app = createApplicationFunc();

  while(true) {
    // Simulate a main loop
    app->Update();
    sleep(1);

    // Check if there's a newer library to load
    auto newestLibPath = findNewestLibrary(sharedLibBasePath);
    if (newestLibPath != sharedLibPath) {
      std::cout << "Reloading..." << std::endl;

      // Delete the old app and close the loaded library
      delete app;
      dlclose(sharedLib);

      // Load the new library and create a new app
      sharedLibPath = newestLibPath;
      std::cout << sharedLibPath << std::endl;
      sharedLib = loadGameLibrary(sharedLibPath);
      auto createApplicationFunc = (CreateApplicationPtr) dlsym(sharedLib, "CreateApplication");
      app = createApplicationFunc();
    }
  }
  delete app;
}
