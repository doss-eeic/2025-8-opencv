/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2009, Willow Garage Inc., all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#ifndef OPENCV_CSHARP_HPP
#define OPENCV_CSHARP_HPP

// OpenCV C# Wrapper Header
// This header provides C-style functions that can be called from C#

#include <opencv2/opencv.hpp>


extern "C" {    
    // VideoCapture functions
    void* cvsharp_videocapture_create(int device);
    bool cvsharp_videocapture_isopened(void* cap);
    bool cvsharp_videocapture_read(void* cap, void* frame);
    void cvsharp_videocapture_release(void* cap);
    
    // Mat functions
    void* cvsharp_mat_create();
    void* cvsharp_mat_create_with_params(int rows, int cols, int type);
    int cvsharp_mat_get_rows(void* mat);
    int cvsharp_mat_get_cols(void* mat);
    int cvsharp_mat_get_type(void* mat);
    bool cvsharp_mat_is_empty(void* mat);
    void cvsharp_mat_release(void* mat);
    
    // Image functions
    bool cvsharp_imwrite(const char* filename, void* frame);
    void cvsharp_imshow(const char* winname, void* frame);
    int cvsharp_waitkey(int delay);
    void cvsharp_destroyallwindows();
}

class cvsharp {
public:
    class VideoCapture {
    private:
        cv::VideoCapture* m_cap;
        
    public:
        VideoCapture(int device);
        ~VideoCapture();
        bool isOpened();
        bool read(cv::Mat& frame);
        void release();
    };

    class Mat {
    private:
        cv::Mat* m_mat;
        
    public:
        Mat();
        Mat(int rows, int cols, int type);
        ~Mat();
        int get_rows();
        int get_cols();
        int get_type();
        bool is_empty();
        cv::Mat* get_mat();
    };

    static void imwrite(const char* filename, cv::Mat& frame);
    static void imshow(const char* winname, cv::Mat& frame);
    static int waitKey(int delay);
    static void destroyAllWindows();
};


#endif // OPENCV_CSHARP_HPP
