    Geometry shaders http://www.kdab.com/opengl-in-qt-5-1-part-5/
    requires version 3.2
    dummy draw command with empty VBO
    glDrawArrays(GL_POINTS, 0, 1);

    shader->release();


    // reading the contents of a file	
   QFile f("/home/eric/Developer/glsl-playground/shaders/test_shader1.frag");
   if (!f.open(QFile::ReadOnly | QFile::Text)) {
       qDebug() << "could not open file!";
       SAFE_DELETE(m_shaderprogram)
   }
   QTextStream in(&f);
   QString code = in.readAll();
   qDebug() << code;

   bool ok = m_shaderprogram->addShaderFromSourceCode(QGLShader::Fragment,code);
