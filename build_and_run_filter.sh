#!/bin/bash

# OpenCV フィルタテストのコンパイルと実行スクリプト
# 使用方法: ./build_and_run_filter.sh

echo "============================================================"
echo "OpenCV フィルタテスト - コンパイルと実行"
echo "============================================================"

# コンパイル
echo "🔨 コンパイル中..."
g++ -std=c++17 \
    -I./build/install/include/opencv4 \
    $(pkg-config --cflags sdl2) \
    -L./build/lib \
    $(pkg-config --libs sdl2) \
    ./test/filter_test.cpp \
    -lopencv_core \
    -lopencv_imgproc \
    -lopencv_imgcodecs \
    -lopencv_videoio \
    -lopencv_highgui \
    -o ./test/filter_test

# コンパイル結果をチェック
if [ $? -eq 0 ]; then
    echo "✅ コンパイル成功！"
    echo ""
    echo "🖼️ プログラムを実行中..."
    echo "終了するには任意のキーを押してください"
    echo ""
    
    # ライブラリパスを設定して実行
    export DYLD_LIBRARY_PATH=./build/lib:$DYLD_LIBRARY_PATH
    ./test/filter_test
else
    echo "❌ コンパイルに失敗しました"
    exit 1
fi
