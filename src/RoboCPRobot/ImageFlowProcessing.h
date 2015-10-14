#pragma once
#include <cv.h>
#include "Controller.h"

#define PI 3.1415  

struct CvCapture;
class DisplacementImages;

class ImageFlowProcessing:
	public Controller
{
public:
	void Start(void);
	void CountDisplacement(IplImage *Img1, IplImage *Img2, DisplacementImages *Displacement);
	void ShowOpticalFlow(CvCapture *Capture);
	ImageFlowProcessing(void);
	~ImageFlowProcessing(void);
};

