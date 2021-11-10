# Distract

## The Pausable Clock

The pausable clock is a clock that can be paused and resumed.

Like literraly ...

Yes it is a clock.

No more seriously it permits to easily turn off your entities rountine.

The way it's used is like this:

```c
// considering a player you could

void update_player(game_t *game, entity_t *entity)
{
    player_t *player = entity->instance;

    tick_pausable_clock(player->movement_clock);
    if (player->movement_clock.time >= 0.3) {
        // do something
    }
}
```
So the movement of the player is automatized but you can pause it by setting the is_paused variable to true.

Here are the possibilities of the pausable clock:
```c
///
/// Create a clock that can be paused.
///
pausable_clock_t *create_pausable_clock(game_t *game);

///
/// Update the clock time.
///
float tick_pausable_clock(pausable_clock_t *clock);

///
/// Destroy the clock that can be paused.
///
void destroy_pausable_clock(pausable_clock_t *clock);

///
/// Restart the clock.
///
void restart_pausable_clock(pausable_clock_t *clock);
```
