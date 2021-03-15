@echo off
xcopy "%~dp0\sq2c.exe" "%windir%\system32\"  /s /h
echo SQ2C installed successfully
pause