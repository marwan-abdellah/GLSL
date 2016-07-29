void main( void )
{
    /// GIVE THE SAME RESULT
    // gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    // gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_Position = ftransform();
}
