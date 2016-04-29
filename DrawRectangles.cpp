#include <opencv2/opencv.hpp>
using namespace cv;
#define WINDOW_NAME "Drawing Rectangle"

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(Mat& img, Rect box);

Rect g_rectangle;
bool g_bDrawingBox = false;
RNG g_rng(0);  // Generate random number

int main(int argc, char** argv) {
	Mat srcImage(600, 800, CV_8UC3);
	Mat tempImage;
	srcImage = Scalar::all(0);
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*) &srcImage);
	while (1) {
		srcImage.copyTo(tempImage);
		if (g_bDrawingBox)
			DrawRectangle(tempImage, g_rectangle);
		imshow(WINDOW_NAME, tempImage);
		if (waitKey(10) == 27)  // stop drawing rectanglge if the key is 'ESC'
			break;
	}
	return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param) {
	Mat& image = *(cv::Mat*) param;
	switch (event) {
	case EVENT_MOUSEMOVE: {    // When mouse moves, get the current rectangle's width and height
		if (g_bDrawingBox) {
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
		break;
	case EVENT_LBUTTONDOWN: {  // when the left mouse button is pressed down,
		                       //get the starting corner's coordinates of the rectangle
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0);
	}
		break;
	case EVENT_LBUTTONUP: {   //when the left mouse button is released,
		                      //draw the rectangle
		g_bDrawingBox = false;
		if (g_rectangle.width < 0) {
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}

		if (g_rectangle.height < 0) {
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		DrawRectangle(image, g_rectangle);
	}
		break;
	}
}
void DrawRectangle(Mat& img, Rect box)
{
	//Draw a rectangle with random color
	rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255),
					g_rng.uniform(0,255),g_rng.uniform(0,255)));
}
