################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LIB_SRCS += \
../lib/SFO_TI_Build_fpu.lib 


# Each subdirectory must supply rules for building sources it contributes
lib/SFO_TI_Build_fpu.out: ../lib/SFO_TI_Build_fpu.lib $(OBJS)
	@echo 'Building file: $<'
	@echo 'Invoking: Linker'
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --diag_warning=225 --large_memory_model --float_support=fpu32 -z -m"../lib/Debug/HRPWM_SFO.map" --stack_size=1000 --heap_size=1000 --warn_sections -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" -i"F:/workspace1/lab29-HRPWM_SFO" --reread_libs --rom_model -o "$@" "$<" $(ORDERED_OBJS)
	@echo 'Finished building: $<'
	@echo ' '


