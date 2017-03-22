#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifdef BACKLIGHT
    #define BPATH "/sys/class/backlight/intel_backlight/brightness"
    #define MPATH "/sys/class/backlight/intel_backlight/max_brightness"
    #define VALUE 69
#endif

#ifdef KBD
    #define BPATH "/sys/class/leds/smc::kbd_backlight/brightness"
    #define MPATH "/sys/class/leds/smc::kbd_backlight/max_brightness"
    #define VALUE 32
#endif

int get_length(FILE *fd) {
    int c = 0;
    int i = 0;
    while((c = fgetc(fd)) != '\n') {
        i++;
    }

    return i;
}

int get_brightness(int max){
    int c = 0;
    int i = 0;
    int brightness = 0;
    char *file;
    if (max) {
        file = malloc(strlen(MPATH));
        if(!file) {
            perror("malloc");
            exit(1);
        }
        strncpy(file, MPATH, strlen(MPATH));
    } else {
        file = malloc(strlen(BPATH));
        if(!file) {
            perror("malloc");
            exit(1);
        }
        strncpy(file, BPATH, strlen(BPATH));
    }
    FILE *fd = fopen(file, "r");
    if(!fd) {
        perror(file);
        exit(1);
    }
    int len = get_length(fd);
    rewind(fd);
    char buff[len+1];
    printf("Reading %s\n", file);
    while ((c = getc(fd)) != '\n') {
        buff[i] = c;
        i++;
    }
    free(file);
    fclose(fd);
    buff[i] = '\0';
    brightness = atoi(buff);

    return brightness;
}

int increase_brightness() {
    int current = get_brightness(0);
    int max = get_brightness(1);
    int new = 0;
    if(current + VALUE > max) {
        new = max;
    } else {
        new = current + VALUE;
    }
    FILE *fd = fopen(BPATH, "w");
    if(!fd) {
        perror(BPATH);
        exit(1);
    }
    printf("Writing new value in %s\n", BPATH);
    fprintf(fd, "%d\n", new);
    printf("Increased backlight by %d!\n", VALUE);
    fclose(fd);
}

int decrease_brightness() {
    int current = get_brightness(0);
    int new = 0;
    if(current - VALUE <= 0) {
        new = 0;
    } else {
        new = current - VALUE;
    }
    FILE *fd = fopen(BPATH, "w");
    if(!fd) {
        perror(BPATH);
        exit(1);
    }
    printf("Writing new value in %s\n", BPATH);
    fprintf(fd, "%d\n", new);
    printf("Decreased backlight by %d!\n", VALUE);
    fclose(fd);
}

void usage(char *name) {
    printf("%s [OPTIONS]\n\n", name);
    printf("\t-c\t display current setting\n");
    printf("\t-d\t decrease brightness\n");
    printf("\t-i\t increase brightness\n\n");
}

int main(int argc, char** argv) {
    if(argc < 2) {
        usage(argv[0]);
    } else if(!(strncmp(argv[1], "-c", 2))) {
        printf("Current setting: %d\n", get_brightness(0));
    } else if(!(strncmp(argv[1], "-i", 2))) {
        increase_brightness();
    } else if(!(strncmp(argv[1], "-d", 2))) {
        decrease_brightness();
    }
    return 0;
}
