#ifndef PONTUAL_H_
#define PONTUAL_H_
#include "../Light.h"

class Pontual : public Light{
  
  public:

    // Attributes
    Point3 source;

    // Constructors
    Pontual(Point3 _source = Point3(0.0,0.0,0.0)) : Light(){
        source = _source;
    }
    Pontual
    // Methods
}
