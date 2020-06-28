#ifndef _TRIANGLE_H
#define _TRIANGLE_H

const constexpr static char* screenVertexSource[] = {
    "#version 300 es\n"
    "in lowp vec2 vPos;"
    "in lowp vec3 vCol;"
    "uniform mat4 MVP;"
    "out lowp vec3 i_color;"
    "void main() {"
    "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);"
    "    i_color = vCol;"
    "}"
};

const constexpr static char* screenFragmentSource[] = {
    "#version 300 es\n"
    "in lowp vec3 i_color;"
    "out lowp vec4 o_color;"
    "void main() {"
    "    o_color = vec4(i_color, 1.0);"
    "}"
};

static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};

class Triangle {
    GLint mvp_location, vpos, vcol;
    GLuint vbo;

    const std::unique_ptr<Shader> mShader;

public:
    Triangle():
        mShader(std::make_unique<Shader>(screenVertexSource, screenFragmentSource))
    {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        mShader->link();
        mvp_location = mShader->getUniformLocation("MVP");
        vpos = mShader->getAttributeLocation("vPos");
        vcol = mShader->getAttributeLocation("vCol");

        Log::debug("mvp=%d  vpos=%d  vcol=%d", mvp_location, vpos, vcol);

        glEnableVertexAttribArray(vpos);
        glEnableVertexAttribArray(vcol);

        glVertexAttribPointer(vpos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) 0);
        glVertexAttribPointer(vcol, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (sizeof(float) * 2));

        glDisableVertexAttribArray(vpos);
        glDisableVertexAttribArray(vcol);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        mShader->stop();
    }

    virtual ~Triangle() {
        glDeleteBuffers(1, &vbo);
    }

    void render(const Matrix4x4& mvp) {
        mShader->run();
        // glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) _mvp);        
        mShader->set("MVP", mvp);

        // glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glEnableVertexAttribArray(vpos);
        glEnableVertexAttribArray(vcol);

        // glVertexAttribPointer(vpos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) 0);
        // glVertexAttribPointer(vcol, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (sizeof(float) * 2));

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(vpos);
        glDisableVertexAttribArray(vcol);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        mShader->stop();
    }
};


#endif
