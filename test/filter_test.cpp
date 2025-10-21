#include <opencv2/opencv.hpp>
#include <iostream>
#include <SDL.h>
#include <unistd.h>

void display_image_by_sdl(cv::Mat image, SDL_Window* window, SDL_Renderer* renderer) {
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        image.data,
        image.cols, image.rows,
        24, // ビット深度
        image.step, // ピッチ
        0x000000FF, 0x0000FF00, 0x00FF0000, 0x00000000 
    );
    if (!surface) {
        std::cerr << " Surfaceの作成に失敗しました: " << SDL_GetError() << std::endl;
        return;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << " テクスチャの作成に失敗しました: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }
    
    // フレームを表示
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    
    // リソースを解放
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}


int main() {
    std::cout << "Webカメラフィルタテストを開始します" << std::endl;
    std::cout << "終了するにはESCキーを押してください" << std::endl;
    
    // SDLを初期化
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDLの初期化に失敗しました: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << " カメラを開けませんでした" << std::endl;
        cap.release();
        SDL_Quit();
        return -1;
    }
    
    std::cout << "カメラが正常に開かれました" << std::endl;
    
    // カメラのウォームアップ期間
    std::cout << "カメラのウォームアップ中..." << std::endl;
    usleep(2000000); // 2秒待機

    // 最初のフレームを取得してウィンドウサイズを決定
    cv::Mat first_frame;
    std::cout << "最初のフレームを取得中..." << std::endl;
    
    // 最初のフレーム取得を複数回試行
    int retry_count = 0;
    const int max_retries = 10;
    
    while (retry_count < max_retries) {
        cap >> first_frame;
        if (!first_frame.empty()) {
            std::cout << "最初のフレームを正常に取得しました" << std::endl;
            break;
        }
        std::cout << "フレーム取得を再試行中... (" << (retry_count + 1) << "/" << max_retries << ")" << std::endl;
        retry_count++;
        usleep(500000); // 500ms待機
    }
    
    if (first_frame.empty()) {
        std::cerr << "最初のフレームを読み込めませんでした" << std::endl;
        cap.release();
        SDL_Quit();
        return -1;
    }
    
    // 最初のフレーム取得成功後、バッファーサイズを最小に制限
    cap.set(cv::CAP_PROP_BUFFERSIZE, 1);
    
    // フレームレートも制限してバッファーオーバーフローを防ぐ
    cap.set(cv::CAP_PROP_FPS, 10);
    
    // 表示用画像を作成
    cv::Mat display_image;
    display_image = first_frame;
    
    // 画像サイズを調整（最大800x600にリサイズ）
    cv::Mat resized_image;
    double scale = std::min(800.0 / display_image.cols, 600.0 / display_image.rows);
    int new_width = static_cast<int>(display_image.cols * scale);
    int new_height = static_cast<int>(display_image.rows * scale);
    cv::resize(display_image, resized_image, cv::Size(new_width, new_height));
    
    // SDLウィンドウを作成（一度だけ）
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Video Preview",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        resized_image.cols, resized_image.rows,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "ウィンドウの作成に失敗しました: " << SDL_GetError() << std::endl;
        cap.release();
        SDL_Quit();
        return -1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "レンダラーの作成に失敗しました: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        cap.release();
        SDL_Quit();
        return -1;
    }
    
    std::cout << "ウィンドウが作成されました。動画を表示中..." << std::endl;

    cv::Mat frame;
    int frame_count = 0;
    
    while (true) {
        // バッファーを完全にクリアして最新のフレームを取得
        cv::Mat temp_frame;
        // バッファーをクリアするために複数回フレームを読み取り
        for (int i = 0; i < 5; i++) {
            cap >> temp_frame;
        }
        
        // 最新のフレームを取得
        cap >> frame;
        
        if (frame.empty()) {
            std::cerr << "フレームを読み込めませんでした。カメラの接続を確認してください。" << std::endl;
            std::cout << "カメラの再接続を試行中..." << std::endl;
            
            // カメラを再初期化
            cap.release();
            cap.open(0);
            
            if (!cap.isOpened()) {
                std::cerr << "カメラの再接続に失敗しました。" << std::endl;
                break;
            }
            
            // バッファーサイズを再設定
            cap.set(cv::CAP_PROP_BUFFERSIZE, 1);
            
            std::cout << "カメラが再接続されました。フレーム取得を再開します。" << std::endl;
            continue;
        }
        
        frame_count++;
        if (frame_count % 30 == 0) { // 30フレームごとに進捗を表示
            std::cout << "フレーム " << frame_count << " を処理中..." << std::endl;
        }
        
        display_image = frame;
        // 画像サイズを調整（同じスケールでリサイズ）
        cv::Mat resized_image;
        cv::resize(display_image, resized_image, cv::Size(new_width, new_height));

        // SDLで動画表示
        display_image_by_sdl(resized_image, window, renderer);
        
        // キーボード入力をチェック（ESCキーで終了）
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                std::cout << "ESCキーが押されました。終了します。" << std::endl;
                break;
            }
        }
        
        SDL_Delay(100); // 約10FPS（バッファーオーバーフローを防ぐため遅めに設定）
    }

    // リソースを解放
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    cv::destroyAllWindows();
    cap.release();
    std::cout << "プログラムが終了しました" << std::endl;
    return 0;
}