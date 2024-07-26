#include "../minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 800
#define HEIGHT 600
#define FRAME_DELAY 10

typedef struct s_player {
    void    *images[4];
    int     current_frame;
    int     total_frames;
    int     x, y;
    int     frame_counter;
} t_player;

void    load_player_images(t_player *player, void *mlx_ptr) {
    int width, height;

    player->total_frames = 4;
    player->images[0] = mlx_xpm_file_to_image(mlx_ptr, "walk_frame1.xpm", &width, &height);
    player->images[1] = mlx_xpm_file_to_image(mlx_ptr, "walk_frame2.xpm", &width, &height);
    player->images[2] = mlx_xpm_file_to_image(mlx_ptr, "walk_frame3.xpm", &width, &height);
    player->images[3] = mlx_xpm_file_to_image(mlx_ptr, "walk_frame4.xpm", &width, &height);
    player->current_frame = 0;
    player->frame_counter = 0;
    player->x = WIDTH / 2;
    player->y = HEIGHT / 2;
}

void    update_player_animation(t_player *player) {
    player->frame_counter++;
    if (player->frame_counter % FRAME_DELAY == 0) {
        player->current_frame = (player->current_frame + 1) % player->total_frames;
    }
}

void    draw_player(void *mlx_ptr, void *win_ptr, t_player *player) {
    mlx_clear_window(mlx_ptr, win_ptr);
    mlx_put_image_to_window(mlx_ptr, win_ptr, player->images[player->current_frame], player->x, player->y);
}

int     key_hook(int keycode, t_player *player) {
    if (keycode == 65307)  // ESC key to exit
        exit(0);
    else if (keycode == 119)  // W key to move up
        player->y -= 10;
    else if (keycode == 115)  // S key to move down
        player->y += 10;
    else if (keycode == 97)   // A key to move left
        player->x -= 10;
    else if (keycode == 100)  // D key to move right
        player->x += 10;

    return (0);
}

int     main_loop(void *mlx_ptr, void *win_ptr, t_player *player) {
    update_player_animation(player);
    draw_player(mlx_ptr, win_ptr, player);
    return (0);
}

int     main(void) {
    void        *mlx_ptr;
    void        *win_ptr;
    t_player    player;

    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Player Animation");

    load_player_images(&player, mlx_ptr);

    mlx_key_hook(win_ptr, (int (*)())key_hook, &player);
    mlx_loop_hook(mlx_ptr, (int (*)())main_loop, &player);
    mlx_loop(mlx_ptr);

    // Liberar recursos
    for (int i = 0; i < player.total_frames; i++) {
        mlx_destroy_image(mlx_ptr, player.images[i]);
    }
    mlx_destroy_window(mlx_ptr, win_ptr);
    mlx_destroy_display(mlx_ptr);
    free(mlx_ptr);

    return (0);
}
