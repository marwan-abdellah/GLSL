#version 150

layout(triangles) in;
layout (triangle_strip, max_vertices=6) out;

uniform mat4 viewMatrix, projMatrix;
uniform vec2 halfPixelSize;

/// OUT
out vec3 positionToFrag;
out vec4 vertexAABBToFrag;
out vec4 vertexColorToFrag;

void main(void)
{
    // Index
    int i;

    // Vertex array for each triangle
    vec4 vertex[3];

    // Vertex XY position
    vec2 position[3];

    // AABB initialized with maximum/minimum NDC values.
    vec4 aabb = vec4(1.0, 1.0, -1.0, -1.0);

    // For each vertex in the input triangle
    for( i = 0; i < gl_in.length(); i++ )
    {
        // Get the vertex position
        vertex[i] = projMatrix * viewMatrix * gl_in[i].gl_Position;

        // Later NDC position if each fragment
        position[i] = vertex[i].xy / vertex[i].w;

        // Get AABB of the triangle
        aabb.xy = min( aabb.xy, position[i].xy );
        aabb.zw = max( aabb.zw, position[i].xy );
    }


    // Calculate triangle for conservative rasterization.
    // Add offset of half pixel size to AABB.
    vec4 aabbConservative = aabb + vec4( -halfPixelSize, halfPixelSize );

    vec3 plane[3];
    for( i = 0; i < gl_in.length(); i++ )
    {
        // Calculate the plane through each edge of the triangle.
        // The plane equation is A * x + B * y + C * w = 0.
        // Note, that D component from the plane is zero, as it goes throught
        // the origin. Also, w is used as the third dimension.
        // The plane goes through the origin, such as
        // (vertex[i].x, vertex[i].y, vertex[i].w) are vectors from the origin.
        // A * x + B * y + C * w = 0 <=> A * x / w + B * y / w + C = 0 [w != 0]
        // is equivalent to  A * xClip + B * yClip + C
        // A * xClip + B * yClip + C is a vector in 2D space.
        // In this case, it is the normal of the edge in 2D space.
        // By calculating the cross product of the two vectors (the end points
        // of the edge), we gather the normal of the plane.
        plane[i] = cross( vertex[i].xyw, vertex[(i + 2) % 3].xyw );

        // Move plane, by adjusting C.
        // Note: A * ( x + dx ) + B * ( y + dy ) + C * w = 0
        // [Another plane with a specific distance d given by dx and dy] <=>
        //  A * x + A * dx + B * y + B * dy + C * w = 0 <=>
        //  A * xClip + B * yClip + C + A * dx + B * dy = 0

        // Half pixel size is d. Absolute of plane's xy, as the sign is already
        // in the normal of the plane.
        plane[i].z -= dot( halfPixelSize, abs( plane[i].xy ));
    }



    // Create conservative, RED RASTERIZED triangle
    vec3 intersect;
    for( i = 0; i < gl_in.length(); i++ )
    {
        // As both planes go through the origin, the intersecting line goes also
        // through the origin. This simplifies the intersection calculation.
        // The intersecting line is perpendicular to both planes (see Wolfram
        // MathWorld), so the intersection line is just the cross product of
        // both normals.
        intersect = cross( plane[i], plane[( i + 1 ) % 3] );

        // The line is a direction (x, y, w) but projects to the same point in
        // window space.
        // Compare: ( x, y, w ) <=> ( x / w, y / w, 1 ) => ( xClip, yClip )
        gl_Position.xyw = intersect;
        gl_Position.z = 0;

        // Later NDC position if each fragment.
        positionToFrag.xy = intersect.xy / intersect.z;
        vertexAABBToFrag = aabbConservative;
        vertexColorToFrag = vec4(1.0, 0.0, 0.0, 0.1);

        // Done for the vertex
        EmitVertex();
    }

   EndPrimitive();

   // Create NORMAL, BLUE RASTERIZED triangle for comparison.
   for( i = 0; i < gl_in.length(); i++ )
   {
       gl_Position = vertex[i];
       gl_Position.z = -1;

       positionToFrag.xy = position[i];
       vertexAABBToFrag = aabb;
       vertexColorToFrag = vec4( 0.0, 0.0, 1.0, 0.1 );

       // Done for the vertex
       EmitVertex();
   }

   // Done for the triangle
   EndPrimitive();
}
