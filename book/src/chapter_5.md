# Distract

## The sound emitter:

If you need to play a sound, you can of course use the resources sound and music.

But if you want to manager easily the sounds, you can use the sound emitter.

The sound emitter will provide you with a list of volumes that you cna use to play the sounds.

The play_sound method will play the sound with the given volume.
Same for the distract_music method.

But be careful to check the return value of the methods.
If the sound is not found, the method will return false and an error will be displayed.

```c
bool play_distract_sound(game_t *game, int distract_sound_type, char *file);
bool play_distract_music(game_t *game, int distract_sound_type, char *file);
void set_distract_sound_volume(game_t *game, unsigned char distract_sound_type, float percentage);
float get_distract_sound_volume(game_t *game, unsigned char distract_sound_type);
```