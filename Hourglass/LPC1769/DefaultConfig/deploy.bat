@echo off

if "%1"=="clean" (
echo.
echo Delete generated sources.
del /s /q *.h
del /s /q *.c
del /s /q *.cpp
for /f "usebackq delims=" %%d in (`"dir /ad/b/s | sort /R"`) do rd "%%d"
)

if not defined WST_CI_BUILD (
set OpenIDEProjectOption=-option "Exporter.IDEProject.openProject"="true"
) else (
echo.
echo Environment variable WST_CI_BUILD set. OpenIDEProject helper deactivated.
)

call "C:\Program Files\IBM\Rational\Rhapsody\jre_x86\bin\java" -jar "C:\Users\joklappe\Hourglass\RXF\RXF\Tools\Deployer\Deployer.jar" ^
-logger "de.wst.modelxchanger.core.logger.consoleLogger" ^
-option "de.wst.wstxchanger.core.exporterImporter.option.stacktrace"="False" ^
%OpenIDEProjectOption% ^
%RXFDeployerAdditionalOptions% ^
-noSplash ^
-doImportExport
