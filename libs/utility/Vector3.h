#ifndef _Vector3_H_
#define _Vector3_H_
#include <cmath>        // sqrt, fabs
#include <iostream>     // cout, cin, endl
#include <cassert>      // assert()
#include <initializer_list> // initializer_list
#include <algorithm>    // copy
#include <iterator>     // std::begin(), std::end(), std::next()
#include <iomanip>      // setprecision()
namespace utility {
    /*!
     * Represents a 3D vector, that might be used to represent
     * points, directions, vectors, colors, offset
     */
    class Vector3
    {
        public:

            // Aliases
            typedef double value_type;
            enum field_t { X=0, Y=1, Z=2, R=0, G=1, B=2 };

            //=== Fields
            value_type e[ 3 ];

            //=== Constructors
            explicit Vector3( value_type e0_, value_type e1_, value_type e2_ )
                : e{ e0_, e1_, e2_ }
            { /* empty */ }

            Vector3(value_type v = 0.d)
                : e{v, v, v}
            { /* empty */ }

            Vector3( const Vector3 & other_ )
                : e{ other_.e[X], other_.e[Y], other_.e[Z] }
            { /* empty */ }

            Vector3( std::initializer_list< value_type > il_ )
            {
                assert( il_.size() >= 3 ) ;
                std::copy( il_.begin(), std::next( il_.begin(), 3 ), std::begin(e) );
            }

            //=== Getters
            inline value_type x() const { return e[X]; }
            inline value_type y() const { return e[Y]; }
            inline value_type z() const { return e[Z]; }
            inline value_type r() const { return e[R]; }
            inline value_type g() const { return e[G]; }
            inline value_type b() const { return e[B]; }

            // indexed access operator (rhs)
            inline value_type operator[]( size_t idx ) const { return e[ idx ]; }
            // indexed access operator (lhs)
            inline value_type& operator[]( size_t idx ) { return e[ idx ]; }

            //=== Algebraic operators
            bool operator==( const Vector3 & other_ ) const
            {
                return fabs( e[X] - other_.e[X] ) < 0.00001f and
                    fabs( e[Y] - other_.e[Y] ) < 0.00001f and
                    fabs( e[Z] - other_.e[Z] ) < 0.00001f    ;
            }
            Vector3 & operator=( const Vector3 & other_ )
            {
                e[X] = other_.e[X];
                e[Y] = other_.e[Y];
                e[Z] = other_.e[Z];
                return *this;
            }
            Vector3 & operator=(std::initializer_list< value_type > il_ )
            {
                assert( il_.size() >= 3 ) ;
                std::copy( il_.begin(), std::next( il_.begin(), 3 ), std::begin(e) );
                return *this;
            }

            // Unary '+'
            inline const Vector3& operator+( void ) const { return *this; }

            // Unary '-'
            inline Vector3 operator-( void ) const { return Vector3( -e[X], -e[Y], -e[Z] ); }

            // Algebraic binary operators
            inline Vector3& operator+=( const Vector3& );
            inline Vector3& operator-=( const Vector3& );
            inline Vector3& operator*=( const Vector3& );
            inline Vector3& operator/=( const Vector3& );
            inline Vector3& operator*=( const value_type );
            inline Vector3& operator/=( const value_type );

            // Returns vector length (|vector|)
            inline value_type length( void ) const
            {
                return sqrt( e[X]*e[X] + e[Y]*e[Y] + e[Z]*e[Z] );
            }
            inline value_type squared_length( void ) const
            {
                return ( e[X]*e[X] + e[Y]*e[Y] + e[Z]*e[Z] );
            }
            inline void make_unit_vector( void );
    };

    // Aliases for vectors
    typedef Vector3 RGB;
    typedef Vector3 Offset;
    typedef Vector3 Point3;
} // namespace utility
#include "Vector3.inl"
#endif
