#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Sofware-Micro.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Sofware-Micro.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Clock.c Main.c IO_Config.c UART.c interupts.c ADC.c RingBuffer.c DAC.c timer.c GPS.c Protocolo_Comm_Yaesu.c Salidas_Motores.c Entradas.c Control_automatico.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Clock.o ${OBJECTDIR}/Main.o ${OBJECTDIR}/IO_Config.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/interupts.o ${OBJECTDIR}/ADC.o ${OBJECTDIR}/RingBuffer.o ${OBJECTDIR}/DAC.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/GPS.o ${OBJECTDIR}/Protocolo_Comm_Yaesu.o ${OBJECTDIR}/Salidas_Motores.o ${OBJECTDIR}/Entradas.o ${OBJECTDIR}/Control_automatico.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Clock.o.d ${OBJECTDIR}/Main.o.d ${OBJECTDIR}/IO_Config.o.d ${OBJECTDIR}/UART.o.d ${OBJECTDIR}/interupts.o.d ${OBJECTDIR}/ADC.o.d ${OBJECTDIR}/RingBuffer.o.d ${OBJECTDIR}/DAC.o.d ${OBJECTDIR}/timer.o.d ${OBJECTDIR}/GPS.o.d ${OBJECTDIR}/Protocolo_Comm_Yaesu.o.d ${OBJECTDIR}/Salidas_Motores.o.d ${OBJECTDIR}/Entradas.o.d ${OBJECTDIR}/Control_automatico.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Clock.o ${OBJECTDIR}/Main.o ${OBJECTDIR}/IO_Config.o ${OBJECTDIR}/UART.o ${OBJECTDIR}/interupts.o ${OBJECTDIR}/ADC.o ${OBJECTDIR}/RingBuffer.o ${OBJECTDIR}/DAC.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/GPS.o ${OBJECTDIR}/Protocolo_Comm_Yaesu.o ${OBJECTDIR}/Salidas_Motores.o ${OBJECTDIR}/Entradas.o ${OBJECTDIR}/Control_automatico.o

# Source Files
SOURCEFILES=Clock.c Main.c IO_Config.c UART.c interupts.c ADC.c RingBuffer.c DAC.c timer.c GPS.c Protocolo_Comm_Yaesu.c Salidas_Motores.c Entradas.c Control_automatico.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Sofware-Micro.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128GP804
MP_LINKER_FILE_OPTION=,--script=p33FJ128GP804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Clock.o: Clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Clock.o.d 
	@${RM} ${OBJECTDIR}/Clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Clock.c  -o ${OBJECTDIR}/Clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Clock.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/Clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Main.c  -o ${OBJECTDIR}/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/IO_Config.o: IO_Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/IO_Config.o.d 
	@${RM} ${OBJECTDIR}/IO_Config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  IO_Config.c  -o ${OBJECTDIR}/IO_Config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/IO_Config.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/IO_Config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/UART.o: UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UART.c  -o ${OBJECTDIR}/UART.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/UART.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/UART.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/interupts.o: interupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interupts.o.d 
	@${RM} ${OBJECTDIR}/interupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interupts.c  -o ${OBJECTDIR}/interupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/interupts.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/interupts.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ADC.o: ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ADC.o.d 
	@${RM} ${OBJECTDIR}/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ADC.c  -o ${OBJECTDIR}/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ADC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/ADC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/RingBuffer.o: RingBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RingBuffer.o.d 
	@${RM} ${OBJECTDIR}/RingBuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  RingBuffer.c  -o ${OBJECTDIR}/RingBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/RingBuffer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/RingBuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/DAC.o: DAC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DAC.o.d 
	@${RM} ${OBJECTDIR}/DAC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  DAC.c  -o ${OBJECTDIR}/DAC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DAC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/DAC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/timer.o: timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timer.c  -o ${OBJECTDIR}/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/GPS.o: GPS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPS.o.d 
	@${RM} ${OBJECTDIR}/GPS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  GPS.c  -o ${OBJECTDIR}/GPS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GPS.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/GPS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Protocolo_Comm_Yaesu.o: Protocolo_Comm_Yaesu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Protocolo_Comm_Yaesu.o.d 
	@${RM} ${OBJECTDIR}/Protocolo_Comm_Yaesu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Protocolo_Comm_Yaesu.c  -o ${OBJECTDIR}/Protocolo_Comm_Yaesu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Protocolo_Comm_Yaesu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/Protocolo_Comm_Yaesu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Salidas_Motores.o: Salidas_Motores.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Salidas_Motores.o.d 
	@${RM} ${OBJECTDIR}/Salidas_Motores.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Salidas_Motores.c  -o ${OBJECTDIR}/Salidas_Motores.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Salidas_Motores.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/Salidas_Motores.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Entradas.o: Entradas.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Entradas.o.d 
	@${RM} ${OBJECTDIR}/Entradas.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Entradas.c  -o ${OBJECTDIR}/Entradas.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Entradas.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/Entradas.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Control_automatico.o: Control_automatico.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Control_automatico.o.d 
	@${RM} ${OBJECTDIR}/Control_automatico.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Control_automatico.c  -o ${OBJECTDIR}/Control_automatico.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Control_automatico.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/Control_automatico.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Clock.o: Clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Clock.o.d 
	@${RM} ${OBJECTDIR}/Clock.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Clock.c  -o ${OBJECTDIR}/Clock.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Clock.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/Clock.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Main.c  -o ${OBJECTDIR}/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/IO_Config.o: IO_Config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/IO_Config.o.d 
	@${RM} ${OBJECTDIR}/IO_Config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  IO_Config.c  -o ${OBJECTDIR}/IO_Config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/IO_Config.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/IO_Config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/UART.o: UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART.o.d 
	@${RM} ${OBJECTDIR}/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UART.c  -o ${OBJECTDIR}/UART.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/UART.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/UART.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/interupts.o: interupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interupts.o.d 
	@${RM} ${OBJECTDIR}/interupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interupts.c  -o ${OBJECTDIR}/interupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/interupts.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/interupts.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ADC.o: ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ADC.o.d 
	@${RM} ${OBJECTDIR}/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ADC.c  -o ${OBJECTDIR}/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/ADC.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/ADC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/RingBuffer.o: RingBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RingBuffer.o.d 
	@${RM} ${OBJECTDIR}/RingBuffer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  RingBuffer.c  -o ${OBJECTDIR}/RingBuffer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/RingBuffer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/RingBuffer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/DAC.o: DAC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DAC.o.d 
	@${RM} ${OBJECTDIR}/DAC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  DAC.c  -o ${OBJECTDIR}/DAC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DAC.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/DAC.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/timer.o: timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timer.c  -o ${OBJECTDIR}/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/timer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/timer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/GPS.o: GPS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPS.o.d 
	@${RM} ${OBJECTDIR}/GPS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  GPS.c  -o ${OBJECTDIR}/GPS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/GPS.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/GPS.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Protocolo_Comm_Yaesu.o: Protocolo_Comm_Yaesu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Protocolo_Comm_Yaesu.o.d 
	@${RM} ${OBJECTDIR}/Protocolo_Comm_Yaesu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Protocolo_Comm_Yaesu.c  -o ${OBJECTDIR}/Protocolo_Comm_Yaesu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Protocolo_Comm_Yaesu.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/Protocolo_Comm_Yaesu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Salidas_Motores.o: Salidas_Motores.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Salidas_Motores.o.d 
	@${RM} ${OBJECTDIR}/Salidas_Motores.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Salidas_Motores.c  -o ${OBJECTDIR}/Salidas_Motores.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Salidas_Motores.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/Salidas_Motores.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Entradas.o: Entradas.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Entradas.o.d 
	@${RM} ${OBJECTDIR}/Entradas.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Entradas.c  -o ${OBJECTDIR}/Entradas.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Entradas.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/Entradas.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Control_automatico.o: Control_automatico.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Control_automatico.o.d 
	@${RM} ${OBJECTDIR}/Control_automatico.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Control_automatico.c  -o ${OBJECTDIR}/Control_automatico.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Control_automatico.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"../../../../../../../Program Files (x86)/Microchip/xc16/v1.50/support/dsPIC33F/h" -msmart-io=1 -Wall -msfr-warn=off    -mdfp=${DFP_DIR}/xc16
	@${FIXDEPS} "${OBJECTDIR}/Control_automatico.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Sofware-Micro.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Sofware-Micro.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp=${DFP_DIR}/xc16 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Sofware-Micro.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Sofware-Micro.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp=${DFP_DIR}/xc16 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Sofware-Micro.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp=${DFP_DIR}/xc16 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
