
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
HUGIN_HFOV=22
HUGIN_WIDTH=20575
HUGIN_HEIGHT=8333

# options for the programs
NONA_LDR_REMAPPED_COMP=
NONA_OPTS=
ENBLEND_OPTS= -f15335x7531+144+466
ENBLEND_LDR_COMP=
ENBLEND_EXPOSURE_COMP=
ENBLEND_HDR_COMP=
HDRMERGE_OPTS=-m avg -c
ENFUSE_OPTS=
EXIFTOOL_COPY_ARGS=-ImageDescription -Make -Model -Artist -WhitePoint -Copyright -GPS:all -DateTimeOriginal -CreateDate -UserComment -ColorSpace -OwnerName -SerialNumber
EXIFTOOL_INFO_ARGS='-Software=Hugin 2011.4.0.cf9be9344356' '-UserComment<$${UserComment}&\#xa;Projection: Rectilinear (0)&\#xa;FOV: 22 x 9&\#xa;Ev: 0.00' -f

# the output panorama
LDR_REMAPPED_PREFIX=Vykres-Klavesnice
LDR_REMAPPED_PREFIX_SHELL=Vykres-Klavesnice
HDR_STACK_REMAPPED_PREFIX=Vykres-Klavesnice_hdr_
HDR_STACK_REMAPPED_PREFIX_SHELL=Vykres-Klavesnice_hdr_
LDR_EXPOSURE_REMAPPED_PREFIX=Vykres-Klavesnice_exposure_layers_
LDR_EXPOSURE_REMAPPED_PREFIX_SHELL=Vykres-Klavesnice_exposure_layers_
PROJECT_FILE=/home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Vykres-Klavesnice.pto
PROJECT_FILE_SHELL=/home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Vykres-Klavesnice.pto
LDR_BLENDED=Vykres-Klavesnice.png
LDR_BLENDED_SHELL=Vykres-Klavesnice.png
LDR_STACKED_BLENDED=Vykres-Klavesnice_fused.png
LDR_STACKED_BLENDED_SHELL=Vykres-Klavesnice_fused.png
LDR_EXPOSURE_LAYERS_FUSED=Vykres-Klavesnice_blended_fused.png
LDR_EXPOSURE_LAYERS_FUSED_SHELL=Vykres-Klavesnice_blended_fused.png
HDR_BLENDED=Vykres-Klavesnice_hdr.exr
HDR_BLENDED_SHELL=Vykres-Klavesnice_hdr.exr

# first input image
INPUT_IMAGE_1=/home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-1.jpg
INPUT_IMAGE_1_SHELL=/home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-1.jpg

# all input images
INPUT_IMAGES=/home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-1.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-2.jpg
INPUT_IMAGES_SHELL=/home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-1.jpg\
/home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-2.jpg

# remapped images
LDR_LAYERS=Vykres-Klavesnice0000.tif\
Vykres-Klavesnice0001.tif
LDR_LAYERS_SHELL=Vykres-Klavesnice0000.tif\
Vykres-Klavesnice0001.tif

# remapped images (hdr)
HDR_LAYERS=Vykres-Klavesnice_hdr_0000.exr\
Vykres-Klavesnice_hdr_0001.exr
HDR_LAYERS_SHELL=Vykres-Klavesnice_hdr_0000.exr\
Vykres-Klavesnice_hdr_0001.exr

# remapped maxval images
HDR_LAYERS_WEIGHTS=Vykres-Klavesnice_hdr_0000_gray.pgm\
Vykres-Klavesnice_hdr_0001_gray.pgm
HDR_LAYERS_WEIGHTS_SHELL=Vykres-Klavesnice_hdr_0000_gray.pgm\
Vykres-Klavesnice_hdr_0001_gray.pgm

# stacked hdr images
HDR_STACK_0=Vykres-Klavesnice_stack_hdr_0000.exr
HDR_STACK_0_SHELL=Vykres-Klavesnice_stack_hdr_0000.exr
HDR_STACK_0_INPUT=Vykres-Klavesnice_hdr_0000.exr
HDR_STACK_0_INPUT_SHELL=Vykres-Klavesnice_hdr_0000.exr
HDR_STACK_1=Vykres-Klavesnice_stack_hdr_0001.exr
HDR_STACK_1_SHELL=Vykres-Klavesnice_stack_hdr_0001.exr
HDR_STACK_1_INPUT=Vykres-Klavesnice_hdr_0001.exr
HDR_STACK_1_INPUT_SHELL=Vykres-Klavesnice_hdr_0001.exr
HDR_STACKS_NUMBERS=0 1 
HDR_STACKS=$(HDR_STACK_0) $(HDR_STACK_1) 
HDR_STACKS_SHELL=$(HDR_STACK_0_SHELL) $(HDR_STACK_1_SHELL) 

# number of image sets with similar exposure
LDR_EXPOSURE_LAYER_0=Vykres-Klavesnice_exposure_0000.tif
LDR_EXPOSURE_LAYER_0_SHELL=Vykres-Klavesnice_exposure_0000.tif
LDR_EXPOSURE_LAYER_0_INPUT=Vykres-Klavesnice_exposure_layers_0000.tif\
Vykres-Klavesnice_exposure_layers_0001.tif
LDR_EXPOSURE_LAYER_0_INPUT_SHELL=Vykres-Klavesnice_exposure_layers_0000.tif\
Vykres-Klavesnice_exposure_layers_0001.tif
LDR_EXPOSURE_LAYER_0_INPUT_PTMENDER=Vykres-Klavesnice0000.tif\
Vykres-Klavesnice0001.tif
LDR_EXPOSURE_LAYER_0_INPUT_PTMENDER_SHELL=Vykres-Klavesnice0000.tif\
Vykres-Klavesnice0001.tif
LDR_EXPOSURE_LAYER_0_EXPOSURE=0
LDR_EXPOSURE_LAYERS_NUMBERS=0 
LDR_EXPOSURE_LAYERS=$(LDR_EXPOSURE_LAYER_0) 
LDR_EXPOSURE_LAYERS_SHELL=$(LDR_EXPOSURE_LAYER_0_SHELL) 
LDR_EXPOSURE_LAYERS_REMAPPED=Vykres-Klavesnice_exposure_layers_0000.tif\
Vykres-Klavesnice_exposure_layers_0001.tif
LDR_EXPOSURE_LAYERS_REMAPPED_SHELL=Vykres-Klavesnice_exposure_layers_0000.tif\
Vykres-Klavesnice_exposure_layers_0001.tif

# stacked ldr images
LDR_STACK_0=Vykres-Klavesnice_stack_ldr_0000.tif
LDR_STACK_0_SHELL=Vykres-Klavesnice_stack_ldr_0000.tif
LDR_STACK_0_INPUT=Vykres-Klavesnice_exposure_layers_0000.tif
LDR_STACK_0_INPUT_SHELL=Vykres-Klavesnice_exposure_layers_0000.tif
LDR_STACK_1=Vykres-Klavesnice_stack_ldr_0001.tif
LDR_STACK_1_SHELL=Vykres-Klavesnice_stack_ldr_0001.tif
LDR_STACK_1_INPUT=Vykres-Klavesnice_exposure_layers_0001.tif
LDR_STACK_1_INPUT_SHELL=Vykres-Klavesnice_exposure_layers_0001.tif
LDR_STACKS_NUMBERS=0 1 
LDR_STACKS=$(LDR_STACK_0) $(LDR_STACK_1) 
LDR_STACKS_SHELL=$(LDR_STACK_0_SHELL) $(LDR_STACK_1_SHELL) 
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
	@echo 'Project file: /home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Vykres-Klavesnice.pto'
	@echo 'Output prefix: Vykres-Klavesnice'
	@echo 'Projection: Rectilinear (0)'
	@echo 'Field of view: 22 x 9'
	@echo 'Canvas dimensions: 20575 x 8333'
	@echo 'Crop area: (144,466) - (15479,7997)'
	@echo 'Output exposure value: 0.00'
	@echo 'Selected outputs'
	@echo 'Normal panorama'
	@echo '* Blended panorama'
	@echo '==========================================================================='
	@echo 'Input images'
	@echo '==========================================================================='
	@echo 'Number of images in project file: 2'
	@echo 'Number of active images: 2'
	@echo 'Image 0: /home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-1.jpg'
	@echo 'Image 0: Size 10192x7008, Exposure: 0.00'
	@echo 'Image 1: /home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-2.jpg'
	@echo 'Image 1: Size 10192x7008, Exposure: 0.00'

# Rules for ordinary TIFF_m and hdr output

Vykres-Klavesnice0000.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-1.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -m TIFF_m -o $(LDR_REMAPPED_PREFIX_SHELL) -i 0 $(PROJECT_FILE_SHELL)

Vykres-Klavesnice_hdr_0000.exr : /home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-1.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) -r hdr -m EXR_m -o $(HDR_STACK_REMAPPED_PREFIX_SHELL) -i 0 $(PROJECT_FILE_SHELL)

Vykres-Klavesnice0001.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-2.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -m TIFF_m -o $(LDR_REMAPPED_PREFIX_SHELL) -i 1 $(PROJECT_FILE_SHELL)

Vykres-Klavesnice_hdr_0001.exr : /home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-2.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) -r hdr -m EXR_m -o $(HDR_STACK_REMAPPED_PREFIX_SHELL) -i 1 $(PROJECT_FILE_SHELL)

# Rules for exposure layer output

Vykres-Klavesnice_exposure_layers_0000.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-1.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -e 0 -m TIFF_m -o $(LDR_EXPOSURE_REMAPPED_PREFIX_SHELL) -i 0 $(PROJECT_FILE_SHELL)

Vykres-Klavesnice_exposure_layers_0001.tif : /home/ceres/wrk/120804-Pemdie/Vykres-Klavesnice/Klavesnice-2.jpg $(PROJECT_FILE) 
	$(NONA) $(NONA_OPTS) $(NONA_LDR_REMAPPED_COMP) -r ldr -e 0 -m TIFF_m -o $(LDR_EXPOSURE_REMAPPED_PREFIX_SHELL) -i 1 $(PROJECT_FILE_SHELL)

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
