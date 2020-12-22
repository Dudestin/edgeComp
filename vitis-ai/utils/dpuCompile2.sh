#!/bin/sh

vai_c_tensorflow -f ./quantize_result/quantize_eval_model.pb -a /opt/vitis_ai/compiler/arch/DPUCZDX8G/ZCU102/arch.json -o ./compile_result
