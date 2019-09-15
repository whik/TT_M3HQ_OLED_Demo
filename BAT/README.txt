编译前执行

..\BAT\del_hex.bat			//删除上次编译产生的hex文件

编译后执行

命令1
	fromelf --bin -o "$L@L.bin" "#L"		//调用formelf，将axf文件转换为bin文件
	
命令2
	..\BAT\del_hex_line1.bat				//将新生成的hex文件第一行之后的内容存入新文件，删除编译产生的其他垃圾文件


