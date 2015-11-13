float cycleFraction(long startTime, long duration) {
  return ((float)(millis() - startTime))/((float)duration);
}

void hsi2rgb(float H, char* rgb) {
        int r, g, b;
        H = ((int)H)%360; // cycle H around to 0-360 degrees
        H = 3.14159 * H / 180.0; // Convert to radians.

        // Math! Thanks in part to Kyle Miller.
        if (H < 2.09439) {
                r = hsi_calc_1(H);
                g = hsi_calc_2(H);
                b = 0;
        } else if (H < 4.188787) {
                H = H - 2.09439;
                g = hsi_calc_1(H);
                b = hsi_calc_2(H);
                r = 0;
        } else {
                H = H - 4.188787;
                b = hsi_calc_1(H);
                r = hsi_calc_2(H);
                g = 0;
        }
        rgb[0] = r;
        rgb[1] = g;
        rgb[2] = b;
}

float hsi_calc_1(float H){
        return 85 * (1 + cos(H) / cos(1.047196667 - H));
}
float hsi_calc_2(float H){
        return 85 * (1 + (1 - cos(H) / cos(1.047196667 - H)));
}
