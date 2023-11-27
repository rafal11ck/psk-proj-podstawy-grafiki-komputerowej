#ifndef UPDATEABLEOBJECT_HPP_
#define UPDATEABLEOBJECT_HPP_
/**
 * @brief Updateable object class.
 */
class UpdateableObject {
public:
  /**
   * @brief Updates state of object.
   */
  virtual void update() = 0;
};

#endif // UPDATEABLEOBJECT_HPP_
