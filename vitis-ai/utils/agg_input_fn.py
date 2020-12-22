import os
import glob
import numpy as np
import scipy.ndimage as ndimage

la = glob.glob('./dump_results/**/BiseNetV2_aggregation_branch_guided_aggregation_block_detail_branch_avg_pooling_block_aquant.txt', recursive=True)
lb = glob.glob('./dump_results/**/BiseNetV2_aggregation_branch_guided_aggregation_block_detail_branch_1x1_conv_block_Conv2D_aquant.txt', recursive=True)
lc = glob.glob('./dump_results/**/BiseNetV2_aggregation_branch_guided_aggregation_block_semantic_branch_3x3_conv_block_conv_Conv2D_aquant.txt', recursive=True)
ld = glob.glob('./dump_results/**/BiseNetV2_aggregation_branch_guided_aggregation_block_semantic_branch_1x1_conv_block_Conv2D_aquant.txt', recursive=True)

def sigmoid(x):
    return (1 / (1 + np.exp(-x))).astype(np.int32)

def zoom(x):
    hoge = ndimage.zoom(x, (4, 4, 1), order=1)
    return hoge



lB = []
for (a, b, c, d) in zip(la, lb, lc, ld):
    nA = np.fromfile(a, dtype=np.int8, sep='\n').reshape([1, 19, 31, 64])
    nB = np.fromfile(b, dtype=np.int8, sep='\n').reshape([1, 76, 121, 64])
    nC = np.fromfile(c, dtype=np.int8, sep='\n').reshape([1, 19, 31, 64])
    nD = np.fromfile(d, dtype=np.int8, sep='\n').reshape([1, 19, 31, 64])
    lB.append(nB)

def calib_input(iter):
    #return {"BiseNetV2/aggregation_branch/guided_aggregation_block/aggregation_features/aggregation_feature_output/conv/Conv2D" : lB[iter]}
    return {"input_tensor" : lB[iter]}
