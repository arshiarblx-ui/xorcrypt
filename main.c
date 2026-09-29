#include <stdio.h>
#include <direct.h> 
#include <string.h>

static void readLine(const char *prompt , char *buf , size_t size){
        printf("%s" , prompt);
         if (fgets(buf, (int)size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    buf[strcspn(buf,"\n")] = '\0';
}
static int xorFile(FILE *in, FILE *out, const char *key, size_t keyLen) {
    int byte;
    size_t k = 0;
     while ((byte = fgetc(in)) != EOF) {
        if (fputc(byte ^ (unsigned char)key[k], out) == EOF) {
            return -1;
        }
        k = (k + 1) % keyLen;
    }
    return ferror(in) ? -1 : 0;
}
int main(void){

int choice;
char line[16];
char inputFilename[100];
char outputFilename[100];
char password[100];


readLine("1. Encrypt\n2. Decrypt\nChoose: ", line, sizeof(line));
    if (sscanf(line, "%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        fprintf(stderr, "Invalid choice!\n");
        return 1;
    }

    printf(choice == 1 ? "Encrypting\n" : "Decrypting\n");

    readLine("Enter input filename: ", inputFilename, sizeof(inputFilename));
    readLine("Enter output filename: ", outputFilename, sizeof(outputFilename));
    readLine("Enter password: ", password, sizeof(password));

    size_t passwordLength = strlen(password);
    if (passwordLength == 0) {
        fprintf(stderr, "Password cannot be empty!\n");
        return 1;
    }
    if (strcmp(inputFilename, outputFilename) == 0) {
        fprintf(stderr, "Input and output must be different files!\n");
        return 1;
    }

    FILE *input = fopen(inputFilename, "rb");
    if (input == NULL) {
        fprintf(stderr, "Could not open input file!\n");
        return 1;
    }

    FILE *output = fopen(outputFilename, "wb");
    if (output == NULL) {
        fprintf(stderr, "Could not open output file!\n");
        fclose(input);
        return 1;
    }

    int result = xorFile(input, output, password, passwordLength);
    fclose(input);
    if (fclose(output) != 0) {
        result = -1;
    }

    if (result != 0) {
        fprintf(stderr, "Error while processing the file!\n");
        return 1;
    }

    printf("Done.\n");
    return 0;
}