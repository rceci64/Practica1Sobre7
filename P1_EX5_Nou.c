#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_NOM 30
#define MAX_ESPECIES 10
#define MAX_INPUT 140

typedef struct{
			char nom[MAX_NOM];
			int exemplars;
			char data[11];
			char seccio;
			int habitacle;
}especie;

int comprovarData (char *dat){
	int i = 0, j = 0, dia = 0, mes = 0, any = 0;
	char aux[5];

	//Recorrem la cadena amb la fi de passar-ho tot a enter
	while (dat[i] != '/'){
		aux[j] = dat[i];
		i++;
		j++;
	}
	i++;
	j++;
	aux[j] = '\0';
	dia = atoi(aux);

	j = 0;
	while (dat[i] != '/'){
		aux[j] = dat[i];
		j++;
		i++;
	}
	i++;
	j++;
	aux[j] = '\0';
	mes = atoi(aux);

	j = 0;
	while (dat[i] != '\0'){
		aux[j] = dat[i];
		j++;
		i++;
	}
	i++;
	j++;
	aux[j] = '\0';
	any = atoi(aux);

	if( mes < 1 || mes > 12 || dia < 1 || dia > 31 || any < 1000 || any > 9999){
		return 0;
	}
	if (mes == 4 || mes == 6 || mes == 9 || mes == 11){
		if (dia > 30){
			return 0;
		}
	}
	if (mes == 2){
		if(dia > 28){
			return 0;
		}
	}

	return 1;
}

int comprovarDades (char *cad){
	int i = 0, j = 0;
	char data_aux[11];

	while(cad[i] != '-'){
		i++;
	}
	if(i < MAX_NOM){
		i++;
		while(cad[i] != '-'){
			if(cad[i] >= '0' && cad[i] <= '9'){
				i++;
			}else{
				return 0;
			}
		}
		i++;
		while(cad[i] != '-'){
			data_aux[j] = cad[i];
			i++;
			j++;
		}
		data_aux[j+1] = '\0';
		if(!comprovarData(data_aux)){
			return 0;
		}
		i++;

		j = 0;
		while (cad[i] != '-'){
			if(cad[i] > 'Z' || cad[i] < 'A'){
				return 0;
			}
			j++;
			i++;
		}
		if (j > 1){
			return 0;
		}
		i++;

		while(i < strlen(cad)){
			if(cad[i] >= '0' && cad[i] <= '9'){
				i++;
			}else{
				return 0;
			}
		}
	} else {
		return 0;
	}
	return 1;
}

void actualitzarDades(char *entrada, especie *especies, int index){
	int i = 0, j = 0;
	char aux[MAX_NOM];

	//Actualitzar el nom
	while (entrada[i] != '-'){
		especies[index].nom[i] = entrada[i];
		i++;
	}
	i++;
	especies[index].nom[i] = '\0';

	//Sumar exemplars
	while (entrada[i] != '-'){
		aux[j] = entrada[i];
		i++;
		j++;
	}
	i++;
	j++;
	aux[j] = '\0';
	especies[index].exemplars = especies[index].exemplars + atoi(aux);

	//Actualitzar la data
	j = 0;
	while (entrada[i] != '-'){
		especies[index].data[j] = entrada[i];
		i++;
		j++;
	}
	i++;
	j++;
	especies[index].data[j] = '\0';

	//Actualitzar seccio
	especies[index].seccio = entrada[i];

	i = i+2;

	//Actualitzar l'habitacle
	j = 0;
	while (entrada[i] != '\0'){
		aux[j] = entrada[i];
		i++;
		j++;
	}
	j++;
	aux[j] = '\0';

	especies[index].habitacle = atoi(aux);
}

int comprovarExistent(char *entrada, especie *especies, int *index){
	int i = 0;
	char aux[MAX_NOM];
	while (entrada[i] != '-'){
		aux[i] = entrada[i];
		i++;
	}
	i++;
	aux[i] = '\0';

	while (*index < MAX_ESPECIES){
		if(!strcmp(especies[*index].nom, aux)){
			return 1;
		}
		index++;
	}
	return 0;
}

void inicialitzarArray(especie *a){
	int i = 0;
	while (i < MAX_ESPECIES){
		a[i].nom[0] = '\0';
		a[i].exemplars = 0;
		i++;
	}
}

void main() {
  int opcio, n_especies = 0, index = 0;
  char entrada[MAX_INPUT];
  especie especies_zoo[MAX_ESPECIES];
	//inicialitzarArray(especies_zoo);

  while (opcio != 4){
    printf("\nPrototipus de la reserva natural");
    printf("\n1.Introduïr una nova espècie");
    printf("\n2.Llistar les espècies allotjades");
    printf("\n3.Mostrar estadístiques");
    printf("\n4.Sortir de l'aplicació\n");
    fflushnou();
    scanf("%d", &opcio);

    if (opcio >= 1 && opcio <= 4){
      if(opcio == 1){
				printf("Introdueix una nova especie: ");
				fflushnou();
				gets(entrada);
				index = 0;
				if(comprovarDades(entrada)){
					//Comprovar si ja hi ha aquesta espècie, si és així sumar exemplars i actualitzar camps
					if(comprovarExistent(entrada, especies_zoo, &index)){
						printf("--> Especie ja existent! Actualitzant les dades...\n");
						actualitzarDades(entrada, especies_zoo, index);
						printf("--> Especie afegida correctament! [%d/10] espais ocupats\n", n_especies);
					}else{
						if(n_especies >= MAX_ESPECIES){
							printf("--> Base de dades plena!");
						}else{
							//Si no existeix augmentem n_especies en 1 i actualitzem la base de dades
							actualitzarDades(entrada, especies_zoo, n_especies);
							printf ("%s\n", especies_zoo[n_especies].nom);
							printf ("%d\n", especies_zoo[n_especies].exemplars);
							printf ("%s\n", especies_zoo[n_especies].data);
							printf ("%c\n", especies_zoo[n_especies].seccio);
							printf ("%d\n", especies_zoo[n_especies].habitacle);
							n_especies++;
							printf("--> Especie afegida correctament! [%d/10] espais ocupats", n_especies);
						}
					}
				}else{
					printf("Error en les dades!");
				}

      } else if(opcio == 2){
        //Opció 2
      } else if(opcio == 3){
        //Opcio 3
      } else if(opcio == 4){
        printf("--> Sortint de la base de dades...\n" );
      }
    } else {
      printf("Opcio no valida! Torna-ho a provar");
    }
  }
}
