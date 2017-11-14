#pragma once
#include "Shape.h"


class sRectangle :
	public Shape
{
	RectF m_frame;
	bool m_draw;
	bool m_drawFilled;
	enum class LineType {
		left, top, right, bottom
	};
	class sLine GetLine(const LineType& line);
public:
	
public:
	sRectangle();
	sRectangle(const RectF& rect,bool draw = false,bool drawFilled = false);
	~sRectangle();

	
	class sLine GetLeftLine();
	class sLine GetTopLine();
	class sLine GetRightLine();
	class sLine GetBottomLine();
	RectF operator()();
	virtual void Draw(class Graphics& gfx)override;
	


private: // funtions
	
};

