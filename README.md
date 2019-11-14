# LearnOpenGL
OpenGL学习项目
1. 库依赖：项目需要的外部库，存放于/Libraries目录下；
  其中/include为项目所需的头文件，通过 项目-属性-VC++目录-包含目录添加
  /libs为项目所需的库文件，通过 项目-属性-VC++目录-库目录添加；其他VS版本需要的库也在该目录下
  此外，需要添加附加依赖项，第一次项目，只需要包含opengl32.lib和glfw.lib即可
