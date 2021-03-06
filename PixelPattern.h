#ifndef PixelPatterns_h
#define PixelPatterns_h

struct RGB {
	unsigned char r, g, b;
};

struct HSV {
	unsigned char h, s, v;
};

class PixelPattern
{
  public:
		
		PixelPattern();	
		
		void cycle(long duration); // startTime and duration in millis

		void fade(HSV from, HSV to, long duration);

		RGB loop();

		void stop();
		
		bool running();

 		RGB hsv2rgb(HSV hsv);

	private:

		long _startTime, _duration;
		
		HSV _from, _to;
		
		bool _clockwise;

		float cycleFraction();
		
};

#endif
