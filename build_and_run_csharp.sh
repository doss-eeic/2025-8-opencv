#!/bin/bash

# OpenCV C# テストのビルドと実行スクリプト
# 使用方法: ./build_and_run_csharp.sh

echo "============================================================"
echo "OpenCV C# テスト - ビルドと実行"
echo "============================================================"

# test/csharpディレクトリに移動
cd test/csharp

# ビルド
echo "🔨 C# プロジェクトをビルド中..."
dotnet build csharp.csproj

# ビルド結果をチェック
if [ $? -eq 0 ]; then
    echo "✅ ビルド成功！"
    echo ""
    echo "🖼️ プログラムを実行中..."
    echo "終了するにはESCキーまたは'q'キーを押してください"
    echo ""
    
    # ライブラリパスを設定して実行
    export DYLD_LIBRARY_PATH=.:./build/lib:$DYLD_LIBRARY_PATH
    dotnet run
else
    echo "❌ ビルドに失敗しました"
    exit 1
fi
