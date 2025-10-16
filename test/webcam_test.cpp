#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

int main() {
    std::cout << "============================================================" << std::endl;
    std::cout << "ビルドしたOpenCVを使用するWebカメラテスト" << std::endl;
    std::cout << "============================================================" << std::endl;
    
    // OpenCVバージョンの確認
    std::cout << "OpenCV バージョン: " << CV_VERSION << std::endl;
    //std::cout << "OpenCV ビルド情報:" << std::endl;
    //std::cout << cv::getBuildInformation() << std::endl;
    
    // カメラを初期化
    cv::VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        std::cout << "❌ カメラを開けませんでした" << std::endl;
        return 1;
    }
    
    std::cout << "✅ カメラが正常に開かれました" << std::endl;
    
    // カメラの設定
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 30);
    
    // 実際の設定値を確認
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = cap.get(cv::CAP_PROP_FPS);
    
    std::cout << "カメラ設定:" << std::endl;
    std::cout << "  解像度: " << width << "x" << height << std::endl;
    std::cout << "  FPS: " << fps << std::endl;
    
    cv::Mat frame;
    int frame_count = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::cout << "\nカメラから画像を取得中..." << std::endl;
    std::cout << "終了するには 'q' キーを押してください" << std::endl;
    
    while (true) {
        // フレームを読み取り
        cap >> frame;
        
        if (frame.empty()) {
            std::cout << "フレームを読み取れませんでした" << std::endl;
            break;
        }
        
        frame_count++;
        
        // フレームに情報を描画
        cv::putText(frame, "Frame: " + std::to_string(frame_count), 
                   cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
        cv::putText(frame, "FPS: " + std::to_string(static_cast<int>(fps)), 
                   cv::Point(10, 70), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
        cv::putText(frame, "OpenCV: " + std::string(CV_VERSION), 
                   cv::Point(10, 110), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 0), 2);
        cv::putText(frame, "Press 'q' to quit", 
                   cv::Point(10, height - 20), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
        
        // フレームを表示
        cv::imshow("Built OpenCV Webcam Test", frame);
        
        
        // 'q'キーが押されたら終了
        if ((cv::waitKey(1) & 0xFF) == 'q') {
            std::cout << "ユーザーによって終了されました" << std::endl;
            break;
        }
    }
    
    // 統計情報を表示
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    double actual_fps = frame_count / (elapsed_time.count() / 1000.0);
    
    std::cout << "✅ Webカメラテストが正常に完了しました" << std::endl;
    
    // リソースを解放
    cap.release();
    cv::destroyAllWindows();
    
    return 0;
}
