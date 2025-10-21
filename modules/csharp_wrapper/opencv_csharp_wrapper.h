#ifndef OPENCV_CSHARP_WRAPPER_H
#define OPENCV_CSHARP_WRAPPER_H

// OpenCV C# Wrapper Header
// This header provides C-style functions that can be called from C#

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#ifdef __cplusplus
extern "C" {
#endif

// VideoCapture wrapper functions
typedef void* VideoCaptureHandle;

// Create VideoCapture instance
VideoCaptureHandle opencv_videocapture_create(int device);

// Check if VideoCapture is opened
int opencv_videocapture_isOpened(VideoCaptureHandle handle);

// Read frame from VideoCapture
int opencv_videocapture_read(VideoCaptureHandle handle, unsigned char* data, int width, int height);

// Release VideoCapture
void opencv_videocapture_release(VideoCaptureHandle handle);

// Mat wrapper functions
typedef void* MatHandle;

// Create Mat instance
MatHandle opencv_mat_create(int rows, int cols, int type);

// Get Mat data pointer
unsigned char* opencv_mat_data(MatHandle handle);

// Get Mat dimensions
int opencv_mat_rows(MatHandle handle);
int opencv_mat_cols(MatHandle handle);
int opencv_mat_type(MatHandle handle);

// Check if Mat is empty
int opencv_mat_empty(MatHandle handle);

// Release Mat
void opencv_mat_release(MatHandle handle);

// High-level GUI functions
int opencv_imshow(const char* winname, MatHandle mat);
int opencv_waitKey(int delay);
void opencv_destroyAllWindows();

// Simple camera functions for C# integration
int opencv_camera_read_and_show(VideoCaptureHandle handle, const char* winname);
int opencv_camera_simple_test(int device, const char* winname);

// Utility functions
void opencv_initialize();
void opencv_cleanup();

#ifdef __cplusplus
}
#endif

#endif // OPENCV_CSHARP_WRAPPER_H
