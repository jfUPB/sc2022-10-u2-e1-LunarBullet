#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef DOLOG
#define LOG(...) fprintf(log, __VA_ARGS__);
#else
#define LOG(...)
#endif

struct array
{
    int *pdata;
    int size;
};

void initArray(struct array *);
void getArray(struct array *);
void arrayCommon(struct array *, struct array *, struct array *);
void printArray(struct array *);
void freeMemory(struct array *, struct array *, struct array *);

void initArray(struct array *arr){
    arr->pdata = NULL;
    arr->size = -1;
}

void printArray(struct array *parr)
{
    for (int i = 0; i < parr->size; i++)
    {
        printf("%d ", parr->pdata[i]);
    }
    printf("\n");
}

void getArray(struct array *parr)
{
    char numbersToRead[60];
    int arraySize = 0;

    fgets(numbersToRead, 60, stdin); // lee datos 

    numbersToRead[strlen(numbersToRead) -1 ] = 0; //encuentra el tamano de la chain de chars del terminal
    sscanf(numbersToRead,"%d", &arraySize); // guarda el tamano del array
    
    parr->size=arraySize;

    parr->pdata = malloc(sizeof(int)*arraySize);

    //asigno los valores

    for (int i = 0; i < arraySize; i++)
    {
        if(fgets(numbersToRead,60, stdin)!=NULL)
        {
            sscanf(numbersToRead," %d ", parr->pdata+i);
        }
    }
    
    
}

void arrayCommon(struct array *arrIn1, struct array *arrIn2, struct array *arrOut)
{
    int arraySize = 0;
    int arrayElements[60];

    int repeatedChecker;

    int repeatedCounter=0;

    int a, b, c; //for removing repeated/duplicates


    //analizamos y guardamos si hay valores en comun (nested loop)
    for (size_t i = 0; i < arrIn1->size; i++) //recorremos array1
    {
        for (size_t j = 0; j < arrIn2->size; j++) //recorremos arr2 entero por cada valor de arr1
        {
            if (arrIn1->pdata[i]==arrIn2->pdata[j]) //por cada elemento i comparamos todos los elementos j
            {                                       //de manera que asi sabremos si hay elementos en comun
                repeatedChecker=arrIn1->pdata[j];
                arraySize++;
                arrayElements[i]=arrIn1->pdata[i];    //this will give us the raw duplicated numbers       
            }
        }
    }

    //remove duplicates logic
   for ( a = 0; a < arraySize; a ++)  
    {  
        for ( b = a + 1; b < arraySize; b++)  
        {  
            // use if statement to check duplicate element  
            if ( arrayElements[a] == arrayElements[b])  
            {  
                // delete the current position of the duplicate element  
                for ( c = b; c < arraySize - 1; c++)  
                {  
                    arrayElements[c] = arrayElements [c + 1];  
                }  
                // decrease the size of array after removing duplicate element  
                arraySize--;  
                  
            // if the position of the elements is changes, don't increase the index j  
                b--;      
            }  
        }  
    }  
   

    //we assign then the proccesed data
    arrOut->size=arraySize;
    arrOut->pdata = malloc(sizeof(int)*arraySize);

    for (int i = 0; i < arraySize; i++)
    {
       arrOut->pdata[i]=arrayElements[i];
    }
    

}

void freeMemory(struct array *arr1, struct array *arr2, struct array *arr3)
{
    free(arr1->pdata);
    free(arr1);

    free(arr2->pdata);
    free(arr2);

    free(arr3->pdata);
    free(arr3);
}

int main(void)
{

#ifdef DOLOG
    FILE *log = fopen("log", "w");
    if (log == NULL)
    {
        perror("log file creation fails: ");
        return EXIT_FAILURE;
    }
#endif

    char commandBuf[64];

    LOG("creating an object for each array\n");

    struct array *arr1 = malloc(sizeof(struct array) * 1);
    initArray(arr1);
    struct array *arr2 = malloc(sizeof(struct array) * 1);
    initArray(arr2);    
    struct array *arr3 = malloc(sizeof(struct array) * 1);
    initArray(arr3);


    LOG("Init command loop\n");

    while (fgets(commandBuf, sizeof(commandBuf), stdin) != NULL)
    {
        commandBuf[strlen(commandBuf) - 1] = 0;

        if (strncmp(commandBuf, "arr1", strlen("arr1")) == 0)
        {
            LOG("getting array1\n");
            getArray(arr1);
        }
        else if (strncmp(commandBuf, "arr2", strlen("arr2")) == 0)
        {
            LOG("getting array2\n");
            getArray(arr2);
        }
        else if (strncmp(commandBuf, "printArr1", strlen("printArr1")) == 0)
        {
            LOG("printing arr1\n");
            printArray(arr1);
        }
        else if (strncmp(commandBuf, "printArr2", strlen("printArr2")) == 0)
        {
            LOG("printing arr2\n");
            printArray(arr2);
        }
        else if (strncmp(commandBuf, "compare", strlen("compare")) == 0)
        {
            LOG("Compare arrays\n");
            arrayCommon(arr1, arr2, arr3);
        }
        else if (strncmp(commandBuf, "printResult", strlen("printResult")) == 0)
        {
            LOG("printing compare result\n");
            printf("%d\n", arr3->size);
            if (arr3->size != 0)
            {
                printArray(arr3);
            }
        }
        else if (strncmp(commandBuf, "exit", strlen("exit")) == 0)
        {
            LOG("running exit command\n");
            freeMemory(arr1,arr2,arr3);
            break;
        }
    }

    return EXIT_SUCCESS;
}
