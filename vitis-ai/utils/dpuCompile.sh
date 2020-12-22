#!/bin/sh

ARCH='arch.json'
FROZEN_MODEL='./quantize_result/deploy_model.pb'
OUTPUT_DIR='./compile_result'

vai_c_tensorflow \
	--frozen_pb ${FROZEN_MODEL} \
	--arch ${ARCH} \
	--output_dir ${OUTPUT_DIR}
