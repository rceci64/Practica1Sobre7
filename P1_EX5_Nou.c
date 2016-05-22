#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_NOM 30
#define MAX_ESPECIES 10
#define MAX_INPUT 140

typedef struct{
	int dia;
	int mes;
	int any;
}Data;

typedef struct{
	int numE;
	char seccio;
}Seccions;

typedef struct{
			char nom[MAX_NOM];
			int exemplars;
			Data dataI;
			char data[11];
			char seccio;
			int habitacle;
}especie;

Data obtenirData(char *dat){
	int i = 0, j = 0;
	char aux[5];
	Data dataAux;

	while (dat[i] != '/'){
		aux[j] = dat[i];
		i++;
		j++;
	}
	i++;
	j++;
	aux[j] = '\0';
	dataAux.dia = atoi(aux);

	j = 0;
	while (dat[i] != '/'){
		aux[j] = dat[i];
		j++;
		i++;
	}
	i++;
	j++;
	aux[j] = '\0';
	dataAux.mes = atoi(aux);

	j = 0;
	while (dat[i] != '\0'){
		aux[j] = dat[i];
		j++;
		i++;
	}
	i++;
	j++;
	aux[j] = '\0';
	dataAux.any = atoi(aux);

	return dataAux;
}

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
	//i++;
	especies[index].nom[i] = '\0';
	i++;

	//Sumar exemplars
	while (entrada[i] != '-'){
		aux[j] = entrada[i];
		i++;
		j++;
	}
	i++;
	//j++;
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
	//j++;
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
	//j++;
	aux[j] = '\0';

	especies[index].habitacle = atoi(aux);
	fflushnou();
}

int comprovarExistent(char *entrada, especie *especies, int *index){
	int i = 0;
	char aux[MAX_NOM];
	while (entrada[i] != '-'){
		aux[i] = entrada[i];
		i++;
	}
	//i++;
	aux[i] = '\0';

	while (*index < MAX_ESPECIES){
		if(!strcmp(especies[*index].nom, aux)){
			return 1;
		}
		index++;
	}
	return 0;
}

void mostraDades(especie *e, int n_especies){
	int i;

	if(n_especies >= 1){
		for(i = 0; i < n_especies; i++){
			printf("-->Especie: %s\nExemplars: %d\nData entrada: %s\nSeccio: %c\nHabitacle: %d\n\n", e[i].nom, e[i].exemplars, e[i].data, e[i].seccio, e[i].habitacle);
		}
	}else{
		printf("No hi ha especies");
	}
}

void mostraEstadistiques(especie *e, int n_especies){
	int i, j, trobat, especieMesExemplars = 0, especieMenysExemplars = 0, seccioMesExemplars = 0, especieMesAntiga = 0, n_seccions = 0;
	Seccions seccions[MAX_ESPECIES];

	if(n_especies >= 1){
		printf("-->Quantitat d'especies: %d\n", n_especies);
		//for(i = 0; i < n_especies; i++){
		//	e[i].dataI = obtenirData(e[i].data);
		//}
		for(i = 0; i < n_especies; i++){
			e[i].dataI = obtenirData(e[i].data);
			if(e[i].exemplars > e[especieMesExemplars].exemplars){
				especieMesExemplars = i;
			}
			if(e[i].exemplars < e[especieMenysExemplars].exemplars){
				especieMenysExemplars = i;
			}
			if(e[i].dataI.any < e[especieMesAntiga].dataI.any){
				especieMesAntiga = i;
			}else if(e[i].dataI.any == e[especieMesAntiga].dataI.any){
				if(e[i].dataI.mes < e[especieMesAntiga].dataI.mes){
					especieMesAntiga = i;
				}else if(e[i].dataI.mes == e[especieMesAntiga].dataI.mes){
					if(e[i].dataI.dia < e[especieMesAntiga].dataI.dia){
						especieMesAntiga = i;
					}
				}
			}
			trobat = 0;
			for(j = 0; j < n_especies && !trobat; j++){
				if(e[i].seccio == seccions[j].seccio){
					seccions[j].numE = seccions[j].numE + e[i].seccio;
					trobat = 1;
				}
			}
			if(!trobat){
				seccions[n_seccions].seccio = e[i].seccio;
				seccions[n_seccions].numE = e[i].exemplars;
				n_seccions++;
			}
		}
		for(i = 0; i < n_especies; i++){
			if(seccions[i].numE > seccions[seccioMesExemplars].numE){
				seccioMesExemplars = i;
			}
		}

		printf("-->Especie amb mes exemplars: %s (%d)\n", e[especieMesExemplars].nom, e[especieMesExemplars].exemplars);
		printf("-->Especie amb menys exemplars: %s (%d)\n", e[especieMenysExemplars].nom, e[especieMenysExemplars].exemplars);
		printf("-->Seccio amb mes exemplars: Seccio %c (%d)\n", seccions[seccioMesExemplars].seccio, seccions[seccioMesExemplars].numE);
		printf("-->Especie mes antiga: %s (%s)\n", e[especieMesAntiga].nom, e[especieMesAntiga].data);
	}else{
		printf("-->Quantitat d'especies: 0\n-->Especie amb mes exemplars: Cap\n-->Especie amb menys exemplars: Cap\n-->Seccio amb mes exemplars: Cap\n-->Especie mes antiga: Cap\n");
	}
}

void main() {
  int opcio, n_especies = 0, index = 0, i;
  char entrada[MAX_INPUT];
  especie especies_zoo[MAX_ESPECIES];
	Data comprovarDataI;
	for (i = 0; i < MAX_ESPECIES; i++){ //Incialitza els exemplars de l'array a 0
		especies_zoo[i].exemplars = 0;
	}

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
				//entrada[strlen(entrada)-1] = '\0';
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
				mostraDades(especies_zoo, n_especies);
      } else if(opcio == 3){
        //Opcio 3
				mostraEstadistiques(estadistiques_zoo, n_especies);
      } else if(opcio == 4){
        printf("--> Sortint de la base de dades...\n" );
      }
    } else {
      printf("Opcio no valida! Torna-ho a provar");
    }
  }
}
