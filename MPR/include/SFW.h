// ---------------------------------------------------------------------------
// Project Name   : Simple Framework
// File Name    : SFW.h
// Author     : Sun Tjen Fam
// Creation Date  : 2008/09/15
// Purpose      : header file for a simple OpenGL framework
// ---------------------------------------------------------------------------

#ifndef SFW_H
#define SFW_H

// ---------------------------------------------------------------------------
// includes

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <conio.h>
#include <windows.h>
#include <float.h>
#include <vector>
#include <list>
#include <direct.h>

#include "glew.h"
#include "wglew.h"

// ---------------------------------------------------------------------------
// additional libraries

#pragma comment (lib, "glew\\glew32.lib")

#ifndef SFW_CAMERA_H
  #pragma comment (lib, "lib\\Lib_Camera.lib")
#endif

#ifndef SFW_SHAPES_H
  #pragma comment (lib, "lib\\Lib_Shapes.lib")
#endif

#ifndef SFW_SHADER_H
  #pragma comment (lib, "lib\\Lib_Shader.lib")
#endif

#ifndef SFW_GEOMETRY_H
  #pragma comment (lib, "lib\\Lib_Geometry.lib")
#endif

#ifndef SFW_MESH_H
  #pragma comment (lib, "lib\\Lib_Mesh.lib")
#endif

// ---------------------------------------------------------------------------
// defines 

#define _CRT_SECURE_NO_WARNINGS

// ---------------------------------------------------------------------------
// typedef for basic variable types

typedef char        s8;
typedef unsigned char   u8;
typedef signed short    s16;
typedef unsigned short    u16;
typedef signed long     s32;
typedef unsigned long   u32;
typedef signed long long  s64;
typedef unsigned long long  u64;
typedef float       f32;
typedef double        f64;

// ---------------------------------------------------------------------------
// defines

// define PI if it is not defined yet
#ifndef PI
  const f64 PI  = 3.1415926535897932384626433832795;
#endif

#ifndef EPSILON
  const f64 EPSILON = 0.001;
#endif

// shortcut for two and half pi
const f64 TWO_PI  = PI * 2.0;
const f64 HALF_PI = PI * 0.5;

// epsilon squared
const f64 EPSILON_SQ = EPSILON * EPSILON;

// float version of the above
const f32 PIf     = (f32)(PI);
const f32 TWO_PIf   = (f32)(TWO_PI);
const f32 HALF_PIf    = (f32)(HALF_PI);
const f32 EPSILONf    = (f32)(EPSILON);
const f32 EPSILON_SQf = (f32)(EPSILON_SQ);

// ---------------------------------------------------------------------------
// Assert defines

#ifndef FINAL

// ---------------------------------------------------------------------------

#define PRINT(...)  printf(__VA_ARGS__)

// ---------------------------------------------------------------------------

#define SFW_ASSERT(x)                       \
{                                 \
  if((x) == 0)                          \
  {                               \
    PRINT("SFW_ASSERT: %s\nLine: %d\nFunc: %s\nFile: %s\n",   \
      #x, __LINE__, __FUNCTION__, __FILE__);          \
    _getch();                         \
    exit(1);                          \
  }                               \
}

// ---------------------------------------------------------------------------

#define SFW_ASSERT_MESG(x, ...)                     \
{                                   \
  if((x) == 0)                            \
  {                                 \
    PRINT("SFW_ASSERT_MESG: %s\nLine: %d\nFunc: %s\nFile: %s\n",  \
      #x, __LINE__, __FUNCTION__, __FILE__);            \
    PRINT("Mesg: "__VA_ARGS__);                   \
    PRINT("\n");                          \
    _getch();                           \
    exit(1);                            \
  }                                 \
}

// ---------------------------------------------------------------------------

#define SFW_ASSERT_PARM(x)                        \
{                                   \
  if((x) == 0)                            \
  {                                 \
    PRINT("SFW_ASSERT_PARM: %s\nLine: %d\nFunc: %s\nFile: %s\n",  \
      #x, __LINE__, __FUNCTION__, __FILE__);            \
    _getch();                           \
    exit(1);                            \
  }                                 \
}

// ---------------------------------------------------------------------------

#define SFW_ASSERT_ALLOC(x)                       \
{                                   \
  if((x) == 0)                            \
  {                                 \
    PRINT("SFW_ASSERT_ALLOC: %s\nLine: %d\nFunc: %s\nFile: %s\n", \
      #x, __LINE__, __FUNCTION__, __FILE__);            \
    _getch();                           \
    exit(1);                            \
  }                                 \
}


// ---------------------------------------------------------------------------

#define SFW_WARNING(x)                      \
{                               \
  if((x) == 0)                        \
  {                             \
    PRINT("SFW_WARNING: %s\nLine: %d\nFunc: %s\nFile: %s\n",  \
      #x, __LINE__, __FUNCTION__, __FILE__);        \
  }                             \
}

// ---------------------------------------------------------------------------

#define SFW_WARNING_MESG(x, ...)                    \
{                                   \
  if((x) == 0)                            \
  {                                 \
    PRINT("SFW_WARNING_MESG: %s\nLine: %d\nFunc: %s\nFile: %s\n", \
      #x, __LINE__, __FUNCTION__, __FILE__);            \
    PRINT("Mesg: "__VA_ARGS__);                   \
    PRINT("\n");                          \
  }                                 \
}

// ---------------------------------------------------------------------------

#define SFW_WARNING_PARM(x)                       \
{                                   \
  if((x) == 0)                            \
  {                                 \
    PRINT("SFW_WARNING_PARM: %s\nLine: %d\nFunc: %s\nFile: %s\n", \
      #x, __LINE__, __FUNCTION__, __FILE__);            \
  }                                 \
}

// ---------------------------------------------------------------------------

#else // FINAL

// ---------------------------------------------------------------------------

#define PRINT(...)

#define SFW_ASSERT(x)
#define SFW_ASSERT_MESG(x, ...)
#define SFW_ASSERT_PARM(x)
#define SFW_ASSERT_ALLOC(x)

#define SFW_WARNING(x)
#define SFW_WARNING_MESG(x, ...)
#define SFW_WARNING_PARM(x)
#define SFW_WARNING_ALLOC(x)

// ---------------------------------------------------------------------------

#endif // FINAL

// ---------------------------------------------------------------------------

#define SFW_HALT(...)                   \
{                             \
  PRINT("SFW_HALT:\nLine: %d\nFunc: %s\nFile: %s\n",    \
    __LINE__, __FUNCTION__, __FILE__);          \
  if (" "#__VA_ARGS__[1]) PRINT("Mesg: "__VA_ARGS__);   \
  PRINT("\n");                      \
  _getch();                       \
  exit(1);                        \
}

// ---------------------------------------------------------------------------

#define SFW_GL_ERROR(...)                   \
{                               \
  GLenum glError = glGetError();                \
  if (glError != GL_NO_ERROR)                 \
  {                             \
    PRINT("SFW_GL_ERROR:\nLine: %d\nFunc: %s\nFile: %s\n",  \
      __LINE__, __FUNCTION__, __FILE__);          \
    PRINT("Code: 0x%0.8x\n", glError);            \
    PRINT("Mesg: "__VA_ARGS__);               \
    PRINT("\n");                      \
    _getch();                       \
    exit(1);                        \
  }                             \
}

// ---------------------------------------------------------------------------

namespace SFW
{

// ---------------------------------------------------------------------------
// class declarations

// ---------------------------------------------------------------------------
// a simple 2D vector class

struct Vec2
{
  union
  {
    struct 
    { 
      f32 x, y;
    };
    struct
    {
      f32 r, g;
    };
    struct 
    { 
      f32 s, t;
    };
    f32   v[2];
  };
  
        Vec2      ()                {         }
        Vec2      (const Vec2& rhs)       { (*this) = rhs;  }
        Vec2      (f32 xx, f32 yy)        { x = xx, y = yy; }
  explicit  Vec2      (f32 xx)            { x = y = xx;   }

  // accessor
  f32     operator[]    (u32 idx) const         { return v[idx];  }
  f32&    operator[]    (u32 idx)           { return v[idx];  }

  // unary operation
  Vec2    operator+   () const            { return *this;     }
  Vec2    operator-   () const            { return Vec2(-x, -y);  }
  
  // add/subtract/multiply/divide with vector
  Vec2    operator+   (const Vec2& rhs) const     { return Vec2(x + rhs.x, y + rhs.y);    }
  Vec2    operator-   (const Vec2& rhs) const     { return Vec2(x - rhs.x, y - rhs.y);    }
  Vec2    operator*   (const Vec2& rhs) const     { return Vec2(x * rhs.x, y * rhs.y);    }
  Vec2    operator/   (const Vec2& rhs) const     { return Vec2(x / rhs.x, y / rhs.y);    }
  Vec2&   operator+=    (const Vec2& rhs)       { return (*this) = (*this) + rhs;     }
  Vec2&   operator-=    (const Vec2& rhs)       { return (*this) = (*this) - rhs;     }
  Vec2&   operator*=    (const Vec2& rhs)       { return (*this) = (*this) * rhs;     }
  Vec2&   operator/=    (const Vec2& rhs)       { return (*this) = (*this) / rhs;     }
  
  // add/subtract/multiply/divide with scalar
  Vec2    operator+   (f32 s) const         { return Vec2(x + s, y + s);        }
  Vec2    operator-   (f32 s) const         { return Vec2(x - s, y - s);        }
  Vec2    operator*   (f32 s) const         { return Vec2(x * s, y * s);        }
  Vec2    operator/   (f32 s) const         { return Vec2(x / s, y / s);        }
  Vec2&   operator+=    (f32 s)             { return (*this) = (*this) + s;     }
  Vec2&   operator-=    (f32 s)             { return (*this) = (*this) - s;     }
  Vec2&   operator*=    (f32 s)             { return (*this) = (*this) * s;     }
  Vec2&   operator/=    (f32 s)             { return (*this) = (*this) / s;     }

  // multiply or divide by a vector

  // get vector length
  f32     Length      () const            { return sqrtf((*this).Dot(*this));   }
  f32     LengthSq    () const            { return (*this).Dot(*this);        }

  // calculate normalized vector
  Vec2    Normalize   () const            { return (*this) / Length();        }
  Vec2&   NormalizeThis ()                { return (*this) = (*this) / Length();  }

  // dot product
  f32     Dot       (const Vec2& rhs) const     { return x * rhs.x + y * rhs.y;     }

  // cross product
  // * pretend that the vectors are in 3d, return the 'z' component of the resulting cross product
  f32     Cross     (const Vec2& rhs) const     { return x * rhs.y - y * rhs.x;     }

  // comparison
  bool    operator==    (const Vec2& rhs) const     { return (*this - rhs).LengthSq() < EPSILON_SQ;     }
  bool    operator!=    (const Vec2& rhs) const     { return !operator==(rhs);                }
  bool    IsZero      () const            { return (fabs(x) < EPSILON) && (fabs(y) < EPSILON);    }

  void    Print     () const            { printf("%10f %10f\n", x, y);      }
};

// ---------------------------------------------------------------------------

template <typename T>
Vec2 operator*(T s, const Vec2& rhs)
{
  return (rhs * s);
}

// ---------------------------------------------------------------------------
// a simple 3D vector class

struct Vec3
{
  union
  {
    struct 
    {
      f32 x, y, z;
    };
    struct 
    { 
      f32 r, g, b;
    };
    struct 
    { 
      f32 s, t, p;
    };
    f32   v[3];
  };
  
        Vec3      ()                {                   }
        Vec3      (const Vec3& rhs)       { (*this) = rhs;            }
        Vec3      (const Vec2& rhs, f32 zz)   { x = rhs.x,  y = rhs.y,  z = zz;   }
        Vec3      (f32 xx, const Vec2& rhs)   { x = xx,   y = rhs.x,  z = rhs.y;  }
        Vec3      (f32 xx, f32 yy, f32 zz)    { x = xx,   y = yy,   z = zz;   }
  explicit  Vec3      (f32 xx)            { x = y = z = xx;           }
  explicit  Vec3      (const Vec2& rhs)       { x = rhs.x,  y = rhs.y,  z = 0.0;  }

  // accessor
  f32     operator[]    (u32 idx) const         { return v[idx];  }
  f32&    operator[]    (u32 idx)           { return v[idx];  }

  // unary operation
  Vec3    operator+   () const            { return *this;       }
  Vec3    operator-   () const            { return Vec3(-x, -y, -z);  }

  // casting to Vec?
        operator Vec2 () const            { return Vec2(x, y);      }

  // add/substract/multply/divide per component
  Vec3    operator+   (const Vec3& rhs) const     { return Vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
  Vec3    operator-   (const Vec3& rhs) const     { return Vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
  Vec3    operator*   (const Vec3& rhs) const     { return Vec3(x * rhs.x, y * rhs.y, z * rhs.z); }
  Vec3    operator/   (const Vec3& rhs) const     { return Vec3(x / rhs.x, y / rhs.y, z / rhs.z); }
  Vec3&   operator+=    (const Vec3& rhs)       { return (*this) = (*this) + rhs;         }
  Vec3&   operator-=    (const Vec3& rhs)       { return (*this) = (*this) - rhs;         }
  Vec3&   operator*=    (const Vec3& rhs)       { return (*this) = (*this) * rhs;         }
  Vec3&   operator/=    (const Vec3& rhs)       { return (*this) = (*this) / rhs;         }

  // add/subtract/multiply/divide (scalar)
  Vec3    operator+   (f32 s) const         { return Vec3(x + s, y + s, z + s);       }
  Vec3    operator-   (f32 s) const         { return Vec3(x - s, y - s, z - s);       }
  Vec3    operator*   (f32 s) const         { return Vec3(x * s, y * s, z * s);       }
  Vec3    operator/   (f32 s) const         { return Vec3(x / s, y / s, z / s);       }
  Vec3&   operator+=    (f32 s)             { return (*this) = (*this) + s;         }
  Vec3&   operator-=    (f32 s)             { return (*this) = (*this) - s;         }
  Vec3&   operator*=    (f32 s)             { return (*this) = (*this) * s;         }
  Vec3&   operator/=    (f32 s)             { return (*this) = (*this) / s;         }

  // get vector length
  f32     Length      () const            { return sqrtf((*this).Dot(*this));       }
  f32     LengthSq    () const            { return (*this).Dot(*this);            }

  // calculate normalized vector
  Vec3    Normalize   () const            { return (*this) / Length();            }
  Vec3&   NormalizeThis ()                { return (*this) = (*this) / Length();      }

  // dot product
  f32     Dot       (const Vec3& rhs) const     { return x * rhs.x + y * rhs.y + z * rhs.z;   }

  // cross product
  Vec3    Cross     (const Vec3& rhs) const     { return Vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x); }

  // comparison
  bool    operator==    (const Vec3& rhs) const     { return (*this - rhs).LengthSq() < EPSILON_SQ; }
  bool    operator!=    (const Vec3& rhs) const     { return !operator==(rhs);            }
  bool    IsZero      () const            { return (fabs(x) < EPSILON) && (fabs(y) < EPSILON) && (fabs(z) < EPSILON);     }

  void    Print     () const            { printf("%10f %10f %10f\n", x, y, z);      }
};

// ---------------------------------------------------------------------------

template <typename T>
Vec3 operator*(T s, const Vec3& rhs)
{
  return (rhs * s);
}

// ---------------------------------------------------------------------------
// a simple 4D vector class

struct Vec4
{
  union
  {
    struct 
    { 
      f32 x, y, z, w;
    };
    struct 
    { 
      f32 r, g, b, a;
    };
    struct 
    { 
      f32 s, t, p, q;
    };
    f32   v[4];
  };
  
        Vec4      ()                  {                         }
        Vec4      (const Vec4& rhs)         { (*this) = rhs;                  }
        Vec4      (const Vec3& rhs, f32 ww)     { x = rhs.x,  y = rhs.y,  z = rhs.z,  w = ww;   }
        Vec4      (f32 xx, const Vec3& rhs)     { x = xx,     y = rhs.x,  z = rhs.y,  w = rhs.z;  }
        Vec4      (const Vec2& rhs, f32 zz, f32 ww) { x = rhs.x,  y = rhs.y,  z = zz,   w = ww;   }
        Vec4      (f32 xx, const Vec2& rhs, f32 ww) { x = xx,   y = rhs.x,  z = rhs.y,  w = ww;   }
        Vec4      (f32 xx, f32 yy, const Vec2& rhs) { x = xx,   y = yy,   z = rhs.x,  w = rhs.y;  }
        Vec4      (const Vec2& xy, const Vec2& zw)  { x = xy.x, y = xy.y, z = zw.x, w = zw.y; }
        Vec4      (f32 xx, f32 yy, f32 zz, f32 ww)  { x = xx,     y = yy,   z = zz;   w = ww;   }
  explicit  Vec4      (f32 xx)              { x = y = z = w = xx;               }
  explicit  Vec4      (const Vec2& rhs)         { x = rhs.x,  y = rhs.y,  z = 0.0f, w = 0.0f; }
  explicit  Vec4      (const Vec3& rhs)         { x = rhs.x,  y = rhs.y,  z = rhs.z,  w = 0.0f; }

  // accessor
  f32     operator[]    (u32 idx) const           { return v[idx];  }
  f32&    operator[]    (u32 idx)             { return v[idx];  }

  // unary operation
  Vec4    operator+   () const              { return *this;         }
  Vec4    operator-   () const              { return Vec4(-x, -y, -z, -w);  }

  // casting to Vec?
        operator Vec2 () const              { return Vec2(x, y);        }
        operator Vec3 () const              { return Vec3(x, y, z);     }
  
  // add or substract
  Vec4    operator+   (const Vec4& rhs) const       { return Vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);  }
  Vec4    operator-   (const Vec4& rhs) const       { return Vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);  }
  Vec4    operator*   (const Vec4& rhs) const       { return Vec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);  }
  Vec4    operator/   (const Vec4& rhs) const       { return Vec4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);  }
  Vec4&   operator+=    (const Vec4& rhs)         { return (*this) = (*this) + rhs;               }
  Vec4&   operator-=    (const Vec4& rhs)         { return (*this) = (*this) - rhs;               }
  Vec4&   operator*=    (const Vec4& rhs)         { return (*this) = (*this) * rhs;               }
  Vec4&   operator/=    (const Vec4& rhs)         { return (*this) = (*this) / rhs;               }
  
  // multiply or divide by a scalar
  Vec4    operator+   (f32 s) const           { return Vec4(x + s, y + s, z + s, w + s);    }
  Vec4    operator-   (f32 s) const           { return Vec4(x - s, y - s, z - s, w - s);    }
  Vec4    operator*   (f32 s) const           { return Vec4(x * s, y * s, z * s, w * s);    }
  Vec4    operator/   (f32 s) const           { return Vec4(x / s, y / s, z / s, w / s);    }
  Vec4&   operator+=    (f32 s)               { return (*this) = (*this) + s;         }
  Vec4&   operator-=    (f32 s)               { return (*this) = (*this) - s;         }
  Vec4&   operator*=    (f32 s)               { return (*this) = (*this) * s;         }
  Vec4&   operator/=    (f32 s)               { return (*this) = (*this) / s;         }

  // get vector length
  f32     Length      () const              { return sqrtf((*this).Dot(*this));       }
  f32     LengthSq    () const              { return (*this).Dot(*this);            }

  // calculate normalized vector
  Vec4    Normalize   () const              { return (*this) / Length();            }
  Vec4&   NormalizeThis ()                  { return (*this) = (*this) / Length();      }

  // dot product
  f32     Dot       (const Vec4& rhs) const       { return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w; }

  // cross product
  // * no cross product for 4D vectors
  //Vec4    Cross     (const Vec4& rhs) const       { return Vec4(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x); }

  // comparison
  bool    operator==    (const Vec4& rhs) const       { return (*this - rhs).LengthSq() < EPSILON_SQ; }
  bool    operator!=    (const Vec4& rhs) const       { return !operator==(rhs);            }
  bool    IsZero      () const              { return (fabs(x) < EPSILON) && (fabs(y) < EPSILON) && (fabs(z) < EPSILON) && (fabs(w) < EPSILON);      }

  void    Print     () const              { printf("%10f %10f %10f %10f\n", x, y, z, w);  }
};

// ---------------------------------------------------------------------------

template <typename T>
Vec4 operator*(T s, const Vec4& rhs)
{
  return (rhs * s);
}

// ---------------------------------------------------------------------------
// a simple 4x4 matrix class

struct Mtx44
{
  union
  {
    // matrix data is stored row major
    struct
    {
      f32   m00, m01, m02, m03, 
          m10, m11, m12, m13, 
          m20, m21, m22, m23, 
          m30, m31, m32, m33;
    };
    f32     v[16];
  };

  // constructor
          Mtx44     ();
          Mtx44     (const f32* mm);
          Mtx44     (f32 m00, f32 m01, f32 m02, f32 m03, 
                   f32 m10, f32 m11, f32 m12, f32 m13, 
                   f32 m20, f32 m21, f32 m22, f32 m23, 
                   f32 m30, f32 m31, f32 m32, f32 m33);
          Mtx44     (const Mtx44& rhs);

  // ---------------------------------------------------------------------------
  // accessors

  f32&      RowCol      (u32 row, u32 col)      { return v[row * 4 + col];  }
  f32       RowCol      (u32 row, u32 col) const  { return v[row * 4 + col];  }

  // ---------------------------------------------------------------------------
  // operator overload

  // accessors
  f32       operator[]    (u32 idx) const       { return v[idx];          }
  f32&      operator[]    (u32 idx)         { return v[idx];          }
  f32       operator()    (u32 row, u32 col) const  { return RowCol(row, col);    }
  f32&      operator()    (u32 row, u32 col)      { return RowCol(row, col);    }

  Mtx44     operator+   (const Mtx44& rhs) const;
  Mtx44     operator-   (const Mtx44& rhs) const;
  Mtx44     operator*   (f32 s) const       { return Mult(s);         }
  Mtx44     operator*   (const Mtx44& rhs) const  { return Mult(rhs);       }
  Mtx44     operator/   (f32 s) const       { return Mult(1.0 / s);     }

  Mtx44&      operator+=    (const Mtx44& rhs)      { return (*this) = (*this) + rhs; }
  Mtx44&      operator-=    (const Mtx44& rhs)      { return (*this) = (*this) - rhs; }
  Mtx44&      operator*=    (f32 s)           { return (*this) = (*this) * s; }
  Mtx44&      operator*=    (const Mtx44& rhs)      { return (*this) = (*this) * rhs; }
  Mtx44&      operator/=    (f32 s)           { return (*this) = (*this) / s; }
  
  // multiply with a 3D vector
  // * '*' assume w = 1.0
  // * '/' assume w = 0.0
  Vec3      operator*   (const Vec3& v) const   { return MultVec(v);        }
  Vec3      operator/   (const Vec3& v) const   { return MultVecSR(v);      }

  // multiply with a 4D vector
  Vec4      operator*   (const Vec4& v) const   { return MultVec(v);        }
  
  // ---------------------------------------------------------------------------
  // member functions

  void      Print     () const;

  // Mtx44 * scalar
  Mtx44     Mult      (f32 s) const;
  const Mtx44&  MultThis    (f32 s);

  // Mtx44 * Mtx44
  Mtx44     Mult      (const Mtx44& rhs) const;
  const Mtx44&  MultThis    (const Mtx44& rhs);

  // Mtx44 * Vec3
  Vec3      MultVec     (const Vec3& v) const;
  Vec3      MultVecSR   (const Vec3& v) const;

  // Mtx44 * Vec4
  Vec4      MultVec     (const Vec4& v) const;
  
  // transpose
  Mtx44     Transpose   () const;
  const Mtx44&  TransposeThis ();

  // inverse
  Mtx44     Inverse     () const;
  const Mtx44&  InverseThis   ();

  // the following functions will be applied to 'this' matrix
  const Mtx44&  ZeroThis    ();
  const Mtx44&  IdentityThis  ();
  const Mtx44&  ScaleThis   (f32 x, f32 y, f32 z);
  const Mtx44&  RotateThis    (f32 x, f32 y, f32 z, f32 angle);
  const Mtx44&  TranslateThis (f32 x, f32 y, f32 z);

  // the following functions construct a matrix
  static Mtx44  Zero      ();
  static Mtx44  Identity    ();
  static Mtx44  Scale     (f32 x, f32 y, f32 z);
  static Mtx44  Rotate      (f32 x, f32 y, f32 z, f32 angle);
  static Mtx44  Translate   (f32 x, f32 y, f32 z);

  // calculate a look at matrix
  // * camera is looking along -z axis and y is up
  static Mtx44  LookAt      (f32 posX, f32 posY, f32 posZ, f32 targetX, f32 targetY, f32 targetZ, f32 upX,  f32 upY,  f32 upZ);
  static Mtx44  LookAt      (const Vec3& pos, const Vec3& target, const Vec3& up);
};

// ---------------------------------------------------------------------------

template <typename T>
Mtx44 operator*(T s, const Mtx44& rhs)
{
  return (rhs * s);
}

// ---------------------------------------------------------------------------

class Input
{
public:
  static Input* Instance  ();
  static void   Free    ();

  static void   Update    ()        { Instance()->update(); }

  static u8   KeyStateCurr  (u8 key)  { return Instance()->keyStateCurr(key); }
  static u8   KeyStatePrev  (u8 key)  { return Instance()->keyStatePrev(key); }
  
  static bool   CheckPrevious (u8 key)  { return Instance()->checkPrevious(key);  }
  static bool   CheckPressed  (u8 key)  { return Instance()->checkPressed(key); }
  static bool   CheckReleased (u8 key)  { return Instance()->checkReleased(key);  }
  static bool   CheckTriggered  (u8 key)  { return Instance()->checkTriggered(key); }
  
  // return the current cursor (mouse) position
  static s32    CursorPosX    ()      { return Instance()->cursorPosX();    }
  static s32    CursorPosY    ()      { return Instance()->cursorPosY();    }

  // return the cursor (mouse) displacement between the last 2 updates
  static s32    CursorDeltaX  ()      { return Instance()->cursorDeltaX();    }
  static s32    CursorDeltaY  ()      { return Instance()->cursorDeltaY();    }
  
private:
  // variables to keep track the keyboard status
  u8*       mpKeyStateCurr;
  u8*       mpKeyStatePrev;

  // variables to to keep track the mouse position
  s32       mCursorPosX, 
          mCursorPosY;
  s32       mCursorDeltaX, 
          mCursorDeltaY;
          
          Input   ();
          Input   (const Input& rhs);
  Input&      operator= (const Input& rhs);

          ~Input    ();

  void      update    ();

  u8        keyStateCurr  (u8 key) const  { return mpKeyStateCurr[key]; }
  u8        keyStatePrev  (u8 key) const  { return mpKeyStatePrev[key]; }
  
  bool      checkPrevious (u8 key) const  { return (mpKeyStatePrev[key] & 0x80) != 0; }
  bool      checkPressed  (u8 key) const  { return (mpKeyStateCurr[key] & 0x80) != 0; }
  bool      checkReleased (u8 key) const  { return (mpKeyStatePrev[key] & (~mpKeyStateCurr[key]) & 0x80) != 0;  }
  bool      checkTriggered  (u8 key) const  { return (mpKeyStateCurr[key] & (~mpKeyStatePrev[key]) & 0x80) != 0;  }
  
  // return the current cursor (mouse) position
  s32       cursorPosX    () const    { return mCursorPosX;   }
  s32       cursorPosY    () const    { return mCursorPosY;   }

  // return the cursor (mouse) displacement between the last 2 updates
  s32       cursorDeltaX  () const    { return mCursorDeltaX; }
  s32       cursorDeltaY  () const    { return mCursorDeltaY; }
};

// ---------------------------------------------------------------------------

class System
{
  friend class  Input;

public:
  static System*  Instance    ();
  static void   Free      ();

  bool      InitWindow    (HINSTANCE hAppInst, LPCSTR pTitle, u32 width, u32 height);
  bool      InitConsole   (LPCSTR pTitle);

  u32       WinSizeX    () const  { return mWinSizeX; }
  u32       WinSizeY    () const  { return mWinSizeY; }

  bool      WinExists   () const  { return mWinExists;  }
  bool      WinActive   () const  { return mWinActive;  }

  void      WinText     (const char* pText);

  // reset the frame counter and its associated variables
  void      FrameReset    (u32 frameRateMax = 60);

  void      FrameStart    ();
  void      FrameEnd    ();

  u32       FrameRateMax  () const  { return mFrameRateMax; }
  f64       FrameTimeMin  () const  { return mFrameTimeMin; }

  u32       FrameCounter  () const  { return mFrameCounter; }
  u32       FrameRate   () const  { return mFrameRate;    }
  f64       FrameTime   () const  { return mFrameTime;    }
  f64       FrameTimeCPU  () const  { return mFrameTimeCPU; }
  
private:
  HINSTANCE   mhAppInstance;
  LPCSTR      mpWinTitle;
  LPCSTR      mpWinClassName;

  WNDCLASS    mWinClass;
  HWND      mhWin;

  u32       mWinSizeX, 
          mWinSizeY;

  bool      mWinExists;
  bool      mWinActive;
  
  // console title
  LPCSTR      mpConsoleTitle;

  // openGL device context
  HDC       mhDeviceContext;
  HGLRC     mhRenderContext;

  // maximum allowed framerate (the frame rate lock)
  // * mFrameTimeMin = 1.0 / mFrameRateMax;
  u32       mFrameRateMax;
  f64       mFrameTimeMin;

  u32       mFrameCounter;
  u32       mFrameRate;
  f64       mFrameTime;
  f64       mFrameTimeCPU;
  
  f64       mFrameTimeStart;
  f64       mFrameTimeEnd;

          System      ();
          System      (const System& rhs);
  System&     operator=   (const System& rhs);

          ~System     ();

  // window callback function
  static LRESULT CALLBACK winCallBack(HWND hWin, UINT msg, WPARAM wp, LPARAM lp);
};

// ---------------------------------------------------------------------------

class Image
{
public:
  // create an empty image
  // * bpp must be 24 or 32
  static Image* Create  (u32 sizeX, u32 sizeY, u32 bpp = 32);

  // load image from disk
  static Image* Load  (const char* pName);

  // free previously created/loaded image
  static void   Free  (Image* pImage);
  
  // save the image to disk
  void      Save  (const char* pName);

  const u8*   Data  () const  { return mpData;  }
  u8*       Data  ()      { return mpData;  }
  u32       BPP   () const  { return mBPP;  }
  u32       SizeX () const  { return mSizeX;  }
  u32       SizeY () const  { return mSizeY;  }

private:
  u8*       mpData;
  u32       mBPP;
  u32       mSizeX;
  u32       mSizeY;

  // ---------------------------------------------------------------------------

          Image ();
          Image (const Image& rhs);
          ~Image  ();

  // ---------------------------------------------------------------------------
  
  bool      loadTGA (u8* pData, u32 dataSize);
  bool      saveTGA (const char* pName);
  bool      saveTXT (const char* pName);
};

// ---------------------------------------------------------------------------
// Function prototypes

// shortcut to get the frame rate information from the system class
u32 FrameCounter();
u32 FrameRate ();
f64 FrameTime ();

// ---------------------------------------------------------------------------

// function to get the high resolution time
void GetHiResTime(f64* pT);

// function to calculate CRC of a given string
u32 StrToId(const s8* pInput);

// return true if x is a power of 2
template<typename T>
bool IsPowOf2(T x)
{
  return ((x > 0) && ((x & (x - 1)) == 0));
}

// ---------------------------------------------------------------------------

template <typename T>
inline T DegToRad(const T x)
{
  return x * (PI / 180.0);
}

// ---------------------------------------------------------------------------

template <typename T>
inline T RadToDeg(const T x)
{
  return x * (180.0 / PI);
}

// ---------------------------------------------------------------------------

template <typename T>
inline T Min(const T x, const T y)
{
  return (x < y) ? x : y;
}

// ---------------------------------------------------------------------------

inline Vec2 Min(const Vec2& x, const Vec2& y)
{
  return Vec2(
    (x.x < y.x) ? x.x : y.x, 
    (x.y < y.y) ? x.y : y.y);
}

// ---------------------------------------------------------------------------

inline Vec3 Min(const Vec3& x, const Vec3& y)
{
  return Vec3(
    (x.x < y.x) ? x.x : y.x, 
    (x.y < y.y) ? x.y : y.y, 
    (x.z < y.z) ? x.z : y.z);
}

// ---------------------------------------------------------------------------

inline Vec4 Min(const Vec4& x, const Vec4& y)
{
  return Vec4(
    (x.x < y.x) ? x.x : y.x, 
    (x.y < y.y) ? x.y : y.y, 
    (x.z < y.z) ? x.z : y.z, 
    (x.w < y.w) ? x.w : y.w);
}

// ---------------------------------------------------------------------------

template <typename T>
inline T Max(const T x, const T y)
{
  return (x < y) ? y : x;
}

// ---------------------------------------------------------------------------

inline Vec2 Max(const Vec2& x, const Vec2& y)
{
  return Vec2(
    (x.x > y.x) ? x.x : y.x, 
    (x.y > y.y) ? x.y : y.y);
}

// ---------------------------------------------------------------------------

inline Vec3 Max(const Vec3& x, const Vec3& y)
{
  return Vec3(
    (x.x > y.x) ? x.x : y.x, 
    (x.y > y.y) ? x.y : y.y, 
    (x.z > y.z) ? x.z : y.z);
}

// ---------------------------------------------------------------------------

inline Vec4 Max(const Vec4& x, const Vec4& y)
{
  return Vec4(
    (x.x > y.x) ? x.x : y.x, 
    (x.y > y.y) ? x.y : y.y, 
    (x.z > y.z) ? x.z : y.z, 
    (x.w > y.w) ? x.w : y.w);
}

// ---------------------------------------------------------------------------

template <typename T>
inline T Clamp(const T x, const T xMin, const T xMax)
{
  return Max(xMin, Min(x, xMax));
}

// ---------------------------------------------------------------------------

template <typename T>
inline T Wrap(const T x, const T xMin, const T xMax)
{
  return (x < xMin) ? (x + (xMax - xMin)) : ((x > xMax) ? (x - (xMax - xMin)) : x);
}

// ---------------------------------------------------------------------------

template <typename T0, typename T1>
inline T0 Lerp(const T0 xMin, const T0 xMax, const T1 t)
{
  return xMin + (xMax - xMin) * t;
}

// ---------------------------------------------------------------------------

template <typename T>
inline bool InRange(const T x, const T xMin, const T xMax)
{
  return ((xMin <= x) && (x <= xMax));
}

// ---------------------------------------------------------------------------

template <typename T>
inline void Swap(T& x, T& y)
{
  T temp = x;
  x      = y;
  y      = temp;
}

// ---------------------------------------------------------------------------

inline bool IsEqual(f32 x, f32 y)
{
  return (fabs(x - y) < EPSILON * Max(1.0f, Max(fabs(x), fabs(y))));
}

// ---------------------------------------------------------------------------

inline bool IsEqual(f64 x, f64 y)
{
  return (abs(x - y) < EPSILON * Max(1.0, Max(abs(x), abs(y))));
}

// ---------------------------------------------------------------------------

inline bool IsEqual(const Vec3& x, const Vec3& y)
{
  return IsEqual(x.x, y.x) && IsEqual(x.y, y.y) && IsEqual(x.z, y.z);
}

// ---------------------------------------------------------------------------

} // namespace SFW

// ---------------------------------------------------------------------------

#endif // SFW_H


