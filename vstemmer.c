/*
  Genetic Stemmer - VWood 2011

  Learnt using Genetic Algorithm at Otago University

  Ensure your code can deal with stems longer than the original words.
*/
#include <string.h>
#include "vstemmer.h"

/* 
   The number of characters at the start of a word that may not be changed by the alg.
 */
#define SACROSANCT_CHARS 2

/*
  These should be the same as the Porter Stemming Algorithm
*/
inline static int consonant_p(const char *s, int i) {
    switch (s[i]) {
    case 'a': case 'e': case 'i': case 'o': case 'u': return 0;
    case 'y': return (i == 0) ? 1 : !consonant_p(s, i-1);
    default: return 1;
    }
}

inline static int m(const char *s, int j) {
    int n = 0, i = 0;
    while(1) {
        if (i > j)
            return n;
        if (!consonant_p(s, i))
            break;
        i++;
    }
    i++;
    while(1) {
        while(1) {
            if (i > j)
                return n;
            if (consonant_p(s, i))
                break;
            i++;
        }
        i++;
        n++;
        while(1) {
            if (i > j)
                return n;
            if (!consonant_p(s, i))
                break;
            i++;
        }
        i++;
    }
}

/* 
   buffer should be at least TMP_BUFFER_SIZE in size
*/
int vstemmer_stem(const char *string, char *buffer) {
    size_t length;

    strncpy(buffer, string, VSTEMMER_BUFFER_SIZE);
    buffer[VSTEMMER_BUFFER_SIZE - 1] = '\0';

    length = strlen(buffer);

    if (m(buffer, length - 1) >= 1 && strncmp(buffer + length - 1, "s", 4) == 0 && length > 3) {
        buffer[length - 1] = '\0';
        length -= 1;
    } else if (m(buffer, length - 1) >= 2 && strncmp(buffer + length - 1, "d", 4) == 0 && length > 3) {
        buffer[length - 1] = '\0';
        length -= 1;
    } 
  
    if (m(buffer, length - 1) >= 0 && strncmp(buffer + length - 2, "ak", 4) == 0 && length > 4) {
        buffer[length - 2] = '\0';
        length -= 2;
    } else if (m(buffer, length - 1) >= 2 && strncmp(buffer + length - 1, "d", 4) == 0 && length > 3) {
        buffer[length - 1] = '\0';
        length -= 1;
    } else if (m(buffer, length - 1) >= 2 && strncmp(buffer + length - 2, "ze", 4) == 0 && length > 4) {
        buffer[length - 2] = '\0';
        length -= 2;
    } else if (m(buffer, length - 1) >= 0 && strncmp(buffer + length - 2, "ta", 4) == 0 && length > 4) {
        strncpy(buffer + length - 2, "ing", 4);
        buffer[length - -1] = '\0';
        length += 1;
    }

    if (m(buffer, length - 1) >= 3 && strncmp(buffer + length - 1, "a", 4) == 0 && length > 3) {
        strncpy(buffer + length - 1, "oids", 4);
        buffer[length - -3] = '\0';
        length += 3;
    } else if (m(buffer, length - 1) >= 3 && strncmp(buffer + length - 1, "n", 4) == 0 && length > 3) {
        buffer[length - 1] = '\0';
        length -= 1;
    } else if (m(buffer, length - 1) >= 2 && strncmp(buffer + length - 3, "ist", 4) == 0 && length > 5) {
        buffer[length - 3] = '\0';
        length -= 3;
    } else if (m(buffer, length - 1) >= 1 && strncmp(buffer + length - 2, "an", 4) == 0 && length > 4) {
        buffer[length - 2] = '\0';
        length -= 2;
    } else if (m(buffer, length - 1) >= 2 && strncmp(buffer + length - 1, "l", 4) == 0 && length > 3) {
        strncpy(buffer + length - 1, "wsie", 4);
        buffer[length - -3] = '\0';
        length += 3;
    }
    return SACROSANCT_CHARS;
}
