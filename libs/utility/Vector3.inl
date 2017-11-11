#include "Vector3.h"
#include <random>

namespace utility {
    //
    //=== Member function implementation.
    //
    inline void Vector3::make_unit_vector( void )
    {
        /**
         * +---> unit vector.
         * |
         *
         * ^     1
         * v = _____ * v
         *     ||v||
         *
         * ||v|| = sqrt( v dot v )
         *
         *      1
         * k =_____
         *    ||v||
         */
        auto v_dot_v = e[X]*e[X] + e[Y]*e[Y] + e[Z]*e[Z] ;
        // make sure we divide by zero here.
        assert( fabs( v_dot_v - 0.d ) > 0.000001 );
        value_type k = 1.d/ sqrt( v_dot_v );
        e[X] *= k;
        e[Y] *= k;
        e[Z] *= k;
    }
    //
    //=== Non-member function implementation: operator overloading.
    //
    inline std::istream& operator>>( std::istream& is, Vector3 & v )
    {
        is >> v.e[Vector3::field_t::X]
            >> v.e[Vector3::field_t::Y]
            >> v.e[Vector3::field_t::Z];
        return is;
    }
    inline std::ostream& operator<<( std::ostream& os, const Vector3 & v )
    {
        os << std::fixed << std::setprecision( 2 )
            << "{ "
            << v.e[Vector3::field_t::X]
            << " "
            << v.e[Vector3::field_t::Y]
            << " "
            << v.e[Vector3::field_t::Z]
            << " }";
        return os;
    }

    // vectorial sum
    inline Vector3 operator+( const Vector3 & v1, const Vector3 & v2 )
    {
        return Vector3( v1.e[Vector3::X] + v2.e[Vector3::X],
                v1.e[Vector3::Y] + v2.e[Vector3::Y],
                v1.e[Vector3::Z] + v2.e[Vector3::Z] );
    }
    inline Vector3 operator-( const Vector3 & v1, const Vector3 & v2 )
    {
        return Vector3( v1.e[Vector3::X] - v2.e[Vector3::X],
                v1.e[Vector3::Y] - v2.e[Vector3::Y],
                v1.e[Vector3::Z] - v2.e[Vector3::Z] );
    }

    inline Vector3 operator*( const Vector3 & v1, const Vector3 & v2 )
    {
        return Vector3( v1.e[Vector3::X] * v2.e[Vector3::X],
                v1.e[Vector3::Y] * v2.e[Vector3::Y],
                v1.e[Vector3::Z] * v2.e[Vector3::Z] );
    }
    inline Vector3 operator/( const Vector3 & v1, const Vector3 & v2 )
    {
        return Vector3( v1.e[Vector3::X] / v2.e[Vector3::X],
                v1.e[Vector3::Y] / v2.e[Vector3::Y],
                v1.e[Vector3::Z] / v2.e[Vector3::Z] );
    }

    // Scalar Multiplication
    inline Vector3 operator*( const Vector3 & v, Vector3::value_type t )
    {
        return Vector3( v.e[Vector3::X] * t,
                v.e[Vector3::Y] * t,
                v.e[Vector3::Z] * t );
    }
    inline Vector3 operator*( Vector3::value_type t, const Vector3 & v )
    {
        return Vector3( v.e[Vector3::X] * t,
                v.e[Vector3::Y] * t,
                v.e[Vector3::Z] * t );
    }
    inline Vector3 operator/( const Vector3 & v, Vector3::value_type t )
    {
        return Vector3( v.e[Vector3::X] / t,
                v.e[Vector3::Y] / t,
                v.e[Vector3::Z] / t );
    }

    //inner (dot) product
    inline Vector3::value_type dot( const Vector3 & v1, const Vector3 & v2 )
    {
        return v1.e[Vector3::X] * v2.e[Vector3::X] +
            v1.e[Vector3::Y] * v2.e[Vector3::Y] +
            v1.e[Vector3::Z] * v2.e[Vector3::Z] ;
    }

    //cross or vectorial product
    inline Vector3 cross( const Vector3 & v1, const Vector3 & v2 )
    {
        return Vector3(    v1.e[Vector3::Y] * v2.e[Vector3::Z] - v1.e[Vector3::Z] * v2.e[Vector3::Y]  ,
                -( v1.e[Vector3::X] * v2.e[Vector3::Z] - v1.e[Vector3::Z] * v2.e[Vector3::X] ),
                v1.e[Vector3::X] * v2.e[Vector3::Y] - v1.e[Vector3::Y] * v2.e[Vector3::X]    );
    }
    inline Vector3& Vector3::operator+=( const Vector3 & v )
    {
        e[X] += v.e[X];
        e[Y] += v.e[Y];
        e[Z] += v.e[Z];
        return *this;
    }
    inline Vector3& Vector3::operator-=( const Vector3 & v )
    {
        e[X] -= v.e[X];
        e[Y] -= v.e[Y];
        e[Z] -= v.e[Z];
        return *this;
    }
    inline Vector3& Vector3::operator*=( const Vector3 & v )
    {
        e[X] *= v.e[X];
        e[Y] *= v.e[Y];
        e[Z] *= v.e[Z];
        return *this;
    }
    inline Vector3& Vector3::operator/=( const Vector3 & v )
    {
        e[X] /= v.e[X];
        e[Y] /= v.e[Y];
        e[Z] /= v.e[Z];
        return *this;
    }
    inline Vector3& Vector3::operator*=( const value_type t )
    {
        e[X] *= t;
        e[Y] *= t;
        e[Z] *= t;
        return *this;
    }
    inline Vector3& Vector3::operator/=( const value_type t )
    {
        assert( fabs( t - 0.d ) > 0.000001 );
        value_type k = 1.d/t;
        e[X] *= k;
        e[Y] *= k;
        e[Z] *= k;
        return *this;
    }
    inline static Vector3 unit_vector( const Vector3 & v )
    {
        return v / v.length() ;
    }

    std::knuth_b random_generator(3);
    inline static Vector3 random_vector_in_unit_sphere(){
      // random_generator = std::knuth_b(seed);
      Vector3 v;
      do {
        //Get random x, y and z
        double x = std::generate_canonical<double, std::numeric_limits<double>::digits> (random_generator);
        double y = std::generate_canonical<double, std::numeric_limits<double>::digits> (random_generator);
        double z = std::generate_canonical<double, std::numeric_limits<double>::digits> (random_generator);

        v = 2 * Vector3(x,y,z) - Vector3(1);//normalize between [-1,1]
      } while(dot(v,v) >= 1.0); //until len^2 < 1

      return v;
    }

    inline static Vector3 random_vector_in_unit_disk(){
      Vector3 v;

      do{
        double x = std::generate_canonical<double, std::numeric_limits<double>::digits> (random_generator);
        double y = std::generate_canonical<double, std::numeric_limits<double>::digits> (random_generator);
        v = 2 * Vector3(x,y,0) - Vector3(1,1,0);
      } while(dot(v,v) >= 1.0);

      return v;
    }

} // namespace utility
