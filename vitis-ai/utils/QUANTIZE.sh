#!/bin/sh

vai_q_tensorflow quantize \
--input_frozen_graph frozen_graph.pb \
--input_nodes 'input_tensor' \
--input_shapes 1,512,1024,3 \
--output_nodes 'final_output' \
--input_fn my_input_fn.calib_input \
--calib_iter 1000
