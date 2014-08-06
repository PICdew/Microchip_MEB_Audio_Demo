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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MEB_Audio_Demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MEB_Audio_Demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../BSP/cpld.c ../BSP/SST25VF016.c ../BSP/TouchScreen.c ../BSP/WM8731Drv.c ../Source/Audio.c ../Source/Fonts.c ../Source/frog.c ../Source/GraphicsLayout.c ../Source/MainDemo.c ../Source/TimeDelay.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1360889168/cpld.o ${OBJECTDIR}/_ext/1360889168/SST25VF016.o ${OBJECTDIR}/_ext/1360889168/TouchScreen.o ${OBJECTDIR}/_ext/1360889168/WM8731Drv.o ${OBJECTDIR}/_ext/1728301206/Audio.o ${OBJECTDIR}/_ext/1728301206/Fonts.o ${OBJECTDIR}/_ext/1728301206/frog.o ${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o ${OBJECTDIR}/_ext/1728301206/MainDemo.o ${OBJECTDIR}/_ext/1728301206/TimeDelay.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1360889168/cpld.o.d ${OBJECTDIR}/_ext/1360889168/SST25VF016.o.d ${OBJECTDIR}/_ext/1360889168/TouchScreen.o.d ${OBJECTDIR}/_ext/1360889168/WM8731Drv.o.d ${OBJECTDIR}/_ext/1728301206/Audio.o.d ${OBJECTDIR}/_ext/1728301206/Fonts.o.d ${OBJECTDIR}/_ext/1728301206/frog.o.d ${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o.d ${OBJECTDIR}/_ext/1728301206/MainDemo.o.d ${OBJECTDIR}/_ext/1728301206/TimeDelay.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1360889168/cpld.o ${OBJECTDIR}/_ext/1360889168/SST25VF016.o ${OBJECTDIR}/_ext/1360889168/TouchScreen.o ${OBJECTDIR}/_ext/1360889168/WM8731Drv.o ${OBJECTDIR}/_ext/1728301206/Audio.o ${OBJECTDIR}/_ext/1728301206/Fonts.o ${OBJECTDIR}/_ext/1728301206/frog.o ${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o ${OBJECTDIR}/_ext/1728301206/MainDemo.o ${OBJECTDIR}/_ext/1728301206/TimeDelay.o

# Source Files
SOURCEFILES=../BSP/cpld.c ../BSP/SST25VF016.c ../BSP/TouchScreen.c ../BSP/WM8731Drv.c ../Source/Audio.c ../Source/Fonts.c ../Source/frog.c ../Source/GraphicsLayout.c ../Source/MainDemo.c ../Source/TimeDelay.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MEB_Audio_Demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1360889168/cpld.o: ../BSP/cpld.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360889168 
	@${RM} ${OBJECTDIR}/_ext/1360889168/cpld.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360889168/cpld.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360889168/cpld.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1360889168/cpld.o.d" -o ${OBJECTDIR}/_ext/1360889168/cpld.o ../BSP/cpld.c   
	
${OBJECTDIR}/_ext/1360889168/SST25VF016.o: ../BSP/SST25VF016.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360889168 
	@${RM} ${OBJECTDIR}/_ext/1360889168/SST25VF016.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360889168/SST25VF016.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360889168/SST25VF016.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1360889168/SST25VF016.o.d" -o ${OBJECTDIR}/_ext/1360889168/SST25VF016.o ../BSP/SST25VF016.c   
	
${OBJECTDIR}/_ext/1360889168/TouchScreen.o: ../BSP/TouchScreen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360889168 
	@${RM} ${OBJECTDIR}/_ext/1360889168/TouchScreen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360889168/TouchScreen.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360889168/TouchScreen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1360889168/TouchScreen.o.d" -o ${OBJECTDIR}/_ext/1360889168/TouchScreen.o ../BSP/TouchScreen.c   
	
${OBJECTDIR}/_ext/1360889168/WM8731Drv.o: ../BSP/WM8731Drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360889168 
	@${RM} ${OBJECTDIR}/_ext/1360889168/WM8731Drv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360889168/WM8731Drv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360889168/WM8731Drv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1360889168/WM8731Drv.o.d" -o ${OBJECTDIR}/_ext/1360889168/WM8731Drv.o ../BSP/WM8731Drv.c   
	
${OBJECTDIR}/_ext/1728301206/Audio.o: ../Source/Audio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Audio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Audio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/Audio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1728301206/Audio.o.d" -o ${OBJECTDIR}/_ext/1728301206/Audio.o ../Source/Audio.c   
	
${OBJECTDIR}/_ext/1728301206/Fonts.o: ../Source/Fonts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Fonts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Fonts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/Fonts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1728301206/Fonts.o.d" -o ${OBJECTDIR}/_ext/1728301206/Fonts.o ../Source/Fonts.c   
	
${OBJECTDIR}/_ext/1728301206/frog.o: ../Source/frog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/frog.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/frog.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/frog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1728301206/frog.o.d" -o ${OBJECTDIR}/_ext/1728301206/frog.o ../Source/frog.c   
	
${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o: ../Source/GraphicsLayout.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o.d" -o ${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o ../Source/GraphicsLayout.c   
	
${OBJECTDIR}/_ext/1728301206/MainDemo.o: ../Source/MainDemo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/MainDemo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/MainDemo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/MainDemo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1728301206/MainDemo.o.d" -o ${OBJECTDIR}/_ext/1728301206/MainDemo.o ../Source/MainDemo.c   
	
${OBJECTDIR}/_ext/1728301206/TimeDelay.o: ../Source/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/TimeDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1728301206/TimeDelay.o.d" -o ${OBJECTDIR}/_ext/1728301206/TimeDelay.o ../Source/TimeDelay.c   
	
else
${OBJECTDIR}/_ext/1360889168/cpld.o: ../BSP/cpld.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360889168 
	@${RM} ${OBJECTDIR}/_ext/1360889168/cpld.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360889168/cpld.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360889168/cpld.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1360889168/cpld.o.d" -o ${OBJECTDIR}/_ext/1360889168/cpld.o ../BSP/cpld.c   
	
${OBJECTDIR}/_ext/1360889168/SST25VF016.o: ../BSP/SST25VF016.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360889168 
	@${RM} ${OBJECTDIR}/_ext/1360889168/SST25VF016.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360889168/SST25VF016.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360889168/SST25VF016.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1360889168/SST25VF016.o.d" -o ${OBJECTDIR}/_ext/1360889168/SST25VF016.o ../BSP/SST25VF016.c   
	
${OBJECTDIR}/_ext/1360889168/TouchScreen.o: ../BSP/TouchScreen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360889168 
	@${RM} ${OBJECTDIR}/_ext/1360889168/TouchScreen.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360889168/TouchScreen.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360889168/TouchScreen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1360889168/TouchScreen.o.d" -o ${OBJECTDIR}/_ext/1360889168/TouchScreen.o ../BSP/TouchScreen.c   
	
${OBJECTDIR}/_ext/1360889168/WM8731Drv.o: ../BSP/WM8731Drv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1360889168 
	@${RM} ${OBJECTDIR}/_ext/1360889168/WM8731Drv.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360889168/WM8731Drv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360889168/WM8731Drv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1360889168/WM8731Drv.o.d" -o ${OBJECTDIR}/_ext/1360889168/WM8731Drv.o ../BSP/WM8731Drv.c   
	
${OBJECTDIR}/_ext/1728301206/Audio.o: ../Source/Audio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Audio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Audio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/Audio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1728301206/Audio.o.d" -o ${OBJECTDIR}/_ext/1728301206/Audio.o ../Source/Audio.c   
	
${OBJECTDIR}/_ext/1728301206/Fonts.o: ../Source/Fonts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Fonts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/Fonts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/Fonts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1728301206/Fonts.o.d" -o ${OBJECTDIR}/_ext/1728301206/Fonts.o ../Source/Fonts.c   
	
${OBJECTDIR}/_ext/1728301206/frog.o: ../Source/frog.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/frog.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/frog.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/frog.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1728301206/frog.o.d" -o ${OBJECTDIR}/_ext/1728301206/frog.o ../Source/frog.c   
	
${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o: ../Source/GraphicsLayout.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o.d" -o ${OBJECTDIR}/_ext/1728301206/GraphicsLayout.o ../Source/GraphicsLayout.c   
	
${OBJECTDIR}/_ext/1728301206/MainDemo.o: ../Source/MainDemo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/MainDemo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/MainDemo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/MainDemo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1728301206/MainDemo.o.d" -o ${OBJECTDIR}/_ext/1728301206/MainDemo.o ../Source/MainDemo.c   
	
${OBJECTDIR}/_ext/1728301206/TimeDelay.o: ../Source/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1728301206 
	@${RM} ${OBJECTDIR}/_ext/1728301206/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1728301206/TimeDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1728301206/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../Include/Graphics" -I"../Include/BSP" -I"../Include" -I".." -MMD -MF "${OBJECTDIR}/_ext/1728301206/TimeDelay.o.d" -o ${OBJECTDIR}/_ext/1728301206/TimeDelay.o ../Source/TimeDelay.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MEB_Audio_Demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../Lib/Graphics_lib.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MEB_Audio_Demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\Lib\Graphics_lib.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,--defsym=_min_heap_size=8192,--defsym=_min_stack_size=4096,-L"../../../../../../../../Program Files/Microchip/TNAA/lib",-L"../../../../../../../../Program Files/Microchip/TNAA/pic32mx/lib",-L"..",-Map="${DISTDIR}/MEB_Audio_Demo.X.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MEB_Audio_Demo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../Lib/Graphics_lib.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MEB_Audio_Demo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\Lib\Graphics_lib.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=8192,--defsym=_min_stack_size=4096,-L"../../../../../../../../Program Files/Microchip/TNAA/lib",-L"../../../../../../../../Program Files/Microchip/TNAA/pic32mx/lib",-L"..",-Map="${DISTDIR}/MEB_Audio_Demo.X.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MEB_Audio_Demo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
