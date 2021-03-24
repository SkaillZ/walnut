#include <Walnut.h>

class Sandbox : public Walnut::Application {
public:
  void Update() override {
    WN_INFO("Hello from SandboxApp.");
  }
};

// entry point, called by the player
// cppcheck-suppress unusedFunction
extern "C" Walnut::Application* CreateApplication() { 
  return new Sandbox();
}
