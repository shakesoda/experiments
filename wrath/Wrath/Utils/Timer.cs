using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;

using OpenTK;

using Wrath;

namespace Wrath
{
	public class Timer
	{
		protected TimeSpan m_span;
		protected enum Mode { Countdown, Stopwatch };

		public Timer(double _time)
		{
			m_span = TimeSpan.FromSeconds(_time);
		}

		public void Touch()
		{
			m_time = 0.0f;
			m_span = TimeSpan.Zero;
		}

		public float GetTime()
		{
			TimeSpan _ret = TimeSpan.FromSeconds(m_time) - DateTime.Now.TimeOfDay.Seconds;
			return _ret.TotalSeconds;
		}
	}
}

