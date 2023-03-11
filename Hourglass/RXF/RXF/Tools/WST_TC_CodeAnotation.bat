@echo off

rem ===================================================
rem $Id: WST_TC_CodeAnotation.bat 67316 2020-08-17 09:05:18Z mspieker $
rem $URL: https://svn.willert.de/V8/trunk/Framework/Shared/RXF/Tools/WST_TC_CodeAnotation.bat $
rem
rem Batch file that is called inside RhapsodyMake.bat
rem
rem This file belongs to the Willert Software Tools RXF Product:  
rem @WST_RELEASE_NAME@ (@WST_INSTALLDATE@).
rem Copyright (c) 2019, Willert Software Tools GmbH.
rem 
rem For detailed information about this product see release info file:
rem @WILLERT_2@/@WST_RELEASE_NAME@/ReleaseInfo.txt
rem
rem ==============================================

rem absolute path of the tool "TCCodeAnnotation.exe" in the Rhapsody installation folder
set EXECUTABLE_PATH=@WST_ENV_WST_OCTOPUS_RPY_PROGRAM_PATH@\TestConductor

rem absolute path your project path
set PROJECT_PATH=

rem path of deployed model code relative to project path
set MODEL_CODE_SUB_PATH=GeneratedModel

rem Includes needed for the code anotation
set INCLUDES=-I .
set INCLUDES=%INCLUDES% -I RXF
set INCLUDES=%INCLUDES% -I RXF/oxf
set INCLUDES=%INCLUDES% -I GeneratedModel

rem Defines needed for the code anotation
set DEFINES=
set OLDDIR=%CD%
cd /D %PROJECT_PATH%
FOR /R %%F IN (*.cpp *.c) DO (

	"%EXECUTABLE_PATH%\TCCodeAnnotation.exe" "%PROJECT_PATH%/%MODEL_CODE_SUB_PATH%" %INCLUDES% %DEFINES% "%%F"
)
cd /D %OLDDIR%
