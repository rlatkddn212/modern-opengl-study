# 나의 첫번째 OpenGL 프로그램

- 어플리케이션 작성 방법을 알아본다.
- 삼각형을 하나 그려본다.



### 간단한 애플리케이션 작성



- C02_FirstProgram에 소스코드를 작성했다.
  - Release x64로 설정 후 실행해보자.



#### [함수]

- ClearBufferfv

  - 설명 : 화면 버퍼을 Clear한다. 함수 뒤 fv 의 의미는 float형 vector라는 의미이다.

  - GLenum buffer : 특정 버퍼를 클리어한다. color 버퍼, z 버퍼(깊이 버퍼), 스텐실 버퍼 등
  - GLint drawBuffer : 지울 출력 버퍼가 어려개 일 경우 사용한다.
  - const GLfloat* value : 이 인자 값으로 지워라.



### 쉐이더 사용하기

- C02_FirstProgram 프로젝트 파일에 쉐이더 파일인 vertex.glsl, Image.glsl 이 들어 있다.
  - 단순히 ifstream를 사용하여 파일을 읽은 후 사용한다.
  - 파일명은 원하는 이름으로 작성해도 상관없다. glsl 확장자 명도 필요없다.
- 쉐이더 소스 파일은 object파일로 컴파일(compile) 되고 하나의 프로그램으로 링크(link)된다.
  - 일반 소스파일 처럼 빌드 된다는 말이다. cpp도 마찬가지로 컴파일, 링크 과정을 거쳐 프로그램을 생성한다.
- 하나의 program Object는 여러개의 쉐이더 들을 포함할 수 있다.
  - 버텍스 쉐이더, 프래그먼트 쉐이더, 테셀레이션 쉐이더, 지오메트리 쉐이더, 컴퓨트 쉐이더
- 소스 파일에 #version 430 core는 쉐이더 프로그램의 버전을 의미한다.
- vertex.glsl 소스 파일에 gl_Position의 다른 쉐이더들과 연결되는 변수이다. gl_ 가 붙은 변수는 쉐이더나 고정 파이프라인에서 사용되어진다.
  - gl_Position의 기능을 설명하자면.. vertex 쉐이더가 정점들과 속성을 입력 받아 출력으로 정점을 반환하는 쉐이더인데 출력으로 사용될 vertex들이 들어가게된다.



#### [함수]

- glCreateShader
  - 쉐이더 객체를 생성한다.

- glShaderSource
  - 소스코드를 적용한다. (컴파일 전)
- glCompileShader
  - 쉐이더 소스코드를 목적(Object)파일로 컴파일한다.
- glCreateProgram
  - Shader를 적용시킬 프로그램 객체를 생성한다.
- glAttachShader
  - 쉐이더를 프로그램 객체에 장착(Attach)한다.
- glLinkProgram
  - 장착된 쉐이더들을 모두 링크시킨다.
- glDeleteShader
  - 프로그램을 링크 시켰으면 바이너리 코드로 보관 되기 때문에 기존 쉐이더를 지워 준다.



### 처음 그리는 삼각형

- VBO 생성, 뒤 챕터에서 배우겠지만 그래픽카드안에 vertex를 저장하는 버퍼이다.
- VAO 생성, VBO와 비슷하다. 뒤 챕터에서 다루게 된다. 사용방법만 봅시다.



### [함수]

- glGenVertexArrays
  - VAO를 생성한다.
- glBindVertexArray
  - context VAO를 연결(bind) 시킨다.
- glUseProgram
  - 쉐이더를 가지고 있는 프로그램을 사용한다.
- glDrawArrays
  - 정점(vertex)들을 그린다.



#### <실행 결과>

![1559881576469](C:\Users\swkim\AppData\Roaming\Typora\typora-user-images\1559881576469.png)



### 참고 자료

<http://www.opengl-tutorial.org/kr/beginners-tutorials/tutorial-2-the-first-triangle/>

꼭 보고 따라해보자.