#pragma once

#include "Core.h"
#include "Log.h"

namespace Walnut {

  class WN_API Application {
  public:
    Application();
    virtual ~Application();

    virtual void Update() = 0;
  };

}
