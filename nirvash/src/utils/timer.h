#ifndef _TIMER_H_
#define _TIMER_H_

namespace Nepgear
{

/* store two points of time and a difference */
class Timer
{
public:
	double ago();

	void calculate_delta();
	void touch();

protected:
	struct
	{
	  double then;
	  double now;
	  double delta;
	} time;
};

}

#endif

