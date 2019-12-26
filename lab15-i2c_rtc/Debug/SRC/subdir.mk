################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/DSP2833x_CpuTimers.c \
../SRC/DSP2833x_DefaultIsr.c \
../SRC/DSP2833x_GlobalVariableDefs.c \
../SRC/DSP2833x_I2C.c \
../SRC/DSP2833x_PieCtrl.c \
../SRC/DSP2833x_PieVect.c \
../SRC/DSP2833x_Spi.c \
../SRC/DSP2833x_SysCtrl.c \
../SRC/DSP2833x_Xintf.c \
../SRC/i2c_rtc.c 

ASM_SRCS += \
../SRC/DSP2833x_ADC_cal.asm \
../SRC/DSP2833x_CodeStartBranch.asm \
../SRC/DSP2833x_usDelay.asm 

ASM_DEPS += \
./SRC/DSP2833x_ADC_cal.pp \
./SRC/DSP2833x_CodeStartBranch.pp \
./SRC/DSP2833x_usDelay.pp 

OBJS += \
./DSP2833x_ADC_cal.obj \
./DSP2833x_CodeStartBranch.obj \
./DSP2833x_CpuTimers.obj \
./DSP2833x_DefaultIsr.obj \
./DSP2833x_GlobalVariableDefs.obj \
./DSP2833x_I2C.obj \
./DSP2833x_PieCtrl.obj \
./DSP2833x_PieVect.obj \
./DSP2833x_Spi.obj \
./DSP2833x_SysCtrl.obj \
./DSP2833x_Xintf.obj \
./DSP2833x_usDelay.obj \
./i2c_rtc.obj 

C_DEPS += \
./SRC/DSP2833x_CpuTimers.pp \
./SRC/DSP2833x_DefaultIsr.pp \
./SRC/DSP2833x_GlobalVariableDefs.pp \
./SRC/DSP2833x_I2C.pp \
./SRC/DSP2833x_PieCtrl.pp \
./SRC/DSP2833x_PieVect.pp \
./SRC/DSP2833x_Spi.pp \
./SRC/DSP2833x_SysCtrl.pp \
./SRC/DSP2833x_Xintf.pp \
./SRC/i2c_rtc.pp 

OBJS__QTD += \
".\DSP2833x_ADC_cal.obj" \
".\DSP2833x_CodeStartBranch.obj" \
".\DSP2833x_CpuTimers.obj" \
".\DSP2833x_DefaultIsr.obj" \
".\DSP2833x_GlobalVariableDefs.obj" \
".\DSP2833x_I2C.obj" \
".\DSP2833x_PieCtrl.obj" \
".\DSP2833x_PieVect.obj" \
".\DSP2833x_Spi.obj" \
".\DSP2833x_SysCtrl.obj" \
".\DSP2833x_Xintf.obj" \
".\DSP2833x_usDelay.obj" \
".\i2c_rtc.obj" 

ASM_DEPS__QTD += \
".\SRC\DSP2833x_ADC_cal.pp" \
".\SRC\DSP2833x_CodeStartBranch.pp" \
".\SRC\DSP2833x_usDelay.pp" 

C_DEPS__QTD += \
".\SRC\DSP2833x_CpuTimers.pp" \
".\SRC\DSP2833x_DefaultIsr.pp" \
".\SRC\DSP2833x_GlobalVariableDefs.pp" \
".\SRC\DSP2833x_I2C.pp" \
".\SRC\DSP2833x_PieCtrl.pp" \
".\SRC\DSP2833x_PieVect.pp" \
".\SRC\DSP2833x_Spi.pp" \
".\SRC\DSP2833x_SysCtrl.pp" \
".\SRC\DSP2833x_Xintf.pp" \
".\SRC\i2c_rtc.pp" 

ASM_SRCS_QUOTED += \
"../SRC/DSP2833x_ADC_cal.asm" \
"../SRC/DSP2833x_CodeStartBranch.asm" \
"../SRC/DSP2833x_usDelay.asm" 

C_SRCS_QUOTED += \
"../SRC/DSP2833x_CpuTimers.c" \
"../SRC/DSP2833x_DefaultIsr.c" \
"../SRC/DSP2833x_GlobalVariableDefs.c" \
"../SRC/DSP2833x_I2C.c" \
"../SRC/DSP2833x_PieCtrl.c" \
"../SRC/DSP2833x_PieVect.c" \
"../SRC/DSP2833x_Spi.c" \
"../SRC/DSP2833x_SysCtrl.c" \
"../SRC/DSP2833x_Xintf.c" \
"../SRC/i2c_rtc.c" 


# Each subdirectory must supply rules for building sources it contributes
./DSP2833x_ADC_cal.obj: ../SRC/DSP2833x_ADC_cal.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_ADC_cal.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_CodeStartBranch.obj: ../SRC/DSP2833x_CodeStartBranch.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_CodeStartBranch.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_CpuTimers.obj: ../SRC/DSP2833x_CpuTimers.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_CpuTimers.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_DefaultIsr.obj: ../SRC/DSP2833x_DefaultIsr.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_DefaultIsr.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_GlobalVariableDefs.obj: ../SRC/DSP2833x_GlobalVariableDefs.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_GlobalVariableDefs.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_I2C.obj: ../SRC/DSP2833x_I2C.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_I2C.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_PieCtrl.obj: ../SRC/DSP2833x_PieCtrl.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_PieCtrl.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_PieVect.obj: ../SRC/DSP2833x_PieVect.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_PieVect.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_Spi.obj: ../SRC/DSP2833x_Spi.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_Spi.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_SysCtrl.obj: ../SRC/DSP2833x_SysCtrl.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_SysCtrl.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_Xintf.obj: ../SRC/DSP2833x_Xintf.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_Xintf.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./DSP2833x_usDelay.obj: ../SRC/DSP2833x_usDelay.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/DSP2833x_usDelay.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

./i2c_rtc.obj: ../SRC/i2c_rtc.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="F:/workspace1/lab15-i2c_rtc/INCLUDE" --include_path="D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="D:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --diag_warning=225 --large_memory_model --float_support=fpu32 --preproc_with_compile --preproc_dependency="SRC/i2c_rtc.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


