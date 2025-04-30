#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "feiticos.h"
#define MAX_CHARS 500

School string_2_school(char *s){
    if (strcmp(s, "Enchantment") == 0) return Enchantment;
   
    else if (strcmp(s, "Necromancy") == 0) return Necromancy;
   
    else if (strcmp(s, "Divination") == 0) return Divination;
     
    else if (strcmp(s, "Evocation") == 0) return Evocation;
   
    else if (strcmp(s, "Abjuration") == 0) return Abjuration;
   
    else if (strcmp(s, "Transmutation") == 0) return Transmutation;

    else if (strcmp(s, "Illusion") == 0) return Illusion;

    else if (strcmp(s, "Conjuration") == 0) return Conjuration;
   
    else return Invalid;
   
}

const char * school_2_string(School t){
    switch (t)
    {
    case Enchantment: return "Enchantment";
   
    case Necromancy: return "Necromancy";

    case Divination: return "Divination";

    case Evocation: return "Evocation";

    case Abjuration: return "Abjuration";

    case Transmutation: return "Transmutation";

    case Illusion: return "Illusion";

    case Conjuration: return "Conjuration";

    default: return "Invalid";
    }
}

Feitico *create_feitico(char *name, char *casting_time, char *school, int lvl, int range, int duration, int concentration, char *description){
    if (name == NULL || casting_time ==  NULL || lvl < 0 || lvl > 9 || range < 0 || duration < 0 || string_2_school(school) == -1 ||concentration < 0 || concentration >1 || description[0] == '\0' || description == NULL)
    {
        return NULL;
    }
   
    Feitico *f = (Feitico*) malloc(sizeof(Feitico)); //se alocar de forma errada retorna null
    if (f == NULL)
    {
        free_feitico(f);
        return NULL;
    }
    strcpy(f->name, name);
   
    f->casting_time = (char *)malloc(strlen(casting_time) + 1); //+1 para contar com o caracter nulo
    strcpy(f->casting_time, casting_time);
   
    f->school = string_2_school(school);
    f->level = lvl;
    f->range = range;
    f->duration = duration;
    f->concentration = concentration;
   
    f->description = (char *)malloc(strlen(description) + 1); //+1 pois o strlen não le o carecter nulo
    strcpy(f->description, description);
    return f;
}

void free_feitico(Feitico *f){
   if (f != NULL)
   {
        free(f->casting_time);
        free(f->description);
        free(f);
   }  
}

Feitico* read_feitico_from(FILE *stream){
    char name[MAX_CHARS], school_str[MAX_CHARS], casting_time_str[MAX_CHARS], lvl_str[MAX_CHARS], range_str[MAX_CHARS], duration_str[MAX_CHARS], concentration_str[MAX_CHARS];
    int lvl, range, duration, concentration;
    char line[MAX_CHARS];
   
    //%[^\r\n] serve para ler tudo até encontrar um \r ou \n, ou seja, uma nova linha(assim faz com que leia os espaços)
    //\r\n serve para ler, o fscanf depois de ler tudo saber que vem a seguir um \r\n
    if (fscanf(stream, "%[^\r\n]\r\n", name) != 1) { //basicamente isto serve tudo para ler tudo incluido os espaços
        return NULL; //se não conseguir ler o nome, retorna NULL
    }

    if (name[0] == '\0') { //verifica se o nome nao esta vazio
        return NULL;
    }
    fscanf(stream, "%s\r\n%s\r\n%[^\r\n]\r\n%s\r\n%s\r\n%s\r\n", lvl_str, school_str, casting_time_str, range_str, duration_str, concentration_str);
   
    sscanf(lvl_str, "%d", &lvl); //conveter de str para int
    sscanf(range_str, "%d", &range);
    sscanf(duration_str, "%d", &duration);
    sscanf(concentration_str, "%d", &concentration);

    char *description = (char*) malloc(1); //alocaçao inicial de memoria para a descriçao, (1) para armezenar apenas 1 byte, o suf para guardar o \0
    if (description == NULL)
    {
        free(description);
        return NULL;
    }
   
    description[0] = '\0'; //inicizaliar a string description como uma string vazia
    while (1) //1 pq assim o loop fica infinito ate que seja feito um break para sair do loop
    {
        if (fgets(line, MAX_CHARS, stream) == NULL)
        {
            break;
        }
       
        if (strstr(line, "\\EOD") != NULL) //se for encotrado o \\EOD em line o strstr nao retorna null (ent é vdd) e faz break no loop
        {
            break;
        }
        description = (char*) realloc(description, strlen(description) + strlen(line) + 1);
        assert(description != NULL);
        strcat(description, line); //strcat serve para "juntar" as duas strings
    }
   
    if (strlen(description) == 0) //pus agr
    {
        free(description);
        description = NULL;
    }

    Feitico *f = create_feitico(name, casting_time_str, school_str, lvl, range, duration, concentration, description);
    if (f == NULL)
    {
        free(description); //pus agr
        printf("Invalid Spell: %s\n", name);
    }
    else
    {
        free(description);
    }
    return f;
}

Feitico** read_feiticos_from(FILE *stream, int* out_size){
    int size = 20;
    int count = 0;
    Feitico** feiticos = (Feitico**) malloc(size * sizeof(Feitico*)); //aloca memoeria para o vetor de feiticos(vetor principal)

    //feof retorna 0 qnd atinge o final do arquivo
    while(feof(stream) == 0) //feof serve para ver se estou no final do ficheiro, caso nao esteja vou dando read_feitico_from, caso ocupe a memoria toda aloco mais
    {
        Feitico* f = read_feitico_from(stream);
        if (f == NULL)
        {
            continue;
        }

        if (count >= size - 1) //se o numero de feiticos for maior que o size, dobra se o size e realocamos mais memoria para guadar os feiticos
        {
            size *= 2;
            feiticos = (Feitico**)realloc(feiticos, size * sizeof(Feitico*));
        }
           
        feiticos[count] = f;
        count++;
    }

    feiticos = (Feitico**)realloc(feiticos, (count + 1) * sizeof(Feitico*)); //apos ler a memoria é realocada para corresponder exatamente ao numero de feitios lidos
    *out_size = count; //numero de feiticos efitivamente lidos
    if (*out_size == 0)
    {
        free(feiticos);
        return NULL;
    }

    return feiticos;
}

void write_feitico_to(FILE *stream, Feitico *f){
    fprintf(stream, "%s\n%d\n%s\n%s\n%d\n%d\n%d\n%s\\EOD", f->name, f->level, school_2_string(f->school), f->casting_time, f->range, f->duration, f->concentration, f->description);
}

void write_feiticos_to(FILE *stream, Feitico *feiticos[], int n){
    for (int i = 0; i < n; i++)
    {
        write_feitico_to(stream, feiticos[i]);

        if (i != n - 1) //mete um \n sempre que nao é o ultimo \\EOD -> qnd chega ao ultimo nao coloca \n
        {
            fprintf(stream, "\n"); //se nao for o utlimo add o \n -> qnd chega ao ultimo EOD nao mete \n
        }
    }
   
}

void println_feitico(Feitico *f){
    printf("------------------------------\n");
    printf("%s\n", f->name);
    const char* nome_escola = school_2_string(f->school);
    printf("Level: %d, %s\n", f->level, nome_escola);
    printf("Casting Time: %s\n", f->casting_time);
    printf("Range: %d feet\n", f->range);
   
    printf("Duration: ");
    if (f->duration == 0)
    {
        printf("Instantaneous");
    }
    else if (f->duration <= 10)
    {
        printf("%d rounds", f->duration);
    }
    else if (f->duration <= 599)
    {
        int minutos = f->duration / 10;
        printf("%d minutes", minutos);
    }
    else
    {
        int horas = f->duration / 600;
        printf("%d hours", horas);
    }

    if (f->concentration == 1)
    {
        printf(" (Concentration)");
    }
   
    printf("\n");

    printf("%s", f->description);

    printf("------------------------------\n");
}

void println_feiticos(Feitico *feiticos[], int n){
    for (int i = 0; i < n; i++)
    {
        println_feitico(feiticos[i]);
    }
   
}

Feitico *find_feitico(Feitico *feiticos[], int n, char *name){
    for (int i = 0; i < n; i++)
    {
        if (strcmp(feiticos[i]->name, name) == 0)
        {
            return feiticos[i];
        }
       
    }
    return NULL;
   
}

void update_feitico(Feitico** feiticos, int *out_size, FILE *stream){
    char name[MAX_CHARS], school_str[MAX_CHARS], casting_time_str[MAX_CHARS], lvl_str[MAX_CHARS], range_str[MAX_CHARS], duration_str[MAX_CHARS], concentration_str[MAX_CHARS];
    int lvl, range, duration, concentration;
    char line[MAX_CHARS]; //cria uma linha para a descriçao
     
    fscanf(stream, "%[^\r\n]\r\n%s\r\n%s\r\n%[^\r\n]\r\n%s\r\n%s\r\n%s\r\n", name, lvl_str, school_str, casting_time_str, range_str, duration_str, concentration_str);
   
    sscanf(lvl_str, "%d", &lvl); //conveter de str para int
    sscanf(range_str, "%d", &range);
    sscanf(duration_str, "%d", &duration);
    sscanf(concentration_str, "%d", &concentration);

    char *description = (char*) malloc(1); //aloca espaço para a descriçao para 1 caracter
    description[0] = '\0'; //inicializa a descriçao com o caracter nulo
    while (fgets(line, 500, stream) != NULL)
    {
        if (strcmp(line, "*\n") == 0)
        {
            free(description);
            description = line;
            break;
        }
       
        if (strstr(line, "\\EOD") != NULL)
        {
            break;
        }
        description = (char*) realloc(description, strlen(description) + strlen(line) + 1);
        assert(description != NULL);
        strcat(description, line); //strcat serve para "juntar" as duas strings
    }


    Feitico *f = find_feitico(feiticos, *out_size, name);
    if (f == NULL)
    {
        printf("No such spell exists!\n");
        return;
    }

    strcpy(f->name, name);
    if (strcmp(lvl_str, "*") != 0) //se e so se o lvl_str for diferente *, copia lvl (lvl_str convetido) para o f->level senao f->level fica igual
    {
        f->level = lvl;
    }
    if (strcmp(school_str, "*") != 0)
    {
        f->school = string_2_school(school_str);
    }
    if (strcmp(casting_time_str, "*") != 0)
    {
        free(f->casting_time);
        f->casting_time = strdup(casting_time_str);
    }
    if (strcmp(range_str, "*") != 0)
    {
        f->range = range;
    }
    if (strcmp(duration_str, "*") != 0)
    {
        f->duration = duration;
    }
    if (strcmp(concentration_str, "*") != 0)
    {
        f->concentration = concentration;
    }
    if (strcmp(description, "*\n") != 0) //mesmo pensamento que os outros mas neste caso so se for diferente de *\n porque é o ultimo elemeto de um feitico
    {
        free(f->description); //limpar o q estava antes na description
        f->description = strdup(description); //guadar no f->descripton alocando memoria
        if (description != NULL)
        {
            free(description);
        }  
    }
    printf("Spell %s updated.\n", f->name);  
}

Feitico *copy_feitico(Feitico *f){
    if (f == NULL)
    {
        return NULL;
    }
   
    Feitico *copia = (Feitico *)malloc(sizeof(Feitico));

    if (copia == NULL)
    {
        return NULL;
    }
   
    strcpy(copia->name, f->name);
    copia->level = f->level;
    copia->school = f->school;
    copia->casting_time = strdup(f->casting_time);
    copia->range = f->range;
    copia->duration = f->duration;
    copia->concentration = f->concentration;
    copia->description = strdup(f->description);

    return copia;
}

int delete_feitico(Feitico *feiticos[], int n, char *name){
    assert(n > 0);
    int indix_feitico = -1;

    for (int i = 0; i < n; i++)
    {
        if (strcmp(feiticos[i]->name, name) == 0)
        {
            indix_feitico = i;
            break;    
        }
       
    }

    if (indix_feitico != -1)
    {
        free_feitico(feiticos[indix_feitico]);
       
        for (int i = indix_feitico; i < n - 1; i++)
        {
            feiticos[i] = feiticos[i + 1];
        }
       
        n--;
   
    }

    return n;
   
}

Feitico **atualizar_vista(int *size_vista, Feitico **feiticos, int size) {
    Feitico **nova_vista = (Feitico**)malloc(size * sizeof(Feitico*)); //cria memoria para a nova vista
   
    if (nova_vista == NULL) {
        return NULL; //se for mal criada
    }

    for (int i = 0; i < size; i++) {
        nova_vista[i] = feiticos[i]; //guadar cada feitico presente em feieitocs em nova_vista
    }

    *size_vista = size; //atualizar o numero da vista
    return nova_vista;
}

typedef int (*IntFeiticoSelector)(Feitico *); //ponteiro para uma funçao que recebe um array de Feiticos e retorna um inteiro
//o argumento selector é um ponteiro para a funçao to tipo IntFeiticoSelector que será usada para selecionar os elementos
int filter_feiticos_between(Feitico *in[], Feitico *out[], int n, IntFeiticoSelector selector, int min, int max){
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if ((*selector)(in[i]) >= min && (*selector)(in[i]) <= max) //verifica se o valor retornado pela funçao apontada por "seletor" esta dentro do intervalo
        {
            out[count++] = in[i]; //se o valor estiver dentro do intevalo é copiado para o array de saída
        }
       
    }
    return count;
}

int select_lvl(Feitico *f){
    return f->level;
}

int select_ran(Feitico *f){
    return f->range;
}

int select_dur(Feitico *f){
    return f->duration;
}

typedef int (*Comparer)(const void *, const void *); //um ponteiro pra um funçao que recebe dois poneteiros e retorna um int
typedef int (*FeiticoComparer)(const Feitico **, const Feitico **); //um ponteiro para uma funçao que recebe dois ponteirios const e retorna um int

int compare_feitico_name_asc(const Feitico **f1, const Feitico **f2) {
    return strcmp((*f1)->name, (*f2)->name); //compara as duas strings f1->name e f2->name, retorna -1 se name1<name2, 0 se forem igual e 1 se name1 > name2
}

int compare_feitico_name_des(const Feitico **f1, const Feitico **f2) {
    return strcmp((*f2)->name, (*f1)->name); //mesmo raciocinio que o de cima mas desta vez DES
}

int compare_feitico_lvl_asc(const Feitico **f1, const Feitico **f2) {
    return (*f1)->level - (*f2)->level; //retorna a diferenca entre os niveis de f->1 e f->2, se lvl1 > lvl 2 retorna 1, se for igual retorna 0, se for lvl1 < lvl2 retorna -1
}

int compare_feitico_lvl_des(const Feitico **f1, const Feitico **f2) {
    return (*f2)->level - (*f1)->level; //mesma ideia
}

void runSMS(void){
    int n2 = 0;
    Feitico **feiticos = NULL;
    Feitico **feiticos_vista;
    int num_vista = 0;
   
    char comando[30];
    char linha[MAX_CHARS];
    char nome_ficheiro[MAX_CHARS];
    char nome_feitico[MAX_CHARS];
    char novo_nome_2[MAX_CHARS];
    Feitico *feitico_copy;
    Feitico *feitico_delete;

    while (scanf("%[^\n]%*c", linha) != EOF) //le o caracter a seguir do \n mas ignora-o
    {
        if (linha[0] == '\n')
        {
            continue;
        }
       
        if (sscanf(linha, "%29s", comando) != 1)
        {
            continue;
        }
   
        if (strcmp(comando, "UPDATE") == 0)
        {
            update_feitico(feiticos, &n2, stdin);
        }
        else if (strcmp(comando, "LOAD") == 0)
        {
            if (sscanf(linha, "%29s %49[^\n]", comando, nome_ficheiro) != 2)
            {
                printf("Invalid command arguments!\n");
                continue;
            }
           
            FILE* file = fopen(nome_ficheiro, "r");
            if (file == NULL)
            {
                printf("Invalid file or error opening file!\n");
            }
            else
            {
                for (int i = 0; i < n2; i++)
                {
                    free_feitico(feiticos[i]);
                }
                feiticos = read_feiticos_from(file, &n2);
                fclose(file);
                printf("%d spells successfully loaded.\n", n2);
                feiticos_vista = atualizar_vista(&num_vista, feiticos, n2);
            }
        }
        else if (strcmp(comando, "SAVE") == 0)
        {
            if (sscanf(linha, "%29s %49[^\n]", comando, nome_ficheiro) != 2)
            {
                printf("Invalid command arguments!\n");
                continue;
            }

            FILE* file = fopen(nome_ficheiro, "w");
            if (file == NULL)
            {
                printf("Error opening or writing file!\n");
            }
            else
            {
                write_feiticos_to(file, feiticos, n2);
                fclose(file);
                printf("%d spells successfully saved.\n", n2);
            }
           
        }
        else if (strcmp(comando, "DELETE") == 0)
        {
            if (sscanf(linha, "%29s \"%49[^\"] \"", comando, nome_feitico) != 2)
            {
                printf("Invalid command arguments!\n");
                continue;
            }
           
            feitico_delete = find_feitico(feiticos, n2, nome_feitico);
            if (feitico_delete != NULL)
            {
                n2 = delete_feitico(feiticos, n2, nome_feitico);
                feiticos_vista = atualizar_vista(&num_vista, feiticos, n2);
                printf("Spell deleted.\n");
               
            }
            else
            {
                printf("No such spell exists!\n");
            }
           
        }
        else if (strcmp(comando, "FILTER") == 0)
        {
            char membro[MAX_CHARS];  
            int valor1, valor2;
           
            if (sscanf(linha, "%29s %99s %d %d", comando, membro, &valor1, &valor2) != 4 || (strcmp(membro, "lvl") != 0 && strcmp(membro, "ran") != 0 && strcmp(membro, "dur") != 0))
            {
                printf("Invalid command arguments!\n");
                continue;
            }
            //printf("Comando: %s, membro: %s, valor_1: %d, valor_2: %d\n", comando, membro, valor1, valor2); // debug para ver se esta a ler correto
            int tamanho_nova_vista = 0;
            Feitico **feiticos_filtrados = (Feitico**)malloc(num_vista * sizeof(Feitico*));
   
            if (strcmp(membro, "lvl") == 0)
            {
                tamanho_nova_vista = filter_feiticos_between(feiticos_vista, feiticos_filtrados, num_vista, select_lvl, valor1, valor2);
            }
            else if (strcmp(membro, "ran") == 0)
            {
                tamanho_nova_vista = filter_feiticos_between(feiticos_vista, feiticos_filtrados, num_vista, select_ran, valor1, valor2);
            }
            else if (strcmp(membro, "dur") == 0)
            {
                tamanho_nova_vista = filter_feiticos_between(feiticos_vista, feiticos_filtrados, num_vista, select_dur, valor1, valor2);
            }
           
            printf("View filtered. %d spells selected.\n", tamanho_nova_vista);
            feiticos_vista = atualizar_vista(&num_vista, feiticos_filtrados, tamanho_nova_vista);
            free(feiticos_filtrados);
        }
        else if (strcmp(comando, "PRINT") == 0)
        {
            if (sscanf(linha, "%29s \"%49[^\"] \"", comando, nome_feitico) != 2) //-> \"%49[^\"] \" -> é usado para ler oq estiver dentro de "" ate encontrar um \n
            {
                printf("Invalid command arguments!\n");
                continue;
            }

            Feitico* feitico_print = find_feitico(feiticos, n2, nome_feitico);
            if (feitico_print != NULL)
            {
                println_feitico(feitico_print);
            }
            else
            {
                printf("No such spell exists!\n");
            }
        }
        else if (strcmp(comando, "ADD") == 0)
        {
            Feitico* feitico_add = read_feitico_from(stdin);
            if (feitico_add != NULL) //quer dizer que criou o feitico
            {
                Feitico* duplicado = find_feitico(feiticos, n2, feitico_add->name);
                if (duplicado != NULL) //nome existe
                {
                    printf("Cannot create duplicate spell: %s!\n", feitico_add->name);
                    free_feitico(feitico_add);
                }
                else
                {
                    feiticos = (Feitico**)realloc(feiticos, (n2 + 1 ) * sizeof(Feitico*)); //realocar mem para por o feitico no fim do array de feiticos
                    feiticos[n2] = feitico_add; //por no fim do arrays de feitiços
                    n2++; //atualizar o n2
                    printf("Spell successfully added.\n");
                    feiticos_vista = atualizar_vista(&num_vista, feiticos, n2);
                }
               
            }
        }
        else if (strcmp(comando, "LIST") == 0)
        {
            int numero;
            if (sscanf(linha, "%29s %d", comando, &numero) == 1)
            {
                //printf("%d\n", num_vista); // ->debug
                println_feiticos(feiticos_vista, num_vista);
            }
            else
            {
                if (numero > num_vista)
                {
                    numero = num_vista;
                }
                for (int i = 0; i < numero; i++)
                {
                    println_feitico(feiticos_vista[i]);
                }
            }
        }
        else if (strcmp(comando, "ORDER") == 0)
        {
            char membro[MAX_CHARS];
            char direcao[MAX_CHARS];
            if (sscanf(linha, "%29s %99s %99s", comando, membro, direcao) != 3)
            {
                printf("Invalid command arguments!\n");
                continue;
            }
           
            if (strcmp(membro, "nam") == 0 && strcmp(direcao, "ASC") == 0)
            {
                qsort(feiticos_vista, num_vista, sizeof(Feitico *), (Comparer)compare_feitico_name_asc); //fiz o cast (Comparer) pq o qsort so aceita const void
                printf("%d spells ordered.\n", num_vista);
            }
            else if (strcmp(membro, "nam") == 0 && strcmp(direcao, "DES") == 0)
            {
                qsort(feiticos_vista, num_vista, sizeof(Feitico *), (Comparer)compare_feitico_name_des);
                printf("%d spells ordered.\n", num_vista);

            }
            else if (strcmp(membro, "lvl") == 0 && strcmp(direcao, "ASC") == 0)
            {
                qsort(feiticos_vista, num_vista, sizeof(Feitico *), (Comparer)compare_feitico_lvl_asc);
                printf("%d spells ordered.\n", num_vista);
            }
            else if (strcmp(membro, "lvl") == 0 && strcmp(direcao, "DES") == 0)
            {
                qsort(feiticos_vista, num_vista, sizeof(Feitico *), (Comparer)compare_feitico_lvl_des);
                printf("%d spells ordered.\n", num_vista);
            }
            else{
                printf("Invalid command arguments!\n");
            }
        }
        else if (strcmp(comando, "RESET") == 0)
        {
            feiticos_vista = atualizar_vista(&num_vista, feiticos, n2);
            printf("View reset. %d spells selected.\n", num_vista);
        }
        else if (strcmp(comando, "SAVEVIEW") == 0)
        {
            if (sscanf(linha, "%29s %49[^\n]", comando, nome_ficheiro) != 2) //para ler com aspas \""\ <-
            {
                printf("Invalid command arguments!\n");
                continue;
            }

            FILE* file = fopen(nome_ficheiro, "w");
            if (file == NULL)
            {
                printf("Error opening or writing file!\n");
            }
            else
            {
                write_feiticos_to(file, feiticos_vista, num_vista);
                fclose(file);
                printf("%d spells successfully saved.\n", num_vista);
            }
        }
        else if (strcmp(comando, "COPY") == 0)
        {
            if (sscanf(linha, "%29s \"%49[^\"] \" \"%49[^\"] \"", comando, nome_feitico, novo_nome_2) != 3)
            {
                printf("Invalid command arguments!\n");
                continue;
            }
           
            feitico_copy = find_feitico(feiticos, n2, nome_feitico);
            if (feitico_copy != NULL)
            {
                Feitico* nome_existente;
                nome_existente = find_feitico(feiticos, n2, novo_nome_2);
                if (nome_existente != NULL) //quer dizer que o nome existe
                {
                    printf("Cannot create duplicate spell: %s!\n", novo_nome_2);
                }
                else{
                    Feitico* novo_feitico = copy_feitico(feitico_copy);
                    feiticos = (Feitico**)realloc(feiticos, (n2 + 1 ) * sizeof(Feitico*)); //realocar mem para por o feitico no fim do array de feiticos
                    feiticos[n2] = novo_feitico; //por no fim do arrays de feitiços
                    n2++; //aumentar o tamanho do n2
                    strcpy(novo_feitico->name, novo_nome_2); //atualizar o nome do feitico que acabou de ser guardado
                    feiticos_vista = atualizar_vista(&num_vista, feiticos, n2);
                }
            }
            else{
                printf("No such spell exists!\n");
            }
        }
        else
        {
            printf("Unknown command!\n");
        }
        //printf("%d\n", num_vista); //debug para ver o numero de feiticos em num_vista
    }

    for (int i = 0; i < n2; i++)
    {
        free_feitico(feiticos[i]); //para limpar todos os feiticos dentro do array
    }
    if (feiticos != NULL) free(feiticos); //limpar o array  
    free(feiticos_vista); //limpar no fim os feiticos em vista
}

//o mooshak ignora esta parte
#ifndef MOOSHAK_MAIN
int main(void){
    runSMS();
    print_memory_leak_report();
    return 0;
}
#endif