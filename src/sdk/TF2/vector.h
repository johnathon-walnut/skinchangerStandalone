#pragma once

#include <math.h>
#include <cfloat>
#define M_RADPI		57.295779513082
#define PI			3.14159265358979323846
#define PI_f		3.141592f
#define DEG2RAD(x)	((float)(x) * (float)((float)(PI) / 180.0f))
#define RAD2DEG(x)	((float)(x) * (float)(180.0f / (float)(PI)))

class Vector2D
{
public:
	float x, y;

	Vector2D(void)
	{
		x = y = 0.0f;
	}

	Vector2D(float X, float Y)
	{
		x = X; y = Y;
	}

	Vector2D(float* v)
	{
		x = v[0]; y = v[1];
	}

	Vector2D(const float* v)
	{
		x = v[0]; y = v[1];
	}

	Vector2D(const Vector2D& v)
	{
		x = v.x; y = v.y;
	}

	Vector2D& operator=(const Vector2D& v)
	{
		x = v.x; y = v.y; return *this;
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	Vector2D& operator+=(const Vector2D& v)
	{
		x += v.x; y += v.y; return *this;
	}

	Vector2D& operator-=(const Vector2D& v)
	{
		x -= v.x; y -= v.y; return *this;
	}

	Vector2D& operator*=(const Vector2D& v)
	{
		x *= v.x; y *= v.y; return *this;
	}

	Vector2D& operator/=(const Vector2D& v)
	{
		x /= v.x; y /= v.y; return *this;
	}

	Vector2D& operator+=(float v)
	{
		x += v; y += v; return *this;
	}

	Vector2D& operator-=(float v)
	{
		x -= v; y -= v; return *this;
	}

	Vector2D& operator*=(float v)
	{
		x *= v; y *= v; return *this;
	}

	Vector2D& operator/=(float v)
	{
		x /= v; y /= v; return *this;
	}

	Vector2D operator+(const Vector2D& v) const
	{
		return Vector2D(x + v.x, y + v.y);
	}

	Vector2D operator-(const Vector2D& v) const
	{
		return Vector2D(x - v.x, y - v.y);
	}

	Vector2D operator*(const Vector2D& v) const
	{
		return Vector2D(x * v.x, y * v.y);
	}

	Vector2D operator/(const Vector2D& v) const
	{
		return Vector2D(x / v.x, y / v.y);
	}

	Vector2D operator+(float v) const
	{
		return Vector2D(x + v, y + v);
	}

	Vector2D operator-(float v) const
	{
		return Vector2D(x - v, y - v);
	}

	Vector2D operator*(float v) const
	{
		return Vector2D(x * v, y * v);
	}

	Vector2D operator/(float v) const
	{
		return Vector2D(x / v, y / v);
	}

	void Set(float X = 0.0f, float Y = 0.0f)
	{
		x = X; y = Y;
	}

	float Length(void) const
	{
		return sqrtf(x * x + y * y);
	}

	float LengthSqr(void) const
	{
		return (x * x + y * y);
	}

	float DistTo(const Vector2D& v) const
	{
		return (*this - v).Length();
	}

	float DistToSqr(const Vector2D& v) const
	{
		return (*this - v).LengthSqr();
	}

	float Dot(const Vector2D& v) const
	{
		return (x * v.x + y * v.y);
	}

	bool IsZero(void) const
	{
		return (x > -0.01f && x < 0.01f &&
				y > -0.01f && y < 0.01f);
	}
};

class Vector
{
public:
	float x, y, z;

	__forceinline Vector()
	{
		x = y = z = 0.0f;
	}

	__forceinline void Zero()
	{
		x = y = z = 0.f;
	}

	__forceinline Vector(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
	}

	__forceinline void Clear()
	{
		x = y = z = 0.f;
	}

	__forceinline Vector(float* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	__forceinline Vector(const float* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	__forceinline Vector(const Vector& v)
	{
		x = v.x; y = v.y; z = v.z;
	}

	__forceinline Vector(const Vector2D& v)
	{
		x = v.x; y = v.y; z = 0.0f;
	}

	__forceinline Vector& operator=(const Vector& v)
	{
		x = v.x; y = v.y; z = v.z; return *this;
	}

	__forceinline float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	__forceinline float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	__forceinline Vector& operator+=(const Vector& v)
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}

	__forceinline Vector& operator-=(const Vector& v)
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	__forceinline Vector& operator*=(const Vector& v)
	{
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	__forceinline Vector& operator/=(const Vector& v)
	{
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	__forceinline Vector& operator+=(float v)
	{
		x += v; y += v; z += v; return *this;
	}

	__forceinline Vector& operator-=(float v)
	{
		x -= v; y -= v; z -= v; return *this;
	}

	__forceinline Vector& operator*=(float v)
	{
		x *= v; y *= v; z *= v; return *this;
	}

	__forceinline Vector& operator/=(float v)
	{
		x /= v; y /= v; z /= v; return *this;
	}

	__forceinline Vector operator+(const Vector& v) const
	{
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	__forceinline Vector operator-(const Vector& v) const
	{
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	__forceinline Vector operator*(const Vector& v) const
	{
		return Vector(x * v.x, y * v.y, z * v.z);
	}

	__forceinline Vector operator/(const Vector& v) const
	{
		return Vector(x / v.x, y / v.y, z / v.z);
	}

	__forceinline Vector operator+(float v) const
	{
		return Vector(x + v, y + v, z + v);
	}

	__forceinline Vector operator-(float v) const
	{
		return Vector(x - v, y - v, z - v);
	}

	__forceinline Vector operator*(float v) const
	{
		return Vector(x * v, y * v, z * v);
	}

	__forceinline Vector operator/(float v) const
	{
		return Vector(x / v, y / v, z / v);
	}

	__forceinline bool operator==(const Vector& v) const
	{
		return (x == v.x && y == v.y && z == v.z);
	}

	__forceinline bool operator!=(const Vector& v) const
	{
		return (x != v.x || y != v.y || z != v.z);
	}

	//negation operator
	__forceinline Vector operator-() const
	{
		return Vector(-x, -y, -z);
	}

	__forceinline void Set(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
	{
		x = X; y = Y; z = Z;
	}

	__forceinline Vector VectorMA(float scale, const Vector& direction)
	{
		Vector dest;
		dest.x = this->x + scale * direction.x;
		dest.y = this->y + scale * direction.y;
		dest.z = this->z + scale * direction.z;
		return dest;
	}

	__forceinline float Length(void) const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	__forceinline float LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}

	Vector Forward() const;

	__forceinline Vector PointBetween(const Vector& v, float fraction) const
	{
		return Vector(x + (v.x - x) * fraction, y + (v.y - y) * fraction, z + (v.z - z) * fraction);
	}

	__forceinline Vector Look(Vector target) const
	{
		target -= *this;
		Vector angles;
		if (target.y == 0.0f && target.x == 0.0f)
		{
			angles.x = (target.z > 0.0f) ? 270.0f : 90.0f;
			angles.y = 0.0f;
		}
		else
		{
			angles.x = static_cast<float>(atan2(-target.z, target.Length2D()) * 180.f / PI);
			angles.y = static_cast<float>(atan2(target.y, target.x) * 180.f / PI);
		}

		angles.z = 0.0f;
		return angles;
	}

	__forceinline Vector AngleTo() const
	{
		Vector angles;
		if (y == 0.0f && x == 0.0f)
		{
			angles.x = (z > 0.0f) ? 270.0f : 90.0f;
			angles.y = 0.0f;
		}
		else
		{
			angles.x = static_cast<float>(atan2(-z, Length2D()) * 180.f / PI);
			angles.y = static_cast<float>(atan2(y, x) * 180.f / PI);
		}

		angles.z = 0.0f;
		return angles;
	}

	__forceinline Vector Normalized() const
	{
		const float ln = Length();
		if (isnan(ln) || ln == 0.f)
			return Vector();
		Vector ret = *this;
		ret.x /= ln;
		ret.y /= ln;
		ret.z /= ln;
		return ret;
	};

	__forceinline float Normalize()
	{
		float fl_length = Length();
		float fl_length_normal = 1.f / (FLT_EPSILON + fl_length);

		x = x * fl_length_normal;
		y = y * fl_length_normal;
		z = z * fl_length_normal;

		return fl_length;
	}

	__forceinline Vector toAngle() const noexcept
	{
		return Vector{ RAD2DEG(atan2(-z, hypot(x, y))),
					 RAD2DEG(atan2(y, x)),
					 0.0f };
	}

	__forceinline Vector fromAngle() const noexcept
	{
		return Vector{ (float)(cos(DEG2RAD(x)) * cos(DEG2RAD(y))),
					 (float)(cos(DEG2RAD(x)) * sin(DEG2RAD(y))),
					 (float)(-sin(DEG2RAD(x))) };
	}

	__forceinline void Scale2D(const float scale)
	{
		x *= scale;
		y *= scale;
	}

	__forceinline void Rotate2D(const float& flYaw)
	{
		float s, c, r = DEG2RAD(flYaw);
		s = (float)sin(r); c = (float)cos(r);

		float _x = x, _y = y;

		x = (_x * c) - (_y * s);
		y = (_x * s) + (_y * c);
	}

	__forceinline void CrossProduct(const Vector& b, Vector& result)
	{
		result.x = this->y * b.z - this->z * b.y;
		result.y = this->z * b.x - this->x * b.z;
		result.z = this->x * b.y - this->y * b.x;
	}

	__forceinline float NormalizeInPlace()
	{
		return Normalize();
	}

	__forceinline float Length2D(void) const
	{
		return sqrtf(x * x + y * y);
	}

	__forceinline float Length2DSqr(void) const
	{
		return (x * x + y * y);
	}

	__forceinline float DistTo(const Vector& v) const
	{
		return (*this - v).Length();
	}

	__forceinline float DistToSqr(const Vector& v) const
	{
		return (*this - v).LengthSqr();
	}

	__forceinline float Dist2D(const Vector& v) const
	{
		return (*this - v).Length2D();
	}

	__forceinline float Dot(const Vector& v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}

	__forceinline Vector Cross(const Vector& v) const
	{
		return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	__forceinline bool IsZero(void) const
	{
		return (x > -0.01f && x < 0.01f &&
				y > -0.01f && y < 0.01f &&
				z > -0.01f && z < 0.01f);
	}

	__forceinline bool NonZero(void) const
	{
		return (x <= -0.01f || x >= 0.01f ||
				y <= -0.01f || y >= 0.01f ||
				z <= -0.01f || z >= 0.01f);
	}

	__forceinline Vector Scale(float fl)
	{
		return Vector(x * fl, y * fl, z * fl);
	}

	__forceinline void Init(float ix = 0, float iy = 0, float iz = 0)
	{
		x = ix; y = iy; z = iz;
	}

	__forceinline void MultAdd(Vector& vOther, float fl)
	{
		x += fl * vOther.x;
		y += fl * vOther.y;
		z += fl * vOther.z;
	}

	__forceinline Vector CrossProduct(const Vector& b)
	{
		return Vector(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}

	__forceinline  float* Base()
	{
		return (float*)this;
	}

	__forceinline  float const* Base() const
	{
		return (float const*)this;
	}
};

class Vector4D
{
public:
	float x, y, z, w;
};

using QAngle = Vector;
using RadianEuler = Vector;
using VelocityImpulse = Vector;
using AngularImpulse = Vector;

struct matrix3x4_t
{
public:
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void Init(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin)
	{
		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin)
	{
		Init(xAxis, yAxis, zAxis, vecOrigin);
	}

	inline void Invalidate(void)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_flMatVal[i][j] = 0x7FC00000;
			}
		}
	}

	Vector GetOrigin() const
	{
		return Vector(m_flMatVal[0][3], m_flMatVal[1][3], m_flMatVal[2][3]);
	}

	QAngle GetAngles() const
	{
		QAngle angles;

		// Calculate pitch
		if (m_flMatVal[2][0] != 1.0f && m_flMatVal[2][0] != -1.0f)
		{
			angles.x = -asinf(m_flMatVal[2][0]);
			// Calculate yaw
			angles.y = atan2f(m_flMatVal[2][1], m_flMatVal[2][2]);
			// Calculate roll
			angles.z = atan2f(m_flMatVal[1][0], m_flMatVal[0][0]);
		}
		else
		{
			// Gimbal lock case
			angles.y = 0;
			if (m_flMatVal[2][0] == -1.0f)
			{
				angles.x = static_cast<float>(PI) / 2.f;
				angles.z = atan2f(m_flMatVal[0][1], m_flMatVal[0][2]);
			}
			else
			{
				angles.x = static_cast<float>(-PI) / 2.f;
				angles.z = atan2f(-m_flMatVal[0][1], -m_flMatVal[0][2]);
			}
		}

		return angles;
	}

	float* operator[](int i) { return m_flMatVal[i]; }
	const float* operator[](int i) const { return m_flMatVal[i]; }
	float* Base() { return &m_flMatVal[0][0]; }
	const float* Base() const { return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4] = {};
};

