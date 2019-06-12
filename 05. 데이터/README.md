# 데이터

- 이번 챕터는 분량이 많다. 책으로도 90 페이지가량..
- OpenGL은 많은 량의 데이터를 처리하고 생성할 수 있는 스트리밍 프로세서 방식

- OpenGL은 2가지 형태의 데이터 스토리지를 제공
  - 버퍼 : 데이터의 연속 공간 (메모리 할당과 유사함)
  - 텍스쳐 : 이미지 같은 다차원 데이터를 저장하기 위해 사용됨

-----------

### 버퍼

- 버퍼를 사용하기 전 이름을 예약해야함 -> glGenBuffers
- 그 이름을 사용하여 메모리를 할당하고 저장 할 수 있음 -> glBufferData
- OpenGL Context에서 그 이름을 bind 해줘야 사용할 수 있음  -> glBindBuffer



#### 버퍼를 사용하여 메모리 할당

- glBufferData를 사용하여 메모리 할당을 할 수 있음



[함수]

- glBufferData
  - 설명 : 버퍼 객체를 사용하여 메모리 할당
  - GLenum target : 버퍼가 어떤 타겟에 바인딩 될지 알려준다. GL_ARRAY_BUFFER
  - GLsizeiptr size : 버퍼 사이즈
  - const GLvoid * data : 데이터
  - GLenum usage : 사용 목적, GL_STREAM_DRAW
  
- glGenBuffers
  
  - 설명 : 버퍼에 대한 이름을 예약한다.
  - GLsizei n : 버퍼의 이름의 개수 지정
  - GLuint * buffers : 버퍼의 이름을 개수만큼 배열에 저장
  
- glBindBuffer
  - 설명 : OpenGL context에 해당 버퍼를 바인딩한다.
  - GLenum target : bind 대상을 지정 (인덱스를 사용하는지 지정)
  
  - GLuint buffer : 버퍼의 이름
  
- glBufferSubData
  - 설명 : 버퍼 데이터에 subset을 변경(update)한다.
  - GLenum target : 어떤 타겟에 바인딩 하는지
  - GLintptr offset : 버퍼 데이터를 대체할 시작 위치
  - GLsizeiptr size : 데이터를 변경할 사이즈
  - const GLvoid * data : 변경할 새로운 데이터
  
- glMapBuffer

  - 설명 : 직접 데이터를 복사 할 수 있도록 사용자의 주소공간(주 메모리)에 매핑, void*를 리턴 받아 그 곳에 값을 채운 후 glUnmapBuffer를 호출한다.
  - GLenum target : 어떤 타겟 버퍼를 맵핑하는지 지정
  - GLenum access : 접근 방식을 지정함



#### 버퍼에 데이터 채우기 및 복사

버퍼에 저장하는 데이터가 하나의 상수 값일 경우 사용

- glClearBufferSubData
  - 고정된 하나의 상수 값으로 버퍼를 채운다.
- glCopyBufferSubData
  - 버퍼 데이터를 다른 버퍼로 복사한다.



#### 버텍스 쉐이더에 입력 전달

정점 데이터, uv 데이터, 노멀데이터 등 각 속성들이 버퍼에 어디에 위치하는지 알아야 한다.

데이터를 입력한 방식에 따라 버퍼의 위치가 달라지기 때문에 glVertexAttribPointer를 사용하여 위치를 지정해 줄 수 있다.



[함수]

- glVertexAttribPointer

  - 버퍼의 속성 값의 위치와 속성값의 데이터 형식을 지정함
  - GLuint index : 속성의 인덱스를 지정함
	- GLint size : 버텍스 속성의 사이즈
	- GLenum type : 데이터 타입
	- GLboolean normalized : 데이터를 0~1 사이 값으로 정규화할 것인지 지정
	- GLsizei stride : 버텍스와 다음 버텍스 사이에 크기가 얼마인지 지정 (0으로 넣을 경우 자동으로 계산됨)
	- const GLvoid * pointer : 속성 데이터가 시작하는 offset

- glEnableVertexAttribArray

  - 버퍼의 속성 값을 활성화한다.

  - GLuint index : glVertexAttribPointer에서 설정한 위치

- glDisableVertexAttribArray

  - 버퍼의 속성값을 비활성화한다.




#### 버텍스 쉐이더에 입력 여러개 전달할 때

- 버텍스 쉐이더 입력을 애플리케이션 데이터로 연결하는 방법
  - structure of array
    - 여러개의 배열 point, uv, normal이 독립적으로 있을 때
  - array of structure
    - point, uv, normal 값이 구조체로 저장된 배열 일 때  



[함수]

- giGetAttribLocation
  - 설명 : 배열의 속성값 위치를 가져온다.



--------------------

### 유니폼

- 스토리지 형태가 아님
- 버텍스 속성의 경우 버텍스 별로 존재하지만 유니폼의 경우 전체 프리미티브에 대한 상수 값으로 존재
- 쉐이더로 데이터를 전달 할 수 있음
- 디폴트 블록 유니폼, 유티폼 블록 2가지 타입이 있다.



#### 디폴트 유니폼 블록

- 쉐이더에서는 변수 선언 앞에 uniform 키워드를 붙여 주기만 하면 됨
- 레이아웃 지시어를 통해 유니폼 위치를 지정 할 수 있다.(이 값은 애플리케이션에 지정한 위치와 연결된다.)



[함수]

- glGetUniformLocation
  - 설명 : 유니폼이 어떤 위치에 할당되었는지 확인할 수 있다.
- glUniform*
  - 설명 : 유니폼 값을 지정한다. * 에는 데이터 타입, 스칼라, 벡터, 행렬 타입이 지정된다.



#### 유니폼 블록

- 많은 상수 데이터를 사용할 경우 이를 모두 쉐이더로 전달하면 비효율적이된다.
  - glUniform* 함수 호출이 많아지기 때문
- 이를 단순화 하기 위해 유니폼 블록으로 그룹화 할 수 있다.
- 기존 유니폼과는 다르게 버퍼를 사용하여 블록을 만들 수 있다.
  - GL_UNIFORM_BUFFER 로 버퍼 공간을 bind하고 Data 공간을 생성해주면된다.
- 유니폼 버퍼 쉐이더 코드

```
layout (std140) uniform ExampleBlock
{
    float value;
    vec3  vector;
    mat4  matrix;
    float values[3];
    bool  boolean;
    int   integer;
};  
```

- std140의 경우 OpenGL 기본 패킹 룰 사용을 지정한다.
  - 메모리 정렬의 의미
- C++과 OpenGL 패킹 룰이 다르다. std140의 패킹 룰은 아래와 같다.

```
layout (std140) uniform ExampleBlock
{
                     // base alignment  // aligned offset
    float value;     // 4               // 0 
    vec3 vector;     // 16              // 16  (must be multiple of 16 so 4->16)
    mat4 matrix;     // 16              // 32  (column 0)
                     // 16              // 48  (column 1)
                     // 16              // 64  (column 2)
                     // 16              // 80  (column 3)
    float values[3]; // 16              // 96  (values[0])
                     // 16              // 112 (values[1])
                     // 16              // 128 (values[2])
    bool boolean;    // 4               // 144
    int integer;     // 4               // 148
}; 
```

- 기본적으로 4바이트 패딩으로 보이는데, float 배열 요소 하나의 크기가 16 byte..가 될 수 있다.
-  위 예제는 [LearnOpenGL](https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL)에서 가져왔다.



#### 유니폼을 사용한 지오메트리 변환

예제 프로그램 TODO



------------

### 쉐이더 스토리지 블록

- 쉐이더 스토리지 블록을 사용하면 유니폼 블록과 다르게 쉐이더에서 쓰기 공간으로사용할 수 있음
- write 가 가능 해지므로 아토믹 연산이 필요해진다.
  - 쉐이더 코드가 병렬처리로 동작하기 때문에 쓰기 동작의 경우 레이스 컨디션, 명령어 정렬 문제가 생길 수 있다.
- 버퍼 타겟을 GL_SHADER_STORAGE_BUFFER로 설정하면 된다.
- 쉐이더 코드에는 유니폼 블록과 동일한 문법에 buffer 키워드를 붙여주면된다.
- std430 패킹룰을 사용한다
  - std140 보다 촘촘하게 패킹한다.



-----------

### 어토믹 카운터

- 버퍼 객체를 생성할 때 GL_ATOMIC_COUNTER_BUFFER로 생성한다.
- 어토믹 카운터 예제 (TODO)



---------

### 텍스처

-  쉐이더가 읽고 쓸 수 있는 스토리지 영역이다.



#### 텍스쳐 생성 초기화

[함수]

- glGenTextures
- glBindTexture
- glTexStorage2D
- glTexSubImage2D



#### 텍스쳐 target, type



#### 셰이더에서 텍스쳐 읽기



#### 파일에서 텍스쳐 로딩



#### 텍스처 데이터 제어



#### 배열 텍스쳐



#### 쉐이더에서 텍스쳐 출력



#### 이미지 접근 동기화



#### 텍스쳐 압축







-------------------