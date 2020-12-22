#!/bin/sh

ARCH='arch.json'
NET_NAME='bisenetv2_agg'
FROZEN_MODEL='./quantize_result/AGG/deploy_model.pb'
OUTPUT_DIR='./compile_result'
vai_c_tensorflow \
	--frozen_pb ${FROZEN_MODEL} \
	--arch ${ARCH} \
	--output_dir ${OUTPUT_DIR} \
	--net_name ${NET_NAME}

NET_NAME='bisenetv2_sem'
FROZEN_MODEL='./quantize_result/SEM/deploy_model.pb'
vai_c_tensorflow \
	--frozen_pb ${FROZEN_MODEL} \
	--arch ${ARCH} \
	--output_dir ${OUTPUT_DIR} \
	--net_name ${NET_NAME}

NET_NAME='bisenetv2_det'
FROZEN_MODEL='./quantize_result/DET/deploy_model.pb'
vai_c_tensorflow \
	--frozen_pb ${FROZEN_MODEL} \
	--arch ${ARCH} \
	--output_dir ${OUTPUT_DIR} \
	--net_name ${NET_NAME}
