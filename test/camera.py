import sys
import numpy as np
from PIL import Image
from matplotlib import pyplot as plt

# このpathは適宜変更して下さい
OPENCV_PATH = '/Users/junnamuzaurusu/Documents/3A/big_software/opencv/build/install/lib/python3.13/site-packages'
sys.path.append(OPENCV_PATH)
import cv2


def show_webcam():
    """Webカメラからの映像をPILで表示"""
    cap = cv2.VideoCapture(0)
    
    if not cap.isOpened():
        raise Exception("カメラを開けませんでした")
        return
    
    print("カメラが正常に開かれました")
    print("終了するには Ctrl+C を押してください")
    
    try:
        while True:
            ret, frame = cap.read()
            if not ret:
                print("フレームを読み取れませんでした")
                break
            
            # ToDo: これがなくても表示できるようにする
            # BGRからRGBに変換
            #frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)



            # PIL Image型へ変換
            pil_image = Image.fromarray(frame)

            # matplotlibで表示
            plt.clf()  # 前のフレームをクリア
            plt.imshow(pil_image)
            plt.pause(0.03)  # 約30FPS
            
    except KeyboardInterrupt:
        print("\nユーザーによって終了されました")
    
    cap.release()
    plt.close()

if __name__ == "__main__":
    show_webcam()