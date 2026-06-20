#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
 
#define MAX_STRING_SIZE 1000
#define MAX_LOCATIONS 5
#define MAX_SECTORS 5
#define MAX_SENSORS 3
#define MAX_INSPECTIONS 5
#define MAX_SENSORS_TYPES 5
#define MAX_INSPECTIONS_ON_SAME_DAY 2
#define END 0
#define NOT_FOUND 0
#define NOT_SELECTED -1

typedef char string[MAX_STRING_SIZE];

typedef enum entities{
    LOCATION,
    SECTOR,
    SENSOR,
    INSPECTION
} t_entities;

typedef enum sensor_types{
    TEMPERATURE,
    VIBRATION,
    PRESSURE,
    CURRENT,
    HUMIDITY
} t_sensor_types;

typedef struct datetime {
    string date;
} t_date_string;

typedef struct inspection t_inspection;
struct inspection {
    string id;
    int sensor_id;
    float value;
    time_t date_inspection;
    t_inspection *next;
};

typedef struct sensor t_sensor;
struct sensor {
    string id;
    int sector_id;
    string name;
    t_sensor_types sensor_type;
    t_inspection *inspections;
    float range_min;
    float range_max;
    int inspections_quantity;
    t_sensor *next;
};

typedef struct sector t_sector;
struct sector {
    string id;
    int location_id;
    string name;
    string description;
    t_sensor *sensors;
    int sensors_quantity;
    t_sector *next;
};

typedef struct location t_location;
struct location {
    string id;
    string name;
    t_sector *sectors;
    int sectors_quantity;
    t_location *next;
};

typedef struct stringAsStructResponse {
    string response;
} t_string;


void menuLocations(t_location **locations, t_location *location_selected);
void menuSectors(void);
void menuSensors(void);
void actionMenuLocations(int option, t_location **locations, t_location *location_selected);
void actionMenuSectors(int option);
void actionMenuSensors(int option);
void actionMenuInspections(int option);

void shutdownProgram();
void generateUniqueId(char* buffer, t_entities entity_type);
void formatStringRemoveEnter(string str);
void formatStringToUppercase(string str);
void formatStringToSystemPattern(string str);

t_location *createNewLocation();
void listAllLocations(t_location **list_location);
void insertNewLocationAtDatabase(t_location **list,  t_location *new_location);

int main(){
    srand(time(NULL));
    t_location *locations;
    t_location *location_selected_pointer = NULL;
    t_sector *sector_selected_pointer = NULL;
    t_sensor *sensor_selected_pointer = NULL;
    t_inspection *inspection_selected_pointer = NULL;
    for(;;){
        if(
            location_selected_pointer != NULL &&
            sector_selected_pointer != NULL
        ){
            menuSensors();
        } else if(
            location_selected_pointer != NULL
        ){
            menuSectors(); 
        } else {
            menuLocations(&locations, location_selected_pointer);
        }   
    }
    return 0;
}

void menuLocations(t_location **locations, t_location *location_selected_pointer){
        int option;
        printf("Bem-vindo 👋. \n");
        printf("Escolha uma opção: \n");
        printf("1. Criar Planta \n");
        printf("2. Selecionar Planta \n");
        printf("0. Fechar (Sair do programa):. \n");
        printf(":: \n");
        scanf("%i", &option);
        getchar();
        if(option == 0){
            shutdownProgram();
            return;
        }
        actionMenuLocations(option, locations, location_selected_pointer);
}
void menuSectors(){
        int option;
        printf("Escolha uma opção: \n");
        printf("1. Criar setor. \n");
        printf("2. Listar todos Setores. \n");
        printf("3. Selecionar setor. \n");
        printf("0. Voltar. \n");
        scanf("%i", &option);
        getchar();
        actionMenuSectors(option);
}
void menuSensors(){
        int option;
        printf(" Escolha uma opção: ");
        printf("1. Criar sensor. \n");
        printf("2. Listar sensores. \n");
        printf("3. Selecionar sensor. \n");
        printf("0. Voltar. \n");
        scanf("%i", &option);
        getchar();
        actionMenuSensors(option);
}
void menuInspection(){
        int option;
        printf("Escolha uma opção: \n");
        printf("1. Gerar leitura no sensor. \n");
        printf("2. Listar leituras do sensor. \n");
        printf("0. Voltar. \n");
        scanf("%i", &option);
        getchar();
        actionMenuInspections(option);
}

void actionMenuLocations(int option, t_location **locations, t_location *location_selected){
    switch(option){
            case 1:
                t_location *new_location = createNewLocation();
                insertNewLocationAtDatabase(locations, new_location);
                break;
            case 2: 
                listAllLocations(locations);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            default: break;
        }
}
void actionMenuSectors(int option){
        switch (option)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 0: 
                break;
            default:
                break;
        }
}
void actionMenuSensors(int option){
    switch (option)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 0: 
                break;
            default:
                break;
        }
}
void actionMenuInspections(int option){
    switch (option)
        {  
            case 1:
                break;
            case 2:
                break;
            case 0: 
                break;
            default:
                break;
        }
}
void shutdownProgram(){
    printf("Encerrando operação. Até logo 👋\n ");
    exit(0);
}

t_string mapSensorTypeToString(int sensor_type_enum){
    t_string object;
    string SENSOR_TYPES_STRING_MAPPED[] = {"TEMPERATURE", "VIBRATION", "PRESSURE", "CURRENT", "HUMIDITY"};
    strcpy(object.response, SENSOR_TYPES_STRING_MAPPED[sensor_type_enum]);
    return object;
}
t_string mapSensorTypeUnitToString(int sensor_type_unit_enum){
    t_string object;
    string SENSOR_TYPES_UNIT_STRING_MAPPED[] = {"°C", "mm/s", "PSI", "A", "%"};    
    strcpy(object.response, SENSOR_TYPES_UNIT_STRING_MAPPED[sensor_type_unit_enum]);
    return object;
}
t_string mapEntityToString(int entity){
    t_string object;
    string ENTITIES_TYPES[] = {"LOCATION", "SECTOR", "SENSOR", "INSPECTION"};    
    strcpy(object.response, ENTITIES_TYPES[entity]);
    return object;
}

t_location *createNewLocation(){
    t_location *new_location = NULL;
    new_location = (t_location*)malloc(sizeof(t_location));
    string unique_id; 
    generateUniqueId(unique_id, 0);
    strcpy(new_location->id, unique_id);
    
    printf("- Digite o nome: \n");
    fgets(new_location->name, MAX_STRING_SIZE, stdin);
    formatStringToSystemPattern(new_location->name);

    new_location->sectors_quantity = 0;
    
    printf("Nova planta foi cadastrada com sucesso. \n");
    return new_location;
};
void insertNewLocationAtDatabase(t_location **list,  t_location *new_location){
    if(list == NULL){
        new_location->next = NULL;
    } else {
        new_location->next = *list;
    } 
    *list = new_location;
    printf("Nova planta foi inserida com sucesso. \n");
}
void listAllLocations(t_location **list_location){
    t_location *copy_list_location = *list_location;
    int counter = 0;
    while(copy_list_location != NULL){
        printf("[IDX: %i]\n-> [ID: %s, Nome: %s]. \n", counter, copy_list_location->id, copy_list_location->name);
        copy_list_location = copy_list_location->next;
        counter++;
    }
    printf("\n\nTotal de plantas encontradas no sistema: %i.\n\n", counter);
}

void generateUniqueId(char* buffer, t_entities entity_type){
    t_string struct_sensor_type_string = mapEntityToString(entity_type);
    snprintf(buffer, 1000, "id_%.100s_%li_%i", struct_sensor_type_string.response, time(NULL), rand());
    printf("%s. \n", buffer);
}
void formatStringRemoveEnter(string str){
    if(strlen(str) < 1) return;
    str[strlen(str) - 1] = '\0';
}
void formatStringToUppercase(string str){
    for(int i = 0; str[i] != '\0'; i++){
        str[i] = toupper(str[i]);
    }
}
void formatStringToSystemPattern(string str){
    formatStringRemoveEnter(str);
    formatStringToUppercase(str);
}