#version 150

/// IN
in vec3 positionToFrag;
in vec4 vertexAABBToFrag;
in vec4 vertexColorToFrag;

out vec4 outputF;

void main(void)
{
    // Discard pixels, which are not inside the AABB.
    if( positionToFrag.x < vertexAABBToFrag.x || positionToFrag.y < vertexAABBToFrag.y ||
            positionToFrag.x > vertexAABBToFrag.z || positionToFrag.y > vertexAABBToFrag.w )
    {
        discard;
    }

    outputF = vertexColorToFrag;
}
