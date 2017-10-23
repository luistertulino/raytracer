#ifndef _RAY_H_
#define _RAY_H_
#include "Vector3.h" // necessário para acessar Vector3
using namespace utility;
class Ray {

    private:

        Point3 O; // the origin of the ray.
        Vector3 D; // The ray's direction.

    public:

        //=== Alias
        typedef double real_type;

        //=== Constructor
        Ray( Point3 o_=Point3(), Vector3 d_=Vector3() )
            : O( o_ )
            , D( d_ )
        { /* empty */ }

        //=== Getters
        inline Vector3 get_direction( void ) const { return D; }
        inline Point3 get_origin( void ) const { return O; }

        //Get a Point3 for the point given an "instant" t_
        Point3 point_at( real_type t_ )  const
        {
            return O + t_ * D; // parametric equation of the ray.
        }
};
#endif
