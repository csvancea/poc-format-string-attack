// Example of exploitable format string: ./poc %d%d%d%d%d%d---%s
// The string may vary depending on the compiler+flags combo used.

// NOTE: Error checks were omitted for visibility reasons.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_FILE "key"

static char* load_key(void)
{
    char *key;
    FILE *fkey;
    size_t sz;

    fkey = fopen(KEY_FILE, "r");
    if (!fkey)
    {
        return NULL;
    }

    // Get the file size + 1 extra character for the NUL terminator
    fseek(fkey, 0, SEEK_END);
    sz = ftell(fkey) + 1;
    key = malloc(sz);
    rewind(fkey);

    // Read the key
    fgets(key, sz, fkey);
    fclose(fkey);
    return key;
};

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("  %s [password]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *key = load_key();
    char *input = argv[1];

    if (strcmp(key, input))
    {
        printf("Wrong password, keep trying!\n");

        // Log the attempt to stderr
        fprintf(stderr, input);
    }
    else
    {
        printf("Have fun!\n");
        system("sh");
    }

    free(key); // Pointless anyway
    return EXIT_SUCCESS;
}
