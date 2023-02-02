#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "linked_list.h"
#include "mbstrings.h"

/** Updates the game by a single step, and modifies the game information
 * accordingly. Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: width of the board.
 *  - height: height of the board.
 *  - snake_p: pointer to your snake struct (not used until part 2!)
 *  - input: the next input.
 *  - growing: 0 if the snake does not grow on eating, 1 if it does.
 */
/*void update(int* cells, size_t width, size_t height, snake_t* snake_p,
            enum input_key input, int growing) {
    // `update` should update the board, your snake's data, and global
    // variables representing game information to reflect new state. If in the
    // updated position, the snake runs into a wall or itself, it will not move
    // and global variable g_game_over will be 1. Otherwise, it will be moved
    // to the new position. If the snake eats food, the game score (`g_score`)
    // increases by 1. This function assumes that the board is surrounded by
    // walls, so it does not handle the case where a snake runs off the board.
    int curr_posn = width*(snake_p->y_pos) + snake_p->x_pos;

    if (input != INPUT_NONE) {
        snake_p->direction = input;
    }

    if (snake_p->direction == INPUT_RIGHT) {
        printf("%s\n", "R");
        if (cells[curr_posn + 1] == FLAG_WALL) {
            printf("%s\n", "Err1");
            g_game_over = 1;
        }
        else if (cells[curr_posn + 1] == FLAG_FOOD) {
            cells[curr_posn] = FLAG_PLAIN_CELL;
            cells[curr_posn + 1] = FLAG_SNAKE;
            snake_p->x_pos += 1;
            g_score += 1;
            place_food(cells, width, height);
        }
        else {
            cells[curr_posn] = FLAG_PLAIN_CELL;
            cells[curr_posn + 1] = FLAG_SNAKE;
            snake_p->x_pos += 1;
        }

    }
    
    else if (snake_p->direction == INPUT_DOWN) {
        printf("%s\n", "D");
        if (cells[curr_posn + 20] == FLAG_WALL) {
            printf("%s\n", "Err2");
            g_game_over = 1;
        }
        else if (cells[curr_posn + 20] == FLAG_FOOD) {
            cells[curr_posn] = FLAG_PLAIN_CELL;
            cells[curr_posn + 20] = FLAG_SNAKE;
            snake_p->y_pos += 1;
            g_score += 1;
            place_food(cells, width, height);
        }
        else {
            cells[curr_posn] = FLAG_PLAIN_CELL;
            cells[curr_posn + 20] = FLAG_SNAKE;
            snake_p->y_pos += 1;
        }
    }
    
    else if (snake_p->direction == INPUT_UP) {
        printf("%s\n", "U");
        if (cells[curr_posn - 20] == FLAG_WALL) {
            printf("%s\n", "Err3");
            g_game_over = 1;
        }
        else if (cells[curr_posn - 20] == FLAG_FOOD) {
            cells[curr_posn] = FLAG_PLAIN_CELL;
            cells[curr_posn - 20] = FLAG_SNAKE;
            snake_p->y_pos -= 1;
            g_score += 1;
            place_food(cells, width, height);
        }
        else {
            cells[curr_posn] = FLAG_PLAIN_CELL;
            cells[curr_posn - 20] = FLAG_SNAKE;
            snake_p->y_pos -= 1;
        }
    }
    
    else if (snake_p->direction == INPUT_LEFT) {
        printf("%s\n", "L");
        if (cells[curr_posn - 1] == FLAG_WALL) {
            printf("%s\n", "Err4");
            g_game_over = 1;
        }
        else if (cells[curr_posn - 1] == FLAG_FOOD) {
            cells[curr_posn] = FLAG_PLAIN_CELL;
            cells[curr_posn - 1] = FLAG_SNAKE;
            snake_p->x_pos -= 1;
            g_score += 1;
            place_food(cells, width, height);
        }
        else {
            cells[curr_posn] = FLAG_PLAIN_CELL;
            cells[curr_posn - 1] = FLAG_SNAKE;
            snake_p->x_pos -= 1;
        }
    }
    // TODO: implement!
}*/

void update(int* cells, size_t width, size_t height, snake_t* snake_p,
            enum input_key input, int growing) {
    // `update` should update the board, your snake's data, and global
    // variables representing game information to reflect new state. If in the
    // updated position, the snake runs into a wall or itself, it will not move
    // and global variable g_game_over will be 1. Otherwise, it will be moved
    // to the new position. If the snake eats food, the game score (`g_score`)
    // increases by 1. This function assumes that the board is surrounded by
    // walls, so it does not handle the case where a snake runs off the board.
    int* posn_p = snake_p->posn->data;
    int curr_posn = *posn_p;

    if (input != INPUT_NONE) {
        snake_p->direction = input;
    }

    if (snake_p->direction == INPUT_RIGHT) {
        printf("%s\n", "R");
        if (cells[curr_posn + 1] == FLAG_WALL) {
            printf("%s\n", "Err1");
            g_game_over = 1;
        }
        else if (cells[curr_posn + 1] == FLAG_SNAKE) {
            g_game_over = 1;
        }
        else if (cells[curr_posn + 1] == FLAG_FOOD) {
            int snake_posn = curr_posn + 1;
            insert_first(&(snake_p->posn), &snake_posn, sizeof(int));

            cells[curr_posn + 1] = FLAG_SNAKE;
            g_score += 1;
            place_food(cells, width, height);
        }
        else {
            int snake_posn = curr_posn + 1;
            insert_first(&(snake_p->posn), &snake_posn, sizeof(int));

            int* last_p = get_last(snake_p->posn);
            cells[*last_p] = FLAG_PLAIN_CELL;
            remove_last(&(snake_p->posn));

            cells[curr_posn + 1] = FLAG_SNAKE;
        }

    }
    
    else if (snake_p->direction == INPUT_DOWN) {
        printf("%s\n", "D");
        if (cells[curr_posn + width] == FLAG_WALL || cells[curr_posn + width] == FLAG_SNAKE) {
            printf("%s\n", "Err2");
            g_game_over = 1;
        }
        else if (cells[curr_posn + width] == FLAG_FOOD) {
            int snake_posn = curr_posn + width;
            insert_first(&(snake_p->posn), &snake_posn, sizeof(int));

            cells[curr_posn + width] = FLAG_SNAKE;
            g_score += 1;
            place_food(cells, width, height);
        }
        else {
            int snake_posn = curr_posn + width;
            insert_first(&(snake_p->posn), &snake_posn, sizeof(int));

            int* last_p = get_last(snake_p->posn);
            cells[*last_p] = FLAG_PLAIN_CELL;
            remove_last(&(snake_p->posn));

            cells[curr_posn + width] = FLAG_SNAKE;
        }
    }
    
    else if (snake_p->direction == INPUT_UP) {
        printf("%s\n", "U");
        if (cells[curr_posn - width] == FLAG_WALL || cells[curr_posn - width] == FLAG_SNAKE) {
            printf("%s\n", "Err3");
            g_game_over = 1;
        }
        else if (cells[curr_posn - width] == FLAG_FOOD) {
            int snake_posn = curr_posn - width;
            insert_first(&(snake_p->posn), &snake_posn, sizeof(int));

            cells[curr_posn - width] = FLAG_SNAKE;
            g_score += 1;
            place_food(cells, width, height);
        }
        else {
            int snake_posn = curr_posn - width;
            insert_first(&(snake_p->posn), &snake_posn, sizeof(int));

            int* last_p = get_last(snake_p->posn);
            cells[*last_p] = FLAG_PLAIN_CELL;
            remove_last(&(snake_p->posn));

            cells[curr_posn - width] = FLAG_SNAKE;
        }
    }
    
    else if (snake_p->direction == INPUT_LEFT) {
        printf("%s\n", "L");
        if (cells[curr_posn - 1] == FLAG_WALL || cells[curr_posn - 1] == FLAG_SNAKE) {
            printf("%s\n", "Err4");
            g_game_over = 1;
        }
        else if (cells[curr_posn - 1] == FLAG_FOOD) {
            int snake_posn = curr_posn - 1;
            insert_first(&(snake_p->posn), &snake_posn, sizeof(int));

            cells[curr_posn - 1] = FLAG_SNAKE;
            g_score += 1;
            place_food(cells, width, height);
        }
        else {
            int snake_posn = curr_posn - 1;
            insert_first(&(snake_p->posn), &snake_posn, sizeof(int));
            
            int* last_p = get_last(snake_p->posn);
            cells[*last_p] = FLAG_PLAIN_CELL;
            remove_last(&(snake_p->posn));

            cells[curr_posn - 1] = FLAG_SNAKE;
        }
    }
    // TODO: implement!
}

/** Sets a random space on the given board to food.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - width: the width of the board
 *  - height: the height of the board
 */
void place_food(int* cells, size_t width, size_t height) {
    /* DO NOT MODIFY THIS FUNCTION */
    unsigned food_index = generate_index(width * height);
    if (*(cells + food_index) == FLAG_PLAIN_CELL) {
        *(cells + food_index) = FLAG_FOOD;
    } else {
        place_food(cells, width, height);
    }
    /* DO NOT MODIFY THIS FUNCTION */
}

/** Prompts the user for their name and saves it in the given buffer.
 * Arguments:
 *  - `write_into`: a pointer to the buffer to be written into.
 */
void read_name(char* write_into) {
    // TODO: implement! (remove the call to strcpy once you begin your
    // implementation)
    strcpy(write_into, "placeholder");
}

/** Cleans up on game over — should free any allocated memory so that the
 * LeakSanitizer doesn't complain.
 * Arguments:
 *  - cells: a pointer to the first integer in an array of integers representing
 *    each board cell.
 *  - snake_p: a pointer to your snake struct. (not needed until part 2)
 */
void teardown(int* cells, snake_t* snake_p) {
    // TODO: implement!
    free(cells);
}
