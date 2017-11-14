#pragma once

#include <algorithm>
#include <vector>
#include <d2d1.h>
#ifdef _DEBUG
#pragma comment(lib,"Vec2Lib_d.lib")
#else
#pragma comment(lib,"Vec2Lib_r.lib")
#endif


static const double EPS = 0.0000000001;
#define PI (float)M_PI

template <typename T>
inline T sq(T val)
{
	return val * val;
}

template <typename T>
class _Vec2
{
public:
	inline			_Vec2() {}
	inline			_Vec2(T x, T y)
		:
		x(x),
		y(y)
	{}
	inline			_Vec2(const _Vec2& vect)
		:
		_Vec2(vect.x, vect.y)
	{}
	template <typename T2>
	inline			operator _Vec2< T2 >() const
	{
		return{ (T2)x,(T2)y };
	}
	inline T Angle()
	{
		return (T)atan2(y, x);
	}
	inline void ConfineLength(T len)
	{
		x = (T)cosf(angle()) * len;
		y = (T)sinf(angle()) * len;

	}
	inline T		LenSq() const
	{
		return *this * *this;
	}
	inline T		Len() const
	{
		return sqrt(LenSq());
	}
	inline _Vec2&	Normalize()
	{
		const T length = Len();
		x /= length;
		y /= length;
		return *this;
	}
	inline _Vec2&	CCW90()
	{
		T temp = y;
		y = -x;
		x = temp;
		return *this;
	}
	inline _Vec2&	CW90()
	{
		T temp = y;
		y = x;
		x = -temp;
		return *this;
	}
	inline _Vec2&	Swap(_Vec2& vect)
	{
		const _Vec2 temp = vect;
		vect = *this;
		*this = temp;
		return *this;
	}
	inline _Vec2	operator-() const
	{
		return _Vec2(-x, -y);
	}
	inline _Vec2&	operator=(const _Vec2 &rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}
	inline _Vec2&	operator+=(const _Vec2 &rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}
	inline _Vec2&	operator-=(const _Vec2 &rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}
	inline T		operator*(const _Vec2 &rhs) const
	{
		return this->x * rhs.x + this->y * rhs.y;
	}
	inline _Vec2	operator+(const _Vec2 &rhs) const
	{
		return _Vec2(*this) += rhs;
	}
	inline _Vec2	operator-(const _Vec2 &rhs) const
	{
		return _Vec2(*this) -= rhs;
	}
	inline _Vec2&	operator*=(const T &rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}
	inline _Vec2	operator*(const T &rhs) const
	{
		return _Vec2(*this) *= rhs;
	}
	inline _Vec2&	operator/=(const T &rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		return *this;
	}
	inline _Vec2	operator/(const T &rhs) const
	{
		return _Vec2(*this) /= rhs;
	}
	inline T		CrossWith(const _Vec2 &rhs) const
	{
		return x * rhs.y - y * rhs.x;
	}
	inline D2D1_POINT_2F ToD2DPointF()
	{
		return D2D1::Point2F((float)x, (float)y);
	}
	inline D2D1_POINT_2U ToD2DPointU()
	{
		return D2D1::Point2U((UINT)x, (UINT)y);
	}
	inline _Vec2	ClosestPtOnLine(const _Vec2 &lnpt1, const _Vec2 &lnpt2) const
	{
		_Vec2 p1 = lnpt1;
		_Vec2 p2 = lnpt2;
		_Vec2 pointOnLine;
		if (abs(p1.x - p2.x) > 0.0f)
		{
			if (p1.x > p2.x)
			{
				p1.Swap(p2);
			}
			const T m = (p2.y - p1.y) / (p2.x - p1.x);
			const T b = p1.y - m * p1.x;

			if (abs(m) > 0.0f)
			{
				T n = -1.0f / m;
				T c = this->y - this->x * n;
				pointOnLine.x = (b - c) / (n - m);
				pointOnLine.y = m * pointOnLine.x + b;
			}
			else
			{
				pointOnLine.x = this->x;
				pointOnLine.y = p1.y;
			}
		}
		else
		{
			pointOnLine.x = p1.x;
			pointOnLine.y = this->y;
		}
		return pointOnLine;
	}
	inline bool		IsInsideRect(const _Vec2 &p1, const _Vec2 & p2) const
	{
		const T medianX = (p1.x + p2.x) / 2.0f;
		const T medianY = (p1.y + p2.y) / 2.0f;
		return abs(medianX - x) <= abs(medianX - p1.x) &&
			abs(medianY - y) <= abs(medianY - p1.y);
	}
	inline bool		operator==(const _Vec2 &rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	inline bool		operator!=(const _Vec2 &rhs) const
	{
		return !(*this == rhs);
	}
	inline _Vec2	MidpointWith(const _Vec2& p2) const
	{
		return _Vec2((x + p2.x) / 2.0f, (y + p2.y) / 2.0f);
	}
	inline _Vec2	Rotation(const float angle) const
	{
		_Vec2<T> result;
		float cosine = cosf(angle);
		float sine = sinf(angle);
		result.x = x * cosine - y * sine;
		result.y = x * sine + y * cosine;
		return result;
	}

public:
	union {
		struct
		{
			T x;
			T y;
		};
		struct
		{
			T width;
			T height;
		};
		struct
		{
			T column;
			T row;
		};
	};
};

typedef _Vec2< float > Vec2f;
typedef _Vec2< double > Vec2d;
typedef _Vec2< int > Vec2i;

template< typename T >
inline std::vector< _Vec2<T> > CalculateIntersectionPoints(_Vec2<T> q, _Vec2<T> p1, _Vec2<T> p2, T r)
{
	std::vector< _Vec2<T> > points;
	// calculate discriminant
	const _Vec2<T> d = p2 - p1;
	const T dr2 = d.LenSq();
	const T D = (p1 - q).CrossWith(p2 - q);
	const T disc = sq(r) * dr2 - sq(D);
	// line intersection test
	if (disc >= (T)0.0)
	{
		// calculate points of intersection
		const T sqrtDisc = sqrt(disc);
		const T lhsx = D * d.y;
		const T rhsx = sgn(d.y) * d.x * sqrtDisc;
		const T lhsy = -D * d.x;
		const T rhsy = abs(d.y) * sqrtDisc;
		points.push_back(_Vec2<T> { (lhsx + rhsx) / dr2, (lhsy + rhsy) / dr2 } +q);
		if (disc > (T)0.0)
		{
			points.push_back(_Vec2<T> { (lhsx - rhsx) / dr2, (lhsy - rhsy) / dr2 } +q);
		}
	}
	return points;
}


template < typename T >
class Rect
{
public:
	inline	Rect() {}
	inline	Rect(T left, T top, T right, T bottom)
		:
		left(left),
		top(top),
		right(right),
		bottom(bottom)
	{}
	inline	Rect(const Rect& rect)
		:
		top(rect.top),
		bottom(rect.bottom),
		left(rect.left),
		right(rect.right)
	{}
	inline	Rect(_Vec2<T> p0, _Vec2<T> p1)
		:
		Rect(min(p0.x, p1.x),
			min(p0.y, p1.y),
			max(p0.x, p1.x),
			max(p0.y, p1.y))
	{}
	inline Rect(D2D1_RECT_F& rct)
	{
		(float)left = rct.left;
		(float)top = rct.top;
		(float)right = rct.right;
		(float)bottom = rct.bottom;
	}
	inline	void Translate(_Vec2< T > d)
	{
		Translate(d.x, d.y);
	}
	inline	void Translate(T dx, T dy)
	{
		top += dy;
		bottom += dy;
		left += dx;
		right += dx;
	}
	inline bool operator == (Rect& other)
	{
		return left == other.left && top == other.top &&
			right == other.right && bottom == other.bottom;
	}
	template < typename T2 >
	inline	operator Rect< T2 >() const
	{
		return{ (T2)left,(T2)top,(T2)right,(T2)bottom };
	}
	inline	void ClipTo(const Rect& rect)
	{
		top = max(top, rect.top);
		bottom = min(bottom, rect.bottom);
		left = max(left, rect.left);
		right = min(right, rect.right);
	}
	inline	void ClipTo(const Rect& rect)const
	{
		top = max(top, rect.top);
		bottom = min(bottom, rect.bottom);
		left = max(left, rect.left);
		right = min(right, rect.right);
	}
	inline Rect ClipWith(const Rect& R)const
	{
		return{
			std::max(left, R.left),
			std::max(top, R.top),
			std::min(right, R.right),
			std::min(bottom, R.bottom)
		};
	}
	inline	T GetWidth() const
	{
		return right - left;
	}
	inline	T GetHeight() const
	{
		return bottom - top;
	}
	inline	bool Overlaps(const Rect& rect) const
	{
		return top < rect.bottom && bottom > rect.top &&
			left < rect.right && right > rect.left;
	}
	template < typename T2 >
	inline	bool Contains(_Vec2<T2> p) const
	{
		return p.y >= top && p.y <= bottom && p.x >= left && p.x <= right;
	}
	inline D2D1_RECT_F ToD2D()
	{
		return D2D1::RectF((float)left, (float)top, (float)right, (float)bottom);
	}
	
	inline _Vec2< T > Min()
	{
		return _Vec2<T>(left, top);
	}
	
	inline _Vec2< T > Max()
	{
		return _Vec2<T>(right, bottom);
	}
	inline _Vec2< T > Min()const
	{
		return _Vec2<T>(left, top);
	}

	inline _Vec2< T > Max()const
	{
		return _Vec2<T>(right, bottom);
	}
public:
	union {
		struct {
			T left;
			T top;
			T right;
			T bottom;
		};
		struct {
			T r;
			T g;
			T b;
			T a;
		};
	};
};

typedef Rect< int > RectI;
typedef Rect< float > RectF;

template<typename T>
class Sphere
{
public:
	Sphere() = default;
	Sphere(const _Vec2<T>& center, const T& radius)
		:center(center), radius(radius)
	{}
	_Vec2<T> center;
	T radius;
};
typedef Sphere<float> SphereF;
template<typename T>
class AABB
{
public:
	_Vec2<T> minPt;
	_Vec2<T> maxPt;
	AABB() = default;
	AABB(_Vec2<T> min, _Vec2<T> max)
		:minPt(min), maxPt(max)
	{}
	AABB(Rect<T>& rect)
		:minPt(rect.left, rect.top), maxPt(rect.right, rect.bottom)
	{}
	float Width() { return maxPt.x - minPt.x; }
	float Height() { return maxPt.y - minPt.y; }
};
typedef AABB<float> AABBF;
template<typename T>
class Line
{
public:
	_Vec2<T> pt0;
	_Vec2<T> pt1;
	Line() = default;
	Line(_Vec2<T> p0, _Vec2<T> p1)
		:pt0(p0), pt1(p1)
	{}
	_Vec2<T> MidPoint()
	{
		return pt0.MidpointWith(pt1);
	}
};
typedef Line<float> LineF;
typedef Line<int> LineI;
typedef std::vector<Vec2f> Vec2fContainer;
class Intersect
{
public:
	static bool BoundingBox(const RectF& A, const RectF& B, Vec2f& correction);
	static Vec2fContainer LineToSpherePts(LineF& line, SphereF& sphere);
	static bool LineToSphere(const LineF& line, const SphereF& sphere);
	static bool LineToLine(const LineF& A, const LineF& B, Vec2f& intersectPt);
	static bool LineToLine(const LineF& A, const LineF& B);
	static bool LineToBoundingBox(const LineF& line, const AABBF& box);
	static bool PointInBoundingBox(const Vec2f& point, const AABBF& box);
	static bool BoundingBox(const AABBF& A, const AABBF& B);
	static bool BoundingBoxToSphere(const AABBF& box, const SphereF& sphere);
};