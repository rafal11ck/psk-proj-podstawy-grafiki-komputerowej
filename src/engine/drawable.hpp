#ifndef DRAWABLE_H_
#define DRAWABLE_H_

/**
 * @brief abstract class for drawables
 */
class Drawable {
public:
  /**
   *@brief draw */
  virtual void draw() = 0;

  virtual ~Drawable() = 0;
};

#endif // DRAWABLE_H_
