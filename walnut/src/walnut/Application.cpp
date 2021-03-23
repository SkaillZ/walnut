#include "Application.h"

namespace Walnut {

  Application::Application() {
    Walnut::Log::Init();
    WN_CORE_WARN("Initialized log.");
    WN_INFO("Hello. Var={0}", 5);
  }

  Application::~Application() {
    WN_CORE_WARN("Shutting down app.");
    Walnut::Log::Shutdown();
  }

}
