#include <stdio.h>
#include "seven_seg_peripheral.h"

/*
Prints out the contents of a seven seg display
*/
void print_seven_segment(SEVEN_SEG_DISPLAY sev_display){

	printf("%c = %u", SEV_SEG_A, sev_display.seg_a);
	printf("%c = %u", SEV_SEG_B, sev_display.seg_b);
	printf("%c = %u", SEV_SEG_C, sev_display.seg_c);
	printf("%c = %u", SEV_SEG_D, sev_display.seg_d);
	printf("%c = %u", SEV_SEG_E, sev_display.seg_e);
	printf("%c = %u", SEV_SEG_F, sev_display.seg_f);
	printf("%c = %u", SEV_SEG_G, sev_display.seg_g);
}


/*
Sets the correct section of the seven segment display

sev_display: The seven segment display
seg: The char segment selected
value: The value to set the segment to

Returns:
Returns 0 on success, a negative value on failure
*/
int set_seven_segment(SEVEN_SEG_DISPLAY * sev_display, char seg, unsigned int value){

	//Make sure that the segment value is no greater than max val of
	//one byte
	if(value > SEV_SEG_MAX_VAL){
		return -1;
	}


	switch(seg){
		case SEV_SEG_A:
			sev_display->seg_a = value;
			break;
		case SEV_SEG_B:
			sev_display->seg_b = value;
			break;
		case SEV_SEG_C:
			sev_display->seg_c = value;
			break;
		case SEV_SEG_D:
			sev_display->seg_d = value;
			break;
		case SEV_SEG_E:
			sev_display->seg_e = value;
			break;
		case SEV_SEG_F:
			sev_display->seg_f = value;
			break;
		case SEV_SEG_G:
			sev_display->seg_g = value;
			break;

		//Invalid segment
		default:
			return -1;
	}
	return 0;
}