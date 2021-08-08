# Distract

## Resources in General:

As seen before the resources are managed automatically by the system.

Everything is destroyed when the scene is ended.

The list of resources that exists are:
    - sfTexture *,
    - sfFont *,
    - sfSound *,
    - sfMusic *,
    - sfSoundBuffer *,
    - sfVertexArray *

## How to store/get a resource:
```c
distract_resource_t *create_distract_resource(game_t *game, char *file, enum distract_resource_type type);
```
Would be the first one coming to mind.
But it is not the only way to store/get a resource.

Some functions are provided to help you such as seen before:
```c
sfFont *create_font(game_t *game, char *filepath);
sfSound *create_distract_sound(game_t *game, char *filepath);
sfMusic *create_distract_music(game_t *game, char *filepath);
sfVertexArray *create_vertex(game_t *game, char *filepath);
sfTexture *create_texture(game_t *game, char *filepath);
```

Thoses all uses the same function: create_distract_resource.
But really consider using the wrappers which are more convenient.

One thing important is about the create_vertex function.
The "filepath" argument is not the path to the file, but the name of the vertex array.

If you want to create a resource please be sure to name it carefully.
For example:
```c
sfTexture *tx = create_texture(game, "my_texture.png");
sfTexture *tx2 = create_texture(game, "my_texture.png");

// Tx and tx2 are the same texture. because they have the same name.
// The system will recognize that and will not create a new resource.
// So you can freely "create" multiple times the same resource.
```

But for vertex arrays you must be careful.
If you use the same name twice for the same vertex array, the system will not create a new resource.
So you will end up with two vertex arrays with the same pointer in memory.
That could lead up to very bad things.
So name your vertex arrays carefully!

## Behind the scenes: (advanced)

Thoses are stored in a tagged union type (This is some advanced stuff to understand the back-end of Distract but you can give it a try if you want).

The struct is :
```c
typedef struct distract_resource {
    enum distract_resource_type type;
    char *path;
    union {
        sfTexture *texture;
        sfMusic *distract_music;
        sfSoundBuffer *distract_sound_buffer;
        sfSound *distract_sound;
        sfFont *font;
        sfVertexArray *vao;
    };
} distract_resource_t;
```
The type of the resource is stored in the type field and path is the path to the file (or name of the vertex array).
[Jacob Sorber Union Data Types](https://www.youtube.com/watch?v=b9_0bqrm2G8)