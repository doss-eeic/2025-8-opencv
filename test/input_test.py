from PIL import Image
import numpy as np
import cv2

IMAGE_PATH = "./img/mountain.jpg"

def input_test():
    input_image = cv2.imread(IMAGE_PATH)
    input_image = np.array(input_image)
    Image.fromarray(input_image).show()

if __name__ == "__main__":
    input_test()
