# 버텍스 프로세싱 및 드로잉 커맨드



----------------

## 버텍스 프로세싱



### 버텍스 쉐이더 입력

- 버텍스 쉐이더 이전 버텍스 관련 입력을 구성해야한다.
- glVertexAttribPointer로 버퍼를 버텍스 쉐이더에 입력으로 연결한다.
- 입력을 넣는 저수준의 함수도 지원한다.



[함수]

- glVertexAtrribFormat
- glVertexAttribBinding
- glBindVertexBuffer



### 버텍스 쉐이더 출력

- vec4 gl_Position :  변환된 정점의 위치

- float gl_PointSize : 점의 크기

- float gl_ClipDistance[] : 클리핑에 사용됨



----------------

## 드로잉 커맨드



### 인덱스된 모델 드로잉 커맨드

- glDrawArrays의 경우 인덱스 되지 않은 모델에 대한 드로잉 커맨드이다.
- 인덱스된 모델의 경우 GL_ELEMNET_ARRAY_BUFFER로 인덱스 데이터를 바인딩해야한다.
- 그리고 드로우 커맨드는 glDrawElements를 사용한다.

인덱스 예제 : [[인덱스된 모델 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C07_DrawIndexedModel)

이 예제는 Object 파일을 읽어서 사용한다. 

초보시절 만들었던 Object를 열었다. meshlab으로 열면 다음과 같이 보인다.

- (노멀 값이 잘못되어 오류가 있다. 실제로 파일을 열어 보면 normal 값이 들어 있지 않은데 이는 모든 오브젝트가 ccw로 구성되지 않았기 때문이다.)

![1562325330911](https://github.com/rlatkddn212/opengl_super_bible/blob/master/assets/1562325330911.png)

예제를 실행시키면 아래와 같이 랜더링 된다. ObjModel.cpp에서 Obj파일에 기본적인 정보만 읽고 있는데 그 소스파일을 분석하면 어떤식으로 모델을 읽게 되는지 알 수 있다.

![1562325265481](https://github.com/rlatkddn212/opengl_super_bible/blob/master/assets/1562325265481.png)

### 베이스 버텍스

- glDrawElementsBaseVertex()

  - 시작 index 위치를 지정한다.



### 프리미티브 재시작

- GL_PRIMITIVE_RESTART를 활성화 시켜 사용한다.

프리미티브 재시작 예제 C07_PrimitiveRestart(TODO)



### 인스턴스

- vertex Array와 index 를 지원한다.

  - glDrawArraysInstanced

  - glDrawElementsInstanced

- vertexshader에 gl_InstanceID로 각 인스턴스를 구분할 수 있다.

- vertex buffer에 데이터를 인스턴스로 사용할 수 있도록 분리해 줄 수 있다.

  - glVertexAttribDivisor 함수를 사용한다.



인스턴스 예제 : [[인스턴스 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C07_InstancedModel)

Texture Array와 똑같이 랜더링 되지만 Instance를 추가했기 때문에 Draw Call을 절약할 수 있다.

![1562336322590](https://github.com/rlatkddn212/opengl_super_bible/blob/master/assets/1562336322590.png)



### indirect Draw

- Draw 할 때 필요한 인자를 미리 저장해 두거나 인자를 실시간으로 생성하여 변경할 수 있는 방법
- glDrawElements



예제 추가(TODO)



--------------------

## 변환된 버텍스



### 변환 피드백



변환 피드백 예제 : [[변환 피드백 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C07_TransformFeedBack)

- 책에 변환 피드백 예제에서는 스프링 메쉬를 구현한다.
- 스프링의 경우 후크의 법칙에 의해 아래와 같은 공식이 적용된다.
  - 힘 F = -스프링 상수 k * 늘어난 길이 x
  - 스프링에 가지는 기본 길이가 있으니 그점도 고려해야한다.
  - 고등학교 물리책엔 용수철이라고 부른다. :)
  - 방향까지 고려한다면 f = - ()



---------------------

## 클리핑



### 사용자 정의 클리핑

- 내장 변수 gl_ClipDistance[]를 사용하여 클립 거리 값을 사용가능

  - 평면의 방정식 ax + by + cz +d = 0 일 때 평면의 면 방향 h = (a,b,c) 이다. 이점을 이용하여 h와 점의 위치를 내적하여 음수 일 경우 vertex를 클리핑하면된다.

  - 평면을 클리핑하는 방법 이외에도 gl_ClipDistance를 음수로 만들 경우 클리핑 되기 때문에 다양한 방법으로 클리핑을 적용할 수 있다. (책 예제에서는 원으로 클리핑한다.)



사용자 정의 클리핑 예제 : [[사용자 정의 클리핑 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C07_ClipDistance)

- 예제는 폴리곤의 일부를 vertexShader에서 클리핑한다.

![1562405034928](https://github.com/rlatkddn212/opengl_super_bible/blob/master/assets/1562405034928.png)



------------------

