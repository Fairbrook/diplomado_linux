Restricciones para la creación del Makefile:

1. libarith.c deberá ser compilado como biblioteca compartida
2. El target "all" deberá generar la biblioteca compartida y la aplicación demo
3. El target "install" deberá instalar la biblioteca en el sistema en /usr/lib y header file en /usr/include
4. El target "clean" deberá borrar todo el código objeto y ejecutable generado (biblioteca y aplicación)
5. Make deberá reconocer cuando un archivo ha cambiado de manera individual y compilar solamente ese
6. Usar variables en cada receta y al menos dos banderas de compilación de gcc

