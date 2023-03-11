@rem $Id: Embedded_Uml_Target_Debugger.bat 39938 2017-11-09 15:22:31Z cmaas $
@rem $URL: https://svn.willert.de/V8/trunk/Framework/Shared/RXF/Tools/TargetDebugger/Embedded_Uml_Target_Debugger.bat $

@echo off
cd /d %~p0\bin

start TargetDebugger.exe %* 2> NUL

