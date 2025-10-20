from PIL import Image
import numpy as np
import cv2

IMAGE_PATH = "./img/mountain.jpg"

def output_test():
    input_image = Image.open(IMAGE_PATH)
    cv2.imshow("Image", np.array(input_image))
    cv2.waitKey(0)  # キー入力待ち
    cv2.destroyAllWindows()  # ウィンドウを閉じる

if __name__ == "__main__":
    output_test()