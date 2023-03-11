
############# Target type (Debug/Release) ##################
############################################################
CPPCompileDebug=-g
CPPCompileRelease=-O
LinkDebug=-g
LinkRelease=-O

CleanupFlagForSimulink=
SIMULINK_CONFIG=False
ifeq ($(SIMULINK_CONFIG),True)
CleanupFlagForSimulink=-DOM_WITH_CLEANUP
endif

ConfigurationCPPCompileSwitches=   $(INCLUDE_QUALIFIER). $(INCLUDE_QUALIFIER)$(OMROOT) $(INCLUDE_QUALIFIER)$(OMROOT)/LangCpp $(INCLUDE_QUALIFIER)$(OMROOT)/LangCpp/oxf $(DEFINE_QUALIFIER)CYGWIN $(INST_FLAGS) $(INCLUDE_PATH) $(INST_INCLUDES) -Wno-write-strings $(CPPCompileDebug) -c  $(CleanupFlagForSimulink)
ConfigurationCCCompileSwitches=$(INCLUDE_PATH) -c 

#########################################
###### Predefined macros ################
RM=/bin/rm -rf
INCLUDE_QUALIFIER=-I
DEFINE_QUALIFIER=-D
CC=g++
LIB_CMD=ar
LINK_CMD=g++
LIB_FLAGS=rvu
LINK_FLAGS= $(LinkDebug)   

#########################################
####### Context macros ##################

FLAGSFILE=
RULESFILE=
OMROOT="C:/Program Files/IBM/Rational/Rhapsody/Share"
RHPROOT="C:/Program Files/IBM/Rational/Rhapsody"
FRAMEWORK_LIB_ROOT="C:/ProgramData/IBM/Rhapsody/9.0x64/UserShare"

CPP_EXT=.cpp
H_EXT=.h
OBJ_EXT=.o
EXE_EXT=.exe
LIB_EXT=.a

INSTRUMENTATION=Animation

TIME_MODEL=RealTime

TARGET_TYPE=Executable

TARGET_NAME=Simulation

all : $(TARGET_NAME)$(EXE_EXT) Simulation.mak

TARGET_MAIN=MainSimulation

LIBS=

INCLUDE_PATH= \
  $(INCLUDE_QUALIFIER)$(OMROOT)/LangCpp/osconfig/Cygwin

ADDITIONAL_OBJS=

OBJS= \
  TimeCounter.o \
  DisplayTask.o \
  Display.o \
  Controller.o \
  AccelerationData.o \
  AccelerationMeasuring.o \
  ConfigStorage.o \
  EepromData.o \
  SimulationBuilder.o \
  SimulationDisplay.o \
  SimulationAcceleration.o \
  Application.o \
  Simulation.o




#########################################
####### Predefined macros ###############
$(OBJS) : $(INST_LIBS) $(OXF_LIBS)

ifeq ($(INSTRUMENTATION),Animation)

INST_FLAGS=$(DEFINE_QUALIFIER)OMANIMATOR $(DEFINE_QUALIFIER)__USE_W32_SOCKETS 
INST_INCLUDES=$(INCLUDE_QUALIFIER)$(OMROOT)/LangCpp/aom $(INCLUDE_QUALIFIER)$(OMROOT)/LangCpp/tom
INST_LIBS=$(FRAMEWORK_LIB_ROOT)/LangCpp/lib/cygwinaomanimx64$(LIB_EXT) $(FRAMEWORK_LIB_ROOT)/LangCpp/lib/cygwinoxsiminstx64$(LIB_EXT)
OXF_LIBS=$(FRAMEWORK_LIB_ROOT)/LangCpp/lib/cygwinoxfinstx64$(LIB_EXT) $(FRAMEWORK_LIB_ROOT)/LangCpp/lib/cygwinomcomapplx64$(LIB_EXT)
SOCK_LIB=-lws2_32

else
ifeq ($(INSTRUMENTATION),Tracing)

INST_FLAGS=$(DEFINE_QUALIFIER)OMTRACER 
INST_INCLUDES=$(INCLUDE_QUALIFIER)$(OMROOT)/LangCpp/aom $(INCLUDE_QUALIFIER)$(OMROOT)/LangCpp/tom
INST_LIBS=$(FRAMEWORK_LIB_ROOT)/LangCpp/lib/cygwintomtracex64$(LIB_EXT) $(FRAMEWORK_LIB_ROOT)/LangCpp/lib/cygwinaomtracex64$(LIB_EXT) $(FRAMEWORK_LIB_ROOT)/LangCpp/lib/cygwinoxsiminstx64$(LIB_EXT)
OXF_LIBS=$(FRAMEWORK_LIB_ROOT)/LangCpp/lib/cygwinoxfinstx64$(LIB_EXT) $(FRAMEWORK_LIB_ROOT)/LangCpp/lib/cygwinomcomapplx64$(LIB_EXT)
SOCK_LIB=-lws2_32

else
ifeq ($(INSTRUMENTATION),None)

INST_FLAGS= 
INST_INCLUDES=
INST_LIBS=$(FRAMEWORK_LIB_ROOT)/LangCpp/lib/cygwinoxsimx64$(LIB_EXT)
OXF_LIBS=$(FRAMEWORK_LIB_ROOT)/LangCpp/lib/cygwinoxfx64$(LIB_EXT)
SOCK_LIB=-lws2_32

else
	@echo An invalid Instrumentation $(INSTRUMENTATION) is specified.
	exit
endif
endif
endif

.SUFFIXES: $(CPP_EXT)

#####################################################################
##################### Context dependencies and commands #############






TimeCounter.o : TimeCounter.cpp TimeCounter.h    Application.h 
	@echo Compiling TimeCounter.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o TimeCounter.o TimeCounter.cpp




DisplayTask.o : DisplayTask.cpp DisplayTask.h    Application.h Display.h 
	@echo Compiling DisplayTask.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o DisplayTask.o DisplayTask.cpp




Display.o : Display.cpp Display.h    Application.h 
	@echo Compiling Display.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o Display.o Display.cpp




Controller.o : Controller.cpp Controller.h    Application.h DisplayTask.h TimeCounter.h AccelerationMeasuring.h ConfigStorage.h 
	@echo Compiling Controller.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o Controller.o Controller.cpp




AccelerationData.o : AccelerationData.cpp AccelerationData.h    Application.h 
	@echo Compiling AccelerationData.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o AccelerationData.o AccelerationData.cpp




AccelerationMeasuring.o : AccelerationMeasuring.cpp AccelerationMeasuring.h    Application.h AccelerationData.h 
	@echo Compiling AccelerationMeasuring.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o AccelerationMeasuring.o AccelerationMeasuring.cpp




ConfigStorage.o : ConfigStorage.cpp ConfigStorage.h    Application.h EepromData.h 
	@echo Compiling ConfigStorage.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o ConfigStorage.o ConfigStorage.cpp




EepromData.o : EepromData.cpp EepromData.h    Application.h 
	@echo Compiling EepromData.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o EepromData.o EepromData.cpp




SimulationBuilder.o : SimulationBuilder.cpp SimulationBuilder.h    Simulation.h DisplayTask.h SimulationDisplay.h Controller.h TimeCounter.h SimulationAcceleration.h AccelerationMeasuring.h Display.h AccelerationData.h 
	@echo Compiling SimulationBuilder.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o SimulationBuilder.o SimulationBuilder.cpp




SimulationDisplay.o : SimulationDisplay.cpp SimulationDisplay.h    Simulation.h Display.h 
	@echo Compiling SimulationDisplay.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o SimulationDisplay.o SimulationDisplay.cpp




SimulationAcceleration.o : SimulationAcceleration.cpp SimulationAcceleration.h    Simulation.h AccelerationData.h 
	@echo Compiling SimulationAcceleration.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o SimulationAcceleration.o SimulationAcceleration.cpp




Application.o : Application.cpp Application.h    TimeCounter.h DisplayTask.h Display.h Controller.h AccelerationData.h AccelerationMeasuring.h ConfigStorage.h EepromData.h 
	@echo Compiling Application.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o Application.o Application.cpp




Simulation.o : Simulation.cpp Simulation.h    SimulationBuilder.h SimulationDisplay.h SimulationAcceleration.h 
	@echo Compiling Simulation.cpp
	@$(CC) $(ConfigurationCPPCompileSwitches)  -o Simulation.o Simulation.cpp







$(TARGET_MAIN)$(OBJ_EXT) : $(TARGET_MAIN)$(CPP_EXT) $(OBJS)
	@echo Compiling $(TARGET_MAIN)$(CPP_EXT)
	@$(CC) $(ConfigurationCPPCompileSwitches) -o  $(TARGET_MAIN)$(OBJ_EXT) $(TARGET_MAIN)$(CPP_EXT)

####################################################################
############## Predefined Instructions #############################
$(TARGET_NAME)$(EXE_EXT): $(OBJS) $(ADDITIONAL_OBJS) $(TARGET_MAIN)$(OBJ_EXT) Simulation.mak
	@echo Linking $(TARGET_NAME)$(EXE_EXT)
	@$(LINK_CMD)  $(TARGET_MAIN)$(OBJ_EXT) $(OBJS) $(ADDITIONAL_OBJS) \
	$(LIBS) \
	$(OXF_LIBS) \
	$(INST_LIBS) \
	$(OXF_LIBS) \
	$(INST_LIBS) \
	$(SOCK_LIB) \
	$(LINK_FLAGS) -o $(TARGET_NAME)$(EXE_EXT)

$(TARGET_NAME)$(LIB_EXT) : $(OBJS) $(ADDITIONAL_OBJS) Simulation.mak
	@echo Building library $@
	@$(LIB_CMD) $(LIB_FLAGS) $(TARGET_NAME)$(LIB_EXT) $(OBJS) $(ADDITIONAL_OBJS)



clean:
	@echo Cleanup
	$(RM) TimeCounter.o
	$(RM) DisplayTask.o
	$(RM) Display.o
	$(RM) Controller.o
	$(RM) AccelerationData.o
	$(RM) AccelerationMeasuring.o
	$(RM) ConfigStorage.o
	$(RM) EepromData.o
	$(RM) SimulationBuilder.o
	$(RM) SimulationDisplay.o
	$(RM) SimulationAcceleration.o
	$(RM) Application.o
	$(RM) Simulation.o
	$(RM) $(TARGET_MAIN)$(OBJ_EXT) $(ADDITIONAL_OBJS)
	$(RM) $(TARGET_NAME)$(LIB_EXT)
	$(RM) $(TARGET_NAME)$(EXE_EXT)

