?@echo off
:menu
cls
echo ========================================
echo.  어떤 프로젝트의 문서를 여시겠습니까?
echo ========================================
echo.
echo.  [1] Allocator
echo.  [2] Json_Parser_Wrapping
echo.
echo ========================================
set /p "choice=번호를 입력하세요 (1-2): "

if "%choice%"=="1" (
    start "" "Document\Allocator\html\index.html"
    goto end
)
if "%choice%"=="2" (
    start "" "Document\Json_Parser_Wrapping\html\index.html"
    goto end
)

echo.
echo  잘못된 번호입니다. 다시 시도하세요.
pause
goto menu

:end
exit