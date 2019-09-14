#ifndef _TRACER_H_
#define _TRACER_H_

#include <common/Math.h>
#include <common/Array.h>

//! �������� ������ � ������������, ��� ������
class CTracer
{
public:
	CTracer(int iTracePoolSize = 10);
	~CTracer();

	//! �������� ����� ����� �� ����� vPoint � ������ fFracColor (0-1)
	void begin(const float3 &vPoint, float fFracColor = 0.0f);

	//! ����������� �������� �����
	void end();

	//! ������� ��� �������
	void clear();

	//! �������� ����� �� ��������� �����
	void lineTo(const float3 &vPoint, float fFracColor=0.0f);

	void render();

protected:
	bool m_isTracing;
	int m_iCurTrace;
	int m_iPoolSize;
	int m_iLineCount;

	void putPoint(const float3 &vPoint, float fFracColor);
	unsigned int getColor(float fFrac);

	struct Point
	{
		float3_t vPos;
		unsigned int color;
	};

	Array<Point> *m_vpPoints;
};

#endif
