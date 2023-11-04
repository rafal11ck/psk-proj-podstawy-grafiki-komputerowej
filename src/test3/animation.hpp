#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "animatedObject.hpp"
#include <string_view>

class Animation : public AnimatedObject {
public:
  Animation(std::string_view path);
};

#endif // ANIMATION_H_
