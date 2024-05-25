cl -W4 src/gera-numero.c src/include/ehprimo.c src/include/concat.c -Fo"bin/" -I"src/include/" -link -out:bin/gera-numero.exe
cl -W4 -MT src/main.c src/include/ehprimo.c src/include/concat.c -Fo"bin/" -I"src/include/" -I"D:\Programas\vcpkg\installed\x64-windows-static\include" -link -LIBPATH:"D:\Programas\vcpkg\installed\x64-windows-static\lib" pthreadVC3.lib -out:bin/produtor-consumidor.exe
