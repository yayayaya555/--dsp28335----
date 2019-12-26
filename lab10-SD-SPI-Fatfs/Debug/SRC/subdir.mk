################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/DSP2833x_CpuTimers.c \
../SRC/DSP2833x_DefaultIsr.c \
../SRC/DSP2833x_GlobalVariableDefs.c \
../SRC/DSP2833x_PieCtrl.c \
../SRC/DSP2833x_PieVect.c \
../SRC/DSP2833x_Spi.c \
../SRC/DSP2833x_SysCtrl.c \
../SRC/DSP2833x_Xintf.c \
../SRC/SD_SPI_Erase.c \
../SRC/SD_SPI_Initialization.c \
../SRC/SD_SPI_Read.c \
../SRC/SD_SPI_Registers.c \
../SRC/SD_SPI_Transmission.c \
../SRC/SD_SPI_Write.c \
../SRC/disk_sd.c \
../SRC/diskio.c \
../SRC/ff.c \
../SRC/main.c 

ASM_SRCS += \
../SRC/DSP2833x_CodeStartBranch.asm \
../SRC/DSP2833x_usDelay.asm 

ASM_DEPS += \
./SRC/DSP2833x_CodeStartBranch.pp \
./SRC/DSP2833x_usDelay.pp 

OBJS += \
./DSP2833x_CodeStartBranch.obj \
./DSP2833x_CpuTimers.obj \
./DSP2833x_DefaultIsr.obj \
./DSP2833x_GlobalVariableDefs.obj \
./DSP2833x_PieCtrl.obj \
./DSP2833x_PieVect.obj \
./DSP2833x_Spi.obj \
./DSP2833x_SysCtrl.obj \
./DSP2833x_Xintf.obj \
./DSP2833x_usDelay.obj \
./SD_SPI_Erase.obj \
./SD_SPI_Initialization.obj \
./SD_SPI_Read.obj \
./SD_SPI_Registers.obj \
./SD_SPI_Transmission.obj \
./SD_SPI_Write.obj \
./disk_sd.obj \
./diskio.obj \
./ff.obj \
./main.obj 

C_DEPS += \
./SRC/DSP2833x_CpuTimers.pp \
./SRC/DSP2833x_DefaultIsr.pp \
./SRC/DSP2833x_GlobalVariableDefs.pp \
./SRC/DSP2833x_PieCtrl.pp \
./SRC/DSP2833x_PieVect.pp \
./SRC/DSP2833x_Spi.pp \
./SRC/DSP2833x_SysCtrl.pp \
./SRC/DSP2833x_Xintf.pp \
./SRC/SD_SPI_Erase.pp \
./SRC/SD_SPI_Initialization.pp \
./SRC/SD_SPI_Read.pp \
./SRC/SD_SPI_Registers.pp \
./SRC/SD_SPI_Transmission.pp \
./SRC/SD_SPI_Write.pp \
./SRC/disk_sd.pp \
./SRC/diskio.pp \
./SRC/ff.pp \
./SRC/main.pp 

OBJS__QTD += \
".\DSP2833x_CodeStartBranch.obj" \
".\DSP2833x_CpuTimers.obj" \
".\DSP2833x_DefaultIsr.obj" \
".\DSP2833x_GlobalVariableDefs.obj" \
".\DSP2833x_PieCtrl.obj" \
".\DSP2833x_PieVect.obj" \
".\DSP2833x_Spi.obj" \
".\DSP2833x_SysCtrl.obj" \
".\DSP2833x_Xintf.obj" \
".\DSP2833x_usDelay.obj" \
".\SD_SPI_Erase.obj" \
".\SD_SPI_Initialization.obj" \
".\SD_SPI_Read.obj" \
".\SD_SPI_Registers.obj" \
".\SD_SPI_Transmission.obj" \
".\SD_SPI_Write.obj" \
".\disk_sd.obj" \
".\diskio.obj" \
".\ff.obj" \
".\main.obj" 

ASM_DEPS__QTD += \
".\SRC\DSP2833x_CodeStartBranch.pp" \
".\SRC\DSP2833x_usDelay.pp" 

C_DEPS__QTD += \
".\SRC\DSP2833x_CpuTimers.pp" \
".\SRC\DSP2833x_DefaultIsr.pp" \
".\SRC\DSP2833x_GlobalVariableDefs.pp" \
".\SRC\DSP2833x_PieCtrl.pp" \
".\SRC\DSP2833x_PieVect.pp" \
".\SRC\DSP2833x_Spi.pp" \
".\SRC\DSP2833x_SysCtrl.pp" \
".\SRC\DSP2833x_Xintf.pp" \
".\SRC\SD_SPI_Erase.pp" \
".\SRC\SD_SPI_Initialization.pp" \
".\SRC\SD_SPI_Read.pp" \
".\SRC\SD_SPI_Registers.pp" \
".\SRC\SD_SPI_Transmission.pp" \
".\SRC\SD_SPI_Write.pp" \
".\SRC\disk_sd.pp" \
".\SRC\diskio.pp" \
".\SRC\ff.pp" \
".\SRC\main.pp" 

ASM_SRCS_QUOTED += \
"../SRC/DSP2833x_CodeStartBranch.asm" \
"../SRC/DSP2833x_usDelay.asm" 

C_SRCS_QUOTED += \
"../SRC/DSP2833x_CpuTimers.c" \
"../SRC/DSP2833x_DefaultIsr.c" \
"../SRC/DSP2833x_GlobalVariableDefs.c" \
"../SRC/DSP2833x_PieCtrl.c" \
"../SRC/DSP2833x_PieVect.c" \
"../SRC/DSP2833x_Spi.c" \
"../SRC/DSP2833x_SysCtrl.c" \
"../SRC/DSP2833x_Xintf.c" \
"../SRC/SD_SPI_Erase.c" \
"../SRC/SD_SPI_Initialization.c" \
"../SRC/SD_SPI_Read.c" \
"../SRC/SD_SPI_Registers.c" \
"../SRC/SD_SPI_Transmission.c" \
"../SRC/SD_SPI_Write.c" \
"../SRC/disk_sd.c" \
"../SRC/diskio.c" \
"../SRC/ff.c" \
"../SRC/main.c" 


# Each subdirectory must supply rules for building sources it contributes
./DSP2833x_CodeStartBranch.obj: ../SRC/DSP2833x_CodeStartBranch.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_CodeStartBranch.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_CpuTimers.obj: ../SRC/DSP2833x_CpuTimers.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_CpuTimers.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_DefaultIsr.obj: ../SRC/DSP2833x_DefaultIsr.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_DefaultIsr.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_GlobalVariableDefs.obj: ../SRC/DSP2833x_GlobalVariableDefs.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_GlobalVariableDefs.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_PieCtrl.obj: ../SRC/DSP2833x_PieCtrl.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_PieCtrl.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_PieVect.obj: ../SRC/DSP2833x_PieVect.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_PieVect.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_Spi.obj: ../SRC/DSP2833x_Spi.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_Spi.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_SysCtrl.obj: ../SRC/DSP2833x_SysCtrl.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_SysCtrl.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_Xintf.obj: ../SRC/DSP2833x_Xintf.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_Xintf.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_usDelay.obj: ../SRC/DSP2833x_usDelay.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_usDelay.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./SD_SPI_Erase.obj: ../SRC/SD_SPI_Erase.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/SD_SPI_Erase.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./SD_SPI_Initialization.obj: ../SRC/SD_SPI_Initialization.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/SD_SPI_Initialization.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./SD_SPI_Read.obj: ../SRC/SD_SPI_Read.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/SD_SPI_Read.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./SD_SPI_Registers.obj: ../SRC/SD_SPI_Registers.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/SD_SPI_Registers.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./SD_SPI_Transmission.obj: ../SRC/SD_SPI_Transmission.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/SD_SPI_Transmission.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./SD_SPI_Write.obj: ../SRC/SD_SPI_Write.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/SD_SPI_Write.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./disk_sd.obj: ../SRC/disk_sd.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/disk_sd.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./diskio.obj: ../SRC/diskio.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/diskio.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./ff.obj: ../SRC/ff.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/ff.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./main.obj: ../SRC/main.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab10-SD-SPI-Fatfs/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


