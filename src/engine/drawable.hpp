#ifndef DRAWABLE_H_
#define DRAWABLE_H_

/**
 * @brief abstract class for drawables
 */

class Drawable {

public:
  /**
   *@brief draw */
  virtual void draw() const = 0;
};

#endif // DRAWABLE_H_
