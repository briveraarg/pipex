# Pipex

`Pipex` es un programa en C que simula el comportamiento del operador de tubería (`|`) en los shells de Unix. Permite ejecutar una cadena de comandos donde la salida de un comando se redirige como entrada del siguiente.

### ¿Qué es una tubería (pipe)? 🧐
Una **tubería** es un mecanismo de comunicación interprocesos unidireccional en sistemas Unix/Linux. Permite redirigir la salida estándar de un proceso a la entrada estándar de otro, facilitando el encadenamiento de comandos.

## Partes del Proyecto 📂

### 👨‍👩 Parte Obligatoria: Una Familia de Dos Hijos 
Esta parte del proyecto se centra en crear una tubería simple entre dos comandos.

**Características Principales:**
- **Tubería Simple**: Ejecuta dos comandos en una tubería, similar a `cmd1 | cmd2`.
- **Redirección de Archivos**: Redirige la entrada desde un `infile` y envía la salida a un `outfile`.
- **Manejo de Errores**: Previene fallos inesperados y fugas de memoria.
- **Ejecución de Comandos**: Soporta comandos básicos de shell con argumentos.

### 👨‍👩 👨‍👩‍👧‍👦 Parte Bonus: Familia Numerosa y `here_doc`
La parte bonus amplía la funcionalidad para manejar múltiples tuberías y la característica `here_doc`.

**Características Principales:**
- **Múltiples Tuberías**: Soporta el encadenamiento de más de dos comandos (ej., `cmd1 | cmd2 | cmd3`).
- **Here Document**: Implementa la redirección de entrada usando `<<` cuando el primer parámetro es `here_doc`.
- **Manejo de Errores Avanzado**: Mejora la gestión de errores para casos límite.

## ❤️ Función Corazón del Proyecto 

La función `pipex` es el núcleo del programa. Se encarga de crear los procesos hijos, gestionar las tuberías y esperar a que los comandos finalicen.

```c
int	pipex(t_pipex *data)
{
	int		i;
	int		status;

	i = 0;
	data->pid = ft_calloc(data->argc - 3, sizeof(pid_t));
	if (!data->pid)
		return (perror("malloc"), ENOMEM);
	while (i < data->argc - data->non_command_args)
	{
		if (create_pipes(data))
			return (ft_free_ptr((void *)&data->pid), EXIT_FAILURE);
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (perror("fork"), ft_free_ptr((void *)&data->pid), 1);
		if (data->pid[i] == 0)
			run_pipeline(i, data);
		else
			bye_bye_pipe_father(data);
		i++;
	}
	wait_childs(data->argc - data->non_command_args, &status, data->pid);
	ft_free_ptr((void *)&data->pid);
	if (data->prev_pipes != -1)
		close(data->prev_pipes);
	return (status);
}
```

## Instalación y Uso 🚀

1.  **Clona el repositorio:**
    ```sh
    git clone https://github.com/briveraarg/pipex.git
    cd pipex
    ```

2.  **Compila el programa:**
    - Para la parte obligatoria:
      ```sh
      make
      ```
    - Para la parte bonus:
      ```sh
      make bonus
      ```

3.  **Ejecuta el programa:**

    - **Obligatorio:**
      ```sh
      ./pipex infile cmd1 cmd2 outfile
      ```
      **Ejemplo:**
      ```sh
      ./pipex input.txt "grep hello" "wc -l" output.txt
      ```

    - **Bonus (Múltiples Tuberías):**
      ```sh
      ./pipex_bonus infile cmd1 cmd2 cmd3 ... outfile
      ```

    - **Bonus (`here_doc`):**
      `here_doc` permite redirigir la entrada estándar desde la línea de comandos hasta que se encuentre un `LIMITADOR` especificado.
      ```sh
      ./pipex_bonus here_doc LIMITER cmd1 cmd2 outfile
      ```
      **Ejemplo:**
      ```sh
      ./pipex_bonus here_doc END "cat" "wc -l" output.txt
      ```

## Recomendaciones para Pruebas 🧪

Para asegurar que el programa funciona correctamente, considera las siguientes pruebas:

- **Tiempo de Ejecución**: Usa `time` con comandos como `sleep` para verificar la ejecución concurrente.
- **Variables de Entorno**:
  - Usa `env` para comprobar si las variables (ej., `PATH`) se pasan correctamente a los comandos.
  - Desactiva `PATH` con `unset PATH` o `export PATH=""` para probar el comportamiento sin un `PATH`.
- **Rutas de Comandos**: Usa `which ls` para encontrar la ruta absoluta de un comando y prueba `pipex` con ella.
- **Memoria y Descriptores de Archivos**: Usa `valgrind --trace-children=yes --track-fds=yes` para detectar fugas de memoria y verificar la gestión de descriptores de archivos.

## Recursos Adicionales 📚

Para una comprensión más profunda del proyecto, recomiendo leer la documentación de Oliver, que explica cada parte en detalle. ¡No olvides darle una estrella!

[Repositorio de Pipex de Oliver](https://github.com/oliverkingz/pipex)

## Autora 👩‍💻

Proyecto desarrollado por **Brenda Rivera** como parte del currículo de 42 Madrid.

## Licencia 📄

Este proyecto está bajo la Licencia MIT. Consulta el archivo `LICENSE` para más detalles.



