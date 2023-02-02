#include "game_setup.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ALLOWED TO INCLUDE THIS? >:)
# include <ctype.h> 
//////////////////////////////////
///////////////////////////////

// Some handy dandy macros for decompression
#define E_CAP_HEX 0x45
#define E_LOW_HEX 0x65
#define S_CAP_HEX 0x53
#define S_LOW_HEX 0x73
#define W_CAP_HEX 0x57
#define W_LOW_HEX 0x77
#define DIGIT_START 0x30
#define DIGIT_END 0x39

/** Initializes the board with walls around the edge of the board.
 *
 * Modifies values pointed to by cells_p, width_p, and height_p and initializes
 * cells array to reflect this default board.
 *
 * Returns INIT_SUCCESS to indicate that it was successful.
 *
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 */
enum board_init_status initialize_default_board(int** cells_p, size_t* width_p,
                                                size_t* height_p) {
    *width_p = 20;
    *height_p = 10;
    int* cells = malloc(20 * 10 * sizeof(int));
    *cells_p = cells;
    for (int i = 0; i < 20 * 10; i++) {
        cells[i] = FLAG_PLAIN_CELL;
    }

    // Set edge cells!
    // Top and bottom edges:
    for (int i = 0; i < 20; ++i) {
        cells[i] = FLAG_WALL;
        cells[i + (20 * (10 - 1))] = FLAG_WALL;
    }
    // Left and right edges:
    for (int i = 0; i < 10; ++i) {
        cells[i * 20] = FLAG_WALL;
        cells[i * 20 + 20 - 1] = FLAG_WALL;
    }

    // Add snake
    cells[20 * 2 + 2] = FLAG_SNAKE;

    return INIT_SUCCESS;
}

/** Initialize variables relevant to the game board.
 * Arguments:
 *  - cells_p: a pointer to a memory location where a pointer to the first
 *             element in a newly initialized array of cells should be stored.
 *  - width_p: a pointer to a memory location where the newly initialized
 *             width should be stored.
 *  - height_p: a pointer to a memory location where the newly initialized
 *              height should be stored.
 *  - snake_p: a pointer to your snake struct (not used until part 2!)
 *  - board_rep: a string representing the initial board. May be NULL for
 * default board.
 */
enum board_init_status initialize_game(int** cells_p, size_t* width_p,
                                       size_t* height_p, snake_t* snake_p,
                                       char* board_rep) {
    // TODO: implement!
    if (board_rep == NULL) {
        initialize_default_board(cells_p, width_p, height_p);

        int init_posn = 2 + (2* *width_p);
        node_t* init_node = malloc(sizeof(node_t));
        init_node->data = malloc(sizeof(int));
        memcpy(init_node->data, &init_posn, sizeof(int));
        init_node->prev = NULL;
        init_node->next = NULL;

        snake_p->posn = init_node;
        snake_p->direction = INPUT_RIGHT;
        /*snake_p->x_pos = 2;
        snake_p->y_pos = 2;
        snake_p->direction = INPUT_RIGHT;*/
        place_food(*cells_p, *width_p, *height_p);
        return INIT_SUCCESS;
    }
    else {
        enum board_init_status status = decompress_board_str(cells_p, width_p, height_p,
                        snake_p, board_rep);
        snake_p->direction = INPUT_RIGHT;
        place_food(*cells_p, *width_p, *height_p);
        return status;
    }
}

/** Takes in a string `compressed` and initializes values pointed to by
 * cells_p, width_p, and height_p accordingly. Arguments:
 *      - cells_p: a pointer to the pointer representing the cells array
 *                 that we would like to initialize.
 *      - width_p: a pointer to the width variable we'd like to initialize.
 *      - height_p: a pointer to the height variable we'd like to initialize.
 *      - snake_p: a pointer to your snake struct (not used until part 2!)
 *      - compressed: a string that contains the representation of the board.
 * Note: We assume that the string will be of the following form:
 * B24x80|E5W2E73|E5W2S1E72... To read it, we scan the string row-by-row
 * (delineated by the `|` character), and read out a letter (E, S or W) a number
 * of times dictated by the number that follows the letter.
 */

enum board_init_status decompress_board_str(int** cells_p, size_t* width_p,
                                            size_t* height_p, snake_t* snake_p,
                                            char* compressed) {
    // pointer to index cells


    // retrieve dimensions
    if (*compressed != 'B') return INIT_ERR_BAD_CHAR;
    compressed++;
    
    *height_p = atoi(compressed);
    while (isdigit(*compressed)) {
        compressed++;
    }

    if (*compressed != 'x') return INIT_ERR_BAD_CHAR;
    compressed++;

    *width_p = (size_t) atoi(compressed);
    while (isdigit(*compressed)) {
        compressed++;
    }
    
    int* cells = malloc(*height_p * *width_p * sizeof(int));
    *cells_p = cells;

    int snake_pos = 0;
    int iterations;
    int snake_count = 0;
    size_t curr_width = 0;
    size_t curr_height = 0;

    printf("%s\n", "Height of the board: ");
    printf("%zu\n", *height_p);
    printf("%s\n", "Width of the board: ");
    printf("%zu\n", *width_p);
    
    compressed++;
    while (*compressed != '\0') {
        if (*compressed == '|') {
            printf("\n");
            if (curr_width != *width_p) return INIT_ERR_INCORRECT_DIMENSIONS;
            curr_height++;
            if (curr_height >= *height_p) return INIT_ERR_INCORRECT_DIMENSIONS;
            curr_width=0;
            compressed++;
        }
        if (*compressed == 'E') {
            compressed++;
            iterations = atoi(compressed);
            curr_width += iterations;
            while (isdigit(*compressed)) compressed++;
            for (int i = 0; i < iterations; i++) {
                printf("%c", 'E');
                (*cells_p)[snake_pos] = FLAG_PLAIN_CELL;
                snake_pos++;
                if ((size_t) snake_pos > *height_p * *width_p) return INIT_ERR_INCORRECT_DIMENSIONS;
            }
        }
        else if (*compressed == 'W') {
            compressed++;
            iterations = atoi(compressed);
            curr_width += iterations;
            while (isdigit(*compressed)) compressed++;
            for (int i = 0; i < iterations; i++) {
                printf("%c", 'W');
                (*cells_p)[snake_pos] = FLAG_WALL;
                snake_pos++;
                if ((size_t) snake_pos > *height_p * *width_p) return INIT_ERR_INCORRECT_DIMENSIONS;
            }
        }
        else if (*compressed == 'S') {
            int init_posn = snake_pos;
            // added part
            node_t* init_node = malloc(sizeof(node_t));
            init_node->data = malloc(sizeof(int));
            memcpy(init_node->data, &init_posn, sizeof(int));
            init_node->prev = NULL;
            init_node->next = NULL;

            snake_p->posn = init_node;
            // end added

            /*snake_p->x_pos = snake_pos % *width_p;
            snake_p->y_pos = snake_pos / (int) *width_p;*/
            compressed++;
            iterations = atoi(compressed);
            snake_count += iterations;
            curr_width += iterations;
            while (isdigit(*compressed)) compressed++;
            for (int i = 0; i < iterations; i++) {
                printf("%c", 'S');
                (*cells_p)[snake_pos] = FLAG_SNAKE;
                snake_pos++;
                if ((size_t) snake_pos > *height_p * *width_p) return INIT_ERR_INCORRECT_DIMENSIONS;
            }
        }
        else return INIT_ERR_BAD_CHAR;
    }
    printf("\n");
    if (curr_width != *width_p) return INIT_ERR_INCORRECT_DIMENSIONS;
    if (curr_height != *height_p - 1) return INIT_ERR_INCORRECT_DIMENSIONS;
    if (snake_count != 1) return INIT_ERR_WRONG_SNAKE_NUM;

    return INIT_SUCCESS;
}