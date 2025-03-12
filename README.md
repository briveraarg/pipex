# Pipex

Pipex es un programa en C que simula el comportamiento del operador de pipes (`|`) en la shell de Unix. Permite ejecutar una cadena de comandos conectados por tuberías, redirigiendo la salida de un comando como entrada del siguiente.

### ¿Qué es un pipe?
Un **pipe** es un mecanismo de comunicación entre procesos en sistemas Unix/Linux. Permite redirigir la salida estándar de un proceso hacia la entrada estándar de otro, facilitando el encadenamiento de comandos.

## Partes del proyecto 
### Pipex: una familia de dos hijos
- **Pipe simple**: Ejecuta dos comandos en una pipeline, similar al operador `|` en shells Unix (ejemplo: `cmd1 | cmd2`).
- **Infile/Outfile**: Redirige la entrada desde un archivo y la salida a otro archivo utilizando descriptores de archivos.
- **Manejo de errores**: Previene bloqueos inesperados y fugas de memoria.
- **Soporte básico de comandos**: Permite la ejecución de comandos de shell con argumentos.

### Pipex Bonus: familia numerosa y `here_doc`
- **Múltiples pipes**: Soporta más de dos comandos en una pipeline (ejemplo: `cmd1 | cmd2 | cmd3`).
- **Here Document**: Implementa redirección `<<` y `>>` cuando el primer parámetro es `here_doc`.
- **Manejo de errores avanzado**: Mejora la gestión de errores y casos extremos.

## Instalación

Clona el repositorio:

```sh
git clone https://github.com/tusuario/pipex.git
```
Compilar el programa con:
```sh
make
```
Ejecutar con:
```sh
./pipex infile cmd1 cmd2 outfile
```
Ejemplo:
```sh
./pipex input.txt "grep hello" "wc -l" output.txt
```

## Bonus
Compilar el programa con:
```sh
make bonus
```
Ejecutar con:
```sh
./pipex infile cmd1 cmd2 cmd3 cmd4 outfile
```

El programa soporta `here_doc` con la sintaxis:
```sh
./pipex here_doc LIMITER cmd1 cmd2 outfile
```
Ejemplo:
```sh
./pipex here_doc END "cat" "wc -l" output.txt
```

### ¿Qué es `here_doc`?
`here_doc` es una funcionalidad que permite redirigir la entrada estándar desde la misma línea de comandos o desde un bloque de texto dentro del script, hasta que se detecte un delimitador predefinido. Es útil para pasar múltiples líneas de entrada sin necesidad de un archivo externo.

## Recomendaciones para Testing
- `time`: Medir el tiempo de ejecución de comandos, especialmente con `sleep`, para verificar la concurrencia.
- `env`: Comprobar si las variables de entorno (e.g., `PATH`) se pasan correctamente a los comandos.
- `env -i`: Probar cómo el programa maneja comandos sin variables de entorno.
- `which ls`: Usar `which` para buscar la ruta de los comandos y probar con rutas absolutas en `pipex`.
- `unset PATH` o `export PATH=""`: Probar el comportamiento de `pipex` sin `PATH`.
- `valgrind --trace-children=yes --track-fds=yes`: Usar estas opciones para verificar la gestión de procesos hijo y descriptores de archivos.

## Recursos Recomendados
Para una mejor comprensión sobre la gestión de errores y la salida esperada, recomendamos visitar [este repositorio](https://github.com/oliverkingz/pipex), que explica con más detalle estos aspectos.

## Requisitos
- Sistema Unix/Linux
- Compilador `gcc`
- `Makefile` para compilar

## Autora
Brenda Rivera


