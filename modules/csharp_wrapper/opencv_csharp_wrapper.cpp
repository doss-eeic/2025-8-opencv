#include "opencv_csharp_wrapper.h"
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

// VideoCapture wrapper implementation
VideoCaptureHandle opencv_videocapture_create(int device) {
    try {
        cv::VideoCapture* cap = new cv::VideoCapture(device);
        return static_cast<VideoCaptureHandle>(cap);
    } catch (const std::exception& e) {
        std::cerr << "Error creating VideoCapture: " << e.what() << std::endl;
        return nullptr;
    }
}

int opencv_videocapture_isOpened(VideoCaptureHandle handle) {
    if (!handle) return 0;
    try {
        cv::VideoCapture* cap = static_cast<cv::VideoCapture*>(handle);
        return cap->isOpened() ? 1 : 0;
    } catch (const std::exception& e) {
        std::cerr << "Error checking VideoCapture: " << e.what() << std::endl;
        return 0;
    }
}

int opencv_videocapture_read(VideoCaptureHandle handle, unsigned char* data, int width, int height) {
    if (!handle || !data) return 0;
    try {
        cv::VideoCapture* cap = static_cast<cv::VideoCapture*>(handle);
        cv::Mat frame;
        if (cap->read(frame)) {
            if (frame.empty()) return 0;
            
            // Resize frame if necessary
            if (frame.cols != width || frame.rows != height) {
                cv::Mat resized;
                cv::resize(frame, resized, cv::Size(width, height));
                frame = resized;
            }
            
            // Convert BGR to RGB for C# compatibility
            cv::Mat rgb_frame;
            cv::cvtColor(frame, rgb_frame, cv::COLOR_BGR2RGB);
            
            // Copy data to provided buffer
            memcpy(data, rgb_frame.data, width * height * 3);
            return 1;
        }
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error reading VideoCapture: " << e.what() << std::endl;
        return 0;
    }
}

void opencv_videocapture_release(VideoCaptureHandle handle) {
    if (handle) {
        try {
            cv::VideoCapture* cap = static_cast<cv::VideoCapture*>(handle);
            cap->release();
            delete cap;
        } catch (const std::exception& e) {
            std::cerr << "Error releasing VideoCapture: " << e.what() << std::endl;
        }
    }
}

// Mat wrapper implementation
MatHandle opencv_mat_create(int rows, int cols, int type) {
    try {
        cv::Mat* mat = new cv::Mat(rows, cols, type);
        return static_cast<MatHandle>(mat);
    } catch (const std::exception& e) {
        std::cerr << "Error creating Mat: " << e.what() << std::endl;
        return nullptr;
    }
}

unsigned char* opencv_mat_data(MatHandle handle) {
    if (!handle) return nullptr;
    try {
        cv::Mat* mat = static_cast<cv::Mat*>(handle);
        return mat->data;
    } catch (const std::exception& e) {
        std::cerr << "Error getting Mat data: " << e.what() << std::endl;
        return nullptr;
    }
}

int opencv_mat_rows(MatHandle handle) {
    if (!handle) return 0;
    try {
        cv::Mat* mat = static_cast<cv::Mat*>(handle);
        return mat->rows;
    } catch (const std::exception& e) {
        std::cerr << "Error getting Mat rows: " << e.what() << std::endl;
        return 0;
    }
}

int opencv_mat_cols(MatHandle handle) {
    if (!handle) return 0;
    try {
        cv::Mat* mat = static_cast<cv::Mat*>(handle);
        return mat->cols;
    } catch (const std::exception& e) {
        std::cerr << "Error getting Mat cols: " << e.what() << std::endl;
        return 0;
    }
}

int opencv_mat_type(MatHandle handle) {
    if (!handle) return 0;
    try {
        cv::Mat* mat = static_cast<cv::Mat*>(handle);
        return mat->type();
    } catch (const std::exception& e) {
        std::cerr << "Error getting Mat type: " << e.what() << std::endl;
        return 0;
    }
}

int opencv_mat_empty(MatHandle handle) {
    if (!handle) return 1;
    try {
        cv::Mat* mat = static_cast<cv::Mat*>(handle);
        return mat->empty() ? 1 : 0;
    } catch (const std::exception& e) {
        std::cerr << "Error checking Mat empty: " << e.what() << std::endl;
        return 1;
    }
}

void opencv_mat_release(MatHandle handle) {
    if (handle) {
        try {
            cv::Mat* mat = static_cast<cv::Mat*>(handle);
            delete mat;
        } catch (const std::exception& e) {
            std::cerr << "Error releasing Mat: " << e.what() << std::endl;
        }
    }
}

// High-level GUI functions
int opencv_imshow(const char* winname, MatHandle mat) {
    if (!winname || !mat) return 0;
    try {
        cv::Mat* cv_mat = static_cast<cv::Mat*>(mat);
        cv::imshow(winname, *cv_mat);
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error showing image: " << e.what() << std::endl;
        return 0;
    }
}

int opencv_waitKey(int delay) {
    try {
        return cv::waitKey(delay);
    } catch (const std::exception& e) {
        std::cerr << "Error waiting for key: " << e.what() << std::endl;
        return -1;
    }
}

void opencv_destroyAllWindows() {
    try {
        cv::destroyAllWindows();
    } catch (const std::exception& e) {
        std::cerr << "Error destroying windows: " << e.what() << std::endl;
    }
}

// Utility functions
void opencv_initialize() {
    // Initialize OpenCV if needed
    // This function can be used for any initialization
}

void opencv_cleanup() {
    // Cleanup OpenCV resources if needed
    cv::destroyAllWindows();
}

// Simple camera functions for C# integration
int opencv_camera_read_and_show(VideoCaptureHandle handle, const char* winname) {
    if (!handle) return 0;
    try {
        cv::VideoCapture* cap = static_cast<cv::VideoCapture*>(handle);
        cv::Mat frame;
        if (cap->read(frame)) {
            if (!frame.empty()) {
                cv::imshow(winname, frame);
                return 1;
            }
        }
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error in camera_read_and_show: " << e.what() << std::endl;
        return 0;
    }
}

int opencv_camera_simple_test(int device, const char* winname) {
    try {
        cv::VideoCapture cap(device);
        if (!cap.isOpened()) {
            std::cerr << "Cannot open camera device " << device << std::endl;
            return 0;
        }
        
        cv::Mat frame;
        int frame_count = 0;
        
        while (true) {
            if (!cap.read(frame) || frame.empty()) {
                std::cerr << "Cannot read frame" << std::endl;
                break;
            }
            
            frame_count++;
            cv::imshow(winname, frame);
            
            int key = cv::waitKey(1);
            if (key == 27 || key == 'q') { // ESC or 'q' key
                break;
            }
            
            // Print frame count every 100 frames
            if (frame_count % 100 == 0) {
                std::cout << "Frame count: " << frame_count << std::endl;
            }
        }
        
        cap.release();
        cv::destroyAllWindows();
        std::cout << "Camera test completed. Total frames: " << frame_count << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error in camera_simple_test: " << e.what() << std::endl;
        return 0;
    }
}

