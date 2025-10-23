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

#ifndef OPENCV_CSHARP_CPP
#define OPENCV_CSHARP_CPP

# include "csharp.hpp"
# include <iostream>
# include <opencv2/opencv.hpp>
# include <opencv2/videoio.hpp>
# include <opencv2/highgui.hpp>
# include <opencv2/imgproc.hpp>
# include <opencv2/imgcodecs.hpp>

// C-style function implementations for C# interop
extern "C" {    
    void* cvsharp_videocapture_create(int device) {
        cv::VideoCapture* cap = new cv::VideoCapture(device);
        return static_cast<void*>(cap);
    }
    
    bool cvsharp_videocapture_isopened(void* cap) {
        if (!cap) return false;
        cv::VideoCapture* capture = static_cast<cv::VideoCapture*>(cap);
        return capture->isOpened();
    }
    
    bool cvsharp_videocapture_read(void* cap, void* frame) {
        if (!cap || !frame) return false;
        cv::VideoCapture* capture = static_cast<cv::VideoCapture*>(cap);
        cv::Mat* mat = static_cast<cv::Mat*>(frame);
        return capture->read(*mat);
    }
    
    void cvsharp_videocapture_release(void* cap) {
        if (cap) {
            cv::VideoCapture* capture = static_cast<cv::VideoCapture*>(cap);
            capture->release();
            delete capture;
        }
    }
    
    void* cvsharp_mat_create() {
        cv::Mat* mat = new cv::Mat();
        return static_cast<void*>(mat);
    }
    
    void* cvsharp_mat_create_with_params(int rows, int cols, int type) {
        cv::Mat* mat = new cv::Mat(rows, cols, type);
        return static_cast<void*>(mat);
    }
    
    int cvsharp_mat_get_rows(void* mat) {
        if (!mat) return 0;
        cv::Mat* m = static_cast<cv::Mat*>(mat);
        return m->rows;
    }
    
    int cvsharp_mat_get_cols(void* mat) {
        if (!mat) return 0;
        cv::Mat* m = static_cast<cv::Mat*>(mat);
        return m->cols;
    }
    
    int cvsharp_mat_get_type(void* mat) {
        if (!mat) return 0;
        cv::Mat* m = static_cast<cv::Mat*>(mat);
        return m->type();
    }
    
    bool cvsharp_mat_is_empty(void* mat) {
        if (!mat) return true;
        cv::Mat* m = static_cast<cv::Mat*>(mat);
        return m->empty();
    }
    
    void cvsharp_mat_release(void* mat) {
        if (mat) {
            cv::Mat* m = static_cast<cv::Mat*>(mat);
            delete m;
        }
    }
    
    bool cvsharp_imwrite(const char* filename, void* frame) {
        if (!frame) return false;
        cv::Mat* mat = static_cast<cv::Mat*>(frame);
        return cv::imwrite(filename, *mat);
    }
    
    void cvsharp_imshow(const char* winname, void* frame) {
        if (!frame) return;
        cv::Mat* mat = static_cast<cv::Mat*>(frame);
        cv::namedWindow(winname, cv::WINDOW_NORMAL);
        cv::resizeWindow(winname, 800, 450);
        cv::moveWindow(winname, 100, 100);
        cv::imshow(winname, *mat);
    }
    
    int cvsharp_waitkey(int delay) {
        return cv::waitKey(delay);
    }
    
    void cvsharp_destroyallwindows() {
        cv::destroyAllWindows();
    }
}

// Class implementations
cvsharp::VideoCapture::VideoCapture(int device) {
    m_cap = new cv::VideoCapture(device);
}

cvsharp::VideoCapture::~VideoCapture() {
    if (m_cap) {
        m_cap->release();
        delete m_cap;
    }
}

bool cvsharp::VideoCapture::isOpened() {
    return m_cap ? m_cap->isOpened() : false;
}

bool cvsharp::VideoCapture::read(cv::Mat& frame) {
    return m_cap ? m_cap->read(frame) : false;
}

void cvsharp::VideoCapture::release() {
    if (m_cap) {
        m_cap->release();
    }
}

cvsharp::Mat::Mat() {
    m_mat = new cv::Mat();
}

cvsharp::Mat::Mat(int rows, int cols, int type) {
    m_mat = new cv::Mat(rows, cols, type);
}

cvsharp::Mat::~Mat() {
    if (m_mat) {
        delete m_mat;
    }
}

int cvsharp::Mat::get_rows() {
    return m_mat ? m_mat->rows : 0;
}

int cvsharp::Mat::get_cols() {
    return m_mat ? m_mat->cols : 0;
}

int cvsharp::Mat::get_type() {
    return m_mat ? m_mat->type() : 0;
}

bool cvsharp::Mat::is_empty() {
    return m_mat ? m_mat->empty() : true;
}

cv::Mat* cvsharp::Mat::get_mat() {
    return m_mat;
}

void cvsharp::imwrite(const char* filename, cv::Mat& frame) {
    cv::imwrite(filename, frame);
}

void cvsharp::imshow(const char* winname, cv::Mat& frame) {
    cv::imshow(winname, frame);
}

int cvsharp::waitKey(int delay) {
    return cv::waitKey(delay);
}

void cvsharp::destroyAllWindows() {
    cv::destroyAllWindows();
}

#endif // OPENCV_CSHARP_CPP

