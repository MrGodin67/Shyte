#pragma once
#include <math.h>
#include <vector>
#include <algorithm>
#include <d2d1.h>
#ifdef _DEBUG
#pragma comment(lib,"Lib2D_d.lib")
#else
#pragma comment(lib,"Lib2D_r.lib")
#endif


namespace bw
{
	static const double EPS = 0.0000000001;
#define PI (float)M_PI

	template <typename T>
	inline T sq(T val)
	{
		return val * val;
	}


	template <typename T>
	T sgn(T val)
	{
		return (T)((T)0 <= val) - (val < (T)0);
	}
	class Vector2D
	{
	public:
		float x;
		float y;

	public:
		Vector2D();
		Vector2D(float _x, float _y);
		Vector2D(const Vector2D& vect);
		~Vector2D();
		float       angle();
		float       lengthSq() const;
		float       length() const;
		float       dot(Vector2D& other)const;
		Vector2D&	normalize();
		Vector2D&	cw90();
		Vector2D&	ccw90();
		void        confineLength(float len);
		Vector2D&	swap(Vector2D& vect);
		Vector2D	operator-() const;
		Vector2D&	operator=(const Vector2D &rhs);
		Vector2D&	operator+=(const Vector2D &rhs);
		Vector2D&	operator-=(const Vector2D &rhs);
		float       operator*(const Vector2D &rhs) const;
		Vector2D	operator+(const Vector2D &rhs) const;
		Vector2D	operator-(const Vector2D &rhs) const;
		Vector2D&	operator*=(float &rhs);
		Vector2D	operator*(float&rhs) const;
		Vector2D&	operator/=(float &rhs);
		Vector2D	operator/(float &rhs) const;
		Vector2D	operator/(const float &rhs);
		float       cross(const Vector2D &rhs) const;
		Vector2D	midPoint(const Vector2D& p2) const;
		Vector2D	rotation(const float angle) const;
		bool		operator==(const Vector2D &rhs) const;
		bool		operator!=(const Vector2D &rhs) const;
		D2D1_POINT_2F ToD2DPointF();

	};

	typedef Vector2D Vec2f;
	typedef std::vector<Vector2D> Vec2Container;
	//////////////////////////////////////////////////////////
	class Size2D
	{
	public:
		float width;
		float height;
		Size2D();
		Size2D(float w, float h);
		Size2D(const Size2D& size);
	};
	//////////////////////////////////////////
	class Rect
	{
	public:
		float left;
		float top;
		float right;
		float bottom;
		Rect();
		Rect(float l, float t, float r, float b);
		bool overlaps(const Rect& other)const;
		bool contains(float x, float y)const;
		bool contains(const Vector2D& pt)const;
		D2D1_RECT_F ToD2DRectF();
	};

	//////////////////////////////////////////////////
	// SPHERE
	//////////////////////////////////////////////////
	class Sphere2D
	{
	public:
		Vector2D center;
		float radius;
		Sphere2D();
		Sphere2D(Vector2D& center, float &radius);
		bool pointIn(const float& x, const float& y)const;
		bool pointIn(const Vector2D& pt)const;
		bool overlaps(const Sphere2D& other)const;
	};

	///////////////////////////////////////////////////////
	// LINE SEGMENT
	///////////////////////////////////////////////////////
	class LineSegment
	{
	public:
		Vector2D pt0;
		Vector2D pt1;
		LineSegment();
		LineSegment(Vector2D p0, Vector2D p1);
		LineSegment(const LineSegment& other);
		Vector2D MakeNormal();
	};
	//////////////////////////////////////////////
	// AABB
	//////////////////////////////////////////////
	class BoundingBox2D
	{
	public:
		Vector2D minPt;
		Vector2D maxPt;
		BoundingBox2D();
		BoundingBox2D(const Vector2D& minP, const Vector2D& maxP);
		BoundingBox2D(const BoundingBox2D& other);
		float width()const;
		float height()const;
	};
	//////////////////////////////////////////////
	// TRIANGLE
	//////////////////////////////////////////////
	class Triangle
	{
	public:
		Triangle();
		Triangle(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2);
		Triangle(const Triangle& tri);
		Vector2D center();
		Vector2D pt0;
		Vector2D pt1;
		Vector2D pt2;
	};
	///////////////////////////////////////////////
	// Shape
	///////////////////////////////////////////////
	class Shape
	{
	protected:
		Vec2Container verticies;
	public:
		Shape();
		virtual ~Shape() {}
		Shape(Vec2Container& verts);
	};

	////////////////////////////////////////////////////
	// Matrix 3X3
	/////////////////////////////////////////////////////
	class Matrix3x3
	{
	public:
		Matrix3x3() = default;
		Matrix3x3(float e0, float e1, float e2, float e3, float e4,
			float e5, float e6, float e7, float e8)
		{

			elements[0][0] = e0;
			elements[0][1] = e1;
			elements[0][2] = e2;

			elements[1][0] = e3;
			elements[1][1] = e4;
			elements[1][2] = e5;

			elements[2][0] = e6;
			elements[2][1] = e7;
			elements[2][2] = e8;


		}
		Matrix3x3& operator =(const Matrix3x3& rhs);
		Matrix3x3& operator *=(const float rhs);
		Matrix3x3 operator *(const float rhs) const;
		Matrix3x3 operator *(const Matrix3x3& rhs) const;
		Matrix3x3& operator *=(const Matrix3x3& rhs);
		Vector2D operator *(const Vector2D rhs) const;
	public:
		// [ row ][ col ]
		float elements[3][3];
	};
	class  Mat3x3Construct
	{
	public:
		static Matrix3x3 Identity();
		static Matrix3x3 Rotation(float theta);
		static Matrix3x3 Scaling(float factor);
		static Matrix3x3 Translation(const Vector2D offset);
	};
	///////////////////////////////////////////////
	// Intersects
	///////////////////////////////////////////////
	class Intersect
	{
	public:
		static Vec2Container LineToSpherePts(LineSegment& line, Sphere2D& sphere);
		static bool LineToSphere(const LineSegment& line, const Sphere2D& sphere);
		static bool LineToLine(const LineSegment& A, const LineSegment& B, Vector2D& intersectPt);
		static bool LineToLine(const LineSegment& A, const LineSegment& B);
		static bool LineToBoundingBox(const LineSegment& line, const BoundingBox2D& box);
		static bool PointInBoundingBox(const Vector2D& point, const BoundingBox2D& box);
		static bool BoundingBox(const BoundingBox2D& A, const BoundingBox2D& B);
		static bool BoundingBoxToSphere(const BoundingBox2D& box, const Sphere2D& sphere);
	};

}

