#ifndef PixelPatterns_h
#define PixelPatterns_h

enum PixelState { STOP, CYCLE, FADE };

class PixelPattern
{
  public:
		
		PixelPattern();	
		float I;
		long _startTime, _duration;
		PixelState	state;

		#ifndef NO_FADE
		float fade_from, fade_to;
		#endif

    void cycle(long duration); // startTime and duration in millis

		void fade(float fromH, float toH, long duration);

		void loop(char* rgb);

		void stop();

	private:

		void doFade(char* rgb);

    void hsi2rgb(float H, float I, char* rgb);

		float cycleFraction();
};

#endif
