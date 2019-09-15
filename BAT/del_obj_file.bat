%删除OBJ目录下的多余文件%
del ..\OBJ\*.lnp /s
::del ..\OBJ\*.opt /s  ::不允许删除JLINK的设置
del ..\OBJ\*.__i /s
del ..\OBJ\*.crf /s
del ..\OBJ\*.o /s
del ..\OBJ\*.d /s

%删除USER目录下的多余文件%
del ..\USER\*.map /s
del ..\USER\*.lst /s
del ..\USER\*.dep /s
del ..\USER\*.build_log.htm /s

echo 编译产生的其他文件已经删除
