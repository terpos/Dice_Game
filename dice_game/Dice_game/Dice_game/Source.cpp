#include <random>
#include <string>
#include <ctime>
#include <cstdlib>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>



int main()
{
	ALLEGRO_DISPLAY *Window;
	ALLEGRO_BITMAP *dice[6] = { NULL };	
	ALLEGRO_TIMER *timer = NULL;
	double fps = 60.0;

	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_mouse();

	Window = al_create_display(300, 300);

	ALLEGRO_FONT *font = al_load_font("arial.ttf", 16, 0);
	timer = al_create_timer(1 / fps);

	int x, y;

	dice[0] = al_load_bitmap("diceone.png");
	dice[1] = al_load_bitmap("dicetwo.png");
	dice[2] = al_load_bitmap("dicethree.png");
	dice[3] = al_load_bitmap("dicefour.png");
	dice[4] = al_load_bitmap("dicefive.png");
	dice[5] = al_load_bitmap("dicesix.png");

	srand(time(0));
	ALLEGRO_EVENT_QUEUE *ev = al_create_event_queue();
	
	al_register_event_source(ev, al_get_display_event_source(Window));
	al_register_event_source(ev, al_get_mouse_event_source());
	al_register_event_source(ev, al_get_timer_event_source(timer));

	al_start_timer(timer);

	int guessnum;
	int actnum;
	bool done = false;
	bool reveal = false;


	while (!done)
	{
		
		ALLEGRO_MOUSE_STATE mouse;
		ALLEGRO_EVENT e;
		al_wait_for_event(ev, &e);

		srand(time(0));

		if (e.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

		else if (e.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			x = e.mouse.x;
			y = e.mouse.y;
		}

		al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Pick any number from a six sided die");

		al_get_mouse_state(&mouse);

		al_draw_bitmap(dice[0], 40, 24, NULL);

		if (x > 40 && x < 90 && y > 24 && y < 74)
		{
			al_draw_tinted_bitmap(dice[0], al_map_rgba_f(0, 0, 0, .5), 40, 24, 0);

			if (mouse.buttons & 1)
			{
				al_draw_tinted_bitmap(dice[0], al_map_rgba_f(0, 1, 0, .5), 40, 24, 0);
				guessnum = 1;
				actnum = (rand() % 6) + 1;
				reveal = true;
			}
		}

		al_draw_bitmap(dice[1], 100, 24, NULL);

		if (x > 100 && x < 150 && y > 24 && y < 74)
		{
			al_draw_tinted_bitmap(dice[1], al_map_rgba_f(0, 0, 0, .5), 100, 24, 0);
			if (mouse.buttons & 1)
			{
				al_draw_tinted_bitmap(dice[1], al_map_rgba_f(0, 1, 0, .5), 100, 24, 0);
				guessnum = 2;
				actnum = (rand() % 6) + 1;
				reveal = true;
			}
		}

		al_draw_bitmap(dice[2], 160, 24, NULL);

		if (x > 160 && x < 210 && y > 24 && y < 74)
		{
			al_draw_tinted_bitmap(dice[2], al_map_rgba_f(0, 0, 0, .5), 160, 24, 0);
			if (mouse.buttons & 1)
			{
				al_draw_tinted_bitmap(dice[2], al_map_rgba_f(0, 1, 0, .5), 160, 24, 0);
				guessnum = 3;
				actnum = (rand() % 6) + 1;
			}
		}

		al_draw_bitmap(dice[3], 40, 84, NULL);

		if (x > 40 && x < 90 && y > 84 && y < 134)
		{
			al_draw_tinted_bitmap(dice[3], al_map_rgba_f(0, 0, 0, .5), 40, 84, 0);
			if (mouse.buttons & 1)
			{
				al_draw_tinted_bitmap(dice[3], al_map_rgba_f(0, 1, 0, .5), 40, 84, 0);
				guessnum = 4;
				actnum = (rand() % 6) + 1;
				reveal = true;
			}
		}

		al_draw_bitmap(dice[4], 100, 84, NULL);

		if (x > 100 && x < 150 && y > 84 && y < 134)
		{
			al_draw_tinted_bitmap(dice[4], al_map_rgba_f(0, 0, 0, .5), 100, 84, 0);
			if (mouse.buttons & 1)
			{
				al_draw_tinted_bitmap(dice[4], al_map_rgba_f(0, 1, 0, .5), 100, 84, 0);
				guessnum = 5;
				actnum = (rand() % 6) + 1;
				reveal = true;
			}
		}

		al_draw_bitmap(dice[5], 160, 84, NULL);

		if (x > 160 && x < 210 && y > 84 && y < 134)
		{
			al_draw_tinted_bitmap(dice[5], al_map_rgba_f(0, 0, 0, .5), 160, 84, 0);
			if (mouse.buttons & 1)
			{
				al_draw_tinted_bitmap(dice[5], al_map_rgba_f(0, 1, 0, .5), 160, 84, 0);
				guessnum = 6;
				actnum = (rand() % 6) + 1;
				reveal = true;
			}
		}


		if (reveal)
		{
			if (guessnum == actnum)
			{
				al_draw_text(font, al_map_rgb(255, 255, 255), 0, 230, 0, "CORRECT!! PLAY AGAIN!");
			}

			else
			{
				al_draw_text(font, al_map_rgb(255, 255, 255), 0, 230, 0, "WRONG!! TRY AGAIN");
				al_draw_bitmap(dice[actnum - 1], 200, 230, NULL);
			}
		}
		

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_font(font);
	al_destroy_event_queue(ev);
	al_destroy_timer(timer);
	for (int i = 0; i < 6; i++)
	{
		al_destroy_bitmap(dice[i]);
	}
	
	al_destroy_display(Window);

	return 0;
}

