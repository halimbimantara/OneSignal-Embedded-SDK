#include "OSCharBuffer.h"
#include <string.h>

#define DEFAULT_BUFFER_SIZE 100
#define DEFAULT_GROWTH_INCREMENT 50

OSCharBuffer::OSCharBuffer()
{
    stringBuffer = (char*)calloc(DEFAULT_BUFFER_SIZE, sizeof(char));
    size = DEFAULT_BUFFER_SIZE;
    index = 0;
}

bool OSCharBuffer::growBuffer(char *text, size_t addSize)
{
    size_t newSize = (addSize * sizeof(char)) + (size * sizeof(char));

    stringBuffer = (char *)realloc(stringBuffer, newSize);

    size = addSize + size;

    return stringBuffer != NULL;
}

bool OSCharBuffer::addText(char *text)
{
    size_t freeSpace = size - index;
    size_t newTextSize = strlen(text) + 1;

    bool succeeded = false;

    if (newTextSize > freeSpace) {
        // buffer must be grown
        size_t growTo = DEFAULT_GROWTH_INCREMENT;

        if (newTextSize - freeSpace > DEFAULT_GROWTH_INCREMENT)
            growTo = newTextSize - freeSpace + DEFAULT_GROWTH_INCREMENT;
        

        succeeded = growBuffer(text, growTo);

        if (!succeeded) 
            return false;
    }

    strcat(stringBuffer, text);
    
    index += newTextSize - 1;
}