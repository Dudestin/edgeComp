import pprint
import time
import numpy as np
import os

path = "./seg_train_images"

def preprocess_image(src_image, input_tensor_size):
    output_image = src_image[:, :, (2, 1, 0)]
    output_image = cv2.resize(
        output_image,
        dsize=(input_tensor_size[0], input_tensor_size[1]),
        interpolation=cv2.INTER_LINEAR
    )
    output_image = output_image.astype('float32') / 255.0
    img_mean = np.array(MEAN_VALUE).reshape((1, 1, len(MEAN_VALUE)))
    img_std  = np.array(STD_VALUE).reshape((1, 1, len(STD_VALUE)))
    output_image -= img_mean
    output_image /= img_std
    return output_image


def calib_input(iter):
    input_tensor_size = [1936,1216]
    input_tensor_size = [int(tmp/2) for tmp in input_tensor_size]
    files = os.listdir(path)
    file = [f for f in files if os.path.isfile(os.path.join(path, f))]
    image_path = path + '/' + file[iter]
    print(image_path)
    src_image = cv2.imread(image_path, cv2.IMREAD_COLOR)
    pre_img   = preprocess_image(src_image, input_tensor_size)
    print(pre_img.shape)
    return  {'input_tensor': pre_img[np.newaxis, :, :, :]}

