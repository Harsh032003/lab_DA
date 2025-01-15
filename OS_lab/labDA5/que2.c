#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 10

typedef struct
{
    int blocks[MAX_BLOCKS];
    int block_count;
} SequentialFile;

typedef struct
{
    int index_block;
    int blocks[MAX_BLOCKS];
} IndexedFile;

typedef struct LinkedBlock
{
    int block_number;
    struct LinkedBlock *next;
} LinkedBlock;

typedef struct
{
    LinkedBlock *head;
} LinkedFile;

void allocate_sequential(SequentialFile *file, int start_block, int block_count)
{
    file->block_count = block_count;
    for (int i = 0; i < block_count; i++)
    {
        file->blocks[i] = start_block + i;
    }
}

void display_sequential(const SequentialFile *file)
{
    printf("Sequential Allocation:\nBlocks: ");
    for (int i = 0; i < file->block_count; i++)
    {
        printf("%d ", file->blocks[i]);
    }
    printf("\n");
}

void allocate_indexed(IndexedFile *file, int index_block, int *data_blocks, int block_count)
{
    file->index_block = index_block;
    for (int i = 0; i < block_count; i++)
    {
        file->blocks[i] = data_blocks[i];
    }
}

void display_indexed(const IndexedFile *file, int block_count)
{
    printf("Indexed Allocation:\nIndex Block: %d\nBlocks: ", file->index_block);
    for (int i = 0; i < block_count; i++)
    {
        printf("%d ", file->blocks[i]);
    }
    printf("\n");
}

void allocate_linked(LinkedFile *file, int *blocks, int block_count)
{
    LinkedBlock *current = NULL;
    for (int i = 0; i < block_count; i++)
    {
        LinkedBlock *new_block = (LinkedBlock *)malloc(sizeof(LinkedBlock));
        new_block->block_number = blocks[i];
        new_block->next = NULL;
        if (file->head == NULL)
        {
            file->head = new_block;
            current = file->head;
        }
        else
        {
            current->next = new_block;
            current = current->next;
        }
    }
}

void display_linked(const LinkedFile *file)
{
    printf("Linked Allocation:\nBlocks: ");
    LinkedBlock *current = file->head;
    while (current != NULL)
    {
        printf("%d ", current->block_number);
        current = current->next;
    }
    printf("\n");
}

void free_linked(LinkedFile *file)
{
    LinkedBlock *current = file->head;
    while (current != NULL)
    {
        LinkedBlock *temp = current;
        current = current->next;
        free(temp);
    }
    file->head = NULL;
}

int main()
{
    int start_block, block_count;

    SequentialFile seq_file;
    printf("Enter start block and number of blocks for Sequential Allocation: ");
    scanf("%d %d", &start_block, &block_count);
    allocate_sequential(&seq_file, start_block, block_count);
    display_sequential(&seq_file);

    IndexedFile idx_file;
    int idx_block, idx_block_count;
    printf("Enter index block and number of data blocks for Indexed Allocation: ");
    scanf("%d %d", &idx_block, &idx_block_count);
    int idx_blocks[idx_block_count];
    printf("Enter the data blocks: ");
    for (int i = 0; i < idx_block_count; i++)
    {
        scanf("%d", &idx_blocks[i]);
    }
    allocate_indexed(&idx_file, idx_block, idx_blocks, idx_block_count);
    display_indexed(&idx_file, idx_block_count);

    LinkedFile lnk_file = {NULL};
    int lnk_block_count;
    printf("Enter the number of blocks for Linked Allocation: ");
    scanf("%d", &lnk_block_count);
    int lnk_blocks[lnk_block_count];
    printf("Enter the blocks: ");
    for (int i = 0; i < lnk_block_count; i++)
    {
        scanf("%d", &lnk_blocks[i]);
    }
    allocate_linked(&lnk_file, lnk_blocks, lnk_block_count);
    display_linked(&lnk_file);
    free_linked(&lnk_file);

    return 0;
}
