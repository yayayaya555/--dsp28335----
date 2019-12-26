################################################################################
# Automatically-generated file. Do not edit!
################################################################################

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"../CMD/DSP2833x_Headers_nonBIOS.cmd" \
"./main.obj" \
"./ff.obj" \
"./diskio.obj" \
"./disk_sd.obj" \
"./SD_SPI_Write.obj" \
"./SD_SPI_Transmission.obj" \
"./SD_SPI_Registers.obj" \
"./SD_SPI_Read.obj" \
"./SD_SPI_Initialization.obj" \
"./SD_SPI_Erase.obj" \
"./DSP2833x_usDelay.obj" \
"./DSP2833x_Xintf.obj" \
"./DSP2833x_SysCtrl.obj" \
"./DSP2833x_Spi.obj" \
"./DSP2833x_PieVect.obj" \
"./DSP2833x_PieCtrl.obj" \
"./DSP2833x_GlobalVariableDefs.obj" \
"./DSP2833x_DefaultIsr.obj" \
"./DSP2833x_CpuTimers.obj" \
"./DSP2833x_CodeStartBranch.obj" \
-l"rts2800_fpu32.lib" \
"../CMD/28335_RAM_lnk.cmd" \

-include ../makefile.init

RM := DEL /F

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include SRC/subdir.mk
-include CMD/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: SD.out

# Tool invocations
SD.out: $(GEN_CMDS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(shell echo --silicon_version=28 > ccsLinker.opt)
	$(shell echo -g >> ccsLinker.opt)
	$(shell echo --define="_DEBUG" --define="LARGE_MODEL" >> ccsLinker.opt)
	$(shell echo --diag_warning=225 >> ccsLinker.opt)
	$(shell echo --large_memory_model >> ccsLinker.opt)
	$(shell echo --float_support=fpu32 >> ccsLinker.opt)
	$(shell echo -z >> ccsLinker.opt)
	$(shell echo -m"SD.map" >> ccsLinker.opt)
	$(shell echo --stack_size=1000 >> ccsLinker.opt)
	$(shell echo --heap_size=1000 >> ccsLinker.opt)
	$(shell echo --warn_sections >> ccsLinker.opt)
	$(shell echo -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" -i"F:/workspace1/lab10-SD-SPI-Fatfs" >> ccsLinker.opt)
	$(shell echo --reread_libs >> ccsLinker.opt)
	$(shell echo --rom_model >> ccsLinker.opt)
	$(shell type ccsObjs.opt >> ccsLinker.opt)
	"D:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsLinker.opt -o "SD.out"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QTD) "SD.out"
	-$(RM) ".\DSP2833x_CodeStartBranch.obj" ".\DSP2833x_CpuTimers.obj" ".\DSP2833x_DefaultIsr.obj" ".\DSP2833x_GlobalVariableDefs.obj" ".\DSP2833x_PieCtrl.obj" ".\DSP2833x_PieVect.obj" ".\DSP2833x_Spi.obj" ".\DSP2833x_SysCtrl.obj" ".\DSP2833x_Xintf.obj" ".\DSP2833x_usDelay.obj" ".\SD_SPI_Erase.obj" ".\SD_SPI_Initialization.obj" ".\SD_SPI_Read.obj" ".\SD_SPI_Registers.obj" ".\SD_SPI_Transmission.obj" ".\SD_SPI_Write.obj" ".\disk_sd.obj" ".\diskio.obj" ".\ff.obj" ".\main.obj" 
	-$(RM) ".\SRC\DSP2833x_CodeStartBranch.pp" ".\SRC\DSP2833x_usDelay.pp" 
	-$(RM) ".\SRC\DSP2833x_CpuTimers.pp" ".\SRC\DSP2833x_DefaultIsr.pp" ".\SRC\DSP2833x_GlobalVariableDefs.pp" ".\SRC\DSP2833x_PieCtrl.pp" ".\SRC\DSP2833x_PieVect.pp" ".\SRC\DSP2833x_Spi.pp" ".\SRC\DSP2833x_SysCtrl.pp" ".\SRC\DSP2833x_Xintf.pp" ".\SRC\SD_SPI_Erase.pp" ".\SRC\SD_SPI_Initialization.pp" ".\SRC\SD_SPI_Read.pp" ".\SRC\SD_SPI_Registers.pp" ".\SRC\SD_SPI_Transmission.pp" ".\SRC\SD_SPI_Write.pp" ".\SRC\disk_sd.pp" ".\SRC\diskio.pp" ".\SRC\ff.pp" ".\SRC\main.pp" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
