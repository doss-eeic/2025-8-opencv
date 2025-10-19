from PIL import Image
import cv2
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.patches import Rectangle



cap = cv2.VideoCapture(0)
if not cap.isOpened():
    raise Exception("カメラを開けませんでした")

print("カメラが正常に開かれました")
print("終了するにはウィンドウを閉じるか、Ctrl+Cを押してください")

# matplotlibの設定
fig, ax = plt.subplots(figsize=(10, 8))
ax.set_title("リアルタイムカメラ映像", fontsize=16)
ax.axis('off')

# 初期フレームを取得
ret, frame = cap.read()
if not ret:
    raise Exception("初期フレームを読み取れませんでした")

im = ax.imshow(frame)

frame_count = 0

def animate(frame_num):
    global frame_count
    ret, frame = cap.read()
    if not ret:
        return im
    
    frame_count += 1
    
    # BGRからRGBに変換
    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    
    # 画像を更新
    im.set_array(frame_rgb)
    
    # フレームカウントを表示
    ax.set_title(f"リアルタイムカメラ映像 - フレーム: {frame_count}", fontsize=16)
    
    return im

try:
    # アニメーションを開始（30fps）
    ani = animation.FuncAnimation(fig, animate, interval=33, blit=False, cache_frame_data=False)
    plt.show()
    
except KeyboardInterrupt:
    print("\nCtrl+Cが押されたため終了します")

except Exception as e:
    print(f"エラーが発生しました: {e}")

finally:
    # リソースを解放
    cap.release()
    cv2.destroyAllWindows()
    plt.close('all')
    print("リソースを解放しました")