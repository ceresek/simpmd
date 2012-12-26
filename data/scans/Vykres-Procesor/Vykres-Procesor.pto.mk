
# makefile for panorama stitching, created by hugin using the new makefilelib

# Tool configuration
NONA=nona
PTSTITCHER=PTStitcher
PTMENDER=PTmender
PTBLENDER=PTblender
PTMASKER=PTmasker
PTROLLER=PTroller
ENBLEND=enblend
ENFUSE=enfuse
SMARTBLEND=smartblend.exe
HDRMERGE=hugin_hdrmerge
RM=rm
EXIFTOOL=exiftool

# Project parameters
HUGIN_PROJECTION=0
HUGIN_HFOV=29
HUGIN_WIDTH=26670
HUGIN_HEIGHT=27632

# options for the programs
NONA_LDR_REMAPPED_COMP=
NONA_OPTS=
ENBLEND_OPTS= -f20870x26971+661+0
ENBLEND_LDR_COMP=
ENBLEND_EXPOSURE_COMP=
ENBLEND_HDR_COMP=
HDRMERGE_OPTS=-m avg -c
ENFUSE_OPTS=
EXIFTOOL_COPY_ARGS=-ImageDescription -Make -Model -Artist -WhitePoint -Copyright -GPS:all -DateTimeOriginal -CreateDate -UserComment -ColorSpace -OwnerName -SerialNumber
EXIFTOOL_INFO_ARGS='-Software=Hugin 2011.4.0.cf9be9344356' '-UserComment<$${UserComment}&\#xa;Projection: Rectilinear (0)&\#xa;FOV: 29 x 30&\#xa;Ev: 0.00' -f

# the output panorama
LDR_REMAPPED_PREFIX=Vykres-Procesor
LDR_REMAPPED_PREFIX_SHELL=Vykres-Procesor
HDR_STACK_REMAPPED_PREFIX=Vykres-Procesor_hdr_
HDR_STACK_REMAPPED_PREFIX_SHELL=Vykres-Procesor_hdr_
LDR_EXPOSURE_REMAPPED_PREFIX=Vykres-Procesor_exposure_layers_
LDR_EXPOSURE_REMAPPED_PREFIX_SHELL=Vykres-Procesor_exposure_layers_
PROJECT_FILE=/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Vykres-Procesor.pto
PROJECT_FILE_SHELL=/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Vykres-Procesor.pto
LDR_BLENDED=Vykres-Procesor.png
LDR_BLENDED_SHELL=Vykres-Procesor.png
LDR_STACKED_BLENDED=Vykres-Procesor_fused.png
LDR_STACKED_BLENDED_SHELL=Vykres-Procesor_fused.png
LDR_EXPOSURE_LAYERS_FUSED=Vykres-Procesor_blended_fused.png
LDR_EXPOSURE_LAYERS_FUSED_SHELL=Vykres-Procesor_blended_fused.png
HDR_BLENDED=Vykres-Procesor_hdr.exr
HDR_BLENDED_SHELL=Vykres-Procesor_hdr.exr

# first input image
INPUT_IMAGE_1=/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-1.jpg
INPUT_IMAGE_1_SHELL=/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-1.jpg

# all input images
INPUT_IMAGES=/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-1.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-2.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-3.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-4.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-5.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-6.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-7.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-8.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-9.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-0.jpg
INPUT_IMAGES_SHELL=/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-1.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-2.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-3.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-4.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-5.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-6.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-7.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-8.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-9.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-0.jpg

# remapped images
LDR_LAYERS=Vykres-Procesor0000.tif\
Vykres-Procesor0001.tif\
Vykres-Procesor0002.tif\
Vykres-Procesor0003.tif\
Vykres-Procesor0004.tif\
Vykres-Procesor0005.tif\
Vykres-Procesor0006.tif\
Vykres-Procesor0007.tif\
Vykres-Procesor0008.tif\
Vykres-Procesor0009.tif
LDR_LAYERS_SHELL=Vykres-Procesor0000.tif\
Vykres-Procesor0001.tif\
Vykres-Procesor0002.tif\
Vykres-Procesor0003.tif\
Vykres-Procesor0004.tif\
Vykres-Procesor0005.tif\
Vykres-Procesor0006.tif\
Vykres-Procesor0007.tif\
Vykres-Procesor0008.tif\
Vykres-Procesor0009.tif

# remapped images (hdr)
HDR_LAYERS=Vykres-Procesor_hdr_0000.exr\
Vykres-Procesor_hdr_0001.exr\
Vykres-Procesor_hdr_0002.exr\
Vykres-Procesor_hdr_0003.exr\
Vykres-Procesor_hdr_0004.exr\
Vykres-Procesor_hdr_0005.exr\
Vykres-Procesor_hdr_0006.exr\
Vykres-Procesor_hdr_0007.exr\
Vykres-Procesor_hdr_0008.exr\
Vykres-Procesor_hdr_0009.exr
HDR_LAYERS_SHELL=Vykres-Procesor_hdr_0000.exr\
Vykres-Procesor_hdr_0001.exr\
Vykres-Procesor_hdr_0002.exr\
Vykres-Procesor_hdr_0003.exr\
Vykres-Procesor_hdr_0004.exr\
Vykres-Procesor_hdr_0005.exr\
Vykres-Procesor_hdr_0006.exr\
Vykres-Procesor_hdr_0007.exr\
Vykres-Procesor_hdr_0008.exr\
Vykres-Procesor_hdr_0009.exr

# remapped maxval images
HDR_LAYERS_WEIGHTS=Vykres-Procesor_hdr_0000_gray.pgm\
Vykres-Procesor_hdr_0001_gray.pgm\
Vykres-Procesor_hdr_0002_gray.pgm\
Vykres-Procesor_hdr_0003_gray.pgm\
Vykres-Procesor_hdr_0004_gray.pgm\
Vykres-Procesor_hdr_0005_gray.pgm\
Vykres-Procesor_hdr_0006_gray.pgm\
Vykres-Procesor_hdr_0007_gray.pgm\
Vykres-Procesor_hdr_0008_gray.pgm\
Vykres-Procesor_hdr_0009_gray.pgm
HDR_LAYERS_WEIGHTS_SHELL=Vykres-Procesor_hdr_0000_gray.pgm\
Vykres-Procesor_hdr_0001_gray.pgm\
Vykres-Procesor_hdr_0002_gray.pgm\
Vykres-Procesor_hdr_0003_gray.pgm\
Vykres-Procesor_hdr_0004_gray.pgm\
Vykres-Procesor_hdr_0005_gray.pgm\
Vykres-Procesor_hdr_0006_gray.pgm\
Vykres-Procesor_hdr_0007_gray.pgm\
Vykres-Procesor_hdr_0008_gray.pgm\
Vykres-Procesor_hdr_0009_gray.pgm

# stacked hdr images
HDR_STACK_0=Vykres-Procesor_stack_hdr_0000.exr
HDR_STACK_0_SHELL=Vykres-Procesor_stack_hdr_0000.exr
HDR_STACK_0_INPUT=Vykres-Procesor_hdr_0000.exr
HDR_STACK_0_INPUT_SHELL=Vykres-Procesor_hdr_0000.exr
HDR_STACK_1=Vykres-Procesor_stack_hdr_0001.exr
HDR_STACK_1_SHELL=Vykres-Procesor_stack_hdr_0001.exr
HDR_STACK_1_INPUT=Vykres-Procesor_hdr_0001.exr
HDR_STACK_1_INPUT_SHELL=Vykres-Procesor_hdr_0001.exr
HDR_STACK_2=Vykres-Procesor_stack_hdr_0002.exr
HDR_STACK_2_SHELL=Vykres-Procesor_stack_hdr_0002.exr
HDR_STACK_2_INPUT=Vykres-Procesor_hdr_0002.exr
HDR_STACK_2_INPUT_SHELL=Vykres-Procesor_hdr_0002.exr
HDR_STACK_3=Vykres-Procesor_stack_hdr_0003.exr
HDR_STACK_3_SHELL=Vykres-Procesor_stack_hdr_0003.exr
HDR_STACK_3_INPUT=Vykres-Procesor_hdr_0003.exr
HDR_STACK_3_INPUT_SHELL=Vykres-Procesor_hdr_0003.exr
HDR_STACK_4=Vykres-Procesor_stack_hdr_0004.exr
HDR_STACK_4_SHELL=Vykres-Procesor_stack_hdr_0004.exr
HDR_STACK_4_INPUT=Vykres-Procesor_hdr_0004.exr
HDR_STACK_4_INPUT_SHELL=Vykres-Procesor_hdr_0004.exr
HDR_STACK_5=Vykres-Procesor_stack_hdr_0005.exr
HDR_STACK_5_SHELL=Vykres-Procesor_stack_hdr_0005.exr
HDR_STACK_5_INPUT=Vykres-Procesor_hdr_0005.exr
HDR_STACK_5_INPUT_SHELL=Vykres-Procesor_hdr_0005.exr
HDR_STACK_6=Vykres-Procesor_stack_hdr_0006.exr
HDR_STACK_6_SHELL=Vykres-Procesor_stack_hdr_0006.exr
HDR_STACK_6_INPUT=Vykres-Procesor_hdr_0006.exr
HDR_STACK_6_INPUT_SHELL=Vykres-Procesor_hdr_0006.exr
HDR_STACK_7=Vykres-Procesor_stack_hdr_0007.exr
HDR_STACK_7_SHELL=Vykres-Procesor_stack_hdr_0007.exr
HDR_STACK_7_INPUT=Vykres-Procesor_hdr_0007.exr
HDR_STACK_7_INPUT_SHELL=Vykres-Procesor_hdr_0007.exr
HDR_STACK_8=Vykres-Procesor_stack_hdr_0008.exr
HDR_STACK_8_SHELL=Vykres-Procesor_stack_hdr_0008.exr
HDR_STACK_8_INPUT=Vykres-Procesor_hdr_0008.exr
HDR_STACK_8_INPUT_SHELL=Vykres-Procesor_hdr_0008.exr
HDR_STACK_9=Vykres-Procesor_stack_hdr_0009.exr
HDR_STACK_9_SHELL=Vykres-Procesor_stack_hdr_0009.exr
HDR_STACK_9_INPUT=Vykres-Procesor_hdr_0009.exr
HDR_STACK_9_INPUT_SHELL=Vykres-Procesor_hdr_0009.exr
HDR_STACKS_NUMBERS=0 1 2 3 4 5 6 7 8 9 
HDR_STACKS=$(HDR_STACK_0) $(HDR_STACK_1) $(HDR_STACK_2) $(HDR_STACK_3) $(HDR_STACK_4) $(HDR_STACK_5) $(HDR_STACK_6) $(HDR_STACK_7) $(HDR_STACK_8) $(HDR_STACK_9) 
HDR_STACKS_SHELL=$(HDR_STACK_0_SHELL) $(HDR_STACK_1_SHELL) $(HDR_STACK_2_SHELL) $(HDR_STACK_3_SHELL) $(HDR_STACK_4_SHELL) $(HDR_STACK_5_SHELL) $(HDR_STACK_6_SHELL) $(HDR_STACK_7_SHELL) $(HDR_STACK_8_SHELL) $(HDR_STACK_9_SHELL) 

# number of image sets with similar exposure
LDR_EXPOSURE_LAYER_0=Vykres-Procesor_exposure_0000.tif
LDR_EXPOSURE_LAYER_0_SHELL=Vykres-Procesor_exposure_0000.tif
LDR_EXPOSURE_LAYER_0_INPUT=Vykres-Procesor_exposure_layers_0000.tif\
Vykres-Procesor_exposure_layers_0001.tif\
Vykres-Procesor_exposure_layers_0002.tif\
Vykres-Procesor_exposure_layers_0003.tif\
Vykres-Procesor_exposure_layers_0004.tif\
Vykres-Procesor_exposure_layers_0005.tif\
Vykres-Procesor_exposure_layers_0006.tif\
Vykres-Procesor_exposure_layers_0007.tif\
Vykres-Procesor_exposure_layers_0008.tif\
Vykres-Procesor_exposure_layers_0009.tif
LDR_EXPOSURE_LAYER_0_INPUT_SHELL=Vykres-Procesor_exposure_layers_0000.tif\
Vykres-Procesor_exposure_layers_0001.tif\
Vykres-Procesor_exposure_layers_0002.tif\
Vykres-Procesor_exposure_layers_0003.tif\
Vykres-Procesor_exposure_layers_0004.tif\
Vykres-Procesor_exposure_layers_0005.tif\
Vykres-Procesor_exposure_layers_0006.tif\
Vykres-Procesor_exposure_layers_0007.tif\
Vykres-Procesor_exposure_layers_0008.tif\
Vykres-Procesor_exposure_layers_0009.tif
LDR_EXPOSURE_LAYER_0_INPUT_PTMENDER=Vykres-Procesor0000.tif\
Vykres-Procesor0001.tif\
Vykres-Procesor0002.tif\
Vykres-Procesor0003.tif\
Vykres-Procesor0004.tif\
Vykres-Procesor0005.tif\
Vykres-Procesor0006.tif\
Vykres-Procesor0007.tif\
Vykres-Procesor0008.tif\
Vykres-Procesor0009.tif
LDR_EXPOSURE_LAYER_0_INPUT_PTMENDER_SHELL=Vykres-Procesor0000.tif\
Vykres-Procesor0001.tif\
Vykres-Procesor0002.tif\
Vykres-Procesor0003.tif\
Vykres-Procesor0004.tif\
Vykres-Procesor0005.tif\
Vykres-Procesor0006.tif\
Vykres-Procesor0007.tif\
Vykres-Procesor0008.tif\
Vykres-Procesor0009.tif
LDR_EXPOSURE_LAYER_0_EXPOSURE=0
LDR_EXPOSURE_LAYERS_NUMBERS=0 
LDR_EXPOSURE_LAYERS=$(LDR_EXPOSURE_LAYER_0) 
LDR_EXPOSURE_LAYERS_SHELL=$(LDR_EXPOSURE_LAYER_0_SHELL) 
LDR_EXPOSURE_LAYERS_REMAPPED=Vykres-Procesor_exposure_layers_0000.tif\
Vykres-Procesor_exposure_layers_0001.tif\
Vykres-Procesor_exposure_layers_0002.tif\
Vykres-Procesor_exposure_layers_0003.tif\
Vykres-Procesor_exposure_layers_0004.tif\
Vykres-Procesor_exposure_layers_0005.tif\
Vykres-Procesor_exposure_layers_0006.tif\
Vykres-Procesor_exposure_layers_0007.tif\
Vykres-Procesor_exposure_layers_0008.tif\
Vykres-Procesor_exposure_layers_0009.tif
LDR_EXPOSURE_LAYERS_REMAPPED_SHELL=Vykres-Procesor_exposure_layers_0000.tif\
Vykres-Procesor_exposure_layers_0001.tif\
Vykres-Procesor_exposure_layers_0002.tif\
Vykres-Procesor_exposure_layers_0003.tif\
Vykres-Procesor_exposure_layers_0004.tif\
Vykres-Procesor_exposure_layers_0005.tif\
Vykres-Procesor_exposure_layers_0006.tif\
Vykres-Procesor_exposure_layers_0007.tif\
Vykres-Procesor_exposure_layers_0008.tif\
Vykres-Procesor_exposure_layers_0009.tif

# stacked ldr images
LDR_STACK_0=Vykres-Procesor_stack_ldr_0000.tif
LDR_STACK_0_SHELL=Vykres-Procesor_stack_ldr_0000.tif
LDR_STACK_0_INPUT=Vykres-Procesor_exposure_layers_0000.tif
LDR_STACK_0_INPUT_SHELL=Vykres-Procesor_exposure_layers_0000.tif
LDR_STACK_1=Vykres-Procesor_stack_ldr_0001.tif
LDR_STACK_1_SHELL=Vykres-Procesor_stack_ldr_0001.tif
LDR_STACK_1_INPUT=Vykres-Procesor_exposure_layers_0001.tif
LDR_STACK_1_INPUT_SHELL=Vykres-Procesor_exposure_layers_0001.tif
LDR_STACK_2=Vykres-Procesor_stack_ldr_0002.tif
LDR_STACK_2_SHELL=Vykres-Procesor_stack_ldr_0002.tif
LDR_STACK_2_INPUT=Vykres-Procesor_exposure_layers_0002.tif
LDR_STACK_2_INPUT_SHELL=Vykres-Procesor_exposure_layers_0002.tif
LDR_STACK_3=Vykres-Procesor_stack_ldr_0003.tif
LDR_STACK_3_SHELL=Vykres-Procesor_stack_ldr_0003.tif
LDR_STACK_3_INPUT=Vykres-Procesor_exposure_layers_0003.tif
LDR_STACK_3_INPUT_SHELL=Vykres-Procesor_exposure_layers_0003.tif
LDR_STACK_4=Vykres-Procesor_stack_ldr_0004.tif
LDR_STACK_4_SHELL=Vykres-Procesor_stack_ldr_0004.tif
LDR_STACK_4_INPUT=Vykres-Procesor_exposure_layers_0004.tif
LDR_STACK_4_INPUT_SHELL=Vykres-Procesor_exposure_layers_0004.tif
LDR_STACK_5=Vykres-Procesor_stack_ldr_0005.tif
LDR_STACK_5_SHELL=Vykres-Procesor_stack_ldr_0005.tif
LDR_STACK_5_INPUT=Vykres-Procesor_exposure_layers_0005.tif
LDR_STACK_5_INPUT_SHELL=Vykres-Procesor_exposure_layers_0005.tif
LDR_STACK_6=Vykres-Procesor_stack_ldr_0006.tif
LDR_STACK_6_SHELL=Vykres-Procesor_stack_ldr_0006.tif
LDR_STACK_6_INPUT=Vykres-Procesor_exposure_layers_0006.tif
LDR_STACK_6_INPUT_SHELL=Vykres-Procesor_exposure_layers_0006.tif
LDR_STACK_7=Vykres-Procesor_stack_ldr_0007.tif
LDR_STACK_7_SHELL=Vykres-Procesor_stack_ldr_0007.tif
LDR_STACK_7_INPUT=Vykres-Procesor_exposure_layers_0007.tif
LDR_STACK_7_INPUT_SHELL=Vykres-Procesor_exposure_layers_0007.tif
LDR_STACK_8=Vykres-Procesor_stack_ldr_0008.tif
LDR_STACK_8_SHELL=Vykres-Procesor_stack_ldr_0008.tif
LDR_STACK_8_INPUT=Vykres-Procesor_exposure_layers_0008.tif
LDR_STACK_8_INPUT_SHELL=Vykres-Procesor_exposure_layers_0008.tif
LDR_STACK_9=Vykres-Procesor_stack_ldr_0009.tif
LDR_STACK_9_SHELL=Vykres-Procesor_stack_ldr_0009.tif
LDR_STACK_9_INPUT=Vykres-Procesor_exposure_layers_0009.tif
LDR_STACK_9_INPUT_SHELL=Vykres-Procesor_exposure_layers_0009.tif
LDR_STACKS_NUMBERS=0 1 2 3 4 5 6 7 8 9 
LDR_STACKS=$(LDR_STACK_0) $(LDR_STACK_1) $(LDR_STACK_2) $(LDR_STACK_3) $(LDR_STACK_4) $(LDR_STACK_5) $(LDR_STACK_6) $(LDR_STACK_7) $(LDR_STACK_8) $(LDR_STACK_9) 
LDR_STACKS_SHELL=$(LDR_STACK_0_SHELL) $(LDR_STACK_1_SHELL) $(LDR_STACK_2_SHELL) $(LDR_STACK_3_SHELL) $(LDR_STACK_4_SHELL) $(LDR_STACK_5_SHELL) $(LDR_STACK_6_SHELL) $(LDR_STACK_7_SHELL) $(LDR_STACK_8_SHELL) $(LDR_STACK_9_SHELL) 
DO_LDR_BLENDED=1

all : startStitching $(LDR_BLENDED) 

startStitching : 
	@echo '==========================================================================='
	@echo 'Stitching panorama'
	@echo '==========================================================================='

clean : 
	@echo '==========================================================================='
	@echo 'Remove temporary files'
	@echo '==========================================================================='
	-$(RM) $(LDR_LAYERS_SHELL) 

test : 
	@echo '==========================================================================='
	@echo 'Testing programs'
	@echo '==========================================================================='
	@echo -n 'Checking nona...'
	@-$(NONA) --help > /dev/null 2>&1 && echo '[OK]' || echo '[FAILED]'
	@echo -n 'Checking enblend...'
	@-$(ENBLEND) -h > /dev/null 2>&1 && echo '[OK]' || echo '[FAILED]'
	@echo -n 'Checking enfuse...'
	@-$(ENFUSE) -h > /dev/null 2>&1 && echo '[OK]' || echo '[FAILED]'
	@echo -n 'Checking hugin_hdrmerge...'
	@-$(HDRMERGE) -h > /dev/null 2>&1 && echo '[OK]' || echo '[FAILED]'
	@echo -n 'Checking exiftool...'
	@-$(EXIFTOOL) -ver > /dev/null 2>&1 && echo '[OK]' || echo '[FAILED]'

info : 
	@echo '==========================================================================='
	@echo '***************  Panorama makefile generated by Hugin       ***************'
	@echo '==========================================================================='
	@echo 'System information'
	@echo '==========================================================================='
	@echo -n 'Operating system: '
	@-uname -o
	@echo -n 'Release: '
	@-uname -r
	@echo -n 'Kernel version: '
	@-uname -v
	@echo -n 'Machine: '
	@-uname -m
	@echo 'Disc usage'
	@-df -h
	@echo 'Memory usage'
	@-free -m
	@echo '==========================================================================='
	@echo 'Output options'
	@echo '==========================================================================='
	@echo 'Hugin Version: 2011.4.0.cf9be9344356'
	@echo 'Project file: /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Vykres-Procesor.pto'
	@echo 'Output prefix: Vykres-Procesor'
	@echo 'Projection: Rectilinear (0)'
	@echo 'Field of view: 29 x 30'
	@echo 'Canvas dimensions: 26670 x 27632'
	@echo 'Crop area: (661,0) - (21531,26971)'
	@echo 'Output exposure value: 0.00'
	@echo 'Selected outputs'
	@echo 'Normal panorama'
	@echo '* Blended panorama'
	@echo '==========================================================================='
	@echo 'Input images'
	@echo '==========================================================================='
	@echo 'Number of images in project file: 10'
	@echo 'Number of active images: 10'
	@echo 'Image 0: /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-1.jpg'
	@echo 'Image 0: Size 9930x7020, Exposure: 0.00'
	@echo 'Image 1: /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-2.jpg'
	@echo 'Image 1: Size 9930x7020, Exposure: 0.00'
	@echo 'Image 2: /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-3.jpg'
	@echo 'Image 2: Size 7008x9930, Exposure: 0.00'
	@echo 'Image 3: /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-4.jpg'
	@echo 'Image 3: Size 7020x9920, Exposure: 0.00'
	@echo 'Image 4: /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-5.jpg'
	@echo 'Image 4: Size 9920x7008, Exposure: 0.00'
	@echo 'Image 5: /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-6.jpg'
	@echo 'Image 5: Size 9920x7008, Exposure: 0.00'
	@echo 'Image 6: /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-7.jpg'
	@echo 'Image 6: Size 7008x9930, Exposure: 0.00'
	@echo 'Image 7: /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-8.jpg'
	@echo 'Image 7: Size 7020x9920, Exposure: 0.00'
	@echo 'Image 8: /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-9.jpg'
	@echo 'Image 8: Size 7008x9930, Exposure: 0.00'
	@echo 'Image 9: /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-0.jpg'
	@echo 'Image 9: Size 7014x10192, Exposure: 0.00'

# Rules for ordinary TIFF_m and hdr output

Vykres-Procesor0000.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-1.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -m TIFF_m -o $(LDR_REMAPPED_PREFIX_SHELL) -i 0 $(PROJECT_FILE_SHELL)

Vykres-Procesor_hdr_0000.exr : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-1.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) -r hdr -m EXR_m -o $(HDR_STACK_REMAPPED_PREFIX_SHELL) -i 0 $(PROJECT_FILE_SHELL)

Vykres-Procesor0001.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-2.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -m TIFF_m -o $(LDR_REMAPPED_PREFIX_SHELL) -i 1 $(PROJECT_FILE_SHELL)

Vykres-Procesor_hdr_0001.exr : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-2.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) -r hdr -m EXR_m -o $(HDR_STACK_REMAPPED_PREFIX_SHELL) -i 1 $(PROJECT_FILE_SHELL)

Vykres-Procesor0002.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-3.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -m TIFF_m -o $(LDR_REMAPPED_PREFIX_SHELL) -i 2 $(PROJECT_FILE_SHELL)

Vykres-Procesor_hdr_0002.exr : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-3.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) -r hdr -m EXR_m -o $(HDR_STACK_REMAPPED_PREFIX_SHELL) -i 2 $(PROJECT_FILE_SHELL)

Vykres-Procesor0003.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-4.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -m TIFF_m -o $(LDR_REMAPPED_PREFIX_SHELL) -i 3 $(PROJECT_FILE_SHELL)

Vykres-Procesor_hdr_0003.exr : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-4.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) -r hdr -m EXR_m -o $(HDR_STACK_REMAPPED_PREFIX_SHELL) -i 3 $(PROJECT_FILE_SHELL)

Vykres-Procesor0004.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-5.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -m TIFF_m -o $(LDR_REMAPPED_PREFIX_SHELL) -i 4 $(PROJECT_FILE_SHELL)

Vykres-Procesor_hdr_0004.exr : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-5.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) -r hdr -m EXR_m -o $(HDR_STACK_REMAPPED_PREFIX_SHELL) -i 4 $(PROJECT_FILE_SHELL)

Vykres-Procesor0005.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-6.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -m TIFF_m -o $(LDR_REMAPPED_PREFIX_SHELL) -i 5 $(PROJECT_FILE_SHELL)

Vykres-Procesor_hdr_0005.exr : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-6.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) -r hdr -m EXR_m -o $(HDR_STACK_REMAPPED_PREFIX_SHELL) -i 5 $(PROJECT_FILE_SHELL)

Vykres-Procesor0006.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-7.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -m TIFF_m -o $(LDR_REMAPPED_PREFIX_SHELL) -i 6 $(PROJECT_FILE_SHELL)

Vykres-Procesor_hdr_0006.exr : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-7.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) -r hdr -m EXR_m -o $(HDR_STACK_REMAPPED_PREFIX_SHELL) -i 6 $(PROJECT_FILE_SHELL)

Vykres-Procesor0007.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-8.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -m TIFF_m -o $(LDR_REMAPPED_PREFIX_SHELL) -i 7 $(PROJECT_FILE_SHELL)

Vykres-Procesor_hdr_0007.exr : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-8.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) -r hdr -m EXR_m -o $(HDR_STACK_REMAPPED_PREFIX_SHELL) -i 7 $(PROJECT_FILE_SHELL)

Vykres-Procesor0008.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-9.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -m TIFF_m -o $(LDR_REMAPPED_PREFIX_SHELL) -i 8 $(PROJECT_FILE_SHELL)

Vykres-Procesor_hdr_0008.exr : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-9.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) -r hdr -m EXR_m -o $(HDR_STACK_REMAPPED_PREFIX_SHELL) -i 8 $(PROJECT_FILE_SHELL)

Vykres-Procesor0009.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-0.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -m TIFF_m -o $(LDR_REMAPPED_PREFIX_SHELL) -i 9 $(PROJECT_FILE_SHELL)

Vykres-Procesor_hdr_0009.exr : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-0.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) -r hdr -m EXR_m -o $(HDR_STACK_REMAPPED_PREFIX_SHELL) -i 9 $(PROJECT_FILE_SHELL)

# Rules for exposure layer output

Vykres-Procesor_exposure_layers_0000.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-1.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -e 0 -m TIFF_m -o $(LDR_EXPOSURE_REMAPPED_PREFIX_SHELL) -i 0 $(PROJECT_FILE_SHELL)

Vykres-Procesor_exposure_layers_0001.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-2.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -e 0 -m TIFF_m -o $(LDR_EXPOSURE_REMAPPED_PREFIX_SHELL) -i 1 $(PROJECT_FILE_SHELL)

Vykres-Procesor_exposure_layers_0002.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-3.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -e 0 -m TIFF_m -o $(LDR_EXPOSURE_REMAPPED_PREFIX_SHELL) -i 2 $(PROJECT_FILE_SHELL)

Vykres-Procesor_exposure_layers_0003.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-4.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -e 0 -m TIFF_m -o $(LDR_EXPOSURE_REMAPPED_PREFIX_SHELL) -i 3 $(PROJECT_FILE_SHELL)

Vykres-Procesor_exposure_layers_0004.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-5.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -e 0 -m TIFF_m -o $(LDR_EXPOSURE_REMAPPED_PREFIX_SHELL) -i 4 $(PROJECT_FILE_SHELL)

Vykres-Procesor_exposure_layers_0005.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-6.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -e 0 -m TIFF_m -o $(LDR_EXPOSURE_REMAPPED_PREFIX_SHELL) -i 5 $(PROJECT_FILE_SHELL)

Vykres-Procesor_exposure_layers_0006.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-7.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -e 0 -m TIFF_m -o $(LDR_EXPOSURE_REMAPPED_PREFIX_SHELL) -i 6 $(PROJECT_FILE_SHELL)

Vykres-Procesor_exposure_layers_0007.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-8.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -e 0 -m TIFF_m -o $(LDR_EXPOSURE_REMAPPED_PREFIX_SHELL) -i 7 $(PROJECT_FILE_SHELL)

Vykres-Procesor_exposure_layers_0008.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-9.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -e 0 -m TIFF_m -o $(LDR_EXPOSURE_REMAPPED_PREFIX_SHELL) -i 8 $(PROJECT_FILE_SHELL)

Vykres-Procesor_exposure_layers_0009.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Procesor/Procesor-0.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -e 0 -m TIFF_m -o $(LDR_EXPOSURE_REMAPPED_PREFIX_SHELL) -i 9 $(PROJECT_FILE_SHELL)

# Rules for LDR and HDR stack merging, a rule for each stack

$(LDR_STACK_0) : $(LDR_STACK_0_INPUT) 
	$(ENFUSE) $(ENFUSE_OPTS) -o $(LDR_STACK_0_SHELL) -- $(LDR_STACK_0_INPUT_SHELL)
	-$(EXIFTOOL) -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(LDR_STACK_0_SHELL)

$(HDR_STACK_0) : $(HDR_STACK_0_INPUT) 
	$(HDRMERGE) $(HDRMERGE_OPTS) -o $(HDR_STACK_0_SHELL) -- $(HDR_STACK_0_INPUT_SHELL)

$(LDR_STACK_1) : $(LDR_STACK_1_INPUT) 
	$(ENFUSE) $(ENFUSE_OPTS) -o $(LDR_STACK_1_SHELL) -- $(LDR_STACK_1_INPUT_SHELL)
	-$(EXIFTOOL) -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(LDR_STACK_1_SHELL)

$(HDR_STACK_1) : $(HDR_STACK_1_INPUT) 
	$(HDRMERGE) $(HDRMERGE_OPTS) -o $(HDR_STACK_1_SHELL) -- $(HDR_STACK_1_INPUT_SHELL)

$(LDR_STACK_2) : $(LDR_STACK_2_INPUT) 
	$(ENFUSE) $(ENFUSE_OPTS) -o $(LDR_STACK_2_SHELL) -- $(LDR_STACK_2_INPUT_SHELL)
	-$(EXIFTOOL) -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(LDR_STACK_2_SHELL)

$(HDR_STACK_2) : $(HDR_STACK_2_INPUT) 
	$(HDRMERGE) $(HDRMERGE_OPTS) -o $(HDR_STACK_2_SHELL) -- $(HDR_STACK_2_INPUT_SHELL)

$(LDR_STACK_3) : $(LDR_STACK_3_INPUT) 
	$(ENFUSE) $(ENFUSE_OPTS) -o $(LDR_STACK_3_SHELL) -- $(LDR_STACK_3_INPUT_SHELL)
	-$(EXIFTOOL) -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(LDR_STACK_3_SHELL)

$(HDR_STACK_3) : $(HDR_STACK_3_INPUT) 
	$(HDRMERGE) $(HDRMERGE_OPTS) -o $(HDR_STACK_3_SHELL) -- $(HDR_STACK_3_INPUT_SHELL)

$(LDR_STACK_4) : $(LDR_STACK_4_INPUT) 
	$(ENFUSE) $(ENFUSE_OPTS) -o $(LDR_STACK_4_SHELL) -- $(LDR_STACK_4_INPUT_SHELL)
	-$(EXIFTOOL) -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(LDR_STACK_4_SHELL)

$(HDR_STACK_4) : $(HDR_STACK_4_INPUT) 
	$(HDRMERGE) $(HDRMERGE_OPTS) -o $(HDR_STACK_4_SHELL) -- $(HDR_STACK_4_INPUT_SHELL)

$(LDR_STACK_5) : $(LDR_STACK_5_INPUT) 
	$(ENFUSE) $(ENFUSE_OPTS) -o $(LDR_STACK_5_SHELL) -- $(LDR_STACK_5_INPUT_SHELL)
	-$(EXIFTOOL) -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(LDR_STACK_5_SHELL)

$(HDR_STACK_5) : $(HDR_STACK_5_INPUT) 
	$(HDRMERGE) $(HDRMERGE_OPTS) -o $(HDR_STACK_5_SHELL) -- $(HDR_STACK_5_INPUT_SHELL)

$(LDR_STACK_6) : $(LDR_STACK_6_INPUT) 
	$(ENFUSE) $(ENFUSE_OPTS) -o $(LDR_STACK_6_SHELL) -- $(LDR_STACK_6_INPUT_SHELL)
	-$(EXIFTOOL) -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(LDR_STACK_6_SHELL)

$(HDR_STACK_6) : $(HDR_STACK_6_INPUT) 
	$(HDRMERGE) $(HDRMERGE_OPTS) -o $(HDR_STACK_6_SHELL) -- $(HDR_STACK_6_INPUT_SHELL)

$(LDR_STACK_7) : $(LDR_STACK_7_INPUT) 
	$(ENFUSE) $(ENFUSE_OPTS) -o $(LDR_STACK_7_SHELL) -- $(LDR_STACK_7_INPUT_SHELL)
	-$(EXIFTOOL) -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(LDR_STACK_7_SHELL)

$(HDR_STACK_7) : $(HDR_STACK_7_INPUT) 
	$(HDRMERGE) $(HDRMERGE_OPTS) -o $(HDR_STACK_7_SHELL) -- $(HDR_STACK_7_INPUT_SHELL)

$(LDR_STACK_8) : $(LDR_STACK_8_INPUT) 
	$(ENFUSE) $(ENFUSE_OPTS) -o $(LDR_STACK_8_SHELL) -- $(LDR_STACK_8_INPUT_SHELL)
	-$(EXIFTOOL) -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(LDR_STACK_8_SHELL)

$(HDR_STACK_8) : $(HDR_STACK_8_INPUT) 
	$(HDRMERGE) $(HDRMERGE_OPTS) -o $(HDR_STACK_8_SHELL) -- $(HDR_STACK_8_INPUT_SHELL)

$(LDR_STACK_9) : $(LDR_STACK_9_INPUT) 
	$(ENFUSE) $(ENFUSE_OPTS) -o $(LDR_STACK_9_SHELL) -- $(LDR_STACK_9_INPUT_SHELL)
	-$(EXIFTOOL) -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(LDR_STACK_9_SHELL)

$(HDR_STACK_9) : $(HDR_STACK_9_INPUT) 
	$(HDRMERGE) $(HDRMERGE_OPTS) -o $(HDR_STACK_9_SHELL) -- $(HDR_STACK_9_INPUT_SHELL)

$(LDR_BLENDED) : $(LDR_LAYERS) 
	$(ENBLEND) $(ENBLEND_LDR_COMP) $(ENBLEND_OPTS) -o $(LDR_BLENDED_SHELL) -- $(LDR_LAYERS_SHELL)
	-$(EXIFTOOL) -E -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(EXIFTOOL_INFO_ARGS) $(LDR_BLENDED_SHELL)

$(LDR_EXPOSURE_LAYER_0) : $(LDR_EXPOSURE_LAYER_0_INPUT) 
	$(ENBLEND) $(ENBLEND_EXPOSURE_COMP) $(ENBLEND_OPTS) -o $(LDR_EXPOSURE_LAYER_0_SHELL) -- $(LDR_EXPOSURE_LAYER_0_INPUT_SHELL)
	-$(EXIFTOOL) -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(LDR_EXPOSURE_LAYER_0_SHELL)

$(LDR_STACKED_BLENDED) : $(LDR_STACKS) 
	$(ENBLEND) $(ENBLEND_LDR_COMP) $(ENBLEND_OPTS) -o $(LDR_STACKED_BLENDED_SHELL) -- $(LDR_STACKS_SHELL)
	-$(EXIFTOOL) -E -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(EXIFTOOL_INFO_ARGS) $(LDR_STACKED_BLENDED_SHELL)

$(LDR_EXPOSURE_LAYERS_FUSED) : $(LDR_EXPOSURE_LAYERS) 
	$(ENFUSE) $(ENBLEND_LDR_COMP) $(ENFUSE_OPTS) -o $(LDR_EXPOSURE_LAYERS_FUSED_SHELL) -- $(LDR_EXPOSURE_LAYERS_SHELL)
	-$(EXIFTOOL) -E -overwrite_original_in_place -TagsFromFile $(INPUT_IMAGE_1_SHELL) $(EXIFTOOL_COPY_ARGS) $(EXIFTOOL_INFO_ARGS) $(LDR_EXPOSURE_LAYERS_FUSED_SHELL)

$(HDR_BLENDED) : $(HDR_STACKS) 
	$(ENBLEND) $(ENBLEND_HDR_COMP) $(ENBLEND_OPTS) -o $(HDR_BLENDED_SHELL) -- $(HDR_STACKS_SHELL)

$(LDR_REMAPPED_PREFIX)_multilayer.tif : $(LDR_LAYERS) 
	tiffcp $(LDR_LAYERS_SHELL) $(LDR_REMAPPED_PREFIX_SHELL)_multilayer.tif

$(LDR_REMAPPED_PREFIX)_fused_multilayer.tif : $(LDR_STACKS) $(LDR_EXPOSURE_LAYERS) 
	tiffcp $(LDR_STACKS_SHELL) $(LDR_EXPOSURE_LAYERS_SHELL) $(LDR_REMAPPED_PREFIX_SHELL)_fused_multilayer.tif

$(LDR_REMAPPED_PREFIX)_multilayer.psd : $(LDR_LAYERS) 
	PTtiff2psd -o $(LDR_REMAPPED_PREFIX_SHELL)_multilayer.psd $(LDR_LAYERS_SHELL)

$(LDR_REMAPPED_PREFIX)_fused_multilayer.psd : $(LDR_STACKS) $(LDR_EXPOSURE_LAYERS) 
	PTtiff2psd -o $(LDR_REMAPPED_PREFIX_SHELL)_fused_multilayer.psd $(LDR_STACKS_SHELL)$(LDR_EXPOSURE_LAYERS_SHELL)
