
#include <so_long.h>

typedef struct s_mapa{
	
	int tiene_salida = 0;
    int tiene_posicion_inicial = 0;
    int tiene_objeto = 0;
    int caracteres_invalidos = 0;
} t_mapita;
    

// Implementación de las funciones existentes
// ...
int verificar_componentes(const char *nombre_archivo) 
{
    int fd;
	char *line;
	t_mapita	info;

	info.

	fd = open(nombre_archivo, O_RDONLY);
    if (fd == -1) {
        perror("No se puede abrir el archivo");
        return 0;
    }

    while ((line = get_next_line(fd)) != NULL) {
        for (int i = 0; line[i] != '\0' || != '\n'; i++) {
            if (line[i] == 'E') {
				info.tiene_salida++;
            } else if (line[i] == 'C') {
                info.tiene_objeto = 1;
            } else if (line[i] == 'P') {
                info.tiene_posicion_inicial++;
            } else if (line[i] != '0' && line[i] != '1') {
                info.caracteres_invalidos = 1;
            }
        }
        free(line);
    }
    close(fd);
    if (info.caracteres_invalidos || info.tiene_salida || info.posicion_inicial != 1 || !tiene_objeto) {
       perror("mapa invalido\n")
	   exit(1);   
    }
	return 0;
}