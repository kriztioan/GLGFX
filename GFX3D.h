/**
 *  @file   GLGFX.h
 *  @brief  OpenGL Pixel Graphics
 *  @author KrizTioaN (christiaanboersma@hotmail.com)
 *  @date   2021-08-01
 *  @note   BSD-3 licensed
 *
 ***********************************************/

#ifndef CBGLGFX_GFX3D_H_
#define CBGLGFX_GFX3D_H_

#include <cmath>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

namespace cb {
struct vec3d;
struct vec2d;
struct triangle3d;
struct triangle2d;
struct mat4x4;
struct mesh;
} // namespace cb

struct [[maybe_unused]] cb::vec3d {

  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
  float w = 1.0f;

  cb::vec3d operator+(const cb::vec3d &vec) const {

    return { this->x + vec.x, this->y + vec.y, this->z + vec.z };
  }

  cb::vec3d &operator+=(const cb::vec3d &vec) {

    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;

    return *this;
  }

  cb::vec3d operator-(const cb::vec3d &vec) const {

    return { this->x - vec.x, this->y - vec.y, this->z - vec.z };
  }

  cb::vec3d &operator-=(const cb::vec3d &vec) {

    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;

    return *this;
  }

  cb::vec3d operator+(const float &f) const {

    return { this->x + f, this->y + f, this->z + f };
  }

  cb::vec3d &operator+=(const float &f) {

    this->x += f;
    this->y += f;
    this->z += f;

    return *this;
  }

  cb::vec3d operator-(const float &f) const {

    return { this->x - f, this->y - f, this->z - f };
  }

  cb::vec3d &operator-=(const float &f) {

    this->x -= f;
    this->y -= f;
    this->z -= f;

    return *this;
  }

  cb::vec3d operator*(const float &f) const {

    return { this->x * f, this->y * f, this->z * f };
  }

  cb::vec3d &operator*=(const float &f) {

    this->x *= f;
    this->y *= f;
    this->z *= f;

    return *this;
  }

  cb::vec3d operator/(const float &f) const {

    return { this->x / f, this->y / f, this->z / f };
  }

  cb::vec3d &operator/=(const float &f) {

    this->x /= f;
    this->y /= f;
    this->z /= f;

    return *this;
  }

  float operator*(const cb::vec3d &vec) const {

    return this->x * vec.x + this->y * vec.y + this->z * vec.z;
  }

  [[maybe_unused]] [[nodiscard]] cb::vec3d cross(const cb::vec3d &vec) const {

    return { this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x,
             vec.w };
  }

  [[maybe_unused]] [[nodiscard]] float norm() const {

    return std::sqrt( this->x * this->x + this->y * this->y + this->z * this->z );
  }

  [[maybe_unused]] [[nodiscard]] vec3d normalize() const {

    float number = this->x * this->x + this->y * this->y + this->z * this->z;

    const float number_half = 0.5f * number;

    int i;

    std::memcpy( &i, &number, sizeof( int ) );

    i = 0x5f3759df - ( i >> 1 );

    std::memcpy( &number, &i, sizeof( float ) );

    number = number * ( 1.5f - number_half * number * number );

    return { this->x * number, this->y * number, this->z * number, 1.0f };
  }
};

struct [[maybe_unused]] cb::vec2d {

  float u = 0.0f;
  float v = 0.0f;
  float w = 0.0f;

  cb::vec2d operator+(const cb::vec2d &vec) const {

    return { this->u + vec.u, this->u + vec.v, this->w + vec.w };
  }

  cb::vec2d &operator+=(const cb::vec2d &vec) {

    this->u += vec.u;
    this->v += vec.v;
    this->w += vec.w;

    return *this;
  }

  cb::vec2d operator-(const cb::vec2d &vec) const {

    return { this->u - vec.u, this->v - vec.v, this->w - vec.w };
  }

  cb::vec2d &operator-=(const cb::vec2d &vec) {

    this->u -= vec.u;
    this->v -= vec.v;
    this->w -= vec.w;

    return *this;
  }

  cb::vec2d operator+(const float &f) const {

    return { this->u + f, this->v + f, this->w + f };
  }

  cb::vec2d &operator+=(const float &f) {

    this->u += f;
    this->v += f;
    this->w += f;

    return *this;
  }

  cb::vec2d operator-(const float &f) const {

    return { this->u - f, this->v - f, this->w - f };
  }

  cb::vec2d &operator-=(const float &f) {

    this->u -= f;
    this->v -= f;
    this->w -= f;

    return *this;
  }

  cb::vec2d operator*(const float &f) const {

    return { this->u * f, this->v * f, this->w * f };
  }

  cb::vec2d &operator*=(const float &f) {

    this->u *= f;
    this->v *= f;
    //this->w *= w;

    return *this;
  }

  cb::vec2d operator/(const float &f) const {

    return { this->u / f, this->v / f, this->w / f };
  }

  cb::vec2d &operator/=(const float &f) {

    this->u /= f;
    this->v /= f;
    this->w /= f;

    return *this;
  }

  float operator*(const cb::vec2d &vec) const {

    return this->u * vec.u + this->v * vec.v;
  }

  [[maybe_unused]] [[nodiscard]] float norm() const {

    return std::sqrt( this->u * this->u + this->v * this->v );
  }

  [[maybe_unused]] [[nodiscard]] cb::vec2d normalize() const {

    float number = this->u * this->u + this->v * this->v;

    const float number_half = 0.5f * number;

    int i;

    std::memcpy( &i, &number, sizeof( int ) );

    i = 0x5f3759df - ( i >> 1 );

    std::memcpy( &number, &i, sizeof( float ) );

    number = number * ( 1.5f - number_half * number * number );

    return { this->u * number, this->v * number, 1.0f };
  }
};

struct [[maybe_unused]] cb::triangle3d {

  cb::vec3d p1;
  cb::vec3d p2;
  cb::vec3d p3;

  int color {};

  cb::triangle3d &operator+=(const float f) {

    this->p1 += f;
    this->p2 += f;
    this->p3 += f;

    return *this;
  }

  //triangle3d &operator*= ( const mat4x4 &m );
};

struct [[maybe_unused]] cb::mesh {

  std::vector<cb::triangle3d> triangles;

  [[maybe_unused]] bool ReadObj( const std::wstring &filename ) {

    std::ifstream ifstr;
    ifstr.open( filename );
    if( ifstr.fail() ) return false;

    triangles.clear();

    std::vector< vec3d > vVertices;

    std::string line;

    char cIndicator;

    while( !ifstr.eof() ) {

      std::getline( ifstr, line );

      std::stringstream ss( line );

      if( line.at( 0 ) == 'v' ) {

        cb::vec3d v;

        ss >> cIndicator >> v.x >> v.y >> v.z;

        vVertices.emplace_back( v );

      } else if( line.at( 0 ) == 'f' ) {

        int nIndices[3];

        ss >> cIndicator >> nIndices[ 0 ] >> nIndices[ 1 ] >> nIndices[ 2 ];

        triangles.push_back( { vVertices.at( nIndices[ 0 ] - 1 ), vVertices.at( nIndices[ 1 ] - 1 ),
                               vVertices.at( nIndices[ 2 ] - 1 ) } );
      }
    }

    return true;
  }

  [[maybe_unused]] void UnitCube() {

    triangles.clear();

    triangles = {

        // SOUTH
        { {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f} },
        { {0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },

        // EAST
        { {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, },
        { {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f}, },

        // NORTH
        { {1.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f} },
        { {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f} },

        // WEST
        { {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
        { {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f} },

        // TOP
        { {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
        { {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f} },

        // BOTTOM
        { {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f} },
        { {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
    };
  };
};

struct [[maybe_unused]] cb::triangle2d {

  cb::vec2d p1;
  cb::vec2d p2;
  cb::vec2d p3;
};

struct [[maybe_unused]] cb::mat4x4 {

  float m[4][4] = { 0 };

  cb::vec3d operator*(const cb::vec3d &v) {

    cb::vec3d o;

    o.x = v.x * this->m[ 0 ][ 0 ] + v.y * this->m[ 1 ][ 0 ] + v.z * this->m[ 2 ][ 0 ] + v.w * this->m[ 3 ][ 0 ];
    o.y = v.x * this->m[ 0 ][ 1 ] + v.y * this->m[ 1 ][ 1 ] + v.z * this->m[ 2 ][ 1 ] + v.w * this->m[ 3 ][ 1 ];
    o.z = v.x * this->m[ 0 ][ 2 ] + v.y * this->m[ 1 ][ 2 ] + v.z * this->m[ 2 ][ 2 ] + v.w * this->m[ 3 ][ 2 ];
    //o.w = v.x * this->m[ 0 ][ 3 ] + v.y * this->m[ 1 ][ 3 ] + v.z * this->m[ 2 ][ 3 ] + v.w * this->m[ 3 ][ 3 ];
    o.w = v.x * this->m[ 0 ][ 3 ] + v.y * this->m[ 1 ][ 3 ] + v.z * this->m[ 2 ][ 3 ] + this->m[ 3 ][ 3 ];


    if( o.w != 0.0f ) {

      o.x /= o.w;
      o.y /= o.w;
      o.z /= o.w;
      o.z /= o.w;
    }

    return o;
  }

  cb::mat4x4 operator*(const cb::mat4x4 &M) {

    cb::mat4x4 mat;

    for( int c = 0; c < 4; c++ )
      for( int r = 0; r < 4; r++ )
        mat.m[ r ][ c ] =
            this->m[ r ][ 0 ] * M.m[ 0 ][ c ] + this->m[ r ][ 1 ] * M.m[ 1 ][ c ] + this->m[ r ][ 2 ] * M.m[ 2 ][ c ] +
            this->m[ r ][ 3 ] * M.m[ 3 ][ c ];

    return mat;
  }

  cb::triangle3d operator*(const cb::triangle3d &t) {

    triangle3d o;

    o.p1 = *this * t.p1;
    o.p2 = *this * t.p2;
    o.p3 = *this * t.p3;

    o.color = t.color;

    return o;
  }
};

[[maybe_unused]] cb::mat4x4 IdentityMatrix() {

  return { { { 1.0f, 0.0f, 0.0f, 0.0f },
               { 0.0f, 1.0f, 0.0f, 0.0f },
               { 0.0f, 0.0f, 1.0f, 0.0f },
               { 0.0f, 0.0f, 0.0f, 1.0f } } };
}

[[maybe_unused]] cb::mat4x4 TranslationMatrix(float x, float y, float z) {

  return { { { 1.0f, 0.0f, 0.0f, 0.0f },
               { 0.0f, 1.0f, 0.0f, 0.0f },
               { 0.0f, 0.0f, 1.0f, 0.0f },
               { x, y, z, 1.0f } } };
}

[[maybe_unused]] cb::mat4x4 ScalingMatrix( float x, float y, float z ) {

  return { { { x, 0.0f, 0.0f, 0.0f },
               { 0.0f, y, 0.0f, 0.0f },
               { 0.0f, 0.0f, z, 0.0f },
               { 0.0, 0.0, 0.0, 1.0f } } };
}

[[maybe_unused]] cb::mat4x4 RotationMatrixX(float theta) {

  return { { { 1.0f, 0.0f, 0.0f, 0.0f },
               { 0.0f, std::cos( theta ), std::sin( theta ), 0.0f },
               { 0.0f, -std::sin( theta ), std::cos( theta ), 0.0f },
               { 0.0f, 0.0f, 0.0f, 1.0f } } };
}

[[maybe_unused]] cb::mat4x4 RotationMatrixY(float theta) {

  return { { { std::cos( theta ), 0.0f, -std::sin( theta ), 0.0f },
               { 0.0f, 1.0f, 0.0f, 0.0f },
               { std::sin( theta ), 0.0f, std::cos( theta ), 0.0f },
               { 0.0f, 0.0f, 0.0f, 1.0f } } };
}

[[maybe_unused]] cb::mat4x4 RotationMatrixZ(float theta) {
  return { { { std::cos( theta ), std::sin( theta ), 0.0f, 0.0f },
               { -std::sin( theta ), std::cos( theta ), 0.0f, 0.0f },
               { 0.0f, 0.0f, 1.0f, 0.0f },
               { 0.0f, 0.0f, 0.0f, 1.0f } } };
}

[[maybe_unused]] cb::mat4x4 ProjectionMatrix(float fNear, float fFar,
                                             float fFov, float fAspectRatio) {

  return { { { fAspectRatio / tanf( fFov * 0.5f / 180.0f * M_PI ), 0.0f, 0.0f, 0.0f },
               { 0.0f, 1.0f / tanf( fFov * 0.5f / 180.0f * M_PI ), 0.0f, 0.0f },
               { 0.0f, 0.0f, fFar / ( fFar - fNear ), 1.0f },
               { 0.0f, 0.0f, ( -fFar * fNear ) / ( fFar - fNear ), 0.0f } } };
}

[[maybe_unused]] cb::mat4x4 PointMatrix(cb::vec3d &vPosition,
                                        cb::vec3d &vTarget, cb::vec3d &vUp) {

  cb::vec3d vForward = ( vTarget - vPosition ).normalize();
  cb::vec3d vUpProj = (vUp - (vForward * (vUp * vForward))).normalize();
  cb::vec3d vRight = vUpProj.cross(vForward);

  return { { { vRight.x, vRight.y, vRight.z, 0.0f },
               { vUpProj.x, vUpProj.y, vUpProj.z, 0.0f },
               { vForward.x, vForward.y, vForward.z, 0.0f },
               { vPosition.x, vPosition.y, vPosition.z, 1.0f } } };
}

[[maybe_unused]] cb::mat4x4 ViewMatrix(cb::vec3d &vPosition, cb::vec3d &vTarget,
                                       cb::vec3d &vUp) {

  cb::mat4x4 M = PointMatrix(vPosition, vTarget, vUp);
  cb::mat4x4 mView;

  mView.m[ 0 ][ 0 ] = M.m[ 0 ][ 0 ];
  mView.m[ 0 ][ 1 ] = M.m[ 1 ][ 0 ];
  mView.m[ 0 ][ 2 ] = M.m[ 2 ][ 0 ];
  mView.m[ 0 ][ 3 ] = 0.0f;
  mView.m[ 1 ][ 0 ] = M.m[ 0 ][ 1 ];
  mView.m[ 1 ][ 1 ] = M.m[ 1 ][ 1 ];
  mView.m[ 1 ][ 2 ] = M.m[ 2 ][ 1 ];
  mView.m[ 1 ][ 3 ] = 0.0f;
  mView.m[ 2 ][ 0 ] = M.m[ 0 ][ 2 ];
  mView.m[ 2 ][ 1 ] = M.m[ 1 ][ 2 ];
  mView.m[ 2 ][ 2 ] = M.m[ 2 ][ 2 ];
  mView.m[ 2 ][ 3 ] = 0.0f;
  mView.m[ 3 ][ 0 ] = -( M.m[ 3 ][ 0 ] * mView.m[ 0 ][ 0 ] + M.m[ 3 ][ 1 ] * mView.m[ 1 ][ 0 ] +
                         M.m[ 3 ][ 2 ] * mView.m[ 2 ][ 0 ] );
  mView.m[ 3 ][ 1 ] = -( M.m[ 3 ][ 0 ] * mView.m[ 0 ][ 1 ] + M.m[ 3 ][ 1 ] * mView.m[ 1 ][ 1 ] +
                         M.m[ 3 ][ 2 ] * mView.m[ 2 ][ 1 ] );
  mView.m[ 3 ][ 2 ] = -( M.m[ 3 ][ 0 ] * mView.m[ 0 ][ 2 ] + M.m[ 3 ][ 1 ] * mView.m[ 1 ][ 2 ] +
                         M.m[ 3 ][ 2 ] * mView.m[ 2 ][ 2 ] );
  mView.m[ 3 ][ 3 ] = 1.0f;

  return mView;
}

[[maybe_unused]] cb::vec3d IntersectPlane(cb::vec3d &vPlanePoint,
                                          cb::vec3d &vPlaneNormal,
                                          cb::vec3d &vLine0,
                                          cb::vec3d &vLine1) {

  float ad = vLine0 * vPlaneNormal.normalize();

  return vLine0 + ( vLine1 - vLine0 ) * ( ( vPlaneNormal * vPlanePoint ) - ad ) / ( ( vLine1 * vPlaneNormal ) - ad );
}

[[maybe_unused]] int Clip(cb::vec3d vPlanePoint, cb::vec3d vPlaneNormal,
                          cb::triangle3d &tIn, cb::triangle3d &tOut1,
                          cb::triangle3d &tOut2) {

  auto Distance = [&](cb::vec3d vPoint) {

    return vPlaneNormal.x * vPoint.x + vPlaneNormal.y * vPoint.y + vPlaneNormal.z * vPoint.z -
           vPlaneNormal * vPlanePoint;
  };

  cb::vec3d *pInside[3];
  int nInside = 0;

  cb::vec3d *pOutside[3];
  int nOutside = 0;

  if( Distance( tIn.p1 ) >= 0.0f ) pInside[ nInside++ ] = &tIn.p1;
  else pOutside[ nOutside++ ] = &tIn.p1;

  if( Distance( tIn.p2 ) >= 0.0f ) pInside[ nInside++ ] = &tIn.p2;
  else pOutside[ nOutside++ ] = &tIn.p2;

  if( Distance( tIn.p3 ) >= 0.0f ) pInside[ nInside++ ] = &tIn.p3;
  else pOutside[ nOutside++ ] = &tIn.p3;

  if( nInside == 0 ) return 0;

  if( nInside == 3 ) {

    tOut1 = tIn;

    return 1;
  }

  if( nInside == 1 ) {

    tOut1 = tIn;

    tOut1.p1 = *pInside[ 0 ];
    tOut1.p2 = IntersectPlane( vPlanePoint, vPlaneNormal, *pInside[ 0 ], *pOutside[ 0 ] );
    tOut1.p3 = IntersectPlane( vPlanePoint, vPlaneNormal, *pInside[ 0 ], *pOutside[ 1 ] );

    //tOut1.color = 4;

    return 1;
  }


  tOut1 = tIn;
  tOut1.p1 = *pInside[ 0 ];
  tOut1.p2 = *pInside[ 1 ];
  tOut1.p3 = IntersectPlane( vPlanePoint, vPlaneNormal, *pInside[ 0 ], *pOutside[ 0 ] );

  tOut2 = tIn;
  tOut2.p1 = *pInside[ 1 ];
  tOut2.p2 = tOut1.p3;
  tOut2.p3 = IntersectPlane( vPlanePoint, vPlaneNormal, *pInside[ 1 ], *pOutside[ 0 ] );

  //tOut1.color = 2;
  //tOut2.color = 3;

  return 2;
}

#endif //CBGLGFX_GFX3D_H_
