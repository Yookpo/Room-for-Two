?@echo off
:menu
cls
echo ========================================
echo.  � ������Ʈ�� ������ ���ðڽ��ϱ�?
echo ========================================
echo.
echo.  [1] Allocator
echo.  [2] Json_Parser_Wrapping
echo.
echo ========================================
set /p "choice=��ȣ�� �Է��ϼ��� (1-2): "

if "%choice%"=="1" (
    start "" "Document\Allocator\html\index.html"
    goto end
)
if "%choice%"=="2" (
    start "" "Document\Json_Parser_Wrapping\html\index.html"
    goto end
)

echo.
echo  �߸��� ��ȣ�Դϴ�. �ٽ� �õ��ϼ���.
pause
goto menu

:end
exit