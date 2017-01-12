/*
 * image-pid.c
 *
 *  Created on: 2017年1月4日
 *      Author: kohill
 */

#include <stdint.h>
#define CAL_ROW_START 90
#define CAL_ROW_END 110
#define BALCK_WHITE_THRESHOLD 130

#define IMAGE_WIDTH 160
#define IMAGE_HEIGHT 120
#if ((IMAGE_HEIGHT < CAL_ROW_START) || (IMAGE_HEIGHT < CAL_ROW_END))
#error "Check CAL_ROW_END AND CAL_ROW_START PLEASE!"
#endif
#define LIMIT_SCOPE(x_,MIN_,MAX_) {if( x_< (MIN_) ) x_ = (MIN_); if ( x_ > (MAX_)) x_= (MAX_);};
typedef struct
{
	float k;
	float i;
	float integration;
}PID_PROCESS_Typedef;

static PID_PROCESS_Typedef pid_process={
	.k = 50.2f,
	.i = 0.02f,
	.integration = .0f,
};
uint32_t image_pid_update(const uint8_t *image){
	int32_t left_white_count = 0,right_white_count = 0;
	for(int i = CAL_ROW_START; i< CAL_ROW_END; i++ ){
		for(int j=0; j< IMAGE_WIDTH/2 ;j++){
			left_white_count  += (image[IMAGE_WIDTH * i + j ] > BALCK_WHITE_THRESHOLD)?1:0;
			right_white_count += (image[IMAGE_WIDTH * i + j + IMAGE_WIDTH/2] > BALCK_WHITE_THRESHOLD)?1:0;
		}
	}
	//PID 准备工作：单位归一化：

	float left_white_count_f  =  1.0f * left_white_count / ((CAL_ROW_END - CAL_ROW_START) * (IMAGE_WIDTH/2));
	float right_white_count_f  =  1.0f * right_white_count / ((CAL_ROW_END - CAL_ROW_START) * (IMAGE_WIDTH/2));
	float delta = left_white_count_f - right_white_count_f;
	pid_process.integration += delta;

	LIMIT_SCOPE(pid_process.integration , -10,+10);

	int32_t r = pid_process.k * (delta) + pid_process.i*(pid_process.integration);
	LIMIT_SCOPE(r,-20,+20);
	return  (r + 95);
}
