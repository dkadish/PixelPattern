#include <PixelPattern.h>
#include <math.h>
#include <Arduino.h>

PixelPattern::PixelPattern()
{

	I = 1.0;

	#ifndef NO_FADE
	fade_from = 0.0;
	fade_to = 0.0;
	#endif

	state = STOP;
}

void PixelPattern::cycle(long duration=1000)
{
	_duration = duration;
	_startTime = millis();

	state = CYCLE;
}

#ifndef NO_FADE
void PixelPattern::fade(float fromH, float toH, long duration=1000)
{
	_duration = duration;
	_startTime = millis();

	fade_from = fromH;
	fade_to = toH;

	state = FADE;
}
#endif

void PixelPattern::stop()
{
	state = STOP;
}

void PixelPattern::loop(char* rgb){
	float fract = PixelPattern::cycleFraction();
	if( fract > 1.0 ){
		state = STOP;
	}

	switch(state){
		case STOP:
		  rgb[0] = 0;
			rgb[1] = 0;
			rgb[2] = 0;
			break;
		case CYCLE:
			hsi2rgb(fract * 360.0, I, rgb);
			break;
#ifndef NO_FADE
		case FADE:
			doFade(rgb);
#endif
	}

}

void PixelPattern::doFade(char* rgb){
	float H = (fade_to - fade_from)*cycleFraction();
	hsi2rgb(H, I, rgb);	
}

void PixelPattern::hsi2rgb(float H, float I, char* rgb) {
	int r, g, b;
	H = fmod(H, 360); // cycle H around to 0-360 degrees
	H = 3.14159 * H / (float)180; // Convert to radians.
	I = I > 0 ? (I < 1 ? I : 1) : 0;

	// Math! Thanks in part to Kyle Miller.
	if (H < 2.09439) {
		r = 255 * I / 3 * (1 + cos(H) / cos(1.047196667 - H));
		g = 255 * I / 3 * (1 + (1 - cos(H) / cos(1.047196667 - H)));
		b = 0;
	} else if (H < 4.188787) {
		H = H - 2.09439;
		g = 255 * I / 3 * (1 + cos(H) / cos(1.047196667 - H));
		b = 255 * I / 3 * (1 + (1 - cos(H) / cos(1.047196667 - H)));
		r = 0;
	} else {
		H = H - 4.188787;
		b = 255 * I / 3 * (1 + cos(H) / cos(1.047196667 - H));
		r = 255 * I / 3 * (1 + (1 - cos(H) / cos(1.047196667 - H)));
		g = 0;
	}
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}

float PixelPattern::cycleFraction() {
	return ((float)(millis() - _startTime))/((float)_duration);
}
