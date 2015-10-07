#include <PixelPattern.h>
#include <Arduino.h>

PixelPattern::PixelPattern()
{
	_from = {0,255,255};
	_to = {0,255,255};
}

void PixelPattern::cycle(long duration=1000)
{
	_duration = duration;
	_startTime = millis();
	
	_from = {0, 255, 255};
	_to = {255, 255, 255};

}

void PixelPattern::fade(HSV from, HSV to, long duration=1000)
{
	_duration = duration;
	_startTime = millis();

	_from = from;
	_to = to;
}

void PixelPattern::stop()
{
	_duration = 0;
}

RGB PixelPattern::loop(){
	float fract = PixelPattern::cycleFraction();
	if( fract > 1.0 ){
		RGB rgb = {0, 0, 0};
		return rgb;
	} else {
		HSV hsv = {(int)((_to.h - _from.h)*cycleFraction()+0.5), 255, 255};
		return hsv2rgb(hsv);
	}
}

RGB PixelPattern::hsv2rgb(HSV hsv) {
	RGB rgb;
	unsigned char region, fpart, p, q, t;
	
    if(hsv.s == 0) {
        /* color is grayscale */
        rgb.r = rgb.g = rgb.b = hsv.v;
        return rgb;
    }
	
    /* make hue 0-5 */
    region = hsv.h / 43;
    /* find remainder part, make it from 0-255 */
    fpart = (hsv.h - (region * 43)) * 6;
	
	/* calculate temp vars, doing integer multiplication */
    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * fpart) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - fpart)) >> 8))) >> 8;
        
    /* assign temp vars based on color cone region */
    switch(region) {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p; break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p; break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t; break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v; break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v; break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q; break;
    }
    
    return rgb;
}

float PixelPattern::cycleFraction() {
	return ((float)(millis() - _startTime))/((float)_duration);
}
