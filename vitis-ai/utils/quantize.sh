#!/bin/sh
output_dir='./quantize_result'
INPUT_NODE='input_tensor'
INPUT_NODE='BiseNetV2/aggregation_branch/guided_aggregation_block/aggregation_features/fused_features'
INPUT_SHAPE='1,76,121,64'
#INPUT_SHAPE='1,968,608,3'
OUTPUT_NODE='BiseNetV2/logits/1x1_conv_block/Conv2D'

vai_q_tensorflow quantize \
        --input_frozen_graph './bisenetv2_segcomp_optimized.pb' \
        --input_fn 'my_input_fn.calib_input' \
        --input_nodes ${INPUT_NODE} \
        --output_nodes ${OUTPUT_NODE} \
        --input_shapes ${INPUT_SHAPE} \
        --output_dir ${output_dir} \
	--calib_iter 10
