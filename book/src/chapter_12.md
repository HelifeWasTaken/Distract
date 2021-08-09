# Distract

## Advanced Graphics

### What is a Vertex ?

What is a vertex, and why are they always in arrays?

A vertex is the smallest graphical entity that you can manipulate. In short, it is a graphical point: Naturally, it has a 2D position (x, y), but also a color, and a pair of texture coordinates. We'll go into the roles of these attributes later.

Vertices (plural of vertex) alone don't do much. They are always grouped into primitives: Points (1 vertex), lines (2 vertices), triangles (3 vertices) or quads (4 vertices). You can then combine multiple primitives together to create the final geometry of the entity.

### Your First Vertex Buffer

For example this code will generate you nice little triangle to visualize
```c
sfVertexArray *vertices = create_vertex(game, "My Random Vertex Array");
sfVertexArray_setPrimitiveType(vertices, SF_TRIANGLES);
sfVertexArray_resize(vertices, 3);
sfVertex *vertex = sfVertexArray_getVertex(vertices, 0);

vertex[0].position = (sfVector2f){10.0f, 10.0f};
vertex[1].position = (sfVector2f){100.0f, 10.0f};
vertex[2].position = (sfVector2f){100.0f, 100.0f};
vertex[0].color = sfRed;
vertex[1].color = sfGreen;
vertex[2].color = sfBlue;

// To draw the vertex array
sfRenderWindow_drawVertexArray(game->window, vertices);
```

There is a full List of primitive types in the [SFML Primitives](http://www.sfml-dev.org/documentation/1.6/namespacesf_1_1Primitive.php) documentation.
Please have a look at it.

I recommend you to check out the section about TileMapping if you want to understand how to use the Vertex Array very well. But be aware that the documentation is in C++ and it uses some RenderStates not aviable in C. So some implementations need to be done by hand.

Especially the RenderState. Your Vertex Array will be transparant, if you use the default RenderState.

### Your first Advanced Tilemap (Or maybe just your first Tilemap):

Here is an example of a oDistract Entity Tilemap that uses the Vertex Array:

```c

struct tilemap {
    sfVertexArray *vertices;
    sfTexture *texture;
    entity_t *entity;
};

static void tilemap_load(tilemap *tilemap, unsigned int *map_data, sfVector2u tile_size, sfVector2u map_size)
{
    sfVertexArray_setPrimitiveType(tilemap->vertices, SF_QUADS);
    sfVertexArray_resize(tilemap->vertices, map_size.x * map_size.y);
    for (unsigned int x = 0; i < map_size.x; i++) {
        for (unsigned int y = 0; y < map_size.y; y++) {
            int tile = map_data[x + y * map_size.x];
            int tu = tile % (sfTexture_getSize(tilemap->texture) / tile_size.x);
            int tv = tile / (sfTexture_getSize(tilemap->texture) / tile_size.x);
            sfVertex *quad= sfVertexArray_getVertex(tilemap->vertices, (x + y * map_size.x) * 4);
            quad[0].position = (sfVector2f){(float)x * tile_size.x, (float)y * tile_size.y};
            quad[1].position = (sfVector2f){(float)(x + 1) * tile_size.x, (float)y * tile_size.y};
            quad[2].position = (sfVector2f){(float)(x + 1) * tile_size.x, (float)(y + 1) * tile_size.y};
            quad[3].position = (sfVector2f){(float)x * tile_size.x, (float)(y + 1) * tile_size.y};
            quad[0].texCoords = (sfVector2f){(float)tu * tile_size.x, (float)tv * tile_size.x};
            quad[1].texCoords = (sfVector2f){(float)(tu + 1) * tile_size.x, (float)tv * tile_size.x};
            quad[2].texCoords = (sfVector2f){(float)(tu + 1) * tile_size.x, (float)(tv + 1) * tile_size.x};
            quad[3].texCoords = (sfVector2f){(float)tu * tile_size.x, (float)(tv + 1) * tile_size.x};
        }
    }
}

bool create_tilemap(game_t *game, entity_t *entity)
{
    tilemap_t *tilemap = calloc(1, sizeof(tilemap_t));

    if (tilemap == NULL) {
        fprintf(stderr, "Failed to allocate memory for tilemap\n");
        return false;
    }
    tilemap->entity = entity;
    entity->instance = tilemap;
    tilemap->texture = create_texture(game, "tilemap.png");
    tilemap->vertices = create_vertex(game, "an original vertex array name");
    if (tilemap->texture == NULL || tilemap->vertices == NULL) {
        fprintf(stderr, "Failed to allocate memory for tilemap\n");
        return false;
    }
    // Considering that you uses a config file that gives you info about the map etc...
    // Tiled is a good choice to generate the maps.
    // Otherwise for this tutorial you can just create a static array such as the SFML tutorial does.
    // Json works well with Tiled consider using it!
    // We will use static arrays and the image of the SFML tutorial for this.
    const int level[] = {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };
    tilemap_load(tilemap, level, (sfVector2u){32, 32}, (sfVector2u){16, 8});
    return true;
}

// The handle event and update function
// You may need it if you have special event occuring in your game changing the map look

void draw_tilemap(tilemap_t *tilemap)
{
    sfRenderStates state = DEFAULT_RENDERSTATE(NULL);

    state.texture = tilemap->texture;
    sfRenderWindow_drawVertexArray(game->window, tilemap->vertices, &state);
}
```

The default RenderState macro is this one:
```c
#define DEFAULT_RENDERSTATE(shader) \
    (sfRenderStates) { sfBlendAlpha, sfTransform_Identity, NULL, shader }
```
This permits to the VertexArray that has no render states to be transformable and to be transparant.

The NULL is the shader that will be used. If you do not use a shader, you can use the default one.

You can also notice that you had to set the texture to the VertexArray.

### The Shader

 A shader is a small program that is executed on the graphics card. It provides the programmer with more control over the drawing process and in a more flexible and simple way than using the fixed set of states and operations provided by OpenGL. With this additional flexibility, shaders are used to create effects that would be too complicated, if not impossible, to describe with regular OpenGL functions: Per-pixel lighting, shadows, etc. Today's graphics cards and newer versions of OpenGL are already entirely shader-based, and the fixed set of states and functions (which is called the "fixed pipeline") that you might know of has been deprecated and will likely be removed in the future.

Shaders are written in GLSL (OpenGL Shading Language), which is very similar to the C programming language.

There are three types of shaders:
- Vertex Shaders
- Fragment Shaders
- Geometry Shaders

The shaders are read and compiled at runtime, and are executed on the graphics card.

### How to load a shader ?

We have thoses functions:
```c
sfShader* sfShader_createFromFile(const char* vertexShaderFilename, const char* geometryShaderFilename, const char* fragmentShaderFilename);

sfShader* sfShader_createFromMemory(const char* vertexShader, const char* geometryShader, const char* fragmentShader);
```

If one of thoses arguments is NULL, the specified shader is skipped.

So to create a shader for vertex you can do it this way:
```c
#include <SFML/OpenGL.hpp>
sfShader *shader = sfShader_createFromFile("vertex.glsl", NULL, NULL);
if (shader == NULL) {
    fprintf(stderr, "Failed to load vertex shader\n");
    return false;
}
```
Or this way:
```c
#include <SFML/OpenGL.hpp>

static char const *VERTEX_SHADER_CODE =
"void main()\n" \
"{\n" \
"    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n" \
"}"; // for example

sfShader *shader = sfShader_createFromMemory(VERTEX_SHADER_CODE, NULL, NULL);
if (shader == NULL) {
    fprintf(stderr, "Failed to load vertex shader\n");
    return false;
}
```

I shall recommend checking the [OpenGL Shading Language](http://www.opengl.org/wiki/Shading_language) page for more information about GLSL for more details.

And the [CSFML Shader Header](https://github.com/SFML/CSFML/blob/master/include/SFML/Graphics/Shader.h)

Do not forget to also deallocate the shader when you are done with it:
```c
sfShader_destroy(shader);
```