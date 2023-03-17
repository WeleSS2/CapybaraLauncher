:loop
    tasklist /FI "IMAGENAME eq CapybaraLauncher.exe" 2>NUL | find /I /N "CapybaraLauncher.exe">NUL
    if "%ERRORLEVEL%"=="0" (
        timeout /T 1 > NUL
        goto loop
    ) else (
        tar -xzf temp_download.zip --strip-components=1-C . TWCapybara
        del temp_download.zip
        start CapybaraLauncher.exe
        exit
    )